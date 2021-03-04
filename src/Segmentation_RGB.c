//=========================================================================%
// This function segmentate image and reture two value:
// The one is binarry image and another is segmentation image with black
// background
// Background: 0 (Black)
// Foreground: 1 (White)
// IMGSeg_dis use for display image in GUI,
// IMGSeg use for continous steps (have back ground is '0', others are
// density + 1
//=========================================================================%

#include "Coffee_bean.h"
#include "stdio.h"
//#include <time.h>



uint8 Segmentation_RGB(uint8 IMG_1[ROW][COL],
                      uint8 IMG_2[ROW][COL],
                      uint8 IMG_3[ROW][COL],
                      uint8 IMGBi[ROW][COL]
                      )
{
    //======================================// declare
    uint16 	i        =   0,
            j        =   0,
            nb_label =   0;

    uint8   IMGBitem[ROW][COL];
    int16 	THRBLUE  =   0;

    //======================================// Calculate Otsu Thr
    THRBLUE     = Otsu_process(IMG_3);

    //======================================// Calculate Binary image

    for (i=0;i<ROW;i++)
    {
        for (j=0;j<COL;j++)
        {
            IMGBitem[i][j] =   	(IMG_3[i][j] >= (THRBLUE + ADD_BINARY_THR));
        }
    }

    //======================================//Eliminate noises
//    *pstart = clock();
    Gaussian_filter(IMGBi,IMGBitem);	// Gaussiane
//   *pendtime = clock();
    //======================================//Eliminating border pixels
    for (i=0;i<ROW;i++)
    {
        for (j=0;j<COL;j++)
        {
            if ((i <5) | (i>= ROW-5) | (j<5) | (j>= COL-5))
                IMGBi[i][j] = 1;
        }
    }
    //-------------------------------
//    Test_matrix_sub(IMGBi);
    nb_label = Cc_label(IMGBi);			// Component Connecting labels

    if (nb_label == NO_OBJECT)
        return ER_SEG_NO_OBJECT_CCLABLE;
    else if (nb_label == E_OVFL_CCLABLE)
        return ER_SEG_OVFL_CCLABLE;
    else
    {
    //----------------------------------------------------------// CIE Segmentation image

        for (i=0;i<ROW;i++)
        {
            for (j=0;j<COL;j++)
            {
                if ((i==0) || (j==0) || (i==ROW-1) || (j==COL-1))
                    IMGBi[i][j] = BLACK;
                else
                {
                    if(IMGBi[i][j] != 1) 	IMGBi[i][j] = WHITE;
                    else 			IMGBi[i][j] = BLACK;
                }
                IMG_1[i][j] *= (IMGBi[i][j]);
                IMG_2[i][j] *= (IMGBi[i][j]);
                IMG_3[i][j] *= (IMGBi[i][j]);
            }
        }
 //       Test_matrix_sub(IMG_3);

        return OK_;
    }
}

