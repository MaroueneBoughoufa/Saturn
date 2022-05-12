import os
import subprocess
import platform

from SetupPython import PythonConfiguration as PythonRequirements

# Make sure everything we need for the setup is installed
PythonRequirements.Validate()

from SetupPremake import PremakeConfiguration as PremakeRequirements

os.chdir('./../')
premakeInstalled = PremakeRequirements.Validate()

print("\nUpdating submodules...")
subprocess.call(["git", "submodule", "update", "--init", "--recursive"])

if (premakeInstalled):
    if platform.system() == "Windows":
        print("\nRunning Premake")
        subprocess.call([os.path.abspath("./premake.bat"),  "vs2019", "nopause"])
        print("\nSetup completed!")
    if platform.system() == "Linux":
        print("\nRunning Premake")
        subprocess.call([os.path.abspath("./premake.bat "), "gmake2", "nopause"])
        print("\nSetup completed!")
else:
    print("Saturn requires Premake to generate project files.")
