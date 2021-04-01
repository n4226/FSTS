
workspace "FlightSimTerrainSystem"
	architecture "x64"
		

	configurations {
		"Debug",
		"Release",
		"Dist"
	}


	flags
	{
		"MultiProcessorCompile"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}


group "Dependencies"

group ""

include "Sunrise"
include "FlightSimTerrainSystem"
include "FlightSimTerrainSystemXplanePlugin"