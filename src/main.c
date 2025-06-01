/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mirokugo <mirokugo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 18:35:00 by mirokugo          #+#    #+#             */
/*   Updated: 2025/06/01 18:35:00 by mirokugo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "interfaces/parser_interface.h"
#include "entities/token.h"
#include "entities/command.h"

/* テスト用のトークン作成ヘルパー */
static Token *create_token(TokenType type, const char *text)
{
	Token *token = malloc(sizeof(Token));
	if (!token)
		return NULL;
	
	token->type = type;
	token->text = strdup(text);
	token->length = strlen(text);
	token->line_number = 1;
	token->column = 1;
	token->next = NULL;
	
	if (type == TOKEN_WORD) {
		token->value.word = strdup(text);
	}
	
	return token;
}

/* トークンストリーム作成ヘルパー */
static TokenStream *create_token_stream(void)
{
	TokenStream *stream = malloc(sizeof(TokenStream));
	if (!stream)
		return NULL;
	
	stream->head = NULL;
	stream->current = NULL;
	stream->count = 0;
	stream->error_message = NULL;
	stream->error_line = 0;
	stream->error_column = 0;
	
	return stream;
}

/* トークンをストリームに追加 */
static void add_token_to_stream(TokenStream *stream, Token *token)
{
	if (!stream->head) {
		stream->head = token;
		stream->current = token;
	} else {
		Token *last = stream->head;
		while (last->next)
			last = last->next;
		last->next = token;
	}
	stream->count++;
}

/* パース結果を表示 */
static void print_parse_result(t_parse_result *result)
{
	if (!result) {
		printf("❌ Parse failed: result is NULL\n");
		return;
	}
	
	if (result->error_msg) {
		printf("❌ Parse failed: %s\n", result->error_msg);
		return;
	}
	
	if (!result->ast) {
		printf("❌ Parse failed: AST is NULL\n");
		return;
	}
	
	printf("✅ Parse successful!\n");
	printf("📊 AST Structure:\n");
	
	t_pipeline *pipeline = result->ast;
	int pipeline_num = 1;
	
	while (pipeline) {
		printf("  🔗 Pipeline %d:\n", pipeline_num);
		
		t_cmd *cmd = pipeline->cmds;
		int cmd_num = 1;
		
		while (cmd) {
			printf("    📋 Command %d: ", cmd_num);
			if (cmd->argv && cmd->argv[0]) {
				printf("'%s'", cmd->argv[0]);
				for (int i = 1; cmd->argv[i]; i++) {
					printf(" '%s'", cmd->argv[i]);
				}
			}
			printf("\n");
			
			if (cmd->redirects) {
				printf("      ↪️  Redirections: ");
				t_redirect *redir = cmd->redirects;
				while (redir) {
					printf("[%d:%s] ", redir->type, redir->file);
					redir = redir->next;
				}
				printf("\n");
			}
			
			cmd = cmd->next;
			cmd_num++;
		}
		
		if (pipeline->connector != CONN_NONE) {
			printf("    🔗 Connector: %d\n", pipeline->connector);
		}
		
		pipeline = pipeline->next;
		pipeline_num++;
	}
}

/* 簡単なコマンドをテスト */
static void test_simple_command(const char *input)
{
	printf("\n🧪 Testing: \"%s\"\n", input);
	printf("==========================================\n");
	
	TokenStream *stream = create_token_stream();
	char *token_str = strdup(input);
	char *word = strtok(token_str, " ");
	
	while (word) {
		add_token_to_stream(stream, create_token(TOKEN_WORD, word));
		word = strtok(NULL, " ");
	}
	add_token_to_stream(stream, create_token(TOKEN_EOF, ""));
	
	t_parse_result *result = parse(stream);
	print_parse_result(result);
	
	if (result)
		free_parse_result(result);
	free(token_str);
	free(stream);
}

/* インタラクティブモード */
static void interactive_mode(void)
{
	char input[1024];
	
	printf("\n🎮 Interactive Parser Mode\n");
	printf("Enter commands to parse (type 'exit' to quit):\n");
	printf("==========================================\n");
	
	while (1) {
		printf("minishell> ");
		if (!fgets(input, sizeof(input), stdin))
			break;
		
		// 改行文字を除去
		input[strcspn(input, "\n")] = '\0';
		
		if (strcmp(input, "exit") == 0)
			break;
		
		if (strlen(input) == 0)
			continue;
		
		test_simple_command(input);
	}
	
	printf("\n👋 Goodbye!\n");
}

/* メイン関数 */
int main(int argc, char **argv)
{
	printf("🚀 Minishell Parser Demo\n");
	printf("==========================================\n");
	
	if (argc > 1 && strcmp(argv[1], "-i") == 0) {
		interactive_mode();
		return 0;
	}
	
	printf("📋 Running preset demos:\n\n");
	test_simple_command("ls");
	test_simple_command("ls -la");
	test_simple_command("echo hello world");
	test_simple_command("cat file.txt");
	test_simple_command("grep pattern input.txt");
	
	printf("\n💡 Tip: Run './minishell -i' for interactive mode!\n");
	printf("✨ Demo completed!\n");
	return 0;
}