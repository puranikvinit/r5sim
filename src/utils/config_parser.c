#include "utils/config_parser.h"

configs parsed_configs;

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

  cpu_config cpu_parsed;
  mem_config mem_parsed;
  stats_config stats_parsed;
  logs_config logs_parsed;

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
          int value = atoi(((char *)token.data.scalar.value));

          if (strncmp(block_name, "cpu", strlen("cpu")) == 0) {
            if (strncmp(key_name, "register_file_length",
                        strlen("register_file_length")) == 0) {
              cpu_parsed.register_file_length = value;
            } else if (strncmp(key_name, "register_file_width",
                               strlen("register_file_width")) == 0)
              cpu_parsed.register_file_width = value;
            else if (strncmp(key_name, "pipeline_stages",
                             strlen("pipeline_stages")) == 0)
              cpu_parsed.pipeline_stages = value;
          } else if (strncmp(block_name, "memory", strlen("memory")) == 0) {
            if (strncmp(key_name, "l1_icache_size", strlen("l1_icache_size")) ==
                0)
              mem_parsed.l1_icache_size = value;
            else if (strncmp(key_name, "l1_dcache_size",
                             strlen("l1_dcache_size")) == 0)
              mem_parsed.l1_dcache_size = value;
            else if (strncmp(key_name, "l2_cache_size",
                             strlen("l2_cache_size")) == 0)
              mem_parsed.l2_cache_size = value;
            else if (strncmp(key_name, "dram_size", strlen("dram_size")) == 0)
              mem_parsed.dram_size = value;
          } else if (strncmp(block_name, "enable_stats",
                             strlen("enable_stats")) == 0) {
            if (strncmp(key_name, "cache_misses", strlen("cache_misses")) == 0)
              stats_parsed.cache_misses = value;
            else if (strncmp(key_name, "branch_mispredictions",
                             strlen("branch_mispredictions")) == 0)
              stats_parsed.branch_mispredictions = value;
            else if (strncmp(key_name, "memory_heatmap",
                             strlen("memory_heatmap")) == 0)
              stats_parsed.memory_heatmap = value;
            else if (strncmp(key_name, "register_heatmap",
                             strlen("register_heatmap")) == 0)
              stats_parsed.register_heatmap = value;
          } else if (strncmp(block_name, "logs", strlen("logs")) == 0) {
            if (strncmp(key_name, "verbosity_level",
                        strlen("verbosity_level")) == 0) {
              logs_parsed.verbosity_level = value;
            }
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

  parsed_configs.cpu_conf = cpu_parsed;
  parsed_configs.mem_conf = mem_parsed;
  parsed_configs.stat_conf = stats_parsed;
  parsed_configs.log_conf = logs_parsed;

  return &parsed_configs;
}
