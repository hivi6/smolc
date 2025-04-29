C_FILES := $(shell find src -name '*.c')

all: ${C_FILES}
	gcc -o smolc ${C_FILES}

.PHONY: clean
clean:
	rm smolc
