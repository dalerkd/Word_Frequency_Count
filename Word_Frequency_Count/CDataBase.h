#pragma once

/*���ݿ�ӿ���*/

class CDataBase
{
public:
	CDataBase(void) 
	{
		;
	}
virtual	~CDataBase(void)=0
{
	;
}


public:
	virtual void	CreateDataBase(){};
	virtual size_t	Counter(){return 0;};	//ͳ������
	virtual size_t  Explorer(){return 0;};	//����
	
	virtual void	SaveData(){};		//��
	virtual void    DeleteData(){};		//ɾ
	virtual void    ChangeData(){};		//��
	virtual size_t	QueryData(){return 0;};		//��

	virtual void	LocalLoadDataBase(){};//�������ݿ����ݴӱ����ļ�
	virtual void	LocalSaveDataBase(){};//�洢���ݿ����ݵ������ļ�

	virtual void	Sort(){};//����

private:


};





