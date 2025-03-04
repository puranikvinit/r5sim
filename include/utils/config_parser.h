#ifndef CONFIG_PARSER_H
#define CONFIG_PARSER_H

#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <yaml.h>

#ifndef CONFIG_FILE_PATH
#define CONFIG_FILE_PATH "config.yaml"
#endif

#ifndef CONFIG_DEFINES_FILE
#define CONFIG_DEFINES_FILE "include/config_defines.h"
#endif

typedef enum { INFO, DEBUG, WARN, ERROR } verbosity_levels;

// 0: success
// 1: file read failed
// 2: parser init failed
int parse_configs();

void _str_to_upper(char *str);

#endif // !CONFIG_PARSER_H
