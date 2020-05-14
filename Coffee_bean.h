//#ifndef COFFEE_BEAN_H
//#define COFFEE_BEAN_H

//#endif // COFFEE_BEAN_H
/*
 * Coffee_bean.h
 *
 *  Created on: Aug 19, 2019
 *      Author: ducan
 */

/*
#ifdef __cplusplus
extern "C" {
#endif
*/

//==================================// DEFINE
#define  int8      signed char		// -128...127
#define  uint8     unsigned char    	//0...255
#define  uint16    unsigned short   	//0...65535
#define  int16     signed short      	//-32768...32767
#define  uint32    unsigned long    	// 0...2^32
#define  int32     signed long      	//-2^32+1...2^32
#define  dbfl      float		//

//==================================//

#define ROW_KERNEL 5   //5
#define COL_KERNEL 5   //5


#define RED_      		    1
#define GREEN_			    2
#define BLUE_ 			    3

#define GOOD                        1
#define BAD  			    0

#define ROW_CAM			    480
#define COL_CAM 		    640


#define ROW                         240		//480		
#define COL                         320		//640
#define SIZE_IMG                    240*320
#define ELIMINATE_RESIZED_SPACE     76800
#define PROCESSING_SPACE            153600
#define PI                          3.14159265358979
#define BLACK                       0
#define WHITE                       1
#define ON                          1
#define OFF                         0
#define OK_                         0
#define ERROR                       1

#define ROW_POSI_SINGLE 2000

//THR
#define NUM_PART		6
#define	THR_convex		0.2			//0.065
#define	THR_block		1
#define	L_THR			30
#define b_THR			11				//10
#define	Chroma_THR		11				//10
#define NUM_LIMIT_OBJ	20




#define THRCIE_sRGB2XYZ_ISC			0.03928   //0.04045
#define THRCIE_XYZ2Lab_T			0.008856

extern const double GAUSS_BLUR[5][5];
//==================================// DEFINE ERROR

//------------------------- CC_Label
#define NO_OBJECT       0
#define E_OVFL_CCLABLE  500

#define ER_SEG_NO_OBJECT_CCLABLE    2
#define ER_SEG_OVFL_CCLABLE         3


#define E_B_S_First_point 						2
#define E_B_S_OVERFLOW_SIZE_POS_SINGLE_LOCAL 	3              //E_B_S_OVERFLOW_SIZE_POS_SINGLE_LOCAL
#define E_B_S_NOISE_OBJECT						4

#define MAX_MT_POS      20
#define DIS_COL         10
#define DIS_ROW         60

#define ADD_BINARY_THR  -10

//==================================// GLOBAL

//extern 	uint8 	IMG_1[ROW][COL];
//extern	uint8 	IMG_2[ROW][COL];
//extern 	uint8	IMG_3[ROW][COL];
//extern 	uint8	IMGBi[ROW][COL];
//extern  uint16   DUPLI_POS_MT[MAX_MT_POS][3];
//extern uint16   posi_single[ROW_POSI_SINGLE][2];			 // contain pixel position

//extern 	uint8	IMG_Border[ROW][COL];

//#include "time.h"
//==================================//
void 	Test_matrix(uint8 IMG[ROW][COL],
					uint8 type);			// 1: integer, 2: float
uint32 	Test_matrix_sub(uint8 IMG[ROW][COL]);
uint32  Test_matrix_sub_dbfl(dbfl IMG[ROW][COL]);
void    Test_kernel(double IMG[ROW_KERNEL][COL_KERNEL]);
uint8 	read_IMG_Gray(uint8 IMG[ROW][COL]);
uint8   read_IMG_Gray_dbfl(dbfl IMG[ROW][COL]);
uint8  	write_img2txt(	uint8 IMG[ROW][COL],
			uint8 channel);

int32 	round_float(	dbfl  number,
                        uint8 num_point);
dbfl 	abs_dbfl(dbfl value);
//---------------------------------------------



uint8 read_IMG_RGB(uint8 IMG_1[ROW][COL],
                   uint8 IMG_2[ROW][COL],
                   uint8 IMG_3[ROW][COL]);

uint8 Segmentation_RGB(uint8 IMG_1[ROW][COL],
                      uint8 IMG_2[ROW][COL],
                      uint8 IMG_3[ROW][COL],
                      uint8 IMGBi[ROW][COL]
                   	   );
uint8 	Otsu_process(uint8 IMG[ROW][COL]);
void Gaussian_filter(uint8 IMGBi[ROW][COL],
                     uint8 IMGBitem[ROW][COL]);

void 	expand_2x2(dbfl I[ROW+4][COL+4]);
uint16 	Cc_label(uint8 IMG[ROW][COL]);
uint8 	Explore_border(	uint8 	IMGBi[ROW][COL],
                        uint8 	*pnb_object,
                        uint16 	*psize_sum_lsp,
                        uint16  posi_single[ROW_POSI_SINGLE][2],
                        uint8  	IMG_Bdlc[ROW][COL]);
uint8 eliminate_noise_line(uint16   x_cur,
                           uint16   y_cur,
                           uint8  	IMG_Bdlc[ROW][COL]);

void 	Thinning_process(uint8 IMG[ROW][COL]);
void 	invert_image(uint8 IMG[ROW][COL]);
void 	Thin_step1(uint8 IMG[ROW][COL]);
void 	Thin_step2(uint8 IMG[ROW][COL]);
void 	Thin_step2_cd1(uint8 IMG[ROW][COL]);
void 	Thin_step2_cd2(uint8 IMG[ROW][COL]);
void 	Thin_step3(uint8 IMG[ROW][COL]);

uint8 	Explore_border_single( 	uint16 	posi_single[ROW_POSI_SINGLE][2],
                                uint8  	IMG_Bdlc[ROW][COL],
                                uint16  **ppsize_sum_lsp,
                                uint16  x_cur,
                                uint16  y_cur);

uint8 check_shape_color(uint8 	IMG_1[ROW][COL],
                        uint8	IMG_2[ROW][COL],
                        uint8	IMG_3[ROW][COL],
                        uint16  posi_single[ROW_POSI_SINGLE][2],
                        uint8	*pnb_object,
                        dbfl 	result[NUM_LIMIT_OBJ][4],
//                        uint16  DUPLI_POS_MT[MAX_MT_POS][3],
                        uint8   img1_sgm[ROW][COL],			// use for determining color
                        uint8   img2_sgm[ROW][COL],
                        uint8   img3_sgm[ROW][COL],
                        uint8   img_check[ROW][COL]		// use for checking color
                        );

uint8 check_single_shape(dbfl       xO,
                         dbfl       yO,
                         uint16     total_pxl,
                         int16      pnt_st,
                         uint16     posi_single[ROW_POSI_SINGLE][2]);


void explore_single_img(uint16  posi_single[ROW_POSI_SINGLE][2],
                        uint8 	IMG_1[ROW][COL],
                        uint8 	IMG_2[ROW][COL],
                        uint8 	IMG_3[ROW][COL],
                        uint8   img1_sgm[ROW][COL],			// use for determining color
                        uint8   img2_sgm[ROW][COL],
                        uint8   img3_sgm[ROW][COL],
                        uint8   img_check[ROW][COL],		// use for checking color
                        int16 	pnt_st,
                        int16	pnt_end
 //                       uint16  check_ii
                        );

uint8 	check_color(uint8   img1_sgm[ROW][COL],
                    uint8   img2_sgm[ROW][COL],
                    uint8   img3_sgm[ROW][COL],
                    uint8   img_check[ROW][COL]
                    );

void rgb2lab(	uint8   img1_sgm[ROW][COL],
                uint8   img2_sgm[ROW][COL],
                uint8   img3_sgm[ROW][COL],
                dbfl	L[ROW][COL],
                dbfl	a[ROW][COL],
                dbfl	b[ROW][COL]
                );

void Test_pnt(uint8 *a);
void Test_pnt2(uint8 **b);



//============================================INLINE FUNCTION
//------------------------------- Approximative POW
static inline double fastPow(double a, double b) {
  union {
    double d;
    int x[2];
  } u = { a };
  u.x[1] = (int)(b * (u.x[1] - 1072632447) + 1072632447);
  u.x[0] = 0;
  return u.d;
}

/*
#ifdef __cplusplus
}
#endif
*/

