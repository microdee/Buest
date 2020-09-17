# Buest [byːst]

Self contained UE4 plugin providing Boost so other plugins and projects can have a shared dependency on boost libraries. Dependent plugins and projects don't need to include/ship Boost directly on their own.

## Usage:

**Submodule this repository into your project plugins folder**

```
git submodule add https://github.com/microdee/Buest.git Plugins/Buest
git submodule update --init --recursive
```

**NOTE**: This repository has Boost as a submodule, which then has 153 submodules on its own. It takes a while until all are checked out.

**Include Buest in your project/plugin:**

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

If you use one or more Boost libraries which requires building them,  
**create a `boost.libs` file next to your module's `*.build.cs`** *(see below)*

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

## Including Boost headers

Enclose boost includes with `#include "BoostIncludeStart.h"` and `#include "BoostIncludeEnd.h"`. These headers make sure to suppress warnings inherently coming from Boost libraries. If you encounter more, feel free to add the warning disabling pragma and create a pull request ;)

## On Marketplace compatibility

This plugin might violate some patterns Epic has set up for plugins. The result of `Buest.build.cs` script is not pure, it depends on other plugins included with it in a project. Therefore Buest is not suitable to be placed in Engine plugins and it cannot be precompiled. Because of this other plugins depending on Buest might not be publishable to Epic's UE4 Marketplace. However it's not tested, and precompilation might work just fine for dependent plugins, I'm just managing expectations here.