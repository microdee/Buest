# Buest [byːst]

Self contained UE4 plugin providing Boost so other plugins and projects can have a shared dependency on boost libraries.

## Usage:

Include Buest in your project/plugin:

*\*.uplugin* | *\*.uproject*

```json
	"Plugins": [
		{
			"Name": "Buest",
			"Enabled": true
		}
	]
```

*\*.build.cs*

```CSharp
    <Public or Private>DependencyModuleNames.AddRange( new string[]
    {
        // among others
        "Buest"
    });
```

If you use a Boost library which requires building it, create a `boost.libs` file next to your module's `*.build.cs` *(see below)*

## IWYU building of libraries

The boost library is being built during generating projects so by the time dependent modules getting built, static libs and headers are all in place. In Unreal's IWYU fashion, Buest search for other modules in the project it's included inside (both modules of project and plugins) and reads `boost.libs` files placed next to `*.build.cs` files to gather which libraries to build and link. This is only necessary for libraries required to be built and statically linked. Example of one `boost.libs` file:

```
graph
graph_parallel
program_options
mpi
```

It's just a new line separated list of the name of boost libraries (as seen in the boost/libs folder). Specifying a library which doesn't need building, will cause an error, fortunately B2 tells you which library it has a problem with.

If Buest doesn't find any explicit library usage, it will only handle includes (all the header-only libraries of Boost).