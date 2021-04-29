/*
 * round.cpp
 *
 *  Created on: Sep 16, 2019
 *      Author: ducan
 *  Modify by ducan on Mar 3, 2021
 */

#include "img_processing.h"
#include <cmath>

void img_pro::invert_binary_img(Matrix &img)
{
	uint16 i, j;

	for (i = 0; i < ROW; i++)
	{
		for (j = 0; j < COL; j++)
		{
			img.set(i, j) = !img.at(i, j);
		}

	}

}

