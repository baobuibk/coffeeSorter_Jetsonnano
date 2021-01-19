/*
 *	This function check the shape of object and return
 *	value is BAD or GOOD
 *  Created on: Sep 9, 2019
 *  Author: ducan
 */
#include "Coffee_bean.h"


uint8 check_single_shape(dbfl     xO,
                         dbfl     yO,
                         uint16   total_pxl,
                         int16    pnt_st,                          // point to first element
                         uint16   posi_single[ROW_POSI_SINGLE][2]
                         )
{

	dbfl   		vl_ori,vl_check;
	dbfl		scale1;
	uint16		ii;
	uint16 		i;
	uint16      pos1,pos2,pos3,pos4;
	uint16      pos_npx1[total_pxl][2];
	uint16      pos_npx2[total_pxl][2];
	uint16      pos_npx3[total_pxl][2];
	uint16 		pnt_st_lc,pnt_end_lc;		//  started and ended local pointer
	uint16      len_avr = (uint16)(total_pxl/NUM_PART);
	uint16 		xA,xB,yA,yB,xC,yC;
	uint16		convex,concave;
	uint8 		result1;
	uint8 		result2;
	uint8		result3;
	uint8 		result;
	uint8 		cnt_block1 = 0;
	uint8 		cnt_block2 = 0;
	uint8 		cnt_block3 = 0;


//================================================== INITIALIZE VALUE
for(ii=0;ii<total_pxl;ii++)
{
//	xO += posi_single[ii+pnt_st][0];
//	yO += posi_single[ii+pnt_st][1];
	pos1	=  ii	+	pnt_st;

	pos2 	= (ii<	(total_pxl - 	len_avr/3))?(ii +	len_avr/3):(ii - (total_pxl-  len_avr/3));
	pos2   += pnt_st;

	pos3 	= (ii<	(total_pxl -  2*len_avr/3))?(ii + 2*len_avr/3):(ii - (total_pxl-2*len_avr/3));
	pos3   += pnt_st;

	pos4    = (ii<	(total_pxl - 	len_avr/3))?(ii +	len_avr/3):(ii - (total_pxl-  len_avr/3));
	pos4   += pnt_st;

	pos_npx1[ii][0] 	= posi_single[pos1][0];
	pos_npx1[ii][1] 	= posi_single[pos1][1];
	pos_npx2[ii][0] 	= posi_single[pos2][0];
	pos_npx2[ii][1] 	= posi_single[pos2][1];
	pos_npx3[ii][0]		= posi_single[pos3][0];
	pos_npx3[ii][1]		= posi_single[pos3][1];		//error here. check again

}
//xO /= total_pxl;
//yO /= total_pxl;


//================================================== PART 1
for (i=0;i<NUM_PART;i++)
{
	pnt_st_lc	 = i*len_avr ;
	pnt_end_lc	 = pnt_st_lc + len_avr - 1;
	xA			 = pos_npx1[pnt_st_lc ][0];
	yA			 = pos_npx1[pnt_st_lc ][1];
	xB			 = pos_npx1[pnt_end_lc][0];
	yB			 = pos_npx1[pnt_end_lc][1];
	convex		 = 0;
	concave      = 0;
	vl_ori		 = (yA-yB)*(xO-xA) + (xB-xA)*(yO-yA);
	//=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
	for (ii=pnt_st_lc+1;ii<=pnt_end_lc-1;ii++)
	{
		xC 			=	pos_npx1[ii][0];
		yC 			=   pos_npx1[ii][1];
		vl_check 	= 	(yA-yB)*(xC-xA) + (xB-xA)*(yC-yA);
		if(vl_ori*vl_check <0)
			convex  += 1;
		else
			concave += 1;
	}
	//=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

	scale1 = (dbfl)concave/(concave + convex);

	if (scale1 > THR_convex)	cnt_block1 += 1;
}

if (cnt_block1 >= THR_block) result1 = BAD;
else						result1 = GOOD;

//================================================== PART 2

for (i=0;i<NUM_PART;i++)
{
	pnt_st_lc	 = i*len_avr ;
	pnt_end_lc	 = pnt_st_lc + len_avr - 1;
	xA			 = pos_npx2[pnt_st_lc ][0];
	yA			 = pos_npx2[pnt_st_lc ][1];
	xB			 = pos_npx2[pnt_end_lc][0];
	yB			 = pos_npx2[pnt_end_lc][1];
	convex		 = 0;
	concave      = 0;
	vl_ori		 = (yA-yB)*(xO-xA) + (xB-xA)*(yO-yA);
	//=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
	for (ii=pnt_st_lc+1;ii<=pnt_end_lc-1;ii++)
	{
		xC 			=	pos_npx2[ii][0];
		yC 			=   pos_npx2[ii][1];
		vl_check 	= 	(yA-yB)*(xC-xA) + (xB-xA)*(yC-yA);
		if(vl_ori*vl_check <0)
			convex  += 1;
		else
			concave += 1;
	}
	//=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
	scale1 = (dbfl)concave/(concave + convex);

	if (scale1 > THR_convex)	cnt_block2 += 1;
}

if (cnt_block2 >= THR_block) result2 = BAD;
else						result2 = GOOD;

//================================================== PART 3

for (i=0;i<NUM_PART;i++)
{
	pnt_st_lc	 = i*len_avr ;
	pnt_end_lc	 = pnt_st_lc + len_avr - 1;
	xA			 = pos_npx3[pnt_st_lc ][0];
	yA			 = pos_npx3[pnt_st_lc ][1];
	xB			 = pos_npx3[pnt_end_lc][0];
	yB			 = pos_npx3[pnt_end_lc][1];
	convex		 = 0;
	concave      = 0;
	vl_ori		 = (yA-yB)*(xO-xA) + (xB-xA)*(yO-yA);
	//=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
	for (ii=pnt_st_lc+1;ii<=pnt_end_lc-1;ii++)
	{
		xC 			=	pos_npx3[ii][0];
		yC 			=   pos_npx3[ii][1];
		vl_check 	= 	(yA-yB)*(xC-xA) + (xB-xA)*(yC-yA);
		if(vl_ori*vl_check <0)
			convex  += 1;
		else
			concave += 1;
	}
	//=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
	scale1 = (dbfl)concave/(concave + convex);

	if (scale1 > THR_convex)	cnt_block3 += 1;
}

if (cnt_block3 >= THR_block) result3 = BAD;
else						result3 = GOOD;

//================================================== Result

result = result1&&result2&&result3;

//*px_center = (uint16)xO;
//*py_center = (uint16)yO;


return result;
}

