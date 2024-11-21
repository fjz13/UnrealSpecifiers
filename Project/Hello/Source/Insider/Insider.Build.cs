// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class Insider : ModuleRules
{
	public Insider(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		PublicIncludePaths.AddRange(
				new string[] {
				// ... add public include paths required here ...
				ModuleDirectory
				}
				);

		if(Target.bBuildEditor)
		{
			PublicDependencyModuleNames.AddRange(new string[] { "UnrealEd", "BlueprintGraph", "DeveloperSettings", "EditorConfig", "KismetCompiler","AIModule"});
		}


        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore","ApplicationCore","UMG", 
			"StructUtils", "GameplayAbilities","EnhancedInput","GameplayTasks","MovieScene","ControlRig","RigVM","ModelViewViewModel","GameplayTags"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { "AssetRegistry" });

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
