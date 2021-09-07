/**
 *!
 * \file		driver.c
 * \brief       Drive interface Init
 * \version     1.0
 * \date        2021/09/07
 * \author      LiBoran
 *Last modified by LiBoran 2021/09/07
 *Copyright (c) 2021 by LiBoran. All Rights Reserved.
 */
   
/*Includes ----------------------------------------------*/
#include "xdisk.h"
#include "xfat.h"
#include <stdio.h>
   
/**\defgroup driver_Private_TypesDefinitions
 * \{
 */
   
/**
 * \}
 */
   
/**\defgroup driver_Private_Defines
 * \{
 */

#define XDISK_CLASS(x) xdisk_hw_ ## x
   
/**
 * \}
 */
   
/**\defgroup driver_Private_Macros
 * \{
 */
   
/**
 * \}
 */

/**\defgroup driver_Private_FunctionPrototypes
* \{
*/
static xfat_err_t XDISK_CLASS(open)(struct _xdisk_t* disk, void* init_data);
static xfat_err_t XDISK_CLASS(close)(struct _xdisk_t* disk);
static xfat_err_t XDISK_CLASS(read_sector)(struct _xdisk_t* disk, u8_t* buffer, u32_t start_sector, u32_t count);
static xfat_err_t XDISK_CLASS(write_sector)(struct _xdisk_t* disk, u8_t* buffer, u32_t start_sector, u32_t count);
/**
* \}
*/
   
/**\defgroup driver_Private_Variables
 * \{
 */

xdisk_driver_t vdisk_driver = {
	.open = xdisk_hw_open,
	.close = xdisk_hw_close,
	.read_sector = xdisk_hw_read_sector,
	.write_sector = xdisk_hw_write_sector
};
   
/**
 * \}
 */
   

   
/**\defgroup driver_Private_Functions
 * \{
 */

/**
 * \func         xdisk_hw_open
 * 
 * \brief        Open disk
 * 
 * \param        *disk: disk structure pointer
 *				 void* init_data: disk path
 * 
 * \retval       FS_ERR_OK = 0;
 *				 FS_ERR_IO = -1
 * \note         
 */
static xfat_err_t XDISK_CLASS(open)(struct _xdisk_t* disk, void* init_data)
{
	const char* path = (const char*)init_data;

	FILE* file = fopen(path, "rb+");
	if (file == NULL)
	{
		printf("open disk failed:%s\n", path);
		return FS_ERR_IO;
	}

	//将文件信息指针保存
	disk->data = file;
	//每个扇区大小为512个字节
	disk->sector_size = 512;
	
	//把位置指针移动到文件末尾处
	fseek(file, 0, SEEK_END);
	//将文件末尾地址除以文件块大小得到有多少个文件块
	disk->total_sector = ftell(file) / disk->sector_size;
	return FS_ERR_OK;
}

/**
 * \func         xdisk_hw_close
 * 
 * \brief		 close the disk
 * 
 * \param		 *disk: disk structure pointer
 * 
 * \retval		 FS_ERR_OK = 0;
 * \note
 */
static xfat_err_t XDISK_CLASS(close)(struct _xdisk_t* disk)
{
	FILE* file = (FILE*)disk->data;
	fclose(file);

	return FS_ERR_OK;
}

/**
 * \func         xdisk_hw_read_sector
 * 
 * \brief		 Base the sector to read disk
 * 
 * \param		 struct _xdisk_t* disk: Disk structure pointer
 *				 u8_t* buffer: Read disk buffer
 *				 u32_t start_sector: Read the starting address of the disk
 *				 u32_t count: Number of read sectors
 * 
 * \retval		 FS_ERR_IO = -1
 *				 FS_ERR_OK = 0
 * \note
 */
static xfat_err_t XDISK_CLASS(read_sector)(struct _xdisk_t* disk, u8_t* buffer, u32_t start_sector, u32_t count)
{
	//获得偏移量
	u32_t offset = start_sector * disk->sector_size;
	FILE* file = (FILE*)disk->data;

	//将位置指针移动到距离文件开头offset个偏移量的位置处
	int err = fseek(file, offset, SEEK_SET);
	if (err == -1)
	{
		printf("seek disk failed:0x%x\n", offset);
		return FS_ERR_IO;
	}

	//从file中一共读取count个扇区，每个扇区大小为sector_size，将结果保存在buffer中
	err = fread(buffer, disk->sector_size, count, file);
	if (err == -1)
	{
		printf("read disk failed:sector: %d, count: %d\n", start_sector, count);
		return FS_ERR_IO;
	}

	return FS_ERR_OK;
}

/**
 * \func         xdisk_hw_write_sector
 * 
 * \brief		 Base the sector to write disk
 * 
 * \param		 struct _xdisk_t* disk: Disk structure pointer
 *				 u8_t* buffer: Write disk buffer
 *				 u32_t start_sector: Write the starting address of the disk
 *				 u32_t count: Number of Write sectors
 * 
 * \retval		 FS_ERR_IO = -1
 *				 FS_ERR_OK = 0
 * \note
 */
static xfat_err_t XDISK_CLASS(write_sector)(struct _xdisk_t* disk, u8_t* buffer, u32_t start_sector, u32_t count)
{
	//获得偏移量
	u32_t offset = start_sector * disk->sector_size;
	FILE* file = (FILE*)disk->data;

	//将位置指针移动到距离文件开头offset个偏移量的位置处
	int err = fseek(file, offset, SEEK_SET);
	if (err == -1)
	{
		printf("seek disk failed:0x%x\n", offset);
		return FS_ERR_IO;
	}

	//将buffer中内容写入file中，一共写count个扇区，每个扇区大小为sector_size
	err = fwrite(buffer, disk->sector_size, count, file);
	if (err == -1)
	{
		printf("write disk failed:sector: %d, count: %d\n", start_sector, count);
		return FS_ERR_IO;
	}

	//清空文件缓存区
	fflush(file);

	return FS_ERR_OK;
}
   
/**
 * \}
 */
   
/**\addtogroup driver_Exported_Functions
 * \{
 */
   
/**
 * \}
 */
  
/************************ (C) COPYRIGHT LiBoran *****END OF FILE****/

