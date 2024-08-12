# MustBeLevelActor

Usage: UPROPERTY
Feature: Blueprint
Group: Object Property
Type: bool
Status: NotWorked

意思是这个必须是场景里的Actor，而不是LevelScriptActor的意思。

触发时机在用箭头选择的当前选中actor的时候。

源码中遇见：

```cpp
if (FObjectPropertyBase* ObjectProperty = CastField<FObjectPropertyBase>(Property))
{
	ObjectClass = ObjectProperty->PropertyClass;
	bMustBeLevelActor = ObjectProperty->GetOwnerProperty()->GetBoolMetaData(TEXT("MustBeLevelActor"));
	RequiredInterface = ObjectProperty->GetOwnerProperty()->GetClassMetaData(TEXT("MustImplement"));
}
```