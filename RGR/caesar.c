#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "caesar.h"

void caesar(char *text, int key) {
    for (int i=0; text[i];){
        unsigned char f = (unsigned char)text[i];
        unsigned char s = (unsigned char)text[i+1];

        if ((f == 0xD0 && s >= 0x90 && s <= 0xBF && s != 0x81)||(f == 0xD1 && s >= 0x80 && s <= 0x8F && s != 0x91)){
            int upper =(f == 0xD0 && s <= 0xAF);
            int index;

            if (upper) {
                index = s - 0x90;
                index = (index+ key+32)%32;
                text[i] = 0xD0;
                text[i+1] = 0x90 + index;
            } else {
                if (f == 0xD0) {
                    index = s - 0xB0;
                } else {
                    index = s - 0x80 + 16;
                }
                index = (index + key + 32) % 32;

                if (index < 16) {
                    text[i] = 0xD0;
                    text[i+1] = 0xB0 + index;
                } else {
                    text[i] = 0xD1;
                    text[i+1] = 0x80 + (index - 16);
                }
            }
            i+=2;
        } else {
            i++;
        }
    }
}

void encrypt(char *text, int key){
    caesar(text, key);
}

void decrypt(char *text, int key){
    caesar(text, -key);
}

char *read_file(const char *filename) {
    FILE *f = fopen(filename, "rb");
    if (!f) return NULL;

    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    rewind(f);

    char *buffer = malloc(size + 1);
    if (!buffer) {
        fclose(f);
        return NULL;
    }

    fread(buffer, 1, size, f);
    buffer[size] = '\0';
    fclose(f);
    return buffer;
}

void write_file(const char *filename, const char *text) {
    FILE *f = fopen(filename, "wb");
    if (f) {
        fwrite(text, 1, strlen(text), f);
        fclose(f);
    }
}
