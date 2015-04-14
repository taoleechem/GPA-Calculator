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

double GPArule(double score100 )
{
	double result = -10242048;
	const int MaxRule = 100;
	ifstream fromfile("myrule.txt", ios::in);
	if (!fromfile)
	{
		std::cerr << "Error to open myrule.txt" << std::endl;
		exit(1);
	}
	string biaozhi;
	double score, toscore;
	int count = 1;
	double Score[MaxRule], Toscore[MaxRule]; 
	Score[0] = 100; Toscore[0] = 100;
	while ((fromfile >> biaozhi >> score >> toscore)&&!fromfile.eof())
	{
		Score[count] = score;
		Toscore[count] = toscore;
		count+=1;
	}

	for (int i = 1; i != count+1; i++)
	{
		if (score100 >= Score[i])
		{
			result = Toscore[i];
			break;
		}
	}
	fromfile.close();
	if (result != -10242048)
		return result;
	else
	{
		cout << "Error to use this rule" << endl;
		return -10242048;
	}

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

void output(string filename)
{
	ifstream fromfile(filename.c_str(), ios::in);
	if (!fromfile)
	{
		std::cerr << "Error" << std::endl;
		exit(1);
	}
	string name;
	double credit, score;
	int xuhao = 0;
	cout << "序号" << "\t" << "课程名" << "\t" << "学分" << "\t" << "成绩" << endl;
	while (fromfile >> name >> credit >> score&&!fromfile.eof())
	{
		xuhao++;
		cout <<xuhao<< "\t"<<name << "\t" << credit << "\t" << score << endl;
	}
	fromfile.close();
}



int main()
{
	cout << "######################################" << endl;
	cout << "#   This is GPA calculator           #" << endl;
	cout << "######################################" << endl;

	cout << "请输入文件名：   如 my.txt" << endl;
	string filename;
	cin >> filename;
	output(filename);//show
	cout << endl << endl;
	cout << "######################################" << endl;
	
	cout << "算分规格代码如下：" << endl;
	cout << "1\t" << "100分制" << endl;
	cout << "2\t" << "南大5分制" << endl;
	cout << "3\t" << "美国标准4分制(>=90 4.0; >=80 3.0; >=70 2.0; >=60 1.0 >=0 0.0)" << endl;
	cout << "4\t" << "美国改进4分制(>=85 4.0; >=75 3.0; >=60 2.0：>=0 0.0)" << endl;
	cout << "all\t" << "显示以上全部信息" << endl;
	cout << "######################################" << endl;
	cout << "如果你想要的规则不在上面,请在当前程序所在目录下新建一个 myrule.txt 文件 并且规则代码请输入 myrule" << endl;
	cout << "rule.txt请按此格式书写(即txt内请键入，注意空格,注意顺序)：" << endl;
	cout << ">=  90  5.0" << endl;
	cout << ">=  85  4.5" << endl;
	cout << ">=  80  4.0" << endl;
	cout << ">=  70  3.0" << endl;
	cout << ">=  60  2.0" << endl;
	cout << ">=  0   0.0" << endl;
	cout << "######################################" << endl;
	cout << "请输入算分规则代码：   如  all" << endl;
	double(*func)(double) = GPA100;
	string No;
	cin >> No;
	if (No == "1")
	{
		func = GPA100;
		cout << "GPA(100分制)：" <<  GPA(filename, func) << endl;
	}
	else if (No == "2")
	{
		func = GPA5;
		cout << "GPA（南大标准5分制）：" << GPA(filename, func) << endl;
	}
	else if (No == "3")
	{
		func = UGPA_credit1;
		cout << "GPA（美国标准4.0制）：" << GPA(filename, func) << endl;
	}
	else if (No == "4")
	{
		func = UGPA_credit;
		cout << "GPA（美国改进4.0制）："<< GPA(filename, func) << endl;
	}
	else if (No == "all")
	{
		func = GPA100;
		cout << "GPA(100分制)：" << GPA(filename, func) << endl;
		func = GPA5;
		cout << "GPA（南大标准5分制）：" << GPA(filename, func) << endl;
		func = UGPA_credit1;
		cout << "GPA（美国标准4.0制）：" << GPA(filename, func) << endl;
		func = UGPA_credit;
		cout << "GPA（美国改进4.0制）：" << GPA(filename, func) << endl;
	}
	else if (No == "myrule")
	{
		func = GPArule;
		cout << "GPA（自定义规则）：" << GPA(filename, func) << endl;
	}
	system("PAUSE");
	return 0;
}

