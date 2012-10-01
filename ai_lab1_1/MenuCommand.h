#pragma once
#include <iostream>
#include <stdlib.h>
#include "NewObject.h"
#include "DataBase.h"

class CMenuCommand
{
public:
	CMenuCommand(void);
	virtual ~CMenuCommand(void);
	virtual void exec()=0; 
};

class CWriteCommand:public CMenuCommand
{
public:
	CWriteCommand(void){};
	~CWriteCommand(void){};
	void exec(void);
};

class CTrainingCommand:public CMenuCommand
{
public:
	CTrainingCommand(void){};
	~CTrainingCommand(void){};
	void exec(void);
};
