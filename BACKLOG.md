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

### ✅ Issue #5: クォート連結バグ
**状態**: 完了
**影響**: クォート処理の厳密な準拠

**修正内容**:
- トークンに`space_before`フィールドを追加
- レキサー状態に`last_token_end`フィールドを追加
- パーサーで隣接トークンを連結するロジックを実装

**テストケース**:
- [x] `echo "hello"world` → `helloworld`
- [x] `echo 'hello'world` → `helloworld`
- [x] `echo hello"world"test` → `helloworldtest`

---

### Issue #6: ファイルディスクリプタリダイレクション (優先度: 低)
**状態**: 対象外 (42 subject で必須ではない)
**影響**: 標準エラー出力のリダイレクト

**注記**: 42 minishell の subject によると、必須のリダイレクションは `<`, `>`, `<<`, `>>` のみ。
`2>&1` などの fd リダイレクションは必須要件に含まれていない。

**参照**: en.subject_minishell.pdf, Page 7:
> Implement the following redirections:
> - < should redirect input.
> - > should redirect output.
> - << should be given a delimiter...
> - >> should redirect output in append mode.

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

| 機能 | 状態 | 必須/ボーナス |
|------|------|--------------|
| 基本コマンド実行 | ✅ | 必須 |
| パイプ | ✅ | 必須 |
| リダイレクション (<, >, >>) | ✅ | 必須 |
| ヒアドキュメント (<<) | ✅ | 必須 |
| 環境変数展開 ($VAR, $?) | ✅ | 必須 |
| シングルクォート | ✅ | 必須 |
| ダブルクォート | ✅ | 必須 |
| 組み込みコマンド (7個) | ✅ | 必須 |
| クォート連結 | ✅ | 必須 |
| 論理演算子 (&&, \|\|) | ✅ | ボーナス |
| ワイルドカード (*) | ❌ | ボーナス |
| fdリダイレクション (2>&1) | ❌ | 対象外 |

**必須機能完成度: 100%** ✅

---

## 42 Subject 要件整理

### 必須 (Mandatory)
- [x] プロンプト表示
- [x] コマンド履歴
- [x] PATH解決・実行
- [x] シグナル処理 (Ctrl+C, Ctrl+D, Ctrl+\)
- [x] クォート処理 (' と ")
- [x] 環境変数展開 ($VAR, $?)
- [x] リダイレクション (<, >, <<, >>)
- [x] パイプ (|)
- [x] 組み込みコマンド (echo, cd, pwd, export, unset, env, exit)

### ボーナス (Bonus)
- [x] && と || (優先度用の括弧なし)
- [ ] ワイルドカード (*)

### 対象外 (Not Required)
- [ ] バックスラッシュ (\)
- [ ] セミコロン (;) - subject で明示的に対象外
- [ ] fdリダイレクション (2>&1)
