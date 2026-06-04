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
