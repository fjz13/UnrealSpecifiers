# Exec

- **Function description:** Register a function within a specific class as a console command that can accept arguments.
- **Metadata type:** bool
- **Engine module:** Behavior
- **Restriction type:** Specific several classes
- **Action mechanism:** Add [FUNC_Exec](../../../Flags/EFunctionFlags/FUNC_Exec.md) to FunctionFlags
- **Commonly used:** ★★★

Classes typically include: UPlayerInput, APlayerController, APawn, AHUD, AGameModeBase, ACheatManager, AGameStateBase, and subclasses of APlayerCameraManager.

When a console command is entered in the viewport, the execution sequence is as follows: UConsole::ConsoleCommand, then APlayerController::ConsoleCommand, followed by UPlayer::ConsoleCommand. In between, ViewportClient->Exec is attempted (which may handle some editor commands), and finally, ULocalPlayer::Exec is reached (which has already processed some custom commands).

UGameViewportClient, UGameInstance, and UPlayer inherit from FExec, hence they include four overloaded virtual functions: Exec, Exec_Runtime, Exec_Dev, and Exec_Editor.

UEngine::Exec internally forwards the call to various modules for handling. The significant function here is StaticExec, which ultimately calls FSelfRegisteringExec::StaticExec(InWorld, Cmd, Ar) to invoke self-registered Execs.

If a command is executed in the editor with ~, FConsoleCommandExecutor::ExecInternal will ultimately lead to ULocalPlayer::Exec.

## Test code:

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

Results when opening the console and running during PIE:

![Untitled](Untitled.png)

## Principle:

According to the source code flow:

```cpp
bool UGameViewportClient::Exec(UWorld* InWorld, const TCHAR* Cmd, FOutputDevice& Ar)
{
	//ULocalPlayer::Exec_Editor, Exec_Dev, and Exec_Runtime are checked in order to determine if they correspond to certain commands
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
	//ULocalPlayer::Exec_Editor, Exec_Dev, and Exec_Runtime are checked in order to determine if they correspond to certain commands
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

The order to search for Exec should be:

- UGameInstance::Exec, UGameInstance::ProcessConsoleExec
- GEngine->Exec(InWorld, Cmd, Ar)
- `UWorld`::Exec, when there is no LocalPlayer handling
- `UPlayerInput::ProcessConsoleExec`
- `APlayerController::ProcessConsoleExec`
- `APawn::ProcessConsoleExec`
- `AHUD::ProcessConsoleExec`
- `AGameModeBase::ProcessConsoleExec`
- `ACheatManager::ProcessConsoleExec`
- `AGameStateBase::ProcessConsoleExec`
- `APlayerCameraManager::ProcessConsoleExec`

ProcessConsoleExec internally calls the CallFunctionByNameWithArguments code, thus indeed limiting the way Execs declared in this manner to only the aforementioned classes

```cpp
bool UObject::CallFunctionByNameWithArguments(const TCHAR* Str, FOutputDevice& Ar, UObject* Executor, bool bForceCallWithNonExec/*=false*/)
{
	UFunction* Function = FindFunction(Message);//Search for function
}
```