/*
 * round_float.c
 *
 *  Created on: Sep 16, 2019
 *      Author: ducan
 */
#include "Coffee_bean.h"
#include "Math.h"
int32 round_float(	dbfl  value_dbfl,
					uint8 num_point)
{

//	dbfl  	num_dbfl= 0;
	dbfl 	exp_num = 1;
	int32  value_int = 0;
	uint8 	i;
	for (i=0;i<=num_point;i++)
		exp_num     *= 10;

	value_dbfl  *= exp_num;

	if ( abs((uint32)(value_dbfl))  % 10 >= 5)
		value_int = value_dbfl/10 + 1;
	else
		value_int = value_dbfl/10;
//	exp_num /= 10;
//	value_dbfl = (((dbfl)value_int)/(exp_num));3.445466662

	return value_int;
}

