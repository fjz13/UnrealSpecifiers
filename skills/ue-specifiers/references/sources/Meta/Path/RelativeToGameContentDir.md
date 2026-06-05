---
title: "RelativeToGameContentDir"
id: "meta.RelativeToGameContentDir"
kind: "meta"
symbol: "RelativeToGameContentDir"
category: "Path"
source_status: "verified_UE5.8"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "使得系统目录选择对话框的结果为相对Content的相对路径"
usage: "UPROPERTY"
---

# RelativeToGameContentDir

## Decision Summary

- **Use when:** `RelativeToGameContentDir` metadata 的 `UPROPERTY` 场景需要：使得系统目录选择对话框的结果为相对Content的相对路径。
- **Do not use when:** 目标声明不属于 `UPROPERTY`，或该展示/编辑/节点行为不是代码契约的一部分。
- **Requires:** metadata key 名称、参数名和目标声明类型必须与 UE5.8 UHT/编辑器消费路径匹配。
- **Conflicts:** 不要把 metadata 当成 C++ 访问控制、持久化、网络复制或运行时校验，除非正文明确说明。
- **Prefer instead:** 常见组合先看 `constraints.index.md`；不确定宏上下文时先看 `ambiguous-symbols.index.md`。

- **功能描述：** 使得系统目录选择对话框的结果为相对Content的相对路径。
- **使用位置：** UPROPERTY
- **引擎模块：** Path Property
- **元数据类型：** bool
- **限制类型：** FDirectoryPath
- **关联项：** [ContentDir](ContentDir.md)

限制目录选择的结果必须是Conent目录或其子目录，否则会弹出报错信息。转换的逻辑为把左侧的Content路径裁切掉。

```cpp
Directory.RightChopInline(AbsoluteGameContentDir.Len(), EAllowShrinking::No);
```
## UE5.8 审计结论

UE5.8 源码中仍能找到该 metadata 的声明、示例或消费路径；本轮按 UE5.8 标记为已验证。该条目多属于插件、编辑器或内部工作流，使用前应先确认目标模块是否启用。
