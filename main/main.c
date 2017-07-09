#include <stdio.h>
#include <stdlib.h>

#include "../lib/dedup-characters.h"
#include "../lib/capsicumize.h"

int
main(int argc, char **argv) {
  (void)argc;
  (void)argv;
  capsicumize();
  dedup_characters(getchar, putchar, ' ');
  return EXIT_SUCCESS;
}
