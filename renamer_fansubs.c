#include <stdio.h>
#include <string.h>
#include <limits.h>
#include "renamer_fansubs.h"

char *(*remove_headers_fansubs[])(char *src_filename) = { remove_headers_horriblesubs };
char *(*remove_whitespaces_fansubs[])(char *src_filename) = { remove_whitespaces_horriblesubs };

/* 
 * Surely enough we could verify the extension of
 * each and every file to ensure that they are
 * "Authentic" but with all the available fansubs
 * out there, I'll put my trust that they all are.
 */ 
int get_fansub(char *filename)
{
    if (strstr(filename, "[HorribleSubs]")) {
        return (HORRIBLESUBS);
    } else {
        return (NOT_VALID_FANSUB);
    }
}

char *remove_headers_horriblesubs(char *src_filename)
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

char *remove_whitespaces_horriblesubs(char *src_filename)
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