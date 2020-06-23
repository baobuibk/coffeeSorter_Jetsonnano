#include "Coffee_bean.h"
//#include "Math.h"
#include "gauss5x5_table.h"
/*========================================================
 * This function use Gaussian filter with sigma = 3 and size is 5x5
 *
 ========================================================*/

/*
const double GAUSS_BLUR[5][5] = {{0.0317564010287247,	0.0375157550304212,	0.0396589455082867,	0.0375157550304212,	0.0317564010287247},
                                {0.0375157550304212,	0.0443196278517048,	0.0468515082394857,	0.0443196278517048,	0.0375157550304212},
                                {0.0396589455082867,	0.0468515082394857,	0.0495280292438231,	0.0468515082394857,	0.0396589455082867},
                                {0.0375157550304212,	0.0443196278517048,	0.0468515082394857,	0.0443196278517048,	0.0375157550304212},
                                {0.0317564010287247,	0.0375157550304212,	0.0396589455082867,	0.0375157550304212,	0.0317564010287247}
                                };
*/
void Gaussian_filter(uint8 IMGBi[ROW][COL],
                     uint8 IMGBitem[ROW][COL])
{

    //============================================================= Declare

    dbfl    vl_sum_pxl=0;
    uint16 	i,j;
//    uint8   pos_Gauss[6];
//    uint8   num;
    //============================================================= Convolution value
    //-----------------------------calculate temporary IMG value
    for (i = 2; i <  ROW - 2 ; i++)
        {
            for (j = 2; j < COL - 2; j++)
            {
                //=-=-=-=-=-=-=-=-=-=-=-=-
/*
                pos_Gauss[0] = IMGBitem[i-2][j-2]  + IMGBitem[i+2][j-2] + IMGBitem[i-2][j+2] + IMGBitem[i+2][j+2];
                pos_Gauss[1] = IMGBitem[i-1][j-2]  + IMGBitem[i+1][j-2] + IMGBitem[i-2][j-1] + IMGBitem[i+2][j-1]  +
                               IMGBitem[i-2][j+1]  + IMGBitem[i+2][j+1] + IMGBitem[i-1][j+2] + IMGBitem[i+1][j+2];
                pos_Gauss[2] = IMGBitem[i  ][j-2]  + IMGBitem[i-2][j  ] + IMGBitem[i+2][j  ] + IMGBitem[i  ][j+2];
                pos_Gauss[3] = IMGBitem[i  ][j-1]  + IMGBitem[i-1][j  ] + IMGBitem[i+1][j  ] + IMGBitem[i  ][j+1];
                pos_Gauss[4] = IMGBitem[i-1][j-1]  + IMGBitem[i+1][j-1] + IMGBitem[i-1][j+1] + IMGBitem[i+1][j+1];
                pos_Gauss[5] = IMGBitem[i  ][j  ];
                for ( num=0;num<6;num++)
                    vl_sum_pxl += Gauss[num][pos_Gauss[num]];
*/


                vl_sum_pxl =  Gauss_00[IMGBitem[i-2][j-2]  + IMGBitem[i+2][j-2] + IMGBitem[i-2][j+2] + IMGBitem[i+2][j+2]] +
                              Gauss_01[IMGBitem[i-1][j-2]  + IMGBitem[i+1][j-2] + IMGBitem[i-2][j-1] + IMGBitem[i+2][j-1]  +
                                       IMGBitem[i-2][j+1]  + IMGBitem[i+2][j+1] + IMGBitem[i-1][j+2] + IMGBitem[i+1][j+2]] +
                              Gauss_02[IMGBitem[i  ][j-2]  + IMGBitem[i-2][j  ] + IMGBitem[i+2][j  ] + IMGBitem[i  ][j+2]] +
                              Gauss_12[IMGBitem[i  ][j-1]  + IMGBitem[i-1][j  ] + IMGBitem[i+1][j  ] + IMGBitem[i  ][j+1]] +
                              Gauss_11[IMGBitem[i-1][j-1]  + IMGBitem[i+1][j-1] + IMGBitem[i-1][j+1] + IMGBitem[i+1][j+1]] +
                              Gauss_22[IMGBitem[i  ][j  ]];


/*
                vl_sum_pxl = (IMGBitem[i-2][j-2]  + IMGBitem[i+2][j-2] + IMGBitem[i-2][j+2] + IMGBitem[i+2][j+2]) *
                              GAUSS_BLUR[0][0]    +
                             (IMGBitem[i-1][j-2]  + IMGBitem[i+1][j-2] + IMGBitem[i-2][j-1] + IMGBitem[i+2][j-1]  +
                              IMGBitem[i-2][j+1]  + IMGBitem[i+2][j+1] + IMGBitem[i-1][j+2] + IMGBitem[i+1][j+2]) *
                              GAUSS_BLUR[0][1] 	  +
                             (IMGBitem[i][j-2]    + IMGBitem[i-2][j  ] + IMGBitem[i+2][j  ] + IMGBitem[i  ][j+2]) *
                              GAUSS_BLUR[0][2]	  +
                             (IMGBitem[i][j-1]	  + IMGBitem[i-1][j  ] + IMGBitem[i+1][j  ] + IMGBitem[i  ][j+1]) *
                             GAUSS_BLUR[1][2]	  +
                             (IMGBitem[i-1][j-1]  + IMGBitem[i+1][j-1] + IMGBitem[i-1][j+1] + IMGBitem[i+1][j+1]) *
                             GAUSS_BLUR[1][1]	  +
                             IMGBitem[i][j] * GAUSS_BLUR[2][2];
*/
                //=-=-=-=-=-=-=-=-=-=-=-=-
                if (vl_sum_pxl>=0.5)    IMGBi[i][j] = WHITE;
                else 					IMGBi[i][j] = BLACK;
                vl_sum_pxl = 0;
            }
        }
    //=============================================================
}
