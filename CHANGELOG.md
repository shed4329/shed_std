# 更新日志/Change Log

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