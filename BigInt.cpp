#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

vector <int> Multi(vector <int> s1, vector <int> s2);
vector <int> Sub(vector <int> s1, vector <int> s2);
vector <int> Add(vector <int> s1, vector <int> s2);
vector <int> GetSolu(vector <int> s1, int m);
vector <int> DeleteZero(vector <int> s1);

int main()
{
	string s1, s2;
	char c;
	cout << "��һ����������";
	cin >> s1;
	cout << "�������";
	cin >> c;
	cout << "�ڶ�����������";
	cin >> s2;
	
	if (s1[0] != '+'&&s1[0] != '-')
	{
		s1.insert(s1.begin(), '+');
	}
	if (s2[0] != '+'&&s2[0] != '-')
	{
		s2.insert(s2.begin(), '+');
	}
	//�����ִ�ת��Ϊ���ֲ������vector��
	int len1 = s1.size();
	int len2 = s2.size();
	vector <int> v1, v2;
	for (int i = 0; i < len1; ++i)
		v1.push_back(s1[i]-'0');
	for (int i = 0; i < len2; ++i)
		v2.push_back(s2[i] - '0');
	vector<int> mout;
	if (c == '*')
		mout = Multi(v1, v2);
	else if (c == '+')
		mout = Add(v1, v2);
	else if (c == '-')
		mout = Sub(v1, v2);
	else
	{
		cout << "INPUT ERROR!" << endl;
		return 0;
	}
	mout = DeleteZero(mout);
	cout << "��������    ";
	if (mout[0] == '+' - '0')	cout << '+';
	else cout << '-';
	for (int i = 1; i <(int) mout.size(); ++i)
		cout << mout[i];
	cout << endl;
	return 0;
}

vector <int> Multi(vector <int> s1, vector <int> s2)
{
	s1 = DeleteZero(s1);
	s2 = DeleteZero(s2);		//	ȥ����Ч0
	int sign1, sign2;
	if (s1[0] == '+' - '0') sign1 = 0;
	else sign1 = 1;
	if (s2[0] == '+' - '0') sign2 = 0;
	else sign2 = 1;
	s1.erase(s1.begin(), s1.begin() + 1);
	s2.erase(s2.begin(), s2.begin() + 1);

	int len1 = s1.size();
	int len2 = s2.size();
	//������һ��Ϊһλʱ��ֱ�ӷ��ؽ��
	vector<int> mout;
	if (len1 == 1)
	{
		mout = GetSolu(s2, s1[0]);

		if ((sign1 == 1 && sign2 == 0) || (sign1 == 0 && sign2 == 1))
			mout[0] = '-' - '0';
		return mout;
	}
	else if (len2 == 1)
	{
		mout = GetSolu(s1, s2[0]);

		if ((sign1 == 1 && sign2 == 0) || (sign1 == 0 && sign2 == 1))
			mout[0] = '-' - '0';
		return mout;
	}
	//������Чλǰ��0ʹ������������λ��һ��
	if (len1 > len2)
	{
		for (int i = 0; i < len1 - len2; ++i)
			s2.insert(s2.begin(), 0);
	}
	if (len1 < len2)
	{
		for (int i = 0; i < len2 - len1; ++i)
			s1.insert(s1.begin(), 0);
	}
	//��s1,s2��Ϊabcd�Ĳ���
	len1 = s1.size();
	len2 = s2.size();
	vector <int> a(len1 - len1 / 2), b(len1 / 2), c(len2 - len2 / 2), d(len2 / 2);
	std::copy(s1.begin(), s1.begin() + len1 - len1 / 2, a.begin());
	std::copy(s1.begin() + len1 - len1 / 2, s1.end(), b.begin());
	std::copy(s2.begin(), s2.begin() + len2 - len2 / 2, c.begin());
	std::copy(s2.begin() + len2 - len2 / 2, s2.end(), d.begin());
	a.insert(a.begin(), '+' - '0');
	b.insert(b.begin(), '+' - '0');
	c.insert(c.begin(), '+' - '0');
	d.insert(d.begin(), '+' - '0');

	vector <int> m1, m2, m12;
	m1 = Multi(a, c);
	m2 = Multi(b, d);

	m12 = m1;
	
	for (int i = 0; i < len1 / 2 + len2 / 2; ++i)
	{
		m12.push_back(0);
	}


	vector<int> temp1, temp2, m3, temp3, temp4;
	temp1 = Sub(a, b);
	temp2 = Sub(d, c);
	temp1 = Multi(temp1, temp2);
	temp1 = Add(temp1, m1);
	temp1 = Add(temp1, m2);

	for (int i = 0 ; i < len1 / 2; ++i)
	{
		temp1.push_back(0);
	}

	temp1 = Add(temp1, m12);
	temp1 = Add(temp1, m2);

	vector<int> m = temp1;
	//����λ�ж�
	if ((sign1 == 1 && sign2 == 0) || (sign1 == 0 && sign2 == 1))
		if (m[0] == '+' - '0' || m[0] == '-' - '0')
			m[0] = '-' - '0';
		else 		m.insert(m.begin(), '-' - '0');

	else
		if (m[0] == '+' - '0' || m[0] == '-' - '0')
			m[0] = '+' - '0';
		else 		m.insert(m.begin(), '+' - '0');
	return m;

}
//����ʵ��
vector <int> Sub(vector <int> s1, vector <int> s2)
{
	s1 = DeleteZero(s1);
	s2 = DeleteZero(s2);	//ȥ����Ч0
	vector<int> s3, s4;
	s3 = s1;
	s4 = s2;
	int sign1, sign2;
	if (s1[0] == '+' - '0') sign1 = 0;
	else sign1 = 1;
	if (s2[0] == '+' - '0') sign2 = 0;
	else sign2 = 1;

	if (sign1 == 0 && sign2 == 1)
	{
		s2[0] = '+' - '0';
		return Add(s1, s2);		//������ ��Ϊ������
	}
	else if (sign1 == 1 && sign2 == 0)
	{
		s2[0] = '-' - '0';
		return Add(s1, s2);		//������ ��Ϊ���Ӹ�
	}

	s1.erase(s1.begin(), s1.begin() + 1);
	s2.erase(s2.begin(), s2.begin() + 1);	//ȥ������λ

	int len1 = s1.size();
	int len2 = s2.size();
	vector<int> mout;
	int sign = 0;
	int cin = 0;
	int cou;
	if (len1 < len2)
	{
		mout = Sub(s4, s3);
		sign = 1;
	}	//��һ��λ��С�ڵڶ��� ��ΪS2-S1
	else
	{
		for (int i = 0; i < len1 - len2; ++i)
		{
			s2.insert(s2.begin(), 0);
		}
		for (int i = 1; i<=len1; ++i)
		{
			cou = s1[len1 - i] - s2[len1 - i] - cin;
			cin = 0;
			if (cou < 0)
			{
				cou = cou + 10;
				cin = 1;
			}
			mout.insert(mout.begin(), cou);

			if (i == len1&&cin == 1)	//	����һ���������ڶ���ʱ����ΪS2-S1
			{
				sign = 1;
				mout=Sub(s4, s3);
			}

		}
	}

	if(sign1==0&&sign2==0&&sign==0)
		mout.insert(mout.begin(), '+'-'0');
	else if(sign1==1&&sign2==1&&sign==0)
		mout.insert(mout.begin(), '-' - '0');
	if (sign == 1 && mout[0] == '+' - '0') mout[0] = '-' - '0';
	else if (sign == 1 && mout[0] == '-' - '0') mout[0] = '+' - '0';
	return mout;

}

//��һλʵ��
vector <int> GetSolu(vector <int> s1, int m)
{
	int len = s1.size();
	int cin = 0;
	int cou = 0;
	vector <int> s;
	if (s1[0] == '+' - '0' || s1[0] == '-' - '0')
	{
		for (int i = 1; i < len; ++i)
		{
			cou = (s1[len - i] * m + cin) % 10;
			cin = (s1[len - i] * m + cin) / 10;
			s.insert(s.begin(), cou);
		}
		if (cin > 0) s.insert(s.begin(), cin);
		s.insert(s.begin(), s1[0]);
	}
	else
	{
		for (int i = 1; i <= len; ++i)
		{
			cou = (s1[len - i] * m + cin) % 10;
			cin = (s1[len - i] * m + cin) / 10;
			s.insert(s.begin(), cou);
		}
		if (cin > 0) s.insert(s.begin(), cin);
		s.insert(s.begin(), '+' - '0');
	}
	return s;
}

//�ӷ�ʵ��
vector <int> Add(vector <int> s1, vector <int> s2)
{
	s1 = DeleteZero(s1);
	s2 = DeleteZero(s2);		//	�����Ч0
	int sign1, sign2;
	if (s1[0] == '+' - '0') sign1 = 0;
	else sign1 = 1;
	if (s2[0] == '+' - '0') sign2 = 0;
	else sign2 = 1;			//	����λ���

	if (sign1 == 0 && sign2 == 1)
	{
		s2[0] = '+' - '0';
		return Sub(s1, s2);
	}
	else if (sign2 == 0 && sign1 == 1)
	{
		s1[0] = '+' - '0';
		return Sub(s2, s1);
	}					//ת��Ϊ����������

	s1.erase(s1.begin(), s1.begin() + 1);
	s2.erase(s2.begin(), s2.begin() + 1);

	int len1 = s1.size();
	int len2 = s2.size();
	int cin = 0;
	int cou = 0;
	vector <int> s;
	//������Чλ�ļӷ�
	for (int i = 1; i <= len1 && i <= len2; ++i)
	{
		cou = (s1[len1 - i] + s2[len2 - i]+cin) % 10;
		cin = (s1[len1 - i] + s2[len2 - i]+cin) / 10;
		s.insert(s.begin(), cou);
	}		
	if (len1 < len2)	//s1��s2�̣���s2��λ
	{
		for (int i = 1; i <= len2 - len1; ++i)
		{
			cou = (s2[len2 - len1 - i] + cin) % 10;
			cin = (s2[len2 - len1 - i] + cin) / 10;
			s.insert(s.begin(), cou);
		}
	}
	else         //s2��s1�̣���s1��λ
	{
		for (int i = 1; i <= len1 - len2; ++i)
		{
			cou = (s1[len1 - len2 - i] + cin) % 10;
			cin = (s1[len1 - len2 - i] + cin) / 10;
			s.insert(s.begin(), cou);
		}
	}
	if(cin>0)
		s.insert(s.begin(), cin);	//��߽�λ

	if(sign1==1&&sign2==1)
		s.insert(s.begin(), '-'-'0');
	else
		s.insert(s.begin(), '+' - '0');

	return s;
}

vector <int> DeleteZero(vector <int> s1)
{
	
	int flag = 0;
	int len = s1.size();
	vector<int> s;
	s.push_back(s1[0]);	//	����λ����
	//�����Чλǰ��0
	for (int i = 1; i < len; ++i)
	{
		if (flag == 1 || s1[i] != 0)
			s.push_back(s1[i]);
		if (s1[i] != 0)
			flag = 1;
	}
	//��ȫ��Ϊ0ʱ��ʣ��һ��0�������
	if (flag == 0)
		s.push_back(0);
	
	return s;
}
