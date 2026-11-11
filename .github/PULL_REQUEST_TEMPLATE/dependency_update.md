<!--
  Pull Request template: Dependency Update / Change
  Mirrors the Dependency Issue issue template (.github/ISSUE_TEMPLATE/dependency_issue.yml).
-->

## Related Issue
<!-- Link the dependency issue this PR fixes: #123, or "None" if none exists -->

## Summary
<!-- What changed: dependency added, updated, replaced, bundled, or linked differently. -->

## Dependency
<!-- Name & version, same format as the Dependency Issue template -->
<!-- e.g., OpenSSL 3.0, libpng 1.6, custom internal lib -->

## Change Type
<!-- Keep the applicable option(s) from the Dependency Issue "Issue Type" list -->
- [ ] Build / Link Failure Due to Dependency
- [ ] Runtime Missing Symbol / Load Error
- [ ] Version Conflict Between Libraries
- [ ] Incompatible ABI / Qt Version
- [ ] License / Distribution Concern

## Integration Details
<!-- How the dependency is now linked — this is the core section of this PR -->
<!-- Static/shared, pkg-config, CMake, qmake .pri, custom paths, bundled sources vs system package -->
- Linked via: <!-- e.g., app.pri with INCLUDEPATH/LIBS, pkg-config, vcpkg -->
- Detection: <!-- how availability is checked at build/configure time -->
- Bundled vs system: <!-- whether sources are vendored or a system package is required -->

## Before / After
<!-- For failure fixes: key error lines before the change, successful output after. -->
<!-- For updates: old version → new version and what the upgrade changes for the project. -->

## License / Distribution Notes
<!-- Required when license or redistribution is affected: license name, compatibility, bundling implications. -->
<!-- Skip if not applicable. -->

## Environment Tested
<!-- Same format as the Dependency Issue template: OS, Qt version, compiler, package manager -->
| OS | Qt Version | Compiler | Package Manager | Result |
|----|------------|----------|-----------------|--------|
|    |            |          |                 |        |

## Notes for Reviewers
<!-- e.g., minimum required version bumped, new build prerequisite, platform-specific caveats -->

## Author Checklist
- [ ] Build succeeds on Linux.
- [ ] Build succeeds on Windows.
- [ ] Application runs on both platforms (no runtime load/symbol errors).
- [ ] No new compiler warnings introduced.
- [ ] Related dependency issue linked (if one exists).
- [ ] Build/install instructions updated if prerequisites changed (README, INSTALL, CI config).
