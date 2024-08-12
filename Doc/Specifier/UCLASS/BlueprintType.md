# BlueprintType

Description: 可当做变量类型
Feature: Blueprint
Type: bool
MetaOperation: |=
Meta: BlueprintType (../../Meta/Meta/BlueprintType.md)
Status: Done
Sub-item: NotBlueprintType (NotBlueprintType.md)
Trait: Star

可当做变量类型，Blueprintable隐含也可当变量类型。关键是设置BlueprintType和NotBlueprintType这两个metadata

![Untitled](BlueprintType/Untitled.png)

```cpp
用UEdGraphSchema_K2::IsAllowableBlueprintVariableType来判断

const UClass* ParentClass = InClass;
while(ParentClass)
{
	// Climb up the class hierarchy and look for "BlueprintType" and "NotBlueprintType" to see if this class is allowed.
	if(ParentClass->GetBoolMetaData(FBlueprintMetadata::MD_AllowableBlueprintVariableType)
		|| ParentClass->HasMetaData(FBlueprintMetadata::MD_BlueprintSpawnableComponent))
	{
		return true;
	}
	else if(ParentClass->GetBoolMetaData(FBlueprintMetadata::MD_NotAllowableBlueprintVariableType))
	{
		return false;
	}
	ParentClass = ParentClass->GetSuperClass();
}
```