#include "Coffee_bean.h"

void Thinning_process(uint8 IMG[ROW][COL])
{
//	uint32 check;
//	invert_image(IMG);
	Thin_step1(IMG);
	Thin_step2(IMG);
//	Thin_step3(IMG);                        here
//	Test_matrix(IMG);

//	check = Test_matrix_sub(IMG);
//	efficient_pntstr();
	//invert_image();
//	efficent_pointf();
}
