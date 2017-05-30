#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libgen.h>
#include "renamer_file.h"
#include "renamer_fansubs.h"

int rename_file(char *path)
{
    /*
     * Rename an HorribleSubs release by checking if it's valid.
     * Once it's validity has been confirmed, remove the headers
     * as well as the remaining whitespaces.
     *
     * Finally rename accordingly the filename.
     */

    FILE *file;
    file = fopen(path, "w");

    if (file) {
        char *filename = basename(path);
        char *modified_header_filename;
        char *modified_whitespace_filename;

        /* Get the appropriate fansub based on the filename */
        int fansub_ret = get_fansub(filename);

        if (fansub_ret >= 0) {
            printf("Renaming %s...\n", filename);
            modified_header_filename = remove_headers(fansub_ret, filename);
            modified_whitespace_filename = remove_whitespaces(fansub_ret, modified_header_filename);

            int rename_ret = rename(filename, modified_whitespace_filename);

            if (rename_ret == 0) {
                printf("New renamed file: %s\n", modified_whitespace_filename);
            } else {
                fprintf(stderr, "Couldn't rename the file.");
                free(modified_header_filename);
                free(modified_whitespace_filename);
                fclose(file);
                return (1);
            }
            
        } else {
            fprintf(stderr, "%s is not a valid anime release\n", filename);
            fclose(file);
            return (1);
        }

    free(modified_header_filename);
    free(modified_whitespace_filename);
    fclose(file);
    return (0);

    } else {
        fprintf(stderr, "Couldn't access %s", path);
        return (1);
    }
}

char *remove_headers(int fansub, char *src_filename)
{
    return (remove_headers_fansubs[fansub](src_filename));
}

char *remove_whitespaces(int fansub, char *src_filename)
{
   return (remove_whitespaces_fansubs[fansub](src_filename));
}