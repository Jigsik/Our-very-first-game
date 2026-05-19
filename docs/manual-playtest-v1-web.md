# Manual Playtest: v1 Web

Playwright screenshot verification is currently blocked on this WSL/Ubuntu image, so this checklist is the lightweight gate for gameplay changes.

## Start

```bash
cd /home/jigs/.openclaw/workspace/repos/Our-very-first-game
git switch ai/reboot
git pull
cd v1-web
npm install
npm run dev
```

Open:

```text
http://localhost:5177/v1-web/
```

## Checklist

- Page loads without a console-visible crash.
- Countdown appears, then the round starts.
- P1 moves with WASD and sprints with Left Shift.
- P2 moves with arrow keys and sprints with Right Shift.
- Sprint is visible as light dust/trails; the speed rune feels stronger and temporarily overrides sprint.
- Both players start in open space.
- Stone, stump, and brick tiles block movement.
- Players can move through grass, sand, crop, water, and flag tiles.
- P1 shoots with Space.
- P2 shoots with slash.
- Shooting produces recoil, muzzle flash, and a small camera kick.
- Bullets disappear on solid tiles.
- Bullet impacts produce visible sparks.
- Bullets damage the other player.
- Hits flash the target and show damage or block feedback.
- Armor rune adds armor and removes active speed.
- Speed rune increases speed and removes active armor.
- Scatter rune enables a short three-shot spread and is strongest at close range.
- Rune pickups pulse and burst so the pickup event is obvious.
- A player wins when the other reaches 0 HP.
- The losing rabbit plays a short fall-to-ground animation.
- Score increments for the winner.
- The win moment produces a short burst effect.
- Pressing R after a win restarts the round and keeps score.
- The arena feels small enough that players can find each other quickly.

## Current Known Gap

Issue #11 tracks automated screenshot verification. Playwright 1.60 currently refuses Chromium installation on `ubuntu26.04-x64`, so use this manual checklist until that is solved.
