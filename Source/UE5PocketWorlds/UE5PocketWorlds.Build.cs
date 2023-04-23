// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class UE5PocketWorlds : ModuleRules
{
    public UE5PocketWorlds(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] {
            "CommonGame",
            "CommonUI",
            "Core",
            "CoreUObject",
            "Engine",
            "EnhancedInput",
            "GameplayTags",
            "HeadMountedDisplay",
            "InputCore",
            "UMG",
        });
    }
}
