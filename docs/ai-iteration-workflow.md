# AI Iteration Workflow

This repository uses `ai/reboot` as the long-running integration branch for AI-only work. Martin approved direct commits and pushes to this branch so small internal steps do not wait on a pull request every time.

## Branch Policy

- Work on `ai/reboot`.
- Keep `master` stable.
- Push finished, verified slices directly to `ai/reboot`.
- Use a PR to `master` only for larger milestones or when Martin explicitly asks.
- Do not force-push unless Martin explicitly approves it.

## One-Issue Loop

1. Fetch and inspect open issues.
2. Pick one ready issue with clear acceptance criteria.
3. Check whether it is already covered by a commit, branch, or closed issue.
4. Implement the smallest useful slice.
5. Run the smallest meaningful verification.
6. Commit with a terse message.
7. Push to `origin/ai/reboot`.
8. Close the issue with the commit hash and verification commands.
9. Report to Discord `#asistent` with status, changed area, verification, and blockers.

## Ready Issue Criteria

An issue is ready when:

- desired behavior is clear,
- target folder or module is clear,
- verification is possible,
- missing tools are not required or already installed,
- the issue can be finished without broad architecture decisions.

If an issue is useful but not ready, add a clarifying comment or create a smaller issue instead of expanding scope silently.

## Stop Conditions

Stop and report instead of inventing a workaround spiral when:

- a product choice is genuinely unclear,
- a required install needs Martin's password or an unsupported external tool,
- Playwright/browser/native window verification is blocked by missing system support,
- the same verification fails repeatedly after one reasonable fix attempt,
- a change would rewrite legacy archive code without a clear reason,
- Git reports non-trivial conflicts with changes not made in this run.

## Verification Defaults

For `v1-web/`:

```bash
cd v1-web
npm run check
npm run build
npm run dev
curl -fsS http://localhost:5177/v1-web/
```

For `spikes/sfml-cmake/`:

```bash
cd spikes/sfml-cmake
cmake -S . -B build
cmake --build build
```

For `spikes/godot/`:

```bash
~/.local/bin/godot4 --headless --path spikes/godot --check-only --script scripts/arena.gd
~/.local/bin/godot4 --headless --path spikes/godot --quit-after 3
```

Playwright screenshot verification is intentionally tracked separately because current Playwright does not support Chromium on this Ubuntu 26.04 WSL environment.

## Discord Report Format

Use this shape:

```text
Our Very First Game: <short status>.

- commit: <hash> on ai/reboot
- issue: #<number> <title>
- changed: <files/folders>
- verified: <commands>
- blockers: <none or exact blocker>
 [K]
```

Keep it short. Martin wants signal, not a ceremony.
