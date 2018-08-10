TARGET   = snake

CC       = gcc
# compiling flags here
CFLAGS   = -Wall -g

LINKER   = gcc
# linking flags here
LFLAGS   = -Wall -I -lncurses -ltinfo

# change these to proper directories where each file should be
SRCDIR   = src
OBJDIR   = obj
BINDIR   = bin

SOURCES  := $(wildcard $(SRCDIR)/*.c)
INCLUDES := $(wildcard $(SRCDIR)/*.h)
OBJECTS  := $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
rm       = rm -f
mkdir	 = mkdir -p $(OBJDIR)


$(BINDIR)/$(TARGET): $(OBJECTS)
	@$(LINKER) $(OBJECTS) $(LFLAGS) -o $@
	@echo "link complete"

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.c
	@$(mkdir)
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "compiled "$<" successfully"

.PHONY: clean
clean:
	@$(rm) $(OBJECTS)
	@echo "cleaned"

.PHONY: remove
remove: clean
	@$(rm) $(BINDIR)/$(TARGET)
	@echo "removed"
