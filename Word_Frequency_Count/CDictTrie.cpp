#include "CDictTrie.h"


CDictTrie::CDictTrie(void)
{
	pWord = nullptr;
	HeadNode=nullptr;
	CreateDataBase();
}


CDictTrie::~CDictTrie(void)
{


	Explorer_tmp(&CDictTrie::Temp_Test_NULL,&CDictTrie::Temp_Delete_EveryNode,nullptr);
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
	for(int i=0;i<LeafNumber;i++)
	{
		p->next[i]=nullptr;
	}
	p->counte=0;
	return p;


}



void CDictTrie::CreateDataBase()
{
	if (HeadNode==nullptr)
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
	size_t len=strlen(str);
	PNode t,p=HeadNode;
	for(size_t i=0;i<len;i++)
	{
		int c=str[i]-'a';

		if(p->next[c]==nullptr)
		{

			t=CreateNode();
			p->next[c]=t;			
			/*p->counte++;*/

			p=p->next[c];

			if (i==(len-1))
			{
				++(p->counte);
			}
			//cout<<p->counte<<endl;
		}
		else
		{
			p=p->next[c];
			if (i==(len-1))
			{
				++(p->counte);
			}
			//cout<<p->counte<<endl;
		}
	}

}

size_t CDictTrie::QueryData(char* str)
{
	PNode p=HeadNode;
	size_t len=strlen(str);
	int count=0;
	for(size_t i=0;i<len;i++)
	{
		int c=str[i]-'a';
		if(p->next[c]==nullptr)
		{

			//cout<<"�������ַ���"<<endl;
			//throw("�����ڸ��ַ���");
			count=0;
			return 0;
		}
		else
		{
			p=p->next[c];
			count=p->counte;
		}


	}
	return count;
}

void CDictTrie::Explorer(CALLBACK_PFUN pfun)
{

	PNode p = HeadNode;

	char tmpPath[MaxLengthOfWord] = {0};

	ForInNode(pfun,p,tmpPath);

	return;
	/*
	ƴ�ַ���-��ǰ·��
	��ǰcount-���ַ���������;
	*/
}

void CDictTrie::ForInNode(CALLBACK_PFUN pfun,CDictTrie::PNode p,char tmpPath[MaxLengthOfWord])
{
	for (size_t index=0;index<LeafNumber;++index)
	{
		if(p->next[index]!=nullptr)
		{
			strAdd(tmpPath,'a'+index);
			
			if (p->next[index]->counte!=0)/*��������*/
			{
				(this->*pfun)(tmpPath,p->next[index]->counte);
			}
			ForInNode(pfun,p->next[index],tmpPath);

			strSub(tmpPath);/*��Ϊ���ǹ�����һ���ַ���*/
		}

	}

	return;

}


char* CDictTrie::strAdd(char* str,char c)
{
	size_t len = lenOfstr(str);

	if(len >= MaxLengthOfWord-1)
	{
		throw("̫����");
	}

	str[len]=c;
	str[len+1]='\0';

	return str;
}

char* CDictTrie::strSub(char* str)
{
	size_t len = lenOfstr(str);

	if (len==0)
	{
		throw("��ͼ���Ѿ��ǿյ��ַ�������������һ���ַ�");
	}
	
	str[len-1]='\0';

	return str;

}

size_t CDictTrie::lenOfstr(const char* str)
{
	size_t len=0;

	while (str[len]!='\0')
	{
		++len;
	}

	return len;

}

void CDictTrie::Sort()
{
#define Hi 0xff   //�������е�Ч�ʵ�û���Ż��������º������ffff
	 pWord = new strRFC[Hi]();
	 CALLBACK_PFUN p = &CDictTrie::GetAllString;

	 Explorer(p);

	 //QuickSort(1,Hi-1);//��Ҳ������BubbleSort
	 BubbleSort();//��������Ч������Ҳ������

	 //print;

	 size_t count = 0,all=0;
	 for (size_t i=0;i<Hi;++i)
	 {
		 if (pWord[i].RFC!=0)
		 {
			 ++count;
			 all+=pWord[i].RFC;
		 }
		
	 }
	 //��ռ�ȹ�ϵ
	 size_t zong=0;//ǰi�����ֵ�RFC��

	 size_t diao[Hi]={0};//�Űٷֱ�

	 for (int tmp=Hi,i=0;tmp>=1;--tmp,++i)//���������ر�
	 {
		 zong+=pWord[tmp-1].RFC; 
		 diao[Hi-i-1]=zong*100/all;

	 }


	 for (size_t i=0;i<Hi;++i)
	 {
		 printf("ռ��:%2d%% %-10s,RCF:%d\r\n",diao[i],pWord[i].str,pWord[i].RFC);
	 }

	 //delete(pWord);
	 return ;
 
	 
}

void CDictTrie::GetAllString(const char* str,size_t Counte)
{
	char* tmp =(char*)str;
	

	for (size_t i=0;i<Hi;++i)//ÿ�ζ�ȫѭ��Ч�ʲҲ��̶�
	{
		if ((pWord[i].RFC)==0)
		{
			//copy str
			char* pTmp = pWord[i].str;

			while ((*pTmp++=*tmp++)!='\0'){};

			//copy Counte
			pWord[i].RFC = Counte;
			break;
		}

	}




}


void CDictTrie::QuickSort(size_t left,size_t right)
{ 
	strRFC* array = pWord;
	size_t i,j;

	strRFC t,temp;

	if(left>right) 
		return; 

	temp.RFC=array[left].RFC; //temp�д�ľ��ǻ�׼�� 
	strcpy_s(temp.str,array[left].str);

	i=left; 
	j=right; 
	while(i!=j) 
	{ 
		//˳�����Ҫ��Ҫ�ȴ��ұ߿�ʼ�� 
		while(array[j].RFC>=temp.RFC && i<j) 
			j--; 
		//�����ұߵ� 
		while(array[i].RFC<=temp.RFC && i<j) 
			i++; 
		//�����������������е�λ�� 
		if(i<j) 
		{ 
			t.RFC=array[i].RFC;
			strcpy_s(t.str,array[i].str);

			array[i].RFC=array[j].RFC;
			strcpy_s(array[i].str,array[j].str);

			array[j].RFC=t.RFC;
			strcpy_s(array[j].str,t.str);

		} 
	} 
	//���ս���׼����λ 
	array[left].RFC=array[i].RFC;
	strcpy_s(array[left].str,array[i].str);

	array[i].RFC=temp.RFC; 
	strcpy_s(array[i].str,temp.str);

	QuickSort(left,j-1);//����������ߵģ�������һ���ݹ�Ĺ��� 
	QuickSort(i+1,right);//���������ұߵ� ��������һ���ݹ�Ĺ��� 
}

void CDictTrie::BubbleSort()
{
	//����Hi��

	for (size_t i=0;i<Hi;++i)
	{
	 for (size_t j=1+i;j<Hi;++j)
	 {
		 if (pWord[i].RFC>pWord[j].RFC)//swap
		 {
			 pWord[i].RFC^=pWord[j].RFC;
			 pWord[j].RFC^=pWord[i].RFC;
			 pWord[i].RFC^=pWord[j].RFC;

			 char tmpstr[Hi]={0};
			 strcpy_s(tmpstr,pWord[i].str);
			 strcpy_s(pWord[i].str,pWord[j].str);
			 strcpy_s(pWord[j].str,tmpstr);
		 }
	 }

	}
}


void CDictTrie::DelForInNode(CDictTrie::PNode p,CALLBACK_ThisNodeHaveDataCall ThisNodeHaveDataCall,CALLBACK_DataHandBackCall DataHandBackCall, char* other)
{
	for (size_t i=0;i<LeafNumber;++i)
	{
		if(p->next[i]!=nullptr)
		{
			/*
			�����ʵ����������������ж�,�����Ƿ���ĳ����������,ɾ��
			
			*/
			(this->*ThisNodeHaveDataCall)(p->next[i]);

			DelForInNode(p->next[i],ThisNodeHaveDataCall,DataHandBackCall,other);

			(this->*DataHandBackCall)(p->next[i],other);//ĳ���ݽڵ㴦����Ϸ������ĸ��ڵ�ʱ����
			
		}

	}

	return;

}

void CDictTrie::Explorer_tmp(CALLBACK_ThisNodeHaveDataCall ThisNodeHaveDataCall,CALLBACK_DataHandBackCall DataHandBackCall,char* other/*��ѡ�ṩ*/)
{

	PNode p = HeadNode;
	//CALLBACK_PFUN p = &CDictTrie::GetAllString;

	DelForInNode(p,ThisNodeHaveDataCall,DataHandBackCall,other);//�����Ǹ�����������ڲ���

	return;
	/*
	ƴ�ַ���-��ǰ·��
	��ǰcount-���ַ���������;
	*/
}

void CDictTrie::Temp_Test_NULL(PNode tmp)
{
	return;
}

void CDictTrie::Temp_Delete_EveryNode(PNode p,char*)
{
	delete(p);
}
