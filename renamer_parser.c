#include <stdio.h>
#include <string.h>
#include <limits.h>
#include "renamer_parser.h"

char *remove_character_section(char *src_filename, char start, char end)
{
    /* 
     * Verify/Remove the section in between the characters 
     * by creating a temporary string based on the 
     * original filename.
    */
    
    char dst_filename[PATH_MAX] = "";
    int is_in_header;
    int char_count = strlen(src_filename);
    int dst_index = 0;
    int i;

    for (i = 0; i < char_count; i++) {

        if (src_filename[i] == start) {
            is_in_header = 1;
        }

        if (!is_in_header) {
            dst_filename[dst_index] = src_filename[i];
            dst_index++;
        }

         if (src_filename[i] == end) {
            is_in_header = 0;
        }

    }
    return (strdup(dst_filename));
}

char *remove_headers(char *src_filename)
{
    return (remove_character_section(src_filename, '[', ']'));
}

char *remove_parentheses(char *src_filename)
{
    /* 
     * Some fansubs use parenthesis in their releases to
     * complement the use of the brackets. Remove them as well.
    */
    return (remove_character_section(src_filename, '(', ')'));
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
    int last_char_index;
    int number_of_spaces = 0;
    int i;

    /*
     * Find the number of spaces before the extension so it can be 
     * possible to not include them.
    */ 

    for (i = ext_index - 1; i > 0; i--) {

        if (src_filename[i] == ' ') {
            number_of_spaces++;
        } else {
            break;
        }
    }

    last_char_index = ext_index - number_of_spaces;

    /*
     * Don't include the space at the beginning of a file after
     * removing the brackets if any.

     * Also, don't include anything between the last alphanumeric character
     * index and the extension index (Which in this case would be the
     * spaces between them.
    */
    for (i = 0; i < char_count; i++) {

        if (src_filename[0] != ' ' || i > 0 && i < last_char_index || i >= ext_index) {
            dst_filename[dst_index] = src_filename[i];
            dst_index++;
        }
    }

    return (strdup(dst_filename));
}