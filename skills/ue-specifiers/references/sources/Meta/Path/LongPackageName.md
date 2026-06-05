---
title: "LongPackageName"
id: "meta.LongPackageName"
kind: "meta"
symbol: "LongPackageName"
category: "Path"
source_status: "verified_UE5.8"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "使用UE的风格来选择Content以及子目录，或者把文件路径转换为长包名"
usage: "UPROPERTY"
---

# LongPackageName

## Decision Summary

- **Use when:** `LongPackageName` metadata 的 `UPROPERTY` 场景需要：使用UE的风格来选择Content以及子目录，或者把文件路径转换为长包名。
- **Do not use when:** 目标声明不属于 `UPROPERTY`，或该展示/编辑/节点行为不是代码契约的一部分。
- **Requires:** metadata key 名称、参数名和目标声明类型必须与 UE5.8 UHT/编辑器消费路径匹配。
- **Conflicts:** 不要把 metadata 当成 C++ 访问控制、持久化、网络复制或运行时校验，除非正文明确说明。
- **Prefer instead:** 常见组合先看 `constraints.index.md`；不确定宏上下文时先看 `ambiguous-symbols.index.md`。

- **功能描述：** 使用UE的风格来选择Content以及子目录，或者把文件路径转换为长包名。
- **使用位置：** UPROPERTY
- **引擎模块：** Path Property
- **元数据类型：** bool
- **限制类型：** FDirectoryPath，FFilePath
- **常用程度：** ★★★

LongPackageName可以同时用在FDirectoryPath和FFilePath，都限制选取范围在Content目录内。

用在FDirectoryPath上的时候，限制目录为Content或其子目录。

用在FFilePath的时候，限制选择范围为Content里的资产，最终把选取的文件路径转换为“/Game/ObjectPath”这种对象的路径名。
## UE5.8 审计结论

UE5.8 源码中仍能找到该 metadata 的声明、示例或消费路径；本轮按 UE5.8 标记为已验证。该条目多属于插件、编辑器或内部工作流，使用前应先确认目标模块是否启用。
