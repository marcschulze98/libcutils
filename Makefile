all:
	gcc -Og -g -march=native -shared -fPIC -fstrict-aliasing vector.c dyn_string.c -o cutils.so -flto \
	-Wall -Wpedantic -Wnull-dereference -Wshadow -Wconversion -Wstrict-prototypes -Wmissing-prototypes -Wcast-qual -Wstrict-overflow=5 -Wunreachable-code -Wno-unused-parameter
