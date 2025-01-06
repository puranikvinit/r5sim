LLVM_PATH = /opt/homebrew/opt/llvm/bin/
CLANG_FLAGS = -Wall -g -O2 -ffreestanding -Iinclude/ -I /opt/homebrew/Cellar/llvm/18.1.6/lib/clang/18/include/

build: clean

clean:
	/bin/rm -f *.o
