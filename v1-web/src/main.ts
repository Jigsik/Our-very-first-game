type Vec = { x: number; y: number };
type RuneType = "armor" | "speed";
type RoundState = "countdown" | "playing" | "finished";

const canvasElement = document.querySelector<HTMLCanvasElement>("#game");
if (!canvasElement) throw new Error("Canvas #game not found");
const canvas: HTMLCanvasElement = canvasElement;

const renderingContext = canvas.getContext("2d");
if (!renderingContext) throw new Error("2D canvas context not available");
const ctx: CanvasRenderingContext2D = renderingContext;

const keys = new Set<string>();

const assets = {
  player: loadImage("/The_Game/The_Game/Images/player_1.png"),
  bullet: loadImage("/The_Game/The_Game/Images/bullet.png"),
  armorRune: loadImage("/The_Game/The_Game/Images/armor_rune.png"),
  speedRune: loadImage("/The_Game/The_Game/Images/speed_rune.png"),
  armor: loadImage("/The_Game/The_Game/Images/armor.png"),
  tiles: loadImage("/The_Game/The_Game/Maps/mapa.png")
};

const TILE = 30;
const TILE_STONE = 0;
const TILE_STUMP = 1;
const TILE_CROP = 2;
const TILE_BRICK = 3;
const TILE_GRASS = 4;
const TILE_SAND = 5;
const TILE_WATER = 6;
const TILE_FLAG = 7;
const PLAYER_RADIUS = 18;
const SOLID_TILE_IDS = new Set([TILE_STONE, TILE_STUMP, TILE_BRICK]);
const PLAYER_SPAWNS: [Vec, Vec] = [
  { x: 210, y: 420 },
  { x: 1110, y: 420 }
];
const RUNE_SPAWNS: [Rune, Rune] = [
  { type: "armor", position: { x: 660, y: 420 }, ttl: 999 },
  { type: "speed", position: { x: 660, y: 210 }, ttl: 999 }
];
const RUNE_SPAWN_POOL: Vec[] = [
  { x: 660, y: 420 },
  { x: 660, y: 210 },
  { x: 660, y: 630 },
  { x: 360, y: 210 },
  { x: 960, y: 630 },
  { x: 360, y: 630 },
  { x: 960, y: 210 }
];
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
let mapWidth = 44;
let mapHeight = 28;
let roundState: RoundState = "countdown";
let roundTimer = 3;
let winnerId: string | null = null;
const scores: Record<string, number> = { P1: 0, P2: 0 };

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
  map = createV1Arena();
  resetRound();
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
  if (roundState === "countdown") {
    roundTimer -= dt;
    if (roundTimer <= 0) {
      roundState = "playing";
      roundTimer = 0;
    }
    return;
  }

  if (roundState === "finished") {
    if (keys.has("KeyR")) {
      resetRound();
    }
    return;
  }

  for (const player of players) {
    updatePlayer(player, dt);
  }

  for (const bullet of bullets) {
    bullet.position.x += bullet.direction.x * 420 * dt;
    bullet.position.y += bullet.direction.y * 420 * dt;
    bullet.ttl -= dt;
    if (isSolidAt(bullet.position)) {
      bullet.ttl = 0;
    }
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

  finishRoundIfNeeded();
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
  player.position = moveWithCollision(player.position, {
    x: player.velocity.x * dt,
    y: player.velocity.y * dt
  });

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
  const preferred = RUNE_SPAWN_POOL[Math.floor(Math.random() * RUNE_SPAWN_POOL.length)] ?? RUNE_SPAWN_POOL[0]!;
  runes.push({
    type: Math.random() > 0.5 ? "armor" : "speed",
    position: findOpenPosition(preferred, PLAYER_RADIUS),
    ttl: 12
  });
}

function createV1Arena(): number[][] {
  mapWidth = 44;
  mapHeight = 28;
  const arena = Array.from({ length: mapHeight }, () => Array.from({ length: mapWidth }, () => TILE_GRASS));

  const setRect = (x: number, y: number, width: number, height: number, tile: number): void => {
    for (let ty = y; ty < y + height; ty++) {
      for (let tx = x; tx < x + width; tx++) {
        if (arena[ty]?.[tx] !== undefined) arena[ty]![tx] = tile;
      }
    }
  };

  setRect(0, 0, mapWidth, 1, TILE_STONE);
  setRect(0, mapHeight - 1, mapWidth, 1, TILE_STONE);
  setRect(0, 0, 1, mapHeight, TILE_STONE);
  setRect(mapWidth - 1, 0, 1, mapHeight, TILE_STONE);

  setRect(2, 12, mapWidth - 4, 4, TILE_SAND);
  setRect(20, 2, 4, mapHeight - 4, TILE_SAND);

  setRect(21, 4, 2, 7, TILE_BRICK);
  setRect(21, 17, 2, 7, TILE_BRICK);

  setRect(7, 5, 4, 2, TILE_STONE);
  setRect(33, 5, 4, 2, TILE_STONE);
  setRect(7, 21, 4, 2, TILE_STONE);
  setRect(33, 21, 4, 2, TILE_STONE);

  setRect(13, 9, 2, 5, TILE_STUMP);
  setRect(29, 14, 2, 5, TILE_STUMP);
  setRect(13, 17, 2, 3, TILE_STUMP);
  setRect(29, 8, 2, 3, TILE_STUMP);

  setRect(5, 10, 5, 3, TILE_CROP);
  setRect(34, 15, 5, 3, TILE_CROP);
  setRect(5, 17, 5, 3, TILE_CROP);
  setRect(34, 8, 5, 3, TILE_CROP);

  setRect(17, 4, 2, 3, TILE_WATER);
  setRect(25, 21, 2, 3, TILE_WATER);
  setRect(17, 21, 2, 3, TILE_WATER);
  setRect(25, 4, 2, 3, TILE_WATER);

  arena[14]![21] = TILE_FLAG;
  arena[13]![22] = TILE_FLAG;

  for (const spawn of [...PLAYER_SPAWNS, ...RUNE_SPAWN_POOL]) {
    clearAround(arena, spawn, 2);
  }

  return arena;
}

function clearAround(arena: number[][], point: Vec, radiusTiles: number): void {
  const centerX = Math.floor(point.x / TILE);
  const centerY = Math.floor(point.y / TILE);
  for (let y = centerY - radiusTiles; y <= centerY + radiusTiles; y++) {
    for (let x = centerX - radiusTiles; x <= centerX + radiusTiles; x++) {
      if (x > 0 && y > 0 && x < mapWidth - 1 && y < mapHeight - 1) {
        arena[y]![x] = Math.abs(x - centerX) + Math.abs(y - centerY) <= 1 ? TILE_SAND : TILE_GRASS;
      }
    }
  }
}

function resetRound(): void {
  players[0]!.position = findOpenPosition(PLAYER_SPAWNS[0]);
  players[1]!.position = findOpenPosition(PLAYER_SPAWNS[1]);
  for (const player of players) {
    player.hp = 100;
    player.armor = 0;
    player.speedUntil = 0;
    player.shootCooldown = 0;
  }
  bullets = [];
  runes = RUNE_SPAWNS.map((rune) => ({
    ...rune,
    position: findOpenPosition(rune.position, PLAYER_RADIUS)
  }));
  runeTimer = 4;
  winnerId = null;
  roundState = "countdown";
  roundTimer = 3;
}

function finishRoundIfNeeded(): void {
  const alive = players.filter((player) => player.hp > 0);
  if (alive.length !== 1 || winnerId !== null) return;
  winnerId = alive[0]!.id;
  scores[winnerId] = (scores[winnerId] ?? 0) + 1;
  roundState = "finished";
}

function moveWithCollision(position: Vec, delta: Vec): Vec {
  const mapMax = {
    x: mapWidth * TILE - PLAYER_RADIUS,
    y: mapHeight * TILE - PLAYER_RADIUS
  };
  const nextX = {
    x: clamp(position.x + delta.x, PLAYER_RADIUS, mapMax.x),
    y: position.y
  };
  const afterX = circleHitsSolid(nextX, PLAYER_RADIUS) ? position : nextX;
  const nextY = {
    x: afterX.x,
    y: clamp(afterX.y + delta.y, PLAYER_RADIUS, mapMax.y)
  };
  return circleHitsSolid(nextY, PLAYER_RADIUS) ? afterX : nextY;
}

function findOpenPosition(preferred: Vec, clearance = PLAYER_RADIUS + TILE): Vec {
  const clamped = {
    x: clamp(preferred.x, PLAYER_RADIUS, mapWidth * TILE - PLAYER_RADIUS),
    y: clamp(preferred.y, PLAYER_RADIUS, mapHeight * TILE - PLAYER_RADIUS)
  };
  if (!circleHitsSolid(clamped, clearance)) return clamped;

  for (let radius = TILE; radius < Math.max(mapWidth, mapHeight) * TILE; radius += TILE) {
    for (let dy = -radius; dy <= radius; dy += TILE) {
      for (let dx = -radius; dx <= radius; dx += TILE) {
        if (Math.abs(dx) !== radius && Math.abs(dy) !== radius) continue;
        const candidate = {
          x: clamp(clamped.x + dx, PLAYER_RADIUS, mapWidth * TILE - PLAYER_RADIUS),
          y: clamp(clamped.y + dy, PLAYER_RADIUS, mapHeight * TILE - PLAYER_RADIUS)
        };
        if (!circleHitsSolid(candidate, clearance)) return candidate;
      }
    }
  }

  return clamped;
}

function circleHitsSolid(center: Vec, radius: number): boolean {
  const samples: Vec[] = [
    { x: center.x - radius, y: center.y },
    { x: center.x + radius, y: center.y },
    { x: center.x, y: center.y - radius },
    { x: center.x, y: center.y + radius },
    { x: center.x - radius * 0.7, y: center.y - radius * 0.7 },
    { x: center.x + radius * 0.7, y: center.y - radius * 0.7 },
    { x: center.x - radius * 0.7, y: center.y + radius * 0.7 },
    { x: center.x + radius * 0.7, y: center.y + radius * 0.7 }
  ];
  return samples.some(isSolidAt);
}

function isSolidAt(point: Vec): boolean {
  if (point.x < 0 || point.y < 0 || point.x >= mapWidth * TILE || point.y >= mapHeight * TILE) {
    return true;
  }
  const tileX = Math.floor(point.x / TILE);
  const tileY = Math.floor(point.y / TILE);
  const tileId = map[tileY]?.[tileX];
  return tileId === undefined ? false : SOLID_TILE_IDS.has(tileId);
}

function draw(): void {
  ctx.clearRect(0, 0, canvas.width, canvas.height);
  ctx.fillStyle = "#15201a";
  ctx.fillRect(0, 0, canvas.width, canvas.height);

  const panelWidth = (canvas.width - viewportGap) / 2;
  const panelHeight = canvas.height - 76;

  drawViewport(players[0]!, 0, 0, panelWidth, panelHeight);
  drawViewport(players[1]!, panelWidth + viewportGap, 0, panelWidth, panelHeight);

  ctx.fillStyle = "#0d1110";
  ctx.fillRect(0, panelHeight, canvas.width, canvas.height - panelHeight);
  ctx.fillStyle = "#25322b";
  ctx.fillRect(panelWidth, panelHeight, viewportGap, canvas.height - panelHeight);
  drawStatus(players[0]!, 24, panelHeight + 16, panelWidth - 48);
  drawStatus(players[1]!, panelWidth + viewportGap + 24, panelHeight + 16, panelWidth - 48);

  if (roundState === "countdown") {
    ctx.fillStyle = "rgba(0, 0, 0, 0.66)";
    ctx.fillRect(canvas.width / 2 - 130, canvas.height / 2 - 60, 260, 120);
    ctx.fillStyle = "#f8f4dc";
    ctx.font = "42px Arial";
    ctx.textAlign = "center";
    ctx.fillText(Math.ceil(roundTimer).toString(), canvas.width / 2, canvas.height / 2 + 14);
    ctx.font = "16px Arial";
    ctx.fillText("GET READY", canvas.width / 2, canvas.height / 2 + 42);
    ctx.textAlign = "left";
  }

  if (roundState === "finished" && winnerId) {
    ctx.fillStyle = "rgba(0, 0, 0, 0.7)";
    ctx.fillRect(canvas.width / 2 - 210, canvas.height / 2 - 56, 420, 112);
    ctx.fillStyle = "#f8f4dc";
    ctx.font = "24px Arial";
    ctx.textAlign = "center";
    ctx.fillText(`${winnerId} WINS`, canvas.width / 2, canvas.height / 2 - 8);
    ctx.font = "16px Arial";
    ctx.fillText(`Score ${scores.P1} : ${scores.P2}    Press R`, canvas.width / 2, canvas.height / 2 + 24);
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
        ctx.fillStyle = fallbackTileColor(tileId);
        ctx.fillRect(tx * TILE, ty * TILE, TILE, TILE);
      }
    }
  }
}

function fallbackTileColor(tileId: number): string {
  switch (tileId) {
    case TILE_STONE:
      return "#707872";
    case TILE_STUMP:
      return "#865a27";
    case TILE_CROP:
      return "#e0c847";
    case TILE_BRICK:
      return "#7a4b39";
    case TILE_SAND:
      return "#bda747";
    case TILE_WATER:
      return "#68a8bd";
    case TILE_FLAG:
      return "#d52f31";
    case TILE_GRASS:
    default:
      return "#3f9144";
  }
}

function drawPlayer(player: Player): void {
  ctx.save();
  ctx.translate(player.position.x, player.position.y);
  ctx.fillStyle = player.hp <= 0 ? "#555" : player.color;
  ctx.beginPath();
  ctx.arc(0, 0, PLAYER_RADIUS, 0, Math.PI * 2);
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

function drawStatus(player: Player, x: number, y: number, width: number): void {
  const speedLeft = Math.max(0, player.speedUntil - nowSeconds());
  ctx.fillStyle = "#f8f4dc";
  ctx.font = "18px Arial";
  ctx.fillText(`${player.id}`, x, y);
  ctx.font = "14px Arial";
  ctx.fillText(`Score ${scores[player.id]}`, x + 42, y);

  const barX = x + 120;
  const barWidth = Math.min(170, Math.max(120, width - 310));
  drawBar("HP", player.hp, 100, barX, y - 14, barWidth, "#d95d55");
  drawBar("AR", player.armor, 60, barX + barWidth + 48, y - 14, 110, "#74b9d7");

  if (speedLeft > 0) {
    const speedWidth = Math.min(120, Math.max(80, width - barWidth - 310));
    drawBar("SP", speedLeft, 10, x + width - speedWidth, y - 14, speedWidth, "#a5d85e");
  }
}

function drawBar(label: string, value: number, max: number, x: number, y: number, width: number, color: string): void {
  const ratio = clamp(value / max, 0, 1);
  ctx.fillStyle = "#161d19";
  ctx.fillRect(x, y, width, 14);
  ctx.fillStyle = color;
  ctx.fillRect(x, y, width * ratio, 14);
  ctx.strokeStyle = "#526058";
  ctx.lineWidth = 1;
  ctx.strokeRect(x + 0.5, y + 0.5, width - 1, 13);
  ctx.fillStyle = "#f8f4dc";
  ctx.font = "11px Arial";
  ctx.fillText(label, x - 24, y + 11);
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
