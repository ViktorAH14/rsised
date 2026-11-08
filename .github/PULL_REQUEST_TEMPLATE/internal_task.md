<!--
  Pull Request template: Internal Task
  Mirrors the Internal Task issue template (.github/ISSUE_TEMPLATE/internal_task.yml).
-->

## Related Task
<!-- Link the internal task issue: #123, or "None" if none exists -->

## Scope / Area
<!-- Same as the Internal Task issue template -->
<!-- e.g., libshapes build system, rsised tests, CI pipeline -->

## What Was Done
<!-- How the goal was achieved. Reference the Goal and Acceptance Criteria from the linked issue. -->

## Acceptance Criteria Verification
<!-- Copy the Acceptance Criteria from the linked issue and mark each point. -->
<!-- Example (from the issue template placeholder): -->
- [ ] All modules use common.pri
- [ ] No direct INCLUDEPATH in .pro
<!-- Replace the example items with the real criteria from the issue. -->

## Behavior Impact
<!-- Internal tasks should not change user-visible behavior. Confirm or describe what changed. -->
- [ ] No user-visible behavior changes
<!-- If there are changes, describe them and explain why they are acceptable. -->

## Testing
- [ ] Existing tests pass.
- [ ] Refactoring/CI changes verified (build, pipeline run, etc.).

## Platform Verification
| OS | Qt Version | Compiler | Result |
|----|------------|----------|--------|
|    |            |          |        |

## Notes for Reviewers
<!-- Rationale for non-obvious decisions, follow-up tasks, migration notes -->

## Author Checklist
- [ ] Related internal task linked (if one exists).
- [ ] Acceptance criteria from the issue are met and checked above.
- [ ] No leftover debug code, commented-out blocks, or TODOs without follow-up issues.
- [ ] No new compiler warnings introduced.
- [ ] Verified on both Linux and Windows (or explained why not).
