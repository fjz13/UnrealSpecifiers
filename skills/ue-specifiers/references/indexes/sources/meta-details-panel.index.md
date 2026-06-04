# Meta Details Panel

> Category source index. Use targeted search in this file, then open only the listed `Doc`.
> Resolve `Doc` relative to the nearest preceding `Doc root`; each `Doc root` is relative to `references/sources/`.

## Meta - DetailsPanel

> Doc root: `Meta/DetailsPanel/`

| ID | Summary | Usage | Doc |
|---|---|---|---|
| `AdvancedClassDisplay` | 指定该类型的变量在高级显示里显示 | UCLASS | `AdvancedClassDisplay.md` |
| `AllowEditInlineCustomization` | 允许EditInline的对象属性可以自定义属性细节面板来编辑该对象内的数据 | UPROPERTY | `AllowEditInlineCustomization.md` |
| `AutoCollapseCategories` | 指定类内部的属性目录自动折叠起来 | UCLASS | `AutoCollapseCategories.md` |
| `AutoExpandCategories` | 指定类内部的属性目录自动展开起来 | UCLASS | `AutoExpandCategories.md` |
| `Category` | 指定属性在细节面板中的分类 | UFUNCTION, UPROPERTY | `Category.md` |
| `ClassGroupNames` | 指定ClassGroup的名字 | UCLASS | `ClassGroupNames.md` |
| `DeprecatedNode` | 用于BehaviorTreeNode或EnvQueryNode，说明该类已废弃，在编辑器中红色错误展示并有错误ToolTip提示 | UCLASS | `DeprecatedNode.md` |
| `DisplayAfter` | 使本属性在指定的属性之后显示 | UPROPERTY | `DisplayAfter.md` |
| `DisplayPriority` | 指定本属性在细节面板的显示顺序优先级，越小的优先级越高 | UPROPERTY | `DisplayPriority.md` |
| `EditCondition` | 给一个属性指定另外一个属性或者表达式来作为是否可编辑的条件 | UPROPERTY | `EditCondition.md` |
| `EditConditionHides` | 在已经有EditCondition的情况下，指定该属性在EditCondition不满足的情况下隐藏起来 | UPROPERTY | `EditConditionHides.md` |
| `EditInline` | 为对象属性创建一个实例，并作为子对象 | UPROPERTY | `EditInline.md` |
| `ForceInlineRow` | 强制TMap属性里的结构key和其他Value合并到同一行来显示 | UPROPERTY | `ForceInlineRow.md` |
| `HideBehind` | 只在指定的属性为true或不为空的时候本属性才显示 | UPROPERTY | `HideBehind.md` |
| `HideCategories` | 隐藏的类别 | UCLASS | `HideCategories.md` |
| `HideEditConditionToggle` | 用在使用EditCondition的属性上，表示该属性不想要其EditCondition用到的属性被隐藏起来 | UPROPERTY | `HideEditConditionToggle.md` |
| `HideInDetailPanel` | 在Actor的事件面板里隐藏该动态多播委托属性 | UPROPERTY | `HideInDetailPanel.md` |
| `IgnoreCategoryKeywordsInSubclasses` | 用于让一个类的首个子类忽略所有继承的 ShowCategories 和 HideCategories 说明符 | UCLASS | `IgnoreCategoryKeywordsInSubclasses.md` |
| `InlineEditConditionToggle` | 使这个bool属性在被用作EditCondition的时候内联到对方的属性行里成为一个单选框，而不是自己成为一个编辑行 | UPROPERTY | `InlineEditConditionToggle.md` |
| `MaxPropertyDepth` | 指定对象或结构在细节面板里展开的层数 | UPROPERTY | `MaxPropertyDepth.md` |
| `NoEditInline` | Object properties pointing to an UObject instance whos class is marked editinline will not show their properties inli... | UPROPERTY | `NoEditInline.md` |
| `NoResetToDefault` | 禁用和隐藏属性在细节面板上的“重置”功能 | UPROPERTY | `NoResetToDefault.md` |
| `PrioritizeCategories` | 把指定的属性目录优先显示在前面 | UCLASS | `PrioritizeCategories.md` |
| `ReapplyCondition` | // Properties that have a ReapplyCondition should be disabled behind the specified property when in reapply mode | UPROPERTY | `ReapplyCondition.md` |
| `ShowCategories` | 显示类别 | UCLASS | `ShowCategories.md` |
| `UsesHierarchy` | 说明类使用层级数据。用于实例化“细节”面板中的层级编辑功能 | UCLASS | `UsesHierarchy.md` |
| `bShowOnlyWhenTrue` | 旧 Details 条件显示 metadata。UE5.8 新代码通常应优先使用 EditCondition/EditConditionHides | UPROPERTY | `bShowOnlyWhenTrue.md` |


## Meta - Container

> Doc root: `Meta/Container/`

| ID | Summary | Usage | Doc |
|---|---|---|---|
| `ArraySizeEnum` | 为固定数组提供一个枚举，使得数组元素按照枚举值来作为索引和显示 | UPROPERTY | `ArraySizeEnum.md` |
| `EditFixedOrder` | 使数组的元素无法通过拖拽来重新排序 | UPROPERTY | `EditFixedOrder.md` |
| `NoElementDuplicate` | 去除TArray属性里数据项的Duplicate菜单项按钮 | UPROPERTY | `NoElementDuplicate.md` |
| `ReadOnlyKeys` | 使TMap属性的Key不能编辑 | UPROPERTY | `ReadOnlyKeys.md` |
| `TitleProperty` | 指定结构数组里的结构成员属性内容来作为结构数组元素的显示标题 | UPROPERTY | `TitleProperty.md` |


## Meta - Numeric

> Doc root: `Meta/Numeric/`

| ID | Summary | Usage | Doc |
|---|---|---|---|
| `AllowPreserveRatio` | 在细节面板上为FVector属性添加一个比率锁 | UPROPERTY | `AllowPreserveRatio.md` |
| `ArrayClamp` | 限定整数属性的值必须在指定数组的合法下标范围内，[0,ArrayClamp.Size()-1] | UPROPERTY | `ArrayClamp.md` |
| `ClampMax` | 指定数字输入框实际接受的最大值 | UPROPERTY | `ClampMax.md` |
| `ClampMin` | 指定数字输入框实际接受的最小值 | UPROPERTY | `ClampMin.md` |
| `ColorGradingMode` | 使得一个FVector4属性成为颜色显示 | UPROPERTY | `ColorGradingMode.md` |
| `CtrlMultiplier` | 指定数字输入框在Ctrl按下时鼠标轮滚动和鼠标拖动改变值的倍率 | UPROPERTY | `CtrlMultiplier.md` |
| `Delta` | 设定数字输入框值改变的幅度为Delta的倍数 | UPROPERTY | `Delta.md` |
| `ForceUnits` | 固定设定属性值的单位保持不变，不根据数值动态调整显示单位 | UPROPERTY | `ForceUnits.md` |
| `HideAlphaChannel` | 使FColor或FLinearColor属性在编辑的时候隐藏Alpha通道 | UPROPERTY | `HideAlphaChannel.md` |
| `InlineColorPicker` | 使FColor或FLinearColor属性在编辑的时候直接内联一个颜色选择器 | UPROPERTY | `InlineColorPicker.md` |
| `LinearDeltaSensitivity` | 在设定Delta后，进一步设定数字输入框变成线性改变以及改变的敏感度（值越大越不敏感） | UPROPERTY | `LinearDeltaSensitivity.md` |
| `Multiple` | 指定数字的值必须是Mutliple提供的值的整数倍 | UPROPERTY | `Multiple.md` |
| `NoSpinbox` | 使数值属性禁止默认的拖放和滚轮的UI编辑功能，数值属性包括int系列以及float系列 | UPROPERTY | `NoSpinbox.md` |
| `ShiftMultiplier` | 指定数字输入框在Shift按下时鼠标轮滚动和鼠标拖动改变值的倍率 | UPROPERTY | `ShiftMultiplier.md` |
| `ShowNormalize` | 使得FVector变量在细节面板出现一个正规化的按钮 | UPROPERTY | `ShowNormalize.md` |
| `SliderExponent` | 指定数字输入框上滚动条拖动的变化指数分布 | UPROPERTY | `SliderExponent.md` |
| `SupportDynamicSliderMaxValue` | 支持数字输入框上滚动条的最大范围值在Alt按下时被动态改变 | UPROPERTY | `SupportDynamicSliderMaxValue.md` |
| `SupportDynamicSliderMinValue` | 支持数字输入框上滚动条的最小范围值在Alt按下时被动态改变 | UPROPERTY | `SupportDynamicSliderMinValue.md` |
| `UIMax` | 指定数字输入框上滚动条拖动的最大范围值 | UPROPERTY | `UIMax.md` |
| `UIMin` | 指定数字输入框上滚动条拖动的最小范围值 | UPROPERTY | `UIMin.md` |
| `Units` | 设定属性值的单位，支持实时根据数值不同动态改变显示的单位 | UPROPERTY | `Units.md` |
| `WheelStep` | 指定数字输入框上鼠标轮上下滚动产生的变化值 | UPROPERTY | `WheelStep.md` |
| `sRGB` | 使FColor或FLinearColor属性在编辑的时候采用sRGB方式 | UPROPERTY | `sRGB.md` |



