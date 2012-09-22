#pragma once
#include <string>
#include "NewObject.h"
#include "CppSQLite3.h"

class CDataBase
{
public:
	CDataBase(void);
	~CDataBase(void);
	static bool writeObject(std::shared_ptr<CNewObject> iObj);
	static bool writeAttr(std::string iObjName, std::shared_ptr<CAttribute>);
private:
	static std::string aDBName;
};

