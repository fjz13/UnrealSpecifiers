# Within

- **功能描述：**  指定对象创建的时候必须依赖于OuterClassName的对象作为Outer。
- **引擎模块：** Instance
- **元数据类型：** string="abc"
- **作用机制：** 保存在UClass* UClass::ClassWithin=XXX的XXX中
- **常用程度：★★★**

指定对象创建的时候必须依赖于OuterClassName的对象作为Outer。

此类的对象无法在OuterClassName对象的实例之外存在。这意味着，要创建此类的对象，需要提供OuterClassName的一个实例作为其Outer对象。

本类在这种情况一般是用来当做子对象来使用的。

## 示例代码：

```cpp
UCLASS(Within= MyClass_Within_Outer)
class INSIDER_API UMyClass_Within :public UObject
{
	GENERATED_BODY()
};

UCLASS()
class INSIDER_API UMyClass_Within_Outer :public UObject
{
	GENERATED_BODY()
public:
};


```

## 示例结果：

```cpp
//错误！Fatal error: Object MyClass_Within None created in Package instead of MyClass_Within_Outer
UMyClass_Within* obj=NewObject<UMyClass_Within>();

//正确：
UMyClass_Within_Outer* objOuter = NewObject<UMyClass_Within_Outer>();
UMyClass_Within* obj=NewObject<UMyClass_Within>(objOuter);
```

## 原理：

生成的UClass的字段：UClass* ClassWithin会保存这个信息，然后在创建的时候StaticAllocateObject会测试 check(bCreatingCDO || !InOuter || InOuter->IsA(InClass->ClassWithin))。因此需要先创建Within的对象。

```cpp
bool StaticAllocateObjectErrorTests( const UClass* InClass, UObject* InOuter, FName InName, EObjectFlags InFlags)
{
		if ( (InFlags & (RF_ClassDefaultObject|RF_ArchetypeObject)) == 0 )
		{
			if ( InOuter != NULL && !InOuter->IsA(InClass->ClassWithin) )
			{
				UE_LOG(LogUObjectGlobals, Fatal, TEXT("%s"), *FString::Printf( TEXT("Object %s %s created in %s instead of %s"), *InClass->GetName(), *InName.ToString(), *InOuter->GetClass()->GetName(), *InClass->ClassWithin->GetName()) );
				return true;
			}
		}
}
```

在源码里可以搜索到很多Within的用法

UCLASS(Within=Engine, config=Engine, transient)
class ENGINE_API ULocalPlayer

UCLASS(Abstract, DefaultToInstanced, Within=UserWidget)
class UMG_API UUserWidgetExtension : public UObject
{