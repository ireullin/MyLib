#include "UitoxPreheader.h"

#include "MySQL.h"

class dev
{
public:
	char m_buff[10];
	Uitox::ExtendItem<dev> m_item;

	dev()
	{
		memset( &m_buff[0], 0, sizeof(m_buff));
		memcpy( &m_buff[0], "123456789", 9 );
	}
	

	Uitox::IExtendItem& get()
	{
		m_item.set( &m_buff[2]);
		return m_item;
	}


	~dev()
	{}


};


int trycatchmain(int argc, char** argv)
{TRACE_THIS_FUNCTION(ON)
	
	MySQL::Connection _cn;
	_cn.connect("192.168.1.203","remote","letmedie","home");
	// _cn.selectDB("lottery");

	MySQL::Row _row;
	_cn.query("SELECT * FROM  `lottery649`", _row);
	while(_row.next())
	{
		SHOW_VALUES("{%s} {%s}", _row["term"].toString().c_str(),  _row[3].toString().c_str() );
	}

	_cn.close();

	return 0;
}



int main(int argc, char** argv)
{TRACE_THIS_FUNCTION(ON)

	try
	{
		trycatchmain(argc, argv);
	}
	/*catch(MySQL::Exception &e)
	{
		SHOW_VALUES("MySQL::Exception{%s}", e.what());
	}*/
	catch(Uitox::Exception &e)
	{
		SHOW_VALUES("Uitox::Exception{%s}", e.what());
	}
}
