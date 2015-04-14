#include <iostream>
#include <fstream>
#include <string>
using namespace std;

double UGPA_credit(double score100)
{
	if (score100 <= 100 && score100 >= 85)
		return 4.0;
	else if (score100 >= 75)
		return 3.0;
	else if (score100 >= 60)
		return 2.0;
	else if (score100 >= 0)
		return 0;
	else
	{
		std::cout << "Error!" << endl;
		return -10242048;
	}
}

double UGPA_credit1(double score100)
{
	if (score100 <= 100 && score100 >= 90)
		return 4.0;
	else if (score100 >= 80)
		return 3.0;
	else if (score100 >= 70)
		return 2.0;
	else if (score100 >= 60)
		return 1.0;
	else if (score100 >= 0)
		return 0;
	else
	{
		std::cout << "Error!" << endl;
		return -10242048;
	}
}

double GPA100(double score100)
{
	return score100;
}

double GPA5(double score100)
{
	return score100 / 20;
}


double GPA(string filename, double(*function)(double))
{
	ifstream fromfile(filename.c_str(), ios::in);
	if (!fromfile)
	{
		std::cerr << "Error" << std::endl;
		exit(1);
	}
	string name;
	double credit, score;
	double all_credit = 0;
	double all_score = 0;
	while (fromfile >> name >> credit >> score&&!fromfile.eof())
	{
		all_score += credit*(function(score));
		all_credit += credit;
	}
	fromfile.close();
	return all_score / all_credit;
}


int main()
{
	cout << "######################################" << endl;
	cout << "#   This is GPA calculator           #" << endl;
	cout << "######################################" << endl;
	cout << "�밴�������룺    �ļ��� ��ֹ������" << endl;
	cout << "(���磺)" << endl;
	cout << "my.txt  4" << endl;
	cout << "���У���ֹ��������£�" << endl;
	cout << "1\t" << "100����" << endl;
	cout << "2\t" << "�ϴ�5����" << endl;
	cout << "3\t" << "������׼4����(>=90 4.0; >=80 3.0; >=70 2.0; >=60 1.0 >=0 0.0)" << endl;
	cout << "4\t" << "�����Ľ�4����(>=85 4.0; >=75 3.0; >=60 2.0��>=0 0.0)" << endl;
	cout << "�����룺" << endl;
	string filename;
	cin >> filename;
	double(*func)(double) = GPA100;

	int No;
	cin >> No;
	if (No == 1)
		func = GPA100;
	else if (No == 2)
		func = GPA5;
	else if (No == 3)
		func = UGPA_credit1;
	else if (No == 4)
		func = UGPA_credit;
	else
	{
		cout << "������ֹ������" << endl;
		exit(1);
	}
	cout << "����ǣ�" << endl;
	cout << GPA(filename, func) << endl;
	system("PAUSE");
	return 0;
}