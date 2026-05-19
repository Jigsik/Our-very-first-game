type Vec = { x: number; y: number };
type RuneType = "armor" | "speed" | "scatter";
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
  deathRabbit: loadImage("/v1-web/assets/rabbit-death.svg"),
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
const BASE_PLAYER_SPEED = 170;
const SPRINT_MULTIPLIER = 1.25;
const SPEED_RUNE_MULTIPLIER = 1.55;
const BULLET_SPEED = 440;
const AIM_GRACE_RANGE = 620;
const AIM_GRACE_MIN_DOT = 0.42;
const AIM_GRACE_BLEND = 0.72;
const AIM_GRACE_LEAD_SECONDS = 0.24;
const SOLID_TILE_IDS = new Set([TILE_STONE, TILE_STUMP, TILE_BRICK]);
const PLAYER_SPAWNS: [Vec, Vec] = [
  { x: 210, y: 420 },
  { x: 1110, y: 420 }
];
const RUNE_SPAWNS: Rune[] = [
  { type: "armor", position: { x: 660, y: 420 }, ttl: 999, pulseOffset: 0 },
  { type: "speed", position: { x: 660, y: 210 }, ttl: 999, pulseOffset: 1.7 },
  { type: "scatter", position: { x: 660, y: 630 }, ttl: 999, pulseOffset: 3.4 }
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
  scatterUntil: number;
  shootCooldown: number;
  animationTime: number;
  hitFlash: number;
  pickupFlash: number;
  recoil: number;
  isSprinting: boolean;
  deathTime: number;
  deathDirection: Vec;
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
  age: number;
  damage: number;
  color: string;
  speed: number;
  hitRadius: number;
  assisted: boolean;
};

type Rune = {
  type: RuneType;
  position: Vec;
  ttl: number;
  pulseOffset: number;
};

type Particle = {
  position: Vec;
  velocity: Vec;
  color: string;
  radius: number;
  ttl: number;
  age: number;
  gravity?: number;
};

type FloatingText = {
  text: string;
  position: Vec;
  velocity: Vec;
  color: string;
  ttl: number;
  age: number;
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
    scatterUntil: 0,
    shootCooldown: 0,
    animationTime: 0,
    hitFlash: 0,
    pickupFlash: 0,
    recoil: 0,
    isSprinting: false,
    deathTime: 0,
    deathDirection: { x: 1, y: 0 },
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
    scatterUntil: 0,
    shootCooldown: 0,
    animationTime: 0,
    hitFlash: 0,
    pickupFlash: 0,
    recoil: 0,
    isSprinting: false,
    deathTime: 0,
    deathDirection: { x: -1, y: 0 },
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
  { type: "armor", position: { x: 400, y: 260 }, ttl: 999, pulseOffset: 0.4 },
  { type: "speed", position: { x: 760, y: 460 }, ttl: 999, pulseOffset: 2.1 },
  { type: "scatter", position: { x: 660, y: 420 }, ttl: 999, pulseOffset: 3.4 }
];
let particles: Particle[] = [];
let floatingTexts: FloatingText[] = [];
let runeTimer = 4;
let map: number[][] = [];
let mapWidth = 44;
let mapHeight = 28;
let roundState: RoundState = "countdown";
let roundTimer = 3;
let winnerId: string | null = null;
let screenShake = 0;
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
  updateEffects(dt);

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
    bullet.position.x += bullet.direction.x * bullet.speed * dt;
    bullet.position.y += bullet.direction.y * bullet.speed * dt;
    bullet.age += dt;
    bullet.ttl -= dt;
    if (isSolidAt(bullet.position)) {
      spawnImpact(bullet.position, "#f6d36b", 9);
      bullet.ttl = 0;
    }
  }

  for (const bullet of bullets) {
    for (const player of players) {
      if (player.id === bullet.owner || player.hp <= 0) continue;
      if (distance(player.position, bullet.position) < bullet.hitRadius) {
        const result = applyDamage(player, bullet.damage);
        spawnHitFeedback(player, result.damage, result.blocked);
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
        spawnRunePickup(player, rune.type);
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
  const hasSpeedRune = nowSeconds() < player.speedUntil;
  player.isSprinting = !hasSpeedRune && keys.has(player.controls.sprint) && (normalized.x !== 0 || normalized.y !== 0);
  const movementMultiplier = hasSpeedRune ? SPEED_RUNE_MULTIPLIER : player.isSprinting ? SPRINT_MULTIPLIER : 1;
  player.velocity = {
    x: normalized.x * BASE_PLAYER_SPEED * movementMultiplier,
    y: normalized.y * BASE_PLAYER_SPEED * movementMultiplier
  };
  player.position = moveWithCollision(player.position, {
    x: player.velocity.x * dt,
    y: player.velocity.y * dt
  });

  if (normalized.x !== 0 || normalized.y !== 0) {
    player.direction = normalized;
    player.animationTime += dt * (hasSpeedRune ? 15 : player.isSprinting ? 12 : 8);
    if ((hasSpeedRune || player.isSprinting) && Math.random() < dt * 18) {
      spawnDust(player.position, hasSpeedRune ? "#b6f56d" : "#d8c783", player.direction);
    }
  } else {
    player.animationTime += dt * 2.4;
  }

  player.hitFlash = Math.max(0, player.hitFlash - dt);
  player.pickupFlash = Math.max(0, player.pickupFlash - dt);
  player.recoil = Math.max(0, player.recoil - dt * 8);

  player.shootCooldown = Math.max(0, player.shootCooldown - dt);
  if (keys.has(player.controls.shoot) && player.shootCooldown === 0) {
    const aim = findAimGrace(player, player.direction);
    const muzzle = {
      x: player.position.x + aim.direction.x * 24,
      y: player.position.y + aim.direction.y * 24
    };
    const hasScatter = nowSeconds() < player.scatterUntil;
    const directions = hasScatter
      ? [-0.22, 0, 0.22].map((angle) => rotateVec(aim.direction, angle))
      : [aim.direction];
    for (const direction of directions) {
      bullets.push({
        owner: player.id,
        position: { ...muzzle },
        direction,
        ttl: hasScatter ? 1.15 : 1.6,
        age: 0,
        damage: hasScatter ? 13 : 20,
        color: hasScatter ? "#ff9a5a" : aim.assisted ? "#9edcff" : "#f9d36b",
        speed: BULLET_SPEED,
        hitRadius: aim.assisted ? 30 : 25,
        assisted: aim.assisted
      });
    }
    player.recoil = 1;
    screenShake = Math.max(screenShake, hasScatter ? 2.3 : 1.1);
    spawnMuzzleFlash(muzzle, aim.direction);
    if (aim.assisted) spawnAimGraceSpark(muzzle, aim.direction);
    player.shootCooldown = hasScatter ? 0.42 : 0.35;
  }
}

function findAimGrace(shooter: Player, baseDirection: Vec): { direction: Vec; assisted: boolean } {
  let bestTarget: Player | null = null;
  let bestScore = 0;

  for (const target of players) {
    if (target.id === shooter.id || target.hp <= 0) continue;
    const predicted = {
      x: target.position.x + target.velocity.x * AIM_GRACE_LEAD_SECONDS,
      y: target.position.y + target.velocity.y * AIM_GRACE_LEAD_SECONDS
    };
    const toTarget = normalize({
      x: predicted.x - shooter.position.x,
      y: predicted.y - shooter.position.y
    });
    const range = distance(shooter.position, predicted);
    const aimDot = dot(baseDirection, toTarget);
    if (range > AIM_GRACE_RANGE || aimDot < AIM_GRACE_MIN_DOT) continue;

    const score = aimDot * (1 - range / (AIM_GRACE_RANGE * 1.5));
    if (score > bestScore) {
      bestScore = score;
      bestTarget = target;
    }
  }

  if (!bestTarget) return { direction: baseDirection, assisted: false };

  const predicted = {
    x: bestTarget.position.x + bestTarget.velocity.x * AIM_GRACE_LEAD_SECONDS,
    y: bestTarget.position.y + bestTarget.velocity.y * AIM_GRACE_LEAD_SECONDS
  };
  const desired = normalize({
    x: predicted.x - shooter.position.x,
    y: predicted.y - shooter.position.y
  });

  return {
    direction: normalize({
      x: baseDirection.x * (1 - AIM_GRACE_BLEND) + desired.x * AIM_GRACE_BLEND,
      y: baseDirection.y * (1 - AIM_GRACE_BLEND) + desired.y * AIM_GRACE_BLEND
    }),
    assisted: true
  };
}

function applyDamage(player: Player, amount: number): { damage: number; blocked: number } {
  const wasAlive = player.hp > 0;
  const blocked = Math.min(player.armor, amount);
  player.armor -= blocked;
  const damage = amount - blocked;
  player.hp = Math.max(0, player.hp - damage);
  player.hitFlash = 0.24;
  screenShake = Math.max(screenShake, damage > 0 ? 5 : 2.5);
  if (wasAlive && player.hp <= 0) {
    player.deathTime = 0;
    player.deathDirection = player.direction;
    player.recoil = 1;
    spawnDeathPuff(player.position);
  }
  return { damage, blocked };
}

function applyRune(player: Player, type: RuneType): void {
  if (type === "armor") {
    player.armor = 60;
    player.speedUntil = 0;
  } else if (type === "speed") {
    player.speedUntil = nowSeconds() + 10;
    player.armor = 0;
  } else {
    player.scatterUntil = nowSeconds() + 8;
  }
  player.pickupFlash = 0.5;
}

function spawnRune(): void {
  const preferred = RUNE_SPAWN_POOL[Math.floor(Math.random() * RUNE_SPAWN_POOL.length)] ?? RUNE_SPAWN_POOL[0]!;
  const runeTypes: RuneType[] = ["armor", "speed", "scatter"];
  runes.push({
    type: runeTypes[Math.floor(Math.random() * runeTypes.length)] ?? "armor",
    position: findOpenPosition(preferred, PLAYER_RADIUS),
    ttl: 12,
    pulseOffset: Math.random() * Math.PI * 2
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
    player.scatterUntil = 0;
    player.shootCooldown = 0;
    player.animationTime = 0;
    player.hitFlash = 0;
    player.pickupFlash = 0;
    player.recoil = 0;
    player.isSprinting = false;
    player.deathTime = 0;
    player.deathDirection = player.direction;
  }
  bullets = [];
  particles = [];
  floatingTexts = [];
  screenShake = 0;
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
  screenShake = Math.max(screenShake, 7);
  spawnWinBurst(alive[0]!.position, alive[0]!.color);
}

function updateEffects(dt: number): void {
  screenShake = Math.max(0, screenShake - dt * 12);

  for (const player of players) {
    if (player.hp <= 0) {
      player.deathTime += dt;
      player.recoil = Math.max(0, player.recoil - dt * 5);
    }
  }

  for (const particle of particles) {
    particle.age += dt;
    particle.position.x += particle.velocity.x * dt;
    particle.position.y += particle.velocity.y * dt;
    particle.velocity.y += (particle.gravity ?? 0) * dt;
    particle.velocity.x *= Math.pow(0.06, dt);
    particle.velocity.y *= Math.pow(0.18, dt);
  }
  particles = particles.filter((particle) => particle.age < particle.ttl);

  for (const floatingText of floatingTexts) {
    floatingText.age += dt;
    floatingText.position.x += floatingText.velocity.x * dt;
    floatingText.position.y += floatingText.velocity.y * dt;
  }
  floatingTexts = floatingTexts.filter((floatingText) => floatingText.age < floatingText.ttl);
}

function spawnDust(position: Vec, color: string, direction: Vec): void {
  particles.push({
    position: {
      x: position.x - direction.x * 13 + (Math.random() - 0.5) * 8,
      y: position.y - direction.y * 13 + 13 + (Math.random() - 0.5) * 8
    },
    velocity: {
      x: -direction.x * 42 + (Math.random() - 0.5) * 42,
      y: -direction.y * 42 + (Math.random() - 0.5) * 42
    },
    color,
    radius: 3 + Math.random() * 3,
    ttl: 0.42,
    age: 0
  });
}

function spawnMuzzleFlash(position: Vec, direction: Vec): void {
  for (let i = 0; i < 8; i++) {
    const spread = randomUnitVector();
    particles.push({
      position: { ...position },
      velocity: {
        x: direction.x * (95 + Math.random() * 90) + spread.x * 60,
        y: direction.y * (95 + Math.random() * 90) + spread.y * 60
      },
      color: i % 2 === 0 ? "#ffe58a" : "#ff9a5a",
      radius: 2 + Math.random() * 2,
      ttl: 0.22 + Math.random() * 0.12,
      age: 0
    });
  }
}

function spawnAimGraceSpark(position: Vec, direction: Vec): void {
  for (let i = 0; i < 6; i++) {
    const side = { x: -direction.y, y: direction.x };
    particles.push({
      position: {
        x: position.x + side.x * (i - 2.5) * 3,
        y: position.y + side.y * (i - 2.5) * 3
      },
      velocity: {
        x: direction.x * (60 + Math.random() * 50) + side.x * (Math.random() - 0.5) * 50,
        y: direction.y * (60 + Math.random() * 50) + side.y * (Math.random() - 0.5) * 50
      },
      color: "#9edcff",
      radius: 1.8 + Math.random() * 1.6,
      ttl: 0.24,
      age: 0
    });
  }
}

function spawnImpact(position: Vec, color: string, count: number): void {
  for (let i = 0; i < count; i++) {
    const direction = randomUnitVector();
    particles.push({
      position: { ...position },
      velocity: {
        x: direction.x * (70 + Math.random() * 110),
        y: direction.y * (70 + Math.random() * 110)
      },
      color,
      radius: 2 + Math.random() * 3,
      ttl: 0.28 + Math.random() * 0.2,
      age: 0
    });
  }
}

function spawnHitFeedback(player: Player, damage: number, blocked: number): void {
  const blockedOnly = damage === 0 && blocked > 0;
  spawnImpact(player.position, blockedOnly ? "#8fd0ff" : "#ff756b", blockedOnly ? 12 : 18);
  floatingTexts.push({
    text: blockedOnly ? "BLOCK" : `-${damage}`,
    position: { x: player.position.x, y: player.position.y - 32 },
    velocity: { x: (Math.random() - 0.5) * 18, y: -38 },
    color: blockedOnly ? "#bcecff" : "#ffd1c7",
    ttl: 0.75,
    age: 0
  });
}

function spawnRunePickup(player: Player, type: RuneType): void {
  const color = type === "armor" ? "#8fd0ff" : type === "speed" ? "#b5f56c" : "#ff9a5a";
  for (let i = 0; i < 26; i++) {
    const direction = randomUnitVector();
    particles.push({
      position: { ...player.position },
      velocity: {
        x: direction.x * (75 + Math.random() * 90),
        y: direction.y * (75 + Math.random() * 90)
      },
      color,
      radius: 2 + Math.random() * 3,
      ttl: 0.45 + Math.random() * 0.24,
      age: 0
    });
  }
  floatingTexts.push({
    text: type === "armor" ? "ARMOR" : type === "speed" ? "SPEED" : "SCATTER",
    position: { x: player.position.x, y: player.position.y - 36 },
    velocity: { x: 0, y: -34 },
    color,
    ttl: 0.9,
    age: 0
  });
}

function spawnWinBurst(position: Vec, color: string): void {
  for (let i = 0; i < 70; i++) {
    const direction = randomUnitVector();
    const confettiColor = i % 3 === 0 ? color : i % 3 === 1 ? "#ffe58a" : "#f8f4dc";
    particles.push({
      position: { ...position },
      velocity: {
        x: direction.x * (90 + Math.random() * 240),
        y: direction.y * (90 + Math.random() * 240) - 60
      },
      color: confettiColor,
      radius: 2 + Math.random() * 4,
      ttl: 1.1 + Math.random() * 0.7,
      age: 0,
      gravity: 120
    });
  }
}

function spawnDeathPuff(position: Vec): void {
  for (let i = 0; i < 34; i++) {
    const direction = randomUnitVector();
    particles.push({
      position: { ...position },
      velocity: {
        x: direction.x * (45 + Math.random() * 120),
        y: direction.y * (45 + Math.random() * 120)
      },
      color: i % 2 === 0 ? "#f4efe2" : "#cfc6b6",
      radius: 2 + Math.random() * 5,
      ttl: 0.5 + Math.random() * 0.3,
      age: 0
    });
  }
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
  const shake = screenShake > 0 ? {
    x: (Math.random() - 0.5) * screenShake,
    y: (Math.random() - 0.5) * screenShake
  } : { x: 0, y: 0 };
  ctx.translate(x - camera.x + shake.x, y - camera.y + shake.y);

  drawMap(camera, width, height);
  for (const particle of particles) drawParticle(particle);
  for (const rune of runes) drawRune(rune);
  for (const bullet of bullets) drawBullet(bullet);
  for (const player of players) drawPlayer(player);
  for (const floatingText of floatingTexts) drawFloatingText(floatingText);

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
      drawTileMotion(tileId, tx * TILE, ty * TILE);
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

function drawTileMotion(tileId: number, x: number, y: number): void {
  const t = nowSeconds();
  if (tileId === TILE_WATER) {
    ctx.fillStyle = `rgba(188, 232, 255, ${0.1 + (Math.sin(t * 4 + x * 0.13 + y * 0.07) + 1) * 0.045})`;
    ctx.fillRect(x + 3, y + 8, TILE - 6, 3);
    ctx.fillRect(x + 7, y + 18, TILE - 12, 2);
  }
  if (tileId === TILE_CROP) {
    const sway = Math.sin(t * 3 + x * 0.08 + y * 0.11) * 2;
    ctx.strokeStyle = "rgba(255, 245, 145, 0.28)";
    ctx.lineWidth = 1;
    for (let i = 0; i < 3; i++) {
      const bladeX = x + 8 + i * 7;
      ctx.beginPath();
      ctx.moveTo(bladeX, y + 23);
      ctx.lineTo(bladeX + sway, y + 9);
      ctx.stroke();
    }
  }
}

function drawSpeedStreaks(player: Player, color: string): void {
  ctx.save();
  ctx.strokeStyle = color;
  ctx.lineWidth = 2;
  ctx.globalAlpha = 0.45;
  for (let i = -1; i <= 1; i++) {
    const side = { x: -player.direction.y * i * 8, y: player.direction.x * i * 8 };
    ctx.beginPath();
    ctx.moveTo(-player.direction.x * 10 + side.x, -player.direction.y * 10 + side.y);
    ctx.lineTo(-player.direction.x * 34 + side.x, -player.direction.y * 34 + side.y);
    ctx.stroke();
  }
  ctx.restore();
}

function drawPlayer(player: Player): void {
  if (player.hp <= 0) {
    drawDeathPlayer(player);
    return;
  }

  const speedActive = nowSeconds() < player.speedUntil;
  const step = Math.sin(player.animationTime);
  const bob = player.hp > 0 ? Math.abs(step) * (speedActive ? 5 : player.isSprinting ? 4 : 2) : 0;
  const squash = player.hp > 0 ? 1 + Math.abs(step) * 0.05 : 1;
  const recoilOffset = player.recoil * 5;

  ctx.save();
  ctx.translate(player.position.x, player.position.y);
  ctx.fillStyle = "rgba(0, 0, 0, 0.28)";
  ctx.beginPath();
  ctx.ellipse(0, 14, PLAYER_RADIUS + 4, 7, 0, 0, Math.PI * 2);
  ctx.fill();

  if (speedActive || player.isSprinting) {
    drawSpeedStreaks(player, speedActive ? "#b6f56d" : "#f1d875");
  }

  ctx.translate(-player.direction.x * recoilOffset, -player.direction.y * recoilOffset - bob);
  ctx.scale(squash, 1 / squash);
  ctx.fillStyle = player.hp <= 0 ? "#555" : player.hitFlash > 0 ? "#fff0c0" : player.color;
  ctx.beginPath();
  ctx.arc(0, 0, PLAYER_RADIUS, 0, Math.PI * 2);
  ctx.fill();

  const image = assets.player;
  if (image.complete && image.naturalWidth > 0) {
    const row = directionRow(player.direction);
    ctx.drawImage(image, 0, row * 38, 36, 38, -18, -28, 36, 38);
  }

  if (player.pickupFlash > 0) {
    ctx.strokeStyle = "rgba(255, 255, 255, 0.75)";
    ctx.lineWidth = 2;
    ctx.beginPath();
    ctx.arc(0, 0, 28 + (1 - player.pickupFlash) * 16, 0, Math.PI * 2);
    ctx.stroke();
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

function drawDeathPlayer(player: Player): void {
  const image = assets.deathRabbit;
  const frame = Math.min(3, Math.floor(player.deathTime / 0.16));
  const angle = Math.atan2(player.deathDirection.y, player.deathDirection.x);
  const settle = clamp(player.deathTime / 0.7, 0, 1);

  ctx.save();
  ctx.translate(player.position.x, player.position.y);
  ctx.rotate(angle);
  ctx.globalAlpha = 1 - clamp((player.deathTime - 1.3) / 0.8, 0, 0.45);
  ctx.fillStyle = `rgba(0, 0, 0, ${0.28 * settle})`;
  ctx.beginPath();
  ctx.ellipse(0, 20, PLAYER_RADIUS + 12, 7, 0, 0, Math.PI * 2);
  ctx.fill();

  if (image.complete && image.naturalWidth > 0) {
    const frameWidth = image.naturalWidth / 4;
    ctx.drawImage(image, frame * frameWidth, 0, frameWidth, image.naturalHeight, -36, -46, 72, 72);
  } else {
    ctx.rotate(settle * Math.PI / 2);
    ctx.fillStyle = "#bcb5aa";
    ctx.beginPath();
    ctx.ellipse(0, 0, PLAYER_RADIUS + 6, PLAYER_RADIUS, 0, 0, Math.PI * 2);
    ctx.fill();
  }
  ctx.restore();
}

function drawBullet(bullet: Bullet): void {
  ctx.save();
  ctx.translate(bullet.position.x, bullet.position.y);
  ctx.rotate(Math.atan2(bullet.direction.y, bullet.direction.x));
  ctx.globalAlpha = bullet.assisted ? 0.68 : 0.45;
  ctx.fillStyle = bullet.color;
  ctx.fillRect(bullet.assisted ? -28 : -22, -2, bullet.assisted ? 24 : 18, 4);
  ctx.globalAlpha = 1;
  if (bullet.assisted) {
    ctx.strokeStyle = "#d5f3ff";
    ctx.lineWidth = 2;
    ctx.beginPath();
    ctx.arc(0, 0, 9, -0.7, 0.7);
    ctx.stroke();
  }
  const image = assets.bullet;
  if (image.complete && image.naturalWidth > 0) {
    ctx.drawImage(image, -5, -3);
  } else {
    ctx.fillStyle = bullet.color;
    ctx.fillRect(-6, -3, 12, 6);
  }
  ctx.restore();
}

function drawRune(rune: Rune): void {
  const image = rune.type === "armor" ? assets.armorRune : rune.type === "speed" ? assets.speedRune : null;
  const pulse = Math.sin(nowSeconds() * 5 + rune.pulseOffset);
  const scale = 1 + pulse * 0.08;
  const color = rune.type === "armor" ? "#8fd0ff" : rune.type === "speed" ? "#b5f56c" : "#ff9a5a";

  ctx.save();
  ctx.translate(rune.position.x, rune.position.y);
  ctx.globalAlpha = 0.25 + (pulse + 1) * 0.12;
  ctx.strokeStyle = color;
  ctx.lineWidth = 3;
  ctx.beginPath();
  ctx.arc(0, 0, 23 + pulse * 4, 0, Math.PI * 2);
  ctx.stroke();
  ctx.globalAlpha = 1;
  ctx.scale(scale, scale);
  if (image && image.complete && image.naturalWidth > 0) {
    ctx.drawImage(image, -15, -15);
  } else {
    ctx.fillStyle = color;
    ctx.beginPath();
    ctx.moveTo(0, -16);
    ctx.lineTo(16, 12);
    ctx.lineTo(-16, 12);
    ctx.closePath();
    ctx.fill();
    ctx.strokeStyle = "#231f20";
    ctx.lineWidth = 3;
    ctx.stroke();
    ctx.strokeStyle = "#fff4a3";
    ctx.lineWidth = 2;
    ctx.beginPath();
    ctx.moveTo(-7, -2);
    ctx.lineTo(7, -2);
    ctx.moveTo(-10, 5);
    ctx.lineTo(10, 5);
    ctx.stroke();
  }
  ctx.restore();
}

function drawParticle(particle: Particle): void {
  const alpha = clamp(1 - particle.age / particle.ttl, 0, 1);
  ctx.save();
  ctx.globalAlpha = alpha;
  ctx.fillStyle = particle.color;
  ctx.beginPath();
  ctx.arc(particle.position.x, particle.position.y, particle.radius * (0.6 + alpha * 0.4), 0, Math.PI * 2);
  ctx.fill();
  ctx.restore();
}

function drawFloatingText(floatingText: FloatingText): void {
  const alpha = clamp(1 - floatingText.age / floatingText.ttl, 0, 1);
  ctx.save();
  ctx.globalAlpha = alpha;
  ctx.fillStyle = floatingText.color;
  ctx.font = "bold 14px Arial";
  ctx.textAlign = "center";
  ctx.strokeStyle = "rgba(0, 0, 0, 0.75)";
  ctx.lineWidth = 3;
  ctx.strokeText(floatingText.text, floatingText.position.x, floatingText.position.y);
  ctx.fillText(floatingText.text, floatingText.position.x, floatingText.position.y);
  ctx.restore();
}

function drawStatus(player: Player, x: number, y: number, width: number): void {
  const speedLeft = Math.max(0, player.speedUntil - nowSeconds());
  const scatterLeft = Math.max(0, player.scatterUntil - nowSeconds());
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
  if (scatterLeft > 0) {
    const scatterWidth = 92;
    drawBar("SG", scatterLeft, 8, x + width - scatterWidth, y + 10, scatterWidth, "#ff9a5a");
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

function randomUnitVector(): Vec {
  const angle = Math.random() * Math.PI * 2;
  return { x: Math.cos(angle), y: Math.sin(angle) };
}

function dot(a: Vec, b: Vec): number {
  return a.x * b.x + a.y * b.y;
}

function rotateVec(v: Vec, angle: number): Vec {
  const cos = Math.cos(angle);
  const sin = Math.sin(angle);
  return normalize({
    x: v.x * cos - v.y * sin,
    y: v.x * sin + v.y * cos
  });
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
