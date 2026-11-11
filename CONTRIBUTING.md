# CONTRIBUTING — How to Contribute to the Project

Welcome! This document explains how to properly create Issues and Pull Requests in the RSiSed project (Qt C++).
## Reporting Issues

Before creating an Issue, check if a similar one already exists. If not, choose the template that best describes the problem. This saves time for the team and speeds up triage.

### Available Issue Templates

- **[Bug]: Application Bug** — something is not working as expected.
- **[Feature]: New Feature Request** — a request to add new functionality.
- **[Build]: Build System Issue** — problems with qmake/CMake configuration, compiler settings, or CI builds.
- **[Dependencies]: Dependency Update** — updating Qt, third-party libraries, or submodules.
- **[Task]: Internal Task** — refactoring, tech debt, and other internal work.
- **[Migrate]: Migration Issue** — problems during migration (Qt 5→6, qmake→CMake, OS port, etc.).
- **[Perf]: Performance Regression** — slowdowns, dropped FPS, increased load times.
- **[Test]: Test Problem** — failing or flaky Qt tests.
- **[UI]: Layout / Scaling Issue** — clipped text, incorrect layout, DPI problems.
- **[Docs]: Documentation Issue** — inaccuracies, outdated instructions, improvement suggestions.

> **Tip:** When creating an Issue, always fill in the environment fields (OS, Qt, compiler) and reproduction steps. This is critical for Qt projects where behavior can differ between Linux and Windows.

---

## Submitting Pull Requests

We use specialized PR templates to make reviews predictable and high-quality. **Always choose the template matching the task type.**

### How to Choose a PR Template

When creating a PR, GitHub will offer a list of templates. Pick the one that matches the Issue type (or the type of change if there’s no Issue):

| Task / Change Type | PR Template | Template Path |
|--------------------|-------------|---------------|
| Bug fix | `bug_fix.md` | `.github/PULL_REQUEST_TEMPLATE/` |
| New feature | `feature.md` | `.github/PULL_REQUEST_TEMPLATE/` |
| Build system, flags, CI | `build_change.md` | `.github/PULL_REQUEST_TEMPLATE/` |
| Dependency update | `dependency_update.md` | `.github/PULL_REQUEST_TEMPLATE/` |
| Refactoring, tech debt, CI | `internal_task.md` | `.github/PULL_REQUEST_TEMPLATE/` |
| Migration (Qt 5→6, qmake→CMake, etc.) | `migration.md` | `.github/PULL_REQUEST_TEMPLATE/` |
| Performance fix | `performance_fix.md` | `.github/PULL_REQUEST_TEMPLATE/` |
| Test fix / improvement | `test_fix.md` | `.github/PULL_REQUEST_TEMPLATE/` |
| Layout / scaling / styles fix | `ui_layout_change.md` | `.github/PULL_REQUEST_TEMPLATE/` |
| Documentation update | `docs_update.md` | `.github/PULL_REQUEST_TEMPLATE/` |
| Generic (if none match) | `pull_request_template.md` | `.github/` |

> **Important:** Do not use the generic template if a specialized one fits. Specialized templates include the right checklists and sections (e.g., performance measurements, before/after screenshots, DPI testing) that are essential for a smooth review.

---

## General Requirements for All PRs

Regardless of the template, follow these rules:

- **Link to an Issue.** In the PR body, reference the related Issue (e.g., `Closes #123`). This helps track progress and auto-close tasks after merge.
- **Test on Both Platforms.** The project is cross-platform (Linux and Windows); changes must be verified on both. Include results in the Verification section.
- **Keep PRs Focused.** One PR = one task. Split unrelated changes into separate PRs.
- **Avoid Hard-Coded Pixel Sizes.** In Qt apps, this often breaks scaling and DPI. Use layouts, stretch factors, and size policies instead.
- **Do Not Leave Disabled Tests.** If a test is flaky, don’t use `QSKIP` without explanation. Instead, create a separate Issue to stabilize the test.
- **Commits and Messages.** Use conventional commits: type, scope, short description. You can reference related Issues in the commit footer.

---

## Example Scenarios

**Example 1: Fixed a file-loading bug**
- Issue: `[Bug]: File loading fails on Windows with large files`
- PR: use `bug_fix.md`. It includes sections to describe the bug, reproduction steps, and confirmation of the fix.

**Example 2: Porting a module to Qt 6**
- Issue: `[Migrate]: libshapes fails to build with Qt 6.8`
- PR: use `migration.md`. Attach before/after error screenshots, list replaced APIs, and confirm builds on both old and new stacks.

**Example 3: Optimized shape rendering**
- Issue: `[Perf]: Rendering 10k shapes dropped from 180 FPS to 95 FPS`
- PR: use `performance_fix.md`. Fill the Before/After measurements table with identical conditions (OS, Qt, build type) so the reviewer can objectively assess the gain.

**Example 4: Fixed button alignment in a dialog**
- Issue: `[UI]: Buttons are clipped at 200% scaling`
- PR: use `ui_layout_change.md`. Include screenshots at different DPI and window sizes to show the issue is resolved.

**Example 5: No suitable template**
- If your change doesn’t fit any category (e.g., updating dependencies, adjusting CI without refactoring), use the generic `pull_request_template.md`. Briefly describe the intent and how you verified the changes.

---

## Environment and Verification

We support:
- **OS:** Linux (Ubuntu 22.04+), Windows (10/11)
- **Qt:** 6.5+ (parallel support for Qt 5 during migration)
- **Compilers:** GCC, Clang, MSVC
- **Build System:** CMake (qmake is used only in legacy modules; migration is in progress)

When verifying a PR, pay attention to:
- CI builds (GitHub Actions) on all target platforms.
- Running the full test suite (`ctest` or Qt Test).
- Visual UI checks at different scales (100%, 200%) and resolutions.

---

## Review and Merge Process

1. **Create a PR** with the appropriate template and fill all required sections.
2. **Assign a reviewer** (if you know who owns the module) or leave unassigned—the team will pick it up in order.
3. **Respond to comments** and apply changes to the same PR (do not create a new one).
4. **Once approved**, the PR will be merged into the main branch.

If you have questions or aren’t sure which template to choose, write in the Issue discussion or team chat. We’ll help you pick the right format.

Thank you for your contribution! Together we’re making RSiSed more stable and user-friendly.

---

## УЧАСТИЕ В ПРОЕКТЕ — Русскоязычная справка (кратко)

Ниже — краткая русскоязычная справка для быстрого старта. Основной текст выше — на английском, так как Issue и PR ведутся на английском.

- **Шаблоны Issue:** выбирайте подходящий тип (Bug, Feature, Migration, Perf, Test, UI, Docs, Task) — это ускоряет разбор.
- **Шаблоны PR:** всегда подбирайте шаблон под тип задачи. Специализированные шаблоны содержат нужные чеклисты (замеры, скриншоты, проверка DPI и т.д.).
- **Связь с Issue:** в теле PR указывайте связанный Issue (например, `Closes #123`) — это помогает отслеживать прогресс.
- **Проверка на двух платформах:** проект кроссплатформенный (Linux и Windows) — изменения нужно проверять на обеих ОС.
- **Один PR — одна задача:** не смешивайте несвязанные правки в одном PR.
- **Избегайте жёстких размеров в пикселях:** в Qt-приложениях это частая причина проблем с масштабированием. Используйте layout’ы, stretch-факторы и size policies.
- **Не отключайте тесты без объяснения:** если тест нестабилен, лучше завести отдельный Issue на его стабилизацию.
- **Окружение:** поддерживаются Linux (Ubuntu 22.04+) и Windows (10/11), Qt 6.5+, компиляторы GCC/Clang/MSVC, сборка на CMake (идёт миграция с qmake).

Если у вас есть вопросы или не уверены, какой шаблон выбрать — напишите в обсуждение Issue или в чат команды. Мы поможем подобрать правильный формат.
