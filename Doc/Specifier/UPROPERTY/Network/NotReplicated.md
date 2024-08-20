# NotReplicated

- **功能描述：**跳过复制。这只会应用到服务请求函数中的结构体成员和参数。

- **元数据类型：**bool
- **引擎模块：**Network
- **限制类型：**Struct members
- **作用机制：**在PropertyFlags中加入[CPF_RepSkip](../../../Flags/EPropertyFlags/CPF_RepSkip.md)
- **常用程度：**★★★

只用在结构成员中，指定struct中的某个属性不复制，否则默认就都会复制。这个用于排除掉结构中的某属性。

## 示例代码：

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

其中MyStruct_Replicated会复制，但是其中的MyString_NotReplicated不会复制。