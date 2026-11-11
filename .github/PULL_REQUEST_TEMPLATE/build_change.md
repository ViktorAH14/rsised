<!--
  Pull Request template: Build Change
  Mirrors the Build Issue issue template (.github/ISSUE_TEMPLATE/build_issue.yml).
-->

## Related Issue
<!-- Link the build issue this PR fixes: #123, or "None" if none exists -->

## Summary
<!-- What build-related change is made: qmake configuration, dependencies, build scripts, CI, etc. -->
<!-- Mention key files touched: e.g., RSiSed.pro, .pri files, .github/workflows -->

## Build Error / Problem Solved
<!-- If fixing a build failure: paste the key error lines that were previously reported. -->
<!-- If a proactive build change (e.g., migration to CMake): state what it improves. -->

## Change Details
<!-- What exactly changed and why:
     - qmake/project files
     - dependencies (added/updated/removed)
     - compiler flags or defines
     - CI workflow
-->

## Build Environment Tested
<!-- Same format as the Build Issue template — fill in for every configuration you verified -->
| OS | Qt Version | Compiler | Build Command | Result |
|----|------------|----------|---------------|--------|
|    |            |          |               |        |

## Before / After Output
<!-- For build fixes: key lines of build output before and after the change. -->

## Notes for Reviewers
<!-- Platform-specific caveats, known remaining issues, breaking changes for other developers -->

## Author Checklist
- [ ] Build succeeds on Linux.
- [ ] Build succeeds on Windows.
- [ ] No new compiler warnings introduced.
- [ ] Related build issue linked (if one exists).
- [ ] Documentation updated if build instructions changed (README, INSTALL, etc.).
