//=========================================================================%
// This function segmentates image and returns two values:
// The one is binarry image and another is segmentation image with black
// background
// Background: 0 (Black)
// Foreground: 1 (White)
// IMGSeg_dis use for display image in GUI,
// IMGSeg use for continous steps (have back ground is '0', others are
// density + 1
//=========================================================================%

#include "Coffee_bean.hpp"
#include "stdio.h"
//#include <time.h>

uint8 Algorithm_Cfbean::Coffee_Segmentation(Matrix&     Img_re, 
                                            Matrix&     Img_gr, 
                                            Matrix&     Img_bl, 
                                            Matrix&     Img_Bi, 
                                            img_pro&    img_pro_cfbean)
{
    //======================================// declare
    uint8           Thres_binary;
    uint16          i, j;


//    seg_obj.Gaussian_filter(Img_bl,7,1.5);
 //   seg_obj.Print_matrix(Img_bl);
    Thres_binary = img_pro_cfbean.get_automatic_thres_Otsu(Img_bl);

    for (i = 0; i < ROW; i++)
    {
        for (j = 0; j < COL; j++)
        {
            if ((i < 5) | (i >= ROW - 5) | (j < 5) | (j >= COL - 5))            // Eliminating border pixels    
                Img_Bi.set(i, j) = BLACK;
            else
                Img_Bi.set(i, j) = (Img_bl.at(i, j) < (Thres_binary + ADD_BINARY_THR));
        }
    }
    
    //======================================//
    return 0;
}
