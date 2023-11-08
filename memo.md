# 以下はissueに関するメモ

## 対処中のissue

- **8. 文字列の開始・終了条件の管理**: プロトコルの設計を見直す。

## 未対処のissue

**プログラムの堅牢性と効率改善（ブランチを立てた方が良い）**:
- **9. サーバーの安定性改善**: サーバーがクラッシュしないようにエラー処理を改善する。
- **13. 長文のメモリ確保エラー対処**: メモリ割り当ての失敗時の振る舞いを決定する。

**エラーメッセージ改善（軽微な変更）**:
- **3. エラーメッセージの直接渡し**: 関数に`enum`を渡す代わりに`char *`を渡す。
- **12. `call_limit`の明示化**: 変数名やエラーメッセージをより具体的にする。

**コードの可読性と管理改善（軽微な変更またはブランチを立てた方が良い）**:
- **6. `#define INITIAL_PID 0`の導入**: 定数の使用による可読性の向上。
- **7. `CHAR_BIT`のような定数の使用**: マジックナンバーの削減。
- bit_indexもマジックナンバーをなくした方がいいかもしれない。
- if (g_server_info.current_pid == 0) を has_no_current_client()に置き換える
- server sigaction内の動作順について再度確認する

3. エラーmsgを出力する関数に、enumを渡してエラーメッセージの種類を指定するよりも、出力したい文字列を直接エラーmsgを出力する関数に渡した方が処理がわかりやすいのではないか(char *を渡すということ)
6. #difine INITIAL_PID 0 と書く方が、pidが指定されていない状態を0として表現するのにはわかりやすい
7. #difine の CHAR_BIT のようなものを使えばマジックナンバーを減らせるらしい
9. Severが落ちやすすぎる。clientが間違ったtxtを送ってきただけでserverが終了しているが、リセットをかけるだけにして、serverが落ちないようにしたほうがいい
12. call_limitはなんに対するcall limitなのか明示的にした方がよくて、あとメッセージがいるのかも微妙である
13. メモリが足りず長文のmalloc確保ができなくなった時に、どうするのがいいか？serverのプログラムは終了すべきか、延命すべきなのか

## 保留中のissue

- t_msg_state;の構造体について、現在の実装は抱えている変数が多いため、機能単位で分割して複数の構造体にする必要があるか？
```
typedef struct s_msg_state
{
	char						*buf;
	size_t						buf_index;
	size_t						buf_size;
	char						current_char;
	size_t						bits_count;
	pid_t						sender_pid;
	size_t						call_count;
}								t_msg_state;
```
- if (msg_state->sender_pid == 0) return; は, send_ackの中にも入らないっけ？
- global関数に構造体を使わずに1つにすることができるはず
- mallocの失敗時に、これまでのinputをprintして、続きを受け取る実装にもできると思う
- send_ack, notify failure一緒にできるんじゃないの？
