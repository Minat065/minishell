#ifndef PARSER_INTERFACE_H
#define PARSER_INTERFACE_H

#include "../entities/token.h"
#include "../entities/command.h"

/* パース結果構造体 */
typedef struct s_parse_result {
    t_pipeline *ast;              // パース結果のAST
    char *error_msg;              // エラーメッセージ
    int error_line;               // エラー行
    int error_column;             // エラー列
} t_parse_result;

/* パーサー関数のプロトタイプ */
t_parse_result *parse(TokenStream *tokens);
void free_parse_result(t_parse_result *result);

#endif /* PARSER_INTERFACE_H */