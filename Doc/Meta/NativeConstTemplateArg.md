# NativeConstTemplateArg

Description: 指定该属性是一个const的模板参数。
Usage: UPROPERTY
Feature: UHT
Group: UHT
Type: bool
Status: OnlyInternal

指定该属性是一个const的模板参数。

在源码里并没有找到使用的地方。只有在UHT中用到。

在UHT中查看主要是UhtArrayProperty和UhtObjectPropertyBase，UhtOptionalProperty。