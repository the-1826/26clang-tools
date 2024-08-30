#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    printf("LCS-M Russian .gxt Encoder opened.\n");
    if (argc < 2) {
        fprintf(stderr, "No .gxt file selected.\n");
        return 1;
    }
    printf("Opening .gxt...\n");
    char fname[60], drive[100], ext[5], result_name[50];
    _splitpath(argv[1], drive, drive, fname, ext);
    snprintf(result_name, sizeof result_name, "%s%s", fname, ext);
    FILE *file = fopen(result_name, "rb");
    FILE *file2 = fopen("result.gxt", "wb");
    if (file == NULL) {
        fprintf(stderr, "Error opening .gxt file.\n");
        return 2;
    }
    if (file2 == NULL) {
        fprintf(stderr, "Error creating new .gxt file.\n");
        return 3;
    }
    printf(".gxt opened. Converting...\n");
    unsigned long sz;
    fseek(file, 0L, SEEK_END);
    sz = ftell(file);
    fseek(file,0L,SEEK_SET);
    char testchar[5] = {0, 0, 0, 0, 0}, doublebyte[2] = {1, 0}, fixator[1] = {0xF7}, special_letter_flag = 0, breakdown = 0;
    for (int i = 0; i < sz; i++) {
        fseek(file, i, SEEK_SET);
        fread(&testchar[0], sizeof(char), 1, file);
        if (i - 1 < sz) {
            fseek(file, i - 1, SEEK_SET);
            fread(&testchar[1], sizeof(char), 1, file);
        }
        if (i + 1 < sz) {
            fseek(file, i + 1, SEEK_SET);
            fread(&testchar[2], sizeof(char), 1, file);
        }
        if (i + 2 < sz) {
            fseek(file, i + 2, SEEK_SET);
            fread(&testchar[3], sizeof(char), 1, file);
        }
        if (i - 2 < sz) {
            fseek(file, i - 2, SEEK_SET);
            fread(&testchar[4], sizeof(char), 1, file);
        }
        if ((testchar[1] == 0) && (testchar[2] == 0) && (!((testchar[3] == 0) && (testchar[4] == 0)))) {
            switch (testchar[0]) {
            case '€':
                special_letter_flag = 1;
                testchar[0] = 0x11;
                break;
            case '':
                testchar[0] = 0xFD;
                break;
            case '‚':
                testchar[0] = 0xE4;
                break;
            case -125:
                special_letter_flag = 1;
                testchar[0] = 0x14;
                break;
            case -124:
                testchar[0] = 0xF0;
                break;
            case '…':
                special_letter_flag = 1;
                testchar[0] = 0x6;
                break;
            case '†':
                special_letter_flag = 1;
                testchar[0] = 0x0A;
                break;
            case '‡':
                special_letter_flag = 1;
                testchar[0] = 0x0E;
                break;
            case 'ˆ':
                special_letter_flag = 1;
                testchar[0] = 0x0F;
                break;
            case '‰':
                special_letter_flag = 1;
                testchar[0] = 0x1C;
                break;
            case 'Š':
                testchar[0] = 0xDE;
                break;
            case '‹':
                special_letter_flag = 1;
                breakdown = 1;
                testchar[0] = 0x0;
                break;
            case 'Œ':
                special_letter_flag = 1;
                testchar[0] = 0x0C;
                break;
            case '':
                testchar[0] = 0xF8;
                break;
            case 'Ž':
                special_letter_flag = 1;
                testchar[0] = 0x8;
                break;
            case '':
                special_letter_flag = 1;
                testchar[0] = 0x3;
                break;
            case '':
                special_letter_flag = 1;
                testchar[0] = 0x0B;
                break;
            case '‘':
                special_letter_flag = 1;
                testchar[0] = 0x4;
                break;
            case '’':
                special_letter_flag = 1;
                testchar[0] = 0x10;
                break;
            case '“':
                special_letter_flag = 1;
                testchar[0] = 0x9;
                break;
            case '”':
                special_letter_flag = 1;
                testchar[0] = 0x0D;
                break;
            case '•':
                special_letter_flag = 1;
                testchar[0] = 0x19;
                break;
            case '–':
                special_letter_flag = 1;
                testchar[0] = 0x13;
                break;
            case -105:
                special_letter_flag = 1;
                testchar[0] = 0x7;
                break;
            case '˜':
                special_letter_flag = 1;
                testchar[0] = 0x15;
                break;
            case '™':
                special_letter_flag = 1;
                testchar[0] = 0x0F;
                break;
            case '#':
                testchar[0] = 0xF6;
                break;
            case '›':
                special_letter_flag = 1;
                testchar[0] = 0x16;
                break;
            case 'œ':
                special_letter_flag = 1;
                testchar[0] = 0x1A;
                break;
            case '':
                testchar[0] = 0xE2;
                break;
            case 'ž':
                special_letter_flag = 1;
                testchar[0] = 0xBB;
                break;
            case 'Ÿ':
                special_letter_flag = 1;
                testchar[0] = 0x17;
                break;
            case ' ':
                testchar[0] = 0xED;
                break;
            case '¡':
                testchar[0] = 0xFB;
                break;
            case '¢':
                testchar[0] = 0xEB;
                break;
            case '£':
                testchar[0] = 0xF4;
                break;
            case '¤':
                testchar[0] = 0xE1;
                break;
            case '¥':
                testchar[0] = 0xE5;
                break;
            case '¦':
                testchar[0] = 0xF6;
                break;
            case '§':
                testchar[0] = 0xF5;
                break;
            case '¨':
                testchar[0] = 0xE8;
                break;
            case '©':
                testchar[0] = 0xE3;
                break;
            case 'ª':
                testchar[0] = 0xF7;
                break;
            case '«':
                testchar[0] = 0xDF;
                break;
            case '¬':
                testchar[0] = 0xEC;
                break;
            case -83:
                testchar[0] = 0xE7;
                break;
            case '®':
                testchar[0] = 0xE0;
                break;
            case '¯':
                testchar[0] = 0xFC;
                break;
            case '°':
                testchar[0] = 0xE6;
                break;
            case '±':
                testchar[0] = 0xE9;
                break;
            case '²':
                testchar[0] = 0xF3;
                break;
            case '³':
                testchar[0] = 0xEF;
                break;
            case '´':
                special_letter_flag = 1;
                testchar[0] = 0x1;
                break;
            case 'µ':
                testchar[0] = 0xF9;
                break;
            case '¶':
                special_letter_flag = 1;
                testchar[0] = 0x2;
                break;
            case '·':
                testchar[0] = 0xFE;
                break;
            case '¸':
                testchar[0] = 0xEE;
                break;
            case '¹':
                testchar[0] = 0xFF;
                break;
            case 'º':
                testchar[0] = 0xCC;
                break;
            case -69:
                testchar[0] = 0xFA;
                break;
            case '¼':
                testchar[0] = 0xEA;
                break;
            case '½':
                testchar[0] = 0xF2;
                break;
            case '¾':
                special_letter_flag = 1;
                testchar[0] = 0x5;
                break;
            case '¿':
                testchar[0] = 0xF1;
                break;
            }
        }
        if ((special_letter_flag == 1) && ((testchar[0] == 0) || (breakdown))) {
            special_letter_flag = 0;
            fwrite(breakdown ? &doublebyte[1] : &doublebyte[0], sizeof(char), 1, file2);
        }
        else
            if (testchar[0] != 0xAD) {
                fwrite(breakdown ? &doublebyte[0] : &testchar[0], sizeof(char), 1, file2);
                breakdown = 0;
            }
            else
                fwrite(&fixator[0], sizeof(char), 1, file2);
    }
}
