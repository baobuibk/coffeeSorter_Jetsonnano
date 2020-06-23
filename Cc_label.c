//=========================================================================%
//  This funtion explores labels for a image, return a labeled image
//  and number of label that image, this algorithm will abandon border pixel
//  and adapt '0' value for them.
//  In this funtion uses algorithm "Two pass" by:
//	"https://en.wikipedia.org/wiki/Connected-component_labeling'
//  max = 499 labels
//  return = E_OVFL_CCLABLE: over flow
//  return = MAX_CCLABLE: don't have any object in the image
//=========================================================================%
#include "Coffee_bean.h"

uint16 Cc_label(uint8 IMG[ROW][COL])
{
    uint16  same_lbst1[500];                           // same label in step 1
    uint16  IMG_label[ROW][COL];
    uint16 	label_now=0, lb_min;
	uint16 	i,j;
	uint16  ii,tem;
    uint8   same_lbst2[256];						   // same label in step 2
	uint8 	nei[4];									   // neighboor
    uint8	label_real  =   1;
	uint8 	flag_overflow = OFF;


//	Test_matrix(IMG,1);

    for (ii=0;ii<500;ii++)  same_lbst1[ii]  = 0;
    for (i=0;i<ROW;i++)
    {
        for (j=0;j<COL;j++) IMG_label[i][j] = 0;
    }

	//=========================================================================STEP 1
	for (i=1;i<ROW-1;i++)
	{
		for (j=1;j<COL-1;j++)
		{
			if (IMG[i][j] != BLACK)
			{
				//--------------------------------------------
				lb_min 	  = 500;
				nei[0]    = IMG_label[i  ][j-1];
				nei[1]    = IMG_label[i-1][j-1];
				nei[2]    = IMG_label[i-1][j  ];
				nei[3]    = IMG_label[i-1][j+1];
  				//-------------------------------------------- calculate min label
				for (ii=0;ii<4;ii++)
				{
					if (nei[ii] != 0)
					{
						if (nei[ii] < lb_min)	 lb_min = nei[ii];   	//if don't have any satisfying label: lb_min =500
					}
				}
  				//-------------------------------------------- save same values and adapt label for IMG
				if (lb_min != 500)
				{
					IMG_label[i][j] = lb_min;
					for (ii=0;ii<4;ii++) 	same_lbst1[nei[ii]] = lb_min;    //label have not been written-> write new for all 4 elements
				}
				else
				{
                    IMG_label[i][j] = ++label_now;
					same_lbst1[label_now] = label_now;			// replace
				}
				//--------------------------------------------
			}
			if (label_now >= 500) break;
		}
		if (label_now >= 500) break;
	}
	if (label_now >= 500) flag_overflow = ON;

	same_lbst1[0] = 0;

//	Test_matrix(IMG_label,1);
	//========================================================================= STEP 2

    if (flag_overflow == ON) return E_OVFL_CCLABLE;
    else if (label_now == 0) return NO_OBJECT;
	else
	{
		//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- ARRANGING STORE
		for (ii=1;ii<=label_now;ii++)
		{
			tem = ii;
			if(same_lbst1[ii] == ii) same_lbst2[ii] = label_real++;
			else
			{	while(same_lbst1[tem] != tem)
				{
					tem 			= same_lbst1[tem];
					same_lbst1[ii] 	= tem;
				}
			}
		}
		//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
		for (i=0; i<ROW; i++)
		{
			for (j=0; j<COL; j++)
			{
				//--------------------------------------------
				if (IMG_label[i][j] == BLACK)
					IMG[i][j] = BLACK;
				else
					IMG[i][j] = same_lbst2[same_lbst1[IMG_label[i][j]]];
				//--------------------------------------------
			}
		}
//		Test_matrix(IMG,1);
		return --label_real;
	}
	//=========================================================================


}
