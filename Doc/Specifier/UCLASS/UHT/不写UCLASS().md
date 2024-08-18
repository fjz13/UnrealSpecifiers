# 不写UCLASS()

功能描述: 只是作为一个普通的C++对象，没有反射功能。
引擎模块: UHT
元数据类型: bool
Status: Done
常用程度: 1

只是作为一个普通的C++对象，没有反射功能。

一般情况继承自UObject的最少也会有一个UCLASS()，这样才有反射功能。但是注意，如果调用UMyClass_NoUCLASS::StaticClass()会返回基类UObject的Class，因为子类没有覆盖。因此也可以说本类是没有生成自己的UClass元数据对象。

```cpp
class INSIDER_API UMyClass_NoUCLASS :public UObject
{
	
};
```

UObject的Class默认的标记是：CLASS_Abstract | CLASS_MatchedSerializers | CLASS_Native | CLASS_TokenStreamAssembled | CLASS_Intrinsic | CLASS_Constructed。因此不能被NewObject生成对象。在手动去掉CLASS_Abstract后可以正常new，但是对象的名称依然是Object，显然这是因为使用的就是Object的Class。