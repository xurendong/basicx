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

#ifndef BASICX_COMMON_WINVER_H
#define BASICX_COMMON_WINVER_H

#include <string>

#include "sysdef.h"

#ifdef __OS_WINDOWS__
#include <windows.h>
#endif

#pragma warning(disable: 4996) // GetVersionExW was declared deprecated

namespace basicx {

#ifdef __OS_WINDOWS__
	class WinVer
	{
	public:
		bool m_is_win_nt;
		bool m_is_win_nt3;
		bool m_is_win_nt4;
		bool m_is_win_nt5;
		bool m_is_win_nt6;
		bool m_is_win_xp;
		bool m_is_win_home_server;
		bool m_is_win_media_center;
		bool m_is_win_vista;
		bool m_is_win_7;
		bool m_is_win_8;
		bool m_is_win_2000;
		bool m_is_win_2003;
		bool m_is_win_2008;
		bool m_is_win_server;
		bool m_is_win_9x;
		bool m_is_win_95;
		bool m_is_win_98;
		bool m_is_win_98_me;
		bool m_is_win_98_se;
		bool m_is_win_32s;
		bool m_is_win_64bit;

	protected:
		std::string m_version;

	public:
		WinVer()
			: m_is_win_nt( false )
			, m_is_win_nt3( false )
			, m_is_win_nt4( false )
			, m_is_win_nt5( false )
			, m_is_win_nt6( false )
			, m_is_win_xp( false )
			, m_is_win_home_server( false )
			, m_is_win_media_center( false )
			, m_is_win_vista( false )
			, m_is_win_7( false )
			, m_is_win_8( false )
			, m_is_win_2000( false )
			, m_is_win_2003( false )
			, m_is_win_2008( false )
			, m_is_win_server( false )
			, m_is_win_9x( false )
			, m_is_win_95( false )
			, m_is_win_98( false )
			, m_is_win_98_me( false )
			, m_is_win_98_se( false )
			, m_is_win_32s( false )
			, m_is_win_64bit( false )
			, m_version( "" ) {
		}

		~WinVer() {
		}

	public:
		std::string GetVersion() {
			OSVERSIONINFO version_info;
			version_info.dwOSVersionInfoSize = sizeof( OSVERSIONINFO );
			GetVersionEx( &version_info );
			if( version_info.dwMajorVersion >= 4 && VER_PLATFORM_WIN32_NT == version_info.dwPlatformId ) {
				return GetVersionInfo_WinEx();
			}
			else {
				return GetVersionInfo_Win();
			}
		}

		std::string GetVersionInfo_Win() {
			m_version = "";
			OSVERSIONINFO os_info;
			os_info.dwOSVersionInfoSize = sizeof( OSVERSIONINFOEX );
			int32_t result = GetVersionEx( &os_info );
			if( true ) {
				os_info.dwBuildNumber = LOWORD( os_info.dwBuildNumber );
				switch( os_info.dwPlatformId ) {
				case VER_PLATFORM_WIN32_WINDOWS:
					m_is_win_9x = true;
					switch( os_info.dwMinorVersion ) {
					case 0:
						m_is_win_95 = true;
						switch( os_info.dwBuildNumber ) {
						case 950:
							m_version = "Windows 95";
							break;
						case 111:
							m_version = "Windows 95 SR2.5";
							break;
						default:
							m_version = "Windows 95 SR2";
							break;
						}
						break;
					case 3:
						m_is_win_95 = true;
						m_version = "Windows 95 SR2.x";
						break;
					case 10:
						if( 2222 == os_info.dwBuildNumber ) {
							m_is_win_98_se = true;
							m_version = "Windows 98 Second Edition";
						}
						else {
							m_is_win_98 = true;
							m_version = "Windows 98";
						}
						break;
					case 90:
						m_is_win_98_me = true;
						m_version = "Windows Me (Millenium)";
						break;
					default:
						char temp[10] = { 0 };
						m_version = "Windows v";
						_itoa_s( os_info.dwMajorVersion, temp, sizeof( temp ), 10 );
						m_version.append( temp );
						m_version.append( "." );
						_itoa_s( os_info.dwMinorVersion, temp, sizeof( temp ), 10 );
						m_version.append( temp );
						m_version.append( "." );
						_itoa_s( os_info.dwBuildNumber, temp, sizeof( temp ), 10 );
						m_version.append( temp );
						break;
					}
					break;
				case VER_PLATFORM_WIN32_NT:
					m_is_win_nt = true;
					switch( os_info.dwMajorVersion ) {
					case 3:
						m_is_win_nt3 = true;
						switch( os_info.dwMinorVersion ) {
						case 0:
							m_version = "Windows NT 3";
							break;
						case 1:
							m_version = "Windows NT 3.1";
							break;
						case 51:
							m_version = "Windows NT 3.51";
							break;
						default:
							m_version = "Windows NT";
							break;
						}
						break;
					case 4:
						m_is_win_nt4 = true;
						m_version = "Windows NT 4.0";
						break;
					case 5:
						break;
					default:
						char temp[10];
						m_version = "Windows NT v";
						_itoa_s( os_info.dwMajorVersion, temp, sizeof( temp ), 10 );
						m_version.append( temp );
						m_version.append( "." );
						_itoa_s( os_info.dwMinorVersion, temp, sizeof( temp ), 10 );
						m_version.append( temp );
						m_version.append( "." );
						_itoa_s( os_info.dwBuildNumber, temp, sizeof( temp ), 10 );
						m_version.append( temp );
						break;
					}
					break;
				case VER_PLATFORM_WIN32s:
					m_is_win_32s = true;
					m_version = "Win32s";
					break;
				case 3:
					break;
				default:
					m_version = "ERROE";
					break;
				}
			}
			return m_version;
		}

		std::string GetVersionInfo_WinEx() {
			m_version = "";
			SYSTEM_INFO sys_info;
			OSVERSIONINFOEX os_info;
			os_info.dwOSVersionInfoSize = sizeof( OSVERSIONINFOEX );
			int32_t result = GetVersionEx( (LPOSVERSIONINFO)&os_info );
			if( true ) {
				m_is_win_nt = true;
				switch( os_info.dwMajorVersion ) {
				case 6:
					m_is_win_nt6 = true;
					switch( os_info.dwMinorVersion ) {
					case 0:
						if( VER_NT_WORKSTATION == os_info.wProductType ) {
							m_is_win_vista = true;
							m_version = "Windows Vista";
						}
						else {
							m_is_win_2008 = true;
							m_version = "Windows Server 2008";
						}
						break;
					case 1: {
						m_is_win_7 = true;
						if( 6801 == os_info.dwBuildNumber ) {
							m_version = "Windows 7 preBeta build M3 PDC 2008";
						}
						else {
							m_version = "Windows 7";
						}
					}
					break;
					case 2:
						m_is_win_8 = true;
						if( 7867 == os_info.dwBuildNumber ) {
							m_version = "Windows 8 Milestone1";
						}
						else if( os_info.dwBuildNumber <= 7947 && os_info.dwBuildNumber >= 7910 ) {
							m_version = "Windows 8 Milestone2";
						}
						else if( 7955 == os_info.dwBuildNumber ) {
							m_version = "Windows 8 Milestone3";
						}
						else {
							m_version = "Windows 8";
						}
						break;
					default:
						char temp[10];
						m_version = "Windows NT v";
						_itoa_s( os_info.dwMajorVersion, temp, sizeof( temp ), 10 );
						m_version.append( temp );
						//m_version.append("Windows NT v%d", os_info.dwMajorVersion);
						break;
					}
					m_version += " " + GetVersionInfo_64Bit();
					// 非 Win NT6 的系统加载插件时会报 无法定位入口点 GetProductInfo 于 kernel32.dll 上
					//unsigned long ret_prod_type;
					//GetProductInfo( os_info.dwMajorVersion, os_info.dwMinorVersion, os_info.wServicePackMajor, os_info.wServicePackMinor, (PDWORD)&ret_prod_type );
					//switch( ret_prod_type ) {
					//case PRODUCT_BUSINESS:
					//	m_version += " Business";
					//	break;
					//case PRODUCT_BUSINESS_N:
					//	m_version += " Business N";
					//	break;
					//case PRODUCT_CLUSTER_SERVER:
					//	m_version += " HPC";
					//	break;
					//case PRODUCT_DATACENTER_SERVER:
					//	m_version += " Datacenter";
					//	break;
					//case PRODUCT_DATACENTER_SERVER_CORE:
					//	m_version += " Datacenter (core installation)";
					//	break;
					//case PRODUCT_DATACENTER_SERVER_CORE_V:
					//	m_version += " Datacenter sans Hyper-V(core installation)";
					//	break;
					//case PRODUCT_DATACENTER_SERVER_V:
					//	m_version += " Datacenter sans Hyper-V";
					//	break;
					//case PRODUCT_ENTERPRISE:
					//	m_version += " Enterprise";
					//	break;
					//case PRODUCT_ENTERPRISE_N:
					//	m_version += " Enterprise N";
					//	break;
					//case PRODUCT_ENTERPRISE_SERVER:
					//	m_version += " Server Enterprise";
					//	break;
					//case PRODUCT_ENTERPRISE_SERVER_CORE:
					//	m_version += " Server Enterprise (core installation)";
					//	break;
					//case PRODUCT_ENTERPRISE_SERVER_CORE_V:
					//	m_version += " Server Enterprise sans Hyper-V(core installation)";
					//	break;
					//case PRODUCT_ENTERPRISE_SERVER_IA64:
					//	m_version += " Enterprise pour Itanium";
					//	break;
					//case PRODUCT_ENTERPRISE_SERVER_V:
					//	m_version += " Server Enterprise sans Hyper-V";
					//	break;
					//case PRODUCT_HOME_BASIC:
					//	m_version += " Home Basic";
					//	break;
					//case PRODUCT_HOME_BASIC_N:
					//	m_version += " Home Basic N";
					//	break;
					//case PRODUCT_HOME_PREMIUM:
					//	m_version += " Home Premium";
					//	break;
					//case PRODUCT_HOME_PREMIUM_N:
					//	m_version += " Home Premium N";
					//	break;
					//case PRODUCT_HYPERV:
					//	m_version += " Microsoft Hyper-V Server";
					//	break;
					//case PRODUCT_MEDIUMBUSINESS_SERVER_MANAGEMENT:
					//	m_version += " Essential Business Server Management Server";
					//	break;
					//case PRODUCT_MEDIUMBUSINESS_SERVER_MESSAGING:
					//	m_version += " Essential Business Server Messaging Server";
					//	break;
					//case PRODUCT_MEDIUMBUSINESS_SERVER_SECURITY:
					//	m_version += " Essential Business Server Security Server";
					//	break;
					//case PRODUCT_SERVER_FOR_SMALLBUSINESS:
					//	m_version += " Windows Essential Server Solutions";
					//	break;
					//case PRODUCT_SERVER_FOR_SMALLBUSINESS_V:
					//	m_version += " Windows Essential Server Solutions sans Hyper-V";
					//	break;
					//case PRODUCT_SMALLBUSINESS_SERVER:
					//	m_version += " Small Business Server";
					//	break;
					//case PRODUCT_STANDARD_SERVER:
					//	m_version += " Standard";
					//	break;
					//case PRODUCT_STANDARD_SERVER_CORE:
					//	m_version += " Standard (core installation)";
					//	break;
					//case PRODUCT_STANDARD_SERVER_CORE_V:
					//	m_version += " Standard sans Hyper-V(core installation)";
					//	break;
					//case PRODUCT_STANDARD_SERVER_V:
					//	m_version += " Standard sans Hyper-V";
					//	break;
					//case PRODUCT_STARTER:
					//	m_version += " Starter";
					//	break;
					//case PRODUCT_STORAGE_ENTERPRISE_SERVER:
					//	m_version += " Storage Server Enterprise";
					//	break;
					//case PRODUCT_STORAGE_EXPRESS_SERVER:
					//	m_version += " Storage Server Express";
					//	break;
					//case PRODUCT_STORAGE_STANDARD_SERVER:
					//	m_version += " Storage Server Standard";
					//	break;
					//case PRODUCT_STORAGE_WORKGROUP_SERVER:
					//	m_version += " Storage Server Workgroup";
					//	break;
					//case PRODUCT_ULTIMATE:
					//	m_version += " Ultimate";
					//	break;
					//case PRODUCT_ULTIMATE_N:
					//	m_version += " Ultimate N";
					//	break;
					//case PRODUCT_WEB_SERVER:
					//	m_version += " Web Server";
					//	break;
					//case PRODUCT_WEB_SERVER_CORE:
					//	m_version += " Web Server(core installation)";
					//	break;
					//case PRODUCT_UNDEFINED:
					//	m_version += " Produit inconnu";
					//	break;
					//}

					// 目前不需要
					//m_version.append( " (" );
					//m_version.append( GetVersionInfo_MediaCenter() );
					//m_version.append( ")" );
					break;
				case 5:
					m_is_win_nt5 = true;
					switch( os_info.dwMinorVersion ) {
					case 0:
						m_is_win_2000 = true;
						m_version = "Windows 2000";
						if( VER_NT_WORKSTATION == os_info.wProductType ) {
							if( os_info.wSuiteMask && VER_SUITE_PERSONAL == os_info.wSuiteMask ) {
								m_version += " Home Edition";
							}
							else {
								m_version += " Professionel";
							}
						}
						else {
							m_is_win_server = true;
							if( os_info.wSuiteMask && VER_SUITE_DATACENTER == os_info.wSuiteMask ) {
								m_version += " DataCenter Server ";
							}
							else if( os_info.wSuiteMask && VER_SUITE_ENTERPRISE == os_info.wSuiteMask ) {
								m_version += " Advanced Server ";
							}
							else {
								m_version += " Server ";
							}
						}
						break;
					case 1:
						m_is_win_xp = true;
						m_version = "Windows XP";
						if( os_info.wSuiteMask && VER_SUITE_PERSONAL == os_info.wSuiteMask )
							m_version += " Home Edition";
						else
							m_version += " Professionel";
						break;
					case 2:
						if( GetSystemMetrics( SM_SERVERR2 ) != 0 ) {
							m_is_win_2003 = true;
							if( VER_SUITE_STORAGE_SERVER == os_info.wProductType ) {
								m_version = "Windows Storage Server 2003 R2";
							}
							else {
								m_version = "Windows Server 2003 R2";
							}
						}
						else if( VER_SUITE_WH_SERVER == os_info.wProductType ) {
							m_is_win_home_server = true;
							m_version = "Windows Home Server";
						}
						else if( VER_SUITE_STORAGE_SERVER == os_info.wProductType ) {
							m_is_win_2003 = true;
							m_version = "Windows Storage Server 2003";
						}
						else if( VER_NT_WORKSTATION == os_info.wProductType && m_is_win_64bit ) {
							m_is_win_xp = true;
							m_version = "Microsoft Windows XP Professional x64 Edition";
						}
						else {
							m_is_win_2003 = true;
							m_version = "Windows Server 2003";
						}
						if( os_info.wProductType != VER_NT_WORKSTATION ) {
							GetNativeSystemInfo( &sys_info );
							if( PROCESSOR_ARCHITECTURE_IA64 == sys_info.wProcessorArchitecture ) {
								if( os_info.wSuiteMask && VER_SUITE_DATACENTER == os_info.wSuiteMask ) {
									m_version += " Datacenter Edition pour Itanium";
								}
								else if( os_info.wSuiteMask && VER_SUITE_ENTERPRISE == os_info.wSuiteMask ) {
									m_version += " Enterprise Edition pour Itanium";
								}
							}
							else if( PROCESSOR_ARCHITECTURE_AMD64 == sys_info.wProcessorArchitecture ) {
								if( os_info.wSuiteMask && VER_SUITE_DATACENTER == os_info.wSuiteMask ) {
									m_version += " Datacenter x64 Edition";
								}
								else if( os_info.wSuiteMask && VER_SUITE_ENTERPRISE == os_info.wSuiteMask ) {
									m_version += " Enterprise x64 Edition";
								}
								else {
									m_version += " Standard x64 Edition";
								}
							}
							else {
								if( os_info.wSuiteMask && VER_SUITE_DATACENTER == os_info.wSuiteMask ) {
									m_version += " Datacenter Edition";
								}
								else if( os_info.wSuiteMask && VER_SUITE_ENTERPRISE == os_info.wSuiteMask ) {
									m_version += " Enterprise Edition";
								}
								else if( os_info.wSuiteMask && VER_SUITE_COMPUTE_SERVER == os_info.wSuiteMask ) {
									m_version += " Compute Cluster Edition";
								}
								else if( os_info.wSuiteMask && VER_SUITE_BLADE == os_info.wSuiteMask ) {
									m_version += " Web Edition";
								}
								else {
									m_version += " Standard Edition";
								}
							}
						}
						break;
					default:
						char temp[10] = { 0 };
						m_version = "Windows NT v";
						_itoa_s( os_info.dwMajorVersion, temp, sizeof( temp ), 10 );
						m_version.append( temp );
						m_version.append( "." );
						_itoa_s( os_info.dwMinorVersion, temp, sizeof( temp ), 10 );
						m_version.append( temp );
						//m_version.append("Windows NT v%d.%d",os_info.dwMajorVersion,os_info.dwMinorVersion);
						break;
					}
					m_version.append( " " );
					m_version.append( GetVersionInfo_64Bit() );
					m_version.append( " " );
					m_version.append( GetVersionInfo_MediaCenter() );

					break;
				default:
					char temp[10];
					m_version = "Windows NT v";
					_itoa_s( os_info.dwMajorVersion, temp, sizeof( temp ), 10 );
					m_version.append( temp );
					m_version.append( "." );
					_itoa_s( os_info.dwMinorVersion, temp, sizeof( temp ), 10 );
					m_version.append( temp );
					m_version.append( "." );
					_itoa_s( os_info.dwBuildNumber, temp, sizeof( temp ), 10 );
					m_version.append( temp );
					if( 4 == os_info.dwMajorVersion && VER_NT_WORKSTATION == os_info.wProductType ) {
						m_version += " Workstation";
					}
					break;
				}
				if( os_info.wServicePackMajor > 0 ) {
					char temp[10];
					m_version.append( " Service Pack " );
					_itoa_s( os_info.wServicePackMajor, temp, sizeof( temp ), 10 );
					m_version.append( temp );
					if( os_info.wServicePackMinor > 0 ) {
						_itoa_s( os_info.wServicePackMinor, temp, sizeof( temp ), 10 );
						m_version.append( temp );
					}
				}
			}
			return m_version;
		}

		std::string GetVersionInfo_64Bit() {
			SYSTEM_INFO sys_info;
			std::string version = "";
			GetNativeSystemInfo( &sys_info );
			if( PROCESSOR_ARCHITECTURE_AMD64 == sys_info.wProcessorArchitecture ) {
				version = "64bits";
				m_is_win_64bit = true;
			}
			else {
				version = "32bits";
				m_is_win_64bit = false;
			}
			return version;
		}

		std::string GetVersionInfo_MediaCenter() {
			std::string version = "";
			if( GetSystemMetrics( SM_MEDIACENTER ) != 0 ) {
				m_is_win_media_center = true;
				version = "Media Center";
			}
			return version;
		}
	};
#endif

} // namespace basicx

#endif // BASICX_COMMON_WINVER_H
