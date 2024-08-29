# Abstract

- **功能描述：** 指定此类为抽象基类。可被继承，但不可生成对象。
- **引擎模块：** Blueprint
- **元数据类型：** bool
- **作用机制：** 在ClassFlags中添加[CLASS_Abstract](../../../../Flags/EClassFlags/CLASS_Abstract.md)
- **常用程度：** ★★★★★

指定此类为抽象基类。可被继承，但不可生成对象。

一般是用在XXXBase基类。

## 示例代码：

```cpp
/*
	ClassFlags:	CLASS_Abstract | CLASS_MatchedSerializers | CLASS_Native | CLASS_RequiredAPI | CLASS_TokenStreamAssembled | CLASS_Intrinsic | CLASS_Constructed
*/
UCLASS(Blueprintable, abstract)
class INSIDER_API UMyClass_Abstract :public UObject
{
	GENERATED_BODY()
};

//测试语句：
UMyClass_Abstract* obj=NewObject<UMyClass_Abstract>();
```

## 示例效果：

在蓝图中的ConstructObject不会出现该类。同时在C++中NewObject也会报错。

![image](image.png)

## 原理：

在NewObject的时候会进行Abstract的判断。

```cpp
bool StaticAllocateObjectErrorTests( const UClass* InClass, UObject* InOuter, FName InName, EObjectFlags InFlags)
{
	// Validation checks.
	if( !InClass )
	{
		UE_LOG(LogUObjectGlobals, Fatal, TEXT("Empty class for object %s"), *InName.ToString() );
		return true;
	}

	// for abstract classes that are being loaded NOT in the editor we want to error.  If they are in the editor we do not want to have an error
	if (FScopedAllowAbstractClassAllocation::IsDisallowedAbstractClass(InClass, InFlags))
	{
		if ( GIsEditor )
		{
			const FString ErrorMsg = FString::Printf(TEXT("Class which was marked abstract was trying to be loaded in Outer %s.  It will be nulled out on save. %s %s"), *GetPathNameSafe(InOuter), *InName.ToString(), *InClass->GetName());
			// if we are trying instantiate an abstract class in the editor we'll warn the user that it will be nulled out on save
			UE_LOG(LogUObjectGlobals, Warning, TEXT("%s"), *ErrorMsg);
			ensureMsgf(false, TEXT("%s"), *ErrorMsg);
		}
		else
		{
			UE_LOG(LogUObjectGlobals, Fatal, TEXT("%s"), *FString::Printf( TEXT("Can't create object %s in Outer %s: class %s is abstract"), *InName.ToString(), *GetPathNameSafe(InOuter), *InClass->GetName()));
			return true;
		}
	}
	}
	
	bool FScopedAllowAbstractClassAllocation::IsDisallowedAbstractClass(const UClass* InClass, EObjectFlags InFlags)
{
	if (((InFlags& RF_ClassDefaultObject) == 0) && InClass->HasAnyClassFlags(CLASS_Abstract))
	{
		if (AllowAbstractCount == 0)
		{
			return true;
		}
	}

	return false;
}
```