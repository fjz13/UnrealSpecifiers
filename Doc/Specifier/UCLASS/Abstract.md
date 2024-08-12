# Abstract

Type: bool
Feature: Blueprint
Description: Abstract 说明符会将类声明为“抽象基类”，阻止用户向关卡中添加此类的Actor。对于单独存在时没有意义的类，此说明符非常有用。例如，ATriggerBase基类是抽象类，而ATriggerBox子类不是抽象类，可以放置在关卡中。
EClassFlagsOperation: |=
EClassFlags: CLASS_Abstract (../../Flags/EClassFlags/CLASS_Abstract.md)
Status: Done
Trait: Star

指定此类为抽象基类。可被继承，但不可生成对象。一般是XXXBase基类。

![http://static.zybuluo.com/fjz13/cl0gzb009el2bzvxqx9zzt03/image_1e0vf76gdmh9kll84j13ip129j3k.png](http://static.zybuluo.com/fjz13/cl0gzb009el2bzvxqx9zzt03/image_1e0vf76gdmh9kll84j13ip129j3k.png)