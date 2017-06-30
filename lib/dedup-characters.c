#include <stdio.h>

#include "dedup-characters.h"

void
dedup_characters(get_character source, put_character sink, char to_dedup) {
  (void)source;
  (void)sink;
  (void)to_dedup;
  int current_character = 0;
  int previous_character = 0;
  while((previous_character = source()) != EOF) {
    while(
      (current_character = source()) != EOF &&
      current_character == to_dedup &&
      previous_character == to_dedup)
      ;
    sink(previous_character);
    if(current_character != to_dedup) {
      sink(current_character);
    }
  }
}
