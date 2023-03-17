cmake_minimum_required(VERSION 3.22.1)

# Default project config
project(cforge VERSION 0.1) # Project name and version
add_executable(cforge src/main.c) # Defines the executable name
# target_link_libraries(cforge libs) # Include some libs if needed
install(TARGETS cforge DESTINATION bin) # Tells where to store the binarie
