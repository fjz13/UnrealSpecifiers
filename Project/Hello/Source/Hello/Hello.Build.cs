// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class Hello : ModuleRules
{
	public Hello(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		PublicIncludePaths.AddRange(
				new string[] {
				// ... add public include paths required here ...
				ModuleDirectory
				}
				);

		if (Target.bBuildEditor)
		{
			PublicDependencyModuleNames.AddRange(new string[] { "EditorSubsystem" });
			PublicDependencyModuleNames.AddRange(new string[] { "AssetManagerEditor" });

		}

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "Projects","UMG", "AssetRegistry" });

		PrivateDependencyModuleNames.AddRange(new string[] { "Insider","Learn" });


		//DynamicallyLoadedModuleNames.Add("Insider");
		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
