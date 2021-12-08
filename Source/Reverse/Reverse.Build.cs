// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Reverse : ModuleRules
{
	public Reverse(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay" });
	}
}
