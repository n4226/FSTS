
project "FlightSimTerrainSystemXplanePlugin"

	kind "SharedLib"
	language "C++"

	targetname ("win")

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	defines {
		"XPLM200",
		"XPLM210",
		"XPLM300",
		"XPLM301",
		"_DEBUG			",
		"_WINDOWS		",
		"_USRDLL		",
		"SIMDATA_EXPORTS",
	}

	files {
		"src/**.h",
		"src/**.cpp",
	}

	includedirs {
		"%{wks.location}/Sunrise/src",
		"%{wks.location}/Sunrise/vendor",
		"%{wks.location}/Sunrise/vendor/spdlog/include",
		"C:/dev/x-plane sdk/XPSDK303/SDK/CHeaders",
	}	

	libdirs {
		"C:/dev/x-plane sdk/XPSDK303/SDK/Libraries/Win"
	}

	links {
		--"Sunrise",
		"XPLM_64",
		"XPWidgets_64",
		"OpenGL32",
	}

	
	postbuildcommands {
		--("{COPY} ../bin/" .. outputdir .. "/Sunrise/Sunrise.dLL ../bin/" .. outputdir .. "/%{prj.name}/"),

	}


	filter "system:windows"
		
		cppdialect "C++17"
		staticruntime "on"
		systemversion "latest"

		defines {
			"SR_PLATFORM_WINDOWS",
			"IBM"
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
