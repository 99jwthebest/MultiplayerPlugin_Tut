// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class MultiP_TPS_TutProj : ModuleRules
{
	public MultiP_TPS_TutProj(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"UMG",
			"Slate",
            "OnlineSubsystemSteam",
			"OnlineSubsystem",
			"MultiplayerSessions",
        });

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"MultiP_TPS_TutProj",
			"MultiP_TPS_TutProj/Variant_Platforming",
			"MultiP_TPS_TutProj/Variant_Platforming/Animation",
			"MultiP_TPS_TutProj/Variant_Combat",
			"MultiP_TPS_TutProj/Variant_Combat/AI",
			"MultiP_TPS_TutProj/Variant_Combat/Animation",
			"MultiP_TPS_TutProj/Variant_Combat/Gameplay",
			"MultiP_TPS_TutProj/Variant_Combat/Interfaces",
			"MultiP_TPS_TutProj/Variant_Combat/UI",
			"MultiP_TPS_TutProj/Variant_SideScrolling",
			"MultiP_TPS_TutProj/Variant_SideScrolling/AI",
			"MultiP_TPS_TutProj/Variant_SideScrolling/Gameplay",
			"MultiP_TPS_TutProj/Variant_SideScrolling/Interfaces",
			"MultiP_TPS_TutProj/Variant_SideScrolling/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
