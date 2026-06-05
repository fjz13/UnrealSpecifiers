---
title: "Replicated"
id: "UPROPERTY.Replicated"
kind: "specifier"
symbol: "Replicated"
scope: "UPROPERTY"
category: "Network"
source_status: "verified_UE5.8"
target_ue_version: "UE5.8"
normalization_status: "normalized"
normalized_at: "2026-06-04"
summary: "指定该属性应随网络进行复制"
usage: "UPROPERTY / Network"
---

# Replicated

## Decision Summary

- **Use when:** Actor 或 replicated subobject 的属性需要从服务器同步到客户端。
- **Do not use when:** 只需要本地编辑器默认值、存档或配置。
- **Requires:** 拥有者必须启用复制，并在 `GetLifetimeReplicatedProps` 中注册属性。
- **Conflicts:** 不要和 `ReplicatedUsing` 同时用于同一属性；需要通知时用 `ReplicatedUsing`。
- **Prefer instead:** 需要接收端回调用 `ReplicatedUsing`；客户端到服务器行为用 RPC。

- **功能描述：** 指定该属性应随网络进行复制。

- **元数据类型：** bool
- **引擎模块：** Network
- **作用机制：** 在PropertyFlags中加入CPF_Net
- **常用程度：** ★★★★★

## 行为

`Replicated` 把属性标记为网络复制属性。它只声明属性具备复制资格；运行时能否复制还取决于 owning Actor/component 的复制设置、网络角色、`GetLifetimeReplicatedProps` 中的 lifetime 注册以及复制条件。

## UE5.8 审计结论

在 UE5.8 UHT 源码 `UhtPropertyMemberSpecifiers.cs` 中，`ReplicatedSpecifier` 会设置 `EPropertyFlags.Net`，并拒绝直接在 `USTRUCT` 成员上使用 `Replicated`。Hello 样例 `Property/Network/MyProperty_Network.h/.cpp` 中 `MyInt_Replicated` 的 flags 包含 `CPF_Net`，并通过 `DOREPLIFETIME` 注册 lifetime replication。

## 常见误用

- 只写 `UPROPERTY(Replicated)` 不会自动注册 lifetime replication；仍需要 `GetLifetimeReplicatedProps`。
- `Replicated` 不提供 OnRep 回调；需要通知回调时使用 `ReplicatedUsing=FunctionName`。
- `USTRUCT` 内部成员不能直接标 `Replicated`；结构体属性本身在 owning UObject/Actor 上复制，结构体内部可用 `NotReplicated` 排除字段。

## 示例代码：

记得要在cpp代码中相应添加GetLifetimeReplicatedProps函数

```jsx
UCLASS(Blueprintable, BlueprintType)
class INSIDER_API AMyProperty_Network :public AActor
{
public:
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 MyInt_Default = 123;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated)
		int32 MyInt_Replicated = 123;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated)
		FMyReplicatedStruct MyStruct_Replicated;
};

void AMyProperty_Network::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AMyProperty_Network, MyInt_Replicated);
	DOREPLIFETIME(AMyProperty_Network, MyStruct_Replicated);
}
```

示例效果就不发了，这个是基本的网络标记。
