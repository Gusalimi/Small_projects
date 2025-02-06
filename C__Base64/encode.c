#include "base64.h"

char *encode(char *message) {
	char		*encoded = NULL;
	int			c1, c2, c3, c4 = 0;
	int			equal_padding = 0;
	int			message_len = 0;
	uint32_t	three_chars = 0;

	if (!message) {
		return (NULL);
	}

	// find how many equal signs append to result
	equal_padding = 3 - (strlen(message) % 3);

	while (*message) {
		message_len = strlen(message);

		// Join the 3 8 bits characters in one uint32_t
		// to make it easier to split
		three_chars = message[0] << 16;
		if (message_len >= 2) {
			three_chars |= message[1] << 8;
		}
		if (message_len >= 3) {
			three_chars |= message[2];
		}

		// Split packet in 4 6 bits numbers
		c1 = (three_chars >> 18) & 0b111111;
		c2 = (three_chars >> 12) & 0b111111;
		c3 = (three_chars >> 6) & 0b111111;
		c4 = three_chars & 0b111111;

		// Add characters to the string;
		encoded = add_char(encoded, BASE[c1]);
		if (!encoded) return (NULL);
		encoded = add_char(encoded, BASE[c2]);
		if (!encoded) return (NULL);
		if (message_len >= 2) {
			encoded = add_char(encoded, BASE[c3]);
			if (!encoded) return (NULL);
		}
		if (message_len >= 3) {
			encoded = add_char(encoded, BASE[c4]);
			if (!encoded) return (NULL);
		}
		if (message_len >= 3) {
			message += 3;
		} else {
			message += message_len;
		}
	}

	// Pad with equal signs
	for (int i = 0; i < equal_padding; i++) {
		encoded = add_char(encoded, '=');
	}
	return (encoded);
}
