// Some copyright should be here...

using UnrealBuildTool;

public class Buest : ModuleRules
{
	public Buest(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicIncludePaths.AddRange( new string[]
		{
			// ... add public include paths required here ...
		});

		PublicSystemIncludePaths.AddRange(new string[]
		{
			PluginDirectory + "/ThirdParty/boost/libs/graph/include"
		});
		
		PrivateIncludePaths.AddRange( new string[]
		{
			// ... add other private include paths required here ...
		});
			
		
		PublicDependencyModuleNames.AddRange( new string[]
		{
			"Core",
			"Engine",
			"RenderCore"
			// ... add other public dependencies that you statically link with here ...
		});

        if (Target.bBuildEditor == true)
        {
			PublicDependencyModuleNames.Add("UnrealEd");
        }
			
		
		PrivateDependencyModuleNames.AddRange( new string[]
		{
			"CoreUObject",
			"Engine"
			// ... add private dependencies that you statically link with here ...	
		});
		
		
		DynamicallyLoadedModuleNames.AddRange( new string[]
		{
			// ... add any modules that your module loads dynamically here ...
		});
	}
}
