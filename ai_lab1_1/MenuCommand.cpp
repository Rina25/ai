
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

		std::cout<<"\nֵשו גגמהטעü מבתוךע? y/n ";
		std::cin>>lAnswer;
	}while(lAnswer=='y');
}

