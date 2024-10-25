# EarlyAccessPreview

- **Function Description:** Indicates that this class is an early preview version, which is more refined than a beta version but is not yet at the product level.
- **Engine Module:** Development
- **Metadata Type:** bool
- **作用机制:** 在Meta中添加[DevelopmentStatus](../../../../Meta/Development/DevelopmentStatus.md)，将类标记为Early Access
- **Common Usage:** ★★★

Indicates that this class is an early preview version, which is more complete than a trial version but still not at the product level.

This tag will append { "DevelopmentStatus", "EarlyAccess" } to the class's metadata.

## Sample Code:

```cpp
//(BlueprintType = true, DevelopmentStatus = EarlyAccess, IncludePath = Class/Display/MyClass_Deprecated.h, IsBlueprintBase = true, ModuleRelativePath = Class/Display/MyClass_Deprecated.h)
UCLASS(Blueprintable, EarlyAccessPreview)
class INSIDER_API UMyClass_EarlyAccessPreview :public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 MyProperty;
	UFUNCTION(BlueprintCallable)
		void MyFunc() {}
};
```

## Example Results:

![Untitled](Untitled.png)