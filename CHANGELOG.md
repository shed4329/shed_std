# 更新日志/Change Log

## 0.17-beta.5(2026-02-07)

### 新增/Features

- 數學庫`shed_math.h`添加了指數函數`exp`,對數函數`log`，冪函數`pow`
- 添加了隨機數庫`shed_random.h`

## 0.17-beta.4(2026-02-04)

### 優化/Refactored

- 將數學庫`math.h`更名為`shed_math.h`,防止命名衝突

### 修復/Bug Fixes

- `Oostream.h`将double的输出整数部分从int32变为int64，但是仍然不能表示全部的范围

### 新增/Features

- 输出流`Oostream.h`支援了long long的输出
- `shed_types.h`添加了INT64等类型的max和min值定义
- 数学库`shed_math.h`添加了`floor`,`sqrt`等常用函数和常值`MATH_PI`,`MATH_E`

## 0.17-beta.3(2026-01-23)

### 修復/Bug Fixes

- 將Hhashmap的常量迭代器從錯誤的E改爲了pair

### 新增/Features

- 添加了算數錯誤的異常類型`EexceptionArithemetic`
- 為math添加了`float_mod`函數
- 添加了`shed_types.h`頭文件用於定義變量類型

## 0.17-beta.2(2026-01-22)

### 新增/Features

- 使用順序存儲的容器支援使用`data()`函數來獲取底層存儲的原始指針

## 0.17-beta.1(2026-01-22)

### 優化/Refactored

- 為容器的迭代器添加了Tag屬性，使得可以通過`IteratorBase.h`來判定迭代器屬性，使得迭代器表現更加接近標準庫