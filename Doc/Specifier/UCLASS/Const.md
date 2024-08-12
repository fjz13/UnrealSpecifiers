# Const

Type: bool
Feature: Blueprint
Description: 此类中的所有属性和函数都是const并且导出为const。此说明符由子类继承。
Example: UCLASS(Blueprintable,Const)
class INSIDER_API UMyClass_Const :public UObject
{
GENERATED_BODY()
public:
UPROPERTY(EditAnywhere,BlueprintReadWrite)
int32 MyProperty;
UFUNCTION(BlueprintCallable)
void MyFunc(){++MyProperty;}
};
EClassFlagsOperation: |=
EClassFlags: CLASS_Const (../../Flags/EClassFlags/CLASS_Const.md)
Status: Done

表示本类所有的属性和函数都是const的，只读不可写。继承的蓝图类也是如此。其实就是自动的给所有属性函数和子类上添加const的标志。注意只是在蓝图里检查，C++依然可以随意改变，遵循C++的规则。所以这个const是只给蓝图用的，在蓝图里检查。函数依然可以随便调用，只是没有属性的Set方法了，也不能改变了。

![http://static.zybuluo.com/fjz13/blzjnq4vglxf4cay0kwej6wt/image_1e0vdpjoj1qtbmkp14k12452382a.png](http://static.zybuluo.com/fjz13/blzjnq4vglxf4cay0kwej6wt/image_1e0vdpjoj1qtbmkp14k12452382a.png)

跟蓝图里打开这个开关设定的一样

![http://static.zybuluo.com/fjz13/ai90i5msz8e9oez2br1c5rtf/image_1e0vdu7q2jogmb71ag11cbj9kt37.png](http://static.zybuluo.com/fjz13/ai90i5msz8e9oez2br1c5rtf/image_1e0vdu7q2jogmb71ag11cbj9kt37.png)

![Untitled](Const/Untitled.png)