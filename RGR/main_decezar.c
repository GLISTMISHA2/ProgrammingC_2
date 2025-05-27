#include <stdio.h>
#include <locale.h>
#include "caesar.h"

int main(int argc, char *argv[]) {
    setlocale(LC_ALL, "ru_RU.UTF-8");

    if (argc != 4) {
        printf("Использование: %s <входной_файл> <выходной_файл> <ключ>\n", argv[0]);
        return 1;
    }

    char *in = read_file(argv[1]);
    if (!in) {
        printf("Ошибка чтения файла: %s\n", argv[1]);
        return 1;
    }

    int key = atoi(argv[3]);

    printf("Зашифрованный текст:\n %s\n", in);

    decrypt(in, key);
    printf("Расшифрованный текст:\n %s\n", in);

    write_file(argv[2], in);

    free(in);
    return 0;
}
