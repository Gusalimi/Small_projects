# Base64 Encoder/Decoder

### Presentation
Numerical base like base2 (binary), base8 (octal), base10 (decimal) and base16 (hexadecimal). It uses the alphabet in lowercase and uppercase, the digits and '+' and '/'.

### How to convert a message to base64
The first step is to take packets of 3 characters while it's possible. For the examples, let's assume the message is 'message'.

#### 1. Take the ASCII codes
This step is automatic if working on computer, because a character is already its ascii code. Otherwise, you have to find the code of each of these characters in the ASCII table.

#### 2. Split the 3 characters into 4 numbers
Here, you have to split the characters. You'll do that by taking 6 bits per character to create a number. The first num is the 6 first bits of the first character, then the 2 last from the first characters and four from the next one, and so on.

Let's see how it works with our example :

|    m     |    e     |    s     |
| :------: | :------: | :------: |
|   109    |   101    |   115    |
| 01101101 | 01100101 | 01110011 |

| 011011 | 010110 | 010101 | 110011 |
| :----: | :----: | :----: | :----: |
|   27   |   22   |   21   |   51   |

#### 3. Get the corresponding characters from the base
Let's find the 28th, 23rd, 22nd and 52nd characters from the base (it's an index so it begins at 0). We get b, W, V and z.

#### 4. What if the length is not a multiple of 3
In the case where the last packet doesn't have 3 characters, we end the last 6 bits number with 0s and we pad the missing letters with one or two =, depending on the length of the packet.

### Example
Let's do it entirely with 'message'.

|    m     |    e     |    s     |    s     |    a     |    g     |    e     |
| :------: | :------: | :------: | :------: | :------: | :------: | :------: |
|   109    |   101    |   115    |   115    |    97    |   103    |   101    |
| 01101101 | 01100101 | 01110011 | 01110011 | 01100001 | 01100111 | 01100101 |

| 011011 | 010110 | 010101 | 110011 | 011100 | 110110 | 000101 | 100111 | 011001 | 010000 |
| :----: | :----: | :----: | :----: | :----: | :----: | :----: | :----: | :----: | :----: |
|   27   |   22   |   21   |   51   |   28   |   54   |   5    |   39   |   25   |   16   |

Let's find the corresponding characters in the base64 table. We can use a little program to make it easier :
```c
#include <stdio.h>
#include <stdlib.h>

#define BASE "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"

int main(int ac, char **av) {
  for (int i = 1; i < ac; i++) {
    printf("%c", BASE[atoi(av[i])]);
  }
  printf("\n");
}
```

When executing that with the numbers we found as arguments, we get `bWVzc2FnZQ`. Now, we just have to pad it with two `=` (2 characters missing from the last packet to be a multiple of 3) and we get ***`bWVzc2FnZQ==`***

We can now use the `base64` executable to verify it.

### Notes
To create an encoder in C, we could probably use a `uint32_t` to join all the characters in one int (8 * 3 = 24 necessary bits to represent 3 characters), making it easier to split them afterwards.

To decode, we just have to reverse the process : remove the = signs, find the number of each character in the base, cut the 4 numbers into 3 characters and find them in the ascii table
