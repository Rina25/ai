#include "DataBase.h"

std::string CDataBase::aDBName="DB.db";

CDataBase::CDataBase(void)
{
}

CDataBase::~CDataBase(void)
{
}

bool CDataBase::writeObject(CNewObject iObj)
{
	CppSQLite3DB lDB;
	lDB.open(aDBName.c_str());

	lDB.close();
	return 1;
}