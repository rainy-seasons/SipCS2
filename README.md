## Disclaimer: If you attempt to use this online you will be banned.

# Overview
This project uses my library [ProcMem](https://github.com/rainy-seasons/ProcMem) for interacting with the memory of the CS2 process.
The CFGManager class handles operations regarding the configuration file which contains keybind data. Multithreading is implemented for the defuse check so it can run seamlessly alongside other features with little to no performance impact.

The FeatureManager class contains implementations of each feature.

The SettingManager class handles all the settings for the application, including activation states for the features.

# Features
* Perfect BunnyHop
	* Gain momentum to reach maximum speed and maintain it effortlessly
* Triggerbot 
	* Instantly shoot when an enemy is in your crosshair
* Defuse Check 
	* Makes a sound when an enemy is faking the defuse by starting the defuse and ending it early

# Offsets
Offsets are found through static and dynamic analysis of `client.dll` and `engine.dll`.
In order to update the offsets, the data structures must be found through reverse engineering techniques. 

Alternatively, the pattern scanner could be developed to dynamically gain offsets at runtime, with no need for manual analysis, regardless of game updates. (Coming soon)
