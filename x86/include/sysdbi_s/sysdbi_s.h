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

#ifndef BASICX_SYSDBI_S_SYSDBI_S_H
#define BASICX_SYSDBI_S_SYSDBI_S_H

#include <string>
#include <stdint.h>

#include <common/compile.h>

#import "C:\Program Files (x86)\Common Files\System\ado\msado20.tlb" named_guids rename("EOF", "adoEOF") // SQL Server

typedef ADODB::_Recordset*& Recordset_P_R;
typedef ADODB::_Connection*& Connection_P_R;

namespace basicx {

	class SysDBI_S_P;

	class BASICX_SYSDBI_S_EXPIMP SysDBI_S
	{
	public:
		SysDBI_S();
		~SysDBI_S();

	public:
		static SysDBI_S* GetInstance();

	public:
		int32_t Connect( Connection_P_R connection, Recordset_P_R recordset, std::string host_name, int32_t host_port, std::string user_name, std::string user_pass, std::string database );
		bool Query( Connection_P_R connection, Recordset_P_R recordset, std::string query );
		long GetCount( Recordset_P_R recordset );
		bool GetEOF( Recordset_P_R recordset );
		bool MoveNext( Recordset_P_R recordset );
		void Close( Recordset_P_R recordset );
		void Release( Connection_P_R connection, Recordset_P_R recordset );

	private:
		SysDBI_S_P* m_sysdbi_s_p;
		static SysDBI_S* m_instance;
	};

} // namespace basicx

#endif // BASICX_SYSDBI_S_SYSDBI_S_H
