LINK_TARGET = dyn-background
OBJS = \
	dyn-background.o \
	resolution.o
REBUILDABLES = $(OBJS) $(LINK_TARGET)

all: $(LINK_TARGET)

clean:
	rm -f $(REBUILDABLES)

$(LINK_TARGET): $(OBJS)
	gcc -o $@ $^ -lrt

%.o: %.c
	gcc -o $@ -c $<
