# Meta Editor UI Actor Component Widget

> Category source index. Use targeted search in this file, then open only the listed `Doc`.
> Resolve `Doc` relative to the nearest preceding `Doc root`; each `Doc root` is relative to `references/sources/`.

## Meta - Actor

> Doc root: `Meta/Actor/`

| ID | Summary | Usage | Doc |
|---|---|---|---|
| `ChildCanTick` | 标记允许其蓝图子类可以接受响应Tick事件 | UCLASS | `ChildCanTick.md` |
| `ChildCannotTick` | 用于Actor或ActorComponent子类，标记允许其蓝图子类不可以接受响应Tick事件，哪怕父类可以Tick | UCLASS | `ChildCannotTick.md` |


## Meta - Component

> Doc root: `Meta/Component/`

| ID | Summary | Usage | Doc |
|---|---|---|---|
| `AllowAnyActor` | 用在ComponentReference属性上，在UseComponentPicker的情况下使得组件选取器扩大到场景里其他Actor下的其他组件 | UPROPERTY | `AllowAnyActor.md` |
| `BlueprintSpawnableComponent` | 允许该组件出现在Actor蓝图里Add组件的面板里 | UCLASS | `BlueprintSpawnableComponent.md` |
| `UseComponentPicker` | 用在ComponentReference属性上，使得选取器的列表里展示出Actor属下的Component以便选择 | UPROPERTY | `UseComponentPicker.md` |


## Meta - Scene

> Doc root: `Meta/Scene/`

| ID | Summary | Usage | Doc |
|---|---|---|---|
| `AllowedLocators` | 用来给Sequencer定位可绑定的对象 | UPROPERTY | `AllowedLocators.md` |
| `MakeEditWidget` | 使FVector和FTranform在场景编辑器里出现一个可移动的控件 | UPROPERTY | `MakeEditWidget.md` |
| `ValidateWidgetUsing` | 提供一个函数来验证当前属性值是否合法 | UPROPERTY | `ValidateWidgetUsing.md` |


## Meta - String

> Doc root: `Meta/String/`

| ID | Summary | Usage | Doc |
|---|---|---|---|
| `AllowedCharacters` | 只允许文本框里可以输入这些字符 | UPROPERTY | `AllowedCharacters.md` |
| `GetKeyOptions` | 为TMap里的FName/FString作为Key提供细节面板里选项框的选项值 | UPROPERTY | `GetKeyOptions.md` |
| `GetOptions` | 指定一个外部类的函数提供选项给FName或FString属性在细节面板中下拉选项框提供值列表 | UPARAM, UPROPERTY | `GetOptions.md` |
| `GetValueOptions` | 为TMap里的FName/FString作Value提供细节面板里选项框的选项值 | UPROPERTY | `GetValueOptions.md` |
| `MaxLength` | 在文本编辑框里限制文本的最大长度 | UPROPERTY | `MaxLength.md` |
| `MultiLine` | 使得文本属性编辑框支持换行 | UPROPERTY | `MultiLine.md` |
| `PasswordField` | 使得文本属性显示为密码框 | UPROPERTY | `PasswordField.md` |
| `PropertyValidator` | 用名字指定一个UFUNCTION函数来进行文本的验证 | UPROPERTY | `PropertyValidator.md` |


## Meta - Widget

> Doc root: `Meta/Widget/`

| ID | Summary | Usage | Doc |
|---|---|---|---|
| `BindWidget` | 指定在C++类中该Widget属性一定要绑定到UMG的某个同名控件 | UPROPERTY | `BindWidget.md` |
| `BindWidgetAnim` | 指定在C++类中该UWidgetAnimation属性一定要绑定到UMG下的某个动画 | UPROPERTY | `BindWidgetAnim.md` |
| `BindWidgetAnimOptional` | 指定在C++类中该UWidgetAnimation属性可以要绑定到UMG下的某个动画，也可以不绑定 | UPROPERTY | `BindWidgetAnimOptional.md` |
| `BindWidgetOptional` | 指定在C++类中该Widget属性可以绑定到UMG的某个同名控件，也可以不绑定 | UPROPERTY | `BindWidgetOptional.md` |
| `DefaultGraphNode` | 标记引擎默认创建的蓝图节点 | UCLASS | `DefaultGraphNode.md` |
| `DesignerRebuild` | 指定Widget里的某个属性值改变后应该重新刷新UMG的预览界面 | UPROPERTY | `DesignerRebuild.md` |
| `DisableNativeTick` | 禁用该UserWidget的NativeTick | UCLASS | `DisableNativeTick.md` |
| `EntryClass` | 限定EntryWidgetClass属性上可选类必须继承自的基类，用在DynamicEntryBox和ListView这两个Widget上 | UCLASS, UPROPERTY | `EntryClass.md` |
| `EntryInterface` | 限定EntryWidgetClass属性上可选类必须实现的接口，用在DynamicEntryBox和ListView这两个Widget上 | UCLASS, UPROPERTY | `EntryInterface.md` |
| `IsBindableEvent` | 把一个动态单播委托暴露到UMG蓝图里以绑定相应事件 | UPROPERTY | `IsBindableEvent.md` |
| `OptionalWidget` | 指定在C++类中该Widget属性可以绑定到UMG的某个同名控件，也可以不绑定 | UPROPERTY | `OptionalWidget.md` |
| `ViewmodelBlueprintWidgetExtension` | 用来验证InListItems的Object类型是否符合EntryWidgetClass的MVVM绑定的ViewModelProperty | UFUNCTION | `ViewmodelBlueprintWidgetExtension.md` |



