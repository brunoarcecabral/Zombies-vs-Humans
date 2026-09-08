// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Zombies_vs_Humans : ModuleRules
{
	public Zombies_vs_Humans(ReadOnlyTargetRules Target) : base(Target)
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
			"Slate"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"Zombies_vs_Humans",
			"Zombies_vs_Humans/Variant_Horror",
			"Zombies_vs_Humans/Variant_Horror/UI",
			"Zombies_vs_Humans/Variant_Shooter",
			"Zombies_vs_Humans/Variant_Shooter/AI",
			"Zombies_vs_Humans/Variant_Shooter/UI",
			"Zombies_vs_Humans/Variant_Shooter/Weapons"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
