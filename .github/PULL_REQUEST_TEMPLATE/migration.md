<!--
  Pull Request template: Migration Step
  Mirrors the Migration Issue issue template (.github/ISSUE_TEMPLATE/migration_issue.yml).
-->

## Related Issue
<!-- Link the migration issue this PR addresses: #123, or "None" if none exists -->

## Migration Target
<!-- Keep the applicable option(s) from the Migration Issue template -->
- [ ] Qt 5 → Qt 6
- [ ] Compiler Upgrade (g++/clang/MSVC)
- [ ] OS Port (Windows→Linux, macOS→Windows, etc.)
- [ ] Build System (qmake→CMake)

## Affected Module
<!-- Same as the Migration Issue template: libshapes, rsised, UI layer, tests, etc. -->

## Migration Step
<!-- Migrations are usually done incrementally. Describe which step this PR covers, -->
<!-- so it can be reviewed in isolation (e.g., "Port libshapes to Qt6 container APIs only"). -->

## What Changed
<!-- Same as the Migration Issue template: code changes, removed APIs, new flags, updated .pri/.pro files. -->

## Resolved Errors / Warnings
<!-- Key errors or deprecation warnings from the issue, now fixed by this PR. -->
<!-- Before: -->

    (paste error lines here)

<!-- After: -->

    (paste clean build output here)

## Compatibility Notes
<!-- For Qt 5 → 6: deprecated APIs replaced, behavioral changes (e.g., high-DPI always on, graphics view changes). -->
<!-- For compiler/OS port: platform-specific code paths touched (#ifdefs, etc.). -->
<!-- Skip if not applicable. -->

## Verification
| OS | Qt Version | Compiler | Result |
|----|------------|----------|--------|
|    |            |          |        |

- [ ] Builds on the new target (Qt version / compiler / OS / build system).
- [ ] Still builds on the old target, if the migration is incremental.
- [ ] Existing tests pass.
- [ ] Manual smoke test performed (app launches, core editing features work).

## Notes for Reviewers
<!-- Rationale for non-obvious replacements, remaining migration steps, follow-up issues -->

## Author Checklist
- [ ] Related migration issue linked (if one exists).
- [ ] No unrelated changes mixed in (kept the step as small as possible).
- [ ] Replaced APIs fully removed or #ifdef-guarded (no dead code left).
- [ ] No new compiler warnings introduced (or pre-existing ones documented).
- [ ] Build/install docs updated if the migration changes them (README, INSTALL, CI config).
