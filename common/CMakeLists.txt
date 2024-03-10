# Add the header files directory to the include path
include_directories(inc)

# Explicitly list the source files
set(COMMON_SOURCES
        src/app_cli.c
        src/app_socket.c)

# Create the static library from the source
add_library(common STATIC ${COMMON_SOURCES})

# Specify where the library's headers are
target_include_directories(common PUBLIC inc)