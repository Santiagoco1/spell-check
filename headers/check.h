void insert_char(Word *word, int i, char c, char aux[]);

void fifht_technique(Word *word, Node **mods_list, HashTable *dictionary, HashTable *mods_table, int *count, int *steps);

void fourth_technique(Word *word, Node **mods_list, HashTable *dictionary, HashTable *mods_table, int *count, int *steps);

void eliminate_char(Word *word, int i, char aux[]);

void third_technique(Word *word, Node **mods_list, HashTable *dictionary, HashTable *mods_table, int *count, int *steps);

void second_technique(Word *word, Node **mods_list, HashTable *dictionary, HashTable *mods_table, int *count, int *steps);

void split_str(Word *word, int i, char word1[], char word2[]);

void first_technique(Word *word, Node **mods_list, HashTable *dictionary, HashTable *mods_table, int *count, int *steps);

void apply_techniques(Word *mods_list, Node **list, HashTable *dictionary, HashTable *mods_table, int *count, int *steps);

void _find_suggestions(List *mods_list, HashTable *dictionary, HashTable *mods_table, int *count, int *steps);

void find_suggestions(Word *word, HashTable *dictionary);

void check_text(char *path, HashTable *dictionary);