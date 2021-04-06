/*
* This function thin the object in img to one pixel width
* The input img is the binary image, with foreground =1 and background = 0
* 
*/

#include "img_processing.h"

void img_pro::thining_algorithm(Matrix& img)
{
	thin_step1(img);
	thin_step2(img);
//	Thin_step3(IMG);                        here

}
