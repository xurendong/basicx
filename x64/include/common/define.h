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

#ifndef BASICX_COMMON_DEFINE_H
#define BASICX_COMMON_DEFINE_H

namespace basicx {

#define DEF_APP_NAME "BasicX" // 系统英文名称
#define DEF_APP_NAME_CN "系 统 基 础 模 块" // 系统中文名称
#define DEF_APP_VERSION "V0.5.5-Beta Build 20180930" // 系统版本号
#define DEF_APP_DEVELOPER "Developed by the X-Lab." // 开发者声明
#define DEF_APP_COMPANY "X-Lab (Shanghai) Co., Ltd." // 公司声明
#define DEF_APP_COPYRIGHT "Copyright 2018-2018 X-Lab All Rights Reserved." // 版权声明
#define DEF_APP_HOMEURL "http://www.xlab.com" // 主页链接

// 自定义消息 #define WM_USER 0x0400
#define WM_MY_NEWCONNECT_LOCAL            0x0400 + 40 // 网络通信模块收到新的从客户端连接
#define WM_MY_NEWCONNECT_REMOTE           0x0400 + 41 // 网络通信模块发起新的向服务端连接
#define WM_MY_DISCONNECT_LOCAL            0x0400 + 42 // 网络通信模块收到客户端断开连接
#define WM_MY_DISCONNECT_REMOTE           0x0400 + 43 // 网络通信模块收到服务端断开连接
#define WM_MY_CLOSECONNECT_SERVER         0x0400 + 44 // 网络通信模块服务端主动关闭连接
#define WM_MY_CLOSECONNECT_CLIENT         0x0400 + 45 // 网络通信模块客户端主动关闭连接

// 网络数据包类型定义
#define NW_MSG_ATOM_TYPE_MIN 0 // 网络通信 元操作 类型起始
#define NW_MSG_TYPE_HEART_CHECK           NW_MSG_ATOM_TYPE_MIN + 0 // 连接心跳检测消息
#define NW_MSG_ATOM_TYPE_MAX 7 // 网络通信 元操作 类型终止

#define NW_MSG_USER_TYPE_MIN 8 // 网络通信 自定义 类型起始
#define NW_MSG_TYPE_USER_DATA             NW_MSG_USER_TYPE_MIN + 0 // 用户数据处理消息
#define NW_MSG_USER_TYPE_MAX 15 // 网络通信 自定义 类型终止

// 网络数据包编码定义
#define NW_MSG_CODE_TYPE_MIN 0 // 网络通信 编码 类型起始
#define NW_MSG_CODE_NONE                  NW_MSG_CODE_TYPE_MIN + 0 // 适用于元操作
#define NW_MSG_CODE_STRING                NW_MSG_CODE_TYPE_MIN + 1 // 直接字符串
#define NW_MSG_CODE_JSON                  NW_MSG_CODE_TYPE_MIN + 2 // Json格式
#define NW_MSG_CODE_BASE64                NW_MSG_CODE_TYPE_MIN + 3 // Base64格式
#define NW_MSG_CODE_PROTOBUF              NW_MSG_CODE_TYPE_MIN + 4 // ProtoBuf格式
#define NW_MSG_CODE_ZLIB                  NW_MSG_CODE_TYPE_MIN + 5 // ZLib格式
#define NW_MSG_CODE_MSGPACK               NW_MSG_CODE_TYPE_MIN + 6 // MsgPack格式
#define NW_MSG_CODE_TYPE_MAX 15 // 网络通信 编码 类型终止

} // namespace basicx

#endif // BASICX_COMMON_DEFINE_H
