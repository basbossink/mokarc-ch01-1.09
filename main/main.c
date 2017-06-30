#include <stdio.h>
#include <stdlib.h>

#include "../lib/dedup-characters.h"

int
main(int argc, char **argv) {
  (void)argc;
  (void)argv;
  dedup_characters(getchar, putchar, ' ');
  return EXIT_SUCCESS;
}
