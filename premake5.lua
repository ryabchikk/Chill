workspace "Chill"
    architecture "x64"
    startproject "App"
    configurations
    {
        "Debug",
        "Release",
        "Dist"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
    IncludeDir["GLFW"] = "Chill/vendor/GLFW/include"
    IncludeDir["Glad"] = "Chill/vendor/Glad/include"
    IncludeDir["ImGui"] = "Chill/vendor/imgui"
    IncludeDir["glm"] = "Chill/vendor/glm"
    IncludeDir["stb_image"] = "Chill/vendor/stb_image"

include "Chill/vendor/GLFW"
include "Chill/vendor/Glad"
include "Chill/vendor/imgui"

project "Chill"
    location "Chill"
    --kind "SharedLib"
    kind "StaticLib"
    language "C++"
    cppdialect "C++20"
    staticruntime "on"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    pchheader "chpch.h"
    pchsource "Chill/src/chpch.cpp"

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
        "%{prj.name}/vendor/glm/glm/**.hpp",
        "%{prj.name}/vendor/glm/glm/**.inl",
        "%{prj.name}/vendor/stb_image/**.h",
        "%{prj.name}/vendor/stb_image/**.cpp"
    }

    defines
    {
        "_CRT_SECURE_NO_WARNINGS"
    }

    includedirs
    {
		"%{prj.name}/src",
        "%{prj.name}/vendor/spdlog/include",
 		"%{IncludeDir.GLFW}",
        "%{IncludeDir.Glad}",
        "%{IncludeDir.ImGui}",
        "%{IncludeDir.glm}",
 		"%{IncludeDir.stb_image}"
    }

    links 
 	{ 
 		"GLFW",
        "Glad",
        "ImGui",
 		"opengl32.lib"
 	}

    filter "system:windows"
        --cppdialect "C++20"
        --staticruntime "On"
        systemversion "latest"

        defines
        {
            "CH_PLATFORM_WINDOWS",
            "CH_BUILD_DLL",
 			"GLFW_INCLUDE_NONE"
        }
    
    filter "configurations:Debug"
        defines "CH_DEBUG"
        buildoptions "/MDd"
        symbols "On"

    filter "configurations:Release"
        defines "CH_RELEASE"
        buildoptions "/MD"
        optimize "On"
    
    filter "configurations:Dist"
        defines "CH_DIST"
        buildoptions "/MD"
        optimize "On"

    filter {"system:windows", "configurations:Release"}
            buildoptions "/utf-8"
        
    filter {"system:windows", "configurations:Debug"}
            buildoptions "/utf-8"

project "App"
        location "App"
        kind "ConsoleApp"
        --staticruntime "off"
        language "C++"
        cppdialect "C++20"
        staticruntime "on"

        targetdir ("bin/" .. outputdir .. "/%{prj.name}")
        objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

        files
        {
            "%{prj.name}/src/**.h",
            "%{prj.name}/src/**.cpp"
        }
    
        includedirs
        {
            "Chill/vendor/spdlog/include",
            "Chill/src",
            "%{IncludeDir.glm}",
            "Chill/vendor"
        }
    
        links
        {
            "Chill"
        }
        
        filter "system:windows"
            --cppdialect "C++20"
            --staticruntime "On"
            systemversion "latest"
    
            defines
            {
                "CH_PLATFORM_WINDOWS",
            }

            --postbuildcommands 
            --{
            --    ("{COPY} ../bin/" .. outputdir .. "/Chill/Chill.dll ../bin/" .. outputdir .. "/App")
            --}

        filter "configurations:Debug"
            defines "CH_DEBUG"
            buildoptions "/MDd"
            symbols "On"
    
        filter "configurations:Release"
            defines "CH_RELEASE"
            buildoptions "/MD"
            optimize "On"
        
        filter "configurations:Dist"
            defines "CH_DIST"
            buildoptions "/MD"
            optimize "On"

        filter {"system:windows", "configurations:Release"}
            buildoptions "/utf-8"
        
        filter {"system:windows", "configurations:Debug"}
            buildoptions "/utf-8"