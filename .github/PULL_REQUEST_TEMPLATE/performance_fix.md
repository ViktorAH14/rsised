<!--
  Pull Request template: Performance Fix
  Mirrors the Performance Regression issue template (.github/ISSUE_TEMPLATE/performance_regression.yml).
-->

## Related Issue
<!-- Link the performance regression issue this PR fixes: #123, or "None" if none exists -->

## Affected Component
<!-- Same as the Performance Regression issue template: libshapes rendering, rsised file loading, UI responsiveness, etc. -->

## Type of Regression
<!-- Keep the applicable option(s) from the issue template -->
- [ ] Startup / Load Time Increase
- [ ] Per-Frame / Render Slowdown
- [ ] Algorithmic Complexity Regression
- [ ] Memory Allocation / GC-like Stalls
- [ ] QBENCHMARK Regression

## Root Cause
<!-- What caused the slowdown: changed algorithm, extra copies/allocation, synchronous I/O on the UI thread, lost caching, etc. -->
<!-- Skip if already fully described in the linked issue. -->

## Fix Description
<!-- What was changed: algorithm, data structures, caching, deferred work, threading, etc. -->

## Measurements
<!-- Same metrics and conditions as the issue (Baseline/Current fields). Fill one row per metric. -->
<!-- For QBENCHMARK regressions, paste the QBENCHMARK output before and after. -->
| Metric | Before | After | Conditions |
|--------|--------|-------|------------|
|        |        |       |            |

<!-- Conditions must match the issue environment: OS, Qt version, compiler, CPU/RAM, build type (Debug/Release),
     graphics backend (Raster/OpenGL). -->

## Measurement Methodology
<!-- How the numbers were obtained: number of runs, warm-up, what was measured (QElapsedTimer, perf, QBENCHMARK). -->
- [ ] Consistent measurements (multiple runs, results averaged or worst case noted).
- [ ] Same hardware and comparable background load as the issue report.
- [ ] No new debug logging or instrumentation left in hot paths.

## Verification
| OS | Qt Version | Compiler | Build Type | Graphics Backend | Result |
|----|------------|----------|------------|------------------|--------|
|    |            |          |            |                  |        |

- [ ] Performance restored (within the target stated in the issue, if one was given).
- [ ] No functional regressions: existing tests pass.
- [ ] Manual smoke test: app launches, core editing features work normally.

## Notes for Reviewers
<!-- Tradeoffs: memory vs speed, readability vs micro-optimizations, platform-specific paths. -->
<!-- Link to profiling data (flamegraphs, perf output) if available. -->

## Author Checklist
- [ ] Related performance issue linked (if one exists).
- [ ] Measurements table filled with before/after numbers under matching conditions.
- [ ] No unrelated changes mixed in (kept the fix focused).
- [ ] No new compiler warnings introduced.
- [ ] Verified on both Linux and Windows (or explained why not).
