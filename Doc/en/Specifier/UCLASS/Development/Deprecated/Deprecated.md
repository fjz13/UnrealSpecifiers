# Deprecated

- **Function description:** Indicates that this class is deprecated.
- **Engine module:** Development
- **Metadata type:** bool
- **Mechanism of action:** Add [CLASS_Deprecated](../../../../Flags/EClassFlags/CLASS_Deprecated.md) and [CLASS_NotPlaceable](../../../../Flags/EClassFlags/CLASS_NotPlaceable.md) to ClassFlags, and add [DeprecationMessage](../../../../Meta/Development/DeprecationMessage.md) and [DeprecatedProperty](../../../../Meta/Development/DeprecatedProperty/DeprecatedProperty.md) to Meta
- **Commonly used:** ★★★

Indicates that this class is deprecated.

* Classes will be filtered out of the inheritance list.

## Sample Code 1:

```cpp
UCLASS(Blueprintable)
class INSIDER_API UMyClass_Deprecated :public UObject
{
	GENERATED_BODY()
};
//Change to:
UCLASS(Blueprintable, Deprecated)
class INSIDER_API UDEPRECATED_MyClass_Deprecated :public UObject
{
	GENERATED_BODY()
};
```

## Example Effect 1:

NewObject can still be used.

![Untitled](Untitled.png)

## Sample Code 2:

However, note that this is a UE marking. In the source code, you may see many uses of the UE_DEPRECATED macro, which is a VS compiler-level marking that generates warnings during the compilation process based on usage references.

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

## Example Effect 2:

When attributes and functions are marked with Deprecated, warnings will be generated during BP compilation. Note that the function must first be a normal function, and after connections are completed in BP, marking DeprecatedFunction in C++ will generate a warning. Otherwise, a deprecated function cannot be called in BP.

![Untitled](Untitled%201.png)

## Principle:

In the source code, there are numerous judgments for CLASS_Deprecated, such as in SpawnActor:

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