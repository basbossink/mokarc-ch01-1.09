typedef int (*get_character)(void);
typedef int (*put_character)(int);

void
dedup_characters(get_character source, put_character sink, char to_dedup);

