#include "utils/config_parser.h"

configs parsed_configs;

hash_map cpu_config_hash_map;
hash_map mem_config_hash_map;
hash_map stats_config_hash_map;
hash_map logs_config_hash_map;

unsigned int _hash_function(const char *str) {
  unsigned int hash = 5381;
  int c;
  while ((c = *str++))
    hash = ((hash << 5) + hash) + c; // hash * 33 + c
  return hash % CONFIG_MAP_SIZE;
}

int _hash_map_set(hash_map *map, const char *key, const char *value) {
  unsigned int index = _hash_function(key);

  while (map->slot_used[index]) {
    if (strncmp(map->table[index].key, key, strlen(key)) == 0) {
      strcpy(map->table[index].value, value);
      return 1;
    }
    index = (index + 1) % CONFIG_MAP_SIZE;
  }

  strcpy(map->table[index].key, key);
  strcpy(map->table[index].value, value);
  map->slot_used[index] = 1;

  return 0;
}

const char *_hash_map_get(hash_map *map, const char *key) {
  unsigned int index = _hash_function(key);

  while (map->slot_used[index]) {
    if (strcmp(map->table[index].key, key) == 0) {
      return map->table[index].value;
    }
    index = (index + 1) % CONFIG_MAP_SIZE;
  }

  return NULL;
}

void _hash_map_init(hash_map *map) {
  for (int i = 0; i < CONFIG_MAP_SIZE; i++)
    map->slot_used[i] = 0;

  int init_status = 0;
  _hash_map_set(&cpu_config_hash_map, "pipeline_stages", "5");

  _hash_map_set(&mem_config_hash_map, "l1_icache_size", "128");
  _hash_map_set(&mem_config_hash_map, "l1_dcache_size", "128");
  _hash_map_set(&mem_config_hash_map, "l2_cache_size", "1024");
  _hash_map_set(&mem_config_hash_map, "dram_size", "4096");

  _hash_map_set(&stats_config_hash_map, "cache_misses", "1");
  _hash_map_set(&stats_config_hash_map, "branch_mispredictions", "1");
  _hash_map_set(&stats_config_hash_map, "memory_heatmap", "0");
  _hash_map_set(&stats_config_hash_map, "register_heatmap", "0");

  _hash_map_set(&logs_config_hash_map, "verbosity_level", "3");
}

configs *parse_configs() {
  yaml_parser_t parser;
  yaml_token_t token;

  FILE *config_file = fopen(CONFIG_FILE_PATH, "r");
  if (config_file == NULL)
    printf("config file read failed");

  if (!yaml_parser_initialize(&parser))
    printf("config parser init failed");

  yaml_parser_set_input_file(&parser, config_file);

  int block_mapping_level = 0;
  int is_scalar_key = 0;

  char *block_name;
  char *key_name;

  do {
    yaml_parser_scan(&parser, &token);

    switch (token.type) {
    case YAML_STREAM_START_TOKEN:
      printf("yaml stream: start\n");
      break;
    case YAML_STREAM_END_TOKEN:
      printf("yaml stream: end\n");
      break;
    case YAML_KEY_TOKEN:
      printf("yaml stream: key token\n");
      is_scalar_key = 1;
      break;
    case YAML_VALUE_TOKEN:
      printf("yaml stream: value token\n");
      is_scalar_key = 0;
      break;
    case YAML_BLOCK_SEQUENCE_START_TOKEN:
      printf("yaml stream: start block sequence\n");
      break;
    case YAML_BLOCK_ENTRY_TOKEN:
      printf("yaml stream: start block entry\n");
      break;
    case YAML_BLOCK_MAPPING_START_TOKEN:
      printf("yaml stream: block mapping start\n");
      block_mapping_level++;
      break;
    case YAML_BLOCK_END_TOKEN:
      printf("yaml stream: end block\n");
      block_mapping_level--;
      break;
    case YAML_SCALAR_TOKEN:
      printf("yaml stream: scalar = %s\n", token.data.scalar.value);
      if (block_mapping_level == 1 && is_scalar_key)
        block_name = strdup((char *)token.data.scalar.value);

      else if (block_mapping_level == 2) {
        if (is_scalar_key)
          key_name = strdup((char *)token.data.scalar.value);

        else {
          char *value = (char *)token.data.scalar.value;
          if (strncmp(block_name, "cpu", strlen("cpu")) == 0) {
            _hash_map_set(&cpu_config_hash_map, key_name, value);
          } else if (strncmp(block_name, "memory", strlen("memory")) == 0) {
            _hash_map_set(&mem_config_hash_map, key_name, value);
          } else if (strncmp(block_name, "enable_stats",
                             strlen("enable_stats")) == 0) {
            _hash_map_set(&stats_config_hash_map, key_name, value);
          } else if (strncmp(block_name, "logs", strlen("logs")) == 0) {
            _hash_map_set(&logs_config_hash_map, key_name, value);
          }
        }
      }
      break;
    default:
      printf("yaml stream: token type = %d\n", token.type);
    }

    if (token.type != YAML_STREAM_END_TOKEN)
      yaml_token_delete(&token);
  } while (token.type != YAML_STREAM_END_TOKEN);
  yaml_token_delete(&token);

  yaml_parser_delete(&parser);
  fclose(config_file);
  free(block_name);
  free(key_name);

  parsed_configs.cpu_conf = cpu_config_hash_map;
  parsed_configs.mem_conf = mem_config_hash_map;
  parsed_configs.stat_conf = stats_config_hash_map;
  parsed_configs.log_conf = logs_config_hash_map;

  return &parsed_configs;
}
