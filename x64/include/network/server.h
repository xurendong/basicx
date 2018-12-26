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

#ifndef BASICX_NETWORK_SERVER_H
#define BASICX_NETWORK_SERVER_H

#include <string>
#include <stdint.h>

#include <common/compile.h>

namespace basicx {

	#pragma pack( push )
	#pragma pack( 1 )

	struct NetServerCfg // 用于网络参数设置 // 成员变量均会被赋值
	{
		int32_t m_log_test;
		int32_t m_heart_check_time;
		size_t m_max_msg_cache_number;
		int32_t m_io_work_thread_number;
		int32_t m_client_connect_timeout; // 毫秒
		// 服务端参数
		size_t m_max_connect_total_s;
		size_t m_max_data_length_s;
	};

	struct NetServerInfo // 用于网络事件推送
	{
		int32_t m_info_type;
		std::string m_node_type;
		int32_t m_identity;
		std::string m_endpoint_l;
		std::string m_endpoint_r;

		NetServerInfo( int32_t info_type, std::string& node_type, int32_t identity, std::string& endpoint_l, std::string& endpoint_r );
	};

	struct NetServerData // 用于网络数据推送
	{
		std::string m_node_type;
		int32_t m_identity;
		int32_t m_code;
		std::string m_data;

		NetServerData( std::string& node_type, int32_t identity, int32_t code, std::string& data );
	};

	#pragma pack( pop )

	class BASICX_NETWORK_EXPIMP NetServer_X
	{
	public:
		NetServer_X();
		virtual ~NetServer_X();

		virtual void OnNetServerInfo( NetServerInfo& net_client_info ) = 0;
		virtual void OnNetServerData( NetServerData& net_client_data ) = 0;
	};

	struct ConnectInfo;

	class NetServer_P;

	class BASICX_NETWORK_EXPIMP NetServer
	{
	public:
		NetServer();
		~NetServer();

	public:
		void ComponentInstance( NetServer_X* net_server_x );

	public:
		void StartNetwork( NetServerCfg& config );
		bool IsNetworkStarted();
		bool IsConnectAvailable( ConnectInfo* connect_info );

	public:
		bool Server_CanAddConnect();
		bool Server_CanAddListen( std::string address_l, int32_t port_l ); // 0.0.0.0
		bool Server_AddListen( std::string address_l, int32_t port_l, std::string node_type_l ); // 0.0.0.0

		int32_t Server_SendDataAll( int32_t type, int32_t code, std::string& data );
		int32_t Server_SendData( ConnectInfo* connect_info, int32_t type, int32_t code, std::string& data );

		void Server_CloseAll();
		void Server_Close( ConnectInfo* connect_info );
		void Server_Close( int32_t identity );

		size_t Server_GetConnectCount();
		ConnectInfo* Server_GetConnect( int32_t identity );

	private:
		NetServer_P* m_net_server_p;
	};

} // namespace basicx

#endif // BASICX_NETWORK_SERVER_H
