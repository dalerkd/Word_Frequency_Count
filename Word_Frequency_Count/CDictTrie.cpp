#include "CDictTrie.h"


CDictTrie::CDictTrie(void)
{
	pWord = nullptr;
	HeadNode = nullptr;
	CreateDataBase();
}


CDictTrie::~CDictTrie(void)
{


	Explorer_tmp(&CDictTrie::Temp_Test_NULL, &CDictTrie::Temp_Delete_EveryNode, nullptr);
	delete pWord;
	pWord = nullptr;
	delete HeadNode;
	HeadNode = nullptr;
	/*
	*/
}







CDictTrie::PNode CDictTrie::CreateNode()
{
	PNode p = new node;
	for (int i = 0;i < LeafNumber;i++)
	{
		p->next[i] = nullptr;
	}
	p->counte = 0;
	return p;


}



void CDictTrie::CreateDataBase()
{
	if (HeadNode == nullptr)
	{
		HeadNode = CreateNode();
	}
	else
	{
		throw("Have a DataBase,don't create New");
	}

}


void CDictTrie::SaveData(char* str)
{
	size_t len = strlen(str);
	PNode t, p = HeadNode;
	for (size_t i = 0;i < len;i++)
	{
		int c = str[i] - 'a';

		if (p->next[c] == nullptr)
		{

			t = CreateNode();
			p->next[c] = t;
			/*p->counte++;*/

			p = p->next[c];

			if (i == (len - 1))
			{
				++(p->counte);
			}
			//cout<<p->counte<<endl;
		}
		else
		{
			p = p->next[c];
			if (i == (len - 1))
			{
				++(p->counte);
			}
			//cout<<p->counte<<endl;
		}
	}

}

size_t CDictTrie::QueryData(char* str)
{
	PNode p = HeadNode;
	size_t len = strlen(str);
	int count = 0;
	for (size_t i = 0;i < len;i++)
	{
		int c = str[i] - 'a';
		if (p->next[c] == nullptr)
		{

			//cout<<"不存在字符串"<<endl;
			//throw("不存在该字符串");
			count = 0;
			return 0;
		}
		else
		{
			p = p->next[c];
			count = p->counte;
		}


	}
	return count;
}

void CDictTrie::Explorer(CALLBACK_PFUN pfun)
{

	PNode p = HeadNode;

	char tmpPath[MaxLengthOfWord] = { 0 };

	ForInNode(pfun, p, tmpPath);

	return;
	/*
	拼字符串-当前路径
	当前count-该字符串的数量;
	*/
}

void CDictTrie::ForInNode(CALLBACK_PFUN pfun, CDictTrie::PNode p, char tmpPath[MaxLengthOfWord])
{
	for (size_t index = 0;index < LeafNumber;++index)
	{
		if (p->next[index] != nullptr)
		{
			strAdd(tmpPath, 'a' + index);

			if (p->next[index]->counte != 0)/*存在数据*/
			{
				(this->*pfun)(tmpPath, p->next[index]->counte);
			}
			ForInNode(pfun, p->next[index], tmpPath);

			strSub(tmpPath);/*因为我们共有了一个字符串*/
		}

	}

	return;

}


char* CDictTrie::strAdd(char* str, char c)
{
	size_t len = lenOfstr(str);

	if (len >= MaxLengthOfWord - 1)
	{
		throw("太长了");
	}

	str[len] = c;
	str[len + 1] = '\0';

	return str;
}

char* CDictTrie::strSub(char* str)
{
	size_t len = lenOfstr(str);

	if (len == 0)
	{
		throw("试图向已经是空的字符串申请剃除最后一个字符");
	}

	str[len - 1] = '\0';

	return str;

}

size_t CDictTrie::lenOfstr(const char* str)
{
	size_t len = 0;

	while (str[len] != '\0')
	{
		++len;
	}

	return len;

}

void CDictTrie::Sort()
{
#define Hi 0xff   //本函数中低效率的没有优化的排序导致后果很慢ffff
	pWord = new strRFC[Hi]();
	CALLBACK_PFUN p = &CDictTrie::GetAllString;

	Explorer(p);

	//QuickSort(1,Hi-1);//你也可以用BubbleSort
	BubbleSort();//糟糕的是无效的数据也被排序

}

void CDictTrie::AnalysisData()
{
	size_t count = 0, all/*总的单词量*/ = 0;
	for (size_t i = 0;i < Hi;++i)
	{
		if (pWord[i].RFC != 0)
		{
			++count;
			all += pWord[i].RFC;
		}

	}
	//总占比关系
	size_t zong = 0;//前i个数字的RFC和

	size_t diao[Hi] = { 0 };//放百分比

	for (int tmp = Hi, i = 0;tmp >= 1;--tmp, ++i)//倒序所以特别
	{
		zong += pWord[tmp - 1].RFC;
		diao[Hi - i - 1] = zong * 100 / all;

	}
	bool bHaveKnownList = true;
	CDictTrie* CKnown = new CDictTrie();//已经掌握的单词
	try {
		CKnown->ReadDateFromFile("Exclude.txt");
	}
	catch (char* str)
	{
		bHaveKnownList = false;
		printf("warming:%s\r\n",str);
	}


	size_t var_knowWordNumber = 0;
	size_t var_noKnowNumber = 0;

	/*
	1. 先找到所有的已知词汇的RCF和。

	
	*/
	size_t all_know_RFC = 0;
	for (size_t i = 0;i < Hi;++i)
	{
		if (!bHaveKnownList)
		{
			break;
		}
		if (CKnown->QueryData(pWord[i].str))
		{
			var_knowWordNumber += 1;
			all_know_RFC+=pWord[i].RFC;
		}

	}
	all_know_RFC = all_know_RFC * 100 / all;//得到频率
	

	for (size_t i = 0,number=0;i < Hi;++i)
	{


		if (bHaveKnownList&&CKnown->QueryData(pWord[i].str))
		{
			//var_knowWordNumber+=1;
			//printf("%3d占比:%2d%% %-10s,RCF:%d  √		\r\n",Hi-i, diao[i], pWord[i].str, pWord[i].RFC);
		}
		else
		{
			number += 1;
			
			if (pWord[i].RFC)
			{
				var_noKnowNumber += 1;
				
				printf("%3d %-10s,RCF:%d			\r\n", Hi - number - var_knowWordNumber + 1, pWord[i].str, pWord[i].RFC);

			}

		}
		
	}
	delete(CKnown);
	printf("已经掌握的单词在频率上占比:%d%%\r\n", all_know_RFC);
	printf("已经了解的单词量:%d\r\n",var_knowWordNumber);
	printf("还不了解的单词量:%d\r\n", var_noKnowNumber);
	return;
}

#include <iostream>
#include  <fstream>
void CDictTrie::ReadDateFromFile(const char* inputFileName)
{
	if (nullptr==inputFileName)
	{
		throw("空指针");
	}
	ifstream fin(inputFileName);
	if (!fin.is_open())
	{
		printf("待分析数据文件不存在:%s", inputFileName);
		throw("待分析数据文件不存在");
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
				goto END_FILE_DECIDE;//非字母元素参与不整个不计算,2016年12月14日星期三 23:38Finished
			}
		}
		SaveData((char*)pC);

	END_FILE_DECIDE:

		delete(pC);
		pC = nullptr;
	}

	fin.close();
}
/*
将字符串复制进已经申请的位置，大小为Hi。超过Hi的不再计算
缺陷是超过256就不再记录了。
这里更适合用栈来处理。

*/
void CDictTrie::GetAllString(const char* str, size_t Counte)
{
	char* tmp = (char*)str;


	for (size_t i = 0;i < Hi;++i)//每次都全循环效率惨不忍睹
	{
		if ((pWord[i].RFC) == 0)
		{
			//copy str
			char* pTmp = pWord[i].str;

			while ((*pTmp++ = *tmp++) != '\0') {};

			//copy Counte
			pWord[i].RFC = Counte;
			break;
		}

	}




}


void CDictTrie::QuickSort(size_t left, size_t right)
{
	strRFC* array = pWord;
	size_t i, j;

	strRFC t, temp;

	if (left > right)
		return;

	temp.RFC = array[left].RFC; //temp中存的就是基准数 
	strcpy_s(temp.str, array[left].str);

	i = left;
	j = right;
	while (i != j)
	{
		//顺序很重要，要先从右边开始找 
		while (array[j].RFC >= temp.RFC && i < j)
			j--;
		//再找右边的 
		while (array[i].RFC <= temp.RFC && i < j)
			i++;
		//交换两个数在数组中的位置 
		if (i < j)
		{
			t.RFC = array[i].RFC;
			strcpy_s(t.str, array[i].str);

			array[i].RFC = array[j].RFC;
			strcpy_s(array[i].str, array[j].str);

			array[j].RFC = t.RFC;
			strcpy_s(array[j].str, t.str);

		}
	}
	//最终将基准数归位 
	array[left].RFC = array[i].RFC;
	strcpy_s(array[left].str, array[i].str);

	array[i].RFC = temp.RFC;
	strcpy_s(array[i].str, temp.str);

	QuickSort(left, j - 1);//继续处理左边的，这里是一个递归的过程 
	QuickSort(i + 1, right);//继续处理右边的 ，这里是一个递归的过程 
}

void CDictTrie::BubbleSort()
{
	//排序Hi个

	for (size_t i = 0;i < Hi;++i)
	{
		for (size_t j = 1 + i;j < Hi;++j)
		{
			if (pWord[i].RFC > pWord[j].RFC)//swap
			{
				pWord[i].RFC ^= pWord[j].RFC;
				pWord[j].RFC ^= pWord[i].RFC;
				pWord[i].RFC ^= pWord[j].RFC;

				char tmpstr[Hi] = { 0 };
				strcpy_s(tmpstr, pWord[i].str);
				strcpy_s(pWord[i].str, pWord[j].str);
				strcpy_s(pWord[j].str, tmpstr);
			}
		}

	}
}


void CDictTrie::DelForInNode(CDictTrie::PNode p, CALLBACK_ThisNodeHaveDataCall ThisNodeHaveDataCall, CALLBACK_DataHandBackCall DataHandBackCall, char* other)
{
	for (size_t i = 0;i < LeafNumber;++i)
	{
		if (p->next[i] != nullptr)
		{
			/*
			更普适的情况是在这里进行判断,比如是符合某条件的内容,删除

			*/
			(this->*ThisNodeHaveDataCall)(p->next[i]);

			DelForInNode(p->next[i], ThisNodeHaveDataCall, DataHandBackCall, other);

			(this->*DataHandBackCall)(p->next[i], other);//某数据节点处理完毕返回它的父节点时调用

		}

	}

	return;

}

void CDictTrie::Explorer_tmp(CALLBACK_ThisNodeHaveDataCall ThisNodeHaveDataCall, CALLBACK_DataHandBackCall DataHandBackCall, char* other/*可选提供*/)
{

	PNode p = HeadNode;
	//CALLBACK_PFUN p = &CDictTrie::GetAllString;

	DelForInNode(p, ThisNodeHaveDataCall, DataHandBackCall, other);//这里是个错误调用用于测试

	return;
	/*
	拼字符串-当前路径
	当前count-该字符串的数量;
	*/
}

void CDictTrie::Temp_Test_NULL(PNode tmp)
{
	return;
}

void CDictTrie::Temp_Delete_EveryNode(PNode p, char*)
{
	delete(p);
}
