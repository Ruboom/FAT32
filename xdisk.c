/**
 *!
 * \file		xdisk.c
 * \brief       Disk operation
 * \version     1.0
 * \date        2021/09/07
 * \author      LiBoran
 *Last modified by LiBoran 2021/09/07
 *Copyright (c) 2021 by LiBoran. All Rights Reserved.
 */
   
/*Includes ----------------------------------------------*/
#include "xdisk.h"
   
/**\defgroup xdisk_Private_TypesDefinitions
 * \{
 */
   
/**
 * \}
 */
   
/**\defgroup xdisk_Private_Defines
 * \{
 */
   
/**
 * \}
 */
   
/**\defgroup xdisk_Private_Macros
 * \{
 */
   
/**
 * \}
 */
   
/**\defgroup xdisk_Private_Variables
 * \{
 */
   
/**
 * \}
 */
   
/**\defgroup xdisk_Private_FunctionPrototypes
 * \{
 */
   
/**
 * \}
 */
   
/**\defgroup xdisk_Private_Functions
 * \{
 */
   
/**
 * \}
 */
   
/**\addtogroup xdisk_Exported_Functions
 * \{
 */


/**
 * \func         xdisk_open
 * 
 * \brief        Achieve driver packaging(xdisk_hw_open)
 * 
 * \param        xdisk_t* disk: Disk structure pointer
 *				 const char* name: Disk name
 *				 xdisk_driver_t* driver: Driver structure pointer
 *				 void* init_data: Disk path
 * 
 * \retval       err
 * 
 * \note         
 */
xfat_err_t xdisk_open (xdisk_t* disk, const char* name, xdisk_driver_t* driver, void* init_data)
{
	xfat_err_t err;

	disk->driver = driver;

	err = disk->driver->open(disk, init_data);
	if (err < 0)
	{
		return err;
	}

	disk->name = name;
	return err;
}


/**
 * \func         xdisk_close
 * 
 * \brief        Achieve driver packaging(xdisk_hw_close)
 * 
 * \param        xdisk_t* disk: Disk structure pointer
 * 
 * \retval       err
 * 
 * \note         
 */
xfat_err_t xdisk_close (xdisk_t* disk)
{
	xfat_err_t err;

	err = disk->driver->close(disk);
	if (err < 0)
	{
		return err;
	}

	return err;
}


/**
 * \func         xdisk_read_sector
 * 
 * \brief        Achieve driver packaging(xdisk_hw_read_sector)
 * 
 * \param        xdisk_t* disk: Disk structure pointer
 *				 u8_t* buffer: Read disk buffer
 *				 u32_t start_sector: Read the starting address of the disk
 *				 u32_t count: Number of read sectors
 * 
 * \retval       err
 * \note         
 */
xfat_err_t xdisk_read_sector (xdisk_t* disk, u8_t* buffer, u32_t start_sector, u32_t count)
{
	xfat_err_t err;

	//判断读取扇区是否超过边界
	if (start_sector + count >= disk->total_sector)
	{
		return FS_ERR_PARAM;
	}

	err = disk->driver->read_sector(disk, buffer, start_sector, count);

	return err;
}


/**
 * \func         xdisk_write_sector
 * 
 * \brief        Achieve driver packaging(xdisk_hw_write_sector)
 * 
 * \param        xdisk_t* disk: Disk structure pointer
 *				 u8_t* buffer: Write disk buffer
 *				 u32_t start_sector: Write the starting address of the disk
 *				 u32_t count: Number of write sectors
 * 
 * \retval       err
 * 
 * \note         
 */
xfat_err_t xdisk_write_sector (xdisk_t* disk, u8_t* buffer, u32_t start_sector, u32_t count)
{
	xfat_err_t err;

	//判断写入扇区是否超过边界
	if (start_sector + count >= disk->total_sector)
	{
		return FS_ERR_PARAM;
	}

	err = disk->driver->write_sector(disk, buffer, start_sector, count);

	return err;
}
   
/**
 * \}
 */
  
/************************ (C) COPYRIGHT LiBoran *****END OF FILE****/
