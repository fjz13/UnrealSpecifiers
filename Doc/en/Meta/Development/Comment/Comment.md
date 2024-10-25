# Comment

- **Function description:** Used to record comment content
- **Placement:** Anywhere
- **Engine module:** Development
- **Metadata type:** string="abc"
- **Commonly used:** ★★★

Comment differs from ToolTip; the latter is a hover prompt for users, while the former is simply a record of comments within the code. However, comments written in the code are typically added automatically to the ToolTip, which is why we often see prompts in the UI interface.

But if ToolTips are not desired and only Comments are wanted, they can be added manually in the meta section.

## Test Code:

```cpp
//(BlueprintType = true, Comment = //This is a comment on class, IncludePath = Property/Development/MyProperty_Development.h, ModuleRelativePath = Property/Development/MyProperty_Development.h, ToolTip = This is a comment on class)

//This is a comment on class
UCLASS(BlueprintType)
class INSIDER_API UMyProperty_Development :public UObject
{
	GENERATED_BODY()
public:
	//(Comment = //This is a comment on function, ModuleRelativePath = Property/Development/MyProperty_Development.h, ToolTip = This is a comment on function)

	//This is a comment on function
	UFUNCTION(BlueprintCallable)
	int32 MyFunc(FString str){return 0;}

	//	(Category = MyProperty_Development, Comment = //This is a comment on property, ModuleRelativePath = Property/Development/MyProperty_Development.h, ToolTip = This is a comment on property)

	//This is a comment on property
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MyProperty = 123;

	//(Category = MyProperty_Development, Comment = This is my other property., ModuleRelativePath = Property/Development/MyProperty_Development.h)

	UPROPERTY(EditAnywhere, BlueprintReadWrite,meta=(Comment="This is my other property."))
	int32 MyProperty_WithComment = 123;
};

```

## Test Results:

MyProperty_WithComment has only the Comment added, and thus lacks the mouse hover effect.

![Comment](Comment.gif)