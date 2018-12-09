#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
vector<int> FLOYD_WARSHALL(vector<int> w,vector<int> &V);
void PRINT(vector<int> V,int n);

int main()
{
	vector <int> w;
	int n;
	cout << "����n:";
	cin >> n;
	cout << "����" << endl;
	vector<int> V((n+1)*n*n);
	int temp;
	//�������� 100���������
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			cin >> temp;
			w.push_back(temp);
			if(i==j)
				V[i*n + j] = -1;
			else if (temp < 100)
				V[i*n + j] = i + 1;
			else
				V[i*n + j] = -1;
		}
	}
	
	vector<int> out = FLOYD_WARSHALL(w,V);
	cout << endl;
	//��ӡ���·��
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			cout << out[i*n + j] << " ";
		}
		cout << endl;
	}
	cout << endl;
	
	//��ӡǰ������
	int i = n;
	for (int j = 0; j < n; ++j)
	{
		for (int k = 0; k < n; ++k)
		{
			cout << V[i*n*n + j*n + k] << " ";
		}
		cout << endl;
	}
	cout << endl;
	//��ӡ·��
	PRINT(V, n);
}

vector<int> FLOYD_WARSHALL(vector<int> w,vector<int> &V)
{
	vector <int> D0;
	D0 = w;
	int n = sqrt(w.size());

	vector<int> Dk, Dk_1;
	Dk = D0;
	for (int k = 1; k <= n; ++k)
	{
		Dk_1 = Dk;
		for (int i = 0; i < n; ++i)
		{
			for (int j = 0; j < n; ++j)
			{
				//����һ�������
				if (Dk_1[i*n + k - 1] == 100 || Dk_1[(k - 1)*n + j] == 100)
				{
					Dk[i*n + j] = Dk_1[i*n + j];
					V[k*n*n + i*n + j] = V[(k - 1)*n*n + i*n + j];
				}
				//d(i,j)<d(i,k)+d(k,j)ʱ
				else if (Dk_1[i*n + j] <= Dk_1[i*n + k-1] + Dk_1[(k-1)*n + j])
				{
					Dk[i*n + j] = Dk_1[i*n + j];
					V[k*n*n + i*n + j] = V[(k - 1)*n*n + i*n + j];
				}
				//d(i,j)>=d(i,k)+d(k,j)ʱ
				else
				{
					Dk[i*n + j] = Dk_1[i*n + k-1] + Dk_1[(k-1)*n + j];
					V[k*n*n + i*n + j] = V[(k - 1)*n*n + (k-1)*n + j];

				}
			}
		}
	}
	return Dk;
}
//��ӡ·��
void PRINT(vector<int> V,int n)
{
	int node1, node2;
	cout << "Դ�ڵ㣺";
	cin >> node1;
	cout << "Ŀ�Ľ�㣺";
	cin >> node2;
	int k = n;
	cout << node2 << " ";
	while (node1 != node2)
	{
		if (V[k*n*n + (node1 - 1)*n + node2 - 1] == -1)
		{
			cout << "������·��" << endl;
			break;
		}
		else
		{
			node2 = V[k*n*n + (node1 - 1)*n + node2 - 1];
			cout << node2 << " ";
		}
	}
	cout << endl;
}