# 场景：SaveGame 属性

## 适用问题

用户通常会这样问：

- 这个字段要存档，应该加什么？
- `SaveGame` 会不会自动保存所有对象？
- 临时缓存能不能加 `SaveGame`？

## 推荐写法

```cpp
UPROPERTY(SaveGame, BlueprintReadWrite, Category="Save")
int32 PlayerLevel = 1;
```

## 为什么这样写

- `SaveGame` 标记该属性适合存档序列化路径。
- `BlueprintReadWrite` 只在需要蓝图读写存档数据时添加。
- `SaveGame` 不等于自动完成整个保存流程；仍需要项目的保存/加载系统处理对象和 slot。

## 替代方案

### 只由 C++ 维护的存档字段

```cpp
UPROPERTY(SaveGame)
int32 PlayerLevel = 1;
```

适合：Blueprint 不需要访问。

不适合：UI 或蓝图存档流程需要读写。

### 运行时临时缓存

```cpp
UPROPERTY(Transient)
TObjectPtr<UObject> RuntimeCache;
```

适合：不应该保存的临时状态。

不适合：玩家进度、配置和持久数据。

## 常见误用

- 以为 `SaveGame` 会自动保存 Actor 到磁盘。
- 同一属性同时表达 `SaveGame` 和 `Transient` 的相反意图。
- 保存 UObject 引用但没有考虑加载时对象是否可恢复。

## 版本状态

- UE5.8: verified_UE5.8

## 相关知识

- indexes: `references/indexes/specifiers.index.md`
- original docs: `references/sources/Specifier/UPROPERTY/Serialization/SaveGame/SaveGame.md`, `references/sources/Specifier/UPROPERTY/Serialization/Transient/Transient.md`
