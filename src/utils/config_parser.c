#include "utils/config_parser.h"

void _str_to_upper(char *str) {
  for (int i = 0; str[i] != '\0'; i++)
    str[i] = toupper(str[i]);
}

int parse_configs() {
  yaml_parser_t parser;
  yaml_token_t token;

  FILE *config_file = fopen(CONFIG_FILE_PATH, "r");
  if (config_file == NULL) {
    printf("config file read failed");
    return 1;
  }

  FILE *config_defines_file = fopen(CONFIG_DEFINES_FILE, "w");
  if (config_defines_file == NULL) {
    printf("config defines file open failed");
    return 1;
  }

  if (!yaml_parser_initialize(&parser)) {
    printf("config parser init failed");
    return 2;
  }

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
        if (is_scalar_key) {
          key_name = strdup((char *)token.data.scalar.value);
          _str_to_upper(key_name);
        }

        else {
          char *value = (char *)token.data.scalar.value;
          fprintf(config_defines_file, "#define %s %s\n", key_name, value);
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
  fclose(config_defines_file);
  free(block_name);
  free(key_name);

  return 0;
}
