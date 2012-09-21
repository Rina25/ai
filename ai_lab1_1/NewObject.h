#pragma once
#include <string>
#include <vector>
#include <iostream>

class CAttribute
{
public:
	CAttribute(void);
	CAttribute(std::string iAttrName, std::string iAttrValue);
	CAttribute(std::string iAttrName, std::string iAttrValue, int iAttrStat);
	~CAttribute(void);
	void setStat(int iAttrStat);
	std::shared_ptr<CAttribute> inputAttribute();
private:
	std::string aAttrName;
	std::string aAttrValue;
	int aAttrStat;
};

class CNewObject
{
public:
	CNewObject(void);
	CNewObject(std::shared_ptr<std::vector<std::shared_ptr<CAttribute>>> iAttributes);
	CNewObject(std::string iObjName, std::shared_ptr<std::vector<std::shared_ptr<CAttribute>>> iAttributes);
	~CNewObject(void);

	void setObjName(std::string iObjName);
	std::string getObjName(void);
	void inputObject(); 
private:
	std::string aObjName;
	std::shared_ptr<std::vector<std::shared_ptr<CAttribute>>> aAttributes;
};

