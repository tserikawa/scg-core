# SCG-Core ドキュメント

SCG-Core は Software for Computational Geometry の略で、計算幾何学の学習を目的とした個人用C++ライブラリです。

---

## 環境構築

### 必要な環境

- macOS
- CMake 3.14以上
- C++17対応コンパイラ

### リポジトリ構成

```
SCG-Core/
├── CMakeLists.txt
├── Linear/
│   ├── VectorN.hpp
│   ├── Vector2.hpp
│   ├── Vector3.hpp
│   └── Linear.hpp
└── Tests/
    ├── CMakeLists.txt
    └── Linear/
        ├── VectorNTest.cpp
        ├── Vector2Test.cpp
        └── Vector3Test.cpp
```

### ルートのCMakeLists.txt

```cmake
cmake_minimum_required(VERSION 3.14)
project(scg-core CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
FetchContent_MakeAvailable(googletest)

enable_testing()
add_subdirectory(Tests)
```

### Tests/CMakeLists.txt

```cmake
add_executable(scg-tests
    linear/VectorNTest.cpp
    linear/Vector2Test.cpp
    linear/Vector3Test.cpp
)

target_include_directories(scg-tests PRIVATE
    ${CMAKE_SOURCE_DIR}
)

target_link_libraries(scg-tests
    GTest::gtest_main
)

add_test(NAME SCGTests COMMAND scg-tests)
```

### ビルドと実行

```bash
mkdir build
cd build
cmake ..
cmake --build .
ctest --verbose
```

---

## ベクトルの実装状況

### 命名規則

- 名前空間: `SCG::`
- クラス名: パスカルケース
- メソッド名: パスカルケース
- メンバ変数: `m_`プレフィックス

### VectorN（共通処理）

N次元ベクトルの共通処理を提供するテンプレートクラスです。

| 処理 | 状態 |
|---|---|
| デフォルトコンストラクタ（ゼロ初期化） | ✅ 完了 |
| initializer_listコンストラクタ | ✅ 完了 |
| `operator[]` | ✅ 完了 |
| `operator+`・`operator-` | ✅ 完了 |
| `operator*`（スカラー倍） | ✅ 完了 |
| `operator+=`・`operator-=`・`operator*=` | ✅ 完了 |
| `operator==` | ✅ 完了 |
| `Dot()` | ✅ 完了 |
| `Length()` | ✅ 完了 |
| `Normalize()` | ✅ 完了 |

### Vector2（VectorNを継承）

2次元ベクトル固有の処理を提供するクラスです。

| 処理 | 状態 |
|---|---|
| `X()`・`Y()`アクセサ（読み取り専用） | ✅ 完了 |
| `Cross()`（スカラーを返す） | ✅ 完了 |
| `Rotate()`（ラジアン） | ✅ 完了 |

### Vector3（VectorNを継承）

3次元ベクトル固有の処理を提供するクラスです。

| 処理 | 状態 |
|---|---|
| `X()`・`Y()`・`Z()`アクセサ（読み取り専用） | ✅ 完了 |
| `Cross()`（Vector3を返す） | ✅ 完了 |

### 今後必要になる機能

| 処理 | 対象 | 用途 |
|---|---|---|
| `operator/`（スカラー除算） | VectorN | 一般的な演算 |
| `operator-`（単項マイナス） | VectorN | 符号反転 |
| `Angle()` | Vector2・Vector3 | 2つのベクトルのなす角 |
| `Lerp()` | VectorN | 線形補間 |
| `Distance()` | VectorN | 2点間の距離 |

---

## 今後のタスクリスト

### Linearモジュール

- [ ] MatrixN（共通処理）の実装
- [ ] Matrix2の実装（Vector2の変換行列）
- [ ] Matrix3の実装（2D同次変換行列）
- [ ] Matrix4の実装（3D同次変換行列）

### Geometryモジュール

- [ ] Point2・Point3の実装
- [ ] Segment2の実装（線分）
- [ ] Polygon2の実装（多角形）
- [ ] BoundingBox2の実装（バウンディングボックス）

### Algorithmモジュール

- [ ] 点と線分の距離
- [ ] 線分の交差判定・交点
- [ ] 点が多角形の内側か判定
- [ ] 凸包アルゴリズム

### アプリケーション（SCG-App）

- [ ] リポジトリの作成
- [ ] SCG-Coreをgit submoduleとして取り込む
- [ ] raylib-cppの導入
- [ ] ImGuiの導入
- [ ] 基本的な描画機能の実装