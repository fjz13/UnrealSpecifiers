# UnrealSpecifiers | UE5标识符详解

- **作者：** 大钊
- **文档版本：** 1.1
- **修订日期：** 2024/10/23
- **适用引擎版本：** UE5.4 文档为主；`ue-specifiers` Agent Skill 已按 UE5.8 进行本地审计和路由优化
- **GitHub地址：** https://github.com/fjz13/UnrealSpecifiers
- **知乎地址：** https://www.zhihu.com/people/fjz13
- **邮箱：** fjz13@live.cn
- **版权声明：** 本文档和示例工程作为开源免费阅读学习使用，版权所有归于作者（大钊），其他人不得用于商业用途。

大家好，我是大钊。有感于虚幻社区内经常有人会提问UE中标识符以及各种meta的使用，也不满足于虚幻官方文档对每个标识符解释的匮乏，因此特整理了此文档。包括100多个标识符和300多个meta的详解。本文档库持续维护中。

一般情况下，建议在GitHub上或者clone下来，查看各种md文件文档，这样有更好的目录划分以及链接跳转。网络不畅的也可以查看pdf版本电子书。在文档的开头有各个标识符的整体表格，方便你简单一览所有标识符的作用。然后对特定的标识符，请善用搜索功能查找。

文档必然有各种缺漏错误不足之处，欢迎提交PR或与我反馈联系，让虚幻社区更多人受益。

## 配套资料：

- 这是我在**Unreal Fest Shanghai 2024**上的演讲：[UE5(标识符, meta=(详解, 史上最全)) | 大钊 Epic Games 虚幻社区经理](https://www.bilibili.com/video/BV1152LYrECW/)
- 以及我在知乎上的介绍文章：[UE5标识符详解 | 史上最全](https://zhuanlan.zhihu.com/p/717920216)(大钊)

## Agent Skill 试用

本仓库现在包含一个通用 Agent Skill：[skills/ue-specifiers](skills/ue-specifiers)。它不是把文档简单复制给模型，而是把 UE C++ 反射声明写法整理成“写代码时先用的路由和约束”，可供支持 Agent Skills 的客户端使用，例如 Codex 或 Claude Code。

- `SKILL.md`：指导 AI 编码 agent 在编写、修改、审查 UE C++ 反射声明时，优先选择最小且正确的 specifier/meta 组合。
- `references/indexes/common.index.md`：高频标识符快速入口，按原文档中的 `常用程度` 星级生成。
- `references/indexes/constraints.index.md`：组合场景约束入口，例如 Blueprint 暴露、Details Panel、Config、SaveGame、Replication/RPC、Instanced、UMG、Type Picker、Latent、CustomThunk、Async Action、Material、Script/Python 等。
- `references/indexes/ambiguous-symbols.index.md`：处理 `Category`、`BlueprintType`、`Config`、`DisplayName`、`Transient` 等多上下文重名项。
- `references/sources/`：每个标识符/meta 的规整化 source detail，优先看 `Decision Summary`。
- `tools/validate.ps1`：验证 skill 索引、source 数量、内部链接和路由一致性。

最近一次改造重点：

- 将 skill 的目标从“查询问答”调整为“辅助 AI 编码 agent 写 UE C++ 代码时正确使用 UCLASS/USTRUCT/UENUM/UINTERFACE/UPROPERTY/UFUNCTION/UPARAM/UMETA/meta”。
- 按 UE5.8 源码、UHT/BlueprintGraph/PropertyEditor 消费路径和 `Hello` 项目中的 `Insider` 样例进行 audit。
- 将组合风险集中到 `constraints.index.md`，让 agent 在写代码前先看到关键 caveat，而不是直接打开大量 source detail。
- 删除与最终 skill 使用无关的配图，保留轻量索引和可按需加载的 source detail。
- 增加本地验证脚本，并用 UE5.8 `HelloEditor Win64 Development` build 做过 smoke test。

### 安装到本地 skills 目录

不同客户端的默认 skills 目录可能不同，常见位置如下：

- Codex：`~/.agents/skills`
- Claude Code：`~/.claude/skills`

在本仓库根目录执行下面的 PowerShell 示例即可复制：

```powershell
$repoRoot = Resolve-Path .
$skillsRoot = Join-Path $HOME ".agents\skills"  # Codex
# $skillsRoot = Join-Path $HOME ".claude\skills" # Claude Code
New-Item -ItemType Directory -Force $skillsRoot | Out-Null
Copy-Item -Recurse -Force (Join-Path $repoRoot "skills\ue-specifiers") $skillsRoot
```

复制后建议重新打开一个 agent 会话，让 skills 列表刷新。新会话里如果能看到 `ue-specifiers`，就可以直接试用。

### 验证 skill 文件

```powershell
cd <repo-root>
.\skills\ue-specifiers\tools\validate.ps1
```

预期输出应包含：

```text
ue-specifiers validation passed.
source docs: 447
constraint rows: 65
missing internal markdown links: 0
```

### 用 Hello 项目做 UE5.8 smoke test

本仓库提供了 `bat` 下的本地验证 wrapper。使用前可按你的本机路径设置：

```bat
set UESPEC_UE_ROOT=<path-to-UE_5.8>
set UESPEC_HELLO_ROOT=<path-to-Hello-project-root>
bat\build-hello.bat
```

`Insider` 是样例代码集合，不是 automation test 集锦。它更适合用来对照具体 specifier/meta 的 C++ 声明和编辑器表现。

### 建议试用 prompt

在新的 agent 会话里可以这样试：

```text
Use ue-specifiers. 帮我写一个 UE5.8 UActorComponent，要求能在 Blueprint Add Component 面板中添加，但不要给不必要的 BlueprintReadWrite。
```

```text
Use ue-specifiers. 检查这个 UFUNCTION 的 CustomThunk / CustomStructureParam 写法是否缺少必要的 thunk 实现。
```

```text
Use ue-specifiers. 帮我设计一个 FDataTableRowHandle 属性，只允许选择某个 row struct，并说明应该用哪个 meta。
```

## 目录内容介绍

- 文档阅读请从 [Doc/zh/Main.md](Doc/zh/Main.md) 开始，内部开始划分表格以进行分类。
- Project目录包含所配套的示例代码工程：Hello。内含C++代码和蓝图代码资源。
- Tools目录包含生成pdf电子版的相应步骤和脚本。



---

# UE5 Specifiers Detailed Explanation

- **Author:** Jack Fu
- **Document version:** 1.1
- **Revision Date:** 2024/10/23
- **Applicable engine version:** UE5.4 documentation; the `ue-specifiers` Agent Skill has been audited and routed for UE5.8 local usage.
- **GitHub:** https://github.com/fjz13/UnrealSpecifiers
- **Zhihu:** https://www.zhihu.com/people/fjz13
- **Email:** fjz13@live.cn
- **Copyright statement:** This document and the sample project are provided as open-source material for free reading and learning. All rights are reserved by the author (Jack Fu), and no one else is authorized to use it for commercial purposes.
- **Warning: The English version of this document is translated by AI, which may lead to POOR QUALITY or INCORRECT INFORMATION, please read with CAUTION!"**

Greetings everyone, I am Jack Fu. Inspired by the frequent questions within the Unreal Engine community about specifiers and the use of various metas, and dissatisfied with the insufficient explanations provided in the official Unreal Engine documentation, I have compiled this document. It includes detailed explanations for over 100 specifiers and more than 300 metas. This document is continuously being maintained.

For the best experience, it is recommended to view the various markdown files on GitHub or clone them to benefit from the organized directory structure and linked navigation. For those with limited internet access, a PDF version of the e-book is also available. At the beginning of the document, there is a comprehensive table of specifiers, allowing for a quick overview of their functions. For specific specifiers, please utilize the search function to locate them.

The document is bound to have its share of omissions, errors, and inadequacies. I welcome pull requests or feedback to help improve this resource and benefit the wider Unreal Engine community.

## Supporting Materials: 

- This is my presentation at **Unreal Fest Shanghai 2024**: [UE5 (Specifiers, meta=(Detailed Explanation, Most Comprehensive Ever)) | Jack Fu, Epic Games Unreal Community Manager](https://www.bilibili.com/video/BV1152LYrECW/) 
-  And my introductory article on Zhihu: [UE5 Specifiers Detailed Explanation | Most Comprehensive Ever](https://zhuanlan.zhihu.com/p/717920216)(Jack Fu)

## Agent Skill Preview

This repository now includes a general Agent Skill at [skills/ue-specifiers](skills/ue-specifiers). It is designed for UE C++ code authoring, not only reference lookup. The skill routes the agent through compact indexes first, especially `constraints.index.md`, before opening detailed source docs.

To try it locally, copy the skill into your agent's skills root and start a new session. Common defaults are `~/.agents/skills` for Codex and `~/.claude/skills` for Claude Code.

```powershell
$repoRoot = Resolve-Path .
$skillsRoot = Join-Path $HOME ".agents\skills"  # Codex
# $skillsRoot = Join-Path $HOME ".claude\skills" # Claude Code
New-Item -ItemType Directory -Force $skillsRoot | Out-Null
Copy-Item -Recurse -Force (Join-Path $repoRoot "skills\ue-specifiers") $skillsRoot
```

Validate the skill files:

```powershell
cd <repo-root>
.\skills\ue-specifiers\tools\validate.ps1
```

For the UE5.8 Hello sample project smoke build:

```bat
bat\build-hello.bat
```

Example prompt:

```text
Use ue-specifiers. Review this UE5.8 UPROPERTY/UFUNCTION declaration and suggest the minimal correct specifiers and meta.
```



## Table of Contents Introduction 

- Please start reading the document from [Doc/en/Main.md](Doc/en/Main.md), where tables are used for categorization.
- The Project directory contains the accompanying example code project: **Hello**. It includes C++ code and Blueprint code resources. 
- The Tools directory contains the steps and scripts for generating the PDF electronic version.
