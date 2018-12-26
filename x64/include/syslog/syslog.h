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

#ifndef BASICX_SYSLOG_SYSLOG_H
#define BASICX_SYSLOG_SYSLOG_H

#include <stdint.h> // int32_t, int64_t

#include <common/compile.h>

#define DEF_SYSLOG_FSBM_FULL _IOFBF
#define DEF_SYSLOG_FSBM_LINE _IOLBF
#define DEF_SYSLOG_FSBM_NONE _IONBF

namespace basicx {

	class SysLog_P;

	enum BASICX_SYSLOG_EXPIMP syslog_level {
		n_debug = '0', n_info = '1', n_hint = '2', n_warn = '3', n_error = '4', n_fatal = '5',
		c_debug = 'D', c_info = 'I', c_hint = 'H', c_warn = 'W', c_error = 'E', c_fatal = 'F',
	};

	class BASICX_SYSLOG_EXPIMP SysLog_K // kernel
	{
	private:
		SysLog_K() {};
		
	public:
		SysLog_K( std::string log_name );
		~SysLog_K();

	private:
		SysLog_P * m_syslog_p;
	};

	class BASICX_SYSLOG_EXPIMP SysLog_D // dynamic
	{
	private:
		SysLog_D() {};
		
	public:
		SysLog_D( std::string log_name );
		~SysLog_D();

	public:
		void SetThreadSafe( bool thread_safe ); // Ĭ�� true
		void SetLocalCache( bool local_cache ); // Ĭ�� true
		void SetActiveFlush( bool active_flush ); // Ĭ�� false
		void SetActiveSync( bool active_sync ); // Ĭ�� false // �迪�� active_flush ����Ч
		void SetWorkThreads( size_t work_threads ); // Ĭ�� 1
		void SetInitCapacity( uint32_t init_capacity ); // Ĭ�� 8192
		void SetFileStreamBuffer( int32_t mode, size_t size = 0 ); // ��̬���� MySQL��MariaDB ʱ��Ҫ��Ϊ �޻��� ��Ȼд���ļ�����־�ᱻ����
		void InitSysLog( std::string app_name, std::string app_version, std::string app_company, std::string app_copyright ); // ���úò������ٵ���
		void PrintSysInfo();
		void WriteSysInfo();
		void ClearScreen( short row, short col, bool print_head = false, int32_t wait = 0 ); // �ȴ�������
		// 0������(debug)��1����Ϣ(info)��2����ʾ(hint)��3������(warn)��4������(error)��5������(fatal)
		void LogPrint( syslog_level log_level, std::string& log_cate, std::string& log_info, bool log_move = false );
		void LogWrite( syslog_level log_level, std::string& log_cate, std::string& log_info, bool log_move = false );

	private:
		SysLog_P * m_syslog_p;
	};

	class BASICX_SYSLOG_EXPIMP SysLog_S // static
	{
	private:
		SysLog_S() {};
		
	public:
		SysLog_S( std::string log_name );
		~SysLog_S();

	public:
		static SysLog_S* GetInstance();

	public:
		void SetThreadSafe( bool thread_safe ); // Ĭ�� true
		void SetLocalCache( bool local_cache ); // Ĭ�� true
		void SetActiveFlush( bool active_flush ); // Ĭ�� false
		void SetActiveSync( bool active_sync ); // Ĭ�� false // �迪�� active_flush ����Ч
		void SetWorkThreads( size_t work_threads ); // Ĭ�� 1
		void SetInitCapacity( uint32_t init_capacity ); // Ĭ�� 8192
		void SetFileStreamBuffer( int32_t mode, size_t size = 0 ); // ��̬���� MySQL��MariaDB ʱ��Ҫ��Ϊ �޻��� ��Ȼд���ļ�����־�ᱻ����
		void InitSysLog( std::string app_name, std::string app_version, std::string app_company, std::string app_copyright ); // ���úò������ٵ���
		void PrintSysInfo();
		void WriteSysInfo();
		void ClearScreen( short row, short col, bool print_head = false, int32_t wait = 0 ); // �ȴ�������
		// 0������(debug)��1����Ϣ(info)��2����ʾ(hint)��3������(warn)��4������(error)��5������(fatal)
		void LogPrint( syslog_level log_level, std::string& log_cate, std::string& log_info, bool log_move = false );
		void LogWrite( syslog_level log_level, std::string& log_cate, std::string& log_info, bool log_move = false );

	private:
		SysLog_P* m_syslog_p;
		static SysLog_S* m_instance;
	};

} // namespace basicx

#endif // BASICX_SYSLOG_SYSLOG_H
