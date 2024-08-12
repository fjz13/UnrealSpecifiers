# Within

Type: string="abc"
Feature: Behavior
Description: 此类的对象无法在OuterClassName对象的实例之外存在。这意味着，要创建此类的对象，需要提供OuterClassName的一个实例作为其Outer对象。该类的对象不能脱开OuterClassName的对象当做Outer来存在。意味着在创建该类的时候必须提供一个OuterClassName的Outer object。
Example: Within=OuterClassName
Status: Done
Code: UClass* UClass::ClassWithin=XXX

指定对象创建的时候必须依赖于OuterClassName的对象作为Outer。

生成的UClass的字段：UClass* ClassWithin会保存这个信息，然后在创建的时候StaticAllocateObject会测试 check(bCreatingCDO || !InOuter || InOuter->IsA(InClass->ClassWithin))。因此需要先创建Within的对象。

一般是用来当做子对象来使用的。

```cpp
错误：
UMyClass_Within* obj=NewObject<UMyClass_Within>();

if ( (InFlags & (RF_ClassDefaultObject|RF_ArchetypeObject)) == 0 )
{
	if ( InOuter != NULL && !InOuter->IsA(InClass->ClassWithin) )
	{
		UE_LOG(LogUObjectGlobals, Fatal, TEXT("%s"), *FString::Printf( TEXT("Object %s %s created in %s instead of %s"), *InClass->GetName(), *InName.ToString(), *InOuter->GetClass()->GetName(), *InClass->ClassWithin->GetName()) );
		return true;
	}
}
Fatal error: Object MyClass_Within None created in Package instead of MyClass_Within_Outer

正确：
UMyClass_Within_Outer* objOuter = NewObject<UMyClass_Within_Outer>();
UMyClass_Within* obj=NewObject<UMyClass_Within>(objOuter);
```

在源码里可以搜索到很多Within的用法

UCLASS(Within=Engine, config=Engine, transient)
class ENGINE_API ULocalPlayer

UCLASS(Abstract, DefaultToInstanced, Within=UserWidget)
class UMG_API UUserWidgetExtension : public UObject
{