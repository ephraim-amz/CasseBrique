cmake_minimum_required(VERSION 3.23)
project(CasseBrique C)

set(CMAKE_C_STANDARD 99)

add_executable(CasseBrique main.c Joueur.c Joueur.h Bombe.c Bombe.h Map.c Map.h Menu.c Menu.h Decrementation.h Decrementation.c colors.h colors.c struct.h)