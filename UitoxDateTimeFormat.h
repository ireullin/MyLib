#ifndef __UITOXDATETIMEFORMAT__
#define __UITOXDATETIMEFORMAT__

namespace Uitox{
namespace TimeFormat{


/// 8 yards date format without symbol.
/// Ex. 20110701
struct EightNumDate
{
	std::string operator()(int year, int month, int day, int hour, int minute, int second, int millisecond)
	{
		char _acBuff[20];
		sprintf( _acBuff, "%04d%02d%02d\0", year, month, day);
		std::string _szBuff = static_cast<std::string>(_acBuff);
		return _szBuff;
	}

};
struct EightNumDate eightNumDate;


/// 6 yards time format without symbol.
/// Ex. 132325
struct SixNumTime
{
	std::string operator()(int year, int month, int day, int hour, int minute, int second, int millisecond)
	{
		char _acBuff[20];
		sprintf( _acBuff, "%02d%02d%02d\0", hour, minute, second);
		std::string _szBuff = static_cast<std::string>(_acBuff);
		return _szBuff;
	}

};
struct SixNumTime sixNumTime;


/// 6 yards time format without symbol.
/// Ex. 122342021
struct NineNumTime
{
	std::string operator()(int year, int month, int day, int hour, int minute, int second, int millisecond)
	{
		char _acBuff[20];
		sprintf( _acBuff, "%02d%02d%02d%03d\0", hour, minute, second, millisecond);
		std::string _szBuff = static_cast<std::string>(_acBuff);
		return _szBuff;
	}

};
struct NineNumTime nineNumTime;


/// 13:45:21.254
struct StandardTime
{
	std::string operator()(int year, int month, int day, int hour, int minute, int second, int millisecond)
	{
		char _acBuff[25];
		sprintf( _acBuff, "%02d:%02d:%02d.%03d\0", hour, minute, second, millisecond);
		std::string _szBuff = static_cast<std::string>(_acBuff);
		return _szBuff;
	}

};
struct StandardTime standardTime;


/// 20070806134521254
struct SeventeenNum
{
	std::string operator()(int year, int month, int day, int hour, int minute, int second, int millisecond)
	{
		char _acBuff[25];
		sprintf( _acBuff, "%04d%02d%02d%02d%02d%02d%03d\0", year, month, day, hour, minute, second, millisecond);
		std::string _szBuff = static_cast<std::string>(_acBuff);
		return _szBuff;
	}

};
struct SeventeenNum seventeenNum;

}
}

#endif