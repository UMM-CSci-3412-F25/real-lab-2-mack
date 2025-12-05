#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "disemvowel.h"

static int is_vowel(char c) {
  c = tolower((unsigned char)c);
  return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
}

char *disemvowel(char *str) {
  if (!str) {
    return NULL;
  }

  /* Reusable buf so (tests) don't need to free the result. */
  static char *buffer = NULL;
  static size_t capacity = 0;

  size_t len = strlen(str);
  if (len + 1 > capacity) {
    /* Grow the buf to fit the current input (plus terminator). */
    char *new_buf = (char*) realloc(buffer, len + 1);
    if (!new_buf) {
      return NULL;
    }
    buffer = new_buf;
    capacity = len + 1;
  }

  size_t j = 0;
  for (size_t i = 0; i < len; ++i) {
    /* Copy only non-vowel chars into the output buffer. */
    if (!is_vowel(str[i])) {
      buffer[j++] = str[i];
    }
  }

  buffer[j] = '\0';
  return buffer;
}