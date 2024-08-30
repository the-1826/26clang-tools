#include <stdio.h>
#include <stdlib.h>

int stringExists(char *strArray[], int size, const char *target) {
    for (int i = 0; i < size; i++) {
        if (strcmp(strArray[i], target) == 0) {
            return 1;
        }
    }
    return 0;
}

void toUpperCase(char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        str[i] = toupper(str[i]);
    }
}

void changeLanguage(FILE *file, unsigned long position, const char *newLanguage, const char *currentLanguage) {
    fseek(file, position, SEEK_SET);
    fwrite(newLanguage, sizeof(char), strlen(newLanguage), file);
    char delta = strlen(currentLanguage) - strlen(newLanguage);
    unsigned char null_byte = 0;
    if (delta > 0)
        fwrite(&null_byte, sizeof(char), delta, file);
    printf("Changing language appearance from %s to %s...\n", currentLanguage, newLanguage);
}

int main(int argc, char *argv[]) {
    printf("Language Chronicles 1.0 opened.\n");
    if (argc < 3) {
        fprintf(stderr, "Error: No file or target name specified.\n");
        return 1;
    }
    if (strlen(argv[2]) > 11) {
        fprintf(stderr, "Target .gxt name is too big.\n");
        return 2;
    }
    printf("Opening game ISO...\n");
    char drive[100], fname[60], ext[5];
    _splitpath(argv[1], drive, drive, fname, ext);
    char result_name[50];
    snprintf(result_name, sizeof(result_name), "%s%s", fname, ext);
    FILE *file = fopen(result_name, "rb+");
    if (!file) {
        perror("Error opening file");
        return 3;
    }
    toUpperCase(argv[2]);
    const char *languages[] = {"GERMAN.GXT", "FRENCH.GXT", "ENGLISH.GXT", "SPANISH.GXT", "ITALIAN.GXT"};
    char languagesSize = sizeof(languages) / sizeof(languages[0]);
    if (!(stringExists(languages, languagesSize, argv[2]))) {
        fprintf(stderr, "Entered .gxt name is not one of these: GERMAN.GXT, FRENCH.GXT, ENGLISH.GXT, SPANISH.GXT, .ITALIAN.GXT!\n");
        return 4;
    }
    char buffer[4];
    int changed = 0;
    for (unsigned long i = 3300000; i <= 3400000; i++) {
        fseek(file, i, SEEK_SET);
        fread(buffer, sizeof(char), 4, file);
        for (int j = 0; j < languagesSize; j++) {
            if (strncmp(buffer, languages[j], 4) == 0) {
                changeLanguage(file, i, argv[2], languages[j]);
                changed = 1;
            }
        }
    }
    if (changed) {
        printf("Language changed successfully.\n");
    } else {
        printf("No language changes made.\n");
    }
    fclose(file);
    return 0;
}
