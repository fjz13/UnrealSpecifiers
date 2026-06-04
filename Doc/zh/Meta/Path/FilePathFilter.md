---
title: "FilePathFilter"
id: "meta.FilePathFilter"
kind: "meta"
symbol: "FilePathFilter"
category: "Path"
source_status: "verified_UE5.8"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "设定文件选择器的扩展名，规则符合系统对话框的格式规范，可以填写多个扩展名"
usage: "UPROPERTY"
---

# FilePathFilter

- **功能描述：** 设定文件选择器的扩展名，规则符合系统对话框的格式规范，可以填写多个扩展名。
- **使用位置：** UPROPERTY
- **引擎模块：** Path Property
- **元数据类型：** string="abc"
- **限制类型：** FFilePath
- **常用程度：** ★★★

一般常见的用法是”.umap”，“.uasset”之类的。但也可以支持采用“描述 | *.后缀名”的格式自己书写过滤方式，规则同windows系统选取规则一样，也可以同时写多个后缀名。
## UE5.8 审计结论

UE5.8 源码中仍能找到该 metadata 的声明、示例或消费路径；本轮按 UE5.8 标记为已验证。该条目多属于插件、编辑器或内部工作流，使用前应先确认目标模块是否启用。
