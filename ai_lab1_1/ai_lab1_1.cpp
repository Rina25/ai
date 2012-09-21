#include <iostream>
#include "MenuCommand.h"

int main()
{
	setlocale(LC_CTYPE,"rus");
	std::cout<<"1 - «апись априорной информации;\n2 - режим обучени€ с учителем;\n3 - режим распознавани€;\n";
	std::cout<<"4 - режим распознавани€ с самообучением;\n5 - конец работы с программой.\n\n";
	int number=0;
	std::shared_ptr<CMenuCommand> cmd;
	do{
		std::cin>>number;
		switch(number)
		{
		case 1: 
			cmd=std::shared_ptr<CWriteCommand>(new CWriteCommand());
			cmd->exec();
			break;
		case 2:
			break;
		case 3:
			break;
		case 4:
			break;
		}
	}while(number!=5);
}