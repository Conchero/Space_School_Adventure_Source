// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Build_alpha01 : ModuleRules
{
	public Build_alpha01(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay" , "GameplayTasks", "NavigationSystem", "NinjaCharacter", "UMG", "Niagara", "ApexDestruction" });
	}
}
