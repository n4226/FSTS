

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
		"%{wks.location}/Sunrise/src",
		"%{wks.location}/Sunrise/vendor",
		"%{wks.location}/Sunrise/vendor/spdlog/include",

		"%{wks.location}/Sunrise/vendor/glm-master",
		"%{wks.location}/Sunrise/vendor/marl-main/include",
		"%{wks.location}/Sunrise/vendor/stb",
		"%{wks.location}/Sunrise/vendor/mango-master/mango-master/include",
		"%{wks.location}/Sunrise/vendor/libigl/include",
		"%{wks.location}/Sunrise/vendor/HTTPRequest/include",
		"%{wks.location}/Sunrise/vendor/httplib/include",
		"%{wks.location}/Sunrise/vendor/rapidjson/include",
	}	

	links {
		"Sunrise"
	}

	postbuildcommands {
		("{COPY} ../bin/" .. outputdir .. "/Sunrise/Sunrise.dLL ../bin/" .. outputdir .. "/%{prj.name}/")
	}

	filter "system:windows"
		
		cppdialect "C++17"
		staticruntime "on"
		systemversion "latest"

		defines {
			"SR_PLATFORM_WINDOWS"
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
