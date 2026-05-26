# CMakeの最低バージョンを指定（FetchContentを安定して使うために3.14以上が必要）
cmake_minimum_required(VERSION 3.14)

# プロジェクト名と使用言語を指定
project(scg-core CXX)

# C++17を使用する設定
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)  # C++17非対応のコンパイラはエラーにする

# IntelliSense用にコンパイルコマンドを出力する
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# FetchContentモジュールを読み込む（外部ライブラリの自動取得に使用）
include(FetchContent)

# GoogleTestをGitHubから取得する設定
# バージョンを変更する場合はURLのタグ（v1.14.0）を変更する
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)

# GoogleTestをビルド対象に追加する
FetchContent_MakeAvailable(googletest)

# CMakeのテスト機能を有効化（add_testが使えるようになる）
enable_testing()

# Testsディレクトリのビルド設定を読み込む
# ※ Testsフォルダ内にCMakeLists.txtが必要
add_subdirectory(test)