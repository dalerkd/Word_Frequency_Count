#pragma once

/*数据库接口类*/

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
	virtual size_t	Counter(){return 0;};	//统计数据
	virtual size_t  Explorer(){return 0;};	//遍历
	
	virtual void	SaveData(){};		//增
	virtual void    DeleteData(){};		//删
	virtual void    ChangeData(){};		//改
	virtual size_t	QueryData(){return 0;};		//查

	virtual void	LocalLoadDataBase(){};//加载数据库数据从本地文件
	virtual void	LocalSaveDataBase(){};//存储数据库数据到本地文件

	virtual void	Sort(){};//排序

private:


};





