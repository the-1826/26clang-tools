#include <iostream>
#include <dirent.h>
#include <regex>
#include <string>

using namespace std;

void swap(int argc, char *argv[]) {
    for (int i = 0; i < argc; i++)
        for (int j = 1; j < (argc - i - 1); j++)
            if (strcmp(argv[j], argv[j + 1]) > 0)
                std::swap(argv[j], argv[j + 1]);
}

int main(int argc, char *argv[]) {
    freopen("log.txt","w",stdout);
    unsigned int count = 0;
    dirent* dirp;
    map<unsigned long, string> files;
    regex ext_regex("[a-zA-Z0-9_.-]+\\.vag");
    cout << "Starting looking for source files..." << endl;
    if (DIR *dp = opendir("sourcefiles")) {
        while ((dirp = readdir(dp))) {
            if (regex_match(dirp->d_name, ext_regex)) {
                unsigned long size = 0;
                string filepath = "sourcefiles/" + std::string(dirp->d_name);
                const char * filepathc = filepath.c_str();
                FILE* fd = fopen(filepathc, "rb");
                if (fd == NULL)
                    size = -1;
                else {
                    fseek(fd, 0, SEEK_END);
                    size = ftello(fd);
                    fclose(fd);
                }
                files[size] = std::string(dirp->d_name);
                count++;
            }
        }
        closedir(dp);
    }
    cout << "Source files found. Starting looking for replacement candidates..." << endl << "---" << endl;
    swap(argc, argv);
    char patched = 0;
    char fname[35], drive[100], ext[5], result_name[40];
    for (int i = 1; i < argc; i++) {
        _splitpath(argv[i], drive, drive, fname, ext);
        snprintf(result_name, sizeof result_name, "%s%s", fname, ext);
        FILE* sourcefile = fopen(result_name, "rb+");
        if (sourcefile == NULL) {
            fprintf(stderr, "Wrong files attached.\n");
            return 1;
        }
        fseek(sourcefile, 0, SEEK_END);
        unsigned long source_length = ftell(sourcefile);
        auto it = files.lower_bound(source_length);
        if (it != files.end())
            cout << "File " << result_name << " weight is: " << source_length << " bytes. Closest weight candidate is: " << it->second << " (" << it->first << " bytes)";
        else
            cout << "No more or equal than " << result_name;
        if (i != argc - 1)
            cout << endl;
        string filepath = "sourcefiles/" + std::string(it->second.c_str());
        const char *filepathc = filepath.c_str();
        remove(filepathc);
        files.erase(it->first);
        FILE* newfile = fopen("temp.tmp", "wb");
        if (newfile == NULL) {
            fprintf(stderr, "Can't create a temporary file.\n");
            return 1;
        }
        char temp;
        unsigned long delta = it->first - source_length;
        fseek(sourcefile, 0, SEEK_END);
        for (long i = 0; i < source_length - 15; i++) {
            fseek(sourcefile, i, SEEK_SET);
            fread(&temp, 1, 1, sourcefile);
            fwrite(&temp, 1, 1, newfile);
        }
        temp = 0;
        const char last[15] = {'', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w'};
        fwrite(last, 15, 1, newfile);
        for (unsigned long j = 0; j < delta; j++)
            fwrite(&temp, 1, 1, newfile);
        fclose(sourcefile);
        fclose(newfile);
        remove(result_name);
        char result = rename("temp.tmp", it->second.c_str());
        patched = 1;
    }
    if (!(patched))
        cout << "No files patched." << endl;
    return 0;
}
