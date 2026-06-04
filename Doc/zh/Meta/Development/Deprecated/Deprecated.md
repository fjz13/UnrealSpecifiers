---
title: "Deprecated"
id: "meta.Development.Deprecated"
kind: "meta"
symbol: "Deprecated"
category: "Development"
source_status: "verified_UE5.8"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "指定该元素要废弃的引擎版本号"
usage: "Any"
---

# Deprecated

- **功能描述：** 指定该元素要废弃的引擎版本号。
- **使用位置：** Any
- **引擎模块：** Development
- **元数据类型：** string="abc"
- **常用程度：** ★

指定该元素要废弃的引擎版本号。

这个值只是单纯的在C++代码中记录一下信息，并不会真正的使得一个元素变成废弃。这个值也没有在别的地方UI使用和显示出来。

要废弃一个元素，还是要用别的标记，如**DeprecatedProperty，DeprecatedFunction等。**
## UE5.8 审计结论

UE5.8 源码中仍能找到该 metadata 的声明、示例或消费路径；本轮按 UE5.8 标记为已验证。该条目多属于插件、编辑器或内部工作流，使用前应先确认目标模块是否启用。
