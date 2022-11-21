#include "stdio.h"

void red(){
    printf("\033[1;31m");
}
void yellow(){
    printf("\033[1;33m");
}
void green(){
    printf("\033[1;32m");
}
void cyan(){
    printf("\033[1;36m");
}
void blue(){
    printf("\033[1;34m");
}
void purple(){
    printf("\033[1;35m");
}
void black(){
    printf("\033[0;30m");
}
void resetColor (){
    printf("\033[0m");
}