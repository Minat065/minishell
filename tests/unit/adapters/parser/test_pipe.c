#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "../../../../include/interfaces/parser_interface.h"
#include "../../../../include/entities/token.h"
#include "../../../../include/entities/command.h"

/* テスト用のヘルパー関数（他のテストファイルと同じ） */
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

static void free_token_stream(TokenStream *stream)
{
    if (!stream)
        return;
    
    Token *current = stream->head;
    while (current) {
        Token *next = current->next;
        free(current->text);
        if (current->type == TOKEN_WORD)
            free(current->value.word);
        free(current);
        current = next;
    }
    
    free(stream->error_message);
    free(stream);
}

/* テスト1: 単純なパイプ */
void test_simple_pipe(void)
{
    printf("Test: simple pipe 'ls | grep txt'... ");
    
    // トークンストリームを作成
    // ls | grep txt -> [WORD("ls"), PIPE, WORD("grep"), WORD("txt"), EOF]
    TokenStream *stream = create_token_stream();
    add_token_to_stream(stream, create_token(TOKEN_WORD, "ls"));
    add_token_to_stream(stream, create_token(TOKEN_PIPE, "|"));
    add_token_to_stream(stream, create_token(TOKEN_WORD, "grep"));
    add_token_to_stream(stream, create_token(TOKEN_WORD, "txt"));
    add_token_to_stream(stream, create_token(TOKEN_EOF, ""));
    
    // パース実行
    t_parse_result *result = parse(stream);
    
    // 結果の検証
    assert(result != NULL);
    assert(result->error_msg == NULL);
    assert(result->ast != NULL);
    
    // パイプラインの検証
    t_pipeline *pipeline = result->ast;
    assert(pipeline != NULL);
    assert(pipeline->next == NULL);  // 単一のパイプライン
    
    // 最初のコマンド (ls)
    t_cmd *cmd1 = pipeline->cmds;
    assert(cmd1 != NULL);
    assert(strcmp(cmd1->argv[0], "ls") == 0);
    assert(cmd1->argv[1] == NULL);
    assert(cmd1->redirects == NULL);
    
    // 2番目のコマンド (grep txt)
    t_cmd *cmd2 = cmd1->next;
    assert(cmd2 != NULL);
    assert(strcmp(cmd2->argv[0], "grep") == 0);
    assert(strcmp(cmd2->argv[1], "txt") == 0);
    assert(cmd2->argv[2] == NULL);
    assert(cmd2->redirects == NULL);
    assert(cmd2->next == NULL);  // これ以上のコマンドなし
    
    // クリーンアップ
    free_parse_result(result);
    free_token_stream(stream);
    
    printf("PASSED\n");
}

/* テスト2: 複数のパイプ */
void test_multiple_pipes(void)
{
    printf("Test: multiple pipes 'cat file | grep pattern | wc -l'... ");
    
    // トークンストリームを作成
    TokenStream *stream = create_token_stream();
    add_token_to_stream(stream, create_token(TOKEN_WORD, "cat"));
    add_token_to_stream(stream, create_token(TOKEN_WORD, "file"));
    add_token_to_stream(stream, create_token(TOKEN_PIPE, "|"));
    add_token_to_stream(stream, create_token(TOKEN_WORD, "grep"));
    add_token_to_stream(stream, create_token(TOKEN_WORD, "pattern"));
    add_token_to_stream(stream, create_token(TOKEN_PIPE, "|"));
    add_token_to_stream(stream, create_token(TOKEN_WORD, "wc"));
    add_token_to_stream(stream, create_token(TOKEN_WORD, "-l"));
    add_token_to_stream(stream, create_token(TOKEN_EOF, ""));
    
    // パース実行
    t_parse_result *result = parse(stream);
    
    // 結果の検証
    assert(result != NULL);
    assert(result->error_msg == NULL);
    
    // コマンドチェーンの検証
    t_cmd *cmd1 = result->ast->cmds;
    assert(strcmp(cmd1->argv[0], "cat") == 0);
    assert(strcmp(cmd1->argv[1], "file") == 0);
    
    t_cmd *cmd2 = cmd1->next;
    assert(cmd2 != NULL);
    assert(strcmp(cmd2->argv[0], "grep") == 0);
    assert(strcmp(cmd2->argv[1], "pattern") == 0);
    
    t_cmd *cmd3 = cmd2->next;
    assert(cmd3 != NULL);
    assert(strcmp(cmd3->argv[0], "wc") == 0);
    assert(strcmp(cmd3->argv[1], "-l") == 0);
    assert(cmd3->next == NULL);
    
    // クリーンアップ
    free_parse_result(result);
    free_token_stream(stream);
    
    printf("PASSED\n");
}

/* テスト3: パイプの前後にコマンドがない場合（エラーケース） */
void test_pipe_without_command(void)
{
    printf("Test: pipe without command '| grep'... ");
    
    // トークンストリームを作成
    TokenStream *stream = create_token_stream();
    add_token_to_stream(stream, create_token(TOKEN_PIPE, "|"));
    add_token_to_stream(stream, create_token(TOKEN_WORD, "grep"));
    add_token_to_stream(stream, create_token(TOKEN_EOF, ""));
    
    // パース実行
    t_parse_result *result = parse(stream);
    
    // エラーが発生することを確認
    assert(result != NULL);
    assert(result->error_msg != NULL);
    assert(result->ast == NULL);
    
    // クリーンアップ
    free_parse_result(result);
    free_token_stream(stream);
    
    printf("PASSED\n");
}

/* テスト4: パイプの後にコマンドがない場合（エラーケース） */
void test_pipe_at_end(void)
{
    printf("Test: pipe at end 'ls |'... ");
    
    // トークンストリームを作成
    TokenStream *stream = create_token_stream();
    add_token_to_stream(stream, create_token(TOKEN_WORD, "ls"));
    add_token_to_stream(stream, create_token(TOKEN_PIPE, "|"));
    add_token_to_stream(stream, create_token(TOKEN_EOF, ""));
    
    // パース実行
    t_parse_result *result = parse(stream);
    
    // エラーが発生することを確認
    assert(result != NULL);
    assert(result->error_msg != NULL);
    assert(result->ast == NULL);
    
    // クリーンアップ
    free_parse_result(result);
    free_token_stream(stream);
    
    printf("PASSED\n");
}

/* メイン関数 */
int main(void)
{
    printf("=== Parser Tests: Pipe Handling ===\n");
    
    test_simple_pipe();
    test_multiple_pipes();
    test_pipe_without_command();
    test_pipe_at_end();
    
    printf("\nAll tests passed!\n");
    return 0;
}