#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char *argv[]){

    if (argc != 2) {
        printf("Неверное число аргументов");
    }

    FILE *file;
    file = fopen(argv[1], "w");

    if (file == NULL){
        printf("Ошибка открытия файла");
    }

    for(float x = 0.0; x < 3.1; x += 0.1){
        float y = sin(x);
        float z = tan(x);
        fprintf(file, "x=%.1f   sin(x)=%.3f    tg(x)=%.3f\n",x,y,z);
    }

    if (fclose(file) != 0){
        printf("Ошибка быхода");
    }
}
//gcc lab4.c -lm
//./a.out lab4.txt
//cat lab4.txt
