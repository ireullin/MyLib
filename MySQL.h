/***************************************************************************************************************
Wrapped MySQL's API to a class.

Author: Ireul Lin
Last update: 2014/02/17
Copyright is owned by UITOX.
***************************************************************************************************************/
#ifndef __MYSQLH__
#define __MYSQLH__

#include <mysql/mysql.h>

namespace MySQL
{

class Connection;
class Row;

class Exception : public Uitox::Exception
{
private:
	typedef Uitox::Exception super;

public:
	Exception(int error_no, const std::string& errmsg, const std::string& file, int line)
		:super(error_no, errmsg, file, line)
	{}

	Exception(const std::string& errmsg, const std::string& file, int line)
		:super(errmsg, file, line)
	{}
};


class Row
{
private:
	friend class MySQL::Connection;

	Row(const Row&);
	Row& operator= (const Row&);

	MYSQL_ROW 	m_row;
	MYSQL_RES*	m_res;
	Uitox::ExtendItem<MySQL::Row>			m_item;
	Uitox::Dictionary<std::string, int>*	m_dColumns;

	void getColumns()
	{
		m_dColumns = new Uitox::Dictionary<std::string, int>();
		int _size = numColumns();
		MYSQL_FIELD* _fields = mysql_fetch_fields(m_res);

		for(int i = 0; i < _size; i++)
			m_dColumns->add(_fields[i].name, i);
	}

public:
	Row()
		:m_res(NULL),m_dColumns(NULL)
	{
	}

	virtual ~Row()
	{
		mysql_free_result(m_res);
		SAFE_DELETE(m_dColumns);
	}

	unsigned long count()
	{
		return (unsigned long)mysql_num_rows(m_res);
	}

	Uitox::IExtendItem& operator[](int i)
	{
		
		m_item.set(m_row[i]);
		return m_item;
	}

	Uitox::IExtendItem& operator[](const std::string& col)
	{
		if(m_dColumns==NULL)
			getColumns();

		int i = (*m_dColumns)[col];
		m_item.set(m_row[i]);
		return m_item;
	}

	bool next()
	{
		m_row = mysql_fetch_row(m_res);
		if(m_row==NULL)
			return false;
		else
			return true;
	}

	int numColumns()
	{
		return mysql_num_fields(m_res);
	}
};


class Connection
{
private:
	Connection(const Connection&);
	Connection& operator= (const Connection&);

	MYSQL m_cn;

public:
	Connection()
	{
	}


	virtual ~Connection()
	{
	}


	void connect(const char* host, const char* user, const char* passwd, const char* db, unsigned int port=0, unsigned long clientflag=0)
	{
		if(mysql_init(&m_cn)==NULL)
			throw MySQL::Exception(mysql_errno(&m_cn), mysql_error(&m_cn), __FILE__, __LINE__);

		if(mysql_real_connect(&m_cn, host, user, passwd, db, port, 0, clientflag)==NULL)
			throw MySQL::Exception(mysql_errno(&m_cn), mysql_error(&m_cn), __FILE__, __LINE__);			
	}


	bool connected()
	{
		return mysql_ping(&m_cn)==0;
	}
	

	void close()
	{
		mysql_close(&m_cn);
	}


	void selectDB(const char* db)
	{
		int _rc = mysql_select_db(&m_cn, db);
		if(_rc!=0)
			throw MySQL::Exception(mysql_errno(&m_cn), mysql_error(&m_cn), __FILE__, __LINE__);
	}


	void query(const char* queryString, MySQL::Row& row)
	{
		int _rc1 = mysql_query(&m_cn, queryString);
		if(_rc1!=0)
			throw MySQL::Exception(mysql_errno(&m_cn), mysql_error(&m_cn), __FILE__, __LINE__);


		MYSQL_RES* _rc2 = mysql_store_result(&m_cn);
		if(_rc2==0)
			throw MySQL::Exception(mysql_errno(&m_cn), mysql_error(&m_cn), __FILE__, __LINE__);

		row.m_res = _rc2;
	}


	// have not tested.
	int execute(const std::string& queryString)
	{
		int _rc1 = mysql_query(&m_cn, queryString.c_str());
		if(_rc1!=0)
			throw MySQL::Exception(mysql_errno(&m_cn), mysql_error(&m_cn), __FILE__, __LINE__);


		int _rc2 = mysql_affected_rows(&m_cn);
		if(_rc2<0)
			throw MySQL::Exception(mysql_errno(&m_cn), mysql_error(&m_cn), __FILE__, __LINE__);

		return _rc2;
	}

};

} // namespace
#endif
