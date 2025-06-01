NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror -g

# ディレクトリ
SRCS_DIR = srcs
OBJS_DIR = objs
INCLUDES_DIR = includes
TESTS_DIR = tests
LIBFT_DIR = $(SRCS_DIR)/libft

# libft
LIBFT = $(LIBFT_DIR)/libft.a

# ソースファイル
SRCS = $(SRCS_DIR)/parser/parser.c

# オブジェクトファイル
OBJS = $(SRCS:.c=.o)

# インクルード
INCLUDES = -I$(INCLUDES_DIR) -I$(LIBFT_DIR)

# テスト関連
TEST_SRCS = $(TESTS_DIR)/parser/test_simple_command.c \
            $(TESTS_DIR)/parser/test_quote_handling.c \
            $(TESTS_DIR)/parser/test_pipe.c \
            $(TESTS_DIR)/parser/test_redirection.c \
            $(TESTS_DIR)/parser/test_operators.c \
            $(TESTS_DIR)/parser/test_heredoc.c
TEST_BINS = $(TEST_SRCS:.c=)

all: $(LIBFT) $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# テストのビルドと実行
test: test_parser

test_parser: test_simple_command test_quote_handling test_pipe test_redirection test_operators test_heredoc

test_simple_command: $(TESTS_DIR)/parser/test_simple_command
	./$(TESTS_DIR)/parser/test_simple_command

test_quote_handling: $(TESTS_DIR)/parser/test_quote_handling
	./$(TESTS_DIR)/parser/test_quote_handling

test_pipe: $(TESTS_DIR)/parser/test_pipe
	./$(TESTS_DIR)/parser/test_pipe

test_redirection: $(TESTS_DIR)/parser/test_redirection
	./$(TESTS_DIR)/parser/test_redirection

test_operators: $(TESTS_DIR)/parser/test_operators
	./$(TESTS_DIR)/parser/test_operators

test_heredoc: $(TESTS_DIR)/parser/test_heredoc
	./$(TESTS_DIR)/parser/test_heredoc

$(TESTS_DIR)/parser/test_simple_command: $(LIBFT) $(TESTS_DIR)/parser/test_simple_command.c $(SRCS_DIR)/parser/parser.c
	$(CC) $(CFLAGS) $(INCLUDES) $(TESTS_DIR)/parser/test_simple_command.c $(SRCS_DIR)/parser/parser.c $(LIBFT) -o $@

$(TESTS_DIR)/parser/test_quote_handling: $(LIBFT) $(TESTS_DIR)/parser/test_quote_handling.c $(SRCS_DIR)/parser/parser.c
	$(CC) $(CFLAGS) $(INCLUDES) $(TESTS_DIR)/parser/test_quote_handling.c $(SRCS_DIR)/parser/parser.c $(LIBFT) -o $@

$(TESTS_DIR)/parser/test_pipe: $(LIBFT) $(TESTS_DIR)/parser/test_pipe.c $(SRCS_DIR)/parser/parser.c
	$(CC) $(CFLAGS) $(INCLUDES) $(TESTS_DIR)/parser/test_pipe.c $(SRCS_DIR)/parser/parser.c $(LIBFT) -o $@

$(TESTS_DIR)/parser/test_redirection: $(LIBFT) $(TESTS_DIR)/parser/test_redirection.c $(SRCS_DIR)/parser/parser.c
	$(CC) $(CFLAGS) $(INCLUDES) $(TESTS_DIR)/parser/test_redirection.c $(SRCS_DIR)/parser/parser.c $(LIBFT) -o $@

$(TESTS_DIR)/parser/test_operators: $(LIBFT) $(TESTS_DIR)/parser/test_operators.c $(SRCS_DIR)/parser/parser.c
	$(CC) $(CFLAGS) $(INCLUDES) $(TESTS_DIR)/parser/test_operators.c $(SRCS_DIR)/parser/parser.c $(LIBFT) -o $@

$(TESTS_DIR)/parser/test_heredoc: $(LIBFT) $(TESTS_DIR)/parser/test_heredoc.c $(SRCS_DIR)/parser/parser.c
	$(CC) $(CFLAGS) $(INCLUDES) $(TESTS_DIR)/parser/test_heredoc.c $(SRCS_DIR)/parser/parser.c $(LIBFT) -o $@

clean:
	rm -rf $(OBJS_DIR)
	rm -f $(OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	rm -f $(TEST_BINS)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re test test_parser test_simple_command test_quote_handling test_pipe test_redirection test_operators test_heredoc