/* In this project, Descartes coordinate will be rule following
 *  x = row
 *  y = col
 *        O(0,0) -------y axis = col
 *          |
 *          |
 *          |
 *          |
 *      x axis = row
 *
 *  Created on: Sep 9, 2019
 *      Author: ducan
 */
#include "Coffee_bean.h"
//#include "stdio.h"
uint8 check_shape_color(uint8 	IMG_1[ROW][COL],
			uint8	IMG_2[ROW][COL],
			uint8	IMG_3[ROW][COL],
			uint16  posi_single[ROW_POSI_SINGLE][2], // contain position of image pixels
                        uint8	*pnb_object,
                        dbfl 	result[NUM_LIMIT_OBJ][4],
//                        uint16  DUPLI_POS_MT[MAX_MT_POS][3],
//                        dbfl   img1_sgm[ROW][COL],				// use for determining color
//                        dbfl   img2_sgm[ROW][COL],
//                        dbfl   img3_sgm[ROW][COL],
                        uint8   img_check[ROW][COL],			// use for checking color
			dbfl    *ptimer,
			dbfl 	L[ROW][COL],
			dbfl    a[ROW][COL],
			dbfl    b[ROW][COL]
//			uint16    *ploop
                        )
{

    dbfl	xO = 0,yO= 0;
//    dbfl    	cnd1=0,cnd2=0;
    uint16  	ii=0;
//    uint16 	iii=0;
    uint16  	x_center=0,y_center=0;				// center coodinate value
    uint16  	total_pxl=0;
//    uint16  	copy_DUPLI_POS_MT[MAX_MT_POS][3];
    int16 	pnt_st = 0;							// Point to the first elements
    int16	pnt_end = -1;						// point to the end elements
    uint8   	i=0;
    uint8  	result_shape=0;						// single result
    uint8   	result_color=0;

//    uint8   check_dis=0;
//    uint8   ovfl_DUPLI_POS_MT = OFF;
//    uint8   nb_object_after = *pnb_object;
//    uint8   error_same_object= OFF;
//	clock_t  start_time;
//	clock_t  end_time;

//============================================================== copy value to check later
/*
for (i=0;i<MAX_MT_POS;i++)
{
    copy_DUPLI_POS_MT[i][0] = DUPLI_POS_MT[i][0];
    copy_DUPLI_POS_MT[i][1] = DUPLI_POS_MT[i][1];
    copy_DUPLI_POS_MT[i][2] = DUPLI_POS_MT[i][2];
}
*/
	result[0][0] = *pnb_object;
	result[0][1] = 1111;
	result[0][2] = 3333;
//static count = 0;
//static timer = 0;
//============================================================== SHAPE
	for(i=0;i<*pnb_object;i++)
	{
    //=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-= INITIALIZE VALUE
//	start_time = 0;
//	end_time   = 0;


    		pnt_st 		= pnt_end + 2;
    		pnt_end 	= pnt_st  + posi_single[pnt_st - 1][1] - 1;

    //----------------------------------- calculate center pixel
    		total_pxl       = posi_single[pnt_st-1][1];
//    check_dis       = 0;
    		xO              = 0;
   		yO              = 0;

    		for(ii=0;ii<total_pxl;ii++)
    		{
        		xO += posi_single[ii + pnt_st][0];
        		yO += posi_single[ii + pnt_st][1];
    		}
    		xO /= total_pxl;
  	  	yO /= total_pxl;
    		x_center = (uint16)xO;
    		y_center = (uint16)yO;

    //----------------------------------- Explore if duplicate value
/*
    for(iii=0;iii<MAX_MT_POS;iii++)
    {
        cnd1 = abs_dbfl(x_center - DUPLI_POS_MT[iii][0]) ;
        cnd2 = abs_dbfl(y_center - DUPLI_POS_MT[iii][1]) ;
        if((cnd1 <= DIS_ROW) && (cnd2 <= DIS_COL))
        {
            DUPLI_POS_MT[iii][0] = x_center;    // update new coodinate
            DUPLI_POS_MT[iii][1] = y_center;
            DUPLI_POS_MT[iii][2] = iii+1;       // ID = iii+1;
            check_dis  += 1;
        }
        else continue;
    }
*/
    //----------------------------------- Check object shape and color
//    if (check_dis == 0)
//    {
        //=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=	SHAPE
		result_shape	= check_single_shape(xO,yO,total_pxl,pnt_st,posi_single);

	//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-= 	COLOR
        	explore_single_img(posi_single,IMG_1,IMG_2,IMG_3,img_check,pnt_st,pnt_end,L,a,b);

       	//       *pstart     = clock();
//	start_time 	= clock();

//		result_color	= check_color(img_check,L,a,b);
//	end_time   	= clock();

	//        *pendtime   = clock();
        	result[i+1][0]  = x_center;
        	result[i+1][1]  = y_center;
        	result[i+1][2]  = result_shape && result_color;
        	result[i+1][3]  = i+1;

//	float seconds = (float)(end_time - start_time)/ CLOCKS_PER_SEC;
//	printf("time = %.4f \n", seconds);
//	(*ploop)++;
//	(*ptimer) += seconds;
        //------------------------------  attach new coordinate for object
        /*
        for (ii=0;ii<MAX_MT_POS;ii++)
        {
            if (DUPLI_POS_MT[ii][0] == 0)
            {
                DUPLI_POS_MT[ii][2] = ii+1;  //attach ID for object
                DUPLI_POS_MT[ii][0] = xO;
                DUPLI_POS_MT[ii][1] = yO;
                break;
            }
        }
        if ( ii ==(MAX_MT_POS-1) &&
            (DUPLI_POS_MT[ii][0] == copy_DUPLI_POS_MT[ii][0]) &&
            (DUPLI_POS_MT[ii][1] == copy_DUPLI_POS_MT[ii][1]) &&
            (DUPLI_POS_MT[ii][2] == copy_DUPLI_POS_MT[ii][2]))
        {
            ovfl_DUPLI_POS_MT = ON;          // give this value go out to alarm over flow
        }
        */
        //------------------------------
//    }

//    else if (check_dis == 1) nb_object_after -=1;
//    else if (check_dis >= 2) error_same_object = ON;     // this error will be checked later
//    else continue;
	}

//==============================================================
/*
for (i=0;i<MAX_MT_POS;i++)
{
    if( (copy_DUPLI_POS_MT[i][0] == DUPLI_POS_MT[i][0]) &&       //if don't change -> eliminate old values
        (copy_DUPLI_POS_MT[i][1] == DUPLI_POS_MT[i][1]) &&
        (copy_DUPLI_POS_MT[i][2] == DUPLI_POS_MT[i][2]))
    {
        DUPLI_POS_MT[i][0] = 0;
        DUPLI_POS_MT[i][1] = 0;
        DUPLI_POS_MT[i][2] = 0;
    }
    else continue;
}
*/
return 1;
}
