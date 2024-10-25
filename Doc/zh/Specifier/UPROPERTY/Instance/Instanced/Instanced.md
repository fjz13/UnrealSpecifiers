# Instanced

- **功能描述：** 指定对该对象属性的编辑赋值应该新创建一个实例并作为子对象，而不是寻找一个对象引用。
- **元数据类型：** bool
- **引擎模块：** Instance
- **限制类型：** UObject*
- **作用机制：** 在PropertyFlags中加入[CPF_PersistentInstance](../../../../Flags/EPropertyFlags/CPF_PersistentInstance.md), [CPF_ExportObject](../../../../Flags/EPropertyFlags/CPF_ExportObject.md), [CPF_InstancedReference](../../../../Flags/EPropertyFlags/CPF_InstancedReference.md)，在Meta中加入[EditInline](../../../../Meta/DetailsPanel/EditInline/EditInline.md)
- **常用程度：** ★★★

指定对该对象属性的编辑赋值应该新创建一个实例并作为子对象，而不是寻找一个对象引用。

- 单个属性上的Instanced和UCLASS上的DefaultToInstanced作用有点类似，区别是前者只作用于单个属性，后者作用于该类类型的所有属性。
- 常常和EditInlineNew一起使用，在细节面板上可以为对象属性新创建实例并编辑。
- Instanced隐含了EditInline and Export.

在Object*属性上设置值的时候，如果不标Instanced，则只能为其设置一个对象引用。而如果想在编辑器里为其真正的创建一个对象实例并赋予给这个属性，则需要加上Instanced标记。但光有Instanced还不够，这个Class还需要加上EditInlineNew，才能让该类出现在可新创建类实例的列表里。

当然，在C++里手动设置对象给这个属性的话还是都可以的。也要注意和UCLASS(DefaultToInstanced)区分，DefaultToInstanced是表明这个类的所有属性都默认的加上Instanced的意思，避免了对该类的所有属性每次都要手动设置。

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

![Untitled](Untitled.png)