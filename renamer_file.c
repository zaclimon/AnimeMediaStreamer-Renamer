#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libgen.h>
#include "renamer_file.h"
#include "renamer_parser.h"

int rename_file(char *path)
{
    /*
     * Rename an anime release by checking if it's valid.
     * Once it's validity has been confirmed, remove the headers
     * possible parentheses as well as the remaining whitespaces.
     *
     * Finally rename accordingly the filename.
     */

    FILE *file;
    file = fopen(path, "w");

    if (file) {
        char *filename = basename(path);
        char *modified_header_filename;
        char *modified_parentheses_filename;
        char *modified_whitespace_filename;

        int extension_ret = is_extension_valid(filename);

        if (extension_ret) {
            printf("Renaming %s...\n", filename);
            modified_header_filename = remove_headers(filename);
            modified_parentheses_filename = remove_parentheses(modified_header_filename);
            modified_whitespace_filename = remove_whitespaces(modified_parentheses_filename);

            int rename_ret = rename(filename, modified_whitespace_filename);

            if (rename_ret == 0) {
                printf("New renamed file: %s\n", modified_whitespace_filename);
            } else {
                fprintf(stderr, "Couldn't rename the file.");
                free(modified_header_filename);
                free(modified_parentheses_filename);
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
    free(modified_parentheses_filename);
    free(modified_whitespace_filename);
    fclose(file);
    return (0);

    } else {
        fprintf(stderr, "Couldn't access %s", path);
        return (1);
    }
}

int is_extension_valid(char *filename)
{
    /*
     * Although it is a weak way to see if the extension is valid,
     * most (if not all) anime releases are either in ".mp4" or in ".mkv"
     * depending on the fansub.
    */
    return (strstr(filename, ".mkv") || strstr(filename, ".mp4") ? 1 : 0);
}