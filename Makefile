CC = gcc

CFLAGS  = -std=c23 -Wall -Wextra -Isrc -O2 -g -MMD -MP
LDFLAGS = -lopengl32 -lgdi32 -luser32

TARGET   = build\raw_renderer.exe
BUILDDIR = build

SHELL := cmd.exe
.SHELLFLAGS := /c

# dir /s /b returns absolute paths with backslashes, e.g.
# E:\projects\c\raw_renderer\src\main.c — normalize slashes, then
# strip the CURDIR prefix so we get relative paths like src/main.c
SOURCES := $(subst \,/,$(shell dir /s /b src\*.c 2>nul))
SOURCES := $(patsubst $(subst \,/,$(CURDIR))/%,%,$(SOURCES))

OBJECTS := $(patsubst src/%.c,$(BUILDDIR)/%.o,$(SOURCES))
DEPS    := $(OBJECTS:.o=.d)

all: $(TARGET)

debug: CFLAGS += -DDEBUG -O0
debug: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $^ $(LDFLAGS) -o $@

$(BUILDDIR)/%.o: src/%.c
	@if not exist "$(dir $@)" mkdir "$(dir $@)"
	$(CC) $(CFLAGS) -c $< -o $@

-include $(DEPS)

clean:
	if exist "$(BUILDDIR)" rd /s /q "$(BUILDDIR)"

.PHONY: all debug clean