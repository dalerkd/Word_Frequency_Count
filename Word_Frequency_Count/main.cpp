#define CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include <windows.h>

#include "CDictTrie.h"

#include <iostream>
#include <string>



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
		return 0;
	}
	SetConsoleTitleA(inputFileNmae); // 设置窗口标题
	cout << "Welcome,欢迎使用字典树" << endl;
	CDictTrie* CA = new CDictTrie();

	CA->ReadDateFromFile(inputFileNmae);
	

	int c = CA->QueryData("hi");
	cout << c << endl;
	c = CA->QueryData("hello");
	cout << c << endl;
	c = CA->QueryData("my");
	cout << c << endl;

	CA->Sort();
	CA->AnalysisData();


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

	return 0;
}


/*
DOIT:
扩展内容:大小写关系，现在只支持小写
遍历数据
统计:排序


*/