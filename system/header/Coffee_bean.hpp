
/*
 * Coffee_bean.h
 *
 *  Created on: Aug 19, 2019
 *      Author: ducan
 */
#ifndef COFFEE_HEADER
#define COFFEE_HEADER

#include "img_processing.hpp"
#include "external_devices.hpp"
//==================================// DEFINE
#define ADD_BINARY_THR	-17

#define THR_PXL			11
#define THR_PERCENTAGE	0.07
#define THR_SHAPE		1.16
//==================================//


//==================================// GLOBAL
//extern		uint8	flag_timer;
//extern 	uint8 	IMG_1[ROW][COL];
//extern	uint8 	IMG_2[ROW][COL];
//extern 	uint8	IMG_3[ROW][COL];
//extern 	uint8	IMGBi[ROW][COL];
//extern  uint16   DUPLI_POS_MT[MAX_MT_POS][3];
//extern uint16   posi_single[ROW_POSI_SINGLE][2];			 // contain pixel position

//extern 	uint8	IMG_Border[ROW][COL];

//#include "time.h"
//#include "stdio.h"
//==================================//

class Algorithm_Cfbean
{
public:
	uint8 Coffee_Segmentation(Matrix& Img_re, Matrix& Img_gr, Matrix& Img_bl, Matrix& Img_Bi, img_pro &img_pro_cfbean);
	
	uint8 features_evaluation(	Matrix		&Img_seg, 
					Matrix16	&img_label, 
					uint16		nb_object, 
					uint16		order_label[100], 
					uint16		result[500][4],
					uint16		arr_posi_obj[ROW_POSI_SINGLE][2],
					Algorithm_Cfbean &alg_cfbean);

	uint8 evaluate_color(	Matrix&		Img_seg,
				Matrix16&	img_label,
				uint16		nb_object,
				uint16		result_color[500][4]);


	uint8 check_roundness(	uint16		arr_posi_obj[ROW_POSI_SINGLE][2],
				Matrix16&	img_label,
				uint16		nb_obj);

};


#endif

