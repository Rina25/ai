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
	
std::shared_ptr<CAttribute> CAttribute::inputAttribute()
{
	std::cout<<"Введите название атрибута: ";
	std::cin>>aAttrName;
	std::cout<<"Введите значение атрибута: ";
	std::cin>>aAttrValue;
	char lAnswer;
	std::cout<<"Выполнять статистическую обработку атрибута? y/n";
	std::cin>>lAnswer;
	if(lAnswer=='y') aAttrStat=4;
	else aAttrStat=0;
	return std::shared_ptr<CAttribute>(this);
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

std::shared_ptr<CNewObject> CNewObject::inputObject()
{
	std::cout<<"Введите название объекта: ";
	std::cin>>aObjName;
	aAttributes=std::shared_ptr<std::vector<std::shared_ptr<CAttribute>>>(new std::vector<std::shared_ptr<CAttribute>>);
	char lAnswer;
	do
	{
		std::shared_ptr<CAttribute> lAttribute=std::shared_ptr<CAttribute>(new CAttribute()); 
		lAttribute->inputAttribute();
		aAttributes->push_back(lAttribute);
		std::cout<<"Ввести еще атрибут? y/n ";
		std::cin>>lAnswer;
	}while(lAnswer=='y');
	return std::shared_ptr<CNewObject>(this);
}