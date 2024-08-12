# NotReplicated

Type: bool
Feature: Network
LimitedType: Struct members
Description: 跳过复制。这只会应用到服务请求函数中的结构体成员和参数。
EPropertyFlags: CPF_RepSkip (../../Flags/EPropertyFlags/CPF_RepSkip.md)
Status: Done

只用在结构成员中，指定struct中的某个属性不复制，否则默认就都会复制

测试代码：

```cpp
USTRUCT(BlueprintType)
struct FMyReplicatedStruct
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString MyString_Default;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,NotReplicated)
		FString MyString_NotReplicated;
};

UCLASS(Blueprintable, BlueprintType)
class INSIDER_API AMyProperty_Network :public AActor
{
public:
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated)
		FMyReplicatedStruct MyStruct_Replicated;
};
```