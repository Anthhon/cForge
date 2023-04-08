# cForge
cForge is a lightweight library designed to help you build scalable and efficient C applications. It is similar to Rust's cargo, providing a set of tools for managing your C projects.

One common challenge when starting a new C project is the tedious process of creating a project structure, organizing files, and configuring project settings such as CMakeLists.txt. Additionally, it's easy to forget to initialize a new project with git, which can cause headaches down the line.

## Requirements
- gcc compiler
- make utility

## Installation

```bash
git clone https://github.com/Anthhon/cForge.git
or
git clone git@github.com:Anthhon/cForge.git
mkdir build
cd build
cmake .. && make
```
If you want to install the project in your system, use this command:
```bash
make install
```

## File Structure
The project is structured as follows:

-   `src/`: Source code directory
    -   `builder.c`: Implementation of the build system
    -   `common.c`: Implementation of common functions and values
    -   `main.c`: Entry point for the program and argument parser
-   `include/`: Header file directory
    -   `builder.h`: Header file for the build system
    -   `common.h`: Header file for common functions
-   `Makefile`: Makefile for building the project

## Roadmap
- [X] Create a boilerplate folder project folder
- [X] Create a boilerplate project basic files
- [X] Initiate git project
- [X] Implement arguments to change project definitions
- [ ] Implement testing command
- [ ] Implement build system
- [ ] Implement flags for build system
- [ ] Implement code formatting
- [ ] Implement code profiling

## License
This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
