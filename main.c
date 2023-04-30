#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

int main(int argc, char *argv[]) {
    system("title Language Chronicles");
    system("mode con cols=50 lines=8");
    setlocale(0,"");
    int language = GetSystemDefaultLangID();
    if (language != 1049) {
        printf("Language Chronicles 1.1 opened.\n");
        printf("Opening game ISO...\n");
    }
    else {
        printf("Language Chronicles 1.1 открыт.\n");
        printf("Открывается образ игры...\n");

    }
    char fname[60], drive[100], ext[5], result_name[50];
    _splitpath(argv[1], drive, drive, fname, ext);
    snprintf(result_name, sizeof result_name, "%s%s", fname, ext);
    FILE *file = fopen(result_name, "rb+");
    if (file != NULL) {
        if (language != 1049)
            printf("ISO opened.\n");
        else
            printf("Образ открыт.\n");
        char buffer[4], found = 0, changed = 0, russian[6] = {"GERMAN"}, english[6] = {"FRENCH"};
        for (unsigned long i = 73000; i <= 75000; i++) {
            fseek(file, i - 5, SEEK_SET);
            fread(&buffer[0], sizeof(char), 1, file);
            fseek(file, i - 4, SEEK_SET);
            fread(&buffer[1], sizeof(char), 1, file);
            fseek(file, i - 3, SEEK_SET);
            fread(&buffer[2], sizeof(char), 1, file);
            fseek(file, i - 2, SEEK_SET);
            fread(&buffer[3], sizeof(char), 1, file);
            fseek(file, i - 1, SEEK_SET);
            fseek(file, i, SEEK_SET);
            if ((buffer[0] == 'G') && (buffer[1] == 'E') && (buffer[2] == 'R') && (buffer[3] == 'M')) {
                if (!found) {
                    found = 1;
                    if (language != 1049) {
                        printf("Current language: Russian.\n");
                        printf("Changing language to English...\n");
                    }
                    else  {
                        printf("Текущий язык: русский.\n");
                        printf("Язык изменяется на английский...\n");
                    }
                }
                fseek(file, i - 5, SEEK_SET);
                fwrite(&english[0], sizeof(char), 1, file);
                fseek(file, i - 4, SEEK_SET);
                fwrite(&english[1], sizeof(char), 1, file);
                fseek(file, i - 3, SEEK_SET);
                fwrite(&english[2], sizeof(char), 1, file);
                fseek(file, i - 2, SEEK_SET);
                fwrite(&english[3], sizeof(char), 1, file);
                fseek(file, i - 1, SEEK_SET);
                fwrite(&english[4], sizeof(char), 1, file);
                fseek(file, i, SEEK_SET);
                fwrite(&english[5], sizeof(char), 1, file);
                changed = 1;
                continue;
            }
            if ((buffer[0] == 'F') && (buffer[1] == 'R') && (buffer[2] == 'E') && (buffer[3] == 'N')) {
                if (!found) {
                    found = 1;
                    if (language != 1049) {
                        printf("Current language: English.\n");
                        printf("Changing language to Russian...\n");
                    }
                    else  {
                        printf("Текущий язык: английский.\n");
                        printf("Язык изменяется на русский...\n");
                    }
                }
                fseek(file, i - 5, SEEK_SET);
                fwrite(&russian[0], sizeof(char), 1, file);
                fseek(file, i - 4, SEEK_SET);
                fwrite(&russian[1], sizeof(char), 1, file);
                fseek(file, i - 3, SEEK_SET);
                fwrite(&russian[2], sizeof(char), 1, file);
                fseek(file, i - 2, SEEK_SET);
                fwrite(&russian[3], sizeof(char), 1, file);
                fseek(file, i - 1, SEEK_SET);
                fwrite(&russian[4], sizeof(char), 1, file);
                fseek(file, i, SEEK_SET);
                fwrite(&russian[5], sizeof(char), 1, file);
                changed = 1;
            }
        }
        if (changed == 1) {
            if (language != 1049)
                printf("Language changed!\n");
            else
                printf("Язык изменен!\n");
        }
        else {
           if (language != 1049)
                printf("Language wasn't changed.\n");
            else
                printf("Язык не был изменен.\n");
        }
    }
    else
        if (language != 1049)
            printf("Error opening ISO.\n");
        else
            printf("Ошибка открытия образа.\n");
    system("pause");
}
