# Exec

- **功能描述：** 在特定类里注册一个函数为作为控制台命令，允许接受参数。
- **元数据类型：** bool
- **引擎模块：** Behavior
- **限制类型：** 特定的几个类
- **作用机制：** 在FunctionFlags中加入[FUNC_Exec](../../../Flags/EFunctionFlags/FUNC_Exec.md)
- **常用程度：** ★★★

一般特定的几个类是：UPlayerInput，APlayerController，APawn，AHUD，AGameModeBase，ACheatManager，AGameStateBase，APlayerCameraManager的子类。

当在视口中输入控制台命令后，首先执行到的是UConsole::ConsoleCommand，然后是APlayerController::ConsoleCommand，然后是UPlayer::ConsoleCommand，中间先尝试ViewportClient->Exec（可能处理一些编辑器命令），然后到达ULocalPlayer::Exec（已经处理一些自定义命令了）。

UGameViewportClient，UGameInstance，UPlayer是继承于FExec的，因此本身含有一些Exec，Exec_Runtime，Exec_Dev，Exec_Editor的4个虚函数重载。

其中UEngine::Exec，内部会转发给各个模块来尝试。其中重要的是StaticExec，最后会FSelfRegisteringExec::StaticExec( InWorld, Cmd,Ar )来调用自注册的Exec。

如果是在编辑器中~执行命令，FConsoleCommandExecutor::ExecInternal，最后也会到ULocalPlayer::Exec。

## 测试代码：

```cpp
UCLASS(Blueprintable, BlueprintType)
class INSIDER_API AMyFunction_Exec :public APawn
{
public:
	GENERATED_BODY()
public:
	//FunctionFlags:	FUNC_Final | FUNC_Exec | FUNC_Native | FUNC_Public
	UFUNCTION(exec)
	void MyExec();
};
void AMyFunction_Exec::MyExec()
{
	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, "MyExec");
}
```

在PIE的时候~打开控制台运行结果：

![Untitled](Untitled.png)

## 原理：

根据源码中的流程：

```cpp
bool UGameViewportClient::Exec(UWorld* InWorld, const TCHAR* Cmd, FOutputDevice& Ar)
{
	//按顺序ULocalPlayer::Exec_Editor,Exec_Dev,Exec_Runtime，各自判断是否是一些命令
	if (FExec::Exec(InWorld, Cmd, Ar))
	{
		return true;
	}
	else if (ProcessConsoleExec(Cmd, Ar, NULL))
	{
		return true;
	}
	else if (GameInstance && (GameInstance->Exec(InWorld, Cmd, Ar) || GameInstance->ProcessConsoleExec(Cmd, Ar, nullptr)))
	{
		return true;
	}
	else if (GEngine->Exec(InWorld, Cmd, Ar))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool UPlayer::Exec( UWorld* InWorld, const TCHAR* Cmd,FOutputDevice& Ar)
{
	// Route through Exec_Dev and Exec_Editor first
	//按顺序ULocalPlayer::Exec_Editor,Exec_Dev,Exec_Runtime，各自判断是否是一些命令
	if (FExec::Exec(InWorld, Cmd, Ar))
	{
		return true;
	}

	AActor* ExecActor = PlayerController;
	if (!ExecActor)
	{
		UNetConnection* NetConn = Cast<UNetConnection>(this);
		ExecActor = (NetConn && NetConn->OwningActor) ? ToRawPtr(NetConn->OwningActor) : nullptr;
	}

	if (ExecActor)
	{
		// Since UGameViewportClient calls Exec on UWorld, we only need to explicitly
		// call UWorld::Exec if we either have a null GEngine or a null ViewportClient
		UWorld* World = ExecActor->GetWorld();
		check(World);
		check(InWorld == nullptr || InWorld == World);
		const bool bWorldNeedsExec = GEngine == nullptr || Cast<ULocalPlayer>(this) == nullptr || static_cast<ULocalPlayer*>(this)->ViewportClient == nullptr;
		APawn* PCPawn = PlayerController ? PlayerController->GetPawnOrSpectator() : nullptr;
		if (bWorldNeedsExec && World->Exec(World, Cmd, Ar))
		{
			return true;
		}
		else if (PlayerController && PlayerController->PlayerInput && PlayerController->PlayerInput->ProcessConsoleExec(Cmd, Ar, PCPawn))
		{
			return true;
		}
		else if (ExecActor->ProcessConsoleExec(Cmd, Ar, PCPawn))
		{
			return true;
		}
		else if (PCPawn && PCPawn->ProcessConsoleExec(Cmd, Ar, PCPawn))
		{
			return true;
		}
		else if (PlayerController && PlayerController->MyHUD && PlayerController->MyHUD->ProcessConsoleExec(Cmd, Ar, PCPawn))
		{
			return true;
		}
		else if (World->GetAuthGameMode() && World->GetAuthGameMode()->ProcessConsoleExec(Cmd, Ar, PCPawn))
		{
			return true;
		}
		else if (PlayerController && PlayerController->CheatManager && PlayerController->CheatManager->ProcessConsoleExec(Cmd, Ar, PCPawn))
		{
			return true;
		}
		else if (World->GetGameState() && World->GetGameState()->ProcessConsoleExec(Cmd, Ar, PCPawn))
		{
			return true;
		}
		else if (PlayerController && PlayerController->PlayerCameraManager && PlayerController->PlayerCameraManager->ProcessConsoleExec(Cmd, Ar, PCPawn))
		{
			return true;
		}
	}
	return false;
}
```

查找Exec的顺序应该是：

- UGameInstance::Exec，UGameInstance::ProcessConsoleExec
- GEngine->Exec(InWorld, Cmd, Ar)
- `UWorld`::Exec，在没有LocalPlayer处理的情况下
- `UPlayerInput::ProcessConsoleExec`
- `APlayerController::ProcessConsoleExec`
- `APawn::ProcessConsoleExec`
- `AHUD::ProcessConsoleExec`
- `AGameModeBase::ProcessConsoleExec`
- `ACheatManager::ProcessConsoleExec`
- `AGameStateBase::ProcessConsoleExec`
- `APlayerCameraManager::ProcessConsoleExec`

ProcessConsoleExec内部会调用CallFunctionByNameWithArguments代码：因此确实会限制这种方式声明的Exec只能在以上几个类里面

```cpp
bool UObject::CallFunctionByNameWithArguments(const TCHAR* Str, FOutputDevice& Ar, UObject* Executor, bool bForceCallWithNonExec/*=false*/)
{
	UFunction* Function = FindFunction(Message);//寻找函数
}
```