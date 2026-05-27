# CRTPパターン（Curiously Recurring Template Pattern）

## 概要

CRTPとは基底クラスに**派生クラスの型をテンプレートパラメータとして渡す**設計パターンです。
静的ポリモーフィズムを実現するために使われます。

```cpp
template<typename T>
class Base
{
    // Tは派生クラスの型
};

class Derived : public Base<Derived>
{
    // 自分自身の型を基底クラスに渡す
};
```

---

## 通常の継承との違い

### 通常の継承（動的ポリモーフィズム）

```cpp
class Base
{
public:
    virtual void Method() = 0;
};

class Derived : public Base
{
public:
    void Method() override { ... }
};
```

- `virtual`キーワードが必要
- 実行時に仮想関数テーブルを参照するためオーバーヘッドがある
- 基底クラスのポインタで派生クラスを扱える

### CRTPによる継承（静的ポリモーフィズム）

```cpp
template<typename T>
class Base
{
public:
    void Method()
    {
        static_cast<T*>(this)->MethodImpl();
    }
};

class Derived : public Base<Derived>
{
public:
    void MethodImpl() { ... }
};
```

- `virtual`キーワードが不要
- コンパイル時に解決されるためオーバーヘッドがない
- 基底クラスのポインタで派生クラスを扱えない

---

## SCG-Coreでの使用例

SCG-Coreではベクトルの演算結果の戻り値の型を正しく返すためにCRTPを使用しています。

### CRTPを使わない場合の問題

```cpp
template<int N>
class VectorN
{
public:
    VectorN Normalize() const { ... }
};

class Vector2 : public VectorN<2> { };

Vector2 v = {3.0f, 4.0f};
auto result = v.Normalize(); // VectorN<2>が返る（Vector2ではない）
```

`Normalize()`の戻り値が`VectorN<2>`になってしまい`Vector2`固有のメソッドが使えなくなります。

### CRTPを使った場合

```cpp
template<typename T, int N>
class VectorBase
{
public:
    T Normalize() const
    {
        float len = Length();
        if (len <= 1e-6f)
        {
            throw std::domain_error("...");
        }
        T result;
        for (size_t i = 0; i < N; i++)
        {
            result[i] = m_values[i] / len;
        }
        return result;
    }
};

class Vector2 : public VectorBase<Vector2, 2> { };

Vector2 v = {3.0f, 4.0f};
auto result = v.Normalize(); // Vector2が返る
```

戻り値が正しく`Vector2`になります。

---

## VectorBaseの設計

### クラス定義

```cpp
template<typename T, int N>
class VectorBase
{
protected:
    float m_values[N];

public:
    // 共通処理（operator+, -, *, /, Dot, Length, Normalizeなど）
    T operator+(const VectorBase<T, N>& other) const
    {
        T result;
        for (size_t i = 0; i < N; i++)
        {
            result[i] = m_values[i] + other[i];
        }
        return result;
    }
};
```

### 派生クラスの定義

```cpp
class Vector2 : public VectorBase<Vector2, 2>
{
public:
    float X() const { return m_values[0]; }
    float Y() const { return m_values[1]; }
    float Cross(const Vector2& other) const { ... }
    Vector2 Rotate(float angle) const { ... }
};

class Vector3 : public VectorBase<Vector3, 3>
{
public:
    float X() const { return m_values[0]; }
    float Y() const { return m_values[1]; }
    float Z() const { return m_values[2]; }
    Vector3 Cross(const Vector3& other) const { ... }
};
```

---

## 基底クラスの直接インスタンス化を防ぐ方法

`VectorBase`は直接インスタンス化することを想定していないため、コンストラクタを`protected`にすることで防げます。

```cpp
template<typename T, int N>
class VectorBase
{
protected:
    VectorBase() { ... }
    VectorBase(std::initializer_list<float> init) { ... }
};
```

---

## N次元ベクトルへの対応

`Vector2`・`Vector3`固有の処理が不要な場合は`VectorN`を定義します。

```cpp
template<int N>
class VectorN : public VectorBase<VectorN<N>, N>
{
    // 固有処理なし
};
```

---

## CRTPの注意点

### 派生クラスのオブジェクト生成

基底クラス内で`T`型のオブジェクトを生成する場合は`T result;`を使います。
`static_cast<T>(*this)`は基底クラスから派生クラスへの変換ができないため使えません。

```cpp
// 正しい
T result;
for (size_t i = 0; i < N; i++)
{
    result[i] = m_values[i] / value;
}
return result;

// 誤り
T result = static_cast<T>(*this); // コンパイルエラー
```

### テストはVectorBaseを直接テストしない

`VectorBase`は基底クラスなので直接テストは不要です。`Vector2`・`Vector3`のテストを通して間接的にテストします。

| テストファイル | テスト対象 |
|---|---|
| `Vector2Test.cpp` | `VectorBase`の共通処理＋`Vector2`固有の処理 |
| `Vector3Test.cpp` | `VectorBase`の共通処理＋`Vector3`固有の処理 |

---

## まとめ

| 項目 | 内容 |
|---|---|
| 目的 | 基底クラスのメソッドの戻り値を派生クラスの型にする |
| 仕組み | 派生クラスの型をテンプレートパラメータとして基底クラスに渡す |
| メリット | 実装が一箇所で済む・戻り値の型が正しくなる |
| デメリット | テンプレートが複雑になる・理解しにくい |
| 用途 | 数学ライブラリ・ポリシーベース設計など |