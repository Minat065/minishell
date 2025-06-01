NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror -g

# ディレクトリ
SRC_DIR = src
OBJ_DIR = obj
INC_DIR = include
TESTS_DIR = tests/unit/adapters/parser
LIBFT_DIR = srcs/libft

# libft
LIBFT = $(LIBFT_DIR)/libft.a

# ライブラリソースファイル（main.c除く）
LIB_SRCS = $(SRC_DIR)/adapters/parser/parser.c \
           $(SRC_DIR)/adapters/parser/parser_factory.c \
           $(SRC_DIR)/adapters/parser/parser_utils.c \
           $(SRC_DIR)/adapters/parser/redirection_parser.c \
           $(SRC_DIR)/adapters/parser/command_parser.c \
           $(SRC_DIR)/adapters/parser/pipeline_parser.c \
           $(SRC_DIR)/entities/command.c

# メインプログラム用ソースファイル
SRCS = $(SRC_DIR)/main.c $(LIB_SRCS)

# オブジェクトファイル
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# インクルード
INCLUDES = -I$(INC_DIR) -I$(LIBFT_DIR)

# テスト関連
TEST_SRCS = $(TESTS_DIR)/test_simple_command.c \
            $(TESTS_DIR)/test_quote_handling.c \
            $(TESTS_DIR)/test_pipe.c \
            $(TESTS_DIR)/test_redirection.c \
            $(TESTS_DIR)/test_operators.c \
            $(TESTS_DIR)/test_heredoc.c
TEST_BINS = $(TEST_SRCS:.c=)

all: $(LIBFT) $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# テストのビルドと実行
test: test_parser

test_parser: test_simple_command test_quote_handling test_pipe test_redirection test_operators test_heredoc

test_simple_command: $(TESTS_DIR)/test_simple_command
	./$(TESTS_DIR)/test_simple_command

test_quote_handling: $(TESTS_DIR)/test_quote_handling
	./$(TESTS_DIR)/test_quote_handling

test_pipe: $(TESTS_DIR)/test_pipe
	./$(TESTS_DIR)/test_pipe

test_redirection: $(TESTS_DIR)/test_redirection
	./$(TESTS_DIR)/test_redirection

test_operators: $(TESTS_DIR)/test_operators
	./$(TESTS_DIR)/test_operators

test_heredoc: $(TESTS_DIR)/test_heredoc
	./$(TESTS_DIR)/test_heredoc

$(TESTS_DIR)/test_simple_command: $(LIBFT) $(TESTS_DIR)/test_simple_command.c $(LIB_SRCS)
	$(CC) $(CFLAGS) $(INCLUDES) $(TESTS_DIR)/test_simple_command.c $(LIB_SRCS) $(LIBFT) -o $@

$(TESTS_DIR)/test_quote_handling: $(LIBFT) $(TESTS_DIR)/test_quote_handling.c $(LIB_SRCS)
	$(CC) $(CFLAGS) $(INCLUDES) $(TESTS_DIR)/test_quote_handling.c $(LIB_SRCS) $(LIBFT) -o $@

$(TESTS_DIR)/test_pipe: $(LIBFT) $(TESTS_DIR)/test_pipe.c $(LIB_SRCS)
	$(CC) $(CFLAGS) $(INCLUDES) $(TESTS_DIR)/test_pipe.c $(LIB_SRCS) $(LIBFT) -o $@

$(TESTS_DIR)/test_redirection: $(LIBFT) $(TESTS_DIR)/test_redirection.c $(LIB_SRCS)
	$(CC) $(CFLAGS) $(INCLUDES) $(TESTS_DIR)/test_redirection.c $(LIB_SRCS) $(LIBFT) -o $@

$(TESTS_DIR)/test_operators: $(LIBFT) $(TESTS_DIR)/test_operators.c $(LIB_SRCS)
	$(CC) $(CFLAGS) $(INCLUDES) $(TESTS_DIR)/test_operators.c $(LIB_SRCS) $(LIBFT) -o $@

$(TESTS_DIR)/test_heredoc: $(LIBFT) $(TESTS_DIR)/test_heredoc.c $(LIB_SRCS)
	$(CC) $(CFLAGS) $(INCLUDES) $(TESTS_DIR)/test_heredoc.c $(LIB_SRCS) $(LIBFT) -o $@

clean:
	rm -rf $(OBJ_DIR)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	rm -f $(TEST_BINS)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re test test_parser test_simple_command test_quote_handling test_pipe test_redirection test_operators test_heredoc