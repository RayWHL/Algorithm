
#include <iostream>
#include <vector>
#include <algorithm>
#include <limits.h>
#include <math.h>

using namespace std;
 
struct node {
	double x;
	double y;
};

struct answer
{
	node node1;
	node node2;
};

vector<answer> AN;

bool cmpx(node x, node y);	//x��������
bool cmpy(node x, node y);	//y��������
double MinDis(vector <node> , vector <node> ,vector<answer> & N);
int findN(vector<answer> N, answer N1);
int main()
{
	int n;
	cout << "�����������";
	cin >> n;
	cout << "��������㣺" << endl;
	vector<node> Q(n), QX(n), QY(n);
	
	for (int i = 0; i < n; ++i)
	{
		cin >> Q[i].x;
		QX[i].x = QY[i].x = Q[i].x;
		cin >> Q[i].y;
		QX[i].y = QY[i].y = Q[i].y;
	}
	sort(QX.begin(), QX.end(), cmpx);	//��x����
	sort(QY.begin(), QY.end(), cmpy);	//��y����
	double cmin = MinDis(QX, QY,AN);
	cout << "the closest distance : " << cmin << endl;
	cout << "the node:" << endl;
	for (int i = 0; i < AN.size(); ++i)
	{
		cout << "(" << AN[i].node1.x << AN[i].node1.y << ")   " << "(" << AN[i].node2.x << AN[i].node2.y << ")";
		cout << endl;
	}
	return 0;
}

bool cmpx(node a, node b)
{
	return a.x < b.x;
}

bool cmpy(node a, node b)
{
	return a.y < b.y;
}

double MinDis(vector <node> QX, vector <node> QY,vector<answer> & N)
{
	vector<answer> LN, RN;
	double cmin, lmin, rmin;
	if (QX.size() < 3)
	{
		if (QX.size() == 2)
		{
			N.push_back({ QX[0],QX[1] });
			
			return sqrt(pow(QX[0].x - QX[1].x, 2) + pow(QX[0].y - QX[1].y, 2));
		}
		if (QX.size() < 2)
			return INT_MAX;
	}
	int d = QX.size() / 2;
	vector <node> QXL(d), QXR(QX.size() - d);
	std::copy(QX.begin(), QX.begin() + d, QXL.begin());
	std::copy(QX.begin()+d,QX.end() , QXR.begin());		//��x��������

	vector <node> QYL, QYR;
	//��y�������ֲ���QL QR�е��Ӧ  O(n)
	for (int i = 0; i < (int)QY.size(); ++i)
	{
		if (QY[i].x >= QX[d].x)
			QYR.push_back(QY[i]);
		else
			QYL.push_back(QY[i]);
	}

	lmin = MinDis(QXL, QYL,LN);	//����ߵݹ�
	rmin = MinDis(QXR, QYR,RN);	//���ұߵݹ�
	//cmin = min(lmin, rmin);
	if (lmin < rmin)
	{
		cmin = lmin;
		N = LN;
	}
	else if (lmin > rmin)
	{
		cmin = rmin;
		N = RN;
	}
	else
	{
		cmin = lmin;
		N = LN;
		N.insert(N.end(), RN.begin(), RN.end());
	}
	vector <node> QYC;
	//���ڵĵ㣬���Ѿ���y��������	O(n)
	for (int i = 0; i < (int)QY.size(); ++i)
	{
		if (fabs(QY[i].x - QX[d].x) < cmin)
			QYC.push_back(QY[i]);
	}
	//�Դ��ڵ�ÿ�����7��������� O(n)
	for (int i = 0; i < (int) QYC.size(); ++i)
	{
		for (int j = 1; j <= 7; ++j)
		{
			if (i + j < (int)QYC.size())
			{
				double min1 = sqrt(pow(QYC[i].x - QYC[i + j].x, 2) + pow(QYC[i].y - QYC[i + j].y, 2));
				if (min1 < cmin)
				{
					cmin = min1;
					N.clear();
					N.push_back({ QYC[i], QYC[i + j] });
				}
				else if(min1==cmin)
				{
					answer pos = { QYC[i], QYC[i + j] };
					if(findN(N,pos)==0)
						N.push_back({ QYC[i], QYC[i + j] });
				}

			}
		}
	}
	return cmin;
}

int findN(vector<answer> N, answer N1)
{
	for (int i = 0; i < N.size(); ++i)
	{
		if (N[i].node1.x == N1.node1.x &&N[i].node1.y == N1.node1.y &&
			N[i].node2.x == N1.node2.x &&N[i].node2.y == N1.node2.y)
			return 1;
		else if (N[i].node2.x == N1.node2.x &&N[i].node1.y == N1.node1.y &&
			N[i].node1.x == N1.node1.x &&N[i].node2.y == N1.node2.y)
			return 1;
	}
	return 0;
}