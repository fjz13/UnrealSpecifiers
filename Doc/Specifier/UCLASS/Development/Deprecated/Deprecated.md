# Deprecated

功能描述: 标明该类已经弃用。
引擎模块: Development
元数据类型: bool
EClassFlagsOperation: |=
EClassFlags: CLASS_Deprecated (../../Flags/EClassFlags/CLASS_Deprecated.md), CLASS_NotPlaceable (../../Flags/EClassFlags/CLASS_NotPlaceable.md)
Meta: DeprecationMessage (../../Meta/Meta/DeprecationMessage.md), DeprecatedProperty (../../Meta/Meta/DeprecatedProperty.md)
Status: Done
常用程度: 3

标明该类已经弃用。

弃用会导致：不可被创建，不可被序列化保存，在继承列表里被过滤掉。此说明符子类会继承下来，标明子类也是废弃的。标上Deprecated 的类需要在类名前加上UDEPRECATED_的显眼前缀，但是类名不会变，Actor加ADEPRECATED_，UObject加UDEPRECATED_。ClassFLags里会标上CLASS_Deprecated和CLASS_NotPlaceable。注意还是可以正常NewObject使用的。而SpawnActor会失败，报错： failed because class %s is deprecated。EditInline也都会被禁止。

示例代码：

```cpp
UCLASS(Blueprintable)
class INSIDER_API UMyClass_Deprecated :public UObject
{
	GENERATED_BODY()
};
//改为：
UCLASS(Blueprintable, Deprecated)
class INSIDER_API UDEPRECATED_MyClass_Deprecated :public UObject
{
	GENERATED_BODY()
};
```

示例效果1：

依然可以NewObject。

![Untitled](Deprecated/Untitled.png)

示例代码2：

但要注意这个是UE的标记。源码里还看见很多UE_DEPRECATED宏的使用，则是在VS编译器级别的标记，会根据使用引用情况在编译的步骤中生成警告。

```cpp
UCLASS(Blueprintable, BlueprintType)
class INSIDER_API UMyClass_Deprecated_Test :public UObject
{
	GENERATED_BODY()
public:

		UE_DEPRECATED(5.2, "MyClass_Deprecated has been deprecated, please remove it.")
		UDEPRECATED_MyClass_Deprecated* MyProperty_Deprecated;

		UE_DEPRECATED(5.2, "MyIntProperty has been deprecated, please remove it.")
		UPROPERTY(EditAnywhere, BlueprintReadWrite,meta=(DeprecatedProperty, DeprecationMessage = "MyIntProperty has been deprecated."))
		int MyIntProperty;

		UE_DEPRECATED(5.2, "MyClass_Deprecated has been deprecated, please remove it.")
		void MyFunc(UDEPRECATED_MyClass_Deprecated* obj){}

		UFUNCTION(BlueprintCallable, meta = (DeprecatedProperty, DeprecationMessage="MyVoidFunc has been deprecated."))
		void MyVoidFunc(){}
};

UCLASS(Blueprintable, BlueprintType)
class INSIDER_API UMyClass_Deprecated_Usage :public UObject
{
	GENERATED_BODY()
public:

	void MyFunc()
	{
		UMyClass_Deprecated_Test* obj=NewObject<UMyClass_Deprecated_Test>();
		UDEPRECATED_MyClass_Deprecated* obj2 = NewObject<UDEPRECATED_MyClass_Deprecated>();
		obj->MyProperty_Deprecated= obj2;
		obj->MyProperty_Deprecated->MyFunc(); 

		obj->MyIntProperty++;
		obj->MyFunc(obj2);
		obj->MyVoidFunc();
	}
};

编译警告：
warning C4996: 'UMyClass_Deprecated_Test::MyProperty_Deprecated': MyClass_Deprecated has been deprecated, please remove it. Please update your code to the new API before upgrading to the next release, otherwise your project will no longer compile.
warning C4996: 'UMyClass_Deprecated_Test::MyProperty_Deprecated': MyClass_Deprecated has been deprecated, please remove it. Please update your code to the new API before upgrading to the next release, otherwise your project will no longer compile.
warning C4996: 'UMyClass_Deprecated_Test::MyIntProperty': MyIntProperty has been deprecated, please remove it. Please update your code to the new API before upgrading to the next release, otherwise your project will no longer compile.
warning C4996: 'UMyClass_Deprecated_Test::MyFunc': MyClass_Deprecated has been deprecated, please remove it. Please update your code to the new API before upgrading to the next release, otherwise your project will no longer compile.
注意如果没有UE_DEPRECATED标记，则不会生成编译警告。

UPROPERTY(EditAnywhere, BlueprintReadWrite)	int MyInt2Property_DEPRECATED;
会触发：
warning : Member variable declaration: Deprecated property 'MyInt2Property_DEPRECATED' should not be marked as blueprint visible without having a BlueprintGetter
warning : Member variable declaration: Deprecated property 'MyInt2Property_DEPRECATED' should not be marked as blueprint writable without having a BlueprintSetter
warning : Member variable declaration: Deprecated property 'MyInt2Property_DEPRECATED' should not be marked as visible or editable
因此只能改成：
UPROPERTY()	int MyInt2Property_DEPRECATED;
```

示例效果2：

属性和函数上加上Deprecated标记后，会在BP编译的时候生成警告。注意函数是先有一个正常的函数，在BP里连接完成之后再在C++里标记DeprecatedFunction才会生成警告，否则已经Deprecated的函数是无法再在BP里调用的。

![Untitled](Deprecated/Untitled%201.png)

原理：

源码中有众多CLASS_Deprecated的判断，比如SpawnActor：

```cpp
AActor* UWorld::SpawnActor( UClass* Class, FTransform const* UserTransformPtr, const FActorSpawnParameters& SpawnParameters )
{
	if( Class->HasAnyClassFlags(CLASS_Deprecated) )
	{
		UE_LOG(LogSpawn, Warning, TEXT("SpawnActor failed because class %s is deprecated"), *Class->GetName() );
		return NULL;
	}
}
```