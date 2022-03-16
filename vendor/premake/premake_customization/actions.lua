newaction {
	trigger = "delete",
	description = "Remove all binaries and intermediate binaries, and project files.",
	execute = function()
		print("Removing binaries...")
		os.rmdir("./bin")
		print("Removing intermediate binaries...")
		os.rmdir("./bin-int")
		print("Removing project files...")
		os.rmdir("./.vs")
		os.remove("**Makefile")
		os.remove("**.mk")
		os.remove("**.workspace")
		os.remove("**.project")
		os.remove("**.sln")
		os.remove("**.vcxproj")
		os.remove("**.vcxproj.filters")
		os.remove("**.vcxproj.user")
		print("Done.")
	end
}

newaction {
	trigger = "clean",
	description = "Remove all binaries and intermediate binaries, and project files.",
	execute = function()
		print("Removing binaries...")
		os.rmdir("./bin")
		print("Removing intermediate binaries...")
		os.rmdir("./bin-int")
		print("Done.")
	end
}
