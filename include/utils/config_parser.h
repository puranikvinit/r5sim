#ifndef CONFIG_PARSER_H
#define CONFIG_PARSER_H

#include <stdio.h>
#include <string.h>
#include <yaml.h>

#ifndef CONFIG_FILE_PATH
#define CONFIG_FILE_PATH "config.yaml"
#endif

typedef struct {
  int register_file_length;
  int register_file_width;
  int pipeline_stages;
} cpu_config;

typedef struct {
  int l1_icache_size;
  int l1_dcache_size;
  int l2_cache_size;
  int dram_size;
} mem_config;

typedef struct {
  int cache_misses;
  int branch_mispredictions;
  int memory_heatmap;
  int register_heatmap;
} stats_config;

typedef enum { INFO, DEBUG, WARN, ERROR } verbosity_levels;

typedef struct {
  verbosity_levels verbosity_level;
} logs_config;

typedef struct {
  cpu_config cpu_conf;
  mem_config mem_conf;
  stats_config stat_conf;
  logs_config log_conf;
} configs;

configs *parse_configs();

#endif // !CONFIG_PARSER_H
