/*//================================================
 * This funtion is used to adjust pixels position
 * at angle
 *
 *
 *
 *///================================================

#include "Coffee_bean.h"

void Thin_step3(uint8 IMG[ROW][COL])
{
	uint16 	i,j;
	int8    ii,jj;
	uint8 	sum_neighbor,fi,se,th;
	uint8  	pnt = 0;
	uint8   pos[3][2];
	uint8   xfi,yfi,xse,yse,xth,yth,x_u,y_u;
	uint16  upd[500][2], size_upd= 0;
	//================================================//
	for(i=5;i < ROW-5;i++)
	{
		for(j=5;j < COL-5;j++)
		{
			//-----------------------------------------
			sum_neighbor = IMG[i+1][j+1] + IMG[i+1][j+2] + IMG[i+2][j+1] + IMG[i+2][j+2];
			if (sum_neighbor == 3)                   // getting pixel position if it's '1'
			{
				//----------------------------------// explore positions == 1
				for (ii=1;ii<=2;ii++)
				{
					for (jj=1;jj<=2;jj++)
					{
						if (IMG[i+ii][j+jj] == 1)
						{
							pos[pnt		][0] = i+ii;  //x
							pos[pnt++	][1] = j+jj;  //y
						}
					}
				}
				xfi = pos[0][0];
				yfi = pos[0][1];
				xse = pos[1][0];
				yse = pos[1][1];
				xth = pos[2][0];
				yth = pos[2][1];
				//----------------------------------// calculating sum of neighbors
				fi = 0;
				se = 0;
				th = 0;
				for (ii=-1;ii<=1;ii++)
				{
					for(jj=-1;jj<=1;jj++)
					{
						fi += IMG[xfi + ii][yfi + jj];
						se += IMG[xse + ii][yse + jj];
						th += IMG[xth + ii][yth + jj];
					}
				}
				//----------------------------------//
				if (((fi-1) == 3) && ((se-1) == 3) && ((th-1) == 3))
				{
					if ((xfi == xse) || (yfi==yse))
					{
						//----------------------------//
						if ((xfi=xth) || (yfi == yth))
						{
							x_u = xfi;
							y_u = yfi;
						}
						else
						{
							x_u = xse;
							y_u = yse;
						}
						//----------------------------//
					}
					else
					{
						x_u = xth;
						y_u = yth;

					}
					upd[size_upd  ][0] = x_u;
					upd[size_upd++][1] = y_u;
				}
				//----------------------------------//
			}
			//-----------------------------------------

		}
	}
	//================================================// Moving to new position

	for (i=0;i<size_upd;i++)
	{
		IMG[ upd[i][0] ][ upd[i][1] ] = 0;
		if (IMG[ upd[i][0]+1 ][ upd[i][1] ] == 0)
			IMG[ upd[i][0]+1 ][ upd[i][1] ] = 1;
		else
		    IMG[upd[i][0]-1][upd[i][1]] = 1;
	}

}
