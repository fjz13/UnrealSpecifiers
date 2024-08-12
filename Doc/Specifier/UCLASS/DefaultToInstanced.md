# DefaultToInstanced

Type: bool
Feature: Behavior
Description: 指定该类的所有实例属性都默认是UPROPERTY(instanced)，即都默认创建新的实例，而不是对对象的引用。
EClassFlagsOperation: |=
EClassFlags: CLASS_DefaultToInstanced (../../Flags/EClassFlags/CLASS_DefaultToInstanced.md)
Status: Done

会继续造成Property的CPF_InstancedReference，也常常和EditInlineNew配合使用。UActorComponent本身就是带有DefaultToInstanced的。

```cpp
UCLASS(Blueprintable, DefaultToInstanced)
class INSIDER_API UMyClass_DefaultToInstanced :public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 MyProperty;
};

UCLASS(Blueprintable, DefaultToInstanced, EditInlineNew)
class INSIDER_API UMyClass_DefaultToInstanced_EditInlineNew :public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 MyProperty;
};

UCLASS(Blueprintable, BlueprintType)
class INSIDER_API UMyClass_DefaultToInstanced_Test :public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced, Category = InstancedProperty)
		UMyClass_DefaultToInstanced* MyObjectInstance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NormalProperty)
		UMyClass_DefaultToInstanced* MyObject;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NormalProperty)
		UMyClass_DefaultToInstanced_EditInlineNew* MyObjectInstanceEditInlineNew;
};
```

即使属性上没有标上Instance标记，也默认是Instance的

![Untitled](DefaultToInstanced/Untitled.png)