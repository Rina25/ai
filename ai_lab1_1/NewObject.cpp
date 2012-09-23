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
	
void CAttribute::inputAttribute()
{
	std::cout<<"������� �������� ��������: ";
	std::cin>>aAttrName;
	std::cout<<"������� �������� ��������: ";
	std::cin>>aAttrValue;
	char lAnswer;
	std::cout<<"��������� �������������� ��������� ��������? y/n";
	std::cin>>lAnswer;
	if(lAnswer=='y') aAttrStat=4;
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
	std::cin>>aObjName;
	aAttributes=std::shared_ptr<std::vector<std::shared_ptr<CAttribute>>>(new std::vector<std::shared_ptr<CAttribute>>);
	char lAnswer;
	do
	{
		std::shared_ptr<CAttribute> lAttribute=std::shared_ptr<CAttribute>(new CAttribute()); 
		lAttribute->inputAttribute();
		aAttributes->push_back(lAttribute);
		std::cout<<"������ ��� �������? y/n ";
		std::cin>>lAnswer;
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