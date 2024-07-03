workspace "Manager"
    configurations {"Debug", "Release"}
    platforms {"Win32", "Win64"}

    filter "configurations:Debug"
        defines {"DEBUG"}
        symbols "On"

    filter "configurations:Release"
        defines {"NDEBUG"}
        optimize "On"

    filter "platforms:Win32"
        system "windows"
        architecture "x86"

    filter "platforms:Win64"
        system "windows"
        architecture "x86_64"

project "App"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"

    files {"src/nlohmann/*.hpp", "src/*.h", "src/*.cpp"}

    location "build"
    targetdir "bin/%{cfg.buildcfg}"

    includedirs {"C:/openssl-3.3.0/include"}

    links {"libssl", "libcrypto"}
    libdirs{"C:/openssl-3.3.0"}