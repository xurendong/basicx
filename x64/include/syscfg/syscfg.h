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

#ifndef BASICX_SYSCFG_SYSCFG_H
#define BASICX_SYSCFG_SYSCFG_H

#include <vector>
#include <stdint.h> // int32_t, int64_t

#include <common/compile.h>

namespace basicx {

#pragma pack( push )
#pragma pack( 1 )

	struct CfgServer
	{
		int32_t m_work;
		int32_t m_port;
		std::string m_type;
	};

	struct CfgClient
	{
		int32_t m_work;
		std::string m_address;
		int32_t m_port;
		std::string m_type;
	};

	struct CfgPlugin
	{
		int32_t m_work;
		std::string m_name;
	};

	struct CfgBasic // 目前未作初始化赋值，使用时请小心
	{
		int32_t m_property_cs;
		int32_t m_work_thread;
		int32_t m_data_length;
		int32_t m_con_time_out;
		int32_t m_heart_check;
		int32_t m_reconnect_c;
		int32_t m_debug_infos;
		int32_t m_statistics;
		int32_t m_con_max_server;
		int32_t m_con_max_client;
		std::vector<CfgServer> m_vec_server;
		std::vector<CfgClient> m_vec_client;

		int32_t m_work_thread_server;
		int32_t m_data_length_server;
		int32_t m_con_time_out_server;
		int32_t m_heart_check_server;
		int32_t m_debug_infos_server;
		int32_t m_max_msg_cache_server;
		int32_t m_con_max_server_server;
		std::vector<CfgServer> m_vec_server_server;

		int32_t m_work_thread_client;
		int32_t m_data_length_client;
		int32_t m_con_time_out_client;
		int32_t m_heart_check_client;
		int32_t m_debug_infos_client;
		int32_t m_max_msg_cache_client;
		int32_t m_con_max_client_client;
		std::vector<CfgClient> m_vec_client_client;

		std::vector<CfgPlugin> m_vec_plugin;
	};

#pragma pack( pop )

	class SysCfg_P;

	class BASICX_SYSCFG_EXPIMP SysCfg_S
	{
	public:
		SysCfg_S();
		~SysCfg_S();

	public:
		static SysCfg_S* GetInstance();

	public:
		void SetGlobalPath( std::string basic_file );
		std::string GetName_AppFull();
		std::string GetPath_AppExec();
		std::string GetPath_AppFolder();
		std::string GetPath_CfgFolder();
		std::string GetPath_PluFolder();
		std::string GetPath_ExtFolder();
		std::string GetPath_CfgBasic();

		CfgBasic* GetCfgBasic();
		bool ReadCfgBasic( std::string file_path );
		bool IsHoliday();
		bool IsWeekend();

	private:
		SysCfg_P* m_syscfg_p;
		static SysCfg_S* m_instance;
	};

} // namespace basicx

#endif // BASICX_SYSCFG_SYSCFG_H
