/*
 * Test_pnt.c
 *
 *  Created on: Sep 6, 2019
 *      Author: ducan
 */
#include "Coffee_bean.h"



void Test_pnt(uint8 *a)
{
*a +=2;
Test_pnt2(&a);
}

