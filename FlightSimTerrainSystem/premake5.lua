

project "FlightSimTerrainSystem"

	kind "ConsoleApp"
	language "C++"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")



	files {
		"src/**.h",
		"src/**.cpp",
	}

	includedirs {
	}	

	links {
		"Sunrise"
	}

	filter "system:windows"
		
		cppdialect "C++17"
		staticruntime "on"
		systemversion "latest"

		defines {
		}


	filter "configurations:Debug"
		defines "SR_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "SR_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "SR_DIST"
		runtime "Release"
		optimize "on"
