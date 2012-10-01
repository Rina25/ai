#pragma once
#include <string>
#include <map>
#include "NewObject.h"
#include "CppSQLite3.h"
#include <sstream>

class CDataBase
{
public:
	CDataBase(void);
	~CDataBase(void);
	static bool writeObject(std::shared_ptr<CNewObject> iObj);
	static bool writeAttr(std::string iObjName, std::shared_ptr<CAttribute>);
	static std::string findObject(std::shared_ptr<std::vector<std::shared_ptr<CAttribute>>> iAttributes);
private:
	static std::string aDBName;
};

