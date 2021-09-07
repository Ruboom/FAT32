
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
 static int array[32];
   
/**
 * \}
 */
   
/**\defgroup fatfs_test_Private_FunctionPrototypes
 * \{
 */
 void print_int(int v);
   
/**
 * \}
 */
   
/**\defgroup fatfs_test_Private_Functions
 * \{
 */

int main()
{
	int* p_array = array;

	for (int i = 0; i < 100; i++)
	{
		print_int(i);
	}

	p_array[0] = 32;

	printf("Test End\n");

	return 0;
}

void print_int(int v)
{
	printf("v = %d\n", v);
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








