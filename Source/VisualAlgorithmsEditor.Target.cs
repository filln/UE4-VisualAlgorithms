// Copyright 2020 Anatoli Kucharau. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class VisualAlgorithmsEditorTarget : TargetRules
{
	public VisualAlgorithmsEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;

		ExtraModuleNames.AddRange( new string[] { "VisualAlgorithms" } );
	}
}
