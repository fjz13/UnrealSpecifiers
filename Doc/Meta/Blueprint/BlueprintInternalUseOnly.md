# BlueprintInternalUseOnly

功能描述: 标明该元素是作为蓝图系统的内部调用或使用，不暴露出来在用户层面直接定义或使用。
使用位置: UFUNCTION, USTRUCT
Feature: Blueprint
引擎模块: Blueprint
元数据类型: bool
Status: Linked
Related Meta: BlueprintType (BlueprintType.md), BlueprintInternalUseOnlyHierarchical (BlueprintInternalUseOnlyHierarchical.md)
Related to UFUNCTION: BlueprintInternalUseOnly (../../Specifier/UFUNCTION/BlueprintInternalUseOnly.md)
Related to USTRUCT: BlueprintInternalUseOnly (../../Specifier/USTRUCT/BlueprintInternalUseOnly.md)
常用程度: 3

也可以用在USTRUCT上，标明该结构不可用来定义新BP变量，但可作为别的类的成员变量暴露和变量传递。

用在UFUNCTION上时：此函数是一个内部实现细节，用于实现另一个函数或节点。其从未直接在蓝图图表中公开。