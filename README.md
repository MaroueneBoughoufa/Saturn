# Saturn
A 2D game engine (currently a WIP).

# Build instructions

### Prerequisites

- You need to have Git installed ...

- You need to have Python 3.8 or above ...

- You need Visual-Studio 2017 or above ...

1. Download the repository:

    ```sh
    git clone --recursive https://github.com/MaroueneBoughoufa/Saturn.git
    ```

    Make sure you add the `--recursive` to fetch all the submodules.

    If the repository was cloned non-recursively previously, use ` git submodule update --init ` to clone the submodules.

2. Configure dependencies

    1. Run the [setup.bat](./scripts/setup.bat) file found in the `scripts` folder. This will download the required prerequisites for the project if they are not present yet.
    2. After that run the [Win-GenProject-vs2019.bat](./scripts/Win-GenProject-vs2019.bat) script file to generate a visual studio 2019 project.

3. Run the build script:

	- Simply run [build.bat](./scripts/build.bat) to generate binaries.

If changes are made, or if you want to regenerate project files, rerun the [Win-GenProject-vs2019.bat](./scripts/Win-GenProject-vs2019.bat) script file found in `scripts` folder.
