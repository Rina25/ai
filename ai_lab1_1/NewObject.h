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
	int getAttrStat();
	std::string getAttrName();
	std::string getAttrValue();
	void inputAttribute();
	std::string toString();
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
	void setAttributes(std::shared_ptr<std::vector<std::shared_ptr<CAttribute>>> iAttributes);
	std::string getObjName(void);
	std::shared_ptr<std::vector<std::shared_ptr<CAttribute>>> getAttributes();
	void inputObject();
	std::string toString();
private:
	std::string aObjName;
	std::shared_ptr<std::vector<std::shared_ptr<CAttribute>>> aAttributes;
};

