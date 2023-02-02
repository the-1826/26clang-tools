#include <iostream>

int main()
{
    char buffer[6];
    char russian[6] = {'G', 'E', 'R', 'M', 'A', 'N'};
    char english[6] = {'F', 'R', 'E', 'N', 'C', 'H'};
    printf("Language Chronicles 1.0 opened.\n");
    printf("Opening ISO...\n");
    FILE *file = fopen("Grand Theft Auto - Sindacco Chronicles.iso","rb+");
    if (file != NULL) {
        printf("ISO opened! Changing Language...\n");
        for (int i = 5; i <= 200000; i++) {
            fseek(file, i - 5, SEEK_SET);
            fread(&buffer[0], sizeof(char), 1, file);
            fseek(file, i - 4, SEEK_SET);
            fread(&buffer[1], sizeof(char), 1, file);
            fseek(file, i - 3, SEEK_SET);
            fread(&buffer[2], sizeof(char), 1, file);
            fseek(file, i - 2, SEEK_SET);
            fread(&buffer[3], sizeof(char), 1, file);
            fseek(file, i - 1, SEEK_SET);
            fread(&buffer[4], sizeof(char), 1, file);
            fseek(file, i, SEEK_SET);
            fread(&buffer[5], sizeof(char), 1, file);
            if ((buffer[0] == 'G') && (buffer[1] == 'E') && (buffer[2] == 'R') && (buffer[3] == 'M') && (buffer[4] == 'A') && (buffer[5] == 'N')) {
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
                continue;
            }
            if ((buffer[0] == 'F') && (buffer[1] == 'R') && (buffer[2] == 'E') && (buffer[3] == 'N') && (buffer[4] == 'C') && (buffer[5] == 'H')) {
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
            }
        }
        printf("Language changed!\n");
    }
    else
        printf("Error opening file. Make sure it is named like that: Grand Theft Auto - Sindacco Chronicles.iso\n");
    system("pause");
}
