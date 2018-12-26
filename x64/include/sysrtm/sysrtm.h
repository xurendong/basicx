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

#ifndef BASICX_SYSRTM_SYSRTM_H
#define BASICX_SYSRTM_SYSRTM_H

#include <common/compile.h>
#include <syslog/syslog.h>
#include <syscfg/syscfg.h>

namespace basicx {

	class SysRtm_P;

	class BASICX_SYSRTM_EXPIMP SysRtm_S
	{
	public:
		SysRtm_S();
		~SysRtm_S();

	public:
		static SysRtm_S* GetInstance();

	public:
		void StartNetServer();
		// 0：调试(debug)，1：信息(info)，2：提示(hint)，3：警告(warn)，4：错误(error)，5：致命(fatal)
		void LogTrans( syslog_level log_level, std::string& log_cate, std::string& log_info );

	private:
		SysRtm_P* m_sysrtm_p;
		static SysRtm_S* m_instance;
	};

} // namespace basicx

#endif // BASICX_SYSRTM_SYSRTM_H
