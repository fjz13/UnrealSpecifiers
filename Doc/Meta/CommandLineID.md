# CommandLineID

Description: 标记UMovieSceneCaptureProtocolBase的子类的协议类型。
Usage: UCLASS
Feature: Editor
Group: Sequencer
Type: string="abc"
LimitedType: UMovieSceneCaptureProtocolBase的子类上
Status: Done

标记UMovieSceneCaptureProtocolBase的子类的协议类型。

用来在Sequcencer渲染导出的时候选择到正确的处理类。一般也就引擎内部使用，除非想自己自定义渲染输出的格式协议类。

测试效果：

![Untitled](CommandLineID/Untitled.png)

原理：

简单来说就是通过选择的格式名字来找到相关的ProtocolType Class

```cpp
void UMovieSceneCapture::Initialize(TSharedPtr<FSceneViewport> InSceneViewport, int32 PIEInstance)
{
			FString ImageProtocolOverrideString;
			if (   FParse::Value( FCommandLine::Get(), TEXT( "-MovieFormat=" ), ImageProtocolOverrideString )
			|| FParse::Value( FCommandLine::Get(), TEXT( "-ImageCaptureProtocol=" ), ImageProtocolOverrideString ) )
			{
				static const TCHAR* const CommandLineIDString = TEXT("CommandLineID");
				TArray<UClass*> AllProtocolTypes = FindAllCaptureProtocolClasses();
				for (UClass* Class : AllProtocolTypes)
				{
					bool bMetaDataMatch = Class->GetMetaData(CommandLineIDString) == ImageProtocolOverrideString;
					if ( bMetaDataMatch || Class->GetName() == ImageProtocolOverrideString )
					{
						OverrideClass = Class;
					}
				}
				ImageCaptureProtocolType = OverrideClass;		
			}
			
		if (FParse::Value( FCommandLine::Get(), TEXT( "-AudioCaptureProtocol=" ), AudioProtocolOverrideString ) )
		{
			static const TCHAR* const CommandLineIDString = TEXT("CommandLineID");
		}
	}
```