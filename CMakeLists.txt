cmake_minimum_required(VERSION 3.23)
project(CasseBrique C)

set(CMAKE_C_STANDARD 99)

add_executable(CasseBrique main.c Joueur.c Joueur.h Map.c Map.h colors.h colors.c)
