#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>
#include "renamer_directory.h"
#include "renamer_file.h"

int rename_directory(char *path)
{
    DIR *d;
    struct dirent *dir;
    char realfilename[256];

    d = opendir(path);

    if (d) {

        /* 
         * Similar to the behavior of a shell, change the path to the
         * one hosting the files. This way, we can rename them
         * even from a distant local location.
         */

        chdir(path);
        
        while ((dir = readdir(d)) != NULL) {
            if (dir->d_type == DT_REG) {
                /* Get the absolute path so it can be easier to modify the path */
                realpath(dir->d_name, realfilename);
                rename_file(realfilename);
            }
        }
    } else {
        fprintf(stderr, "Path not valid: %s\n", path);
        return (0);
    }

    closedir(d);
    return (1);
}