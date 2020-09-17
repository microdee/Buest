// Some copyright should be here...

using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using Tools.DotNETCommon;
using UnrealBuildTool;

public class Buest : ModuleRules
{
	private string BoostRoot()
	{
		return Path.GetFullPath(Path.Combine(PluginDirectory, "ThirdParty", "boost"));
	}

	public Buest(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		bEnableUndefinedIdentifierWarnings = false;

		Bootstrap();
		BuildBoost(Target);

		PublicSystemIncludePaths.AddRange(new string[]
		{
			PluginDirectory + "/ThirdParty/boost"
		});

		if (BoostLibrariesToBuild.Count > 0)
		{
			var libsDir = Path.Combine(BoostRoot(), "stage", "lib");
			var pattern = Target.Configuration < UnrealTargetConfiguration.Development ?
				"*-mt-gd-x64-*.lib" :
				"*-mt-x64-*.lib";

			PublicAdditionalLibraries.AddRange(Directory.EnumerateFiles(libsDir, pattern));
		}
			
		
		PublicDependencyModuleNames.AddRange( new string[]
		{
			"Core"
		});
			
		
		PrivateDependencyModuleNames.AddRange( new string[]
		{
			"CoreUObject"
		});
	}

	private void Bootstrap()
	{
		if (File.Exists(Path.Combine(BoostRoot(), "b2.exe"))) return;

		Log.WriteLine(LogEventType.Console, "Bootstrapping Boost");

		var boostBootstrap = Process.Start(new ProcessStartInfo
		{
			FileName = "cmd.exe",
			Arguments = "/C " + Path.Combine(BoostRoot(), "bootstrap.bat"),
			UseShellExecute = false,
			WorkingDirectory = BoostRoot()
		});
		boostBootstrap.WaitForExit();

		if (boostBootstrap.ExitCode != 0 || !File.Exists(Path.Combine(BoostRoot(), "b2.exe")))
		{
			throw new Exception("Boost bootstrap didn't execute correctly.");
		}
	}

	private List<string> BoostLibrariesToBuild = new List<string>();

	private void SearchModulesIn(string targetPath)
	{
		var sourcePath = Path.Combine(targetPath, "Source");
		if(!Directory.Exists(sourcePath)) return;

		foreach (var moduleDir in Directory.EnumerateDirectories(sourcePath))
		{
			var boostLibsPath = Path.Combine(moduleDir, "boost.libs");
			if (!File.Exists(boostLibsPath)) continue;

			BoostLibrariesToBuild = File.ReadAllText(boostLibsPath)
				.Split(new[] { Environment.NewLine }, StringSplitOptions.RemoveEmptyEntries)
				.Select(L => L.Trim())
				.Union(BoostLibrariesToBuild)
				.ToList();
		}
	}

	private void SearchModules(ReadOnlyTargetRules Target)
	{
		var projectDir = Path.GetDirectoryName(Target.ProjectFile.FullName);
		SearchModulesIn(projectDir);

		foreach (var pluginDir in Directory.EnumerateDirectories(Path.Combine(projectDir, "Plugins")))
		{
			SearchModulesIn(pluginDir);
		}
	}

	private void BuildBoost(ReadOnlyTargetRules Target)
	{
		var args = "headers";

		SearchModules(Target);

		if (BoostLibrariesToBuild.Count > 0)
		{
			foreach (var L in BoostLibrariesToBuild)
			{
				Log.WriteLine(LogEventType.Console, "Using library: {0}", L);
			}

			var withLibs = BoostLibrariesToBuild
				.Select(L => "--with-"+ L)
				.Aggregate("", (acc, L) => acc + " " + L)
				.Trim();

			args = "-j8 "
				+ "toolset=msvc "
				+ "address-model=64 architecture=x86 "
				+ "link=static runtime-link=shared threading=multi "
				+ withLibs
				+ " stage";
		}
		else Log.WriteLine(LogEventType.Console, "No libraries need to be built");

		var boostB2 = Process.Start(new ProcessStartInfo
		{
			FileName = Path.Combine(BoostRoot(), "b2.exe"),
			Arguments = args,
			UseShellExecute = false,
			WorkingDirectory = BoostRoot()
		});
		boostB2.WaitForExit();

		if (boostB2.ExitCode != 0)
		{
			throw new Exception("Boost could not be built.");
		}
	}
}
