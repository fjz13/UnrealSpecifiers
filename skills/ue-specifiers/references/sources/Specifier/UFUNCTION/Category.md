---
title: "Category"
id: "UFUNCTION.Category"
kind: "specifier"
symbol: "Category"
scope: "UFUNCTION"
category: "Category"
source_status: "verified_UE5.8"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "在蓝图的右键菜单中为该函数指定类别分组，可以嵌套多级"
usage: "UFUNCTION / Category"
---

# Category

## Decision Summary

- **Use when:** Blueprint-exposed 函数需要在节点菜单或详情中合理分组。
- **Do not use when:** 函数不是 Blueprint/editor 暴露 API。
- **Requires:** 分类字符串应短、稳定，并与项目 Blueprint API 分组一致。
- **Conflicts:** 不影响函数调用权限、纯/非纯、网络或编辑器执行行为。
- **Prefer instead:** C++-only helper 不需要 Category。

- **功能描述：** 在蓝图的右键菜单中为该函数指定类别分组，可以嵌套多级

- **元数据类型：** strings=“a|b|c”
- **引擎模块：** Editor
- **作用机制：** 在Meta中加入[Category](../../Meta/DetailsPanel/Category.md)
- **常用程度：** ★★★★★

在蓝图的右键菜单中为该函数指定类别分组。
## UE5.8 审计结论

UE5.8 UHT 源码仍注册并处理该 UFUNCTION 条目；本轮按 UE5.8 标记为已验证。

## 测试代码：

```cpp
UCLASS(Blueprintable, BlueprintType)
class INSIDER_API AMyFunction_Default :public AActor
{
public:
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = MyCategory)
	void MyFunc_WithCategory(){}
	UFUNCTION(BlueprintCallable)
	void MyFunc_Default(){}
};
```

## 蓝图中的展示：

