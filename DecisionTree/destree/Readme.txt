15352015 caogj


实现代码：决策树

内容：递归实现决策树

代码解释：

	分为3个大类：Root、Compute以及Unused

Root类：
用于构造实现决策树的节点结构，内含用于计算和返回的值

Compute：
专门用于计算的类，在其他文件中需要的算法都包含在这个文件内部，包括计算熵的算法，GINI指数算法等

Unused：
用于实现文件的读入，此外没有任何作用。

以上三者都在main函数中调用。