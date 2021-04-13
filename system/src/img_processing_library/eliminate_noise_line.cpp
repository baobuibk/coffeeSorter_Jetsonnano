/*
* This function is used for removing redundant border of object
* Input: del_val    : contain the label of object that need to remove
*       img_border  : this is the border of objects  
*       img_label   : store the label each object, this value is calculated
*                     through the cc_label algorithm. 
* Output:
*   x_coor_noise, y_coor_noise: contain the center position of removed object
* 
*/

#include "img_processing.h"


void img_pro::eliminate_noise_line(uint16    del_val,
                                    Matrix   &img_border,
                                    Matrix16 &img_label,
                                    uint32   &row_coor_noise,
                                    uint32   &col_coor_noise)

{
    uint16 i, j;
    uint16 nb_pxl = 0;

    row_coor_noise = 0;
    col_coor_noise = 0;

    for (i = 0; i < ROW; i++)
    {
        for (j = 0; j < COL; j++)
        {
            if (img_label.at(i, j) == del_val)
            {
                img_border.set(i, j) = BLACK;
                row_coor_noise += i;
                col_coor_noise += j;
                nb_pxl++;
            }
        }
    }
    row_coor_noise /= --nb_pxl;
    col_coor_noise /= --nb_pxl;

    //---------------------------------- explore next point to delete
    
}
