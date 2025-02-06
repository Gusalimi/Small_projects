#include "base64.h"


bool is_valid(char *encoded) {
	char	c;
	for (int i = 0; encoded[i]; i++) {
		c = encoded[i];
		if (!(c >= 'A' && c <= 'Z') && !(c >= 'a' && c <= 'z') // character not in base
			&& !(c >= '0' && c <= '9') && c != '+' && c != '/'
			&& c != '=' && c != '\n') {
			return (false);
		} else if (c == '=' && (encoded[i + 1] != '=' && encoded[i + 1] != '\n')) { // = sign not at the end
			return (false);
		} else if (strncmp(encoded + i, "===", 3) == 0) { // More than 2 equal signs
			return (false);
		}
	}
	return (true);
}


// Remove the trailing \n from gnl and the trailing equal signs
char *trim(char *encoded) {
	char	*trimmed = NULL;
	size_t	num_equals = 0;
	size_t	new_len = 0;
	size_t	i = 0;
	int		nl = 0;

	for (i = 0; encoded[i]; i++) {
		if (encoded[i] == '=') {
			num_equals++;
		} else if (encoded[i] == '\n') {
			nl++;
		}
	}

	new_len = strlen(encoded) - num_equals - nl;
	trimmed = calloc(new_len + 2, sizeof(char));
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


char find_index_in_base(char c) {
	for (int i = 0; i < 64; i++) {
		if (BASE[i] == c) {
			return ((char)i);
		}
	}
	return (0);
}


uint32_t decode_packet(char *encoded) {
	uint32_t	three_chars = 0;
	int			c1, c2, c3, c4 = 0;
	int			encoded_len = strlen(encoded);

	c1 = find_index_in_base(encoded[0]);
	c2 = find_index_in_base(encoded[1]);
	if (encoded_len >= 3) {
		c3 = find_index_in_base(encoded[2]);
	} else {
		c3 = 0;
	}
	if (encoded_len >= 4) {
		c4 = find_index_in_base(encoded[3]);
	} else {
		c4 = 0;
	}

	three_chars = (c1 & 0b111111) << 18
					| ((c2 & 0b111111) << 12)
					| ((c3 & 0b111111) << 6)
					| (c4 & 0b111111);
	return (three_chars);
}


char *decode_one(char *encoded) {
	uint32_t	three_chars = 0;
	char		*decoded = NULL;
	char		c1, c2, c3 = 0;

	while (*encoded) {
		three_chars = decode_packet(encoded);
		c1 = (three_chars >> 16) & 0b11111111;
		c2 = (three_chars >> 8) & 0b11111111;
		c3 = (three_chars) & 0b11111111;
		decoded = add_char(decoded, c1);
		if (!decoded) return (NULL);
		decoded = add_char(decoded, c2);
		if (!decoded) return (NULL);
		decoded = add_char(decoded, c3);
		if (!decoded) return (NULL);
		if (strlen(encoded) >= 4) {
			encoded += 4;
		} else {
			encoded += strlen(encoded);
		}
	}
	return (decoded);
}


// Works like the macos version that takes one line at a time
// instead of taking the whole message at once
void decode_interactive() {
	char	*encoded = NULL;
	char	*decoded = NULL;

	while ((encoded = get_next_line(0))) {
		if (!is_valid(encoded)) {
			fprintf(stderr, "Error : invalid hash\n");
			free(encoded);
			continue ;
		}
		encoded = trim(encoded);
		if (!encoded) {
			fprintf(stderr, "Fatal error (malloc)\n");
			return ;
		}
		if (!*encoded) {
			continue ;
		}
		decoded = decode_one(encoded);
		if (!decoded) {
			fprintf(stderr, "Fatal error (malloc)\n");
			free(encoded);
			return ;
		}
		printf("%s", decoded);
		free(decoded);
		free(encoded);
	}
}
