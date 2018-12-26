/*
* Copyright (c) 2017-2018 the BasicX authors
* All rights reserved.
*
* The project sponsor and lead author is Xu Rendong.
* E-mail: xrd@ustc.edu, QQ: 277195007, WeChat: ustc_xrd
* See the contributors file for names of other contributors.
*
* Commercial use of this code in source and binary forms is
* governed by a LGPL v3 license. You may get a copy from the
* root directory. Or else you should get a specific written
* permission from the project author.
*
* Individual and educational use of this code in source and
* binary forms is governed by a 3-clause BSD license. You may
* get a copy from the root directory. Certainly welcome you
* to contribute code of all sorts.
*
* Be sure to retain the above copyright notice and conditions.
*/

#ifndef BASICX_COMMON_ASSIST_H
#define BASICX_COMMON_ASSIST_H

#include <ctime>
#include <string>
#include <tchar.h>
#include <stdint.h> // int32_t, int64_t
#include <iostream>
#include <iomanip>
#include <sstream>

#include "sysdef.h"

#ifdef __OS_WINDOWS__
#include <windows.h>
#endif

#ifdef __GNUC__
#include <endian.h>
#endif

namespace basicx {

	// typedef uint16_t char16_t;
	// typedef std::basic_string<char16_t>

	inline tm GetNowTime() {
		tm now_time;
		time_t now_time_t;
		time( &now_time_t );
		localtime_s( &now_time, &now_time_t );
		return now_time;
	}

	inline double Round_1( double number, const size_t bits ) { // 很快：i7-7500U 100亿次约11.53秒
		double integer_part = floor( number );
		number -= integer_part;
		for( size_t i = 0; i < bits; ++i ) {
			number *= 10;
		}
		number = floor( number + 0.5 );
		for( size_t i = 0; i < bits; ++i ) {
			number /= 10;
		}
		return integer_part + number;
	}

	inline double Round_2( const double number, const size_t bits ) { // 很快：i7-7500U 100亿次约11.53秒
		double result = 0.0;
		double module = number >= 0.0 ? 0.0000001 : -0.0000001;
		result = number;
		result += 5.0 / pow( 10.0, bits + 1.0 );
		result *= pow( 10.0, bits );
		result = floor( result + module );
		result /= pow( 10.0, bits );
		return result;
	}

	inline double Round_3( double number, const size_t bits ) { // 很慢：i7-7500U 1000万次约17秒
		std::stringstream ss;
		ss << std::fixed << std::setprecision( bits ) << number;
		ss >> number;
		return number;
	}

	//double number = 3.1415926535827932;
	//std::cout << std::fixed << std::showpoint << std::setprecision( 15 );
	//std::cout << "number = " << number << std::endl;
	//for( size_t i = 0; i < 15; ++i ) {
	//	std::cout << "number 保留 " << i << " 位小数后为: " << basicx::Round_1( number, i ) << std::endl; // Round_1、Round_2、Round_3
	//}

	inline double NearPrice( const double input_price, const double min_price_unit, const size_t price_places ) {
		int64_t price_temp = (int64_t)std::floor( input_price * std::pow( 10.0, price_places + 1 ) ); // 多保留一位，之后的截掉
		int64_t min_price_unit_temp = (int64_t)( min_price_unit * std::pow( 10.0, price_places + 1 ) );
		int64_t remainder_temp = price_temp % min_price_unit_temp;
		double min_price_unit_temp_half = (double)min_price_unit_temp / 2.0;
		// 下面比较大小，有可能均价刚好处于一个最小报价单位的中间，比如报价单位 0.05 均价 10.025 而上下两个价格为 10.05 和 10.00， 这里就用 >= 判断了，四舍五入嘛
		price_temp = remainder_temp >= min_price_unit_temp_half ? ( price_temp - remainder_temp + min_price_unit_temp ) : ( price_temp - remainder_temp );
		double output_price = (double)price_temp / std::pow( 10.0, price_places + 1 );
		// std::cout << std::setprecision( 6 ) << input_price << "：" << output_price << std::endl;
		return output_price;
	}

	inline std::string StringLeftTrim( const std::string& source, const std::string& drop ) {
		std::string result( source );
		return result.erase( 0, result.find_first_not_of( drop ) );
	}

	inline std::string StringRightTrim( const std::string& source, const std::string& drop ) {
		std::string result( source );
		return result.erase( result.find_last_not_of( drop ) + 1 );
	}

	inline std::string StringTrim( const std::string& source, const std::string& drop ) {
		return StringLeftTrim( StringRightTrim( source, drop ), drop );
	}

	inline void StringReplace( std::string& str_str, const std::string& str_src, const std::string& str_dst ) {
		std::string::size_type pos = 0;
		std::string::size_type src_len = str_src.size();
		std::string::size_type dst_len = str_dst.size();
		while( ( pos = str_str.find( str_src, pos ) ) != std::string::npos ) {
			str_str.replace( pos, src_len, str_dst );
			pos += dst_len;
		}
	}

	inline void AnsiCharToWideChar( const char* source, std::wstring& result ) {
#ifdef __OS_WINDOWS__
		int32_t ansi_length = MultiByteToWideChar( 0, 0, source, -1, NULL, 0 );
		wchar_t* temp_wide = new wchar_t[ansi_length + 1]; // 不加也行
		memset( temp_wide, 0, ansi_length * 2 + 2 );
		MultiByteToWideChar( 0, 0, source, -1, temp_wide, ansi_length );
		result = std::wstring( temp_wide );
		delete[] temp_wide;
#endif
	}

	inline void WideCharToAnsiChar( const wchar_t* source, std::string& result ) {
#ifdef __OS_WINDOWS__
		int32_t wide_length = WideCharToMultiByte( CP_OEMCP, NULL, source, -1, NULL, 0, NULL, FALSE );
		char* temp_ansi = new char[wide_length + 2]; // 不加也行
		memset( temp_ansi, 0, wide_length + 2 );
		WideCharToMultiByte( CP_OEMCP, NULL, source, -1, temp_ansi, wide_length, NULL, FALSE );
		result = std::string( temp_ansi );
		delete[] temp_ansi;
#endif
	}

	inline void GB2312toUTF8( const char* source, std::string& result ) {
#ifdef __OS_WINDOWS__
		int32_t unicode_length = MultiByteToWideChar( CP_ACP, 0, source, -1, NULL, 0 );
		wchar_t* temp_unicode = new wchar_t[unicode_length + 1];
		memset( temp_unicode, 0, unicode_length * 2 + 2 );
		MultiByteToWideChar( CP_ACP, 0, source, -1, temp_unicode, unicode_length ); // GB2312 to Unicode
		int32_t utf8_length = WideCharToMultiByte( CP_UTF8, 0, temp_unicode, -1, NULL, 0, NULL, NULL );
		char* temp_utf8 = new char[utf8_length + 1];
		memset( temp_utf8, 0, utf8_length + 1 );
		WideCharToMultiByte( CP_UTF8, 0, temp_unicode, -1, temp_utf8, utf8_length, NULL, NULL ); // Unicode to UTF8
		result = std::string( temp_utf8 );
		delete[] temp_utf8;
		delete[] temp_unicode;
#endif
	}

	inline void UTF8toGB2312( const char* source, std::string& result ) {
#ifdef __OS_WINDOWS__
		int32_t unicode_length = MultiByteToWideChar( CP_UTF8, 0, source, -1, NULL, 0 );
		wchar_t* temp_unicode = new wchar_t[unicode_length + 1];
		memset( temp_unicode, 0, unicode_length * 2 + 2 );
		MultiByteToWideChar( CP_UTF8, 0, source, -1, temp_unicode, unicode_length ); // UTF8 to Unicode
		int32_t gb2312_length = WideCharToMultiByte( CP_ACP, 0, temp_unicode, -1, NULL, 0, NULL, NULL );
		char* temp_gb2312 = new char[gb2312_length + 1];
		memset( temp_gb2312, 0, gb2312_length + 1 );
		WideCharToMultiByte( CP_ACP, 0, temp_unicode, -1, temp_gb2312, gb2312_length, NULL, NULL ); // Unicode to GB2312
		result = std::string( temp_gb2312 );
		delete[] temp_gb2312;
		delete[] temp_unicode;
#endif
	}

	inline std::wstring StringToWideChar( const std::string& source ) {
		std::wstring result = L"";
		AnsiCharToWideChar( source.c_str(), result );
		return result;
	}

	inline std::string StringToAnsiChar( const std::wstring& source ) {
		std::string result = "";
		WideCharToAnsiChar( source.c_str(), result );
		return result;
	}

	inline std::string StringToUTF8( const std::string& source ) {
		std::string result = "";
		GB2312toUTF8( source.c_str(), result );
		return result;
	}

	inline std::string StringToGB2312( const std::string& source ) {
		std::string result = "";
		UTF8toGB2312( source.c_str(), result );
		return result;
	}

	inline std::wstring StringToWideChar( const char* source ) {
		return StringToWideChar( std::string( source ) );
	}

	inline std::string StringToAnsiChar( const wchar_t* source ) {
		return StringToAnsiChar( std::wstring( source ) );
	}

	inline std::string StringToUTF8( const char* source ) {
		return StringToUTF8( std::string( source ) );
	}

	inline std::string StringToGB2312( const char* source ) {
		return StringToGB2312( std::string( source ) );
	}

	// 以下 UTF16 和 UTF8 的相互转换都是在小端序下进行

	static inline uint16_t byteswap_ushort( uint16_t number ) {
#if defined(_MSC_VER) && _MSC_VER > 1310
		return _byteswap_ushort( number );
#elif defined(__GNUC__)
		return __builtin_bswap16( number );
#else
		return ( number >> 8 ) | ( number << 8 );
#endif
	}

	inline std::string UTF16LE_To_UTF8( const std::u16string& u16str ) {
		if( u16str.empty() ) {
			return std::string();
		}
		const char16_t* data = u16str.data();
		std::u16string::size_type len = u16str.length();
		if( data[0] == 0xFEFF ) { // 带有 bom 标记
			data += 1; // 后移
			len -= 1;
		}
		std::string u8str;
		u8str.reserve( len * 2 );
		char16_t u16char;
		for( std::u16string::size_type i = 0; i < len; ++i ) { // 这里假设是在小端序下，大端序不适用
			u16char = data[i];
			if( u16char < 0x0080 ) { // 1 字节表示部分 // u16char <= 0x007F
									 // U-00000000 - U-000007FF : 0xxxxxxx
				u8str.push_back( (char)( u16char & 0x00FF ) ); // 取低 8 bit
				continue;
			}
			if( u16char >= 0x0080 && u16char <= 0x07FF ) { // 2 字节表示部分
														   // U-00000080 - U-000007FF : 110xxxxx 10xxxxxx
				u8str.push_back( (char)( ( ( u16char >> 6 ) & 0x1F ) | 0xC0 ) );
				u8str.push_back( (char)( ( u16char & 0x3F ) | 0x80 ) );
				continue;
			}
			if( u16char >= 0xD800 && u16char <= 0xDBFF ) { // 4 字节表示部分
														   // U-00010000 - U-001FFFFF : 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
				uint32_t high_sur = u16char;
				uint32_t low_sur = data[++i];
				// 从代理项对到 UNICODE 代码点转换
				uint32_t code_point = high_sur - 0xD800; // 1、从高代理项减去 0xD800 获取有效 10 bit
				code_point <<= 10;
				code_point |= low_sur - 0xDC00; // 2、从低代理项减去 0xDC00 获取有效 10 bit
				code_point += 0x10000; // 3、加上 0x10000 获取 UNICODE 代码点值
									   // 转为 4 字节 UTF8 编码表示
				u8str.push_back( (char)( ( code_point >> 18 ) | 0xF0 ) );
				u8str.push_back( (char)( ( ( code_point >> 12 ) & 0x3F ) | 0x80 ) );
				u8str.push_back( (char)( ( ( code_point >> 06 ) & 0x3F ) | 0x80 ) );
				u8str.push_back( (char)( ( code_point & 0x3F ) | 0x80 ) );
				continue;
			}
			{ // 3 字节表示部分
			  // U-0000E000 - U-0000FFFF : 1110xxxx 10xxxxxx 10xxxxxx
				u8str.push_back( (char)( ( ( u16char >> 12 ) & 0x0F ) | 0xE0 ) );
				u8str.push_back( (char)( ( ( u16char >> 6 ) & 0x3F ) | 0x80 ) );
				u8str.push_back( (char)( ( u16char & 0x3F ) | 0x80 ) );
				continue;
			}
		}
		return u8str;
	}

	inline std::string UTF16BE_To_UTF8( const std::u16string& u16str ) {
		if( u16str.empty() ) {
			return std::string();
		}
		const char16_t* data = u16str.data();
		std::u16string::size_type len = u16str.length();
		if( data[0] == 0xFFFE ) { // 带有 bom 标记
			data += 1; // 后移
			len -= 1;
		}
		std::string u8str;
		u8str.reserve( len * 2 );
		char16_t u16char;
		for( std::u16string::size_type i = 0; i < len; ++i ) { // 这里假设是在小端序下，大端序不适用
			u16char = data[i];
			u16char = byteswap_ushort( u16char ); // 将大端序转为小端序
			if( u16char < 0x0080 ) { // 1 字节表示部分 // u16char <= 0x007F
									 // U-00000000 - U-000007FF : 0xxxxxxx
				u8str.push_back( (char)( u16char & 0x00FF ) ); // 取低 8 bit
				continue;
			}
			if( u16char >= 0x0080 && u16char <= 0x07FF ) { // 2 字节表示部分
														   // U-00000080 - U-000007FF : 110xxxxx 10xxxxxx
				u8str.push_back( (char)( ( ( u16char >> 6 ) & 0x1F ) | 0xC0 ) );
				u8str.push_back( (char)( ( u16char & 0x3F ) | 0x80 ) );
				continue;
			}
			if( u16char >= 0xD800 && u16char <= 0xDBFF ) { // 4 字节表示部分
														   // U-00010000 - U-001FFFFF : 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
				uint32_t high_sur = u16char;
				uint32_t low_sur = byteswap_ushort( data[++i] );
				// 从代理项对到 UNICODE 代码点转换
				uint32_t code_point = high_sur - 0xD800; // 1、从高代理项减去 0xD800 获取有效 10 bit
				code_point <<= 10;
				code_point |= low_sur - 0xDC00; // 2、从低代理项减去 0xDC00 获取有效 10 bit
				code_point += 0x10000; // 3、加上 0x10000 获取 UNICODE 代码点值
									   // 转为 4 字节 UTF8 编码表示
				u8str.push_back( (char)( ( code_point >> 18 ) | 0xF0 ) );
				u8str.push_back( (char)( ( ( code_point >> 12 ) & 0x3F ) | 0x80 ) );
				u8str.push_back( (char)( ( ( code_point >> 06 ) & 0x3F ) | 0x80 ) );
				u8str.push_back( (char)( ( code_point & 0x3F ) | 0x80 ) );
				continue;
			}
			{ // 3 字节表示部分
			  // U-0000E000 - U-0000FFFF : 1110xxxx 10xxxxxx 10xxxxxx
				u8str.push_back( (char)( ( ( u16char >> 12 ) & 0x0F ) | 0xE0 ) );
				u8str.push_back( (char)( ( ( u16char >> 6 ) & 0x3F ) | 0x80 ) );
				u8str.push_back( (char)( ( u16char & 0x3F ) | 0x80 ) );
				continue;
			}
		}
		return u8str;
	}

	inline std::string UTF16_To_UTF8( const std::u16string& u16str ) { // 需要带 BOM 标记
		if( u16str.empty() ) {
			return std::string();
		}
		char16_t bom = u16str[0];
		switch( bom ) {
		case 0xFEFF: // 小端序
			return UTF16LE_To_UTF8( u16str );
			break;
		case 0xFFFE: // 大端序
			return UTF16BE_To_UTF8( u16str );
			break;
		default:
			return std::string();
		}
	}

	inline std::u16string UTF8_To_UTF16LE( const std::string& u8str, bool add_bom ) {
		std::u16string u16str;
		u16str.reserve( u8str.size() );
		std::string::size_type len = u8str.length();
		if( add_bom ) {
			u16str.push_back( 0xFEFF ); // 添加 bom 标记
		}
		const unsigned char* data = (unsigned char*)( u8str.data() );
		if( len > 3 && data[0] == 0xEF && data[1] == 0xBB && data[2] == 0xBF ) { // 判断是否具有 bom 即判断长度小于 3 字节的情况
			data += 3;
			len -= 3;
		}
		for( std::string::size_type i = 0; i < len; ++i ) {
			uint32_t c1 = data[i]; // 取出 UTF8 序列首字节
			if( 0 == ( c1 & 0x80 ) ) { // 最高位为 0 只有 1 字节表示 UNICODE 代码点
				u16str.push_back( (char16_t)c1 );
				continue;
			}
			switch( c1 & 0xF0 ) {
			case 0xF0: { // 4 字节字符 0x10000 到 0x10FFFF
				uint32_t c2 = data[++i];
				uint32_t c3 = data[++i];
				uint32_t c4 = data[++i];
				uint32_t code_point = ( ( c1 & 0x07U ) << 18 ) | ( ( c2 & 0x3FU ) << 12 ) | ( ( c3 & 0x3FU ) << 6 ) | ( c4 & 0x3FU ); // 计算 UNICODE 代码点值，第一个字节取低 3 bit 其余取 6 bit
				if( code_point >= 0x10000 ) { // 在UTF-16 中 U+10000 到 U+10FFFF 用两个 16 bit 单元表示代理项对
					code_point -= 0x10000; // 1、将代码点减去 0x10000 得到长度为 20 bit 的值
					u16str.push_back( (char16_t)( ( code_point >> 10 ) | 0xD800U ) ); // 2、高代理项 是将那 20 bit 中的高 10 bit 加上 0xD800(11011000 00000000)
					u16str.push_back( (char16_t)( ( code_point & 0x03FFU ) | 0xDC00U ) ); // 3、低代理项 是将那 20 bit 中的低 10 bit 加上 0xDC00(11011100 00000000)
				}
				else { // 在 UTF-16 中 U+0000 到 U+D7FF 以及 U+E000 到 U+FFFF 与 UNICODE 代码点值相同，U+D800 到 U+DFFF 是无效字符这里假设不存在如果存在则不做编码
					u16str.push_back( (char16_t)code_point );
				}
				break;
			}
			case 0xE0: { // 3 字节字符 0x800 到 0xFFFF
				uint32_t c2 = data[++i];
				uint32_t c3 = data[++i];
				uint32_t code_point = ( ( c1 & 0x0FU ) << 12 ) | ( ( c2 & 0x3FU ) << 6 ) | ( c3 & 0x3FU ); // 计算 UNICODE 代码点值，第一个字节取低 4 bit 其余取 6 bit
				u16str.push_back( (char16_t)code_point );
				break;
			}
			case 0xD0:
			case 0xC0: { // 2 字节字符 0x80 到 0x7FF
				uint32_t c2 = data[++i];
				uint32_t code_point = ( ( c1 & 0x1FU ) << 12 ) | ( ( c2 & 0x3FU ) << 6 ); // 计算 UNICODE 代码点值，第一个字节取低 5 bit 其余取 6 bit
				u16str.push_back( (char16_t)code_point );
				break;
			}
			default: // 单字节部分，前面已经处理
				break;
			}
		}
		return u16str;
	}

	inline std::u16string UTF8_To_UTF16BE( const std::string& u8str, bool add_bom ) {
		std::u16string u16str = UTF8_To_UTF16LE( u8str, add_bom ); // 先获取 UTF-16 LE 编码字符串
		for( size_t i = 0; i < u16str.size(); ++i ) {
			u16str[i] = byteswap_ushort( u16str[i] ); // 将小端序转换为大端序
		}
		return u16str;
	}

	// 以上 UTF16 和 UTF8 的相互转换都是在小端序下进行

	inline int64_t GetPerformanceFrequency() {
#ifdef __OS_WINDOWS__
		LARGE_INTEGER frequency;
		QueryPerformanceFrequency( &frequency ); // 每秒跳动次数
		return frequency.QuadPart;
#endif
	}

	inline int64_t GetPerformanceTickCount() {
#ifdef __OS_WINDOWS__
		LARGE_INTEGER tick_count;
		QueryPerformanceCounter( &tick_count ); // 当前跳动次数
		return tick_count.QuadPart;
#endif
	}

	// windows：
	// THREAD_PRIORITY_ERROR_RETURN (MAXLONG) 0x7FFFFFFF 2147483647
	// THREAD_PRIORITY_TIME_CRITICAL == THREAD_BASE_PRIORITY_LOWRT 15 // value that gets a thread to LowRealtime-1
	// THREAD_PRIORITY_HIGHEST == THREAD_BASE_PRIORITY_MAX 2 // maximum thread base priority boost
	// THREAD_PRIORITY_ABOVE_NORMAL (THREAD_PRIORITY_HIGHEST-1)
	// THREAD_PRIORITY_NORMAL 0
	// THREAD_PRIORITY_BELOW_NORMAL (THREAD_PRIORITY_LOWEST+1)
	// THREAD_PRIORITY_LOWEST == THREAD_BASE_PRIORITY_MIN (-2) // minimum thread base priority boost
	// THREAD_PRIORITY_IDLE == THREAD_BASE_PRIORITY_IDLE (-15) // value that gets a thread to idle

	inline void SetThreadPriority( const int32_t thread_priority ) {
		::SetThreadPriority( GetCurrentThread(), thread_priority );
	}

	inline bool BindProcess( const size_t processor_number ) {
#ifdef __OS_WINDOWS__
		if( processor_number >= 1 && processor_number <= 32 ) {
			typedef void (CALLBACK* ULPRET)(SYSTEM_INFO*);
			ULPRET proc_address;
			HINSTANCE library;
			SYSTEM_INFO system_info;
			library = LoadLibraryA( "kernel32.dll" );
			if( library ) {
				proc_address = (ULPRET)GetProcAddress( library, "GetNativeSystemInfo" );
				if( proc_address ) { // 可以用 GetNativeSystemInfo，但是32位程序中 ActiveProcessorMask 最大还是只能32位即4294967295
					(*proc_address)(&system_info); // 等同于 GetNativeSystemInfo( &system_info );
				}
				else {
					GetSystemInfo( &system_info ); // 在64位系统，NumberOfProcessors 最大 32 个，ProcessorArchitecture 为 0 不正确
				}
				FreeLibrary( library );
			}

			// std::cout << "处理器：线程 = " << system_info.dwNumberOfProcessors << ", 活动 = " << system_info.dwActiveProcessorMask << ", 水平 = " << system_info.wProcessorLevel << ", 架构 = " << system_info.wProcessorArchitecture << ", 分页 = " << system_info.dwPageSize << "\n";

			if( processor_number > (int32_t)system_info.dwNumberOfProcessors ) {
				// std::cout << "进程绑定处理器时，核心线程编号 " << processor_number << " 超过 核心线程数 " << system_info.dwNumberOfProcessors << " 个！" << "\n";
				return false;
			}
			else {
				DWORD temp = 0x0001;
				DWORD mask = 0x0000;
				for( int32_t i = 0; i < 32; i++ ) { // 32位 0x0000
					if( ( i + 1 ) == processor_number ) {
						mask = temp;
						break;
					}
					temp *= 2; // 前移一位
				}

				// if( SetProcessAffinityMask( GetCurrentProcess(), mask ) ) {
				if( SetThreadAffinityMask( GetCurrentThread(), mask ) ) {
					// std::cout << "线程绑定至第 " << processor_number << " 个核心线程完成。" << "\n" << "\n";
					return true;
				}
				else {
					// std::cout << "线程绑定至第 " << processor_number << " 个核心线程失败！" << "\n" << "\n";
					return false;
				}
			}
		}
		return false;
#endif
	}

	inline void SetMinimumTimerResolution() {
#ifdef __OS_WINDOWS__
		typedef uint32_t* ( WINAPI* lpNST )( uint32_t, bool, uint32_t* );
		typedef uint32_t* ( WINAPI* lpNQT )( uint32_t*, uint32_t*, uint32_t* );
		HMODULE library = LoadLibrary( TEXT( "ntdll.dll" ) );
		if( library ) {
			lpNST NtSetTimerResolution = (lpNST)GetProcAddress( library, "NtSetTimerResolution" );
			lpNQT NtQueryTimerResolution = (lpNQT)GetProcAddress( library, "NtQueryTimerResolution" );
			if( nullptr == NtQueryTimerResolution || nullptr == NtSetTimerResolution ) {
				printf( "SetMinimumTimerResolution: Search function failed!\n" );
			}
			else {
				uint32_t max = 0;
				uint32_t min = 0;
				uint32_t cur = 0;
				uint32_t ret = 0;
				if( 0 == NtQueryTimerResolution( &max, &min, &cur ) ) {
					NtSetTimerResolution( min, true, &ret );
				}
			}
			FreeLibrary( library );
		}
#endif
	}

} // namespace basicx

#endif // BASICX_COMMON_ASSIST_H
