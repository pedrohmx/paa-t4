-- premake5
workspace "paa"
configurations { "debug", "release" }

project "t4"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++latest"
    targetdir "bin/%{cfg.buildcfg}"
    includedirs { "include" }
    files { "src/**.cpp", "src/**.hpp" }
    filter "configurations:debug"
        defines { "DEBUG" }
        symbols "On"
    filter "configurations:release"
        defines { "NDEBUG" }
        optimize "On"
