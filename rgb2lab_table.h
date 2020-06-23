/*
 * rgb2lab_table.h
 *
 *  Created on	: Oct 30, 2019
 *  Author		: ducan
 *  This function uses table method to convert from RGB to LAB
 *  This processing consist of two step: RGB2XYZ and XYZ2LAB
 *  This orginal algorithm is followed according to this site:
 * "https://www.mathworks.com/help/vision/ref/colorspaceconversion.html"
 *
 *
 */

#ifndef RGB2LAB_TABLE_H_
#define RGB2LAB_TABLE_H_

extern const double rgb2xyz_table1[256];
extern const double rgb2xyz_table2[256];

#endif /* RGB2LAB_TABLE_H_ */
