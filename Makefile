CC ?= gcc
DCC ?= ldc2
DFLAGS = -O3 -flto=full -boundscheck=off -release
WNOFLAGS = -Wno-unused-macros -Wno-reserved-identifier
CFLAGS = -march=native -O3 $(WNOFLAGS) \
		 -Wall -Wextra -Wpedantic  \
		 -D_FORTIFY_SOURCE=0
ifeq ($(CC), clang)
	CFLAGS += -Weverything -D__CLANG_COMPILER__
else
	CFLAGS += -D__GCC_COMPILER__
endif
TARGET = fastsearch
$(TARGET): remove
	$(MAKE) remove
	mkdir -p bin
	$(CC) $(CFLAGS) -o bin/$@ $@.c
	$(CC) $(CFLAGS) -o bin/$@-O $@-O.c -lgmp
	$(DCC) $(DFLAGS) -of=bin/$@-d $@.d

remove:
	@rm -rf $(TARGET)
