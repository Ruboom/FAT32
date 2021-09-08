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

//��������ö��
typedef enum _xfs_type_t
{
	FS_NOT_VALID = 0x00,		//��Ч����ֵ
	FS_FAT32 = 0x01,			//FAT32����
	FS_EXTEND = 0x05,			//��չ����
	FS_WIN95_FAT32_0 = 0x0C,
	FS_WIN95_FAT32_1 = 0x0B,
}xfs_type_t;

#pragma pack(1)

#define MBR_PRIMAR_PART_NR 4

//�������ֶνṹ
typedef struct _mbr_part_t
{
	u8_t boot_active;			//����ָʾ��
	u8_t start_header;			//������ʼ��ַ
	u16_t start_sector : 6;		//��ʼ����
	u16_t start_cylinder : 10;	//��ʼ����
	u8_t system_id;				//��������
	u8_t end_header;			//���̽�����ַ
	u16_t end_sector : 6;		//��������
	u16_t end_cylinder : 10;	//��������
	u32_t relative_sectors;		//���������
	u32_t total_sectors;		//��������
}mbr_part_t;

struct _xdisk_t;

//�����ṹ
typedef struct _mbr_t
{
	u8_t code[446];								//446���ֽڿ�ִ�д���
	mbr_part_t part_info[MBR_PRIMAR_PART_NR];	//64���ֽڴ��̷�����
	u8_t boot_sig[2];							//�����ֽ�������Ч��־
}mbr_t;

#pragma pack()

//���������ӿڽṹ
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
xfat_err_t XDISK_CLASS(get_part_count)(xdisk_t* disk, u32_t* count);
   
/**
 * \}
 */
#endif // __XDISK_H__
/************************ (C) COPYRIGHT LiBoran *****END OF FILE****/

