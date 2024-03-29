cmake_minimum_required (VERSION 3.8)
project(Carlos-Dungeon-Crusade VERSION 1.0)
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})
set (CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DLOGGING")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELWITHDEBINFO} -DLOGGING")

if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    find_library(SDL2_LIBRARY SDL2)
    find_library(SDL2_IMAGE_LIBRARY SDL2_image)
    find_library(SDL2_TTF_LIBRARY SDL2_ttf)
    find_library(SDL_MIXER_LIBRART SDL2_mixer)
    set(LIB_FILES 
        "${PROJECT_SOURCE_DIR}/library_binaries/lib/libSDL2.so"
        "${PROJECT_SOURCE_DIR}/library_binaries/lib/libSDL2_image.so"
        "${PROJECT_SOURCE_DIR}/library_binaries/lib/libSDL2_mixer.so"
        "${PROJECT_SOURCE_DIR}/library_binaries/lib/libSDL2_ttf.so"
        "${PROJECT_SOURCE_DIR}/library_binaries/lib/libAIL.so"
    ) 
endif()
if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    find_package(SDL2 REQUIRED PATHS ${PROJECT_SOURCE_DIR}/library_binaries)
    find_package(SDL2_IMAGE REQUIRED PATHS ${PROJECT_SOURCE_DIR}/library_binaries)
    find_package(SDL2_TTF REQUIRED PATHS ${PROJECT_SOURCE_DIR}/library_binaries)
    find_package(SDL2_MIXER REQUIRED PATHS ${PROJECT_SOURCE_DIR}/library_binaries)
    set(LIB_FILES 
        "${SDL2_LIBRARIES}"
        "${PROJECT_SOURCE_DIR}/library_binaries/lib/SDL2_image.lib"
        "${PROJECT_SOURCE_DIR}/library_binaries/lib/SDL2_mixer.lib"
        "${PROJECT_SOURCE_DIR}/library_binaries/lib/SDL2_ttf.lib"
        "${PROJECT_SOURCE_DIR}/library_binaries/lib/AIL.lib"
    ) 
endif()

include_directories(${PROJECT_SOURCE_DIR}/library_binaries/include)

file(GLOB DLLS "library_binaries/bin/*.dll")
set(DESTINATIONS Release Debug MinSizeRel RelWithDebInfo)
foreach(DEST ${DESTINATIONS})
  file(COPY ${DLLS} DESTINATION "${CMAKE_CURRENT_SOURCE_DIR}/build/${DEST}")
endforeach()
file(GLOB AI "library_binaries/Debug/bin/AIL.dll")
file(COPY ${AI} DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/build/Debug)

file(GLOB_RECURSE SOURCE "source/*.*")
foreach(SRC_FILE ${SOURCE})
  file(RELATIVE_PATH RELATIVE ${CMAKE_SOURCE_DIR} ${SRC_FILE})
  get_filename_component(SRC_FILE_DIR ${RELATIVE} DIRECTORY)
  source_group(${SRC_FILE_DIR} FILES ${SRC_FILE})
endforeach()

add_executable (${PROJECT_NAME} ${SOURCE})
target_link_libraries(${PROJECT_NAME} ${LIB_FILES})


option(RUN_TESTS "Run tests" OFF)
if(RUN_TESTS)
    add_library(Carlos-Dungeon-Crusade-Tests STATIC ${SOURCE})
    target_include_directories(Carlos-Dungeon-Crusade-Tests PUBLIC ${PROJECT_SOURCE_DIR}/library_binaries/include)
    target_link_libraries(Carlos-Dungeon-Crusade-Tests ${LIB_FILES})

    install(
        TARGETS Carlos-Dungeon-Crusade-Tests EXPORT AI_STATIC_APP
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        RUNTIME DESTINATION bin
        PUBLIC_HEADER DESTINATION include
        )
endif()