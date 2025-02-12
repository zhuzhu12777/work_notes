#pragma once
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define I_PIXEL8B(A)	((A< 0)? 0: ((A> 255)? 255:A))
#define I_PIXEL10B(A)	((A< 0)? 0: ((A> 1023)? 1023:A))
#define I_PIXEL12B(A)	((A< 0)? 0: ((A> 4095)? 4095:A))
#define I_PIXEL14B(A)	((A< 0)? 0: ((A> 16383)? 16383:A))
#define I_PIXEL16B(A)	((A< 0)? 0: ((A> 65535)? 65535:A))

#define I_MIN(A,B)		((A<= B)? A: B)
#define I_MAX(A,B)		((A< B)? B: A)
#define I_MED(A,B,C)	((C<A)?((C>B)?C:B):((A>B)?A:B))
#define I_ROUND(A)		((A< 0)? (int)(A- 0.5):(int)(A+ 0.5))
#define I_BINARY(A)		((A>= A/2)?1:0)
#define I_ABS(A)		((A<0)?-1*A:A)

#define MASK_SIZE 5
#define DATA_DEPTH 12

#define DEBUG_IDEAL_GAMMA
#define GAMMA 2.2
#define GRAY_IN_MAX 1024
#define LUM_MAX 65535
#define GRAY_OUT_MAX 1024
//#define CONTRAST_ENHANCEMENT_CURVE_DEBUG 
//#define CONTRAST_ENHANCEMENT_TMP_DEBUG 


//#define DEBUG
typedef struct {
	int EN_EDGE_ENHANCE_EXTERNAL;		// u1.0
	int EN_MIX_RGB;						// u1.0
	int EN_PROTECTION_HIGH;				// u1.0
	int EN_PROTECTION_SMOOTH;			// u1.0
	int EN_PROTECTION_LUM;				// u1.0
	int EN_PROTECTION_SATURATION;		// u1.0
	int EN_GAIN;						// u1.0

	int HACTIVE;						// u13.0
	int VACTIVE;						// u12.0
	int THRESHOLD_SMOOTH;				// u10.0
	int THRESHOLD_LUM;					// u10.0

	int *GAIN;							// u4.8
	int *RATIO;							// u1.7	
	int *UNSHARP_MASK;					// u1.9

}REG;

typedef struct {
	int EN_CONTRAST_ENHANCEMENT_EXTERNAL;	// u1.0
	int UPPER_SETTING;						// u8.0
	int LOWER_SETTING;				        // u8.0
	int CONTENT_GAIN_RATIO;			        // u12.0

	int LENH_GAIN;		                    // u8.0
	int LENH_TARGET;						// u8.4

	int TMP_FILTER_ENABLE;				    // u1.0
	int TMP_CYCLE_NUMBER;					// u4.0

	int INTENSITY_SELECT;			     	// u8.0 
	int GREY_THRESHOLD;					    // u8.2
	int TMP_CYCLE_THRESHOLD;				// u8.0 
	int SATURATION_THRESHOLD;               // u12.0
	int MAX_GAIN_MODE;                      // u1.0

	// LUT
	int *HIGH_HISTOGRAM_CURVE;			    // u2.8
	int *LOW_HISTOGRAM_CURVE;			    // u2.8	

	int *CONTENT_RATIO;			            // u0.9	
	int *LENH_RATIO;					    // u0.9
	int *TEMPORAL_FILTER;					// u0.9

}REG2;

typedef struct {
	int LENH_EXTERNAL;		                // u16.0 it is a input data from SoC 
	int LENH_UPDATE_NUMBER;                 // u8.0
	
}REG3;

typedef struct {
	int	VP_VPROCCTL0;
	int	VP_VPROCCTL1;
	int	VP_VPROCCTL2;
	int	VP_DITH_CTRL;
	int	VP_FRC_CDEPTH;
	int	VP_FRC_CTRL;
	int	VP_CEXP_BAND0;
	int	VP_CEXP_BAND1;
	int	VP_CEXP_BAND2;
	int	VP_FS_START0;
	int	VP_FS_START1;

	int *FRC;
	int *DITHER;
}REG4;


typedef struct {
	int LENH_GLOBAL;                        // u12.0 for each ip use.
	int LENH_COUNT;                         // u8.0  bit
}LENH_PARAM;


// PREVIOUS_FINAL_CURVE[129];                // 12 bit LUT
// FIRST_TEMPORAL_TARGET                     // 10 bit
// TEMPORAL_COUNTER                          // 8 bit
// PREVIOUS_TEMPORAL_TARGET                  // 10 bit


typedef struct {
	int PREVIOUS_ENABLE;                    // u1.0  control bit
	int FIRST_TEMPORAL_TARGET;              // u8.2  bit
	
	int CURRENT_TEMPORAL_TARGET;            // u8.2  bit

	int TEMPORAL_COUNTER;                   // u8.0  bit
	int *PREVIOUS_FINAL_CURVE;              // u2.10 bit
}TEMPORAL;

typedef struct
{
	int column;
	int row;
	int *data_in;
	int *data_contrast;
	int *data_edge;
}IMG;


//Process------------------------------------------------------------------------------------
REG* Register_ParametersSetting_by_edge(char* ftp);
REG2* Register_ParametersSetting_by_contrast(char* ftp);
REG3* Register_ParametersSetting_by_global(char* ftp);
REG4* Register_ParametersSetting_by_cdc(char* ftp);

LENH_PARAM* LENH_CONTROL_PARAM_INITIAL(REG3* reg3);


void Lenh_Control_module(REG3* reg3, LENH_PARAM* lenh_param);

void ContrastEnhancement(REG* reg, REG2* reg2, REG3* reg3, TEMPORAL* temporal, IMG* img, int frame_n, LENH_PARAM* lenh_param);


// no need to care , only for debug
void ContrastEnhancement_debug(REG* reg, REG2* reg2, REG3* reg3, TEMPORAL* temporal, IMG* img, int frame_n, LENH_PARAM* lenh_param,int debug_array[16][1024]);



void Curve_Initial(REG2* reg2, REG3* reg3, TEMPORAL* temporal);
void Curve_Calculate(REG2* reg2, REG3* reg3, IMG* img, TEMPORAL* temporal, LENH_PARAM* lenh_param);

	void Temporal_Filter(REG2* reg2, TEMPORAL* temporal, int* content_target_curve, int* content_temporal_curve);



int interpolation_fix_point(int left_value, int right_value, int gain);
int interpolation_fix_point_6bit(int left_value, int right_value, int gain);
void EdgeEnhancement(REG *reg, REG3* reg3, IMG *img, LENH_PARAM* lenh_param);
	int SearchGain(int Lenh_in, REG *reg);

void FreeMemory(REG *reg, REG2 *reg2, REG3* reg3, REG4* reg4, IMG *img, IMG *img2, TEMPORAL *temporal);




