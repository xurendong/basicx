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

#ifndef BASICX_NETWORK_SOCK_CLIENT_H
#define BASICX_NETWORK_SOCK_CLIENT_H

#include <string>
#include <stdint.h>

#include <common/compile.h>

namespace basicx {

	class SockClient_P;

	class BASICX_NETWORK_EXPIMP SockClient
	{
	public:
		SockClient();
		~SockClient();

	public:
		int32_t Connect( std::string address, int32_t port, int32_t try_times, int32_t span_time = 1000 ); // try_times 为 0 时无限重连 // span_time 单位毫秒
		bool IsConnectValid();
		int32_t Read( void* buffer, int32_t length );
		int32_t Write( void* buffer, int32_t length );
		bool IsReadable( int32_t wait_time = 0 );
		bool IsWritable( int32_t wait_time = 0 );
		void Close();

	private:
		SockClient_P* m_sock_client_p;
	};

} // namespace basicx

#endif // BASICX_NETWORK_SOCK_CLIENT_H
