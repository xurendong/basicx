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

#ifndef BASICX_NETWORK_CLIENT_H
#define BASICX_NETWORK_CLIENT_H

#include <string>
#include <stdint.h>

#include <common/compile.h>

namespace basicx {

	#pragma pack( push )
	#pragma pack( 1 )

	struct NetClientCfg // 用于网络参数设置 // 成员变量均会被赋值
	{
		int32_t m_log_test;
		int32_t m_heart_check_time;
		size_t m_max_msg_cache_number;
		int32_t m_io_work_thread_number;
		int32_t m_client_connect_timeout; // 毫秒
		// 客户端参数
		size_t m_max_connect_total_c;
		size_t m_max_data_length_c;
	};

	struct NetClientInfo // 用于网络事件推送
	{
		int32_t m_info_type;
		std::string m_node_type;
		int32_t m_identity;
		std::string m_endpoint_l;
		std::string m_endpoint_r;

		NetClientInfo( int32_t info_type, std::string& node_type, int32_t identity, std::string& endpoint_l, std::string& endpoint_r );
	};

	struct NetClientData // 用于网络数据推送
	{
		std::string m_node_type;
		int32_t m_identity;
		int32_t m_code;
		std::string m_data;

		NetClientData( std::string& node_type, int32_t identity, int32_t code, std::string& data );
	};

	#pragma pack( pop )

	class BASICX_NETWORK_EXPIMP NetClient_X
	{
	public:
		NetClient_X();
		virtual ~NetClient_X();

		virtual void OnNetClientInfo( NetClientInfo& net_client_info ) = 0;
		virtual void OnNetClientData( NetClientData& net_client_data ) = 0;
	};

	struct ConnectInfo;

	class NetClient_P;

	class BASICX_NETWORK_EXPIMP NetClient
	{
	public:
		NetClient();
		~NetClient();

	public:
		void ComponentInstance( NetClient_X* net_client_x );

	public:
		void StartNetwork( NetClientCfg& config );
		bool IsNetworkStarted();
		bool IsConnectAvailable( ConnectInfo* connect_info );

	public:
		bool Client_CanAddConnect();
		bool Client_CanAddServer( std::string address_r, int32_t port_r ); // 只在限制远程一个地址一个端口只一个连接时检测
		bool Client_AddConnect( std::string address_r, int32_t port_r, std::string node_type_r );
		void Client_SetAutoReconnect( bool auto_reconnect );

		int32_t Client_SendDataAll( int32_t type, int32_t code, std::string& data );
		int32_t Client_SendData( ConnectInfo* connect_info, int32_t type, int32_t code, std::string& data );

		void Client_CloseAll();
		void Client_Close( ConnectInfo* connect_info );
		void Client_Close( int32_t identity );

		size_t Client_GetConnectCount();
		ConnectInfo* Client_GetConnect( int32_t identity );

	private:
		NetClient_P* m_net_client_p;
	};

} // namespace basicx

#endif // BASICX_NETWORK_CLIENT_H
