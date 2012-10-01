
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
	std::shared_ptr<CNewObject> lObject=std::shared_ptr<CNewObject>(new CNewObject());
	std::string lObjName;
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
		lObject->setAttributes(lAttributes);
		if(lObjName.empty())
		{
			std::cout<<"\nНеизвестный объект. Введите название объекта: ";
			std::cin>>lObjName;
			lObject->setObjName(lObjName);
		}
		else
		{
			std::cout<<"Предъявлен объект "<<lObjName<<" ? Y/N";
			std::cin>>lAnswer;
			if(lAnswer!='y'||lAnswer!='Y')
			{
				std::cout<<"\nВведите название объекта: ";
				std::cin>>lObjName;
			}
			lObject->setObjName(lObjName);
			CDataBase::writeObject(lObject);
		}
		std::cout<<"Продолжить обучение? Y/N";
		std::cin>>lAnswer;
	}while(lAnswer=='y'||lAnswer=='Y');
}

