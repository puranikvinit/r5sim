CONFIG_FILE_PATH = '"/Users/kvp_933/r5sim/config.yaml"'

UTILS_SRC = $(wildcard src/utils/config_parser.c)
UTILS_OBJ = $(UTILS_SRC:.c=.o)

GCC_PATH = /opt/homebrew/opt/llvm/bin/
GCC_FLAGS = -Wall -g -O2 -ffreestanding -I"include/" -I"/opt/homebrew/Cellar/llvm/18.1.6/lib/clang/18/include/" -I"/opt/homebrew/Cellar/libyaml/0.2.5/include/" -L"/opt/homebrew/Cellar/libyaml/0.2.5/lib/" -lyaml -DCONFIG_FILE_PATH=$(CONFIG_FILE_PATH)
LD_FLAGS =

TARGET = r5sim

all: clean $(TARGET)

$(TARGET): $(UTILS_OBJ)
	$(GCC_PATH)gcc $(GCC_FLAGS) $(LD_FLAGS) main.c $^ -o $@

$(UTILS_OBJ): $(UTILS_SRC)
	$(GCC_PATH)gcc $(GCC_FLAGS) -c $< -o $@

clean:
	@echo "Cleaning up..."
	/bin/rm -f *.o *.out
