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

#ifndef BASICX_COMMON_SYSDEF_H
#define BASICX_COMMON_SYSDEF_H

namespace basicx {

#ifdef _WIN32
    //#include <SDKDDKVer.h>
    //#define NOMINMAX // 避免 common/date.h 的 min()、max() 冲突
    #define WIN32_LEAN_AND_MEAN // 从 Windows 头文件中排除极少使用的信息
    #define __OS_WINDOWS__
    #ifdef _WIN64
        #define __OS_WINDOWS_64__
    #else
        #define __OS_WINDOWS_32__
    #endif
#elif __linux__
    #define __OS_LINUX__
#elif __APPLE__
    #define __OS_APPLE__
    #include "TargetConditionals.h"
    #if TARGET_IPHONE_SIMULATOR
        #define __OS_APPLE_IOS_SIMULATOR__
    #elif TARGET_OS_IPHONE
        #define __OS_APPLE_IOS_DEVICE__
    #elif TARGET_OS_MAC
        #define __OS_APPLE_OTHER_MAC_OS__
    #else
        #error "Unknown Apple Platform"
    #endif
#elif __ANDROID__
    #define __OS_ANDROID__
#elif __unix__ // 要在 windows、linux、apple、android 之后
    #define __OS_UNIX__
#elif defined(_POSIX_VERSION)
    #define __OS_POSIX__
#else
    #error "Unknown Platform"
#endif

} // namespace basicx

#endif // BASICX_COMMON_SYSDEF_H
