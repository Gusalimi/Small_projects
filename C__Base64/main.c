#include "base64.h"

int main(int ac, char **av) {
  bool  decode_mode;
  char  *message;
  char  *transformed;

  decode_mode = should_decode(ac, av);
  if (decode_mode) {
    transformed = decode();
  } else {
    message = get_full_message();
    transformed = encode(message);
  }
  printf("%s\n", transformed);
}
