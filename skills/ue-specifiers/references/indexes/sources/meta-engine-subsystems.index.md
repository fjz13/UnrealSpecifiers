# Meta Engine Subsystems

> Category source index. Use targeted search in this file, then open only the listed `Doc`.
> Resolve `Doc` relative to the nearest preceding `Doc root`; each `Doc root` is relative to `references/sources/`.

## Meta - DataflowFlesh

> Doc root: `Meta/Struct/`

| ID | Summary | Usage | Doc |
|---|---|---|---|
| `DataflowFlesh` | ScriptStruct /Script/DataflowNodes.FloatOverrideDataflowNode | USTRUCT | `DataflowFlesh.md` |



## Meta - Debug

> Doc root: `Meta/`

| ID | Summary | Usage | Doc |
|---|---|---|---|
| `DebugTreeLeaf` | 阻止BlueprintDebugger展开该类的属性以加速编辑器里调试器的性能 | UCLASS | `DebugTreeLeaf.md` |



## Meta - GAS

> Doc root: `Meta/GAS/`

| ID | Summary | Usage | Doc |
|---|---|---|---|
| `HideFromModifiers` | 指定AttributeSet下的某属性不出现在GameplayEffect下的Modifiers的Attribute选择里 | UPROPERTY | `HideFromModifiers.md` |
| `HideInDetailsView` | 把该UAttributeSet子类里的属性隐藏在FGameplayAttribute的选项列表里 | UCLASS, UPROPERTY | `HideInDetailsView.md` |
| `SystemGameplayAttribute` | 把UAbilitySystemComponent子类里面的属性暴露到FGameplayAttribute 选项框里 | UPROPERTY | `SystemGameplayAttribute.md` |



## Meta - Material

> Doc root: `Meta/Material/`

| ID | Summary | Usage | Doc |
|---|---|---|---|
| `MaterialControlFlow` | 标识该UMaterialExpression为一个控制流节点，当前在材质蓝图右键菜单中隐藏 | UCLASS | `MaterialControlFlow.md` |
| `MaterialNewHLSLGenerator` | 标识该UMaterialExpression为采用新HLSL生成器的节点，当前在材质蓝图右键菜单中隐藏 | UCLASS | `MaterialNewHLSLGenerator.md` |
| `MaterialParameterCollectionFunction` | 指定该函数是用于操作UMaterialParameterCollection，从而支持ParameterName的提取和验证 | UFUNCTION | `MaterialParameterCollectionFunction.md` |
| `OverridingInputProperty` | 在UMaterialExpression中指定本float要覆盖的其他FExpressionInput 属性 | UPROPERTY | `OverridingInputProperty.md` |
| `Private` | 标识该UMaterialExpression为私有节点，当前在材质蓝图右键菜单中隐藏 | UCLASS | `Private.md` |
| `RequiredInput` | 在UMaterialExpression中指定FExpressionInput属性是否要求输入，引脚显示白色或灰色 | UPROPERTY | `RequiredInput.md` |
| `ShowAsInputPin` | 使得UMaterialExpression里的一些基础类型属性变成材质节点上的引脚 | UPROPERTY | `ShowAsInputPin.md` |



## Meta - Niagara

> Doc root: `Meta/Niagara/`

| ID | Summary | Usage | Doc |
|---|---|---|---|
| `NiagaraClearEachFrame` | ScriptStruct /Script/Niagara.NiagaraSpawnInfo | USTRUCT | `NiagaraClearEachFrame.md` |
| `NiagaraInternalType` | 指定该结构的类型为Niagara的内部类型 | USTRUCT | `NiagaraInternalType.md` |



## Meta - Script

> Doc root: `Meta/Script/`

| ID | Summary | Usage | Doc |
|---|---|---|---|
| `ScriptConstant` | 把一个静态函数的返回值包装成为一个常量值 | UFUNCTION | `ScriptConstant.md` |
| `ScriptConstantHost` | 在ScriptConstant的基础上，指定常量生成的所在类型 | UFUNCTION | `ScriptConstantHost.md` |
| `ScriptDefaultBreak` | 见ScriptDefaultMake的原理和测试代码 | USTRUCT | `ScriptDefaultBreak.md` |
| `ScriptDefaultMake` | 禁用结构上的HasNativeMake，在脚本里构造的时候不调用C++里的NativeMake函数，而采用脚本内建的默认初始化方式 | USTRUCT | `ScriptDefaultMake.md` |
| `ScriptMethod` | 把静态函数导出变成第一个参数的成员函数 | UFUNCTION | `ScriptMethod.md` |
| `ScriptMethodMutable` | 把ScriptMethod的第一个const结构参数在调用上改成引用参数，函数内修改的值会保存下来 | UFUNCTION | `ScriptMethodMutable.md` |
| `ScriptMethodSelfReturn` | 在ScriptMethod的情况下，指定把这个函数的返回值要去覆盖该函数的第一个参数 | UFUNCTION | `ScriptMethodSelfReturn.md` |
| `ScriptName` | 在导出到脚本里时使用的名字 | Any | `ScriptName.md` |
| `ScriptNoExport` | 不导出该函数或属性到脚本 | UFUNCTION, UPROPERTY | `ScriptNoExport.md` |
| `ScriptOperator` | 把第一个参数为结构的静态函数包装成结构的运算符 | UFUNCTION | `ScriptOperator.md` |



## Meta - Sequencer

> Doc root: `Meta/Sequencer/`

| ID | Summary | Usage | Doc |
|---|---|---|---|
| `CommandLineID` | 标记UMovieSceneCaptureProtocolBase的子类的协议类型 | UCLASS | `CommandLineID.md` |
| `SequencerBindingResolverLibrary` | 把具有SequencerBindingResolverLibrary标记的UBlueprintFunctionLibrary作为动态绑定的类 | UCLASS | `SequencerBindingResolverLibrary.md` |
| `TakeRecorderDisplayName` | 指定UTakeRecorderSource的显示名字 | UCLASS | `TakeRecorderDisplayName.md` |



## Meta - SparseDataType

> Doc root: `Meta/`

| ID | Summary | Usage | Doc |
|---|---|---|---|
| `NoGetter` | 阻止UHT为该属性生成一个C++的get函数，只对稀疏类的结构数据里的属性生效 | UPROPERTY | `NoGetter.md` |



## Meta - UHT

> Doc root: `Meta/UHT/`

| ID | Summary | Usage | Doc |
|---|---|---|---|
| `CppFromBpEvent` | 指定这是个在C++中定义的蓝图事件 | Todo | `CppFromBpEvent.md` |
| `CustomThunk` | 指定UHT不为该函数生成蓝图调用的辅助函数，而需要用户自定义编写 | UFUNCTION | `CustomThunk.md` |
| `DocumentationPolicy` | 指定文档验证的规则，当前只能设为Strict | Any | `DocumentationPolicy.md` |
| `FieldNotifyInterfaceParam` | 指定函数的某个参数提供FieldNotify的ViewModel信息 | UFUNCTION | `FieldNotifyInterfaceParam.md` |
| `IncludePath` | 记录UClass的引用路径 | UCLASS | `IncludePath.md` |
| `ModuleRelativePath` | 记录类型定义的的头文件路径，为其处于模块的内部相对路径 | Any | `ModuleRelativePath.md` |
| `NativeConstTemplateArg` | 指定该属性是一个const的模板参数 | UPROPERTY | `NativeConstTemplateArg.md` |




