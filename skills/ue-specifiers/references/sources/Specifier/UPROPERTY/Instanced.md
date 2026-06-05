---
title: "Instanced"
id: "UPROPERTY.Instanced"
kind: "specifier"
symbol: "Instanced"
scope: "UPROPERTY"
category: "Instance"
source_status: "verified_UE5.8"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "指定对该对象属性的编辑赋值应该新创建一个实例并作为子对象，而不是寻找一个对象引用"
usage: "UPROPERTY / Instance"
---

# Instanced

## Decision Summary

- **Use when:** `UObject*` 属性需要拥有并内联保存一个子对象实例。
- **Do not use when:** 属性只是引用外部资产、类、Actor 或非拥有对象。
- **Requires:** 被实例化对象类通常需要 `EditInlineNew`，属性类型必须适合 UObject 子对象所有权。
- **Conflicts:** 与软引用/资产引用语义相反；不要用它表达资源选择。
- **Prefer instead:** 资产引用用 `TObjectPtr`/`TSoftObjectPtr` 加类型选择 metadata；组件默认子对象用 `CreateDefaultSubobject`。

- **功能描述：** 指定对该对象属性的编辑赋值应该新创建一个实例并作为子对象，而不是寻找一个对象引用。
- **元数据类型：** bool
- **引擎模块：** Instance
- **限制类型：** UObject*
- **作用机制：** 在PropertyFlags中加入CPF_PersistentInstance, CPF_ExportObject, CPF_InstancedReference，在Meta中加入[EditInline](../../Meta/DetailsPanel/EditInline.md)
- **常用程度：** ★★★

指定对该对象属性的编辑赋值应该新创建一个实例并作为子对象，而不是寻找一个对象引用。

- 单个属性上的Instanced和UCLASS上的DefaultToInstanced作用有点类似，区别是前者只作用于单个属性，后者作用于该类类型的所有属性。
- 常常和EditInlineNew一起使用，在细节面板上可以为对象属性新创建实例并编辑。
- Instanced隐含了EditInline and Export.

在Object*属性上设置值的时候，如果不标Instanced，则只能为其设置一个对象引用。而如果想在编辑器里为其真正的创建一个对象实例并赋予给这个属性，则需要加上Instanced标记。但光有Instanced还不够，这个Class还需要加上EditInlineNew，才能让该类出现在可新创建类实例的列表里。

当然，在C++里手动设置对象给这个属性的话还是都可以的。也要注意和UCLASS(DefaultToInstanced)区分，DefaultToInstanced是表明这个类的所有属性都默认的加上Instanced的意思，避免了对该类的所有属性每次都要手动设置。

## 行为

`Instanced` 用于 `UObject*` 类属性，表示该引用应作为 owning object 的 inline 子对象实例处理，而不是普通资产或外部对象引用。编辑器里常与目标类的 `EditInlineNew` 配合，让 Details Panel 可以新建并编辑内联对象。

## UE5.8 审计结论

在 UE5.8 UHT 源码 `UhtPropertyMemberSpecifiers.cs` 中，`InstancedSpecifier` 会设置 `EPropertyFlags.PersistentInstance | EPropertyFlags.ExportObject | EPropertyFlags.InstancedReference`，并加入 `EditInline` metadata。Hello 样例 `Property/Object/MyProperty_Instanced.h` 中 `ObjectInstanced` 的 flags 与这些标记对应。

## 常见误用

- `Instanced` 不会在 C++ 构造函数里自动创建对象；需要默认子对象或运行时对象时仍要显式创建。
- 只有属性标 `Instanced` 还不一定能在 Details Panel 新建目标类型；目标类通常还需要 `UCLASS(EditInlineNew)`。
- 不要用 `Instanced` 表示普通资产引用；资产引用通常使用 object pointer、soft reference 或 data asset 路径。

## 示例代码：

```cpp
UCLASS(Blueprintable, BlueprintType,editinlinenew)
class INSIDER_API UMyProperty_InstancedObject :public UDataAsset
{
public:
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 MyValue = 123;
};

UCLASS(Blueprintable, BlueprintType)
class INSIDER_API UMyProperty_Instanced :public UObject
{
public:
	GENERATED_BODY()
		UMyProperty_Instanced(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
public:
	//PropertyFlags:	CPF_Edit | CPF_BlueprintVisible | CPF_ExportObject | CPF_ZeroConstructor | CPF_InstancedReference | CPF_NoDestructor | CPF_PersistentInstance | CPF_HasGetValueTypeHash | CPF_NativeAccessSpecifierPublic
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced, Category = Behavior)
		UMyProperty_InstancedObject* ObjectInstanced;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Behavior)
		UMyProperty_InstancedObject* Object;
};
```

## 示例效果：

可见ObjectInstanced和Object弹出的编辑框是不同的。

