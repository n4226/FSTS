
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

mainProjDir = "FlightSimTerrainSystem"
sunriseLocation = "%{wks.location}/Sunrise"

group "Dependencies"

group ""

include "Sunrise"
include "FlightSimTerrainSystem"
include "FlightSimTerrainSystemXplanePlugin"