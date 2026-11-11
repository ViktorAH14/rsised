<!--
  Pull Request template: UI / Layout Change
  Mirrors the UI / Layout Issue issue template (.github/ISSUE_TEMPLATE/ui_layout_issue.yml).
-->

## Related Issue
<!-- Link the UI/layout issue this PR fixes: #123, or "None" if none exists -->

## Widget / Window
<!-- Same as the UI / Layout Issue template: MainWindow, ShapeEditorDialog, status bar panel, etc. -->

## Issue Type
<!-- Keep the applicable option(s) from the UI / Layout Issue template -->
- [ ] Widget Clipping / Truncated Text
- [ ] Layout Not Resizing Properly
- [ ] DPI / Scaling Issues (High DPI / 200%)
- [ ] Alignment / Spacing Problems
- [ ] Dynamic Content Not Reflowing
- [ ] Stylesheet Rendering Differences

## Description
<!-- What was wrong and what is expected now. Mention if it occurred only at certain window sizes/DPI. -->

## Layout Changes
<!-- What was changed: layout structure (QVBoxLayout/QGridLayout/QFormLayout), stretch factors, -->
<!-- size policies, margins, minimum/maximum sizes, stylesheets. -->
<!-- If the issue's Layout Details described the old structure, show how it changed. -->

## Screenshots
<!-- Before/after screenshots at multiple sizes and DPI settings. -->
<!-- GitHub supports drag-and-drop for images. -->

| State | Normal DPI | High DPI / 200% | Small window |
|-------|------------|-----------------|--------------|
| Before|            |                 |              |
| After |            |                 |              |

<!-- If screenshots do not capture the problem (e.g., alignment), describe what to look at instead. -->

## Verification
<!-- Same format as the issue's Screen / DPI Info: resolution, scale factor, OS, theme -->
| OS | Resolution | Scale Factor | Theme | Result |
|----|------------|--------------|-------|--------|
|    |            |              |       |        |

- [ ] Layout behaves correctly at different window sizes (resizable, maximized, small).
- [ ] Tested at multiple DPI settings (100%, 200%, or the scale factors from the issue).
- [ ] No custom stylesheets added that override layout behavior (or justified explicitly).
- [ ] Existing tests pass (including any GUI tests for affected widgets).

## Notes for Reviewers
<!-- Platform-specific caveats: font metrics differences Linux vs Windows, native style quirks, -->
<!-- high-DPI policy changes, anything that needs visual review by a maintainer. -->

## Author Checklist
- [ ] Related UI issue linked (if one exists).
- [ ] Before/after screenshots attached for both Linux and Windows (or explained why not).
- [ ] No functional changes mixed in (layout-only PR, or changes clearly separated).
- [ ] No hard-coded pixel sizes where relative sizing is expected (unless justified).
- [ ] No new compiler warnings introduced.
