#ifndef __UITOXEXTENDITEM__
#define __UITOXEXTENDITEM__

namespace Uitox
{

template <typename T>
struct TypeWrapper 
{ 
   typedef T type; 
}; 


class IExtendItem
{
public:
	IExtendItem(){}
	virtual std::string toString()=0;
	virtual int toInt()=0;
	virtual double toDouble()=0;
	virtual long toLong()=0;
	//virtual int toUint()=0; // to do
	//virtual long toUlong()=0;
};


template<typename T>
class ExtendItem : public IExtendItem
{
private:
	friend class TypeWrapper<T>::type;
	
	ExtendItem(const ExtendItem&);
	ExtendItem& operator= (const ExtendItem&);

	std::string m_buff;

	void set(const char* buff, size_t size)
	{
		m_buff.clear();
		m_buff.append(buff, size);
	}

	void set(const std::string& buff)
	{
		m_buff.clear();
		m_buff = buff;
	}



public:
	ExtendItem(){}

	virtual std::string toString()
	{return m_buff;}

	virtual int toInt()
	{return atoi(m_buff.c_str());}

	virtual double toDouble()
	{return atof(m_buff.c_str());}

	virtual long toLong()
	{return atol(m_buff.c_str());}

};


}
#endif
