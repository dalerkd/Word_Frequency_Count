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
	typedef	void(CDictTrie::*CALLBACK_ThisNodeHaveDataCall)(PNode A);			//�����ʵ����������������ж�,�����Ƿ���ĳ����������
	typedef	void(CDictTrie::*CALLBACK_DataHandBackCall)(PNode A,char* other);	//ĳ���ݽڵ㴦����Ϸ������ĸ��ڵ�ʱ����

public:
	CDictTrie(void);
	~CDictTrie(void);


private:


public:
	void	CreateDataBase();

	size_t	Counter(){return 0;};			//ͳ������TODO

	/*����,����ÿ�����ݶ�ִ�д���ĺ���*/
	void	Explorer(CALLBACK_PFUN);
	void	Explorer_tmp(CALLBACK_ThisNodeHaveDataCall ThisNodeHaveDataCall,CALLBACK_DataHandBackCall DataHandBackCall,char* other);
	void	Temp_Test_NULL(PNode tmp);
	void	Temp_Delete_EveryNode(PNode p,char*);

	void	SaveData(char*);		//��
	void    DeleteData(){};			//ɾTODO
	void    ChangeData(){};			//��TODO
	size_t	QueryData(char*);		//��

	void	LocalLoadDataBase(){};//�������ݿ����ݴӱ����ļ�TODO
	void	LocalSaveDataBase(){};//�洢���ݿ����ݵ������ļ�TODO
	//�����Ƿ���
	void	Sort();/* һ���뷨��Explorer��ͬʱ��������������,����ŵ��ʺ�Ƶ��*/
	void	AnalysisData();/*������õ�����*/
	void	ReadDateFromFile(const char* filePath);
private:

	PNode	CreateNode();
	void	ForInNode(CALLBACK_PFUN,PNode,char[MaxLengthOfWord]);//�ݹ����
	void	DelForInNode(CDictTrie::PNode p,CALLBACK_ThisNodeHaveDataCall ThisNodeHaveDataCall,CALLBACK_DataHandBackCall DataHandBackCall,char* other);//ɾ���ڵ㣿

	char* strAdd(char*,char);//��һ���ַ�ƴ�ӵ��ַ�������,����Ƿ񳬳�MaxLengthOfWord;
	char* strSub(char*);//�����һ���ַ�ɾ��;

	size_t lenOfstr(const char*);//�ַ������ȼ��

	void GetAllString(const char* str,size_t Counte);

	void QuickSort(size_t left/*������=1*/,size_t right/*length-1*/);
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

	strRFC* pWord;//�������ܵ��ַ���


};
