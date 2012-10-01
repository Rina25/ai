#pragma once
#include <iostream>
#include <algorithm>
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

class CRecognitionCommand:public CMenuCommand
{
public:
	CRecognitionCommand(void){};
	~CRecognitionCommand(void){};
	void exec(void);
};