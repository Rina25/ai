
#include "MenuCommand.h"


CMenuCommand::CMenuCommand(void)
{
}


CMenuCommand::~CMenuCommand(void)
{
}


void CWriteCommand::exec(void)
{
	char lAnswer;
	std::shared_ptr<CNewObject> lObject;
	do
	{
		lObject=std::shared_ptr<CNewObject>(new CNewObject());
		system("cls");
		lObject->inputObject();
		CDataBase::writeObject(lObject);

		std::cout<<"\nЕще вводить объект? y/n ";
		std::cin>>lAnswer;
	}while(lAnswer=='y');
}

void CTrainingCommand::exec(void)
{
	char lAnswer;
	std::shared_ptr<std::vector<std::shared_ptr<CAttribute>>> lAttributes = std::shared_ptr<std::vector<std::shared_ptr<CAttribute>>>(new std::vector<std::shared_ptr<CAttribute>>);
	std::string lObjName;
	std::shared_ptr<CNewObject> lObject=std::shared_ptr<CNewObject>(new CNewObject());
	do
	{
		system("cls");
		do
		{
			std::shared_ptr<CAttribute> lAttribute=std::shared_ptr<CAttribute>(new CAttribute()); 
			lAttribute->inputAttribute();
			lAttributes->push_back(lAttribute);
			std::cout<<"Ввести еще атрибут? y/n ";
			std::cin>>lAnswer;
		}while(lAnswer=='y'||lAnswer=='Y');
		lObjName=CDataBase::findObject(lAttributes);
		std::cout<<"Предъявлен объект "<<lObjName<<" ? Y/N";
		std::cin>>lAnswer;
		if(lAnswer=='y'||lAnswer=='Y')

		std::cout<<"Продолжить обучение? Y/N";
		std::cin>>lAnswer;
	}while(lAnswer=='y'||lAnswer=='Y');
}