---
title: "MinimalAPI"
id: "UINTERFACE.MinimalAPI"
kind: "specifier"
symbol: "MinimalAPI"
scope: "UINTERFACE"
category: "UHT"
source_status: "verified_UE5.8"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "指定该UInterface对象不导出到别的模块"
usage: "UINTERFACE / UHT"
---

# MinimalAPI

- **功能描述：**  指定该UInterface对象不导出到别的模块
- **元数据类型：** bool
- **引擎模块：** DllExport
- **常用程度：★**

可以参照UCLASS里的MinimalAPI的解释。

简单来说UInterface对象，只是作为接口的辅助对象，因此本身并没有什么可值得暴露出来的函数。因此源码里的大部分UInterface对象都被标记成了MinimalAPI，以加快编译同时隔绝别的模块使用。

```cpp
UINTERFACE(MinimalAPI, BlueprintType)
class USoundLibraryProviderInterface : public UInterface
{
	GENERATED_BODY()
};
```
## UE5.8 审计结论

UE5.8 UHT 或宏路径仍保留该条目；本轮按 UE5.8 标记为已验证。P3 中不少条目属于引擎内部、NoExportTypes 或插件专用用法，不建议普通项目代码直接套用。
