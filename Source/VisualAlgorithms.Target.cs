// Copyright 2020 Anatoli Kucharau. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class VisualAlgorithmsTarget : TargetRules
{
	public VisualAlgorithmsTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;

		ExtraModuleNames.AddRange( new string[] { "VisualAlgorithms" } );
	}
}
