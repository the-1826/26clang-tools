#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_STRINGS 100
#define STRING_LENGTH 17

int main(int argc, char *argv[]) {
    srand(time(NULL));
    FILE *stringFile = fopen("memeinsert.cfg", "r");
    if (stringFile == NULL) {
        fprintf(stderr, "Can't open memeinsert.cfg file\n");
        return 1;
    }
    char strings[MAX_STRINGS][STRING_LENGTH];
    int stringCount = 0, totalStrings = 0;
    while (totalStrings < MAX_STRINGS) {
        char temp[STRING_LENGTH];
        fgets(temp, STRING_LENGTH, stringFile);
        if (feof(stringFile))
            break;
        for (int i = 0; i < strlen(temp); i++) {
            if (!(temp[i] >= 33 && temp[i] <= 126) && temp[i] != ' ') {
                temp[i] = ' ';
            }
        }
        strcpy(strings[stringCount], temp);
        strings[stringCount][strcspn(strings[stringCount], "\n")] = 0;
        stringCount++;
        totalStrings++;
    }
    fclose(stringFile);
    if (stringCount == 0) {
        fprintf(stderr, "Can't read any values from memeinsert.cfg.\n");
        return 2;
    }
    for (int i = 1; i < argc; i++) {
        char null = 0;
        int randomIndex = rand() % stringCount;
        const char* selectedString = strings[randomIndex];
        char fname[60], drive[100], ext[5], result_name[60];
        _splitpath(argv[i], drive, drive, fname, ext);
        snprintf(result_name, sizeof(result_name), "%s%s", fname, ext);
        FILE* sourcefile = fopen(result_name, "rb+");
        if (sourcefile != NULL) {
            fseek(sourcefile, 32, SEEK_SET);
            fwrite(&null, sizeof(char), 16, sourcefile);
            fseek(sourcefile, 32, SEEK_SET);
            fwrite(selectedString, 1, strlen(selectedString), sourcefile);
            fclose(sourcefile);
            printf("Successfully converted file %s...\n", result_name);
        } else {
            fprintf(stderr, "Can't save file %s\n", result_name);
        }
    }
    printf("Converting finished!\n");
    return 0;
}
