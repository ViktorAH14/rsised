<!--
  Pull Request template: Test Fix / Improvement
  Mirrors the Test Issue issue template (.github/ISSUE_TEMPLATE/test_issue.yml).
-->

## Related Issue
<!-- Link the test issue this PR fixes: #123, or "None" if none exists -->

## Test Class and Method
<!-- Same format as the Test Issue template: tst_ClassName::testMethodName -->

## Test Type
<!-- Keep the applicable option(s) from the Test Issue template -->
- [ ] Unit Test (non-GUI)
- [ ] GUI Test (mouse/keyboard simulation)
- [ ] Data-Driven Test
- [ ] Benchmark Test (QBENCHMARK)
- [ ] Integration Test

## Nature of the Fix
<!-- The main question for reviewers: was the code wrong or the test wrong? -->
- [ ] Product code fixed (test caught a real bug)
- [ ] Test itself fixed (flaky, wrong expectations, timing issue)
- [ ] Both

<!-- Briefly explain what exactly was wrong. -->

## Changes Made
<!-- For product code fixes: what changed in the tested behavior. -->
<!-- For test fixes: test restructuring, QSignalSpy usage, waits/timeouts, test data, fixture changes. -->

## Qt Test Specifics
<!-- Mirror the "Additional Context (Qt Test specifics)" field from the issue: -->
<!-- Timeouts (QTEST_FUNCTION_TIMEOUT), QSignalSpy, GUI simulation, QAbstractItemModelTester, QBENCHMARK baselines. -->
<!-- Describe how the fix addresses them. -->

## Failure Reproduction (Before)
<!-- The command that reproduced the failure, from the issue: -->
    ./tst_shapes -testfunction testIntersection
<!-- And a short excerpt of the failure output (QFAIL/QCOMPARE messages). Skip if identical to the issue. -->

## Verification
<!-- Same environment format as the Test Issue template: OS, Qt version, compiler, build type -->
| OS | Qt Version | Compiler | Build Type | Runs | Result |
|----|------------|----------|------------|------|--------|
|    |            |          |            |      |        |

- [ ] The failing test now passes consistently (multiple runs: number = N).
- [ ] Full Qt Test suite passes (no new failures in other tests).
- [ ] Full Qt Test log included in the PR or CI run (not just "passed").
- [ ] If the test was flaky: stable across repeated runs on both platforms.

## Notes for Reviewers
<!-- e.g., tightened/loosened timeouts, changed signal expectations, CI timing caveats -->

## Author Checklist
- [ ] Related test issue linked (if one exists).
- [ ] Verified the same test on another Qt version, if possible (as suggested in the issue checklist).
- [ ] No timing-sensitive constructs added (or justified explicitly).
- [ ] No disabled/skipped tests left behind (QSKIP, #ifdef'd-out checks) without explanation.
- [ ] No new compiler warnings introduced.
- [ ] Verified on both Linux and Windows (or explained why not).
