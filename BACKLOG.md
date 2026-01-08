# Minishell バックログ

更新日: 2026-01-08

---

## 完了した修正

### ✅ Issue #1: ダブルクォート内スペースの処理
**状態**: 完了
```bash
export VAR="hello world" && echo $VAR  # → hello world
```

### ✅ Issue #2: Heredoc (`<<`)
**状態**: 完了
```bash
cat << EOF
hello
EOF
# → 正常動作
```

### ✅ Issue #3: 論理演算子 (`&&`, `||`, `;`)
**状態**: 完了
```bash
true && echo success   # → success
false || echo fallback # → fallback
echo a; echo b         # → a, b
```

### ✅ Issue #4: `cd -` (OLDPWD対応)
**状態**: 完了
```bash
cd /tmp && cd - && pwd  # → /home/user/minishell
```

---

## 残りの問題

### Issue #5: クォート連結バグ (優先度: 高)
**状態**: 未着手
**影響**: クォート処理の厳密な準拠

**問題**:
```bash
echo "hello"world
# 期待 (bash): helloworld
# 実際: hello world (スペースが入る)
```

**原因**: レキサーが引用符で囲まれた部分と囲まれていない部分を別々のトークンとして作成し、パーサーがそれらを連結していない

**修正箇所**:
- `src/usecase/lexer/handler/double_quote_handler.c`
- `src/usecase/lexer/handler/single_quote_handler.c`
- `src/adapters/parser/command_parser.c`

**テストケース**:
- [ ] `echo "hello"world` → `helloworld`
- [ ] `echo 'test'"$HOME"` → `test/root` (現在は動作)
- [ ] `echo hello"world"test` → `helloworldtest`

---

### Issue #6: ファイルディスクリプタリダイレクション未対応 (優先度: 中)
**状態**: 未着手
**影響**: 標準エラー出力のリダイレクト

**問題**:
```bash
echo test 2>&1
# 期待: test
# 実際: (何も出力されない)

cat nonexistent 2>&1
# 期待: エラーメッセージ
# 実際: (何も出力されない)
```

**原因**: `2>&1` の構文がパースされていない

**修正箇所**:
- `src/usecase/lexer/handler/redirect_output_or_append_handler.c`
- `src/adapters/parser/redirection_parser.c`
- `src/usecase/executor/redirection_handler.c`

**テストケース**:
- [ ] `echo test 2>&1` → `test`
- [ ] `ls nonexistent 2>&1` → エラーメッセージ
- [ ] `ls 2>/dev/null` → エラー抑制

---

### Issue #7: ワイルドカード (`*`) 未実装 (優先度: 低 - ボーナス)
**状態**: 未着手
**影響**: ボーナス - Wildcard

**問題**:
```bash
echo *
# 期待: 現在ディレクトリのファイル一覧
# 実際: * (リテラル)
```

**テストケース**:
- [ ] `echo *` → ファイル一覧
- [ ] `echo *.c` → .cファイル一覧
- [ ] `echo "*.c"` → `*.c` (リテラル)

---

## 現在の完成度

| 機能 | 状態 |
|------|------|
| 基本コマンド実行 | ✅ |
| パイプ | ✅ |
| リダイレクション (<, >, >>) | ✅ |
| ヒアドキュメント (<<) | ✅ |
| 環境変数展開 ($VAR, $?) | ✅ |
| シングルクォート | ✅ |
| ダブルクォート | ✅ |
| 組み込みコマンド (7個) | ✅ |
| 論理演算子 (&&, \|\|, ;) | ✅ |
| クォート連結 | ❌ |
| fdリダイレクション (2>&1) | ❌ |
| ワイルドカード (*) | ❌ (ボーナス) |

**完成度: 約95%** (必須項目は全て動作、エッジケースに問題あり)

---

## 実装優先順位

1. **Issue #5**: クォート連結 - 42評価でテストされる可能性あり
2. **Issue #6**: fdリダイレクション - 評価でテストされる可能性あり
3. **Issue #7**: ワイルドカード - ボーナス機能
