# 以下はissueに関するメモ

## 対処すべきissue

- global関数に構造体を使わずに1つにすることができるはず

## 11/10のpeer reviewで指摘されたissue

- 送信先のpidに ”1” を指定できるようになっているのは良くないのではないか
- serverからackを受信したclientがなんらかのmessageを出すようにするべきではないか（ex. "ack received"等。また受け取った文字数を表示するとか）
- intの最大値を越えるpidに対するケアは必要ではないか？
- atoiのオーバーフローへの対処は？
- fd1でwarningを出している箇所がある
