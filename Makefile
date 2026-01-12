# 出力ファイル名
NAME = minishell

SRCS_DIR = src
INCLUDES_DIR = include
DOMAIN_DIR = $(SRCS_DIR)/domain
USE_CASE_DIR = $(SRCS_DIR)/usecase
ADAPTERS_DIR = $(SRCS_DIR)/adapters
UTILS_DIR = $(SRCS_DIR)/utils

# Domain layer sources
DOMAIN_SRCS	=		$(wildcard $(DOMAIN_DIR)/token/*.c) \
					$(wildcard $(DOMAIN_DIR)/command/*.c)

# Use case layer sources
LEXER_SRCS	=		$(wildcard $(USE_CASE_DIR)/lexer/*.c) \
					$(wildcard $(USE_CASE_DIR)/lexer/handler/*.c)
ENV_SRCS	=		$(wildcard $(USE_CASE_DIR)/env/*.c)
EXECUTOR_SRCS	=	$(wildcard $(USE_CASE_DIR)/executor/*.c)
BUILTIN_SRCS	=	$(wildcard $(USE_CASE_DIR)/builtin/*.c)
ASSIGNMENT_SRCS	=	$(wildcard $(USE_CASE_DIR)/assignment/*.c)
EXIT_SRCS	=		$(wildcard $(USE_CASE_DIR)/exit/*.c)
SIGNAL_SRCS	=		$(wildcard $(USE_CASE_DIR)/signal/*.c)

# Adapters layer sources
ADAPT_CLI_SRCS	=	$(wildcard $(ADAPTERS_DIR)/cli/*.c)
ADAPT_PARSER_SRCS	=	$(wildcard $(ADAPTERS_DIR)/parser/*.c)
ADAPT_SYS_SRCS	=	$(wildcard $(ADAPTERS_DIR)/system/*.c)
ADAPT_IO_SRCS	=	$(wildcard $(ADAPTERS_DIR)/io/*.c)

# Infrastructure layer sources
INFRA_SRCS	=	$(wildcard $(SRCS_DIR)/infrastructure/*.c)

# Utilities
UTILS_SRCS	=		$(wildcard $(UTILS_DIR)/libft_custom/*.c)

# ソースファイル一覧
SRCS			=	$(DOMAIN_SRCS) \
					$(LEXER_SRCS) \
					$(ENV_SRCS) \
					$(EXECUTOR_SRCS) \
					$(BUILTIN_SRCS) \
					$(ASSIGNMENT_SRCS) \
					$(EXIT_SRCS) \
					$(SIGNAL_SRCS) \
					$(ADAPT_CLI_SRCS) \
					$(ADAPT_PARSER_SRCS) \
					$(ADAPT_SYS_SRCS) \
					$(ADAPT_IO_SRCS) \
					$(INFRA_SRCS) \
					$(UTILS_SRCS) \
					$(SRCS_DIR)/main.c \
					$(SRCS_DIR)/main_helper.c
OBJS			=	$(SRCS:%.c=%.o)
LIBFT_DIR		=	$(SRCS_DIR)/utils/libft
LIBFT_A			=	libft.a
# ヘッダファイルのあるディレクトリ
INCLUDES		=	-I$(INCLUDES_DIR) -I$(LIBFT_DIR)
LDFLAGS			=	-lreadline -L$(LIBFT_DIR) -lft
START_COMPILING	=	0

# コンパイルオプション
CFLAGS			=	-Wall -Wextra -Werror -g $(INCLUDES)

# コンパイルコマンド
CC				=	cc

# 依存関係
all: $(NAME)

$(NAME): $(OBJS) $(LIBFT_A)
	@echo "\033[0;31m========================================\033[0m\033[0;32m$(@F)\033[0m\033[0;31m========================================\033[0m"
	@$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $(NAME)
	@echo "Make \033[0;32m$(@F)\033[0m.";
.c.o:
	@if [ $(START_COMPILING) -eq 0 ]; then \
		echo "\033[0;31m==============================\033[0m\033[0;32m$(NAME)'s Objects Compiling\033[0m\033[0;31m==============================\033[0m"; \
		$(eval START_COMPILING := 1) \
	fi
	@$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)
	@echo "Compiling $<."

$(LIBFT_A) :
	@echo "\033[0;31m========================================\033[0m\033[0;32m$(@F)\033[0m\033[0;31m========================================\033[0m"
	@$(MAKE) bonus -C $(LIBFT_DIR)
	@echo "Make \033[0;32m$(@F)\033[0m."

localclean:
	@$(RM) $(OBJS)
	@echo "Removed object files."

clean: localclean
	@$(MAKE) clean -C $(LIBFT_DIR)
	@echo "Cleaned minishell."

fclean: clean
	@$(RM) $(NAME)
	@echo "Removed executable and tests."

re: clean all

bonus: all

# Norm check using norminette
# Run 'make norm-install' first to install norminette
NORM_CMD = python3 -m norminette

norm-install:
	@echo "\033[0;33mInstalling norminette...\033[0m"
	@pip3 install norminette --quiet
	@echo "\033[0;32mnorminette installed!\033[0m"

norm:
	@if ! python3 -c "import norminette" 2>/dev/null; then \
		echo "\033[0;31mnorminette not found. Run 'make norm-install' first.\033[0m"; \
		exit 1; \
	fi
	@echo "\033[0;33mChecking norm compliance...\033[0m"
	@$(NORM_CMD) $(SRCS_DIR) $(INCLUDES_DIR) 2>/dev/null | grep -v "^$$" || true

.PHONY: all clean fclean re bonus localclean norm norm-install