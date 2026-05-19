# Asset Catalog

This catalog records the reusable assets found in the old repository. License/source information is mostly unknown, so all assets should be treated as internal prototype material until proven otherwise.

## Source Folders

- `Grafika/`: original working graphics and source PSD files.
- `Grafika/podklady na mapu/`: first tile source set.
- `Grafika/podklady na mapu2/`: expanded tile source set with flag, crop, dirt, water.
- `Grafika/new_map/`: rendered large map plus map text.
- `The_Game/The_Game/Images/`: runtime image assets for the C++ prototype.
- `The_Game/The_Game/Maps/`: runtime tile maps and tilesets.
- `Sounds/`: original loose sound/music files.
- `The_Game/The_Game/Sounds/`: runtime sound/music assets.
- `Fonts/`: original font folder.

## Player And Character Sprites

| Path | Size | Notes |
| --- | ---: | --- |
| `Grafika/player_1.png` | 96x128 | Old 4-direction player sheet, indexed PNG. |
| `Grafika/player_2.png` | 96x128 | Alternate player sheet, indexed PNG. |
| `Grafika/player_3.png` | 96x128 | Alternate player sheet, indexed PNG. |
| `Grafika/rabbit.png` | 36x41 | Single rabbit pose. |
| `Grafika/rabbit left.png` | 36x41 | Single rabbit pose facing left. |
| `Grafika/rabbit_back.png` | 37x45 | Single rabbit back pose. |
| `Grafika/rabbit_front.png` | 35x41 | Single rabbit front pose. |
| `Grafika/rabbitx4.png` | 36x152 | Four-direction rabbit sheet; close to runtime `player_1.png`. |
| `Grafika/rabbitx4.psd` | 36x152 | Photoshop source, RGB. |
| `Grafika/rabbitx44.psd` | 36x152 | Photoshop source, RGBA. |
| `The_Game/The_Game/Images/player_1.png` | 36x152 | Runtime player sheet used by newer `Player`; four vertical directions. |
| `v1-web/assets/rabbit-death.svg` | 576x144 | New v1 web four-frame death/fall sprite sheet, generated locally after the image-generation service hit usage limits. |
| `The_Game/The_Game/Images/player_11.png` | 96x128 | Runtime legacy player sheet. |
| `The_Game/The_Game/Images/enemy_1.png` | 96x128 | Runtime enemy sheet. |

Reuse note: `The_Game/The_Game/Images/player_1.png` is the most important player asset because the newer code explicitly loads it and assumes 1 column by 4 rows.

## Projectiles And Combat

| Path | Size | Notes |
| --- | ---: | --- |
| `Grafika/bullet.png` | 10x6 | Bullet source. |
| `The_Game/The_Game/Images/bullet.png` | 10x6 | Runtime bullet loaded by `Bullet.cpp`. |
| `Grafika/rocket_missile.png` | 25x10 | Smaller rocket missile source. |
| `Grafika/rocket turn.png` | 80x15 | Larger turning/animation rocket strip. |
| `The_Game/The_Game/Images/rocket_missile.png` | 80x15 | Runtime rocket strip. |
| `The_Game/The_Game/Images/rocket_missile_old.png` | 40x16 | Old rocket missile. |

Reuse note: bullets are enough for v1; rockets can wait until the basic combat loop works.

## Runes And Buff Visuals

| Path | Size | Notes |
| --- | ---: | --- |
| `Grafika/runa1.png` | 28x24 | Source rune, likely speed. |
| `Grafika/runa2.png` | 26x25 | Source rune, likely armor. |
| `The_Game/The_Game/Images/speed_rune.png` | 28x24 | Runtime speed rune. |
| `The_Game/The_Game/Images/armor_rune.png` | 26x25 | Runtime armor rune. |
| `Grafika/armor.png` | 50x50 | Source armor visual. |
| `Grafika/armor.psd` | 50x50 | Photoshop source, RGBA. |
| `The_Game/The_Game/Images/armor.png` | 57x57 | Runtime rotating armor shield. |
| `The_Game/The_Game/Images/armor1.png` | 50x50 | Alternate armor visual. |
| `The_Game/The_Game/Images/armor.gif` | 50x50 | Animated or legacy armor GIF. |
| `The_Game/The_Game/Images/circle.gif` | 800x600 | Large circle effect/background, purpose unclear. |

Reuse note: speed and armor rune images are directly mapped by `SpeedRune.cpp` and `ArmorRune.cpp`.

## Tiles And Maps

| Path | Size | Notes |
| --- | ---: | --- |
| `The_Game/The_Game/Maps/mapa.png` | 120x60 | Runtime tileset, likely 4x2 tiles at 30x30. |
| `The_Game/The_Game/Maps/mapa44.png` | 60x60 | Earlier tileset, likely 2x2 tiles. |
| `The_Game/The_Game/Maps/mapa.txt` | 100x100 tiles | Main runtime tile map, ASCII. |
| `The_Game/The_Game/Maps/mapa5.txt` | unknown | UTF-8 with BOM; alternate map data. |
| `Grafika/new_map/mapa_1.png` | 3000x3000 | Large rendered map image, matches 100x100 tiles at 30px. |
| `Grafika/new_map/mapa_1.txt` | unknown | UTF-8 with BOM; likely source map data. |
| `Grafika/new_map/nápady.txt` | text | Map ideas. |

Tile source set 1:

| Path | Size | Notes |
| --- | ---: | --- |
| `Grafika/podklady na mapu/all in one.png` | 60x60 | Combined 2x2 tile source. |
| `Grafika/podklady na mapu/tráva.png` | 30x30 | Grass tile. |
| `Grafika/podklady na mapu/písek.png` | 30x30 | Sand tile. |
| `Grafika/podklady na mapu/kamení.png` | 30x30 | Stones tile. |
| `Grafika/podklady na mapu/pařez.png` | 30x30 | Stump obstacle. |

Tile source set 2:

| Path | Size | Notes |
| --- | ---: | --- |
| `Grafika/podklady na mapu2/all in one.png` | 120x60 | Combined 4x2 tile source, matches runtime tileset size. |
| `Grafika/podklady na mapu2/flag.png` | 30x30 | Capture-the-flag object. |
| `Grafika/podklady na mapu2/tráva.png` | 30x30 | Grass tile. |
| `Grafika/podklady na mapu2/písek.png` | 30x30 | Sand tile. |
| `Grafika/podklady na mapu2/kamení.png` | 30x30 | Stones tile. |
| `Grafika/podklady na mapu2/obilí.png` | 30x30 | Crop/hiding tile. |
| `Grafika/podklady na mapu2/hlína.png` | 30x30 | Dirt/hazard idea. |
| `Grafika/podklady na mapu2/voda.png` | 30x30 | Water hazard idea. |
| `Grafika/podklady na mapu2/pařez.png` | 30x30 | Stump obstacle. |

Reuse note: `The_Game/The_Game/Maps/mapa.txt` plus `mapa.png` is the most important map pair for engine spikes. `Grafika/new_map/mapa_1.png` is useful as a quick visual background if parsing the tile map is too slow for a spike.

## Audio

Durations were not captured because `ffprobe` is not installed in the current WSL environment. File format metadata comes from `file`.

| Path | Format | Notes |
| --- | --- | --- |
| `Sounds/Menu.wav` | WAV PCM 16-bit stereo 44.1 kHz | Menu candidate. |
| `Sounds/musicdvdv.wav` | WAV PCM 16-bit stereo 44.1 kHz | Music candidate. |
| `Sounds/possible game music.wav` | WAV PCM 16-bit stereo 44.1 kHz | Music candidate. |
| `Sounds/rocket_missile_sound.wav` | WAV PCM 16-bit stereo 44.1 kHz | Projectile sound. |
| `Sounds/sprint.wav` | WAV PCM 16-bit stereo 44.1 kHz | Sprint sound. |
| `The_Game/The_Game/Sounds/walk.wav` | WAV PCM 16-bit stereo 44.1 kHz | Runtime walk loop. |
| `The_Game/The_Game/Sounds/sprint.wav` | WAV PCM 16-bit stereo 44.1 kHz | Runtime sprint loop. |
| `The_Game/The_Game/Sounds/music.wav` | WAV PCM 16-bit stereo 44.1 kHz | Runtime music loaded by `Game.cpp`. |
| `The_Game/The_Game/Sounds/musicfd.mp3` | MP3 192 kbps 44.1 kHz joint stereo | Alternate music. |
| `The_Game/The_Game/Sounds/rocket_missile_sound.wav` | WAV PCM 16-bit stereo 44.1 kHz | Runtime projectile sound. |
| `The_Game/The_Game/Sounds/canary.wav` | WAV PCM 8-bit mono 11025 Hz | Purpose unclear. |

Reuse note: keep audio optional for early prototypes. Movement/combat feel matters more than sound parity at this stage.

## Fonts

| Path | Format | Notes |
| --- | --- | --- |
| `Fonts/Face Your Fears.ttf` | TrueType | Copyright line in metadata names David Kerkhoff, 2011. License rights are not proven here. |
| `The_Game/The_Game/Fonts/STENCIL.TTF` | TrueType | Referenced by code as `Fonts/STENCIL.ttf`; case-insensitive Windows path worked, case-sensitive Linux path needs care. |
| `The_Game/The_Game/Fonts/HARNGTON.TTF` | TrueType | Legacy decorative font. |
| `The_Game/The_Game/Fonts/vgafixe.fon` | Windows FON | Legacy bitmap/system font format. |

Reuse note: avoid shipping with unclear font licensing until checked. Use system/default fonts in web and Godot spikes.

## Reuse Priority

1. `The_Game/The_Game/Images/player_1.png`
2. `The_Game/The_Game/Images/bullet.png`
3. `The_Game/The_Game/Images/speed_rune.png`
4. `The_Game/The_Game/Images/armor_rune.png`
5. `The_Game/The_Game/Images/armor.png`
6. `The_Game/The_Game/Maps/mapa.txt`
7. `The_Game/The_Game/Maps/mapa.png`
8. `Grafika/new_map/mapa_1.png` as a fallback background

## Unknowns

- Original source/license for most images.
- Whether the font can be redistributed.
- Whether any audio was original, downloaded, or temporary.
- Whether the large map PNG should be source of truth or generated output.
