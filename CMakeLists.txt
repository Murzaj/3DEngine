cmake_minimum_required(VERSION 3.20)
project(3DEngineProject)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17)

set(SDL2_DEV_DIR "${CMAKE_SOURCE_DIR}/vendor/SDL2-2.32.4")
set(SDL2_MIXER_DEV_DIR "${CMAKE_SOURCE_DIR}/vendor/SDL2_mixer-2.8.1")
set(SDL_ARCH "x64") 
if(NOT EXISTS "${SDL2_DEV_DIR}/include/SDL.h")
    message(FATAL_ERROR "Nie znaleziono SDL.h w ${SDL2_DEV_DIR}/include. SprawdŸ œcie¿kê i strukturê katalogów SDL2.")
endif()
if(NOT EXISTS "${SDL2_DEV_DIR}/lib/${SDL_ARCH}/SDL2.lib")
    message(FATAL_ERROR "Nie znaleziono SDL2.lib w ${SDL2_DEV_DIR}/lib/${SDL_ARCH}. SprawdŸ œcie¿kê, architekturê (${SDL_ARCH}) i strukturê katalogów SDL2.")
endif()
if(NOT EXISTS "${SDL2_MIXER_DEV_DIR}/include/SDL_mixer.h")
    message(FATAL_ERROR "Nie znaleziono SDL_mixer.h w ${SDL2_MIXER_DEV_DIR}/include. SprawdŸ œcie¿kê i strukturê katalogów SDL2_mixer.")
endif()
if(NOT EXISTS "${SDL2_MIXER_DEV_DIR}/lib/${SDL_ARCH}/SDL2_mixer.lib")
    message(FATAL_ERROR "Nie znaleziono SDL2_mixer.lib w ${SDL2_MIXER_DEV_DIR}/lib/${SDL_ARCH}. SprawdŸ œcie¿kê, architekturê (${SDL_ARCH}) i strukturê katalogów SDL2_mixer.")
endif()

FILE(GLOB_RECURSE INCLUDE include/*.hpp include/*.h include/ext/*.h)
FILE(GLOB_RECURSE SOURCES src/*.cpp)


set(ASSETS_SOURCE_DIR "${CMAKE_SOURCE_DIR}/assets")
set(ASSETS_OUTPUT_DIR "${CMAKE_BINARY_DIR}")

# Replace backslashes with forward slashes in PATH
if(DEFINED ENV{PATH})
    string(REPLACE "\\" "/" CLEANED_PATH $ENV{PATH})
    set(ENV{PATH} "${CLEANED_PATH}")
endif()

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(GLEW REQUIRED)
find_package(glm REQUIRED)



add_executable(3DEngine 
  ${PROJECT_SOURCE_FILES}
  ${SOURCES}
  ${INCLUDE}
  ${RESOURCE_FILE} 
 "src/game/GameScene.cpp" "src/game/PlayerController.cpp"     "src/game/Spike.cpp" "src/SolidPlane3D.cpp" "src/game/MenuScene.cpp" "src/SoundHandler.cpp")

target_include_directories(3DEngine PRIVATE ${OPENGL_INCLUDE_DIR})
target_include_directories(3DEngine PRIVATE include/)
target_include_directories(3DEngine PRIVATE "${SDL2_DEV_DIR}/include")
target_include_directories(3DEngine PRIVATE "${SDL2_MIXER_DEV_DIR}/include")


# Add a custom target to copy assets
add_custom_target(copy_assets ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${ASSETS_SOURCE_DIR} ${ASSETS_OUTPUT_DIR}
    COMMENT "Copying assets to the build directory"
)
# Ensure the copy happens before the main build
add_dependencies(3DEngine copy_assets)

target_link_libraries(3DEngine PRIVATE
    GLEW::glew
    OpenGL::GL
    GLEW::glew
    GLUT::GLUT
    glm::glm-header-only
   "${SDL2_DEV_DIR}/lib/${SDL_ARCH}/SDL2main.lib"
    "${SDL2_DEV_DIR}/lib/${SDL_ARCH}/SDL2.lib"
    "${SDL2_MIXER_DEV_DIR}/lib/${SDL_ARCH}/SDL2_mixer.lib"
)

if(EXISTS "${ASSETS_SOURCE_DIR}")
    add_custom_target(copy_project_assets ALL
        COMMAND ${CMAKE_COMMAND} -E copy_directory "${ASSETS_SOURCE_DIR}" "${ASSETS_OUTPUT_DIR}"
        COMMENT "Copying project assets to the build assets directory"
    )
    add_dependencies(3DEngine copy_project_assets)
else()
    message(WARNING "Katalog zasobów (assets) nie zosta³ znaleziony w ${ASSETS_SOURCE_DIR}")
endif()
set(SDL2_DLL_PATH "${SDL2_DEV_DIR}/lib/${SDL_ARCH}/SDL2.dll")
set(SDL2_MIXER_DLL_PATH "${SDL2_MIXER_DEV_DIR}/lib/${SDL_ARCH}/SDL2_mixer.dll")
set(RESOURCE_FILE "${CMAKE_SOURCE_DIR}/resources.rc")

set(SDL2_MIXER_DEPENDENCY_DLL_FILENAMES
    "libgme.dll"      
    "libogg-0.dll"   
    "libopus-0.dll"        
    "libopusfile-0.dll"      
    "libwavpack-1.dll"     
    "libxmp.dll"   

)

macro(COPY_DLL_IF_EXISTS DLL_FULL_PATH TARGET_EXE_NAME DLL_COMMENT)
    if(EXISTS "${DLL_FULL_PATH}")
        add_custom_command(TARGET ${TARGET_EXE_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${DLL_FULL_PATH}"
            $<TARGET_FILE_DIR:${TARGET_EXE_NAME}> 
            COMMENT "${DLL_COMMENT}"
        )
    else()
        message(WARNING "Nie znaleziono pliku DLL: ${DLL_FULL_PATH} do skopiowania.")
    endif()
endmacro()

COPY_DLL_IF_EXISTS("${SDL2_DLL_PATH}" 3DEngine "Copying SDL2.dll to output directory")
COPY_DLL_IF_EXISTS("${SDL2_MIXER_DLL_PATH}" 3DEngine "Copying SDL2_mixer.dll to output directory")

foreach(DLL_FILENAME ${SDL2_MIXER_DEPENDENCY_DLL_FILENAMES})
    set(FULL_DLL_DEP_PATH "${SDL2_MIXER_DEV_DIR}/lib/${SDL_ARCH}/${DLL_FILENAME}")
    COPY_DLL_IF_EXISTS("${FULL_DLL_DEP_PATH}" 3DEngine "Copying ${DLL_FILENAME} to output directory")
endforeach()


set_property(TARGET 3DEngine PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/Debug")