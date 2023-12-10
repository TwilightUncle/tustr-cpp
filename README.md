# tustr-cpp

## テストのビルドと実行
下記の通りコマンドを実行します。
以下で出現する`path/to/tustr-cpp`は、本ライブラリを展開したディレクトリのパスです。

```powershell
# 本ライブラリのソースを展開したディレクトリへ移動
cd path/to/tustr-cpp

# ビルド用ディレクトリ作成、移動
# ※mkdir は 初回のみ
mkdir build
cd build

# プロジェクトの作成
# ※初回のみ
cmake ..

# テストソースのビルド
cmake --build .

# テストの実行
ctest -C Debug
```

詳細なテスト結果は`path\to\tustr-cpp\build\Testing\Temporary\LastTest.log`に出力されます。  
テストが失敗した際の詳細を確認する場合は上記ファイルを参照ください。
