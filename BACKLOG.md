# Minishell バックログ

作成日: 2026-01-08
評価レポート: EVALUATION_REPORT.md

---

## 優先度: 高 (必須機能)

### Issue #1: ダブルクォート内スペースの処理バグ
**状態**: 未着手
**影響**: 8. ダブルクォート、11. export

**問題**:
```bash
export VAR="hello world"
# 期待: VAR=hello world
# 実際: VAR= (空), "hello world" が別引数に
```

**原因**: Lexerでクォート内のスペースが引数区切りとして扱われている

**修正箇所**:
- `src/usecase/lexer/handler/word_handler.c`
- `src/usecase/lexer/handler/double_quote_handler.c`

**テストケース**:
- [ ] `export VAR="hello world"` → `echo $VAR` で `hello world`
- [ ] `export VAR="a b c"` → 正しく設定される
- [ ] `echo "hello world"` → 正常動作（既存）

---

### Issue #2: Heredoc (`<<`) 未実装
**状態**: 未着手
**影響**: 17. リダイレクション

**問題**:
```bash
cat << EOF
hello
world
EOF
# 出力: "Heredoc with process service not yet implemented"
```

**修正箇所**:
- `src/usecase/executor/heredoc_redirection.c`

**テストケース**:
- [ ] `cat << EOF` → 複数行入力を受け付ける
- [ ] heredoc内で変数展開が動作する
- [ ] `cat << 'EOF'` → 変数展開なし

---

## 優先度: 中 (ボーナス機能)

### Issue #3: 論理演算子 (`&&`, `||`, `;`) 未実装
**状態**: 未着手
**影響**: ボーナス - And, Or

**問題**:
```bash
true && echo success   # → 何も出力されない
false || echo fallback # → 何も出力されない
echo a; echo b         # → "a; echo b" と出力
```

**原因**: Lexerに `&&` と `;` のハンドラーがない

**修正箇所**:
- `src/usecase/lexer/token_type_handlers.c` - 新しいハンドラー追加
- `src/usecase/lexer/handler/` - 新規ファイル作成
- `src/usecase/lexer/handler/word_handler.c` - `is_word()` に除外条件追加

**テストケース**:
- [ ] `true && echo success` → `success`
- [ ] `false && echo fail` → 何も出力されない
- [ ] `false || echo fallback` → `fallback`
- [ ] `true || echo skip` → 何も出力されない
- [ ] `echo a; echo b` → `a` と `b` が別行に

---

### Issue #4: ワイルドカード (`*`) 未実装
**状態**: 未着手
**影響**: ボーナス - Wildcard

**問題**:
```bash
echo *
# 期待: 現在ディレクトリのファイル一覧
# 実際: * (リテラル)
```

**修正箇所**:
- 新規: glob展開機能の実装

**テストケース**:
- [ ] `echo *` → ファイル一覧
- [ ] `echo *.c` → .cファイル一覧
- [ ] `echo "*.c"` → `*.c` (リテラル)

---

## 実装順序

1. **Issue #1**: ダブルクォート処理 (必須・影響大)
2. **Issue #2**: Heredoc (必須)
3. **Issue #3**: 論理演算子 (ボーナス・比較的簡単)
4. **Issue #4**: ワイルドカード (ボーナス・複雑)

---

## 完了条件

- [ ] 全必須機能が42評価シートの要件を満たす
- [ ] valgrindでメモリリークなし
- [ ] クラッシュなし
