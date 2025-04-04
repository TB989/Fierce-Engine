project "001_BuildScripts"
	kind "None"
	location "%{wks.location}/%{prj.name}/"

	files
	{
		"%{wks.location}/%{prj.name}/src/**.lua"
	}