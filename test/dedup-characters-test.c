#include <stdio.h>
#include <string.h>

#include "../vendor/minunit/minunit.h"

#include "../lib/dedup-characters.h"


static const char to_be_deduped = '.';


#define FORMATTED_MESSAGE_SIZE_MAX 256
  static char message[FORMATTED_MESSAGE_SIZE_MAX];
#undef FORMATTED_MESSAGE_SIZE_MAX

#define OUTPUT_BUFFER_SIZE 50
#define output_buffer(t) static char t##_output_buffer[OUTPUT_BUFFER_SIZE]

static const char* a = "";
static const char* a_exp = "";
output_buffer(a);
static const char* b = "x";
static const char* b_exp = "x";
output_buffer(b);
static const char* c = "x..x";
static const char* c_exp = "x.x";
output_buffer(c);
static const char* d = "..x..";
static const char* d_exp = ".x.";
output_buffer(d);
static const char* e = ".x..x...x";
static const char* e_exp = ".x.x.x";
output_buffer(e);
static const char* f = "x..x....x..";
static const char* f_exp = "x.x.x.";
output_buffer(f);
static const char* g = "x..x...";
static const char* g_exp = "x.x.";
output_buffer(g);


#define get_character_stub(input) int get_character_stub_##input(void) {\
  static size_t call_count = 0;\
  size_t input_length = strlen(input);\
  int return_value = call_count < input_length ? input[call_count] : EOF;\
  call_count++;\
  return return_value;\
}

#define put_character_stub(x) int put_character_stub_##x(int c) {\
  sprintf(x##_output_buffer, "%s%c", x##_output_buffer, c);\
  return 0;\
}

get_character_stub(a)
get_character_stub(b)
get_character_stub(c)
get_character_stub(d)
get_character_stub(e)
get_character_stub(f)
get_character_stub(g)

#undef get_character_stub

put_character_stub(a)
put_character_stub(b)
put_character_stub(c)
put_character_stub(d)
put_character_stub(e)
put_character_stub(f)
put_character_stub(g)

#undef put_character_stub


#define test_dedup_characters(t) char* test_dedup_characters_##t(void) { \
  const char *message_format = "(%s:%s) expected deduplication of '%c' in '%s' to equal '%s' but got '%s'";\
  memset(t##_output_buffer, 0, sizeof(t##_output_buffer));\
  dedup_characters(get_character_stub_##t, put_character_stub_##t, to_be_deduped);    \
  (void)snprintf(\
    message,\
    sizeof message,\
    message_format,\
    __FILE__,\
    __func__,\
    to_be_deduped,\
    t,\
    t##_exp,\
    t##_output_buffer);\
  mu_assert(message, strncmp(t##_exp, t##_output_buffer, strlen(t##_exp)) == 0); \
  return 0;\
}

test_dedup_characters(a)
test_dedup_characters(b)
test_dedup_characters(c)
test_dedup_characters(d)
test_dedup_characters(e)
test_dedup_characters(f)
test_dedup_characters(g)

#undef test_count_characters

