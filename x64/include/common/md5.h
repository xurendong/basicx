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

#ifndef BASICX_COMMON_MD5_H
#define BASICX_COMMON_MD5_H

#include <string>
#include <fstream>
#include <iostream>

namespace basicx {

	// MD5 转换路由
	#define S11  7
	#define S12 12
	#define S13 17
	#define S14 22
	#define S21  5
	#define S22  9
	#define S23 14
	#define S24 20
	#define S31  4
	#define S32 11
	#define S33 16
	#define S34 23
	#define S41  6
	#define S42 10
	#define S43 15
	#define S44 21

	// MD5 基础函数
	#define F(x, y, z) (((x) & (y)) | ((~x) & (z)))
	#define G(x, y, z) (((x) & (z)) | ((y) & (~z)))
	#define H(x, y, z) ((x) ^ (y) ^ (z))
	#define I(x, y, z) ((y) ^ ((x) | (~z)))

	// 轮换 x 剩 n 位
	#define ROTATE_LEFT(x, n) (((x) << (n)) | ((x) >> (32-(n))))

	// 转换，从加法中隔离轮换以避免重复计算
	#define FF(a, b, c, d, x, s, ac) { \
		(a) += F ((b), (c), (d)) + (x) + ac; \
		(a) = ROTATE_LEFT ((a), (s)); \
		(a) += (b); \
	}
	#define GG(a, b, c, d, x, s, ac) { \
		(a) += G ((b), (c), (d)) + (x) + ac; \
		(a) = ROTATE_LEFT ((a), (s)); \
		(a) += (b); \
	}
	#define HH(a, b, c, d, x, s, ac) { \
		(a) += H ((b), (c), (d)) + (x) + ac; \
		(a) = ROTATE_LEFT ((a), (s)); \
		(a) += (b); \
	}
	#define II(a, b, c, d, x, s, ac) { \
		(a) += I ((b), (c), (d)) + (x) + ac; \
		(a) = ROTATE_LEFT ((a), (s)); \
		(a) += (b); \
	}

	typedef unsigned char byte;
	typedef unsigned long ulong;

	class MD5
	{
	public:
		MD5() {
			Reset();
		}

		MD5( const void* input, size_t length ) {
			Reset();
			Update( input, length );
		}

		MD5( const std::string& str ) {
			Reset();
			Update( str );
		}

		MD5( std::ifstream& file ) {
			Reset();
			Update( file );
		}

		const byte* Digest() { // 返回消息摘要
			if( !m_finished ) {
				m_finished = true;
				Final();
			}
			return m_digest;
		}

		void Reset() { // 重置计算状态
			m_finished = false;
			m_count[0] = m_count[1] = 0; // 重置位数
			// 加载初始化常量
			m_state[0] = 0x67452301;
			m_state[1] = 0xefcdab89;
			m_state[2] = 0x98badcfe;
			m_state[3] = 0x10325476;
		}

		void Update( const void* input, size_t length ) { // 用输入缓存更新上下文
			Update( (const byte*)input, length );
		}

		void Update( const std::string& str ) { // 用字符串更新上下文
			Update( (const byte*)str.c_str(), str.length() );
		}

		void Update( std::ifstream& file ) { // 用文件更新上下文
			if( !file ) {
				return;
			}
			std::streamsize length;
			char buffer[m_buffer_size];
			while( !file.eof() ) {
				file.read( buffer, m_buffer_size );
				length = file.gcount();
				if( length > 0 ) {
					Update( buffer, (size_t)length );
				}
			}
			file.close();
		}

		std::string ToString() { // 转换摘要为字符串
			return BytesToHexString( Digest(), 16 );
		}

		void PrintMD5( const std::string& str, MD5& md5 ) { // 用于测试
			std::cout << "MD5(\"" << str << "\") = " << md5.ToString() << std::endl;
		}

		std::string FileDigest( const std::string& file ) { // 用于测试
			std::ifstream input( file.c_str(), std::ios::binary );
			if( !input ) {
				return "";
			}
			MD5 md5;
			std::streamsize length;
			char buffer[1024];
			while( !input.eof() ) {
				input.read( buffer, 1024 );
				length = input.gcount();
				if( length > 0 ) {
					md5.Update( buffer, length );
				}
			}
			input.close();
			return md5.ToString();
		}

	private:
		MD5( const MD5& md5 ) { // 禁止拷贝
		};

		MD5& operator=( const MD5& md5 ) { // 禁止赋值
		};

		void Update( const byte* input, size_t length ) {
			ulong i = 0;
			m_finished = false;
			ulong index = (ulong)( ( m_count[0] >> 3 ) & 0x3f ); // 计算模 64 的字节数
			if( ( m_count[0] += ( (ulong)length << 3 ) ) < ( (ulong)length << 3 ) ) { // 更新位数
				m_count[1]++;
			}
			m_count[1] += ( (ulong)length >> 29 );
			ulong part_length = 64 - index;
			if( length >= part_length ) { // 尽可能多地转换
				memcpy( &m_buffer[index], input, part_length );
				Transform( m_buffer );
				for( i = part_length; i + 63 < length; i += 64 ) {
					Transform( &input[i] );
				}
				index = 0;
			}
			memcpy( &m_buffer[index], &input[i], length - i ); // 剩余缓存
		}

		void Final() { // 结束消息摘要，写入消息摘要，上下文置零
			byte bits[8];
			ulong old_state[4];
			ulong old_count[2];
			memcpy( old_state, m_state, 16 ); // 保存状态
			memcpy( old_count, m_count, 8 ); // 保存计数
			Encode( m_count, bits, 8 ); // 保存位数
			// 填充 56 模 64
			ulong index = (ulong)( ( m_count[0] >> 3 ) & 0x3f );
			ulong pad_length = ( index < 56 ) ? ( 56 - index ) : ( 120 - index );
			Update( m_padding, pad_length );
			Update( bits, 8 ); // 填充前扩展长度
			Encode( m_state, m_digest, 16 ); // 摘要中保存状态
			memcpy( m_state, old_state, 16 ); // 还原状态
			memcpy( m_count, old_count, 8 ); // 还原计数
		}

		void Transform( const byte block[64] ) { // MD5 基础转换，基于块转换状态
			ulong a = m_state[0];
			ulong b = m_state[1];
			ulong c = m_state[2];
			ulong d = m_state[3];
			ulong x[16];
			Decode( block, x, 64 );
			// Round 1
			FF( a, b, c, d,  x[0], S11, 0xd76aa478 ); //  1
			FF( d, a, b, c,  x[1], S12, 0xe8c7b756 ); //  2
			FF( c, d, a, b,  x[2], S13, 0x242070db ); //  3
			FF( b, c, d, a,  x[3], S14, 0xc1bdceee ); //  4
			FF( a, b, c, d,  x[4], S11, 0xf57c0faf ); //  5
			FF( d, a, b, c,  x[5], S12, 0x4787c62a ); //  6
			FF( c, d, a, b,  x[6], S13, 0xa8304613 ); //  7
			FF( b, c, d, a,  x[7], S14, 0xfd469501 ); //  8
			FF( a, b, c, d,  x[8], S11, 0x698098d8 ); //  9
			FF( d, a, b, c,  x[9], S12, 0x8b44f7af ); // 10
			FF( c, d, a, b, x[10], S13, 0xffff5bb1 ); // 11
			FF( b, c, d, a, x[11], S14, 0x895cd7be ); // 12
			FF( a, b, c, d, x[12], S11, 0x6b901122 ); // 13
			FF( d, a, b, c, x[13], S12, 0xfd987193 ); // 14
			FF( c, d, a, b, x[14], S13, 0xa679438e ); // 15
			FF( b, c, d, a, x[15], S14, 0x49b40821 ); // 16
			// Round 2
			GG( a, b, c, d,  x[1], S21, 0xf61e2562 ); // 17
			GG( d, a, b, c,  x[6], S22, 0xc040b340 ); // 18
			GG( c, d, a, b, x[11], S23, 0x265e5a51 ); // 19
			GG( b, c, d, a,  x[0], S24, 0xe9b6c7aa ); // 20
			GG( a, b, c, d,  x[5], S21, 0xd62f105d ); // 21
			GG( d, a, b, c, x[10], S22, 0x2441453  ); // 22
			GG( c, d, a, b, x[15], S23, 0xd8a1e681 ); // 23
			GG( b, c, d, a,  x[4], S24, 0xe7d3fbc8 ); // 24
			GG( a, b, c, d,  x[9], S21, 0x21e1cde6 ); // 25
			GG( d, a, b, c, x[14], S22, 0xc33707d6 ); // 26
			GG( c, d, a, b,  x[3], S23, 0xf4d50d87 ); // 27
			GG( b, c, d, a,  x[8], S24, 0x455a14ed ); // 28
			GG( a, b, c, d, x[13], S21, 0xa9e3e905 ); // 29
			GG( d, a, b, c,  x[2], S22, 0xfcefa3f8 ); // 30
			GG( c, d, a, b,  x[7], S23, 0x676f02d9 ); // 31
			GG( b, c, d, a, x[12], S24, 0x8d2a4c8a ); // 32
			// Round 3
			HH( a, b, c, d,  x[5], S31, 0xfffa3942 ); // 33
			HH( d, a, b, c,  x[8], S32, 0x8771f681 ); // 34
			HH( c, d, a, b, x[11], S33, 0x6d9d6122 ); // 35
			HH( b, c, d, a, x[14], S34, 0xfde5380c ); // 36
			HH( a, b, c, d,  x[1], S31, 0xa4beea44 ); // 37
			HH( d, a, b, c,  x[4], S32, 0x4bdecfa9 ); // 38
			HH( c, d, a, b,  x[7], S33, 0xf6bb4b60 ); // 39
			HH( b, c, d, a, x[10], S34, 0xbebfbc70 ); // 40
			HH( a, b, c, d, x[13], S31, 0x289b7ec6 ); // 41
			HH( d, a, b, c,  x[0], S32, 0xeaa127fa ); // 42
			HH( c, d, a, b,  x[3], S33, 0xd4ef3085 ); // 43
			HH( b, c, d, a,  x[6], S34, 0x4881d05  ); // 44
			HH( a, b, c, d,  x[9], S31, 0xd9d4d039 ); // 45
			HH( d, a, b, c, x[12], S32, 0xe6db99e5 ); // 46
			HH( c, d, a, b, x[15], S33, 0x1fa27cf8 ); // 47
			HH( b, c, d, a,  x[2], S34, 0xc4ac5665 ); // 48
			//Round 4
			II( a, b, c, d,  x[0], S41, 0xf4292244 ); // 49
			II( d, a, b, c,  x[7], S42, 0x432aff97 ); // 50
			II( c, d, a, b, x[14], S43, 0xab9423a7 ); // 51
			II( b, c, d, a,  x[5], S44, 0xfc93a039 ); // 52
			II( a, b, c, d, x[12], S41, 0x655b59c3 ); // 53
			II( d, a, b, c,  x[3], S42, 0x8f0ccc92 ); // 54
			II( c, d, a, b, x[10], S43, 0xffeff47d ); // 55
			II( b, c, d, a,  x[1], S44, 0x85845dd1 ); // 56
			II( a, b, c, d,  x[8], S41, 0x6fa87e4f ); // 57
			II( d, a, b, c, x[15], S42, 0xfe2ce6e0 ); // 58
			II( c, d, a, b,  x[6], S43, 0xa3014314 ); // 59
			II( b, c, d, a, x[13], S44, 0x4e0811a1 ); // 60
			II( a, b, c, d,  x[4], S41, 0xf7537e82 ); // 61
			II( d, a, b, c, x[11], S42, 0xbd3af235 ); // 62
			II( c, d, a, b,  x[2], S43, 0x2ad7d2bb ); // 63
			II( b, c, d, a,  x[9], S44, 0xeb86d391 ); // 64
			m_state[0] += a;
			m_state[1] += b;
			m_state[2] += c;
			m_state[3] += d;
		}

		void Encode( const ulong* input, byte* output, size_t length ) { // 编码 ulong -> byte 假设长度为 4 的倍数
			for( size_t i = 0, j = 0; j < length; i++, j += 4 ) {
				output[j] = (byte)( input[i] & 0xff );
				output[j + 1] = (byte)( ( input[i] >> 8 ) & 0xff );
				output[j + 2] = (byte)( ( input[i] >> 16 ) & 0xff );
				output[j + 3] = (byte)( ( input[i] >> 24 ) & 0xff );
			}
		}

		void Decode( const byte* input, ulong* output, size_t length ) { // 解码 ulong -> byte 假设长度为 4 的倍数
			for( size_t i = 0, j = 0; j < length; i++, j += 4 ) {
				output[i] = ( (ulong)input[j] ) | ( ( (ulong)input[j + 1] ) << 8 ) | ( ( (ulong)input[j + 2] ) << 16 ) | ( ( (ulong)input[j + 3] ) << 24 );
			}
		}

		std::string BytesToHexString( const byte* input, size_t length ) { // 转换字节数组为16进制字符串
			std::string str;
			str.reserve( length << 1 );
			for( size_t i = 0; i < length; i++ ) {
				int32_t t = input[i];
				int32_t a = t / 16;
				int32_t b = t % 16;
				str.append( 1, m_hex[a] );
				str.append( 1, m_hex[b] );
			}
			return str;
		}

	private:
		ulong m_state[4]; // 状态标志
		ulong m_count[2]; // 位数，取 2^64 模，低字节序优先
		byte m_buffer[64]; // 输入缓存
		byte m_digest[16]; // 消息摘要
		bool m_finished; // 结束标志

	public:
		static const byte m_padding[64]; // 填充用于计算
		static const char m_hex[16];
		static const size_t m_buffer_size = 1024; // 文件读取缓存
	};

	const byte MD5::m_padding[64] = { 0x80 };
	const char MD5::m_hex[16] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f' };

} // namespace basicx

#endif // BASICX_COMMON_MD5_H
