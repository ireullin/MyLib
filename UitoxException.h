/***************************************************************************************************************
An exception, which derived from std::exception, contains extra infomation as number of line, file name and so on...

Author: Ireul Lin
Last update: 2014/01/31
Copyright is owned by UITOX.
***************************************************************************************************************/
#ifndef __UITOXEXCEPTION__
#define __UITOXEXCEPTION__



namespace Uitox{
class Exception : public std::exception
{
private:
	int			m_error_no;
	std::string m_errmsg;
	std::string m_file;
	int			m_line;
	

public:
	Exception(int error_no, const std::string& errmsg, const std::string& file, int line)
		:m_error_no(error_no),m_errmsg(errmsg),m_file(file),m_line(line)
	{}

	Exception(const std::string& errmsg, const std::string& file, int line)
		:m_error_no(-1),m_errmsg(errmsg),m_file(file),m_line(line)
	{}

	int no()
	{
		return m_error_no;
	}

	int line()
	{return m_line;}

	const std::string& message()
	{return m_errmsg;}

	const std::string& file()
	{return m_file;}

	virtual const char* what() const throw()
	{
		std::stringstream _ss;
		_ss << m_file << "(" << m_line <<  ") msg:(" << m_error_no << ")" << m_errmsg;
		return _ss.str().c_str();
	}
	
	virtual ~Exception()throw(){}
};
}//namespace

#endif
