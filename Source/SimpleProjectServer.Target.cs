// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class SimpleProjectServerTarget : TargetRules
{
	public SimpleProjectServerTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Server;
        //bUsesSteam = true;
        ExtraModuleNames.AddRange( new string[] { "SimpleProject" } );
	}
}