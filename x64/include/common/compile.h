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

#ifndef BASICX_COMMON_COMPILE_H
#define BASICX_COMMON_COMPILE_H

//---------- 基础组件 ----------//

#define BASICX_TIMERS_EXP
//#define BASICX_TIMERS_IMP

#define BASICX_SYSLOG_EXP
//#define BASICX_SYSLOG_IMP

#define BASICX_SYSCFG_EXP
//#define BASICX_SYSCFG_IMP

#define BASICX_SYSDBI_M_EXP
//#define BASICX_SYSDBI_M_IMP

#define BASICX_SYSDBI_S_EXP
//#define BASICX_SYSDBI_S_IMP

#define BASICX_NETWORK_EXP
//#define BASICX_NETWORK_IMP

#define BASICX_SYSRTM_EXP
//#define BASICX_SYSRTM_IMP

#define BASICX_PLUGINS_EXP
//#define BASICX_PLUGINS_IMP

#define BASICX_PLUGINS_X_EXP
//#define BASICX_PLUGINS_X_IMP

//---------- 设置结束 ----------//

#ifdef BASICX_TIMERS_EXP
    #define BASICX_TIMERS_EXPIMP __declspec(dllexport)
#endif

#ifdef BASICX_TIMERS_IMP
    #define BASICX_TIMERS_EXPIMP __declspec(dllimport)
#endif

//------------------------------//

#ifdef BASICX_SYSLOG_EXP
    #define BASICX_SYSLOG_EXPIMP __declspec(dllexport)
#endif

#ifdef BASICX_SYSLOG_IMP
    #define BASICX_SYSLOG_EXPIMP __declspec(dllimport)
#endif

//------------------------------//

#ifdef BASICX_SYSCFG_EXP
    #define BASICX_SYSCFG_EXPIMP __declspec(dllexport)
#endif

#ifdef BASICX_SYSCFG_IMP
    #define BASICX_SYSCFG_EXPIMP __declspec(dllimport)
#endif

//------------------------------//

#ifdef BASICX_SYSDBI_M_EXP
    #define BASICX_SYSDBI_M_EXPIMP __declspec(dllexport)
#endif

#ifdef BASICX_SYSDBI_M_IMP
    #define BASICX_SYSDBI_M_EXPIMP __declspec(dllimport)
#endif

//------------------------------//

#ifdef BASICX_SYSDBI_S_EXP
    #define BASICX_SYSDBI_S_EXPIMP __declspec(dllexport)
#endif

#ifdef BASICX_SYSDBI_S_IMP
    #define BASICX_SYSDBI_S_EXPIMP __declspec(dllimport)
#endif

//------------------------------//

#ifdef BASICX_NETWORK_EXP
    #define BASICX_NETWORK_EXPIMP __declspec(dllexport)
#endif

#ifdef BASICX_NETWORK_IMP
    #define BASICX_NETWORK_EXPIMP __declspec(dllimport)
#endif

//------------------------------//

#ifdef BASICX_SYSRTM_EXP
    #define BASICX_SYSRTM_EXPIMP __declspec(dllexport)
#endif

#ifdef BASICX_SYSRTM_IMP
    #define BASICX_SYSRTM_EXPIMP __declspec(dllimport)
#endif

//------------------------------//

#ifdef BASICX_PLUGINS_EXP
    #define BASICX_PLUGINS_EXPIMP __declspec(dllexport)
#endif

#ifdef BASICX_PLUGINS_IMP
    #define BASICX_PLUGINS_EXPIMP __declspec(dllimport)
#endif

//------------------------------//

#ifdef BASICX_PLUGINS_X_EXP
    #define BASICX_PLUGINS_X_EXPIMP __declspec(dllexport)
#endif

#ifdef BASICX_PLUGINS_X_IMP
    #define BASICX_PLUGINS_X_EXPIMP __declspec(dllimport)
#endif

//------------------------------//

#endif // BASICX_COMMON_COMPILE_H
