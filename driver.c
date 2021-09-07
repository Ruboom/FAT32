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
static xfat_err_t XDISK_CLASS(open)(struct _xdisk_t* disk, void* init_data)
{

}
static xfat_err_t XDISK_CLASS(close)(struct _xdisk_t* disk)
{

}
static xfat_err_t XDISK_CLASS(read_sector)(struct _xdisk_t* disk, u8_t* buffer, u32_t start_sector, u32_t count)
{

}
static xfat_err_t XDISK_CLASS(write_sector)(struct _xdisk_t* disk, u8_t* buffer, u32_t start_sector, u32_t count)
{

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

