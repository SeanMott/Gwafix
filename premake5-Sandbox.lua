workspace "Gwafix"
    architecture "x86"
    startproject "Sandbox"

    configurations
    {
        "Debug",
        "Release",
        "Dist"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

includeDir = {}
includeDir["GLFW"] = "Library/GLFW/Include"
includeDir["Glad"] = "Library/Glad/include"
includeDir["stb"] = "Library/stb"
includeDir["glm"] = "Library/cglm/include/cglm"

--includes the premake files
include "Library/GLFW"
include "Library/Glad"
include "Library/stb"

--Gwafix Lib
project "Gwafix"
    location "Gwafix"
    kind "StaticLib"
    language "C"

    targetdir ("bin/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}/%{prj.name}")
    objdir ("bin-obj/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}/%{prj.name}")

    pchheader "gpch.h"
    pchsource "%{prj.name}/src/gpch.c"

    files 
    {
        "%{prj.name}/includes/**.h",
        "%{prj.name}/src/**.c",
        --exclude all platform code
    }
    
    includedirs
    {
        "%{includeDir.Glad}",
        "%{includeDir.GLFW}",
        --"%{includeDir.glm}",
        "%{includeDir.stb}",
        "%{prj.name}/includes"
    }
    
    links
    {
        "StbImage",
        "Glad",
        "GLFW",
        "opengl32.lib"
    }

    defines
    {
        "GLFW_STATIC",
        "GLFW_INCLUDE_NONE",
        "GLM_FORCE_RADIANS",
        "GLM_FORCE_DEPTH_ZERO_TO_ONE",
    }

    filter "system:windows"
        staticruntime "On"
        systemversion "latest"
    
        defines
        {
            "Window_Build",
            "Desktop_Build"
        }

        files 
        {
            --"%{prj.name}/src/**.h",
            --"%{prj.name}/src/**.c",
            --include window platform code
        }
    
    filter "configurations:Debug"
        defines "GWAFIX_DEBUG"
        symbols "On"
    
    filter "configurations:Release"
        defines "GWAFIX_RELEASE"
        optimize "On"
    
    filter "configurations:Dist"
        defines "GWAFIX_DIST"
        optimize "On"

--Sandbox for Gwafix
project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    language "C"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-obj/" .. outputdir .. "/%{prj.name}")


    files 
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.c",
    }
    
    includedirs
    {
        "%{includeDir.Glad}",
        "%{includeDir.GLFW}",
        "%{includeDir.glm}",
        "%{includeDir.stb}",
        "%{prj.name}/src",
        "Gwafix/includes"
    }
    
    links
    {
        "Gwafix"
    }

    defines
    {
        "GLFW_STATIC",
        "GLFW_INCLUDE_NONE",
        "GLM_FORCE_RADIANS",
        "GLM_FORCE_DEPTH_ZERO_TO_ONE",
    }

    filter "system:windows"
        staticruntime "On"
        systemversion "latest"
    
        defines
        {
            "Window_Build",
            "Desktop_Build"
        }
    
    filter "configurations:Debug"
        defines "GWAFIX_DEBUG"
        symbols "On"
    
    filter "configurations:Release"
        defines "GWAFIX_RELEASE"
        optimize "On"
    
    filter "configurations:Dist"
        defines "GWAFIX_DIST"
        optimize "On"