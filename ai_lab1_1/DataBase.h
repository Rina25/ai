#pragma once
#include <string>
#include "NewObject.h"
#include "CppSQLite3.h"

class CDataBase
{
public:
	CDataBase(void);
	~CDataBase(void);
	static bool writeObject(CNewObject iObj);
private:
	static std::string aDBName;
};

