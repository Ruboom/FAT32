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

//分区类型枚举
typedef enum _xfs_type_t
{
	FS_NOT_VALID = 0x00,		//无效分区值
	FS_FAT32 = 0x01,			//FAT32类型
	FS_EXTEND = 0x05,			//拓展分区
	FS_WIN95_FAT32_0 = 0x0C,
	FS_WIN95_FAT32_1 = 0x0B,
}xfs_type_t;

#pragma pack(1)

#define MBR_PRIMAR_PART_NR 4

//分区表字段结构
typedef struct _mbr_part_t
{
	u8_t boot_active;			//引导指示符
	u8_t start_header;			//磁盘起始地址
	u16_t start_sector : 6;		//开始扇区
	u16_t start_cylinder : 10;	//开始柱面
	u8_t system_id;				//分区类型
	u8_t end_header;			//磁盘结束地址
	u16_t end_sector : 6;		//结束扇区
	u16_t end_cylinder : 10;	//结束柱面
	u32_t relative_sectors;		//相对扇区数
	u32_t total_sectors;		//总扇区数
}mbr_part_t;

struct _xdisk_t;

//分区结构
typedef struct _mbr_t
{
	u8_t code[446];								//446个字节可执行代码
	mbr_part_t part_info[MBR_PRIMAR_PART_NR];	//64个字节磁盘分区表
	u8_t boot_sig[2];							//两个字节启动有效标志
}mbr_t;

#pragma pack()

//磁盘驱动接口结构
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
xfat_err_t XDISK_CLASS(get_part_count)(xdisk_t* disk, u32_t* count);
   
/**
 * \}
 */
#endif // __XDISK_H__
/************************ (C) COPYRIGHT LiBoran *****END OF FILE****/

