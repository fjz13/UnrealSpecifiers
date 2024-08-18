# Spacer

功能描述: 隐藏UENUM的某个值
使用位置: UENUM::UMETA
Feature: Blueprint
引擎模块: Enum Property
元数据类型: bool
限制类型: UENUM
Status: Linked
常用程度: 5

Spacer和Hidden的功能大体是一致的。唯一区别是Spacer在蓝图里==的时候还是会显示出来。

因此还是建议如果要隐藏枚举值，还是要尽量都用Hidden。

![Untitled](Hidden/Untitled.png)

其他示例代码见Hidden