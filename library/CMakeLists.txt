cmake_minimum_required(VERSION 3.21)
project(Library)

set(SOURCE_FILES
        include/Resources/Resource.h src/Resources/Resource.cpp
        include/Tiles/Tile.h src/Tiles/Tile.cpp
        include/Player.h src/Player.cpp
        include/Game.h src/Game.cpp
        include/Level.h src/Level.cpp
        include/Resources/ResourceRegistry.h src/Resources/ResourceRegistry.cpp
        include/Entities/Entity.h src/Entities/Entity.cpp
        include/Entities/Goomba.h src/Entities/Goomba.cpp
        include/Entities/PPlant.h src/Entities/PPlant.cpp
        include/Entities/EntityFactory.h src/Entities/EntityFactory.cpp
        src/Entities/Coin.cpp include/Entities/Coin.h
        include/Entities/Strategies/CollisionStrategy.h
        include/Entities/Strategies/StrategyDamagePlayer.h
        include/Entities/Strategies/StrategyChangeLevel.h
        src/Entities/Strategies/CollisionStrategy.cpp
        src/Entities/Strategies/StrategyDamagePlayer.cpp
        src/Entities/Strategies/StrategyChangeLevel.cpp)
add_library(Library ${SOURCE_FILES})

target_link_libraries(Library stb)
target_include_directories(Library PUBLIC include)

#Unit Tests section

# Check if generating Visual Studio 14 2015 project
if(MSVC)
    if(NOT BOOST_ROOT)
        set(BOOST_ROOT "C:/local/boost_1_60_0")
    endif()
    set(Boost_INCLUDE_DIR "${BOOST_ROOT}")
    set(Boost_LIBRARY_DIR "${BOOST_ROOT}/lib32-msvc-14.0")
    set(Boost_USE_STATIC_LIBS ON)
    set(Boost_USE_MULTITHREADED ON)


    if(NOT EXISTS ${Boost_LIBRARY_DIR})
        message(WARNING "Boost library requires manual installation in Windows")
        message("1) Browse: https://sourceforge.net/projects/boost/files/boost-binaries/1.60.0/")
        message("2) Download: boost_1_60_0-msvc-14.0-32.exe")
        message("3) Install into default directory: C:\\local")
        message("")
        message(FATAL_ERROR "Boost libraries not found at ${Boost_LIBRARY_DIR}")
    endif()

    find_package(Boost COMPONENTS unit_test_framework REQUIRED)

    include_directories(${Boost_INCLUDE_DIR})
    link_directories(${Boost_LIBRARY_DIR})

else()
    find_package(Boost COMPONENTS unit_test_framework REQUIRED)
endif()
#find_package(X11 REQUIRED)
#target_link_libraries(Library X11)
#

include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${Boost_INCLUDE_DIRS}
)

set(SOURCE_TEST_PLAYER_FILES
        test/master.cpp
        test/PlayerTest.cpp)

add_executable (TestPlayer ${SOURCE_TEST_PLAYER_FILES})

target_link_libraries(TestPlayer
        Library
        ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
        sfml-audio
        sfml-graphics
        sfml-system
        sfml-window)
