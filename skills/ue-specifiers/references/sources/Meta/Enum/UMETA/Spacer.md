---
title: "Spacer"
id: "meta.Spacer"
kind: "meta"
symbol: "Spacer"
scope: "UMETA"
category: "Enum"
source_status: "imported_from_unreal_specifiers"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "隐藏UENUM的某个值"
usage: "UENUM::UMETA"
---

# Spacer

- **功能描述：** 隐藏UENUM的某个值
- **使用位置：** UENUM::UMETA
- **引擎模块：** Enum Property
- **元数据类型：** bool
- **限制类型：** UENUM
- **常用程度：** ★★★★★

Spacer和Hidden的功能大体是一致的。唯一区别是Spacer在蓝图里==的时候还是会显示出来。

因此还是建议如果要隐藏枚举值，还是要尽量都用Hidden。

![Untitled](Hidden/Untitled.png)

其他示例代码见Hidden