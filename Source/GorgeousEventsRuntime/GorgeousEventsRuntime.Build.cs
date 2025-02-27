// Copyright (c) 2025 Simsalabim Studios (Nils Bergemann). All rights reserved.
/*==========================================================================>
|              Gorgeous Events - Events functionality provider              |
| ------------------------------------------------------------------------- |
|         Copyright (C) 2025 Gorgeous Things by Simsalabim Studios,         |
|              administrated by Epic Nova. All rights reserved.             |
| ------------------------------------------------------------------------- |
|                   Epic Nova is an independent entity,                     |
|         that has nothing in common with Epic Games in any capacity.       |
<==========================================================================*/
using System.IO;
using UnrealBuildTool;

public class GorgeousEventsRuntime : ModuleRules
{
    public GorgeousEventsRuntime(ReadOnlyTargetRules Target) : base(Target)
    {
        var publicIncludePath = Path.Combine(ModuleDirectory, "Public");
        var privateIncludePath = Path.Combine(ModuleDirectory, "Private");

        PublicIncludePaths.AddRange(new string[]
        {
            publicIncludePath,
            Path.Combine(publicIncludePath, "ModuleCore"),
            Path.Combine(publicIncludePath, "Events"),
        });
        
        PrivateIncludePaths.AddRange(new string[]
        {
            Path.Combine(privateIncludePath, "HeaderFiles")
        });
        
        PublicDependencyModuleNames.AddRange(new[] { "GorgeousCoreRuntime", "GorgeousCoreRuntimeUtilities", "Core", "CoreUObject", "Engine", "InputCore", "GameplayTags", "Projects" });
        
        PrivateDependencyModuleNames.Add("GorgeousCoreRuntime");
    }
}