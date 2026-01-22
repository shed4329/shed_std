# shed_std

`shed_std` 是一个shed4329在学校学习数据结构与算法课程时编写的一个C++标准库， 主要聚焦于容器实现，并在容器实现的过程中写了一些其他实用功能。由于知识水平有限，代码有很多问题，希望能够理解。

## 项目结构

- **核心代码**：包含各类数据结构（如 `Ddeque`、`pair` 等）、工具类（如 `Ffunction`、`Ffile_output` 等）的实现。
- **文档**：通过 Doxygen 生成的 HTML 文档，位于 `html` 目录下，可查看类、结构、函数等详细说明。
- **忽略文件**：`.gitignore` 中定义了无需纳入版本控制的文件类型，包括 Python 相关文件（`.py`、`.ipynb`）、可执行文件（`.exe`）、JSON 文件、测试用 C++ 文件（`test*.cpp`）等。

## 主要组件

1. **容器**
   - `Aarray`：定长数组
   - `Ddeque`：双端队列容器
   - `Hhashmap`：哈希表，为可比较的数据结构提供红黑树特化优化
   - `Hheap`:堆，分为大根堆和小根堆，可通过`comparator.h`或自定义比较定义顺序
   - `Llist`：单链表
   - `pair`：用于存储一对值的结构，相关实现可参考 `pair.h`
   - `Qqueue`：队列
   - `Rred_blcak_tree`：红黑树
   - `Sstack`:栈
   - `Sstring`:字符串
   - `Vvector`：动态数组
2. **工具类**
   - `Ffile_output`：文件输出相关类。
   - `Ffunction`：函数对象相关实现，存在 int 隐式转换的待处理问题。

3. **类型工具**
   - 包含 `remove_const`、`remove_reference`、`is_reference`、`enable_if` 等类型转换和判断的工具结构。

4. **其他结构**
   - `Node`：节点结构，可能用于链表等数据结构的实现。
   - `_test_less_equal`：用于测试小于等于关系的结构。

## 待办事项（Todo）

- [ ] Ddeque 等容器不支持右值
- [ ] 完善 pair 相关实现
- [ ] 优化 Ddeque 的头扩容机制
- [ ] 解决 Ffunction 的 int 隐式转换问题
- [ ] 容器大小不再使用int定义

## 文档查看

可通过打开 `html/index.html` 文件查看由 Doxygen 生成的详细文档，了解各类和函数的具体用法、成员等信息。

## 版本

当前版本：0.16