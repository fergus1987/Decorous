// 「递归复杂度」面试题整理


// 递归次数x由式子 n–5x < 0 → x > n/5 计算，可知时间复杂度为O(n/5) = O(n)
int recursiveFun1(int n)
{
	if (n <= 0)
		return 1;
	else
		return 1 + recursiveFun1(n - 5);
}

// 若递归终止条件为 n <= 0，那么递归次数趋于无限，时间复杂度无法计算；
// 若递归终止条件改为 n <= 1，那么递归次数由式子 n/(5^x) < 1 → x > log(n)/log(5) 计算，
// 可知时间复杂度为O(log(n))
int recursiveFun2(int n)
{
	if (n <= 0)
		return 1;
	else
		return 1 + recursiveFun2(n / 5);
}

// 本题的递归构建了一个完全二叉树，树根值为n，树叶值全0。只有树叶进行了打印操作，
// 其余结点均无操作。树叶个数2^n，所以时间复杂度为O(2^n)
void recursiveFun3(int n, int m, int o)
{
	if (n <= 0)
	{
		printf("%d, %d\n", m, o);
	}
	else
	{
		recursiveFun3(n - 1, m + 1, o);
		recursiveFun3(n - 1, m, o + 1);
	}
}