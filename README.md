# Challenger Core Plugin

## Overview

The Challenger Core plugin represents an innovative approach to developing cover systems in games. Built upon the Lyra Project of Unreal Engine 5.3, its main objective is to create a cover system where characters can dynamically interact with the walls of the environment using a single SphereTrace to calculate the entire process.

One of the key advantages of this system is its in-game performance. Due to its simplicity in calculation, especially in online and competitive environments, the plugin provides a smooth and responsive gaming experience. This is crucial for ensuring fluid gameplay and an immersive experience for players.

However, there are some disadvantages to consider. One of them is that the construction of buildings in the environment may be limited due to the nature of the SphereTrace. It is not always possible to create visually stunning scenarios, as interaction with walls is restricted to collision detection with a sphere.

To mitigate this issue, the Challenger Core includes an additional tool: a building constructor. This tool aims to facilitate the process of building the environment, allowing for the fitting of parts where the sphere collision occurs. This provides developers with a way to create more complex and aesthetically appealing scenarios, even within the limitations of the SphereTrace-based cover system.

## Installation

#### **Important Note: This plugin is a conceptual tool and is not yet ready for use in professional environments.**

To use the plugin, the first step is to obtain a version of the LyraProject from the Unreal Engine 5.3 Marketplace. Before generating the files in the Visual Studio IDE, it is necessary to clone this repository at the following path: `LyraStarterGame\Plugins\GameFeatures`.

To use the construction tool, you need to open the `DefaultEngine.ini` file, which is usually located at the following path within the Lyra project: `LyraStarterGame\Config\DefaultEngine.ini`.

Once opened, you should locate the line where the CollisionProfile is defined:

```ini
[/Script/Engine.CollisionProfile]
```

Then, add three new collision profiles below this line:

```ini
+DefaultChannelResponses = (Channel = ECC_GameTraceChannel6, DefaultResponse = ECR_Ignore, bTraceType = True, bStaticObject = False, Name = "TraceChannel_CoverLeft")
+DefaultChannelResponses = (Channel = ECC_GameTraceChannel7, DefaultResponse = ECR_Ignore, bTraceType = True, bStaticObject = False, Name = "TraceChannel_CoverRight")
+DefaultChannelResponses = (Channel = ECC_GameTraceChannel8, DefaultResponse = ECR_Ignore, bTraceType = True, bStaticObject = False, Name = "TraceChannel_CoverCollision")
```

After these steps, generating the `.sln` file should proceed normally.

## Using the tools

After installation, you can navigate to `ChallengerCore\Content\Map` and open the level `L_FinalBuilding` to see the functionality. If you wish to use the tools to create a building, you should go to `ChallengerCore\Content\Editor\BuildingGenerator` and left-click on the file `WU_HUD_RUN` and run. It will open a utility HUD where you can access a simple API explaining the data flow and the functionality of each button on the panel.
