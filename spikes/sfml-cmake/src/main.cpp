#include <SFML/Graphics.hpp>

#include <algorithm>
#include <cmath>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

namespace {

constexpr int tileSize = 30;

struct Player {
    sf::Vector2f position;
    sf::Vector2f direction;
    sf::Color color;
    int hp = 100;
    float cooldown = 0.f;
};

struct Bullet {
    sf::Vector2f position;
    sf::Vector2f direction;
    float ttl = 1.6f;
    int owner = 0;
};

std::filesystem::path repoPath(const std::string& relative) {
    return std::filesystem::path(REPO_ROOT) / relative;
}

std::vector<std::vector<int>> loadMap(const std::filesystem::path& path, int& width, int& height) {
    std::ifstream input(path);
    std::vector<std::vector<int>> rows;
    std::string line;

    while (std::getline(input, line)) {
        if (line.rfind("width=", 0) == 0) {
            width = std::stoi(line.substr(6));
        } else if (line.rfind("height=", 0) == 0) {
            height = std::stoi(line.substr(7));
        } else if (!line.empty() && std::isdigit(static_cast<unsigned char>(line[0]))) {
            std::vector<int> row;
            std::stringstream stream(line);
            std::string value;
            while (std::getline(stream, value, ',')) {
                if (!value.empty()) row.push_back(std::stoi(value) - 1);
            }
            rows.push_back(row);
        }
    }

    return rows;
}

sf::Vector2f normalize(sf::Vector2f value) {
    const float length = std::sqrt(value.x * value.x + value.y * value.y);
    if (length == 0.f) return {0.f, 0.f};
    return {value.x / length, value.y / length};
}

float distance(sf::Vector2f a, sf::Vector2f b) {
    const sf::Vector2f delta = a - b;
    return std::sqrt(delta.x * delta.x + delta.y * delta.y);
}

void updatePlayer(Player& player, float dt, sf::Keyboard::Key up, sf::Keyboard::Key down,
                  sf::Keyboard::Key left, sf::Keyboard::Key right, sf::Keyboard::Key fire,
                  int owner, std::vector<Bullet>& bullets, sf::Vector2f mapSize) {
    sf::Vector2f input{0.f, 0.f};
    if (sf::Keyboard::isKeyPressed(left)) input.x -= 1.f;
    if (sf::Keyboard::isKeyPressed(right)) input.x += 1.f;
    if (sf::Keyboard::isKeyPressed(up)) input.y -= 1.f;
    if (sf::Keyboard::isKeyPressed(down)) input.y += 1.f;

    const sf::Vector2f movement = normalize(input);
    if (movement.x != 0.f || movement.y != 0.f) player.direction = movement;

    player.position += movement * 180.f * dt;
    player.position.x = std::clamp(player.position.x, 20.f, mapSize.x - 20.f);
    player.position.y = std::clamp(player.position.y, 20.f, mapSize.y - 20.f);

    player.cooldown = std::max(0.f, player.cooldown - dt);
    if (sf::Keyboard::isKeyPressed(fire) && player.cooldown == 0.f) {
        bullets.push_back({player.position + player.direction * 24.f, player.direction, 1.6f, owner});
        player.cooldown = 0.35f;
    }
}

} // namespace

int main() {
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Our Very First Game - SFML spike");
    window.setFramerateLimit(120);

    int mapWidth = 100;
    int mapHeight = 100;
    const auto mapRows = loadMap(repoPath("The_Game/The_Game/Maps/mapa.txt"), mapWidth, mapHeight);
    const sf::Vector2f mapSize{static_cast<float>(mapWidth * tileSize), static_cast<float>(mapHeight * tileSize)};

    sf::Texture tileset;
    const bool hasTileset = tileset.loadFromFile(repoPath("The_Game/The_Game/Maps/mapa.png").string());

    sf::Texture playerTexture;
    const bool hasPlayerTexture = playerTexture.loadFromFile(repoPath("The_Game/The_Game/Images/player_1.png").string());
    sf::Sprite playerSprite;
    if (hasPlayerTexture) playerSprite.setTexture(playerTexture);

    Player p1{{220.f, 220.f}, {1.f, 0.f}, sf::Color(90, 190, 255)};
    Player p2{{580.f, 360.f}, {-1.f, 0.f}, sf::Color(255, 205, 100)};
    std::vector<Bullet> bullets;

    sf::Clock clock;
    while (window.isOpen()) {
        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed ||
                (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {
                window.close();
            }
        }

        const float dt = std::min(clock.restart().asSeconds(), 0.033f);
        updatePlayer(p1, dt, sf::Keyboard::W, sf::Keyboard::S, sf::Keyboard::A, sf::Keyboard::D,
                     sf::Keyboard::Space, 1, bullets, mapSize);
        updatePlayer(p2, dt, sf::Keyboard::Up, sf::Keyboard::Down, sf::Keyboard::Left, sf::Keyboard::Right,
                     sf::Keyboard::RControl, 2, bullets, mapSize);

        for (auto& bullet : bullets) {
            bullet.position += bullet.direction * 420.f * dt;
            bullet.ttl -= dt;
            Player& target = bullet.owner == 1 ? p2 : p1;
            if (distance(bullet.position, target.position) < 24.f) {
                target.hp = std::max(0, target.hp - 20);
                bullet.ttl = 0.f;
            }
        }
        bullets.erase(std::remove_if(bullets.begin(), bullets.end(), [](const Bullet& bullet) {
            return bullet.ttl <= 0.f;
        }), bullets.end());

        window.clear(sf::Color(20, 30, 24));
        const float panelWidth = 636.f;
        const sf::Vector2f focuses[] = {p1.position, p2.position};
        const Player players[] = {p1, p2};

        for (int panel = 0; panel < 2; ++panel) {
            sf::View view;
            view.setViewport(sf::FloatRect(panel == 0 ? 0.f : 0.503f, 0.f, 0.497f, 0.94f));
            view.reset(sf::FloatRect(
                std::clamp(focuses[panel].x - panelWidth / 2.f, 0.f, mapSize.x - panelWidth),
                std::clamp(focuses[panel].y - 338.f, 0.f, mapSize.y - 676.f),
                panelWidth,
                676.f
            ));
            window.setView(view);

            if (hasTileset && !mapRows.empty()) {
                sf::VertexArray quads(sf::Quads);
                const int columns = static_cast<int>(tileset.getSize().x) / tileSize;
                for (int y = 0; y < std::min<int>(mapRows.size(), mapHeight); ++y) {
                    for (int x = 0; x < std::min<int>(mapRows[y].size(), mapWidth); ++x) {
                        const int tile = mapRows[y][x];
                        if (tile < 0) continue;
                        const int tu = tile % columns;
                        const int tv = tile / columns;
                        const float px = static_cast<float>(x * tileSize);
                        const float py = static_cast<float>(y * tileSize);
                        quads.append({{px, py}, {static_cast<float>(tu * tileSize), static_cast<float>(tv * tileSize)}});
                        quads.append({{px + tileSize, py}, {static_cast<float>((tu + 1) * tileSize), static_cast<float>(tv * tileSize)}});
                        quads.append({{px + tileSize, py + tileSize}, {static_cast<float>((tu + 1) * tileSize), static_cast<float>((tv + 1) * tileSize)}});
                        quads.append({{px, py + tileSize}, {static_cast<float>(tu * tileSize), static_cast<float>((tv + 1) * tileSize)}});
                    }
                }
                window.draw(quads, &tileset);
            }

            for (const auto& player : players) {
                sf::CircleShape body(18.f);
                body.setOrigin(18.f, 18.f);
                body.setPosition(player.position);
                body.setFillColor(player.hp <= 0 ? sf::Color(80, 80, 80) : player.color);
                window.draw(body);

                if (hasPlayerTexture) {
                    playerSprite.setPosition(player.position - sf::Vector2f{18.f, 28.f});
                    playerSprite.setTextureRect(sf::IntRect(0, 0, 36, 38));
                    window.draw(playerSprite);
                }
            }

            for (const auto& bullet : bullets) {
                sf::CircleShape dot(4.f);
                dot.setOrigin(4.f, 4.f);
                dot.setPosition(bullet.position);
                dot.setFillColor(sf::Color(255, 244, 170));
                window.draw(dot);
            }
        }

        window.setView(window.getDefaultView());
        window.display();
    }

    return 0;
}
