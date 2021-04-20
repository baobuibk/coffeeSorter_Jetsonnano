/*
//=============================================================================
* This function extract texture from image and evaluate
* the quality of coffee beans. 
* Input: Img_se, this value is subtracted from above algorithms (img-background).
* It is utilized for evaluate through color product. 
* Input: Img_seg
* Input: img_label
* Input: nb_object
* Input: order_label
* Output: result
//=============================================================================
*/

#include "Coffee_bean.hpp"

uint8 Algorithm_Cfbean::features_evaluation(	Matrix		&Img_seg,
												Matrix16	&img_label,
												uint16		nb_object,
												uint16		order_label[100],
												uint16		result[500][4],
												uint16		arr_posi_obj[ROW_POSI_SINGLE][2],
												Algorithm_Cfbean &alg_cfbean)
{
	evaluate_color(Img_seg, img_label, nb_object, result);
	alg_cfbean.check_roundness(arr_posi_obj, img_label, nb_object);




	return 0;
}
