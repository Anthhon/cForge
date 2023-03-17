cmake_minimum_required(VERSION 3.22.1)

# Default project config
project(proj-name VERSION X.0) # Project name and version
add_executable(proj-name code-file.c) # Defines the executable name
target_link_libraries(proj-name libs) # Include some libs if needed
install(TARGETS proj-name DESTINATION bin) # Tells where to store the binarie
