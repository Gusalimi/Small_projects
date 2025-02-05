#include "base64.h"

bool should_decode(int ac, char **av) {
  for (int i = 1; i < ac; i++) {
    if (strcmp(av[i], "-d") == 0) {
      return (true);
    }
  }
  return (false);
}

char  *append_line(char *s1, char *s2) {
  if (!s1 && !s2) {
    return (NULL);
  } else if (!s1) {
    return (strdup(s2));
  } else if (!s2) {
    return (strdup(s1));
  }

  int	i, j;
  int   new_len = strlen(s1) + strlen(s2);
  char  *ret = malloc((new_len + 1) * sizeof(char));

  if (!ret) {
    free(s1);
    free(s2);
    return (NULL);
  }

  for (i = 0, j = 0; s1[i]; i++, j++) {
    ret[j] = s1[i];
  }
  for (i = 0; s2[i]; i++, j++) {
    ret[j] = s2[i];
  }
  ret[j] = 0;
  
  free(s1);
  return (ret);
}

char *get_full_message() {
  char  *line = NULL;
  char  *message = NULL;

  while ((line = get_next_line(0))) {
    message = append_line(message, line);
    if (!message) {
      return (NULL);
    }
  }
  return (message);
}
