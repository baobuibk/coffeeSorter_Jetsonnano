#include "img_processing.h"

uint8 img_pro::rm_border_obj(Matrix &ImgBi, Matrix16 &Img_lbl)
{
	uint16 arr_rmbd[100];
	uint8  size_rmbd = 0;
	uint8  flag_check = 0;
	uint16 r, c;

	Cc_label(ImgBi, Img_lbl, 5);

	//==========================================================
	for (r = 5; r< ROW - 5; r++)
	{
		for (c = 5; c< COL - 5; c++)
		{
			if (((r == 5) || (r == ROW - 6) || (c == 5) || (c == COL - 6)) && (Img_lbl.at(r, c) != 0))
			{
				if (size_rmbd == 0)
				{
					arr_rmbd[0] = Img_lbl.at(r, c);
					size_rmbd++;
				}
				else
				{
					for (uint8 ii = 0; ii < size_rmbd; ii++)
						flag_check |= (Img_lbl.at(r, c) == arr_rmbd[ii]);

					if (flag_check == _ON_)
						flag_check = _OFF_;
					else 
						arr_rmbd[size_rmbd++] = Img_lbl.at(r, c);
				}
			}
		}
	}
		
	//==========================================================
	for (r = 5; r < ROW - 5; r++)
	{
		for (c = 5; c < COL - 5; c++)
		{
			if (Img_lbl.at(r, c) != 0)
			{
				for (uint8 ii = 0; ii < size_rmbd; ii++)
				{
					if (Img_lbl.at(r, c) == arr_rmbd[ii])
					{
						ImgBi.set(r, c) = BLACK;
						break;
					}
				}
			}
		}
	}

	return 0;

}