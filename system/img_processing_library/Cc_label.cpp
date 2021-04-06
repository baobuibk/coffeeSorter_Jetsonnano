//=========================================================================%
//  This funtion explores labels for an image, return a labeled image
//  and number of labels of an image, this algorithm will abandon border pixels
//  and attach '0' value for them.
//  In this funtion uses algorithm "Two pass" by:
//	"https://en.wikipedia.org/wiki/Connected-component_labeling"
//  max = 499 labels
//  return = E_OVFL_CCLABLE: over flow
//  return = MAX_CCLABLE: don't have any object in the image
//	Note: In this function, img is the input binary image, 
//	it's also the label output image. 
//	Input: img: is a binary image, getting border is based on this one
//			cut_bd: this value is the number of border pxl that wanna abandon
//  Output: img: this value is the binary input, it also contains the label of
//			output
//=========================================================================%
#include "img_processing.h"

//uint16  IMG_label[ROW][COL];
uint16 img_pro::Cc_label(Matrix &img,Matrix16 &Img_label, uint8 cut_bd)    //adjust the output later, change to uint16 at img_label
{
	uint16  same_lbst1[501];                           // same label in step 1, abandon index at '0'
	uint16 	label_now = 0, lb_min;
	uint16 	i, j;
	uint16  ii, tem;
	uint8   same_lbst2[500];						   // same label in step 2
	uint16 	nei[4];									   // neighboor
	uint8	label_real = 0;
	uint8 	flag_overflow = _OFF_;


	//	Test_matrix(IMG,1);

	for (ii = 0; ii < OV_LB; ii++)  same_lbst1[ii] = 0;
	for (i = 0; i < ROW; i++)
	{
		for (j = 0; j < COL; j++) Img_label.set(i,j) = 0;
	}

	//========================================================================= STEP 1
	for (i = cut_bd; i < ROW - cut_bd; i++)
	{
		for (j = cut_bd; j < COL - cut_bd; j++)
		{
			if (img.at(i,j) != BLACK)
			{
				//--------------------------------------------
				lb_min = OV_LB;
				nei[0] = Img_label.at(i		,j - 1	);
				nei[1] = Img_label.at(i - 1	,j - 1	);
				nei[2] = Img_label.at(i - 1	,j		);
				nei[3] = Img_label.at(i - 1	,j + 1	);
				//-------------------------------------------- calculate min label
				for (ii = 0; ii < 4; ii++)
				{
					if (nei[ii] != 0)
					{
						if (nei[ii] < lb_min)	 lb_min = nei[ii];   	//if don't have any satisfying label: lb_min =500
					}
				}
				//-------------------------------------------- save same values and attach label for IMG
				if (lb_min != OV_LB)												// if having min label 
				{
					Img_label.set(i,j) = lb_min;

					for (ii = 0; ii < 4; ii++) 	same_lbst1[nei[ii]] = lb_min;   //label have not been written-> write new for all 4 elements
				}
				else                                                            // if not having min label -> attach new label
				{
					Img_label.set(i,j)		= ++label_now;
					same_lbst1[label_now]	=   label_now;						// attach new label 
				}
				//--------------------------------------------
			}
			if (label_now >= OV_LB) break;
		}
		if (label_now >= OV_LB) break;
	}
	if (label_now >= OV_LB) flag_overflow = _ON_;

//	same_lbst1[0] = 0;

	//	Test_matrix(IMG_label,1);
		//========================================================================= STEP 2

	if (flag_overflow == _ON_) return OVER_FL_OBJ;
	else if (label_now == 0) return NO_OBJECT;
	else
	{
		//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- ARRANGING STORE
		for (ii = 1; ii <= label_now; ii++)
		{
			tem = ii;
			if (same_lbst1[ii] == ii) same_lbst2[ii] = ++label_real;
			else
			{
				while (same_lbst1[tem] != tem)
				{
					tem = same_lbst1[tem];
					same_lbst1[ii] = tem;
				}
			}
		}
		//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
		for (i = 0; i < ROW; i++)
		{
			for (j = 0; j < COL; j++)
			{
				//--------------------------------------------
				if (Img_label.at(i,j) != BLACK)
					Img_label.set(i, j) = same_lbst2[same_lbst1[Img_label.at(i,j)]];
				//--------------------------------------------
			}
		}
		//		Test_matrix(IMG,1);
		return label_real;
	}
	//=========================================================================


}
