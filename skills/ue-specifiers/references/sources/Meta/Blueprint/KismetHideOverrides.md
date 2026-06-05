---
title: "KismetHideOverrides"
id: "meta.KismetHideOverrides"
kind: "meta"
symbol: "KismetHideOverrides"
category: "Blueprint"
source_status: "verified_UE5.8"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "不允许被覆盖的蓝图事件的列表"
usage: "UCLASS"
---

# KismetHideOverrides

## Decision Summary

- **Use when:** `KismetHideOverrides` metadata 的 `UCLASS` 场景需要：不允许被覆盖的蓝图事件的列表。
- **Do not use when:** 目标声明不属于 `UCLASS`，或该展示/编辑/节点行为不是代码契约的一部分。
- **Requires:** metadata key 名称、参数名和目标声明类型必须与 UE5.8 UHT/编辑器消费路径匹配。
- **Conflicts:** 不要把 metadata 当成 C++ 访问控制、持久化、网络复制或运行时校验，除非正文明确说明。
- **Prefer instead:** 常见组合先看 `constraints.index.md`；不确定宏上下文时先看 `ambiguous-symbols.index.md`。

- **功能描述：** 不允许被覆盖的蓝图事件的列表。
- **使用位置：** UCLASS
- **引擎模块：** Blueprint
- **元数据类型：** strings="a，b，c"

在源码中发现ALevelScriptActor上面定义了很多，用来阻止被覆盖。

## 样例：

```cpp
UCLASS(notplaceable, meta=(ChildCanTick, KismetHideOverrides = "ReceiveAnyDamage,ReceivePointDamage,ReceiveRadialDamage,ReceiveActorBeginOverlap,ReceiveActorEndOverlap,ReceiveHit,ReceiveDestroyed,ReceiveActorBeginCursorOver,ReceiveActorEndCursorOver,ReceiveActorOnClicked,ReceiveActorOnReleased,ReceiveActorOnInputTouchBegin,ReceiveActorOnInputTouchEnd,ReceiveActorOnInputTouchEnter,ReceiveActorOnInputTouchLeave"), HideCategories=(Collision,Rendering,Transformation), MinimalAPI)
class ALevelScriptActor : public AActor
{}
```

但是实际在LevelScriptActor的子类中依然可以覆盖该事件。有一些被隐藏的Event是其实通过HideCategories来做到的。因此该Meta其实并没有实现，如果要达到该效果，还是要通过HideFunctions或HideCategories来达成。


## 原理：

可以看到这里面的判断，并没有用到该Meta

```cpp
void SMyBlueprint::CollectAllActions(FGraphActionListBuilderBase& OutAllActions)
{
// Cache potentially overridable functions
UClass* ParentClass = BlueprintObj->SkeletonGeneratedClass ? BlueprintObj->SkeletonGeneratedClass->GetSuperClass() : *BlueprintObj->ParentClass;
for ( TFieldIterator<UFunction> FunctionIt(ParentClass, EFieldIteratorFlags::IncludeSuper); FunctionIt; ++FunctionIt )
{
	const UFunction* Function = *FunctionIt;
	const FName FunctionName = Function->GetFName();

	UClass *OuterClass = CastChecked<UClass>(Function->GetOuter());
	// ignore skeleton classes and convert them into their "authoritative" types so they
	// can be found in the graph
	if(UBlueprintGeneratedClass *GeneratedOuterClass = Cast<UBlueprintGeneratedClass>(OuterClass))
	{
		OuterClass = GeneratedOuterClass->GetAuthoritativeClass();
	}

	if (    UEdGraphSchema_K2::CanKismetOverrideFunction(Function)
		 && !OverridableFunctionNames.Contains(FunctionName)
		 && !ImplementedFunctionCache.Contains(FunctionName)
		 && !FObjectEditorUtils::IsFunctionHiddenFromClass(Function, ParentClass)
		 && !FBlueprintEditorUtils::FindOverrideForFunction(BlueprintObj, OuterClass, Function->GetFName())
		 && Blueprint->AllowFunctionOverride(Function)
	   )
	{
		FText FunctionTooltip = FText::FromString(UK2Node_CallFunction::GetDefaultTooltipForFunction(Function));
		FText FunctionDesc = K2Schema->GetFriendlySignatureName(Function);
		if ( FunctionDesc.IsEmpty() )
		{
			FunctionDesc = FText::FromString(Function->GetName());
		}

		if (Function->HasMetaData(FBlueprintMetadata::MD_DeprecatedFunction))
		{
			FunctionDesc = FBlueprintEditorUtils::GetDeprecatedMemberMenuItemName(FunctionDesc);
		}

		FText FunctionCategory = FObjectEditorUtils::GetCategoryText(Function);

		TSharedPtr<FEdGraphSchemaAction_K2Graph> NewFuncAction = MakeShareable(new FEdGraphSchemaAction_K2Graph(EEdGraphSchemaAction_K2Graph::Function, FunctionCategory, FunctionDesc, FunctionTooltip, 1, NodeSectionID::FUNCTION_OVERRIDABLE));
		NewFuncAction->FuncName = FunctionName;

		OverridableFunctionActions.Add(NewFuncAction);
		OverridableFunctionNames.Add(FunctionName);
	}
}
}
```

## 行为

UE5.8 class metadata；ObjectMacros 标注为禁止覆盖指定 Blueprint events 的列表。

## UE5.8 审计结论

- 状态：`verified_UE5.8`。
- 结论：已按 UE5.8 源码验证。
- 证据：
  - UE5.8 `ObjectMacros.h` metadata declaration/comment
  - UE5.8 `BlueprintGraph` metadata constants or node usage

## 常见误用

参数名、属性名或目标宏写错导致 metadata 被保留但没有对应编辑器/Blueprint 行为。
