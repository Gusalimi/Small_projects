#ifndef BASE64_H
# define BASE64_H

// == Includes ==
# include <stdio.h>
# include <stdint.h>
# include <string.h>
# include "get_next_line.h"

// == Bools ==
# define true 1
# define false 0
typedef char bool;

// == Defines ==
# define BASE "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"

// == Prototypes ==
// parser.c
bool  should_decode(int ac, char **av);
char  *get_full_message(void);
// utils.c
char  *add_char(char *old_string, char c);
// encode.c
char  *encode(char *message);
// decode.c
char  *decode();

#endif
