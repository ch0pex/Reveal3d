set(SOURCES
        render/renderer.cpp
        render/camera.cpp
        common/timer.cpp
        core/scene.cpp
        core/geometry.cpp
        core/transform.cpp
        render/light.cpp
        config/config.cpp
        input/input.cpp
)

message("Renderer: ${GFX}")
message("Window: ${PLAT}")
aux_source_directory(graphics/${GFX} GRAPHICS)
aux_source_directory(graphics/${GFX}/resources GRAPHICS)
aux_source_directory(window/${PLAT} PLATFORM)
#message(Graphics Sources: ${GRAPHICS})
#message(Platform Sources: ${PLATFORM})

include_directories(PUBLIC .)
include_directories(PUBLIC math/${PLAT})
add_library(Engine STATIC ${SOURCES} ${GRAPHICS} ${PLATFORM})
target_include_directories(Engine PUBLIC math/${PLAT})


if(D3D12)
    target_compile_definitions(Engine PRIVATE "UNICODE" "_UNICODE")
    target_link_libraries(Engine PRIVATE d3d12 dxgi d3dcompiler)
else()

endif()