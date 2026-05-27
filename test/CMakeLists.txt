# テスト用実行ファイルのビルド設定
# -----------------------------------------------
# ✅ テストファイルを追加するときは、add_executableのリストに追加する
#
# 例：新しいテストファイル linear/MatrixTest.cpp を追加する場合
#   add_executable(
#       scg-tests
#       linear/VectorNTest.cpp
#       linear/MatrixTest.cpp   ← 追加
#   )
# -----------------------------------------------
add_executable(
    scg-tests
    linear/Vector2Test.cpp
    linear/Vector3Test.cpp
    linear/MatrixNNTest.cpp
    geometry/Point2Test.cpp
    geometry/Segment2Test.cpp
)

# インクルードパスの設定
# ${CMAKE_SOURCE_DIR} はルートのCMakeLists.txtがあるディレクトリを指す
# ヘッダファイルをルートからのパスでincludeできるようになる
target_include_directories(
    scg-tests
    PRIVATE ${CMAKE_SOURCE_DIR}/include
)

# リンクするライブラリの設定
# GTest::gtest_main はmain関数を自動生成してくれるGoogleTestのターゲット
# -----------------------------------------------
# ✅ 新しい外部ライブラリを追加するときは、このリストに追加する
#
# 例：
#   target_link_libraries(
#       scg-tests
#       GTest::gtest_main
#       SomeOtherLibrary   ← 追加
#   )
# -----------------------------------------------
target_link_libraries(
    scg-tests
    GTest::gtest_main
)

# CTestにテストを登録する
# ctest コマンドや IDEのテストランナーから実行できるようになる
add_test(NAME SCGTests COMMAND scg-tests)