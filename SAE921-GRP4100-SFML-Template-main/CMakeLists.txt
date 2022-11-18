# CMakeList.txt : fichier projet CMake de niveau supérieur, effectuez une configuration globale
# et incluez les sous-projets ici.
#
cmake_minimum_required (VERSION 3.8)

# Solution
project ("SAE921-GRP4100-SFML")

# Each sub-project
set(EXECUTABLE_CUSTOM_NAME "00-Starter")
add_subdirectory ("00-Starter")

set(EXECUTABLE_CUSTOM_NAME "00-WhiteWindow")
add_subdirectory ("00-WhiteWindow")

set(EXECUTABLE_CUSTOM_NAME "00-FormativeCanvas")
add_subdirectory ("00-FormativeCanvas")

set(EXECUTABLE_CUSTOM_NAME "01-DrawableZelda")
add_subdirectory ("01-DrawableZelda")

set(EXECUTABLE_CUSTOM_NAME "02-Anim")
add_subdirectory ("02-Anim")

set(EXECUTABLE_CUSTOM_NAME "03-Sound")
add_subdirectory ("03-Sound")

set(EXECUTABLE_CUSTOM_NAME "04-CasseBrick")
add_subdirectory ("04-CasseBrick")

set(EXECUTABLE_CUSTOM_NAME "10-HelloBox2D")
add_subdirectory ("10-HelloBox2D")

set(EXECUTABLE_CUSTOM_NAME "11-SpaceShooter")
add_subdirectory ("11-SpaceShooter")

set(EXECUTABLE_CUSTOM_NAME "12-Bouncing")
add_subdirectory ("12-Bouncing")