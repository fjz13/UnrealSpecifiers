# Meta Animation Graph And RigVM

> Category source index. Use targeted search in this file, then open only the listed `Doc`.
> Resolve `Doc` relative to the nearest preceding `Doc root`; each `Doc root` is relative to `references/sources/`.

## Meta - AnimationGraph

> Doc root: `Meta/AnimationGraph/`

| ID | Summary | Usage | Doc |
|---|---|---|---|
| `AllowedParamType` | // Sets a parameter's value in the supplied scope. | UFUNCTION | `AllowedParamType.md` |
| `AlwaysAsPin` | 在动画蓝图中使得动画节点的某个属性总是暴露出来成为引脚 | UPROPERTY | `AlwaysAsPin.md` |
| `AnimBlueprintFunction` | 标明是动画蓝图里的内部纯存根函数，只在动画蓝图编译时设置 | UFUNCTION | `AnimBlueprintFunction.md` |
| `AnimGetter` | 指定UAnimInstance及子类的该函数成为一个AnimGetter函数 | UFUNCTION | `AnimGetter.md` |
| `AnimNotifyBoneName` | 使得UAnimNotify或UAnimNotifyState下的FName属性作为BoneName的作用 | UPROPERTY | `AnimNotifyBoneName.md` |
| `AnimNotifyExpand` | 使得UAnimNotify或UAnimNotifyState下的属性直接展开到细节面板里 | UPROPERTY | `AnimNotifyExpand.md` |
| `AnimationGraph.CustomWidget` | 也可以放在属性上 | UFUNCTION, UPROPERTY | `CustomWidget.md` |
| `BlueprintCompilerGeneratedDefaults` | 指定该属性的值是编译器生成的，因此在编译后无需复制，可以加速一些编译性能 | UPROPERTY | `BlueprintCompilerGeneratedDefaults.md` |
| `CustomizeProperty` | 使用在FAnimNode的成员属性上，告诉编辑器不要为它生成默认Details面板控件，后续会在DetailsCustomization里自定义创建相应的编辑控件 | UPROPERTY | `CustomizeProperty.md` |
| `FoldProperty` | 在动画蓝图中使得动画节点的某个属性成为FoldProperty | UPROPERTY | `FoldProperty.md` |
| `GetterContext` | 继续限定AnimGetter函数在哪个地方才可以使用，如果不填，则默认都可以用 | UFUNCTION | `GetterContext.md` |
| `NeverAsPin` | 在动画蓝图中使得动画节点的某个属性总是不暴露出来成为引脚 | UPROPERTY | `NeverAsPin.md` |
| `OnEvaluate` | UE5.8 AnimBlueprintExtension_Base.cpp 仍读取 OnEvaluate metadata，但同一代码路径会输出 “OnEvaluate meta data is deprecated” 警告；因此该条目保留 | UPROPERTY | `OnEvaluate.md` |
| `PinShownByDefault` | 在动画蓝图中使得动画节点的某个属性一开始就暴露出来成为引脚，但也可以改变 | UPROPERTY | `PinShownByDefault.md` |



## Meta - RigVM

> Doc root: `Meta/RigVM/`

| ID | Summary | Usage | Doc |
|---|---|---|---|
| `Abstract` | 标识该FRigUnit为抽象类，不用实现Execute | USTRUCT | `Abstract.md` |
| `Aggregate` | 指定FRigUnit里的属性引脚为可扩展连续二元运算符的运算数 | UPROPERTY | `Aggregate.md` |
| `Constant` | 标识一个属性成为一个常量的引脚 | UPROPERTY, USTRUCT | `Constant.md` |
| `DetailsOnly` | 指定FRigUnit下的该属性只在细节面板中显示 | UPROPERTY | `DetailsOnly.md` |
| `ExpandByDefault` | 把FRigUnit里的属性引脚默认展开 | UPROPERTY | `ExpandByDefault.md` |
| `Icon` | 设定FRigUnit蓝图节点的图标 | USTRUCT | `Icon.md` |
| `Input` | 指定FRigUnit下的该属性作为输入引脚 | UPROPERTY | `Input.md` |
| `MenuDescSuffix` | 标识FRigUnit在蓝图右键菜单项的名字后缀 | USTRUCT | `MenuDescSuffix.md` |
| `NodeColor` | 指定FRigUnit蓝图节点的RGB颜色值 | USTRUCT | `NodeColor.md` |
| `Output` | 指定FRigUnit下的该属性作为输出引脚 | UPROPERTY | `Output.md` |
| `RigVM.CustomWidget` | 指定该FRigUnit里的属性要用自定义的控件来编辑 | UPROPERTY | `CustomWidget.md` |
| `RigVM.Deprecated` | 标识该FRigUnit为弃用状态，不在蓝图右键菜单中显示 | USTRUCT | `Deprecated.md` |
| `RigVM.Hidden` | 指定FRigUnit下的该属性隐藏 | UPROPERTY | `Hidden.md` |
| `RigVM.Keywords` | 设定FRigUnit蓝图节点在右键菜单中的关键字，方便输入查找 | USTRUCT | `Keywords.md` |
| `RigVMTypeAllowed` | 指定一个UENUM可以在FRigUnit的UEnum*属性中被选择 | UENUM | `RigVMTypeAllowed.md` |
| `TemplateName` | 指定该FRigUnit成为一个泛型模板节点 | USTRUCT | `TemplateName.md` |
| `Varying` | ScriptStruct /Script/RigVM.RigVMFunction_GetDeltaTime | UCLASS | `Varying.md` |
| `Visible` | 指定FRigUnit下的该属性为常量引脚，无法连接变量 | UPROPERTY | `Visible.md` |




