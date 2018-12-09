#include <iostream>
#include <math.h>

using namespace std;

void PrintRoot(int **root, int n);
void PrintLChild(int **root, int lc, int rc, int r);
void PrintRChild(int **root, int lc, int rc, int r);

int main()
{
	int n;
	cout << "������������";
	cin >> n;
	float *p = new float[n + 1];
	float *q = new float[n + 1];
	cout << "��������ؼ��ָ��ʣ�";
	for (int i = 1; i < n+1; ++i)
	{
		cin >> p[i];
	}
	cout << "�������α�ؼ��ָ��ʣ�";
	for (int i = 0; i < n + 1; ++i)
	{
		cin >> q[i];
	}
	//����e��ռ�
	float **e = new float*[n + 2];
	for (int i = 0; i < n + 2; ++i)
	{
		e[i] = new float[n + 1];
	}
	//����w��ռ�
	float **w = new float*[n + 2];
	for (int i = 0; i < n + 2; ++i)
	{
		w[i] = new float[n + 1];
	}
	//����root��ռ�
	int **root = new int*[n + 1];
	for (int i = 0; i < n + 1; ++i)
	{
		root[i] = new int[n + 1];
	}
	//��ʼ��
	for (int i = 1; i <= n + 1; ++i)
	{
		e[i][ i - 1] = q[i - 1];
		w[i][ i - 1] = q[i - 1];
	}
	//�Ե����ϼ���root��
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
	//��ӡe��
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

	//��ӡw��
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

	//��ӡroot��
	cout << "root:" << endl;
	for (int i = 1; i < n + 1; ++i)
	{
		for (int j = i; j < n + 1; ++j)
		{
			cout << root[i][j] << " ";
		}
		cout << endl;
	}
	
	//��ӡ����ϵ
	cout << endl;
	PrintRoot(root, n);
	return 0;
}

//��ӡ�����
void PrintRoot(int **root, int n)
{
	cout << "k" << root[1][n] << "Ϊ��" << endl;
	int r = root[1][n];
	int lc = 1;
	int rc = 5;
	PrintLChild(root, lc, r - 1, r);
	PrintRChild(root, r + 1, rc, r);
}
//��ӡ����
void PrintLChild(int **root, int lc, int rc, int r)
{
	if (lc > rc)		//α�ؼ���
		cout << "d" << lc-1 << "��k" << r << "������" << endl;
	else
	{
		cout << "k" << root[lc][rc] << "��k" << r << "������" << endl;
		//�ݹ��ӡ����
		PrintLChild(root, lc, root[lc][rc] - 1, root[lc][rc]);
		//�ݹ��ӡ�Һ���
		PrintRChild(root, root[lc][rc] + 1, rc, root[lc][rc]);
	}
}
//��ӡ�Һ���
void PrintRChild(int **root, int lc, int rc, int r)
{
	if (lc > rc)		//α�ؼ���
	{
		cout << "d" << r << "��k" << r << "���Һ���" << endl;
	}
	else
	{
		cout << "k" << root[lc][rc] << "��k" << r << "���Һ���" << endl;
		//�ݹ��ӡ����
		PrintLChild(root, lc, root[lc][rc] - 1, root[lc][rc]);
		//�ݹ��ӡ�Һ���
		PrintRChild(root, root[lc][rc] + 1, rc, root[lc][rc]);
	}
}
