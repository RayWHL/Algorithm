#include <iostream>
#include <math.h>

using namespace std;

void PrintRoot(int **root, int n);
void PrintLChild(int **root, int lc, int rc, int r);
void PrintRChild(int **root, int lc, int rc, int r);

int main()
{
	int n;
	cout << "请输入结点数：";
	cin >> n;
	float *p = new float[n + 1];
	float *q = new float[n + 1];
	cout << "请输入各关键字概率：";
	for (int i = 1; i < n+1; ++i)
	{
		cin >> p[i];
	}
	cout << "请输入各伪关键字概率：";
	for (int i = 0; i < n + 1; ++i)
	{
		cin >> q[i];
	}
	//分配e表空间
	float **e = new float*[n + 2];
	for (int i = 0; i < n + 2; ++i)
	{
		e[i] = new float[n + 1];
	}
	//分配w表空间
	float **w = new float*[n + 2];
	for (int i = 0; i < n + 2; ++i)
	{
		w[i] = new float[n + 1];
	}
	//分配root表空间
	int **root = new int*[n + 1];
	for (int i = 0; i < n + 1; ++i)
	{
		root[i] = new int[n + 1];
	}
	//初始化
	for (int i = 1; i <= n + 1; ++i)
	{
		e[i][ i - 1] = q[i - 1];
		w[i][ i - 1] = q[i - 1];
	}
	//自底向上计算root表
	for (int l = 1; l <= n; ++l)
	{
		for (int i = 1; i <= n - l + 1; ++i)
		{
			int j = i + l - 1;
			e[i][j] = INT_MAX;
			w[i][j] = w[i][j - 1] + p[j] + q[j];
			for (int r = i; r <= j; ++r)
			{
				float t = e[i][r - 1] + e[r + 1][j] + w[i][j];
				if (t < e[i][j])
				{
					e[i][j] = t;
					root[i][j] = r;
				}
			}
		}
	}
	//打印e表
	cout << "e:" << endl;
	for (int i = 1; i < n + 2; ++i)
	{
		for (int j = i - 1; j < n + 1; ++j)
		{
			cout << e[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;

	//打印w表
	cout << "w:" << endl;
	for (int i = 1; i < n + 2; ++i)
	{
		for (int j = i - 1; j < n + 1; ++j)
		{
			cout << w[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;

	//打印root表
	cout << "root:" << endl;
	for (int i = 1; i < n + 1; ++i)
	{
		for (int j = i; j < n + 1; ++j)
		{
			cout << root[i][j] << " ";
		}
		cout << endl;
	}
	
	//打印结点关系
	cout << endl;
	PrintRoot(root, n);
	return 0;
}

//打印各结点
void PrintRoot(int **root, int n)
{
	cout << "k" << root[1][n] << "为根" << endl;
	int r = root[1][n];
	int lc = 1;
	int rc = 5;
	PrintLChild(root, lc, r - 1, r);
	PrintRChild(root, r + 1, rc, r);
}
//打印左孩子
void PrintLChild(int **root, int lc, int rc, int r)
{
	if (lc > rc)		//伪关键字
		cout << "d" << lc-1 << "是k" << r << "的左孩子" << endl;
	else
	{
		cout << "k" << root[lc][rc] << "是k" << r << "的左孩子" << endl;
		//递归打印左孩子
		PrintLChild(root, lc, root[lc][rc] - 1, root[lc][rc]);
		//递归打印右孩子
		PrintRChild(root, root[lc][rc] + 1, rc, root[lc][rc]);
	}
}
//打印右孩子
void PrintRChild(int **root, int lc, int rc, int r)
{
	if (lc > rc)		//伪关键字
	{
		cout << "d" << r << "是k" << r << "的右孩子" << endl;
	}
	else
	{
		cout << "k" << root[lc][rc] << "是k" << r << "的右孩子" << endl;
		//递归打印左孩子
		PrintLChild(root, lc, root[lc][rc] - 1, root[lc][rc]);
		//递归打印右孩子
		PrintRChild(root, root[lc][rc] + 1, rc, root[lc][rc]);
	}
}
