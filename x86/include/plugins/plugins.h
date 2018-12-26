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

#ifndef BASICX_PLUGINS_PLUGINS_H
#define BASICX_PLUGINS_PLUGINS_H

#include <string>
#include <stdint.h> // int32_t, int64_t

#include <common/compile.h>
//#include <mission/mission.h> //mission//

namespace basicx {

	class BASICX_PLUGINS_EXPIMP Plugins_X
	{
	private:
		Plugins_X();

	public:
		Plugins_X( std::string plugin_name );
		virtual ~Plugins_X();

	public:
		virtual bool Initialize() = 0;
		virtual bool InitializeExt() = 0;
		virtual bool StartPlugin() = 0;
		virtual bool IsPluginRun() = 0;
		virtual bool StopPlugin() = 0;
		virtual bool UninitializeExt() = 0;
		virtual bool Uninitialize() = 0;
		virtual bool AssignTask( int32_t task_id, int32_t identity, int32_t code, std::string& data ) = 0;
	};

	class Plugins_P;

	class BASICX_PLUGINS_EXPIMP Plugins //class Plugins : public Mission_X //mission//
	{
	public:
		Plugins();
		~Plugins();

	public:
		static Plugins* GetInstance();

	public:
		void StartPlugins();
		bool IsPluginsStarted();

	public:
		bool LoadAll( std::string folder );
		void StopAll();

		Plugins_X* GetPluginsX( const std::string& plugin_name ) const;
		void SetPluginsX( const std::string& plugin_name, Plugins_X* plugins_x );

		std::string GetPluginLocationByName( const std::string& plugin_name ) const;
		std::string GetPluginCfgFilePathByName( const std::string& plugin_name ) const;
		std::string GetPluginInfoFilePathByName( const std::string& plugin_name ) const;

	private:
		Plugins_P* m_plugins_p;
		static Plugins* m_instance;
	};

} // namespace basicx

#endif // BASICX_PLUGINS_PLUGINS_H
