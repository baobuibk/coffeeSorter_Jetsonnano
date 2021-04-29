/************************************************
* This function erose for image by using 
* a widown square that size 2x2, center 
* at left top of the windown
* 
*************************************************/


#include "img_processing.h"


uint8 img_pro::erosion_square2x2(Matrix &img)
{
    uint16 r, c;

    for (r = 0; r < ROW; r++)
    {
        for (c = 0; c < COL; c++)
        {
            if (r == ROW-1 || c == COL-1)
                img.set(r, c) = 0;
            else
                img.set(r,c) = img.at(r, c) & img.at(r, c + 1) & img.at(r + 1, c) & img.at(r + 1, c + 1);
        }
    }

    return 0;
    
}
