// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class InsiderEditor : ModuleRules
{
	public InsiderEditor(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
        OverridePackageType = PackageOverrideType.GameDeveloper;


        PublicIncludePaths.AddRange(
				new string[] {
				// ... add public include paths required here ...
				ModuleDirectory
				}
				);

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore","ApplicationCore"});

        PublicDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore", "UnrealEd", "PropertyEditor" });


        PrivateDependencyModuleNames.AddRange(new string[] { "UnrealEd", "BlueprintGraph", "DeveloperSettings", "EditorConfig", "KismetCompiler","AssetTools","AnimGraph" });


        PublicDependencyModuleNames.AddRange(new string[] { "Insider" });

        // Uncomment if you are using Slate UI
        // PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

        // Uncomment if you are using online features
        // PrivateDependencyModuleNames.Add("OnlineSubsystem");

        // To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
    }
}
