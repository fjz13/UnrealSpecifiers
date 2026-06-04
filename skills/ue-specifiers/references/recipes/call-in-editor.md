# 场景：CallInEditor

## 适用问题

用户通常会这样问：

- 想在编辑器 Details Panel 点按钮执行函数。
- 关卡里选中 Actor 后运行一个编辑器工具函数。
- `CallInEditor` 要不要配 `BlueprintCallable`？

## 推荐写法

```cpp
UFUNCTION(CallInEditor, Category="Tools")
void RebuildPreview();
```

## 为什么这样写

- `CallInEditor` 让函数在编辑器 Details Panel 中可调用。
- `Category` 帮助按钮归类。
- 该函数应适合编辑器环境执行，避免依赖运行时-only 状态。

## 替代方案

### 同时允许 Blueprint 调用

```cpp
UFUNCTION(CallInEditor, BlueprintCallable, Category="Tools")
void RebuildPreview();
```

适合：同一操作既要编辑器按钮，也要蓝图调用。

不适合：只应该在编辑器人工触发的危险操作。

### 运行时 Blueprint 函数

```cpp
UFUNCTION(BlueprintCallable, Category="Tools")
void RebuildRuntimeState();
```

适合：游戏运行时逻辑。

不适合：编辑器资产处理或构建预览。

## 常见误用

- 在 `CallInEditor` 函数里假设 BeginPlay 已经执行。
- 执行会修改资产或关卡的大操作但没有事务、确认或脏标记策略。
- 把 editor-only 工具暴露给运行时调用路径。

## 版本状态

- UE5.8: pending_UE5.8_validation

## 相关知识

- indexes: `references/indexes/specifiers.index.md`
- original docs: `references/sources/Specifier/UFUNCTION/Blueprint/CallInEditor/CallInEditor.md`
