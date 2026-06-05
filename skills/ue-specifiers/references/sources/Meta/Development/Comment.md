---
title: "Comment"
id: "meta.Comment"
kind: "meta"
symbol: "Comment"
category: "Development"
source_status: "verified_UE5.8"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "用来记录注释的内容"
usage: "Any"
---

# Comment

## Decision Summary

- **Use when:** `Comment` metadata 的 `Any` 场景需要：用来记录注释的内容。
- **Do not use when:** 目标声明不属于 `Any`，或该展示/编辑/节点行为不是代码契约的一部分。
- **Requires:** metadata key 名称、参数名和目标声明类型必须与 UE5.8 UHT/编辑器消费路径匹配。
- **Conflicts:** 不要把 metadata 当成 C++ 访问控制、持久化、网络复制或运行时校验，除非正文明确说明。
- **Prefer instead:** 常见组合先看 `constraints.index.md`；不确定宏上下文时先看 `ambiguous-symbols.index.md`。

- **功能描述：** 用来记录注释的内容
- **使用位置：** Any
- **引擎模块：** Development
- **元数据类型：** string="abc"
- **常用程度：** ★★★

Comment跟ToolTip不同，后者是用户鼠标悬停上的提示，前者只是简单的代码中的注释的记录。但是一般我们在代码里写上的注释，会自动也加到ToolTip 上，因此我们往往也会看到UI界面上的提示。

但如果不想要ToolTip，想只有Comment，则也可以自己手动在meta里添加。
## UE5.8 审计结论

UE5.8 源码中仍能找到该 metadata 的声明、示例或消费路径；本轮按 UE5.8 标记为已验证。

## 测试代码：

```cpp
//(BlueprintType = true, Comment = //This is a comment on class, IncludePath = Property/Development/MyProperty_Development.h, ModuleRelativePath = Property/Development/MyProperty_Development.h, ToolTip = This is a comment on class)

//This is a comment on class
UCLASS(BlueprintType)
class INSIDER_API UMyProperty_Development :public UObject
{
	GENERATED_BODY()
public:
	//(Comment = //This is a comment on function, ModuleRelativePath = Property/Development/MyProperty_Development.h, ToolTip = This is a comment on function)

	//This is a comment on function
	UFUNCTION(BlueprintCallable)
	int32 MyFunc(FString str){return 0;}

	//	(Category = MyProperty_Development, Comment = //This is a comment on property, ModuleRelativePath = Property/Development/MyProperty_Development.h, ToolTip = This is a comment on property)

	//This is a comment on property
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MyProperty = 123;

	//(Category = MyProperty_Development, Comment = This is my other property., ModuleRelativePath = Property/Development/MyProperty_Development.h)

	UPROPERTY(EditAnywhere, BlueprintReadWrite,meta=(Comment="This is my other property."))
	int32 MyProperty_WithComment = 123;
};

```

## 测试结果：

MyProperty_WithComment是单独只加的Comment，就没有了鼠标悬停效果。

