#include "gauss5x5_table.h"


const float Gauss_00[5] = {0, 0.031756401028725, 0.063512802057449, 0.095269203086174, 0.127025604114899};
const float Gauss_01[9] = {0, 0.0375157550304212,	0.0750315100608424,	0.112547265091264,	0.150063020121685,
                           0.187578775152106,	0.225094530182527,	0.262610285212948,	0.300126040243370 };
const float Gauss_02[5] = {0, 0.0396589455082867,	0.0793178910165733,	0.118976836524860,	0.158635782033147 };
const float Gauss_12[5] = {0, 0.0468515082394857,	0.0937030164789714,	0.140554524718457,	0.187406032957943 };
const float Gauss_11[5] = {0, 0.0443196278517048,	0.0886392557034097,	0.132958883555114,	0.177278511406819 };
const float Gauss_22[2] = {0, 0.049528029243823};


const float Gauss[6][9] = {
    {0, 0.0317564010287247,0.0635128020574493,	0.0952692030861740,	0.127025604114899,	0.158782005143623,	0.190538406172348,	0.222294807201073,	0.254051208229797},
    {0, 0.0375157550304212,0.0750315100608424,	0.112547265091264,	0.150063020121685,	0.187578775152106,	0.225094530182527,	0.262610285212948,	0.300126040243370},
    {0, 0.0396589455082867,0.0793178910165733,	0.118976836524860,	0.158635782033147,	0.198294727541433,	0.237953673049720,	0.277612618558007,	0.317271564066293},
    {0, 0.0468515082394857,0.0937030164789714,	0.140554524718457,	0.187406032957943,	0.234257541197428,	0.281109049436914,	0.327960557676400,	0.374812065915885},
    {0, 0.0443196278517048,0.0886392557034097,	0.132958883555114,	0.177278511406819,	0.221598139258524,	0.265917767110229,	0.310237394961934,	0.354557022813639},
    {0, 0.0495280292438231,0.0990560584876463,	0.148584087731469,	0.198112116975293,	0.247640146219116,	0.297168175462939,	0.346696204706762,	0.396224233950585}
};