cmake_minimum_required(VERSION 3.16)
project(Football11v11Game)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find SFML
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

# Source files
set(SOURCES
    src/main.cpp
    src/Game.cpp
    src/Team.cpp
    src/Player.cpp
    src/Ball.cpp
)

set(HEADERS
    src/Game.h
    src/Team.h
    src/Player.h
    src/Ball.h
)

# Create executable
add_executable(Football11v11 ${SOURCES} ${HEADERS})

# Link SFML libraries
target_link_libraries(Football11v11 PRIVATE sfml-graphics sfml-window sfml-system)

# Set output directory
set_target_properties(Football11v11 PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)
