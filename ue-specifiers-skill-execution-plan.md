# ue-specifiers Skill 执行计划

> 目标：把 `fjz13/UnrealSpecifiers` 升级为可被本地 Codex 长期使用、可审查、可学习、可持续维护的 `ue-specifiers` Skill。  
> 适用场景：UE C++ 反射宏、Specifier、Meta、Flags、UHT、Blueprint 暴露、Details Panel、Replication、SaveGame、Config、Instanced、Editor-only 等知识的推荐、审查、修复和沉淀。  
> 建议执行环境：本地 Codex + Git 仓库工作区。  
> 建议语言：Skill 输出、文档、审查记录默认使用中文；代码注释可中英混合，但面向用户的结论用中文。

---

## 0. 背景与设计原则

`UnrealSpecifiers` 当前是一个非常有价值的 UE 标识符知识库，但它主要是“人类阅读型文档”。现在要将其升级为 AI 可稳定使用的 Skill，需要补上以下能力：

1. **使用入口**：Codex 能知道什么时候该使用这个 Skill。
2. **知识索引**：AI 能快速查到某个 specifier / meta 的摘要、用途、冲突、坑点、版本状态。
3. **场景 recipes**：AI 不只是回答“某个标识符是什么”，还要能回答“我这个开发场景应该怎么写”。
4. **旧知识审查**：对已有知识逐条进行 UE 版本校验，避免过时信息继续误导 AI。
5. **持续学习**：从 LiveData、LiteAngelScript、EchoNotes 等真实项目开发中沉淀新的经验。
6. **安全推广**：AI 可以把新经验写入 inbox，但不能直接污染正式知识库；只有 review / promote 后才能进入主索引。

核心原则：

```text
UnrealSpecifiers = 原始知识源
ue-specifiers Skill = AI 使用、审查、学习、维护这些知识的工作流
```

不要把所有原始文档全部塞进 `SKILL.md`。`SKILL.md` 只负责：

- 触发条件
- 工作流
- 输出格式
- 审查规则
- 学习规则
- 安全约束

真正的知识放到：

```text
references/
scripts/
templates/
```

---

## 1. 本地仓库与路径约定

本机固定使用两个仓库：

```text
D:/github/UnrealSpecifiers
D:/github/AgentSkill
```

其中：

```text
D:/github/UnrealSpecifiers
```

继续作为原始知识源，本计划文件当前位于：

```text
D:/github/UnrealSpecifiers/ue-specifiers-skill-execution-plan.md
```

Skill 的 canonical 源放在本仓库，便于随 `UnrealSpecifiers` 一起 push 到 GitHub：

```text
D:/github/UnrealSpecifiers/skills/ue-specifiers
```

本机 Codex 消费端通过 `AgentSkill` 接入。不要在 `AgentSkill` 里维护第二份内容，优先使用 junction 指向 canonical 源：

```text
D:/github/AgentSkill/skills/unreal-engine/ue-specifiers
  -> D:/github/UnrealSpecifiers/skills/ue-specifiers
```

同时需要更新现有 UE 聚合技能路由：

```text
D:/github/AgentSkill/skills/unreal-engine/SKILL.md
```

执行阶段命令默认从 `D:/github/UnrealSpecifiers` 仓库根目录运行。只有“本机接入”步骤需要进入 `D:/github/AgentSkill` 修改聚合路由或创建 junction。不要再假设计划文件已经复制到 `AgentSkill/.agents/specs/`。

本地可执行约束：

1. canonical skill 路径统一写作 `skills/ue-specifiers`。
2. 空目录占位统一使用 `README.md`，不使用 `.gitkeep`。
3. 第一阶段创建本库 skill；第七阶段才更新 `D:/github/AgentSkill/skills/unreal-engine/SKILL.md` 的 `Skill Map` 和 `Routing Rules`。
4. 所有从 `UnrealSpecifiers` 抽取的知识都保留 `source_doc`，路径相对 `D:/github/UnrealSpecifiers`。
5. 脚本用法以 `python skills/ue-specifiers/scripts/<script>.py ...` 为准。
6. `AgentSkill/skills/unreal-engine/ue-specifiers` 必须是 junction 或同步结果，不是独立编辑源。

当前验证目标：

- `D:/github/GitWorkspace/Hello/Hello.uproject` 已升级到 UE5.8，并已在本机编译成功。
- 后续 audit / finding / sample-based validation 优先按 UE5.8 进行。
- 编译成功只说明样例工程可作为 UE5.8 本机样例语料，不自动证明每个 specifier/meta 行为已验证。
- 本仓库 `bat/` 提供 UE5.8 验证 wrapper：`build-hello.bat` 编译 Hello，`editor-hello.bat` 打开编辑器观察样例行为，`inspect-hello-log.bat` 提取最新 Hello 日志。
- `Insider` 是样例/对比代码集合，不是 automation test suite；验证 Details Panel、Blueprint、资产或运行时表现时，以编辑器观察和日志记录为主。
- 第七阶段本机接入暂缓，等 `skills/ue-specifiers` 内容更完善后再执行。

GitHub 发布形态：

```text
UnrealSpecifiers/
  skills/
    ue-specifiers/
      SKILL.md
      references/
      scripts/
      templates/
```

外部使用者 clone 本仓库后，可以将 `skills/ue-specifiers` 复制或链接到自己的 Agent skill 根目录。仓库内不要依赖 `D:/github/AgentSkill` 才能使用；`AgentSkill` 只是本机开发和 Codex 路由接入层。

执行前自检：

```powershell
Set-Location D:\github\UnrealSpecifiers
git status --short
Test-Path .\skills\ue-specifiers\references\sources
Test-Path D:\github\AgentSkill\skills\unreal-engine\SKILL.md
python --version
is --files -g "*.md" . | Select-Object -First 20
```

预期：

- `D:/github/UnrealSpecifiers/skills/ue-specifiers/references/sources` 存在。
- `D:/github/AgentSkill/skills/unreal-engine/SKILL.md` 存在。
- `is --files` 能列出 `references/sources/...` 下的 Markdown 文件；如果 `is` 不可用，用 `Get-ChildItem D:\github\UnrealSpecifiers\skills\ue-specifiers\references\sources -Recurse -Filter *.md` 临时代替。

---

## 2. 第一阶段：创建 Skill 基础骨架

### 2.1 目标

在 `D:/github/UnrealSpecifiers` 仓库中创建：

```text
skills/
  ue-specifiers/
    SKILL.md
    CHANGELOG.md
    README.md

    references/
      README.md

      indexes/
        specifiers.index.md
        metas.index.md
        flags.index.md
        recipes.index.md

      recipes/
        property-details-panel.md
        property-blueprint-exposure.md
        blueprint-function-node.md
        replicated-property.md
        savegame-property.md
        config-property.md
        instanced-subobject.md
        edit-condition.md
        call-in-editor.md
        world-context.md

      pitfalls/
        common-misuse.md
        stale-or-version-sensitive.md
        ai-hallucination-traps.md

      conflicts/
        property-edit-vs-visible.md
        blueprint-readonly-vs-readwrite.md
        replication-conflicts.md

      audits/
        audit-manifest.jsonl
        audit-status.jsonl
        findings/
          README.md
        reports/
          README.md

      learning/
        inbox/
          README.md
        reviewed/
          README.md
        promoted/
          README.md
        rejected/
          README.md

    scripts/
      README.md
      build_index.py
      audit_manifest.py
      query_specifier.py
      lint_unreal_header.py
      learn_from_patch.py
      promote_learning.py

    templates/
      audit-finding.md
      learning-note.md
      recipe.md
      specifier-entry.json
      meta-entry.json
```

本机实现固定使用每个空目录里的 `README.md` 作为占位，不创建 `.gitkeep`。

### 2.2 `SKILL.md` 初版内容

创建 `skills/ue-specifiers/SKILL.md`：

```md
---
name: ue-specifiers
description: Use when editing, reviewing, validating, or learning Unreal Engine C++ reflection specifiers and metadata, including UCLASS, USTRUCT, UENUM, UINTERFACE, UPROPERTY, UFUNCTION, UPARAM, UMETA, meta=(...), Blueprint exposure, Details Panel behavior, replication, SaveGame, Config, Instanced objects, editor-only behavior, UHT diagnostics, Unreal reflection flags, and Unreal Engine version-specific specifier behavior.
---

# ue-specifiers

This skill helps AI agents choose, verify, correct, and continuously improve Unreal Engine C++ specifier and metadata knowledge.

## Main purposes

1. Recommend correct Unreal specifiers and metadata during UE C++ development.
2. Review existing UCLASS / UPROPERTY / UFUNCTION / meta usage.
3. Audit existing UnrealSpecifiers knowledge against target Unreal Engine versions.
4. Learn from real project development and promote verified lessons back into this skill.

## Language

- Default output language: Chinese.
- Keep code identifiers in English.
- Keep Unreal Engine official terms in English when translation would reduce clarity.

## Knowledge trust levels

Every knowledge item should have one of these statuses:

- unknown
- imported_from_unreal_specifiers
- suspected_stale
- verified_UE5.8
- changed_in_version
- removed_or_deprecated
- project_observation_only
- promoted

Do not treat imported knowledge as fully verified unless it has explicit verification evidence.

## Required workflow for recommendations

When recommending specifiers or metadata:

1. Identify the UE macro involved.
2. Identify the user intent:
   - Details Panel
   - Blueprint exposure
   - serialization
   - config
   - SaveGame
   - replication
   - editor-only
   - instanced subobject
   - UHT behavior
3. Search `references/recipes/` first.
4. Search `references/indexes/` second.
5. Check `references/conflicts/`.
6. Check `references/pitfalls/`.
7. Mention version uncertainty if the item is not verified for the target UE version.
8. Provide:
   - 推荐写法
   - 原因
   - 替代方案
   - 常见误用
   - 相关本地知识路径

## Required workflow for audits

When auditing old knowledge:

1. Pick a small batch from `references/audits/audit-manifest.jsonl`.
2. For each item, check:
   - source document claim
   - Unreal Engine source evidence if available
   - UHT / reflection flag behavior if applicable
   - minimal repro if needed
3. Write one finding file per item.
4. Update `references/audits/audit-status.jsonl`.
5. Do not overwrite canonical knowledge until the finding is reviewed or promoted.

## Required workflow for learning

When learning from daily development:

1. Extract the concrete lesson from the project change.
2. Write a note into `references/learning/inbox/`.
3. Include:
   - project name
   - file path
   - before / after code
   - problem
   - fix
   - related specifier or meta
   - confidence level
   - whether this is project-specific or general UE behavior
4. Do not promote directly unless the user explicitly asks to promote.
5. Promote only after review or reproduction.

## Important rules

- Do not invent Unreal specifiers or metadata keys.
- Do not silently overwrite existing knowledge.
- If knowledge is version-sensitive, record the UE version.
- Prefer actual Unreal Engine source or compiler behavior over memory.
- If evidence is insufficient, mark the item as uncertain.
- AI may write `learning/inbox`, but must not overwrite `indexes`, `recipes`, `pitfalls`, or `conflicts` unless the user explicitly runs a promote/update command.
```

### 2.3 第一阶段验收标准

完成后应满足：

- `skills/ue-specifiers/SKILL.md` 存在。
- Skill 名称为 `ue-specifiers`。
- 有 `references/indexes`、`references/recipes`、`references/audits`、`references/learning` 四类目录。
- `SKILL.md` 明确了：
  - 推荐流程
  - audit 流程
  - learning 流程
  - 不允许凭空编造
  - 不允许自动污染正式知识库
- 本阶段不修改 `D:/github/AgentSkill`，本机接入放到第七阶段。

### 2.4 推荐 Codex 指令

在 `D:/github/UnrealSpecifiers` 仓库根目录执行：

```text
请根据 D:/github/UnrealSpecifiers/ue-specifiers-skill-execution-plan.md 的第一阶段，创建 skills/ue-specifiers 的基础目录和初版 SKILL.md。注意：
1. 输出和文档默认中文。
2. 不要创建无意义的 .gitkeep，如果需要占位目录，用 README.md。
3. 不要实现复杂脚本，只创建带 TODO 的脚本文件和模板文件。
4. 不要复制 D:/github/UnrealSpecifiers/Doc 原始全文。
5. 完成后列出创建和修改的文件清单。
```

---

## 3. 第二阶段：建立 AI 可读索引

### 3.1 目标

从 `UnrealSpecifiers/skills/ue-specifiers/references/sources` 中抽取最小 AI 索引，不要求一次完整覆盖全部条目，先做高频 P0 条目。

优先 P0：

```text
UPROPERTY:
- EditAnywhere
- EditDefaultsOnly
- EditInstanceOnly
- VisibleAnywhere
- VisibleDefaultsOnly
- VisibleInstanceOnly
- BlueprintReadOnly
- BlueprintReadWrite
- Category
- SaveGame
- Transient
- DuplicateTransient
- Config
- GlobalConfig
- Replicated
- ReplicatedUsing
- Instanced

UFUNCTION:
- BlueprintCallable
- BlueprintPure
- BlueprintImplementableEvent
- BlueprintNativeEvent
- CallInEditor
- Server
- Client
- NetMulticast

常见 meta:
- DisplayName
- ToolTip
- ShortToolTip
- ClampMin
- ClampMax
- UIMin
- UIMax
- EditCondition
- EditConditionHides
- InlineEditConditionToggle
- AllowPrivateAccess
- WorldContext
- HidePin
- DefaultToSelf
- AutoCreateRefTerm
- AdvancedDisplay
- ExpandEnumAsExecs
```

### 3.2 `specifiers.index.md` 格式

路径：

```text
skills/ue-specifiers/references/indexes/specifiers.index.md
```

格式建议：

```md
# Specifiers Index

> 该文件是给 AI 快速检索用的摘要索引，不替代原始 UnrealSpecifiers 文档。

## UPROPERTY - Details Panel

| ID | 摘要 | 使用场景 | 相关项 | 冲突项 | 状态 |
|---|---|---|---|---|---|
| UPROPERTY.EditAnywhere | 默认值和实例 Details Panel 均可编辑 | 设计师和关卡实例都需要编辑 | EditDefaultsOnly, EditInstanceOnly | VisibleAnywhere | imported_from_unreal_specifiers |
| UPROPERTY.EditDefaultsOnly | 只允许默认值编辑 | 只希望在 CDO / 蓝图默认值中配置 | EditAnywhere | VisibleDefaultsOnly | imported_from_unreal_specifiers |
| UPROPERTY.EditInstanceOnly | 只允许实例编辑 | 每个关卡实例可单独配置 | EditAnywhere | VisibleInstanceOnly | imported_from_unreal_specifiers |
```

### 3.3 `metas.index.md` 格式

路径：

```text
skills/ue-specifiers/references/indexes/metas.index.md
```

格式建议：

```md
# Metas Index

## Details Panel

| ID | Macro | 摘要 | 使用场景 | 相关项 | 状态 |
|---|---|---|---|---|---|
| meta.EditCondition | UPROPERTY | 条件控制属性是否可编辑 | bool 条件控制另一个属性 | EditConditionHides, InlineEditConditionToggle | imported_from_unreal_specifiers |
| meta.EditConditionHides | UPROPERTY | 条件不满足时隐藏属性 | 希望隐藏而不是禁用 | EditCondition | imported_from_unreal_specifiers |
```

### 3.4 JSONL 第二阶段可暂缓

第一版先用 `.md`，更便于 AI 和人类共同维护。后续再生成：

```text
specifiers.index.jsonl
metas.index.jsonl
```

### 3.5 第二阶段验收标准

- `specifiers.index.md` 至少包含 P0 中 20 个高频 specifier。
- `metas.index.md` 至少包含 P0 中 15 个高频 meta。
- 每个条目至少有：
  - ID
  - 摘要
  - 使用场景
  - 相关项
  - 状态
- 如果知识尚未重新校验，状态必须是 `imported_from_unreal_specifiers`，不要写成 verified。

### 3.6 推荐 Codex 指令

```text
请根据 D:/github/UnrealSpecifiers/ue-specifiers-skill-execution-plan.md 的第二阶段，从 D:/github/UnrealSpecifiers/skills/ue-specifiers/references/sources 中抽取 P0 高频条目，生成 skills/ue-specifiers/references/indexes/specifiers.index.md 和 metas.index.md。

要求：
1. 只做摘要索引，不复制大段原文。
2. 每个条目标注 status=imported_from_unreal_specifiers。
3. 不确定的地方标注 uncertain，不要脑补。
4. 保留原始文档路径，方便后续追溯。
5. 完成后输出覆盖了哪些条目，哪些条目没有找到。
```

---

## 4. 第三阶段：创建场景 Recipes

### 4.1 目标

让 AI 在真实开发场景中能直接给出推荐写法，而不是只查某个标识符定义。

第一批 recipes：

```text
property-details-panel.md
property-blueprint-exposure.md
blueprint-function-node.md
replicated-property.md
savegame-property.md
config-property.md
instanced-subobject.md
edit-condition.md
call-in-editor.md
world-context.md
```

### 4.2 Recipe 模板

路径：

```text
skills/ue-specifiers/templates/recipe.md
```

模板：

```md
# 场景：<场景标题>

## 适用问题

用户通常会这样问：

- 
- 

## 推荐写法

```cpp
// Minimal example
```

## 为什么这样写

-

## 替代方案

### 方案 A

```cpp

```

适合：

不适合：

### 方案 B

```cpp

```

适合：

不适合：

## 常见误用

-

## 版本状态

- UE5.8:

## 相关知识

- indexes:
- original docs:
- audit findings:
```

### 4.3 示例：`property-blueprint-exposure.md`

```md
# 场景：属性需要在 Details Panel 可编辑，同时 Blueprint 可读写

## 适用问题

用户通常会这样问：

- 这个属性想在蓝图里读写，应该加什么？
- EditAnywhere 是不是等于 BlueprintReadWrite？
- 我想让设计师能在面板调参数，同时蓝图也能访问。

## 推荐写法

```cpp
UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Config")
float MoveSpeed = 600.0f;
```

## 为什么这样写

- `EditAnywhere` 控制 Details Panel 中是否可编辑。
- `BlueprintReadWrite` 控制 Blueprint 是否可读写。
- 两者解决的问题不同，不应互相替代。

## 替代方案

### 只允许 Blueprint 读取，不允许 Blueprint 修改

```cpp
UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Config")
float MoveSpeed = 600.0f;
```

### 只允许默认值编辑，不允许实例编辑

```cpp
UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Config")
float MoveSpeed = 600.0f;
```

## 常见误用

- 只写 `EditAnywhere`，以为 Blueprint 就可以访问。
- 只写 `BlueprintReadWrite`，以为 Details Panel 就可以编辑。
- 忘记 `Category`，导致 Blueprint 或 Details Panel 分类不清晰。

## 版本状态

- UE5.8: pending_UE5.8_validation

## 相关知识

- indexes: `references/indexes/specifiers.index.md`
- original docs: `UnrealSpecifiers/skills/ue-specifiers/references/sources`
```

### 4.4 第三阶段验收标准

- 至少完成 10 个 recipes。
- 每个 recipe 都要有：
  - 适用问题
  - 推荐写法
  - 为什么
  - 替代方案
  - 常见误用
  - 版本状态
  - 相关知识
- 不确定版本行为时不能写 verified。

### 4.5 推荐 Codex 指令

```text
请根据 D:/github/UnrealSpecifiers/ue-specifiers-skill-execution-plan.md 的第三阶段，为 skills/ue-specifiers 创建第一批 10 个场景 recipes。

要求：
1. 不要写长篇百科，写成 AI 开发决策指南。
2. 每个 recipe 必须有最小 C++ 示例。
3. 版本状态默认 pending 或 imported_from_unreal_specifiers，不要假装已验证。
4. 所有文件放在 skills/ue-specifiers/references/recipes/。
5. 完成后更新 recipes.index.md。
```

---

## 5. 第四阶段：建立旧知识 Audit 闭环

### 5.1 目标

解决“现有 UnrealSpecifiers 里的知识可能过时”的问题。

不要让 AI 一次性大规模改文档。必须逐条审查、逐条记录证据、逐条标注状态。

### 5.2 Audit 状态

所有条目使用以下状态：

```text
imported_from_unreal_specifiers
audit_pending
audit_in_progress
verified_UE5.8
suspected_stale
changed_in_version
removed_or_deprecated
needs_manual_check
corrected_pending_review
corrected_verified
promoted
```

### 5.3 `audit-manifest.jsonl`

路径：

```text
skills/ue-specifiers/references/audits/audit-manifest.jsonl
```

示例：

```json
{"id":"UPROPERTY.EditAnywhere","kind":"specifier","macro":"UPROPERTY","name":"EditAnywhere","source_doc":"references/sources/Specifier/UPROPERTY/DetaisPanel/EditAnywhere/EditAnywhere.md","priority":"P0","status":"audit_pending","target_versions":["UE5.8"],"finding_path":"references/audits/findings/UPROPERTY.EditAnywhere.md"}
{"id":"UFUNCTION.BlueprintCallable","kind":"specifier","macro":"UFUNCTION","name":"BlueprintCallable","source_doc":"references/sources/Specifier/UFUNCTION/Blueprint/BlueprintCallable.md","priority":"P0","status":"audit_pending","target_versions":["UE5.8"],"finding_path":"references/audits/findings/UFUNCTION.BlueprintCallable.md"}
{"id":"meta.EditCondition","kind":"meta","macro":"UPROPERTY","name":"EditCondition","source_doc":"references/sources/Meta/DetailsPanel/EditCondition.md","priority":"P0","status":"audit_pending","target_versions":["UE5.8"],"finding_path":"references/audits/findings/meta.EditCondition.md"}
```

### 5.4 Audit Finding 模板

路径：

```text
skills/ue-specifiers/templates/audit-finding.md
```

内容：

```md
# Audit Finding: <ID>

## Status

- Current status:
- Target UE versions:
- Last checked:

## Original Claim

从原始文档提取的核心说法：

> 

## Source Document

- 

## Verification Evidence

### Unreal Engine Source Evidence

- Source version:
- Files checked:
- Symbols / flags found:

### UHT / Reflection Evidence

- UHT behavior:
- Reflection flags:
- Metadata behavior:

### Minimal Repro

```cpp
// Minimal code used to test
```

Observed behavior:

-

## Version Notes

- UE5.8:

## Corrections Needed

-

## AI Usage Note

给 AI 推荐时应该如何使用：

-

## Related Items

-
```

### 5.5 Audit 优先级

先审 P0：

```text
P0：高频且容易导致 AI 写错代码
- EditAnywhere / EditDefaultsOnly / EditInstanceOnly
- VisibleAnywhere / VisibleDefaultsOnly / VisibleInstanceOnly
- BlueprintReadOnly / BlueprintReadWrite
- BlueprintCallable / BlueprintPure
- Category
- DisplayName
- Replicated / ReplicatedUsing
- SaveGame
- Transient / DuplicateTransient
- Config / GlobalConfig
- Instanced / EditInlineNew
- CallInEditor
- WorldContext
- EditCondition / EditConditionHides / InlineEditConditionToggle

P1：常用但风险稍低
- AdvancedDisplay
- ClampMin / ClampMax / UIMin / UIMax
- AllowPrivateAccess
- BlueprintProtected / BlueprintPrivate
- HidePin / HideSelfPin
- AutoCreateRefTerm
- ExpandEnumAsExecs

P2：低频、模块特化、编辑器/插件相关
- Niagara
- GameplayAbility
- Animation
- Sequencer
- Editor-only metas
```

### 5.6 Audit 证据优先级

审查时证据优先级：

```text
最高可信：
1. 当前项目实际编译结果
2. 当前 UE 版本源码
3. 最小复现工程验证结果

中等可信：
4. Epic 官方文档
5. UnrealHeaderTool / CoreUObject 源码推断
6. 引擎注释

较低可信：
7. 社区文章
8. 论坛回答
9. AI 记忆
```

### 5.7 第四阶段验收标准

- `audit-manifest.jsonl` 至少包含 P0 条目。
- 每个 P0 条目有唯一 ID。
- 每个条目都有 `source_doc`、`priority`、`status`、`target_versions`、`finding_path`。
- 至少完成 5 个 audit finding。
- finding 里必须明确证据不足、已验证、或疑似过时。

### 5.8 推荐 Codex 指令

```text
请根据 D:/github/UnrealSpecifiers/ue-specifiers-skill-execution-plan.md 的第四阶段，为 skills/ue-specifiers 建立 audit 闭环。

先做：
1. 生成 references/audits/audit-manifest.jsonl，覆盖 P0 条目。
2. 创建 templates/audit-finding.md。
3. 选择 5 个最高频条目生成初版 finding 文件。
4. 不要直接修改 indexes/recipes，只记录 findings。
5. 如果无法访问本地 Unreal Engine 源码，明确标注 evidence_insufficient 或 needs_manual_check。
```

---

## 6. 第五阶段：建立 Learning 闭环

### 6.1 目标

解决“之后日常开发中持续优化 skill”的问题。

AI 在真实项目开发中遇到 specifier/meta 相关经验时，可以写入 learning inbox，但不能直接改正式知识库。

### 6.2 Learning Note 模板

路径：

```text
skills/ue-specifiers/templates/learning-note.md
```

内容：

```md
# Learning Note: <Title>

## Source Project

-

## Date

-

## Related Symbols

-

## Problem

-

## Before

```cpp

```

## After

```cpp

```

## Result

-

## Lesson

-

## Generality

选择一个：

- general_unreal_behavior
- version_specific_behavior
- project_convention
- uncertain

## Confidence

选择一个：

- low
- medium
- high

## Needs Verification

- yes
- no

## Candidate Updates

可能应该更新：

- references/recipes/
- references/pitfalls/
- references/conflicts/
- references/indexes/

## Do Not Promote Before

-
```

### 6.3 Learning 流程

```text
真实项目开发中发现经验
↓
写入 references/learning/inbox/
↓
人工或 AI review
↓
移动到 learning/reviewed/
↓
用户明确执行 promote
↓
更新 recipes / pitfalls / conflicts / indexes
↓
记录 CHANGELOG
↓
移动到 learning/promoted/
```

如果发现是项目特例：

```text
learning/inbox
↓
learning/rejected
```

### 6.4 什么时候触发 Learning

Skill 应在以下情况提示记录 learning：

```text
1. UHT 报错由 specifier/meta 引起
2. Blueprint 暴露行为和预期不一致
3. Details Panel 显示/编辑行为和预期不一致
4. 某个 specifier/meta 组合被验证有效
5. 某个组合被证明有坑
6. UE 版本升级后行为改变
7. AI 之前推荐错误，需要记反例
8. 项目形成了明确的 UE 反射宏风格约定
```

### 6.5 第五阶段验收标准

- 有 `templates/learning-note.md`。
- 有 `learning/inbox/reviewed/promoted/rejected` 目录。
- `SKILL.md` 明确禁止自动 promote。
- 至少创建 2 个示例 learning note：
  - 一个 general_unreal_behavior
  - 一个 project_convention
- `CHANGELOG.md` 有 learning / promoted 记录格式。

### 6.6 推荐 Codex 指令

```text
请根据 D:/github/UnrealSpecifiers/ue-specifiers-skill-execution-plan.md 的第五阶段，为 skills/ue-specifiers 建立 learning 闭环。

要求：
1. 创建 learning-note 模板。
2. 创建 inbox/reviewed/promoted/rejected 目录，并用 README.md 占位。
3. 在 SKILL.md 中明确：AI 可以写 inbox，但不能自动 promote。
4. 创建两个示例 learning note，一个通用 UE 行为，一个项目约定。
5. 更新 CHANGELOG.md 的格式说明。
```

---

## 7. 第六阶段：增加脚本工具

### 7.1 目标

脚本不是第一优先级，但会让 Skill 更像可长期维护的工具。

建议先实现轻量脚本，不要过度工程化。

### 7.2 `query_specifier.py`

用途：

```bash
python skills/ue-specifiers/scripts/query_specifier.py EditAnywhere
python skills/ue-specifiers/scripts/query_specifier.py "蓝图只读 属性可编辑"
python skills/ue-specifiers/scripts/query_specifier.py --macro UPROPERTY --name EditAnywhere
```

职责：

- 搜索 `references/indexes/*.md`
- 搜索 `references/recipes/*.md`
- 搜索 `references/pitfalls/*.md`
- 输出候选匹配及路径

第一版可以只做简单关键词匹配，不需要向量检索。

### 7.3 `audit_manifest.py`

用途：

```bash
python skills/ue-specifiers/scripts/audit_manifest.py list --priority P0
python skills/ue-specifiers/scripts/audit_manifest.py next --priority P0 --limit 10
python skills/ue-specifiers/scripts/audit_manifest.py status
```

职责：

- 读取 `audit-manifest.jsonl`
- 列出待审查条目
- 统计各状态数量
- 找出没有 finding 的条目

### 7.4 `learn_from_patch.py`

用途：

```bash
python skills/ue-specifiers/scripts/learn_from_patch.py --diff-file recent.diff --project LiveData
```

第一版只需要：

- 扫描 diff 中包含 `UCLASS`、`USTRUCT`、`UPROPERTY`、`UFUNCTION`、`meta=`
- 输出候选 learning note 草稿
- 不自动写正式知识库

### 7.5 `promote_learning.py`

用途：

```bash
python skills/ue-specifiers/scripts/promote_learning.py references/learning/reviewed/xxx.md
```

第一版可以只生成“建议修改清单”，不要自动改正式文件。

### 7.6 `lint_unreal_header.py`

用途：

```bash
python skills/ue-specifiers/scripts/lint_unreal_header.py Source/MyPlugin/Public/MyClass.h
```

第一版检查：

- `Edit*` 和 `Visible*` 是否混用
- `BlueprintReadOnly` 和 `BlueprintReadWrite` 是否混用
- `BlueprintCallable` / `BlueprintPure` 组合是否可疑
- `ReplicatedUsing` 是否缺少对应 `OnRep_` 函数声明
- `Blueprint` 暴露属性是否缺少 `Category`
- `meta=(...)` 是否有明显拼写风险

### 7.7 第六阶段验收标准

- 每个脚本有 `--help`。
- 脚本不依赖外部网络。
- 脚本默认只读，除非传入明确写入参数。
- 脚本失败时给出清晰错误信息。
- `scripts/README.md` 记录用法。

### 7.8 推荐 Codex 指令

```text
请根据 D:/github/UnrealSpecifiers/ue-specifiers-skill-execution-plan.md 的第六阶段，实现 skills/ue-specifiers 的第一版轻量脚本。

优先顺序：
1. query_specifier.py
2. audit_manifest.py
3. lint_unreal_header.py
4. learn_from_patch.py
5. promote_learning.py

要求：
1. 所有脚本必须有 --help。
2. 默认只读，不自动改正式知识库。
3. 使用 Python 标准库优先，不引入不必要依赖。
4. 为每个脚本在 scripts/README.md 中写用法。
```

---

## 8. 第七阶段：把 Skill 接入本机 Codex 和 UE 项目（暂缓）

### 8.1 目标

让本仓库发布的 `skills/ue-specifiers` 能被本机 Codex 使用，并让 LiveData、LiteAngelScript、EchoNotes 等项目在本地 Codex 工作时自动知道使用 `ue-specifiers`。

当前决策：暂缓执行第七阶段。等 `skills/ue-specifiers` 的索引、recipes、audit findings、learning 流程和脚本进一步完善后，再创建 junction 和更新 `AgentSkill` 路由。

本阶段允许修改：

```text
D:/github/AgentSkill/skills/unreal-engine/SKILL.md
```

本阶段允许创建 junction：

```text
D:/github/AgentSkill/skills/unreal-engine/ue-specifiers
  -> D:/github/UnrealSpecifiers/skills/ue-specifiers
```

不要在 `AgentSkill` 里手工维护第二份 `ue-specifiers` 内容。

### 8.2 项目级 `AGENTS.md` 推荐片段

在 UE 项目根目录 `AGENTS.md` 中添加：

```md
# Unreal Specifier Guidance

When editing Unreal Engine C++ headers, especially UCLASS, USTRUCT, UENUM, UINTERFACE, UPROPERTY, UFUNCTION, UPARAM, UMETA, or meta=(...), use the `ue-specifiers` skill.

Before changing reflection macros:

1. Identify whether the intent is Details Panel, Blueprint exposure, serialization, config, SaveGame, replication, editor-only behavior, instanced subobjects, or UHT behavior.
2. Use the skill's recipes and indexes before making recommendations.
3. Do not invent specifiers or meta keys.
4. Mention Unreal Engine version uncertainty if the behavior is not verified for this project's UE version.
5. If a new lesson is discovered during development, write a learning note to the skill's learning inbox rather than silently changing canonical knowledge.
```

### 8.3 本机 AgentSkill 接入

唯一源是本库：

```text
D:/github/UnrealSpecifiers/skills/ue-specifiers
```

创建 junction，把唯一源挂到现有 UE 聚合技能树：

```powershell
Set-Location D:\github\AgentSkill
New-Item -ItemType Junction `
  -Path D:\github\AgentSkill\skills\unreal-engine\ue-specifiers `
  -Target D:\github\UnrealSpecifiers\skills\ue-specifiers
```

如果目标路径已存在，先检查它是不是 junction：

```powershell
Get-Item D:\github\AgentSkill\skills\unreal-engine\ue-specifiers | Format-List FullName,LinkType,Target
```

只有确认它是旧的独立副本、且内容已经合并回 `D:/github/UnrealSpecifiers/skills/ue-specifiers` 后，才删除并重建 junction。

修改 `D:/github/AgentSkill/skills/unreal-engine/SKILL.md`，在 `Skill Map` 的 Core C++ 附近加入：

```md
- `ue-specifiers/SKILL.md`: reflection specifiers and metadata, including UCLASS, USTRUCT, UENUM, UINTERFACE, UPROPERTY, UFUNCTION, UPARAM, UMETA, meta=(...), Blueprint exposure, Details Panel behavior, UHT diagnostics, flags, and version-sensitive specifier behavior.
```

在 `Routing Rules` 中加入：

```md
- For UE reflection specifiers or metadata, including UCLASS / UPROPERTY / UFUNCTION / meta=(...), load `ue-specifiers/SKILL.md` plus `ue-cpp-foundations/SKILL.md`.
```

如果需要同步到 Codex / Claude 的用户级目录，只允许从 canonical 源单向同步：

```text
D:/github/UnrealSpecifiers/skills/ue-specifiers
  -> C:/Users/fjz13/.codex/skills/ue-specifiers
  -> C:/Users/fjz13/.claude/skills/ue-specifiers
```

同步脚本应先比较文件差异，再复制；不要手工在多个目录分别编辑同名 skill。GitHub 发布内容只看 `D:/github/UnrealSpecifiers/skills/ue-specifiers`。

### 8.4 第七阶段验收标准

- 至少一个 UE 项目 `AGENTS.md` 引用了 `ue-specifiers`。
- `D:/github/UnrealSpecifiers/skills/ue-specifiers/SKILL.md` 是 canonical 源。
- `D:/github/AgentSkill/skills/unreal-engine/ue-specifiers` 是 junction 或明确记录的同步副本。
- `D:/github/AgentSkill/skills/unreal-engine/SKILL.md` 已路由到 `ue-specifiers/SKILL.md`。
- Codex 在修改 `.h` 文件时能主动考虑该 skill。
- 能通过命令要求 Codex 使用该 skill 做 review。
- 日常开发中发现新经验时，能产生 learning note。

### 8.5 推荐 Codex 指令

```text
请根据 D:/github/UnrealSpecifiers/ue-specifiers-skill-execution-plan.md 的第七阶段，把 ue-specifiers 接入当前 UE 项目。

要求：
1. 在 D:/github/AgentSkill/skills/unreal-engine/ue-specifiers 创建指向 D:/github/UnrealSpecifiers/skills/ue-specifiers 的 junction。
2. 更新 D:/github/AgentSkill/skills/unreal-engine/SKILL.md，让 UE 反射 specifier/meta 任务能路由到 ue-specifiers。
3. 更新项目根目录 AGENTS.md。
4. 不要复制完整 UnrealSpecifiers 原始文档到项目内。
5. 只引用 skill。
6. 给出 3 个日常使用示例命令。
```

---

## 9. 推荐日常使用命令

### 9.1 推荐写法

```text
Use ue-specifiers recommend：我这个属性希望在 Details Panel 可编辑，但蓝图只读，应该怎么写？
```

### 9.2 审查头文件

```text
Use ue-specifiers review Source/LiveDataRuntime/Public/LiveDataTable.h
```

### 9.3 修复标识符问题

```text
Use ue-specifiers fix Source/LiveDataRuntime/Public/LiveDataTable.h
```

### 9.4 审查旧知识

```text
Use ue-specifiers audit UPROPERTY.EditAnywhere against UE5.8
```

### 9.5 批量审查

```text
Use ue-specifiers audit-batch priority=P0 target=UE5.8 limit=10
```

### 9.6 从近期 diff 学习

```text
Use ue-specifiers learn from recent diff
```

### 9.7 推广学习笔记

```text
Use ue-specifiers promote-learning references/learning/reviewed/20260604-xxx.md
```

---

## 10. 建议 Commit 拆分

不要一个大 commit 做完全部。建议拆成：

```text
commit 1: add ue-specifiers skill scaffold
commit 2: add P0 indexes
commit 3: add initial recipes
commit 4: add audit workflow templates and manifest
commit 5: add learning workflow templates
commit 6: add query and audit scripts
commit 7: add lint and learning helper scripts
commit 8: update docs and usage examples
```

这样后续 review 和回滚都容易。

---

## 11. Definition of Done

第一版 MVP 完成标准：

- [ ] `skills/ue-specifiers/SKILL.md` 存在且符合触发条件。
- [ ] `skills/ue-specifiers` 是 GitHub 发布用 canonical 源。
- [ ] `D:/github/AgentSkill/skills/unreal-engine/ue-specifiers` 已通过 junction 或明确记录的同步方式接入 canonical 源。
- [ ] `D:/github/AgentSkill/skills/unreal-engine/SKILL.md` 已把 `ue-specifiers/SKILL.md` 加入 UE 技能路由。
- [ ] 有 P0 `specifiers.index.md`。
- [ ] 有 P0 `metas.index.md`。
- [ ] 有至少 10 个 recipes。
- [ ] 有 audit manifest。
- [ ] 有 audit finding 模板。
- [ ] 有 learning note 模板。
- [ ] 有 learning inbox/reviewed/promoted/rejected 流程。
- [ ] `SKILL.md` 明确禁止自动 promote。
- [ ] 有 `CHANGELOG.md`。
- [ ] 至少一个脚本可用，例如 `query_specifier.py`。
- [ ] 至少一个 UE 项目 `AGENTS.md` 能引用此 skill。
- [ ] 本地 Codex 可以按 `Use ue-specifiers ...` 的方式调用。

---

## 12. 后续增强方向

第一版完成后，再考虑：

1. 自动从 `UnrealSpecifiers/skills/ue-specifiers/references/sources` 生成 JSONL。
2. 对接本地 UE 源码，自动定位 UHT / CoreUObject 相关定义。
3. 对接示例工程，自动生成最小 repro。
4. 做 `lint_unreal_header.py` 的 AST 级增强。
5. 做 `ue-specifiers audit-batch` 的完整闭环。
6. 输出 `dist/ue-specifiers.zip`，方便同步到多个 Agent。
7. 增加 MCP server，让 Codex 按需查询而不是加载静态文件。
8. 先为 UE5.8 建立 verified 知识层；需要兼容历史版本时，再补 UE5.4 / UE5.5 / UE5.6 / UE5.7 对比层。
9. 增加项目约定层，让 LiveData、LiteAngelScript、EchoNotes 可以有各自的 specifier 风格规则，但不污染通用知识库。

---

## 13. 给本地 Codex 的推荐总指令

本机直接使用当前计划文件：

```text
D:/github/UnrealSpecifiers/ue-specifiers-skill-execution-plan.md
```

在本地 Codex 中进入 `D:/github/UnrealSpecifiers` 工作区后执行：

```text
请阅读 D:/github/UnrealSpecifiers/ue-specifiers-skill-execution-plan.md，并按阶段执行 ue-specifiers skill 的建设。

先只执行第一阶段和第二阶段：
1. 创建 skills/ue-specifiers 基础骨架。
2. 创建初版 SKILL.md。
3. 从 D:/github/UnrealSpecifiers/skills/ue-specifiers/references/sources 中抽取 P0 高频条目，生成 specifiers.index.md 和 metas.index.md。
4. 不要修改 D:/github/AgentSkill，本机接入第七阶段暂缓，等 skill 内容更完善后再做。
5. 不要实现复杂脚本。
6. 不确定的信息必须标注 uncertain 或 imported_from_unreal_specifiers。
7. 完成后输出文件清单、未完成项、下一步建议。
```

第二次执行：

```text
继续阅读 D:/github/UnrealSpecifiers/ue-specifiers-skill-execution-plan.md，执行第三阶段和第四阶段：
1. 创建第一批 10 个 recipes。
2. 创建 audit manifest。
3. 创建 audit finding 模板。
4. 选择 5 个 P0 条目做初版 audit finding。
5. 不要把 audit finding 自动推广到正式 indexes/recipes。
6. 完成后输出每个 finding 的状态和证据不足之处。
```

第三次执行：

```text
继续阅读 D:/github/UnrealSpecifiers/ue-specifiers-skill-execution-plan.md，执行第五阶段和第六阶段：
1. 建立 learning inbox/reviewed/promoted/rejected 流程。
2. 创建 learning-note 模板。
3. 实现 query_specifier.py 和 audit_manifest.py 的第一版。
4. 所有脚本默认只读。
5. 更新 scripts/README.md 和 CHANGELOG.md。
```

第四次执行（暂缓，等 skill 更完善后再做）：

```text
继续阅读 D:/github/UnrealSpecifiers/ue-specifiers-skill-execution-plan.md，执行第七阶段：
1. 在 D:/github/AgentSkill/skills/unreal-engine/ue-specifiers 创建指向 D:/github/UnrealSpecifiers/skills/ue-specifiers 的 junction。
2. 更新 D:/github/AgentSkill/skills/unreal-engine/SKILL.md，让 UE 反射 specifier/meta 任务能路由到 ue-specifiers。
3. 更新至少一个 UE 项目 AGENTS.md 引用 ue-specifiers。
4. 不要在 AgentSkill 中维护第二份 ue-specifiers 内容。
5. 完成后输出 junction 状态、路由修改点、项目接入文件。
```

---

## 14. 最重要的约束

必须始终遵守：

```text
1. 最新源以 GitHub / 本地 UnrealSpecifiers 仓库当前文件为准。
2. 不要凭 AI 记忆编造 UE specifier 或 meta。
3. 旧知识默认 imported，不默认 verified。
4. AI 可以写 learning/inbox，但不能直接 promote。
5. 审查结果必须有 finding 文件。
6. 正式知识更新必须能追溯到 source_doc / finding / learning note。
7. 项目特例不能直接进入通用知识库。
8. 所有输出默认中文。
```
