
BUILD := skylake_add_n.o haswell_add_n.o patch1_add_n.o

all: $(BUILD)

%.o:%.as
	yasm -f elf -o $@ $^

.PHONY: clean all
clean:
	rm -f $(BUILD)

