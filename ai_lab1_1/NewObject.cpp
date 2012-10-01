#include "NewObject.h"


CAttribute::CAttribute():aAttrName(""),aAttrValue(""),aAttrStat(0)
{
}

CAttribute::CAttribute(std::string iAttrName, std::string iAttrValue)
	:aAttrName(iAttrName),aAttrValue(iAttrValue),aAttrStat(0)
{
}

CAttribute::CAttribute(std::string iAttrName, std::string iAttrValue, int iAttrStat)
:aAttrName(iAttrName),aAttrValue(iAttrValue),aAttrStat(iAttrStat)
{
}

CAttribute::~CAttribute()
{
}

void CAttribute::setStat(int iAttrStat)
{
	aAttrStat=iAttrStat;
}

int CAttribute::getAttrStat()
{
	return aAttrStat;
}

std::string CAttribute::getAttrName()
{
	return aAttrName;
}

std::string CAttribute::getAttrValue()
{
	return aAttrValue;
}
	
void CAttribute::inputAttribute()
{
	std::cout<<"������� �������� ��������: ";
	//std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::getline(std::cin,aAttrName);
	//std::cin>>aAttrName;
	char lAnswer;
	std::cout<<"��������� �������������� ��������� ��������? y/n";
	std::cin>>lAnswer;
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	if(lAnswer=='y') 
	{
		aAttrStat=4;
		std::cout<<"������� �������� ��������: ";
		std::cin>>aAttrValue;
	}
	else aAttrStat=0;
}

std::string CAttribute::toString()
{
	return aAttrName+": "+aAttrValue;
}

CNewObject::CNewObject(void)
	:aObjName(""),aAttributes(0)
{
}

CNewObject::CNewObject(std::shared_ptr<std::vector<std::shared_ptr<CAttribute>>> iAttributes)
	:aObjName(""), aAttributes(iAttributes)
{
}

CNewObject::CNewObject(std::string iObjName, std::shared_ptr<std::vector<std::shared_ptr<CAttribute>>> iAttributes)
	:aObjName(iObjName), aAttributes(iAttributes)
{

}

CNewObject::~CNewObject(void)
{
}

void CNewObject::setObjName(std::string iObjName)
{
	aObjName=iObjName;
}

void CNewObject::setAttributes(std::shared_ptr<std::vector<std::shared_ptr<CAttribute>>> iAttributes)
{
	aAttributes=iAttributes;
}

std::string CNewObject::getObjName(void)
{
	return aObjName;
}

std::shared_ptr<std::vector<std::shared_ptr<CAttribute>>> CNewObject::getAttributes()
{
	return aAttributes;
}

void CNewObject::inputObject()
{
	std::cout<<"������� �������� �������: ";
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::getline(std::cin,aObjName);
	aAttributes=std::shared_ptr<std::vector<std::shared_ptr<CAttribute>>>(new std::vector<std::shared_ptr<CAttribute>>);
	char lAnswer;
	do
	{
		std::shared_ptr<CAttribute> lAttribute=std::shared_ptr<CAttribute>(new CAttribute()); 
		lAttribute->inputAttribute();
		aAttributes->push_back(lAttribute);
		std::cout<<"������ ��� �������? y/n ";
		std::cin>>lAnswer;
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}while(lAnswer=='y');
}

std::string CNewObject::toString()
{
	std::string lString=aObjName+"\n��������:";
	std::vector<std::shared_ptr<CAttribute>>::iterator it;
	for(it=aAttributes->begin();it<aAttributes->end();it++)
		lString+="\n"+(*it)->toString();
	return lString;
}