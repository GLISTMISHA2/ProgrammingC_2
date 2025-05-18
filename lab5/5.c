#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Toys {
    char name[64];
    int price;
    char shop[64];
} toy;

void createFile(char *filename){

    toy toyy[] = {
        {"Кукла", 100, "Детский мир"},
        {"Юла", 150, "Мир игрушек"},
        {"Машинка",200, "Ярче"},
    };

    FILE *file;
    file = fopen(filename, "wb");

    if (file == NULL){
        printf("ошибка в открытии файла");
        exit(1);
    }

    ..for(int i = 0; i < sizeof(toyy) / sizeof(toyy[0]); i++)
        fwrite(&toyy[0], sizeof(toy), 1, file);
    
    fclose(file);
}

void searchName(char *filename, char *name){
    FILE *file;
    file = fopen(filename, "rb");

    if (file == NULL){
        printf("ошибка в чтении файла");
        exit(1);
    }

    toy toyy;

    int t = 0;
    while(fread(&toyy,sizeof(toy),1,file) == 1){
        if (strcmp(toyy.name,name) == 0) {
            printf("Найденная игрушка: %s || Цена: %d || Магазин: %s\n", toyy.name, toyy.price, toyy.shop);
            t = 1;
        }
    }

    if (t == 0)
        printf("не нашлось \n");

    fclose(file);
}

void searchPrice(char *filename, int price){
    FILE *file;
    file = fopen(filename, "rb");

    if (file == NULL){
        printf("ошибка в чтении файла");
        exit(1);
    }

    toy toyy;

    int t = 0;
    while(fread(&toyy,sizeof(toy), 1, file) == 1){
        if (toyy.price == price){
            printf("Найденная игрушка: %s || Цена: %d || Магазин: %s\n", toyy.name, toyy.price, toyy.shop);
            t = 1;
        }
    }

    if (t == 0)
        printf("нету \n");

    fclose(file);
}

void searchShop(char *filename, char *shop){
    FILE *file;
    file = fopen(filename, "rb");

    if (file == NULL){
        printf("ошибка в чтении файла");
        exit(1);
    }

    toy toyy;

    int t = 0;

    while(fread(&toyy,sizeof(toy),1,file) == 1){
        if (strcmp(toyy.shop,shop) == 0) {
            printf("Найденная игрушка: %s || Цена: %d || Магазин: %s\n", toyy.name, toyy.price, toyy.shop);
            t = 1;
        }
    }


    if (t == 0)
        printf("Оценки испарились \n");

    fclose(file);
}

void choicee(char *filename, int choice){
    switch(choice){
        case 1:
            char name[64];
            printf("Введите игрушку: ");
            getchar();
            fgets(name, sizeof(name), stdin);
            name[strcspn(name, "\n")] = '\0';
            searchName(filename, name);
            break;
        case 2:
            int price;
            printf("Введите цену: ");
            scanf(" %d", &price);
            searchPrice(filename, price);
            break;
        case 3:
            char shop[64];
            printf("Введите адрес магазина: ");
            while (getchar() != '\n');
            fgets(shop, sizeof(shop), stdin);
            shop[strcspn(shop, "\n")] = '\0';
            searchShop(filename, shop);
            break;
    }
}


int main(){
    char *filename = "ToysPrice.dat";
    createFile(filename);

    int choice;
    printf("Выберите поле для поиска \n 1 - Название \n 2 - Цена \n 3 - Название магазина \n");
    scanf(" %d", &choice);
    choicee(filename, choice);
}
