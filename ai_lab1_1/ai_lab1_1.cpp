#include <iostream>
#include "MenuCommand.h"

int main()
{
	setlocale(LC_CTYPE,"rus");
	int number=0;
	std::shared_ptr<CMenuCommand> cmd;
	do{
		system("cls");
		std::cout<<"1 - ������ ��������� ����������;\n2 - ����� �������� � ��������;\n3 - ����� �������������;\n";
		std::cout<<"4 - ����� ������������� � �������������;\n5 - ����� ������ � ����������.\n\n";
		std::cin>>number;
		switch(number)
		{
		case 1: 
			cmd=std::shared_ptr<CWriteCommand>(new CWriteCommand());
			cmd->exec();
			break;
		case 2:
			cmd=std::shared_ptr<CTrainingCommand>(new CTrainingCommand());
			cmd->exec();
			break;
		case 3:
			cmd=std::shared_ptr<CRecognitionCommand>(new CRecognitionCommand());
			cmd->exec();
			break;
		case 4:
			cmd=std::shared_ptr<CRecognitionWriteCommand>(new CRecognitionWriteCommand());
			cmd->exec();
			break;
		}
	}while(number!=5);
	return 0;
}