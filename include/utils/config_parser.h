#ifndef CONFIG_PARSER_H
#define CONFIG_PARSER_H

#include <stdio.h>
#include <string.h>
#include <yaml.h>

#ifndef CONFIG_FILE_PATH
#define CONFIG_FILE_PATH "config.yaml"
#endif

#define CONFIG_MAP_SIZE 100
#define CONFIG_MAX_KEY_SIZE 256
#define CONFIG_MAX_VALUE_SIZE 256

typedef struct {
  char key[CONFIG_MAX_KEY_SIZE];
  char value[CONFIG_MAX_VALUE_SIZE];
} hash_entry;

typedef struct {
  hash_entry table[CONFIG_MAP_SIZE];
  int slot_used[CONFIG_MAP_SIZE];
} hash_map;

typedef enum { INFO, DEBUG, WARN, ERROR } verbosity_levels;

typedef struct {
  hash_map cpu_conf;
  hash_map mem_conf;
  hash_map stat_conf;
  hash_map log_conf;
} configs;

unsigned int _hash_function(const char *str);
int _hash_map_set(hash_map *map, const char *key, const char *value);
const char *_hash_map_get(hash_map *map, const char *key);
void _hash_map_init(hash_map *map);

configs *parse_configs();

#endif // !CONFIG_PARSER_H
