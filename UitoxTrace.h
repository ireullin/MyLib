/***************************************************************************************************************
A class which are able to show stack of methods and position of executing.
It will assist developers tracing the code without gdb.

Author: Ireul Lin
Last update: 2014/01/30
Copyright is owned by UITOX.
***************************************************************************************************************/
#ifndef __UITOXTRACE__
#define __UITOXTRACE__


namespace Uitox
{
class UitoxTrace
{
private:
	UitoxTrace(const UitoxTrace&);
	UitoxTrace& operator= (const UitoxTrace&);

	int			m_showType;
	std::string m_szFile;
	std::string m_szFunction;
	int			m_line; // only for print
	char		m_header[128];

	
	char* fillHeader()
	{
		struct timeb _tmb;    
		ftime(&_tmb);
		struct tm* _ptm = localtime(&_tmb.time);

		memset(&m_header[0], 0, sizeof(m_header));
		sprintf(&m_header[0], "%06ld   %02d:%02d:%02d.%03d",
			pthread_self() % 1000000,
			_ptm->tm_hour, _ptm->tm_min, _ptm->tm_sec, _tmb.millitm
			);

		return &m_header[0];
	}


public:
	UitoxTrace(int showType, const std::string& szFile, const std::string& szFunction)
		:m_showType(showType),m_szFile(szFile),m_szFunction(szFunction),m_line(0)
	{
		if(m_showType!=ON)
			return;
		
		printf("%s   Enter function \033[0;36m%s\033[m\n", 
			fillHeader(),
			m_szFunction.c_str()
			);
	}


	~UitoxTrace()
	{
		if(m_showType!=ON)
			return;
		
		printf("%s   Leave function \033[0;36m%s\033[m\n", 
			fillHeader(),
			m_szFunction.c_str()
			);
	}


	void line(int line)
	{m_line = line;}

	int line()
	{return m_line;}


	void show(const char* format, ...)
	{
		if(m_showType==OFF)
			return;

		char _buff[2048];
		memset(&_buff[0], 0, sizeof(_buff));

		va_list args;
		va_start(args, format);
		vsprintf(&_buff[0], format, args);
		va_end(args);


		printf("%s   \033[0;32;32m%s(%d)\033[m shows \"\033[1;33m%s\033[m\"\n",
			fillHeader(),
			m_szFile.c_str(),
			m_line,
			_buff
			);
	}


	void error(const char* format, ...)
	{
		if(m_showType==OFF)
			return;

		char _buff[2048];
		memset(&_buff[0], 0, sizeof(_buff));

		va_list args;
		va_start(args, format);
		vsprintf(&_buff[0], format, args);
		va_end(args);


		printf("%s   \033[0;32;32m%s(%d)\033[m error \"\033[0;32;31m%s\033[m\"\n",
			fillHeader(),
			m_szFile.c_str(),
			m_line,
			_buff
			);

		assert(false);
	}


	void position(int line)
	{
		if(m_showType==OFF)
			return;

		printf("%s   \033[0;32;32m%s(%d)\033[m is current position\n",
			fillHeader(),
			m_szFile.c_str(),
			line
			);
	}


};
}

#endif
