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

//���̲����ӿڽṹ
typedef struct _xdisk_driver_t
{
	xfat_err_t(*open)(struct _xdisk_t* disk, void* init_data);											//�򿪴���
	xfat_err_t(*close)(struct _xdisk_t* disk);															//�رմ���
	xfat_err_t(*read_sector)(struct _xdisk_t* disk, u8_t* buffer, u32_t start_sector, u32_t count);		//��ȡ���̿�
	xfat_err_t(*write_sector)(struct _xdisk_t* disk, u8_t* buffer, u32_t start_sector, u32_t count);	//д����̿�
}xdisk_driver_t;

//�����������̽ṹ
typedef struct _xdisk_t
{
	const char* name;		//��������
	u32_t sector_size;		//ÿ�����̿�/������С
	u32_t total_sector;		//�ܹ��ж��ٿ�/����
	xdisk_driver_t* driver;	//���̲����ӿ�
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

