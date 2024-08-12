# InvalidEnumValues

Description: 指定枚举属性值上不可选的枚举值选项，用以排除一些选项
Usage: UPROPERTY
Feature: Blueprint
Group: Enum Property
Type: strings="a，b，c"
LimitedType: 枚举属性值
Status: Linked
Parent item: ValidEnumValues (ValidEnumValues.md)

如果同时指定了InvalidEnumValues和ValidEnumValues，且里面的值有重叠，则还是以InvalidEnumValues的为准：这项枚举值就是非法的。