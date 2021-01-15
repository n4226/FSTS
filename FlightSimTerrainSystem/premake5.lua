

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
		"C:/VulkanSDK/1.2.154.1/Include",

		"%{wks.location}/Sunrise/src",
		"%{wks.location}/Sunrise/vendor",
		"%{wks.location}/Sunrise/vendor/spdlog/include",

		"%{wks.location}/Sunrise/vendor/glm-master",
		"%{wks.location}/Sunrise/vendor/marl-main/marl-main/include",
		"%{wks.location}/Sunrise/vendor/stb",
		"%{wks.location}/Sunrise/vendor/mango-master/mango-master/include",
		"%{wks.location}/Sunrise/vendor/libigl/include",
		"%{wks.location}/Sunrise/vendor/HTTPRequest/include",
		"%{wks.location}/Sunrise/vendor/httplib/include",
		"%{wks.location}/Sunrise/vendor/rapidjson/include",
		"%{wks.location}/Sunrise/vendor/libguarded/src",
		"%{wks.location}/Sunrise/vendor/nlohmann/include",

		"%{wks.location}/Sunrise/vendor/bin/glfw/windows/glfw-3.3.2.bin.WIN64/glfw-3.3.2.bin.WIN64/lib-vc2019"

	}	

	links {
		"Sunrise"
	}

	postbuildcommands {
		("{COPY} ../bin/" .. outputdir .. "/Sunrise/Sunrise.dLL ../bin/" .. outputdir .. "/%{prj.name}/"),
		("{COPY} ../bin/" .. outputdir .. "/Sunrise/Sunrise.pdb ../bin/" .. outputdir .. "/%{prj.name}/"),
		--("call ../Sunrise/src/Sunrise/Sunrise/graphcis/shaders/compileShaders.bat"),
		--("XCOPY /S /Y ../Sunrise/src/Sunrise/Sunrise/graphcis/shaders/ ../bin/" .. outputdir .. "/%{prj.name}/shaders"),
	}

	filter "system:windows"
		
		cppdialect "C++17"
		staticruntime "on"
		systemversion "latest"

		defines {
			"SR_PLATFORM_WINDOWS"
		}
		debugdir ("../bin/" .. outputdir .. "/%{prj.name}/")


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
