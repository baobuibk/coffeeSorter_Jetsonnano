#include "Coffee_bean.h"


uint8 eliminate_noise_line(uint16   x_cur,
                           uint16   y_cur,
                           uint8  	IMG_Bdlc[ROW][COL])

{

    uint16  x_next;
    uint16  y_next;
    uint8 	ERP_line;
    uint8   sum_nei;
    int8    ii,jj;
    ERP_line    = ON;

    //---------------------------------- explore next point to delete
    while(ERP_line == ON)
    {
        IMG_Bdlc[x_cur][y_cur] = BLACK;
        sum_nei = 0;
        //----------------------------------
        for(ii=-1;ii<=1;ii++)
        {
            for (jj=-1;jj<=1;jj++)
            {
                if ( IMG_Bdlc[x_cur+ii][y_cur+jj] == 1 )
                {
                    x_next = x_cur + ii;
                    y_next = y_cur + jj;
                    sum_nei += 1;
                }
            }
        }
        //----------------------------------
        if (sum_nei != 1)
            ERP_line = OFF;
        else
        {
            x_cur = x_next;
            y_cur = y_next;
        }
        //----------------------------------
    }
    return OK_;
}
