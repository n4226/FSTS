

project "FlightSimTerrainSystem"

	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "off"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	-- mainProjDir = "FlightSimTerrainSystem"
	-- sunriseLocation = "%{wks.location}/Sunrise"

	glslCompilerLoc = "C:/VulkanSDK/1.2.154.1/Bin/glslangValidator.exe"

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
		"%{wks.location}/Sunrise/vendor/eigen"
	}	


	links {
		"Sunrise",
		"marl",
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
		

		libdirs {
			"C:/VulkanSDK/1.2.154.1/Lib",
		}
		
		links {
			"vulkan-1"
		}


	filter "system:macosx"

		defines {
			"SR_PLATFORM_MACOS"
		}

		xcodebuildsettings { ["ALWAYS_SEARCH_USER_PATHS"] = "YES" }

		includedirs {
			"/usr/local/include",
			"%{wks.location}/Sunrise/vendor/bin/glfw/macos/glfw-3.3.6.bin.MACOS/include",
		}

		libdirs {
			"/usr/local/lib",
			"%{wks.location}/Sunrise/vendor/bin/glfw/macos/glfw-3.3.6.bin.MACOS/lib-universal",
		}

		links {
			"libvulkan.1.dylib",
			"libglfw.3.dylib"
		}

		--https://vulkan.lunarg.com/doc/view/1.2.148.1/windows/spirv_toolchain.html
		glslCompilerLoc = "/usr/local/bin/glslangValidator"

		postbuildcommands {
			("{COPY} %{wks.location}/Sunrise/vendor/bin/glfw/macos/glfw-3.3.6.bin.MACOS/lib-universal/* ../bin/" .. outputdir .. "/%{prj.name}/"),
		}


	filter "configurations:Debug"
		defines "SR_DEBUG"
		runtime "Debug"
		symbols "on"

		libdirs {
			"%{wks.location}/Sunrise/vendor/marl-main/marl-main/build/Debug",
		}

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
		  ("" .. glslCompilerLoc .. (" -V %{file.relpath} -o ../bin/" .. outputdir .. "/%{prj.name}/shaders/%{file.name}.spv -g"))
	   }

	   -- One or more outputs resulting from the build (required)
	   buildoutputs {("../bin/" .. outputdir .. "/%{prj.name}/shaders/%{file.name}.spv")}

	   -- One or more additional dependencies for this build command (optional)
	   --buildinputs { 'path/to/file1.ext', 'path/to/file2.ext' }

