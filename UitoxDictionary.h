#ifndef __UITOXDICTIONARY__
#define __UITOXDICTIONARY__

namespace Uitox{

/**************************************************************************************************
	Example:
	Dictionary2<std::string,std::string> _d;
	for(_d.begin(); !_d.end(); ++_d)
	{
		printf("key=%s value=%s", _d.key().c_str(), _d.value().c_str());	
		_d.Remove();
	}
***************************************************************************************************/

template <typename K, typename V>
class Dictionary{
private:
	typedef std::map<K,V>	MapType;
	typedef std::pair<K,V>	PairType;

	Dictionary(const Dictionary&);
	Dictionary& operator=(const Dictionary&);

	MapType						m_map;
	typename MapType::iterator	m_it;
	bool						m_reset;

public:
	Dictionary()
		:m_reset(false)
	{}


	virtual ~Dictionary()
	{}


	/// 新增一元素,不檢查是否存在
	/// 新增已有元素,會覆蓋舊有元素
	void add(const K& key, const V& val)
	{m_map.insert(PairType(key, val));}

	
	/// 移除該元素,不檢查是否存在
	void removeByKey(const K& key)
	{m_map.erase(key);}


	/// 是否包含這個key值
	bool containKey(const K& key)
	{return m_map.find(key)!=m_map.end();}


	/// 回傳該key對應的元素,不檢查是否存在
	/// 存取不存在元素會造成空元素的存在,使用請小心
	V& operator[](const K& key)
	{return m_map[key];}
	

	/// 回傳該key對應的元素,檢查是否存在
	bool tryGet(const K& key, V& val)
	{
		if(!ContainKey(key))
			return false;

		val = m_map[key];
		return true;
	}


	/// 目前元素的數量
	int size()
	{return m_map.size();}


	/// 清除所有資料
	void clear()
	{m_map.clear();}


	V& value()
	{return (*m_it).second;}


	const K& key()
	{return (*m_it).first;}


	void begin()
	{
		m_reset = false;
		m_it = m_map.begin();
	}


	bool end()
	{return m_it == m_map.end();}


	void remove()
	{
		typename MapType::iterator _tmp;
		_tmp = m_it;
		
		if(m_it==m_map.begin())
			m_reset = true;
		else
			--m_it;
		
		m_map.erase(_tmp);

		if(m_reset)
			m_it = m_map.begin();
	}


	Dictionary<K,V> & operator++()
	{
		if(m_reset) m_reset=false;
		else		++m_it;
		return (*this);
	}


	const Dictionary<K,V> operator++(int i)
	{
		if(m_reset) m_reset=false;
		else		++m_it;

		++m_it;
		Dictionary<K,V> _tmp;
		return _tmp;
	}


};
}

#endif
