#include "DataBase.h"

std::string CDataBase::aDBName="DB.db";

CDataBase::CDataBase(void)
{
}

CDataBase::~CDataBase(void)
{
}

bool CDataBase::writeObject(std::shared_ptr<CNewObject> iObj)
{
	CppSQLite3DB lDB;
	try
	{
		lDB.open(aDBName.c_str());
	}
	catch(...)
	{
		std::cout<<"\nОшибка открытия базы данных";
		return false;
	}
	CppSQLite3Query lQuery;
	try
	{
		//поиск объекта в БД и добавление если он отсутствует
		lQuery = lDB.execQuery(("select object.[id_obj] from object where object.[Name_obj] like \""+iObj->getObjName()+"\"").c_str());
		if(lQuery.eof())
			lDB.execDML(("insert into object values(null, '"+iObj->getObjName()+"')").c_str());
		//добавление или обновление атрибутов

	}
	catch(...)
	{
		std::cout<<"\nОшибка доступа к базе данных";
		lDB.close();
		return false;
	}
	//lDB.close();
	return true;
}