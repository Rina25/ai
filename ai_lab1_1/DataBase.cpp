#include "DataBase.h"

std::string CDataBase::aDBName="DB.db";

CDataBase::CDataBase(void)
{
}

CDataBase::~CDataBase(void)
{
}

bool CDataBase::writeObject(std::shared_ptr<CNewObject> iObj)
{
	CppSQLite3DB lDB;
	try
	{
		lDB.open(aDBName.c_str());
	}
	catch(...)
	{
		std::cout<<"\nОшибка открытия базы данных";
		return false;
	}
	CppSQLite3Query lQuery;
	try
	{
		//поиск объекта в БД и добавление если он отсутствует
		lQuery = lDB.execQuery(("select objects.[id_obj] from objects where objects.[Name_obj] like \""+iObj->getObjName()+"\";").c_str());
		if(lQuery.eof())
			lDB.execDML(("insert into objects values(null, '"+iObj->getObjName()+"');").c_str());
		lQuery.finalize();
		//добавление или обновление атрибутов
		std::shared_ptr<std::vector<std::shared_ptr<CAttribute>>> lAttrVec=iObj->getAttributes();
		std::vector<std::shared_ptr<CAttribute>>::iterator it;
		for(it=lAttrVec->begin();it<lAttrVec->end();it++)
			CDataBase::writeAttr(iObj->getObjName(),*it);
	}
	catch(...)
	{
		std::cout<<"\nОшибка доступа к базе данных";
		//lDB.close();
		return false;
	}
	//lDB.close();
	return true;
}

bool CDataBase::writeAttr(std::string iObjName, std::shared_ptr<CAttribute> iAttr)
{
	CppSQLite3DB lDB;
	try
	{
		lDB.open(aDBName.c_str());
	}
	catch(...)
	{
		std::cout<<"\nОшибка открытия базы данных";
		return false;
	}
	CppSQLite3Query lQuery;
	CppSQLite3Query lQueryStat;
	std::ostringstream lQueryStr;
	try
	{
		//поиск атрибута в БД и добавление если он отсутствует
		lQuery = lDB.execQuery(("select * from attribute, objects where (attribute.[name_attr] like \""+iAttr->getAttrName()+"\" "\
			") and (objects.[Name_obj] like \""+iObjName+"\") and (attribute.[id_obj]=objects.[id_obj])").c_str());
		if(lQuery.eof())
		{
			lQuery=lDB.execQuery(("select id_obj from objects where Name_obj like \""+iObjName+"\"").c_str());;
			lQueryStr<<"insert into attribute values(null, '"<<iAttr->getAttrName()<<"', "<<lQuery.fieldValue("id_obj")<<\
				", "<<iAttr->getAttrStat()<<");";
			lDB.execDML((lQueryStr.str()).c_str());
			lQuery = lDB.execQuery(("select * from attribute, objects where (attribute.[name_attr] like \""+iAttr->getAttrName()+"\" "\
			") and (objects.[Name_obj] like \""+iObjName+"\") and (attribute.[id_obj]=objects.[id_obj])").c_str());

		}
		std::ostringstream lIdAttrStream;
		std::string lIdAttrStr;
		lIdAttrStream<<lQuery.fieldValue("id_attr");
		lIdAttrStr=lIdAttrStream.str();
		//не нужна обработка
	/*	if(iAttr->getAttrStat()==0)
		{
			lQueryStat=lDB.execQuery(("select text_value from statistics where statistics.[id_attr]="\
				+lIdAttrStr).c_str());
			if(lQueryStat.eof())
			{
				lDB.execDML(("insert into statistics values("+lIdAttrStr+",' "+iAttr->getAttrValue()+\
					";');").c_str());
			}
			else
			{
				lDB.execDML(("update statistics set text_value=text_value||' "+iAttr->getAttrValue()+\
					";' where statistics.[id_attr]="+lIdAttrStr).c_str());
			}
		}*/
		//статистическая обработка 4 вида
		if(iAttr->getAttrStat()==4)
		{
			lQueryStat=lDB.execQuery(("select min_value, max_value from statistics_4 where statistics_4.[id_attr]="\
				+lIdAttrStr).c_str());
			if(lQueryStat.eof())
			{
				lDB.execDML(("insert into statistics_4 values("+lIdAttrStr+", "+iAttr->getAttrValue()+\
					", "+iAttr->getAttrValue()+");").c_str());
				return true;
			}
			if(atof(lQueryStat.fieldValue("min_value"))>atof((iAttr->getAttrValue()).c_str()))
			{
				lDB.execDML(("update statistics_4 set min_value="+iAttr->getAttrValue()+\
					" where id_attr="+lIdAttrStr).c_str());
			}
			if(atof(lQueryStat.fieldValue("max_value"))<atof((iAttr->getAttrValue()).c_str()))
			{
				lDB.execDML(("update statistics_4 set max_value="+iAttr->getAttrValue()+\
					" where id_attr="+lIdAttrStr).c_str());
			}
		}
	}
	catch(...)
	{
		std::cout<<"\nОшибка доступа к базе данных";
		return false;
	}
	return true;
}

std::string CDataBase::findObject(std::shared_ptr<std::vector<std::shared_ptr<CAttribute>>> iAttributes)
{
	std::shared_ptr<std::map<std::string, int>> lObjMap=std::shared_ptr<std::map<std::string, int>>(new std::map<std::string, int>);
	std::vector<std::shared_ptr<CAttribute>>::iterator it;
	CppSQLite3DB lDB;
	try
	{
		lDB.open(aDBName.c_str());
	}
	catch(...)
	{
		std::cout<<"\nОшибка открытия базы данных";
		return false;
	}
	CppSQLite3Query lQuery;
	try
	{
		for(it=iAttributes->begin();it<iAttributes->end();it++)
		{
			if((*it)->getAttrStat()==0)
				lQuery=lDB.execQuery(("select objects.[Name_obj] from objects,attribute where objects.[id_obj]=attribute.[id_obj] "\
				"and attribute.[name_attr]='"+(*it)->getAttrName()+"';").c_str());
			if((*it)->getAttrStat()==4)
				lQuery=lDB.execQuery(("select objects.[Name_obj] from objects,attribute,statistics_4 where objects.[id_obj]=attribute.[id_obj]"\
				" and attribute.[name_attr]='"+(*it)->getAttrName()+"' and attribute.[id_attr]=statistics_4.[id_attr]"\
				" and statistics_4.[max_value]>="+(*it)->getAttrValue()+" and statistics_4.[min_value]<="+(*it)->getAttrValue()+";").c_str());
			while(!lQuery.eof())
			{
				(*lObjMap)[lQuery.fieldValue("Name_obj")]++;
				lQuery.nextRow();
			}
		}
		lQuery.finalize();
	}
	catch(...)
	{
		std::cout<<"\nОшибка доступа к БД";
		return 0;
	}
	std::string lObjName;
	return lObjName;
}