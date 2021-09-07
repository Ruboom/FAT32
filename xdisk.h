/**
 *!
 * \file        xdisk.h
 * \brief       
 * \version     1.0
 * \date        2021/09/07
 * \author      LiBoran
 * Last modified by LiBoran 2021/09/07
 * Copyright (c) 2021 by LiBoran. All Rights Reserved.
 */
#ifndef __XDISK_H__
#define __XDISK_H__

/*Includes ----------------------------------------------*/
#include "xtypes.h"
   
/**\defgroup xdisk_Exported_TypesDefinitions
 * \{
 */

struct _xdisk_t;

//磁盘操作接口结构
typedef struct _xdisk_driver_t
{
	xfat_err_t(*open)(struct _xdisk_t* disk, void* init_data);											//打开磁盘
	xfat_err_t(*close)(struct _xdisk_t* disk);															//关闭磁盘
	xfat_err_t(*read_sector)(struct _xdisk_t* disk, u8_t* buffer, u32_t start_sector, u32_t count);		//读取磁盘块
	xfat_err_t(*write_sector)(struct _xdisk_t* disk, u8_t* buffer, u32_t start_sector, u32_t count);	//写入磁盘块
}xdisk_driver_t;

//用于描述磁盘结构
typedef struct _xdisk_t
{
	const char* name;		//磁盘名称
	u32_t sector_size;		//每个磁盘块/扇区大小
	u32_t total_sector;		//总共有多少块/扇区
	xdisk_driver_t* driver;	//磁盘操作接口
	void* data;
}xdisk_t;
   
/**
 * \}
 */
   
/**\defgroup xdisk_Exported_Defines
 * \{
 */
   
#define XDISK_CLASS(x) xdisk_ ## x

/**
 * \}
 */
   
/**\defgroup xdisk_Exported_Macros
 * \{
 */
   
/**
 * \}
 */
   
/**\defgroup xdisk_Exported_Variables
 * \{
 */
   
/**
 * \}
 */
   
/**\defgroup xdisk_Exported_Functions
 * \{
 */

xfat_err_t XDISK_CLASS(open)(xdisk_t* disk, const char* name, xdisk_driver_t* driver, void* init_data);
xfat_err_t XDISK_CLASS(close)(xdisk_t* disk);
xfat_err_t XDISK_CLASS(read_sector)(xdisk_t* disk, u8_t* buffer, u32_t start_sector, u32_t count);
xfat_err_t XDISK_CLASS(write_sector)(xdisk_t* disk, u8_t* buffer, u32_t start_sector, u32_t count);
   
/**
 * \}
 */
#endif // __XDISK_H__
/************************ (C) COPYRIGHT LiBoran *****END OF FILE****/

