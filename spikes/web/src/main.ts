type Vec = { x: number; y: number };
type RuneType = "armor" | "speed";

const canvasElement = document.querySelector<HTMLCanvasElement>("#game");
if (!canvasElement) throw new Error("Canvas #game not found");
const canvas: HTMLCanvasElement = canvasElement;

const renderingContext = canvas.getContext("2d");
if (!renderingContext) throw new Error("2D canvas context not available");
const ctx: CanvasRenderingContext2D = renderingContext;

const keys = new Set<string>();

const assets = {
  player: loadImage("../../The_Game/The_Game/Images/player_1.png"),
  bullet: loadImage("../../The_Game/The_Game/Images/bullet.png"),
  armorRune: loadImage("../../The_Game/The_Game/Images/armor_rune.png"),
  speedRune: loadImage("../../The_Game/The_Game/Images/speed_rune.png"),
  armor: loadImage("../../The_Game/The_Game/Images/armor.png"),
  tiles: loadImage("../../The_Game/The_Game/Maps/mapa.png")
};

const TILE = 30;
const viewportGap = 8;
let lastTime = performance.now();

type Player = {
  id: string;
  position: Vec;
  velocity: Vec;
  direction: Vec;
  color: string;
  hp: number;
  armor: number;
  speedUntil: number;
  shootCooldown: number;
  controls: {
    up: string;
    down: string;
    left: string;
    right: string;
    sprint: string;
    shoot: string;
  };
};

type Bullet = {
  owner: string;
  position: Vec;
  direction: Vec;
  ttl: number;
};

type Rune = {
  type: RuneType;
  position: Vec;
  ttl: number;
};

const players: Player[] = [
  {
    id: "P1",
    position: { x: 220, y: 220 },
    velocity: { x: 0, y: 0 },
    direction: { x: 1, y: 0 },
    color: "#7fd1ff",
    hp: 100,
    armor: 0,
    speedUntil: 0,
    shootCooldown: 0,
    controls: {
      up: "KeyW",
      down: "KeyS",
      left: "KeyA",
      right: "KeyD",
      sprint: "ShiftLeft",
      shoot: "Space"
    }
  },
  {
    id: "P2",
    position: { x: 580, y: 360 },
    velocity: { x: 0, y: 0 },
    direction: { x: -1, y: 0 },
    color: "#ffcf70",
    hp: 100,
    armor: 0,
    speedUntil: 0,
    shootCooldown: 0,
    controls: {
      up: "ArrowUp",
      down: "ArrowDown",
      left: "ArrowLeft",
      right: "ArrowRight",
      sprint: "ShiftRight",
      shoot: "Slash"
    }
  }
];

let bullets: Bullet[] = [];
let runes: Rune[] = [
  { type: "armor", position: { x: 400, y: 260 }, ttl: 999 },
  { type: "speed", position: { x: 760, y: 460 }, ttl: 999 }
];
let runeTimer = 4;
let map: number[][] = [];
let mapWidth = 100;
let mapHeight = 100;

window.addEventListener("keydown", (event) => {
  keys.add(event.code);
  if (["ArrowUp", "ArrowDown", "ArrowLeft", "ArrowRight", "Space"].includes(event.code)) {
    event.preventDefault();
  }
});

window.addEventListener("keyup", (event) => {
  keys.delete(event.code);
});

void boot();

async function boot(): Promise<void> {
  map = await loadMap("../../The_Game/The_Game/Maps/mapa.txt");
  requestAnimationFrame(frame);
}

function frame(now: number): void {
  const dt = Math.min(0.033, (now - lastTime) / 1000);
  lastTime = now;

  update(dt);
  draw();

  requestAnimationFrame(frame);
}

function update(dt: number): void {
  for (const player of players) {
    updatePlayer(player, dt);
  }

  for (const bullet of bullets) {
    bullet.position.x += bullet.direction.x * 420 * dt;
    bullet.position.y += bullet.direction.y * 420 * dt;
    bullet.ttl -= dt;
  }

  for (const bullet of bullets) {
    for (const player of players) {
      if (player.id === bullet.owner || player.hp <= 0) continue;
      if (distance(player.position, bullet.position) < 24) {
        applyDamage(player, 20);
        bullet.ttl = 0;
      }
    }
  }

  bullets = bullets.filter((bullet) => (
    bullet.ttl > 0 &&
    bullet.position.x >= 0 &&
    bullet.position.y >= 0 &&
    bullet.position.x <= mapWidth * TILE &&
    bullet.position.y <= mapHeight * TILE
  ));

  for (const rune of runes) {
    rune.ttl -= dt;
    for (const player of players) {
      if (distance(player.position, rune.position) < 32) {
        applyRune(player, rune.type);
        rune.ttl = 0;
      }
    }
  }

  runes = runes.filter((rune) => rune.ttl > 0);
  runeTimer -= dt;
  if (runeTimer <= 0 && runes.length < 3) {
    spawnRune();
    runeTimer = 5 + Math.random() * 4;
  }

  if (players.some((player) => player.hp <= 0) && keys.has("KeyR")) {
    resetRound();
  }
}

function updatePlayer(player: Player, dt: number): void {
  if (player.hp <= 0) return;

  const input = {
    x: Number(keys.has(player.controls.right)) - Number(keys.has(player.controls.left)),
    y: Number(keys.has(player.controls.down)) - Number(keys.has(player.controls.up))
  };

  const normalized = normalize(input);
  const baseSpeed = nowSeconds() < player.speedUntil ? 250 : 170;
  const sprint = keys.has(player.controls.sprint) ? 1.35 : 1;
  player.velocity = { x: normalized.x * baseSpeed * sprint, y: normalized.y * baseSpeed * sprint };
  player.position.x = clamp(player.position.x + player.velocity.x * dt, 20, mapWidth * TILE - 20);
  player.position.y = clamp(player.position.y + player.velocity.y * dt, 20, mapHeight * TILE - 20);

  if (normalized.x !== 0 || normalized.y !== 0) {
    player.direction = normalized;
  }

  player.shootCooldown = Math.max(0, player.shootCooldown - dt);
  if (keys.has(player.controls.shoot) && player.shootCooldown === 0) {
    bullets.push({
      owner: player.id,
      position: {
        x: player.position.x + player.direction.x * 22,
        y: player.position.y + player.direction.y * 22
      },
      direction: player.direction,
      ttl: 1.6
    });
    player.shootCooldown = 0.35;
  }
}

function applyDamage(player: Player, amount: number): void {
  const blocked = Math.min(player.armor, amount);
  player.armor -= blocked;
  player.hp = Math.max(0, player.hp - (amount - blocked));
}

function applyRune(player: Player, type: RuneType): void {
  if (type === "armor") {
    player.armor = 60;
    player.speedUntil = 0;
  } else {
    player.speedUntil = nowSeconds() + 10;
    player.armor = 0;
  }
}

function spawnRune(): void {
  runes.push({
    type: Math.random() > 0.5 ? "armor" : "speed",
    position: {
      x: 120 + Math.random() * Math.min(900, mapWidth * TILE - 240),
      y: 120 + Math.random() * Math.min(620, mapHeight * TILE - 240)
    },
    ttl: 12
  });
}

function resetRound(): void {
  players[0]!.position = { x: 220, y: 220 };
  players[1]!.position = { x: 580, y: 360 };
  for (const player of players) {
    player.hp = 100;
    player.armor = 0;
    player.speedUntil = 0;
    player.shootCooldown = 0;
  }
  bullets = [];
  runes = [
    { type: "armor", position: { x: 400, y: 260 }, ttl: 999 },
    { type: "speed", position: { x: 760, y: 460 }, ttl: 999 }
  ];
}

function draw(): void {
  ctx.clearRect(0, 0, canvas.width, canvas.height);
  ctx.fillStyle = "#15201a";
  ctx.fillRect(0, 0, canvas.width, canvas.height);

  const panelWidth = (canvas.width - viewportGap) / 2;
  const panelHeight = canvas.height - 52;

  drawViewport(players[0]!, 0, 0, panelWidth, panelHeight);
  drawViewport(players[1]!, panelWidth + viewportGap, 0, panelWidth, panelHeight);

  ctx.fillStyle = "#0d1110";
  ctx.fillRect(0, panelHeight, canvas.width, canvas.height - panelHeight);
  drawStatus(players[0]!, 24, panelHeight + 32);
  drawStatus(players[1]!, panelWidth + viewportGap + 24, panelHeight + 32);

  const winner = players.find((player) => player.hp > 0 && players.some((other) => other.id !== player.id && other.hp <= 0));
  if (winner) {
    ctx.fillStyle = "rgba(0, 0, 0, 0.7)";
    ctx.fillRect(canvas.width / 2 - 190, canvas.height / 2 - 44, 380, 88);
    ctx.fillStyle = "#f8f4dc";
    ctx.font = "24px Arial";
    ctx.textAlign = "center";
    ctx.fillText(`${winner.id} wins - press R to restart`, canvas.width / 2, canvas.height / 2 + 8);
    ctx.textAlign = "left";
  }
}

function drawViewport(focus: Player, x: number, y: number, width: number, height: number): void {
  const camera = {
    x: clamp(focus.position.x - width / 2, 0, mapWidth * TILE - width),
    y: clamp(focus.position.y - height / 2, 0, mapHeight * TILE - height)
  };

  ctx.save();
  ctx.beginPath();
  ctx.rect(x, y, width, height);
  ctx.clip();
  ctx.translate(x - camera.x, y - camera.y);

  drawMap(camera, width, height);
  for (const rune of runes) drawRune(rune);
  for (const bullet of bullets) drawBullet(bullet);
  for (const player of players) drawPlayer(player);

  ctx.restore();
  ctx.strokeStyle = "#9ca38d";
  ctx.lineWidth = 2;
  ctx.strokeRect(x + 1, y + 1, width - 2, height - 2);
}

function drawMap(camera: Vec, width: number, height: number): void {
  const tiles = assets.tiles;
  const startX = Math.max(0, Math.floor(camera.x / TILE) - 1);
  const startY = Math.max(0, Math.floor(camera.y / TILE) - 1);
  const endX = Math.min(mapWidth, Math.ceil((camera.x + width) / TILE) + 1);
  const endY = Math.min(mapHeight, Math.ceil((camera.y + height) / TILE) + 1);
  const columns = Math.max(1, Math.floor(tiles.naturalWidth / TILE));

  for (let ty = startY; ty < endY; ty++) {
    const row = map[ty];
    for (let tx = startX; tx < endX; tx++) {
      const tileId = row?.[tx] ?? 4;
      if (tiles.complete && tiles.naturalWidth > 0 && tileId >= 0) {
        const sx = (tileId % columns) * TILE;
        const sy = Math.floor(tileId / columns) * TILE;
        ctx.drawImage(tiles, sx, sy, TILE, TILE, tx * TILE, ty * TILE, TILE, TILE);
      } else {
        ctx.fillStyle = tileId === 0 ? "#465b40" : tileId === 6 ? "#547b4a" : "#2f4e35";
        ctx.fillRect(tx * TILE, ty * TILE, TILE, TILE);
      }
    }
  }
}

function drawPlayer(player: Player): void {
  ctx.save();
  ctx.translate(player.position.x, player.position.y);
  ctx.fillStyle = player.hp <= 0 ? "#555" : player.color;
  ctx.beginPath();
  ctx.arc(0, 0, 18, 0, Math.PI * 2);
  ctx.fill();

  const image = assets.player;
  if (image.complete && image.naturalWidth > 0) {
    const row = directionRow(player.direction);
    ctx.drawImage(image, 0, row * 38, 36, 38, -18, -28, 36, 38);
  }

  ctx.strokeStyle = "#101010";
  ctx.lineWidth = 3;
  ctx.beginPath();
  ctx.moveTo(0, 0);
  ctx.lineTo(player.direction.x * 28, player.direction.y * 28);
  ctx.stroke();

  if (player.armor > 0) {
    ctx.strokeStyle = "#96d7ff";
    ctx.lineWidth = 3;
    ctx.beginPath();
    ctx.arc(0, 0, 26, 0, Math.PI * 2);
    ctx.stroke();
  }
  ctx.restore();
}

function drawBullet(bullet: Bullet): void {
  ctx.save();
  ctx.translate(bullet.position.x, bullet.position.y);
  ctx.rotate(Math.atan2(bullet.direction.y, bullet.direction.x));
  const image = assets.bullet;
  if (image.complete && image.naturalWidth > 0) {
    ctx.drawImage(image, -5, -3);
  } else {
    ctx.fillStyle = "#f9f2a7";
    ctx.fillRect(-6, -3, 12, 6);
  }
  ctx.restore();
}

function drawRune(rune: Rune): void {
  const image = rune.type === "armor" ? assets.armorRune : assets.speedRune;
  if (image.complete && image.naturalWidth > 0) {
    ctx.drawImage(image, rune.position.x - 15, rune.position.y - 15);
  } else {
    ctx.fillStyle = rune.type === "armor" ? "#8fd0ff" : "#b5f56c";
    ctx.fillRect(rune.position.x - 12, rune.position.y - 12, 24, 24);
  }
}

function drawStatus(player: Player, x: number, y: number): void {
  const speedLeft = Math.max(0, player.speedUntil - nowSeconds());
  ctx.fillStyle = "#f8f4dc";
  ctx.font = "18px Arial";
  ctx.fillText(`${player.id} HP ${player.hp} Armor ${player.armor}`, x, y);
  if (speedLeft > 0) {
    ctx.fillStyle = "#b5f56c";
    ctx.fillText(`Speed ${speedLeft.toFixed(1)}s`, x + 210, y);
  }
}

async function loadMap(path: string): Promise<number[][]> {
  const response = await fetch(path);
  const text = await response.text();
  const lines = text.split(/\r?\n/).map((line) => line.trim()).filter(Boolean);
  mapWidth = Number(lines.find((line) => line.startsWith("width="))?.split("=")[1] || 100);
  mapHeight = Number(lines.find((line) => line.startsWith("height="))?.split("=")[1] || 100);
  return lines
    .filter((line) => /^\d/.test(line))
    .map((line) => line.split(",").filter(Boolean).map((value) => Number(value) - 1));
}

function loadImage(src: string): HTMLImageElement {
  const image = new Image();
  image.src = src;
  return image;
}

function normalize(v: Vec): Vec {
  const length = Math.hypot(v.x, v.y);
  return length === 0 ? { x: 0, y: 0 } : { x: v.x / length, y: v.y / length };
}

function distance(a: Vec, b: Vec): number {
  return Math.hypot(a.x - b.x, a.y - b.y);
}

function clamp(value: number, min: number, max: number): number {
  return Math.min(max, Math.max(min, value));
}

function nowSeconds(): number {
  return performance.now() / 1000;
}

function directionRow(direction: Vec): number {
  if (Math.abs(direction.x) > Math.abs(direction.y)) {
    return direction.x < 0 ? 1 : 2;
  }
  return direction.y < 0 ? 3 : 0;
}
