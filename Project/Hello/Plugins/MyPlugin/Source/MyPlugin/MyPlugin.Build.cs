// Copyright 2018 Jianzhao Fu. All Rights Reserved.
using System.IO;
using UnrealBuildTool;

public class MyPlugin : ModuleRules
{
	public MyPlugin(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"CoreUObject",
				"Engine",
                "Projects",
				// ... add other public dependencies that you statically link with here ...
			}
			);
	}
}
