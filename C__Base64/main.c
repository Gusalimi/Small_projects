#include "base64.h"

int main(int ac, char **av) {
	char	*message;
	char	*encoded;

	if (should_decode(ac, av)) {
		decode_interactive();
	} else {
		message = get_full_message();
		encoded = encode(message);
		printf("%s\n", encoded);
		free(message);
		free(encoded);
	}
	return (0);
}
