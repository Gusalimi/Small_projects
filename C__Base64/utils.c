#include "base64.h"

char *add_char(char *old_string, char c) {
  char  *new_string = NULL;
  int   old_string_len = 0;
  int   i = 0;

  // if old_string == NULL, return a new string with only the character
  if (!old_string) {
    new_string = calloc(2, sizeof(char));
    if (!new_string) {
      free(old_string);
      return (NULL);
    }
    new_string[0] = c;
    new_string[1] = 0;
    return (new_string);
  }

  // Allocate new string
  old_string_len = strlen(old_string);
  new_string = calloc(old_string_len + 2, sizeof(char));
  if (!new_string) {
    free(old_string);
    return (NULL);
  }

  // Fill new string with old string + new character
  for (i = 0; i < old_string_len; i++) {
    new_string[i] = old_string[i];
  }
  new_string[i++] = c;
  new_string[i] = 0;

  free(old_string);
  return (new_string);
}

