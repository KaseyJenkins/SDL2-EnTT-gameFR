cmake_minimum_required(VERSION 3.20)
project(newGameTrial
        VERSION 0.1.0        
)

set(CMAKE_CXX_STANDARD 17)

find_package(SDL2 REQUIRED)

add_subdirectory(libs/tinytmx)

add_executable(gameTrial
        src/main.cpp
        src/core/app.cpp
        src/core/game.cpp
        src/core/factories.cpp

        src/systems/movement.cpp
        src/systems/render.cpp
        src/systems/tileRender.cpp
        src/systems/enemySlimeRender.cpp
        src/systems/enemySliderPosition.cpp
        src/systems/blobMenuRender.cpp
        src/systems/blobMenuRender.hpp
        src/systems/blobMenuPosition.cpp
        src/systems/blobMenuPosition.hpp


        src/util/texture_manager.cpp
        src/util/input_handler.cpp
        src/util/collision.hpp
        src/util/collision_manager.cpp
        src/util/camera.cpp
        src/util/cute_c2.h

        src/util/gameStates/GameState.hpp
        src/util/gameStates/MainMenuState.cpp
        src/util/gameStates/MainMenuState.hpp
        src/util/gameStates/PlayState.cpp
        src/util/gameStates/PlayState.hpp
        src/util/gameStates/GameStateMachine.cpp
        src/util/gameStates/GameStateMachine.hpp

        src/util/font/font.cpp
        src/util/font/font.hpp

        )

target_include_directories(gameTrial PRIVATE
        ${SDL2_INCLUDE_DIRS}
        libs
        src
        )

target_link_libraries(gameTrial PRIVATE
        ${SDL2_LIBRARIES}
        tinytmx::tinytmx
        )

IF (CMAKE_BUILD_TYPE MATCHES Release)
    target_link_libraries(gameTrial PRIVATE
            -mwindows
            )
ENDIF ()
