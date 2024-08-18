# ConversionRoot

功能描述: 在场景编辑器里允许Actor在自身以及子类之间做转换
引擎模块: Scene
元数据类型: bool
MetaOperation: |=
Meta: IsConversionRoot (../../Meta/Meta/IsConversionRoot.md)
Status: Done
常用程度: 1

一般是用在Actor上，在Actor转换的时候用来限制转换的级别。比如ASkeletalMeshActor，AStaticMeshActor等。

常常ComponentWrapperClass一起出现。

根据代码来说，meta中的IsConversionRoot会限制只传达到这一层，不继续往根上查找。

只有配有ConversionRoot的Actor才会允许Convert Actor，否则是禁用的。

示例代码：

```cpp
//(BlueprintType = true, IncludePath = Class/Trait/MyClass_ConversionRoot.h, IsBlueprintBase = true, IsConversionRoot = true, ModuleRelativePath = Class/Trait/MyClass_ConversionRoot.h)
UCLASS(Blueprintable,BlueprintType, ConversionRoot)
class INSIDER_API AMyActor_ConversionRoot :public AActor
{
	GENERATED_BODY()
};

```

示例效果：

在蓝图中创建其子类BP_ConversionRoot_Child1和BP_ConversionRoot_Child2。然后把BP_ConversionRoot_Child1拖放进场景里创建个Actor，也创建个普通的蓝图Actor作为对比。

![Untitled](ConversionRoot/Untitled.png)

在关卡中选择Child1，会允许ConvertActor，在ConverstionRoot的自身以及所有子类之间做转换。

![Untitled](ConversionRoot/Untitled%201.png)

如果是普通的Actor，因为没有定义ConversionRoot，则不能做转换。

![Untitled](ConversionRoot/Untitled%202.png)

原理：

在关卡中的Actor选择：关卡中选择一个Actor，然后DetailsPanel里会显示ConverActor属性栏，可以选择另外一个Actor来进行改变。
TSharedRef<SWidget> FActorDetails::MakeConvertMenu( const FSelectedActorInfo& SelectedActorInfo )
这个函数就是用来创建Select Type的Combo Button的菜单的。内部会调用CreateClassPickerConvertActorFilter：

```cpp
UClass* FActorDetails::GetConversionRoot( UClass* InCurrentClass ) const
{
	UClass* ParentClass = InCurrentClass;

	while(ParentClass)
	{
		if( ParentClass->GetBoolMetaData(FName(TEXT("IsConversionRoot"))) )
		{
			break;
		}
		ParentClass = ParentClass->GetSuperClass();
	}

	return ParentClass;
}

void FActorDetails::CreateClassPickerConvertActorFilter(const TWeakObjectPtr<AActor> ConvertActor, class FClassViewerInitializationOptions* ClassPickerOptions)
Filter->AllowedChildOfRelationship.Add(RootConversionClass);//限定这个基类以下的其他子类

```