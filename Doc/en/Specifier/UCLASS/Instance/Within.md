# Within

- **Function description:** Specifies that an object must be created with a dependency on an instance of OuterClassName as its Outer.
- **Engine module:** Instance
- **Metadata type:** string="abc"
- **Action mechanism:** Stored in the XXX field of UClass* UClass::ClassWithin=XXX
- **Commonly used: ★★★**

Specifies that an object must depend on an instance of OuterClassName as its Outer when it is created.

Objects of this class cannot exist outside of an instance of OuterClassName. This implies that to instantiate an object of this class, an instance of OuterClassName must be provided as its Outer object.

This class is typically used as a sub-object in such scenarios.

## Sample Code:

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

## Example Results:

```cpp
//Error! Fatal error: Object MyClass_Within None created in Package instead of MyClass_Within_Outer
UMyClass_Within* obj=NewObject<UMyClass_Within>();

//Correct:
UMyClass_Within_Outer* objOuter = NewObject<UMyClass_Within_Outer>();
UMyClass_Within* obj=NewObject<UMyClass_Within>(objOuter);
```

## Principle:

The generated UClass field: UClass* ClassWithin will hold this information, and during creation, StaticAllocateObject will check (bCreatingCDO || !InOuter || InOuter->IsA(InClass->ClassWithin)). Hence, the Within object must be created first.

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

You can find many usages of Within by searching through the source code

UCLASS(Within=Engine, config=Engine, transient)
class ENGINE_API ULocalPlayer

UCLASS(Abstract, DefaultToInstanced, Within=UserWidget)
class UMG_API UUserWidgetExtension : public UObject
{