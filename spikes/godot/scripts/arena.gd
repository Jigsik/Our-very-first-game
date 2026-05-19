extends Node2D

const MAP_SIZE := Vector2(3000, 3000)
const PLAYER_RADIUS := 18.0
const BULLET_SPEED := 420.0
const BULLET_TTL := 1.6

var players := [
	{
		"id": "P1",
		"pos": Vector2(220, 220),
		"dir": Vector2.RIGHT,
		"color": Color("#7fd1ff"),
		"hp": 100,
		"armor": 0,
		"speed_until": 0.0,
		"cooldown": 0.0,
		"keys": ["p1_up", "p1_down", "p1_left", "p1_right", "p1_shoot"]
	},
	{
		"id": "P2",
		"pos": Vector2(580, 360),
		"dir": Vector2.LEFT,
		"color": Color("#ffcf70"),
		"hp": 100,
		"armor": 0,
		"speed_until": 0.0,
		"cooldown": 0.0,
		"keys": ["p2_up", "p2_down", "p2_left", "p2_right", "p2_shoot"]
	}
]

var bullets: Array[Dictionary] = []
var runes := [
	{"type": "armor", "pos": Vector2(400, 260), "ttl": 999.0},
	{"type": "speed", "pos": Vector2(760, 460), "ttl": 999.0}
]
var rune_timer := 5.0

func _ready() -> void:
	_register_actions()

func _process(delta: float) -> void:
	_update_players(delta)
	_update_bullets(delta)
	_update_runes(delta)
	if _has_winner() and Input.is_key_pressed(KEY_R):
		_reset_round()
	queue_redraw()

func _draw() -> void:
	var panel_w := (get_viewport_rect().size.x - 8.0) / 2.0
	var panel_h := get_viewport_rect().size.y - 52.0
	_draw_panel(0, Rect2(0, 0, panel_w, panel_h), players[0])
	_draw_panel(1, Rect2(panel_w + 8.0, 0, panel_w, panel_h), players[1])
	draw_rect(Rect2(0, panel_h, get_viewport_rect().size.x, 52), Color("#0d1110"))
	draw_string(ThemeDB.fallback_font, Vector2(24, panel_h + 32), "P1 HP %s Armor %s" % [players[0].hp, players[0].armor], HORIZONTAL_ALIGNMENT_LEFT, -1, 18, Color("#f8f4dc"))
	draw_string(ThemeDB.fallback_font, Vector2(panel_w + 32, panel_h + 32), "P2 HP %s Armor %s" % [players[1].hp, players[1].armor], HORIZONTAL_ALIGNMENT_LEFT, -1, 18, Color("#f8f4dc"))

func _draw_panel(_index: int, panel: Rect2, focus: Dictionary) -> void:
	draw_rect(panel, Color("#1d2b20"))
	var camera := Vector2(
		clampf(focus.pos.x - panel.size.x / 2.0, 0, MAP_SIZE.x - panel.size.x),
		clampf(focus.pos.y - panel.size.y / 2.0, 0, MAP_SIZE.y - panel.size.y)
	)
	var offset := panel.position - camera
	draw_set_transform(offset)
	_draw_grid()
	for rune in runes:
		draw_rect(Rect2(rune.pos - Vector2(12, 12), Vector2(24, 24)), Color("#8fd0ff") if rune.type == "armor" else Color("#b5f56c"))
	for bullet in bullets:
		draw_circle(bullet.pos, 4, Color("#f9f2a7"))
	for player in players:
		draw_circle(player.pos, PLAYER_RADIUS, Color("#555555") if player.hp <= 0 else player.color)
		draw_line(player.pos, player.pos + player.dir * 28.0, Color.BLACK, 3.0)
		if player.armor > 0:
			draw_arc(player.pos, 26.0, 0, TAU, 40, Color("#96d7ff"), 3.0)
	draw_set_transform(Vector2.ZERO)
	draw_rect(panel, Color("#9ca38d"), false, 2.0)

func _draw_grid() -> void:
	for x in range(0, int(MAP_SIZE.x), 30):
		draw_line(Vector2(x, 0), Vector2(x, MAP_SIZE.y), Color(0, 0, 0, 0.07))
	for y in range(0, int(MAP_SIZE.y), 30):
		draw_line(Vector2(0, y), Vector2(MAP_SIZE.x, y), Color(0, 0, 0, 0.07))

func _update_players(delta: float) -> void:
	for index in players.size():
		var player = players[index]
		if player.hp <= 0:
			continue
		var keys: Array = player.keys
		var input := Vector2(
			Input.get_action_strength(keys[3]) - Input.get_action_strength(keys[2]),
			Input.get_action_strength(keys[1]) - Input.get_action_strength(keys[0])
		).normalized()
		if input != Vector2.ZERO:
			player.dir = input
		var speed := 250.0 if Time.get_ticks_msec() / 1000.0 < player.speed_until else 170.0
		player.pos = (player.pos + input * speed * delta).clamp(Vector2(20, 20), MAP_SIZE - Vector2(20, 20))
		player.cooldown = maxf(0.0, player.cooldown - delta)
		if Input.is_action_pressed(keys[4]) and player.cooldown == 0.0:
			bullets.append({"owner": index, "pos": player.pos + player.dir * 22.0, "dir": player.dir, "ttl": BULLET_TTL})
			player.cooldown = 0.35

func _update_bullets(delta: float) -> void:
	for bullet in bullets:
		bullet.pos += bullet.dir * BULLET_SPEED * delta
		bullet.ttl -= delta
		for index in players.size():
			if index == bullet.owner:
				continue
			var player = players[index]
			if player.hp > 0 and player.pos.distance_to(bullet.pos) < 24.0:
				_apply_damage(player, 20)
				bullet.ttl = 0.0
	bullets = bullets.filter(func(bullet): return bullet.ttl > 0.0)

func _update_runes(delta: float) -> void:
	for rune in runes:
		rune.ttl -= delta
		for player in players:
			if player.pos.distance_to(rune.pos) < 32.0:
				_apply_rune(player, rune.type)
				rune.ttl = 0.0
	runes = runes.filter(func(rune): return rune.ttl > 0.0)
	rune_timer -= delta
	if rune_timer <= 0.0 and runes.size() < 3:
		runes.append({
			"type": "armor" if randf() > 0.5 else "speed",
			"pos": Vector2(randf_range(120, 1000), randf_range(120, 700)),
			"ttl": 12.0
		})
		rune_timer = randf_range(5.0, 9.0)

func _apply_damage(player: Dictionary, amount: int) -> void:
	var blocked: int = mini(player.armor, amount)
	player.armor -= blocked
	player.hp = maxi(0, player.hp - (amount - blocked))

func _apply_rune(player: Dictionary, type: String) -> void:
	if type == "armor":
		player.armor = 60
		player.speed_until = 0.0
	else:
		player.speed_until = Time.get_ticks_msec() / 1000.0 + 10.0
		player.armor = 0

func _has_winner() -> bool:
	return players.any(func(player): return player.hp <= 0)

func _reset_round() -> void:
	players[0].pos = Vector2(220, 220)
	players[1].pos = Vector2(580, 360)
	for player in players:
		player.hp = 100
		player.armor = 0
		player.speed_until = 0.0
		player.cooldown = 0.0
	bullets.clear()

func _register_actions() -> void:
	var bindings := {
		"p1_up": KEY_W,
		"p1_down": KEY_S,
		"p1_left": KEY_A,
		"p1_right": KEY_D,
		"p1_shoot": KEY_SPACE,
		"p2_up": KEY_UP,
		"p2_down": KEY_DOWN,
		"p2_left": KEY_LEFT,
		"p2_right": KEY_RIGHT,
		"p2_shoot": KEY_SLASH
	}
	for action in bindings.keys():
		if not InputMap.has_action(action):
			InputMap.add_action(action)
		var event := InputEventKey.new()
		event.keycode = bindings[action]
		InputMap.action_add_event(action, event)
