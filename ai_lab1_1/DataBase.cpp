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
		std::shared_ptr<std::vector<std::shared_ptr<CAttribute>>> lAttrVec=iObj->getAttributes();
		std::vector<std::shared_ptr<CAttribute>>::iterator it;
		for(it=lAttrVec->begin();it<lAttrVec->end();it++)
			CDataBase::writeAttr(iObj->getObjName(),*it);
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

bool CDataBase::writeAttr(std::string iObjName, std::shared_ptr<CAttribute> iAttr)
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
	CppSQLite3Query lQueryObjName;
	std::ostringstream lQueryStr;
	try
	{
		lQuery=lDB.execQuery(("select id_obj from objects where Name_obj like \""+iObjName+"\"").c_str());
		//поиск атрибута в БД и добавление если он отсутствует
		lQuery = lDB.execQuery(("select * from attribute, objects where (attribute.[name_attr] like \""+iAttr->getAttrName()+"\" "\
			") and (objects.[Name_obj] like \""+iObjName+"\") and (attribute.[id_obj]=objects.[id_obj])").c_str());
		if(lQuery.eof())
		{
			lQueryStr<<"insert into attribute values(null, '"<<iAttr->getAttrName()<<"', "<<lQueryObjName.fieldValue("id_obj")<<\
				", "+iAttr->getAttrStat()<<")";
			lDB.execDML((lQueryStr.str()).c_str());
			lQuery = lDB.execQuery(("select * from attribute, objects where (attribute.[name_attr] like \""+iAttr->getAttrName()+"\" "\
			") and (objects.[Name_obj] like \""+iObjName+"\") and (attribute.[id_obj]=objects.[id_obj])").c_str());

		}
		//статистическая обработка 4 вида
		if(iAttr->getAttrStat()==4)
		{
			
		}
	}
	catch(...)
	{
		std::cout<<"\nОшибка доступа к базе данных";
		return false;
	}
	return true;
}