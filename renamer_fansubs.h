/* Function to get the provider based on the providers typedef */
int get_fansub(char *filename);

/* Constant values for fansubs */
#define NOT_VALID_FANSUB -1
#define HORRIBLESUBS 0

/* 
 * Definition of functions for header/whitespace removal of
 * each provider
*/

/* HorribleSubs */
char *remove_headers_horriblesubs(char *src_filename);
char *remove_whitespaces_horriblesubs(char *src_filename);

extern char *(*remove_headers_fansubs[])(char *src_filename);
extern char *(*remove_whitespaces_fansubs[])(char *src_filename);