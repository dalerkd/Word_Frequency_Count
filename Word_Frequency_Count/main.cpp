#define CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include <windows.h>

#include "CDictTrie.h"

#include <iostream>

#include  <fstream>
#include  <string>

//using namespace std;


void PrintM(const char* str,size_t Counte)
{
	printf("0x%x:%s\n",Counte,str);

}

int work(int argc, char** argv)
{
	const char* inputFileNmae = nullptr;
	if (argc == 1)
	{
		inputFileNmae = "data.txt";

	}
	else if (argc == 2)
	{
		inputFileNmae = argv[1];
	}
	else
	{
		printf("参数过多");
		system("pause");
	}
	SetConsoleTitleA(inputFileNmae); // 设置窗口标题


	cout << "Welcome,欢迎使用字典树" << endl;


	CDictTrie* CA = new CDictTrie();

	ifstream fin(inputFileNmae);
	if (!fin.is_open())
	{
		printf("待分析数据文件不存在:%s", inputFileNmae);
		system("pause");
		return -1;
	}

	string str;
	while (fin >> str)
	{
		cout << "Read from file: " << str << endl;

		size_t length = strlen(str.c_str()) + 1;

		char* pC = new char[length]();
		strcpy_s(pC, length, str.c_str());

		for (size_t i = 0;pC[i] != '\0';++i)
		{
			if (isalpha(pC[i]))
			{
				if (isupper(pC[i]))
				{
					pC[i] += 0x20;
				}

			}
			else
			{
				goto here;//非字母元素参与不整个不计算,2016年12月14日星期三 23:38Finished
			}


		}


		CA->SaveData((char*)pC);

	here:;
		delete(pC);
	}
	fin.close();

	int c = CA->QueryData("hi");
	cout << c << endl;
	c = CA->QueryData("hello");
	cout << c << endl;
	c = CA->QueryData("my");
	cout << c << endl;

	CA->Sort();


	fflush(stdin);

	system("pause");
	delete(CA);

	/*cout<<"nihao"<<endl;
	Node *head=createNew();
	char s[10];
	while(cin>>s,strcmp(s,"quit"))
	{
	Insert_str(s,head);
	}*/



	

	return 0;
}


int main(int argc,char** argv)
{
	work(argc, argv);
	_CrtDumpMemoryLeaks();
	_asm int 3;
	return 0;
}


/*
DOIT:
扩展内容:大小写关系，现在只支持小写
遍历数据
统计:排序


*/