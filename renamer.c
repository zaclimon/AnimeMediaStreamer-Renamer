#include <stdio.h>
#include <unistd.h>
#include "renamer_directory.h"
#include "renamer_file.h"

void show_help()
{
    puts("Usage: horriblesubsrename [OPTION]...");
    puts("       horriblesubsrename [OPTION]... [FILE]...");
    puts("       horriblesubsrename [OPTION]... [DIRECTORY]...");
    puts("Renames HorribleSubs supplied releases for easy importation.");
    puts("");
    puts("  -d, --directory     Renames a given directory");
    puts("  -f, --file          Renames a given file");
    puts("  -h, --help          Show this help message");
}

int main(int argc, char *argv[])
{
    int ret;
    char ch;

    while ((ch = getopt(argc, argv, "d:f:h")) != EOF) {
        switch (ch) {
            case 'd':
                ret = rename_directory(optarg);
                break;
            case 'f':
                ret = rename_file(optarg);
                break;
            case 'h':
                show_help();
                break;
        }
    }
    return ret;
}