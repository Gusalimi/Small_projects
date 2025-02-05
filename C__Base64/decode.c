#include "base64.h"

bool is_valid(char *encoded) {
  char  c;
  for (int i = 0; encoded[i]; i++) {
    c = encoded[i];
    if (!(c >= 'A' && c <= 'Z') && !(c >= 'a' && c <= 'z') // character not in base
        && !(c >= '0' && c <= '9') && c != '+' && c != '/'
        && c != '=' && c != '\n') {
      return (false);
    } else if (c == '=' && (encoded[i + 1] != '=' && encoded[i + 1] != '\n')) { // = sign not at the end
      return (false);
    }
  }
  return (true);
}

char *trim(char *encoded) {
  char    *trimmed = NULL;
  size_t  num_equals = 0;
  size_t  new_len = 0;
  size_t  i = 0;
  int     nl = 0;

  for (i = 0; encoded[i]; i++) {
    if (encoded[i] == '=') {
      num_equals++;
    } else if (encoded[i] == '\n') {
      nl++;
    }
  }

  new_len = strlen(encoded) - num_equals - nl;
  printf("strlen = %zu | num_equals = %zu | new_len = %zu\n", strlen(encoded), num_equals, new_len);
  trimmed = calloc(new_len + 1, sizeof(char));
  if (!trimmed) {
    free(encoded);
    return (NULL);
  }

  for (i = 0; encoded[i]; i++) {
    if (encoded[i] != '=' && encoded[i] != '\n') {
      trimmed[i] = encoded[i];
    }
  }
  trimmed[i] = 0;

  free(encoded);
  return (trimmed);
}

char *decode() {
  char  *encoded = NULL;
  /*char      *decoded = NULL;*/
  /*int       c1, c2, c3, c4 = 0;*/
  /*uint32_t  three_chars = 0;*/

  while ((encoded = get_next_line(0))) {
    if (!is_valid(encoded)) {
      fprintf(stderr, "Error : invalid hash\n");
      continue ;
    }
    encoded = trim(encoded);
    printf("new = %s\n", encoded);
  }
  return (NULL);
}
