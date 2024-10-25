# DeterminesOutputType

- **Function description:** Specifies a parameter type as a reference type for the function to dynamically adjust the output parameter type
- **Use location:** UFUNCTION
- **Engine module:** Blueprint
- **Metadata type:** string="abc"
- **Restricted type:** Class or Object pointer type, or container type
- **Related items:** [DynamicOutputParam](../DynamicOutputParam.md)
- **Frequency:** ★★★

Specifies a parameter type as the type of the function's output parameter.

Assuming a function prototype as follows:

```cpp
	UFUNCTION(BlueprintCallable, meta = (DeterminesOutputType = "A",DynamicOutputParam="P1,P2"))
	TypeR MyFunc(TypeA A,Type1 P1,Type2 P2,Type3 P3);
```

The value of DeterminesOutputType specifies a function parameter name, A. The type of TypeA must be a Class or Object, typically TSubClassOf<XXX> or XXX*, but it can also be TArray<XXX*>, or it may point to a property within a parameter structure, such as Args_ActorClassType. TSoftObjectPtr<XXX> is also acceptable, pointing to a subclass Asset object, which can then correspondingly change the base class Asset* output.

The term "output parameters" includes both return values and function output parameters. Therefore, TypeR, P1, and P2 in the function prototype above are all output parameters. For the types of output parameters to change dynamically, the types of TypeR, Type1, and Type2 must also be Class or Object types, and the type actually selected for parameter A on the blueprint node must be a subclass of the output parameter type to allow for automatic conversion.

If there are no P1 and P2, and the return value is considered as TypeR, there is no need to specify DynamicOutputParam, and the return value can be automatically treated as a dynamic output parameter by default. Otherwise, DynamicOutputParam must be manually specified to indicate which function parameters support dynamic typing.

## Test code:

```cpp

UCLASS(Blueprintable, BlueprintType)
class INSIDER_API AMyAnimalActor :public AActor
{
public:
	GENERATED_BODY()
};

UCLASS(Blueprintable, BlueprintType)
class INSIDER_API AMyCatActor :public AMyAnimalActor
{
public:
	GENERATED_BODY()
};

UCLASS(Blueprintable, BlueprintType)
class INSIDER_API AMyDogActor :public AMyAnimalActor
{
public:
	GENERATED_BODY()
};

USTRUCT(BlueprintType)
struct FMyOutputTypeArgs
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 MyInt = 1;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<AMyAnimalActor> ActorClassType;
};

UCLASS(Blueprintable, BlueprintType)
class INSIDER_API UMyFunctionLibrary_OutputTypeTest :public UBlueprintFunctionLibrary
{
public:
	GENERATED_BODY()
public:
	//class
	UFUNCTION(BlueprintCallable, meta = (DeterminesOutputType = "ActorClassType"))
	static TArray<AActor*> MyGetAnimals(TSubclassOf<AMyAnimalActor> ActorClassType);

	//have to add DynamicOutputParam
	UFUNCTION(BlueprintCallable, meta = (DeterminesOutputType = "ActorClassType", DynamicOutputParam = "OutActors"))
	static void MyGetAnimalsOut(TSubclassOf<AMyAnimalActor> ActorClassType, TArray<AActor*>& OutActors);

	//have to add DynamicOutputParam
	UFUNCTION(BlueprintCallable, meta = (DeterminesOutputType = "ActorClassType", DynamicOutputParam = "FirstOutActor,OutActors"))
	static void MyGetAnimalsOut2(TSubclassOf<AMyAnimalActor> ActorClassType, AActor*& FirstOutActor, TArray<AActor*>& OutActors);

	//object
	UFUNCTION(BlueprintCallable, meta = (DeterminesOutputType = "ExampleActor"))
	static TArray<AActor*> MyGetAnimalsWithActor(AMyAnimalActor* ExampleActor);

	UFUNCTION(BlueprintCallable, meta = (DeterminesOutputType = "ExampleActorArray"))
	static TArray<AActor*> MyGetAnimalsWithActorArray(TArray<AMyAnimalActor*> ExampleActorArray);

	//struct property
	UFUNCTION(BlueprintCallable, meta = (DeterminesOutputType = "Args_ActorClassType"))
	static TArray<AActor*> MyGetAnimalsWithStructProperty(const FMyOutputTypeArgs& Args);
};

```

## Blueprint effect:

In an example where the return value is used as an output parameter, note that the return value type actually becomes TArray<AMyCatActor*>.

![pic_a](pic_a.png)

You can also add DynamicOutputParam to specify output parameters as dynamic type parameters:

![pic_b](pic_b.png)

DynamicOutputParam can specify multiple parameters

![pic_c](pic_c.png)

The parameter type of DeterminesOutputType can also be an Object or a container of Objects

![pic_d](pic_d.png)

The parameter of DeterminesOutputType can even be an attribute within a structure, but this only applies when the structure is SplitStruct, because only then do the structure's attributes become function Pins, allowing for name comparison with DeterminesOutputType. In such cases, it should be written as "A_B" rather than "A.B".

![pic_e](pic_e.png)

## Principle:

The mechanism of DeterminesOutputType operates by searching for a Pin on the function blueprint node based on the specified name. This Pin must be of Class or Object type (or a container), as these types support pointer conversion. The Pin is used to specify values through various TypePickers, such as ClassPicker or ObjectPicker, on the blueprint node. Subsequently, based on the value selected by the TypePicker, the type of the parameter (or return parameter) specified by DynamicOutputParam can be dynamically adjusted. The actual line that changes the type is:

Pin->PinType.PinSubCategoryObject = PickedClass;

```cpp
void FDynamicOutputHelper::ConformOutputType() const
{
	if (IsTypePickerPin(MutatingPin))
	{
		UClass* PickedClass = GetPinClass(MutatingPin);
		UK2Node_CallFunction* FuncNode = GetFunctionNode();

		// See if there is any dynamic output pins
		TArray<UEdGraphPin*> DynamicPins;
		GetDynamicOutPins(FuncNode, DynamicPins);

		// Set the pins class
		for (UEdGraphPin* Pin : DynamicPins)
		{
			if (ensure(Pin != nullptr))
		{
					Pin->PinType.PinSubCategoryObject = PickedClass;//Set the subtype for each dynamic parameter
			}
		}
	}
}
```