# Keywords

- **功能描述：** 设定FRigUnit蓝图节点在右键菜单中的关键字，方便输入查找。
- **使用位置：** USTRUCT
- **引擎模块：** RigVMStruct
- **元数据类型：** strings="a，b，c"
- **限制类型：** FRigUnit
- **常用程度：** ★★★

设定FRigUnit蓝图节点在右键菜单中的关键字，方便输入查找。

同Function上的Keywords有一样的作用。

## 测试代码：

```cpp
USTRUCT(meta = (DisplayName = "MyRigKeywords",Keywords="MyKey,OtherWord"))
struct INSIDER_API FRigUnit_MyRigKeywords: public FRigUnit
{
	GENERATED_BODY()

	RIGVM_METHOD()
		virtual void Execute() override;
public:
	UPROPERTY(meta = (Input))
	float MyFloat_Input = 123.f;

	UPROPERTY(meta = (Output))
	float MyFloat_Output = 123.f;
};

```

## 测试效果：

在输入Keywords中的字符的时候，也可以找到该节点。

![Untitled](Untitled.png)

## 原理：

```cpp
URigVMEdGraphUnitNodeSpawner* URigVMEdGraphUnitNodeSpawner::CreateFromStruct(UScriptStruct* InStruct, const FName& InMethodName, const FText& InMenuDesc, const FText& InCategory, const FText& InTooltip)
{
	FString KeywordsMetadata, TemplateNameMetadata;
	InStruct->GetStringMetaDataHierarchical(FRigVMStruct::KeywordsMetaName, &KeywordsMetadata);
	if(!TemplateNameMetadata.IsEmpty())
	{
		if(KeywordsMetadata.IsEmpty())
		{
			KeywordsMetadata = TemplateNameMetadata;
		}
		else
		{
			KeywordsMetadata = KeywordsMetadata + TEXT(",") + TemplateNameMetadata;
		}
	}
	MenuSignature.Keywords = FText::FromString(KeywordsMetadata);

}
```