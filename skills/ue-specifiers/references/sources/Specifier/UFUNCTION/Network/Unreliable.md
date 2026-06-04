---
title: "Unreliable"
id: "UFUNCTION.Unreliable"
kind: "specifier"
symbol: "Unreliable"
scope: "UFUNCTION"
category: "Network"
source_status: "imported_from_unreal_specifiers"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "指定一个RPC函数为“不可靠的”，当遇见网络错误时就会被丢弃。一般用在传播效果表现的函数上，就算漏掉也没有关系"
usage: "UFUNCTION / Network"
---

# Unreliable

- **功能描述：** 指定一个RPC函数为“不可靠的”，当遇见网络错误时就会被丢弃。一般用在传播效果表现的函数上，就算漏掉也没有关系。

- **元数据类型：** bool
- **引擎模块：** Network
- **常用程度：★★★★★**

指定一个RPC函数为“不可靠的”，当遇见网络错误时就会被丢弃。一般用在传播效果表现的函数上，就算漏掉也没有关系。