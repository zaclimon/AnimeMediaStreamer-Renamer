#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libgen.h>
#include <limits.h>
#include "renamer_file.h"

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

        if (is_file_horriblesubs(filename)) {
            printf("Renaming %s...\n", filename);
            modified_header_filename = remove_headers(filename);
            modified_whitespace_filename = remove_whitespaces(modified_header_filename);

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
            fprintf(stderr, "%s is not a valid HorribleSubs release\n", filename);
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

int is_extension_valid(char *filename) {

    /*
    * Verify if the file ends with the ".mkv" extension as all
    * original HorribleSubs releases finishes with it.
    */

    char *extension = strrchr(filename, '.');

    if (extension) {
        int same_extention = strcmp(extension, ".mkv");
        return (same_extention == 0 ? 1 : 0);
    }
    return (0);
}

int is_file_horriblesubs(char *filename)
{
    /* 
    * This might not be the most elegant way of checking this but to
    * ensure that the file is a valid HorribleSubs one, verify if the
    * [HorribleSubs] header is present and if the extension is ".mkv".
    */

    char *ret_header = strstr(filename, "[HorribleSubs]");
    int ret_extension = is_extension_valid(filename);

    return (ret_header && ret_extension == 1 ? 1 : 0);

}

char *remove_headers(char *src_filename)
{
    /* 
     * Verify/Remove the headers by creating a temporary string based
     * on the original filename.
    */
    
    char dst_filename[PATH_MAX] = "";
    int is_in_header;
    int char_count = strlen(src_filename);
    int dst_index = 0;
    int i;

    /* 
    * Remove the "[HorribleSubs]" header as well as the quality 
    * (480p, 720p, 1080p) one. 
    */
    for (i = 0; i < char_count; i++) {

        if (src_filename[i] == '[') {
            is_in_header = 1;
        }

        if (!is_in_header) {
            dst_filename[dst_index] = src_filename[i];
            dst_index++; 
        }

         if (src_filename[i] == ']') {
            is_in_header = 0;
        }
    }
    return (strdup(dst_filename));
}

char *remove_whitespaces(char *src_filename)
{
     /* 
     * Remove any trailing whitespaces. In this case, it would be
     * the first character and the one just before the file 
     * extension.
     *
     * This is of course assuming the file hasn't been altered
     * in any way. (Genuine release from HorribleSubs)
    */

    char *extension = strrchr(src_filename, '.');
    char dst_filename[PATH_MAX] = "";
    int char_count = strlen(src_filename);
    int dst_index = 0;
    int ext_index = extension - src_filename;
    int i;

    for (i = 0; i < char_count; i++) {

        if (i > 0 && i != ext_index - 1) {
            dst_filename[dst_index] = src_filename[i];
            dst_index++;
        }
    }

    return (strdup(dst_filename));
}