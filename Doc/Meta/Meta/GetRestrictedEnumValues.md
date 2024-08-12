# GetRestrictedEnumValues

Usage: UPROPERTY
Feature: Blueprint
Type: string="abc"
Description: 指定一个函数来指定枚举属性值的哪些枚举选项是禁用的
Example: meta=(GetRestrictedEnumValues="FuncName")
LimitedType: TArray<FString> FuncName() const;
Status: Linked
Group: Enum Property
Parent item: ValidEnumValues (ValidEnumValues.md)

Restricted和Invalid的区别是：

Invalid会隐藏掉该选项值

Restricted依然会显示该选项值，只是会灰调不可选。

指定的函数名字必须是一个UFUNCTION函数，这样才能通过名字找到该函数。