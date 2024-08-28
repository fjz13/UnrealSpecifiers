// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class Learn : ModuleRules
{
	public Learn(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "UMG", "AssetRegistry" });
        PublicDependencyModuleNames.AddRange(new string[] { "Insider" });
        PublicDependencyModuleNames.AddRange(new string[] { "StructUtils" });


        PublicIncludePaths.AddRange(
            new string[] {
				// ... add public include paths required here ...
				ModuleDirectory
            }
            );

        if (Target.bBuildEditor)
        {
            PublicDependencyModuleNames.AddRange(new string[] { "UnrealEd" });
        }

        PrivateDependencyModuleNames.AddRange(new string[] {  });

        //Console.WriteLine(ModuleDirectory);
	    //
	    // Uncomment if you are using Slate UI
	    // PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

	    // Uncomment if you are using online features
	    // PrivateDependencyModuleNames.Add("OnlineSubsystem");

	    // To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true

	    //PublicAdditionalLibraries.Add(Path.Combine(librariesPath, "MedusaCore.lib"));
	    //PublicIncludePaths.Add(Path.Combine(MedusaPath, "MedusaCore"));
	    //Definitions.Add("MEDUSA_UE4");
	}
}
