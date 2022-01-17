

project "FlightSimTerrainSystem"

	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	-- mainProjDir = "FlightSimTerrainSystem"
	-- sunriseLocation = "%{wks.location}/Sunrise"

	files {
		"src/**.h",
		"src/**.cpp",

		"src/**.vert",
		"src/**.frag",
		"src/**.comp",
		
		"%{wks.location}/Sunrise/src/**.vert",
		"%{wks.location}/Sunrise/src/**.frag",
		"%{wks.location}/Sunrise/src/**.comp"
	}

	includedirs {
		"C:/VulkanSDK/1.2.154.1/Include",

		"%{wks.location}/Sunrise/src", "%{wks.location}/Sunrise/src/Sunrise",
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

		"%{sunriseLocation}/vendor/asio-1.18.1/include",

		"%{wks.location}/Sunrise/vendor/bin/glfw/windows/glfw-3.3.2.bin.WIN64/glfw-3.3.2.bin.WIN64/lib-vc2019",
		
		"%{wks.location}/Sunrise/vendor/date/include",
		"%{wks.location}/Sunrise/vendor/entt/single_include",
	}	

	libdirs {
		"C:/VulkanSDK/1.2.154.1/Lib",
	}

	links {
		"Sunrise",
		"vulkan-1",
	}

	postbuildcommands {
		--("{COPY} ../bin/" .. outputdir .. "/Sunrise/Sunrise.dLL ../bin/" .. outputdir .. "/%{prj.name}/"),
		--("{COPY} ../bin/" .. outputdir .. "/Sunrise/Sunrise.pdb ../bin/" .. outputdir .. "/%{prj.name}/"),
	}

	filter "system:windows"
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

		
	-- GLSL Shader Compile Pipeline

	filter 'files:**.vert or files:**.frag or files:**.comp'
	   -- A message to display while this build step is running (optional)
	   buildmessage 'Compiling %{file.relpath} TO SPIR-V'
		
	   buildinputs {("%{sunriseLocation}src/Sunrise/graphics/shaders/headers/**.h")}

	   -- One or more commands to run (required)
	   buildcommands {
		  ("C:/VulkanSDK/1.2.154.1/Bin/glslangValidator.exe -V %{file.relpath} -o ../bin/" .. outputdir .. "/%{prj.name}/shaders/%{file.name}.spv -g")
	   }

	   -- One or more outputs resulting from the build (required)
	   buildoutputs {("../bin/" .. outputdir .. "/%{prj.name}/shaders/%{file.name}.spv")}

	   -- One or more additional dependencies for this build command (optional)
	   --buildinputs { 'path/to/file1.ext', 'path/to/file2.ext' }

