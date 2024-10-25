# BindWidgetAnimOptional

- **功能描述：** 指定在C++类中该UWidgetAnimation属性可以要绑定到UMG下的某个动画，也可以不绑定。
- **使用位置：** UPROPERTY
- **引擎模块：** Widget Property
- **元数据类型：** bool
- **限制类型：** UWidget子类里UWidgetAnimation属性
- **关联项：** [BindWidgetAnim](../BindWidgetAnim/BindWidgetAnim.md)
- **常用程度：** ★★★

同BindWidgetOptional作用也类似，在不绑定的时候在编译结果里会有一个提示，而不是像BindWidget一样强制的错误。

![Untitled](Untitled.png)

自然的也说过不能像Widget一样，不加BindWidget就自动默认绑定。

因此用法上要嘛加BindWidgetAnim，要嘛加BindWidgetAnimOptional。