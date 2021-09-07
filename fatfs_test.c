
/**
 *!
 * \file       fatfs_test.c
 * \brief       
 * \version     1.0
 * \date        2021/09/07
 * \author      LiBoran
 *Last modified by notrynohigh 2021/09/07
 *Copyright (c) 2021 by LiBoran. All Rights Reserved.
 */
   
/*Includes ----------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include "xdisk.h"
#include "xfat.h"
   
/**\defgroup fatfs_test_Private_TypesDefinitions
 * \{
 */
   
/**
 * \}
 */
   
/**\defgroup fatfs_test_Private_Defines
 * \{
 */
   
/**
 * \}
 */
   
/**\defgroup fatfs_test_Private_Macros
 * \{
 */
   
/**
 * \}
 */
   
/**\defgroup fatfs_test_Private_Variables
 * \{
 */
 extern xdisk_driver_t vdisk_driver;
 //磁盘路径
 const char* disk_path_test = "disk_test.img";
 //写缓存区160Kb
 static u32_t write_buffer[160 * 1024];
 //读缓存区160Kb
 static u32_t read_buffer[160 * 1024];
   
/**
 * \}
 */
   
/**\defgroup fatfs_test_Private_FunctionPrototypes
 * \{
 */

 /**
 * \func         disk_io_test
 * 
 * \brief		 Read disk and write disk test function
 * 
 * \param		 void
 * 
 * \retval		 error: -1
 *				 no error: 0
 * \note
 */
 int disk_io_test(void)
 {
	 int err;
	 xdisk_t disk_test;

	 memset(read_buffer, 0, sizeof(read_buffer));

	 //打开磁盘
	 err = xdisk_open(&disk_test, "vdisk_test", &vdisk_driver, (void*)disk_path_test);
	 if (err)
	 {
		 printf("open disk failed!\n");
		 return -1;
	 }

	 //将write_buffer从磁盘第0个扇区开始写入两个扇区
	 err = xdisk_write_sector(&disk_test, (u8_t*)write_buffer, 0, 2);
	 if (err)
	 {
		 printf("disk write failed!\n");
		 return -1;
	 }

	 //将磁盘中第0个扇区开始的两个扇区内容读取写入read_buffer
	 err = xdisk_read_sector(&disk_test, (u8_t*)read_buffer, 0, 2);
	 if (err)
	 {
		 printf("disk read failed!\n");
		 return -1;
	 }

	 //对比read_buffer与write_buffer是否一致
	 err = memcmp((u8_t*)read_buffer, (u8_t*)write_buffer, disk_test.sector_size * 2);
	 if (err != 0)
	 {
		 printf("data not equal!\n");
		 return -1;
	 }

	 //关闭磁盘
	 err = xdisk_close(&disk_test);
	 if (err)
	 {
		 printf("disk close failed!\n\n");
		 return -1;
	 }

	 printf("disk io test ok!\n");
	 return 0;
 }
   
/**
 * \}
 */
   
/**\defgroup fatfs_test_Private_Functions
 * \{
 */

int main()
{
	xfat_err_t err;

	//给写入的buffer赋值
	for (int i = 0; i < sizeof(write_buffer) / sizeof(u32_t); i++)
	{
		write_buffer[i] = i;
	}

	err = disk_io_test();
	if (err)
	{
		return err;
	}

	printf("Test End\n");
	return 0;
}

   
/**
 * \}
 */
   
/**\addtogroup fatfs_test_Exported_Functions
 * \{
 */
   
/**
 * \}
 */
  
/************************ (C) COPYRIGHT LiBoran *****END OF FILE****/








