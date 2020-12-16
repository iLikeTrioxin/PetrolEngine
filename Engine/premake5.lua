project "Engine"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"
	
	files 
	{
		"Source/**.cpp",
		"Source/**.h"
	}
	
	targetdir ("%{wks.location}/bin/"    .. outputdir .. "/%{prj.name}")
	objdir    ("%{wks.location}/bin/obj" .. outputdir .. "/%{prj.name}")
	
	pchheader "hzpch.h"
	pchsource "src/hzpch.cpp"
	
	filter "configurations:Debug"
		defines "DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "RELEASE"
		runtime "Release"
		optimize "on"
 
	filter "configurations:Distribution"
		defines "DISTRIBUTION"
		runtime "Release"
		optimize "on"