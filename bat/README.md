# UE5.8 Validation Wrappers

These wrappers compile and test the local `Hello.uproject` sample project used for `ue-specifiers` validation.

They write UE logs to `.agents/logs/` and print only summaries or bounded failure output.

## Environment Overrides

```bat
set UESPEC_UE_ROOT=C:\Program Files\Epic Games\UE_5.8
set UESPEC_HELLO_ROOT=D:\github\GitWorkspace\Hello
set UESPEC_SMOKE_EXTRA_ARGS=-SomeUnrealArg
```

## Commands

```bat
bat\build-hello.bat
bat\editor-hello.bat
bat\inspect-hello-log.bat
```

`Insider` is a sample-code corpus, not an automation test suite. Use `editor-hello.bat` for visual behavior comparison in the editor.

`inspect-hello-log.bat` does not launch UE. Use it after editor observation to extract recent errors and reflection/specifier-related log markers from the latest Hello editor log.

Current observation: `HelloEditor` built successfully on 2026-06-04. A headless automation attempt using `Insider.` was removed because `Insider` is not an automation test collection. A headless `UnrealEditor-Cmd -ExecCmds="Quit"` smoke attempt was also removed because it did not exit reliably for this project.
