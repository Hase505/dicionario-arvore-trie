CC      := gcc
STD     := -std=c11
WARN    := -Wall -Wextra -Werror -Wreturn-type

CFLAGS  := $(STD) $(WARN)
LDFLAGS :=

SAN_FLAGS := -fsanitize=address,undefined -fno-omit-frame-pointer -g

BIN     := dicionario
SRC_DIR := src
OBJ_DIR := build

SRCS := $(shell find $(SRC_DIR) -name '*.c')
OBJS := $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

.PHONY: all clean sanitize format-fix check check-format check-tidy check-cppcheck

all: $(BIN)

$(BIN): $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR) $(BIN)

sanitize: CFLAGS += $(SAN_FLAGS)
sanitize: LDFLAGS += $(SAN_FLAGS)
sanitize: clean all

format-fix:
	clang-format -i $(SRCS)

check: check-format check-tidy check-cppcheck

check-format:
	clang-format --dry-run --Werror $(SRCS)

check-tidy:
	clang-tidy $(SRCS) \
		--warnings-as-errors='*' \
		-- -std=c11 -Wall -Wextra

check-cppcheck:
	cppcheck \
		--language=c \
		--std=c11 \
		--enable=warning,style \
		--error-exitcode=1 \
		$(SRC_DIR)

