# Replicated

功能描述: 指定该属性应随网络进行复制。
元数据类型: bool
引擎模块: Network
EPropertyFlags: CPF_Net (../../Flags/EPropertyFlags/CPF_Net.md)
Status: Done
常用程度: 5

示例代码：

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