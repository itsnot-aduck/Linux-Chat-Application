#set the target
add_executable(MyApp app.c)

# Set the output directory for the executable 
set_target_properties(MyApp PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
    )

# Link the executable to common library
target_link_libraries(MyApp common)
# Ensure the include the headers
target_include_directories(MyApp PRIVATE ../common/inc)