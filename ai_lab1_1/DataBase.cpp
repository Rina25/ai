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
		std::cout<<"\n������ �������� ���� ������";
		return false;
	}
	CppSQLite3Query lQuery;
	try
	{
		//����� ������� � �� � ���������� ���� �� �����������
		lQuery = lDB.execQuery(("select object.[id_obj] from object where object.[Name_obj] like \""+iObj->getObjName()+"\"").c_str());
		if(lQuery.eof())
			lDB.execDML(("insert into object values(null, '"+iObj->getObjName()+"')").c_str());
		//���������� ��� ���������� ���������

	}
	catch(...)
	{
		std::cout<<"\n������ ������� � ���� ������";
		lDB.close();
		return false;
	}
	//lDB.close();
	return true;
}