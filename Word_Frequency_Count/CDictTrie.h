#pragma once
#include "cdatabase.h"
#include <cstring>
#include <string>
using namespace std;

#define MaxLengthOfWord 256

//typedef  void (*CALLBACK_PFUN)(const char* str,size_t Counte);

class CDictTrie :
	public CDataBase
{
#define LeafNumber 26
	typedef struct node
	{
		struct node *next[LeafNumber];
		size_t counte;
		char m_Data[MaxLengthOfWord];
		node()
		{
			memset(this,0,sizeof(node));
		}
	}*PNode;

	typedef	void(CDictTrie::*CALLBACK_PFUN)(const char* str,size_t Counte);
	typedef	void(CDictTrie::*CALLBACK_ThisNodeHaveDataCall)(PNode A);			//更普适的情况是在这里进行判断,比如是符合某条件的内容
	typedef	void(CDictTrie::*CALLBACK_DataHandBackCall)(PNode A,char* other);	//某数据节点处理完毕返回它的父节点时调用

public:
	CDictTrie(void);
	~CDictTrie(void);


private:


public:
	void	CreateDataBase();

	size_t	Counter(){return 0;};			//统计数据TODO

	/*遍历,对于每个数据都执行传入的函数*/
	void	Explorer(CALLBACK_PFUN);
	void	Explorer_tmp(CALLBACK_ThisNodeHaveDataCall ThisNodeHaveDataCall,CALLBACK_DataHandBackCall DataHandBackCall,char* other);
	void	Temp_Test_NULL(PNode tmp);
	void	Temp_Delete_EveryNode(PNode p,char*);

	void	SaveData(char*);		//增
	void    DeleteData(){};			//删TODO
	void    ChangeData(){};			//改TODO
	size_t	QueryData(char*);		//查

	void	LocalLoadDataBase(){};//加载数据库数据从本地文件TODO
	void	LocalSaveDataBase(){};//存储数据库数据到本地文件TODO
	//更像是分析
	void	Sort();/* 一个想法是Explorer的同时进行排序，用链表,来存放单词和频率*/
	void	AnalysisData();/*分析获得的数据*/
	void	ReadDateFromFile(const char* filePath);
private:

	PNode	CreateNode();
	void	ForInNode(CALLBACK_PFUN,PNode,char[MaxLengthOfWord]);//递归遍历
	void	DelForInNode(CDictTrie::PNode p,CALLBACK_ThisNodeHaveDataCall ThisNodeHaveDataCall,CALLBACK_DataHandBackCall DataHandBackCall,char* other);//删除节点？

	char* strAdd(char*,char);//将一个字符拼接到字符串后面,检查是否超长MaxLengthOfWord;
	char* strSub(char*);//将最后一个字符删掉;

	size_t lenOfstr(const char*);//字符串长度检查

	void GetAllString(const char* str,size_t Counte);

	void QuickSort(size_t left/*这里是=1*/,size_t right/*length-1*/);
	void BubbleSort();

private:
	PNode HeadNode;


	struct strRFC{
		strRFC()
		{
			memset(this,0,sizeof(strRFC));
		}
		char str[256];
		size_t RFC;

	};

	strRFC* pWord;//排序用总的字符串


};
