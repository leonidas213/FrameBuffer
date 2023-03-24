add_library(framebuffer
        frameBuffer.cpp
        
)

target_link_libraries(framebuffer
pico_stdlib
        )
target_include_directories (framebuffer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})