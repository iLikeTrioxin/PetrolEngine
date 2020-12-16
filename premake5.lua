require('vstudio')

workspace "Engine"
	architecture "x86_64"
	startproject "Engine"
	
	configurations
	{
		"Debug",
		"Release",
		"Distribution"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
include "Engine"