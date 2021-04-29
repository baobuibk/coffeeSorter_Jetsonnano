/****************************************
* This function is used to remove small object
* or noise with a particular threshold.
* If the number of pxl of an object is 
* smaller than Thr, the object will be remove
* 
*****************************************/
#include "img_processing.h"


uint8 img_pro::remove_sm_obj(Matrix& img, Matrix16& Img_lbl,uint16 Thr,uint8 cut_bd)
{
	uint32 each_obj[501];		//using to contain the nb of pxl in each obj, abandon '0' element
	uint16 nb_obj = Cc_label(img, Img_lbl, 5);
	uint16 r, c;


	for (uint16 i = 0; i < 501; i++)
		each_obj[i] = 0;

	// ----------------------------
	// Calculate the number of pxl
	// in each obj
	// ----------------------------
	for (r = cut_bd; r < ROW - cut_bd; r++)
	{
		for (c = cut_bd; c < COL - cut_bd; c++)
		{
			if (Img_lbl.at(r, c) != 0)
				each_obj[Img_lbl.at(r, c)] += 1;
		}
	}

	// ----------------------------
	// Eliminate small obj
	// ----------------------------

	for (r = cut_bd; r < ROW - cut_bd; r++)
	{
		for (c = cut_bd; c < COL - cut_bd; c++)
		{
			if (each_obj[Img_lbl.at(r, c)] < Thr)
				img.set(r, c) = 0;
			else
				img.set(r, c) = 1;
		}
	}

	return 0;
}
