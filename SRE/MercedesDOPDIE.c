#include "MercedesDOPDIE.h"
#pragma warning(disable : 4996)


void FreeMemory(REG* reg, REG2* reg2, REG3* reg3, REG4* reg4, IMG* img, IMG* img2, TEMPORAL* temporal)
{
	free(reg->GAIN);
	free(reg->RATIO);
	free(reg->UNSHARP_MASK);
	free(reg);

	free(img->data_in);
	free(img->data_contrast);
	free(img->data_edge);
	free(img);

	free(reg2->HIGH_HISTOGRAM_CURVE);
	free(reg2->LOW_HISTOGRAM_CURVE);
	free(reg2->CONTENT_RATIO);
	//free(reg2->LENH_RATIO);
	free(reg2->TEMPORAL_FILTER);
	free(reg2);

	free(reg3);

	free(reg4->DITHER);
	free(reg4->FRC);
	free(reg4);


	free(img2->data_in);
	free(img2->data_contrast);
	free(img2->data_edge);
	free(img2);

	free(temporal->PREVIOUS_FINAL_CURVE);
	//free(temporal->FITTING_CURVE);
	//free(temporal->DEBUG_CURVE);
	free(temporal);

}
LENH_PARAM* LENH_CONTROL_PARAM_INITIAL(REG3* reg3) {

	LENH_PARAM* lenh_param = (LENH_PARAM*)calloc(1, sizeof(LENH_PARAM));
	lenh_param->LENH_COUNT = reg3->LENH_UPDATE_NUMBER;
	lenh_param->LENH_GLOBAL = 0;

	return lenh_param;
};

REG* Register_ParametersSetting_by_edge(char* filename)
{
	REG* reg = (REG*)calloc(1, sizeof(REG));
	reg->RATIO = (int*)calloc(3, sizeof(int));
	reg->GAIN = (int*)calloc(64, sizeof(int));
	reg->UNSHARP_MASK = (int*)calloc(MASK_SIZE * MASK_SIZE, sizeof(int));

	char buf[128];
	FILE* pFile;

	if ((pFile = fopen(filename, "rt")) == NULL)
	{
		printf("Open REG File Error\n");
		system("pause");
	}
	else
	{
		while (fgets(buf, 128, pFile))
		{
			if (strstr(buf, "EN_EDGE_ENHANCE_EXTERNAL"))		reg->EN_EDGE_ENHANCE_EXTERNAL = atoi(strstr(strstr(buf, "EN_EDGE_ENHANCE_EXTERNAL"), ",") + 1);
			else if (strstr(buf, "EN_MIX_RGB"))					reg->EN_MIX_RGB = atoi(strstr(strstr(buf, "EN_MIX_RGB"), ",") + 1);
			else if (strstr(buf, "EN_PROTECTION_HIGH"))			reg->EN_PROTECTION_HIGH = atoi(strstr(strstr(buf, "EN_PROTECTION_HIGH"), ",") + 1);
			else if (strstr(buf, "EN_PROTECTION_SMOOTH"))		reg->EN_PROTECTION_SMOOTH = atoi(strstr(strstr(buf, "EN_PROTECTION_SMOOTH"), ",") + 1);
			else if (strstr(buf, "EN_PROTECTION_LUM"))			reg->EN_PROTECTION_LUM = atoi(strstr(strstr(buf, "EN_PROTECTION_LUM"), ",") + 1);
			else if (strstr(buf, "EN_PROTECTION_SATURATION"))	reg->EN_PROTECTION_SATURATION = atoi(strstr(strstr(buf, "EN_PROTECTION_SATURATION"), ",") + 1);
			else if (strstr(buf, "EN_GAIN"))					reg->EN_GAIN = atoi(strstr(strstr(buf, "EN_GAIN"), ",") + 1);

			else if (strstr(buf, "HACTIVE"))					reg->HACTIVE = atoi(strstr(strstr(buf, "HACTIVE"), ",") + 1);
			else if (strstr(buf, "VACTIVE"))					reg->VACTIVE = atoi(strstr(strstr(buf, "VACTIVE"), ",") + 1);
			else if (strstr(buf, "RATIO_R"))					reg->RATIO[0] = atoi(strstr(strstr(buf, "RATIO_R"), ",") + 1);
			else if (strstr(buf, "RATIO_G"))					reg->RATIO[1] = atoi(strstr(strstr(buf, "RATIO_G"), ",") + 1);
			else if (strstr(buf, "RATIO_B"))					reg->RATIO[2] = atoi(strstr(strstr(buf, "RATIO_B"), ",") + 1);
			else if (strstr(buf, "THRESHOLD_SMOOTH"))			reg->THRESHOLD_SMOOTH = atoi(strstr(strstr(buf, "THRESHOLD_SMOOTH"), ",") + 1);
			else if (strstr(buf, "THRESHOLD_LUM"))				reg->THRESHOLD_LUM = atoi(strstr(strstr(buf, "THRESHOLD_LUM"), ",") + 1);

			else if (strstr(buf, "GAIN_00"))					reg->GAIN[0] = atoi(strstr(strstr(buf, "GAIN_00"), ",") + 1);
			else if (strstr(buf, "GAIN_01"))					reg->GAIN[1] = atoi(strstr(strstr(buf, "GAIN_01"), ",") + 1);
			else if (strstr(buf, "GAIN_02"))					reg->GAIN[2] = atoi(strstr(strstr(buf, "GAIN_02"), ",") + 1);
			else if (strstr(buf, "GAIN_03"))					reg->GAIN[3] = atoi(strstr(strstr(buf, "GAIN_03"), ",") + 1);
			else if (strstr(buf, "GAIN_04"))					reg->GAIN[4] = atoi(strstr(strstr(buf, "GAIN_04"), ",") + 1);
			else if (strstr(buf, "GAIN_05"))					reg->GAIN[5] = atoi(strstr(strstr(buf, "GAIN_05"), ",") + 1);
			else if (strstr(buf, "GAIN_06"))					reg->GAIN[6] = atoi(strstr(strstr(buf, "GAIN_06"), ",") + 1);
			else if (strstr(buf, "GAIN_07"))					reg->GAIN[7] = atoi(strstr(strstr(buf, "GAIN_07"), ",") + 1);
			else if (strstr(buf, "GAIN_08"))					reg->GAIN[8] = atoi(strstr(strstr(buf, "GAIN_08"), ",") + 1);
			else if (strstr(buf, "GAIN_09"))					reg->GAIN[9] = atoi(strstr(strstr(buf, "GAIN_09"), ",") + 1);
			else if (strstr(buf, "GAIN_10"))					reg->GAIN[10] = atoi(strstr(strstr(buf, "GAIN_10"), ",") + 1);
			else if (strstr(buf, "GAIN_11"))					reg->GAIN[11] = atoi(strstr(strstr(buf, "GAIN_11"), ",") + 1);
			else if (strstr(buf, "GAIN_12"))					reg->GAIN[12] = atoi(strstr(strstr(buf, "GAIN_12"), ",") + 1);
			else if (strstr(buf, "GAIN_13"))					reg->GAIN[13] = atoi(strstr(strstr(buf, "GAIN_13"), ",") + 1);
			else if (strstr(buf, "GAIN_14"))					reg->GAIN[14] = atoi(strstr(strstr(buf, "GAIN_14"), ",") + 1);
			else if (strstr(buf, "GAIN_15"))					reg->GAIN[15] = atoi(strstr(strstr(buf, "GAIN_15"), ",") + 1);
			else if (strstr(buf, "GAIN_16"))					reg->GAIN[16] = atoi(strstr(strstr(buf, "GAIN_16"), ",") + 1);
			else if (strstr(buf, "GAIN_17"))					reg->GAIN[17] = atoi(strstr(strstr(buf, "GAIN_17"), ",") + 1);
			else if (strstr(buf, "GAIN_18"))					reg->GAIN[18] = atoi(strstr(strstr(buf, "GAIN_18"), ",") + 1);
			else if (strstr(buf, "GAIN_19"))					reg->GAIN[19] = atoi(strstr(strstr(buf, "GAIN_19"), ",") + 1);
			else if (strstr(buf, "GAIN_20"))					reg->GAIN[20] = atoi(strstr(strstr(buf, "GAIN_20"), ",") + 1);
			else if (strstr(buf, "GAIN_21"))					reg->GAIN[21] = atoi(strstr(strstr(buf, "GAIN_21"), ",") + 1);
			else if (strstr(buf, "GAIN_22"))					reg->GAIN[22] = atoi(strstr(strstr(buf, "GAIN_22"), ",") + 1);
			else if (strstr(buf, "GAIN_23"))					reg->GAIN[23] = atoi(strstr(strstr(buf, "GAIN_23"), ",") + 1);
			else if (strstr(buf, "GAIN_24"))					reg->GAIN[24] = atoi(strstr(strstr(buf, "GAIN_24"), ",") + 1);
			else if (strstr(buf, "GAIN_25"))					reg->GAIN[25] = atoi(strstr(strstr(buf, "GAIN_25"), ",") + 1);
			else if (strstr(buf, "GAIN_26"))					reg->GAIN[26] = atoi(strstr(strstr(buf, "GAIN_26"), ",") + 1);
			else if (strstr(buf, "GAIN_27"))					reg->GAIN[27] = atoi(strstr(strstr(buf, "GAIN_27"), ",") + 1);
			else if (strstr(buf, "GAIN_28"))					reg->GAIN[28] = atoi(strstr(strstr(buf, "GAIN_28"), ",") + 1);
			else if (strstr(buf, "GAIN_29"))					reg->GAIN[29] = atoi(strstr(strstr(buf, "GAIN_29"), ",") + 1);
			else if (strstr(buf, "GAIN_30"))					reg->GAIN[30] = atoi(strstr(strstr(buf, "GAIN_30"), ",") + 1);
			else if (strstr(buf, "GAIN_31"))					reg->GAIN[31] = atoi(strstr(strstr(buf, "GAIN_31"), ",") + 1);
			else if (strstr(buf, "GAIN_32"))					reg->GAIN[32] = atoi(strstr(strstr(buf, "GAIN_32"), ",") + 1);
			else if (strstr(buf, "GAIN_33"))					reg->GAIN[33] = atoi(strstr(strstr(buf, "GAIN_33"), ",") + 1);
			else if (strstr(buf, "GAIN_34"))					reg->GAIN[34] = atoi(strstr(strstr(buf, "GAIN_34"), ",") + 1);
			else if (strstr(buf, "GAIN_35"))					reg->GAIN[35] = atoi(strstr(strstr(buf, "GAIN_35"), ",") + 1);
			else if (strstr(buf, "GAIN_36"))					reg->GAIN[36] = atoi(strstr(strstr(buf, "GAIN_36"), ",") + 1);
			else if (strstr(buf, "GAIN_37"))					reg->GAIN[37] = atoi(strstr(strstr(buf, "GAIN_37"), ",") + 1);
			else if (strstr(buf, "GAIN_38"))					reg->GAIN[38] = atoi(strstr(strstr(buf, "GAIN_38"), ",") + 1);
			else if (strstr(buf, "GAIN_39"))					reg->GAIN[39] = atoi(strstr(strstr(buf, "GAIN_39"), ",") + 1);
			else if (strstr(buf, "GAIN_40"))					reg->GAIN[40] = atoi(strstr(strstr(buf, "GAIN_40"), ",") + 1);
			else if (strstr(buf, "GAIN_41"))					reg->GAIN[41] = atoi(strstr(strstr(buf, "GAIN_41"), ",") + 1);
			else if (strstr(buf, "GAIN_42"))					reg->GAIN[42] = atoi(strstr(strstr(buf, "GAIN_42"), ",") + 1);
			else if (strstr(buf, "GAIN_43"))					reg->GAIN[43] = atoi(strstr(strstr(buf, "GAIN_43"), ",") + 1);
			else if (strstr(buf, "GAIN_44"))					reg->GAIN[44] = atoi(strstr(strstr(buf, "GAIN_44"), ",") + 1);
			else if (strstr(buf, "GAIN_45"))					reg->GAIN[45] = atoi(strstr(strstr(buf, "GAIN_45"), ",") + 1);
			else if (strstr(buf, "GAIN_46"))					reg->GAIN[46] = atoi(strstr(strstr(buf, "GAIN_46"), ",") + 1);
			else if (strstr(buf, "GAIN_47"))					reg->GAIN[47] = atoi(strstr(strstr(buf, "GAIN_47"), ",") + 1);
			else if (strstr(buf, "GAIN_48"))					reg->GAIN[48] = atoi(strstr(strstr(buf, "GAIN_48"), ",") + 1);
			else if (strstr(buf, "GAIN_49"))					reg->GAIN[49] = atoi(strstr(strstr(buf, "GAIN_49"), ",") + 1);
			else if (strstr(buf, "GAIN_50"))					reg->GAIN[50] = atoi(strstr(strstr(buf, "GAIN_50"), ",") + 1);
			else if (strstr(buf, "GAIN_51"))					reg->GAIN[51] = atoi(strstr(strstr(buf, "GAIN_51"), ",") + 1);
			else if (strstr(buf, "GAIN_52"))					reg->GAIN[52] = atoi(strstr(strstr(buf, "GAIN_52"), ",") + 1);
			else if (strstr(buf, "GAIN_53"))					reg->GAIN[53] = atoi(strstr(strstr(buf, "GAIN_53"), ",") + 1);
			else if (strstr(buf, "GAIN_54"))					reg->GAIN[54] = atoi(strstr(strstr(buf, "GAIN_54"), ",") + 1);
			else if (strstr(buf, "GAIN_55"))					reg->GAIN[55] = atoi(strstr(strstr(buf, "GAIN_55"), ",") + 1);
			else if (strstr(buf, "GAIN_56"))					reg->GAIN[56] = atoi(strstr(strstr(buf, "GAIN_56"), ",") + 1);
			else if (strstr(buf, "GAIN_57"))					reg->GAIN[57] = atoi(strstr(strstr(buf, "GAIN_57"), ",") + 1);
			else if (strstr(buf, "GAIN_58"))					reg->GAIN[58] = atoi(strstr(strstr(buf, "GAIN_58"), ",") + 1);
			else if (strstr(buf, "GAIN_59"))					reg->GAIN[59] = atoi(strstr(strstr(buf, "GAIN_59"), ",") + 1);
			else if (strstr(buf, "GAIN_60"))					reg->GAIN[60] = atoi(strstr(strstr(buf, "GAIN_60"), ",") + 1);
			else if (strstr(buf, "GAIN_61"))					reg->GAIN[61] = atoi(strstr(strstr(buf, "GAIN_61"), ",") + 1);
			else if (strstr(buf, "GAIN_62"))					reg->GAIN[62] = atoi(strstr(strstr(buf, "GAIN_62"), ",") + 1);
			else if (strstr(buf, "GAIN_63"))					reg->GAIN[63] = atoi(strstr(strstr(buf, "GAIN_63"), ",") + 1);

			else if (strstr(buf, "UNSHARP_MASK_00"))			reg->UNSHARP_MASK[0] = atoi(strstr(strstr(buf, "UNSHARP_MASK_00"), ",") + 1);
			else if (strstr(buf, "UNSHARP_MASK_01"))			reg->UNSHARP_MASK[1] = atoi(strstr(strstr(buf, "UNSHARP_MASK_01"), ",") + 1);
			else if (strstr(buf, "UNSHARP_MASK_02"))			reg->UNSHARP_MASK[2] = atoi(strstr(strstr(buf, "UNSHARP_MASK_02"), ",") + 1);
			else if (strstr(buf, "UNSHARP_MASK_03"))			reg->UNSHARP_MASK[3] = atoi(strstr(strstr(buf, "UNSHARP_MASK_03"), ",") + 1);
			else if (strstr(buf, "UNSHARP_MASK_04"))			reg->UNSHARP_MASK[4] = atoi(strstr(strstr(buf, "UNSHARP_MASK_04"), ",") + 1);
			else if (strstr(buf, "UNSHARP_MASK_05"))			reg->UNSHARP_MASK[5] = atoi(strstr(strstr(buf, "UNSHARP_MASK_05"), ",") + 1);
			else if (strstr(buf, "UNSHARP_MASK_06"))			reg->UNSHARP_MASK[6] = atoi(strstr(strstr(buf, "UNSHARP_MASK_06"), ",") + 1);
			else if (strstr(buf, "UNSHARP_MASK_07"))			reg->UNSHARP_MASK[7] = atoi(strstr(strstr(buf, "UNSHARP_MASK_07"), ",") + 1);
			else if (strstr(buf, "UNSHARP_MASK_08"))			reg->UNSHARP_MASK[8] = atoi(strstr(strstr(buf, "UNSHARP_MASK_08"), ",") + 1);
			else if (strstr(buf, "UNSHARP_MASK_09"))			reg->UNSHARP_MASK[9] = atoi(strstr(strstr(buf, "UNSHARP_MASK_09"), ",") + 1);
			else if (strstr(buf, "UNSHARP_MASK_10"))			reg->UNSHARP_MASK[10] = atoi(strstr(strstr(buf, "UNSHARP_MASK_10"), ",") + 1);
			else if (strstr(buf, "UNSHARP_MASK_11"))			reg->UNSHARP_MASK[11] = atoi(strstr(strstr(buf, "UNSHARP_MASK_11"), ",") + 1);
			else if (strstr(buf, "UNSHARP_MASK_12"))			reg->UNSHARP_MASK[12] = atoi(strstr(strstr(buf, "UNSHARP_MASK_12"), ",") + 1);
			else if (strstr(buf, "UNSHARP_MASK_13"))			reg->UNSHARP_MASK[13] = atoi(strstr(strstr(buf, "UNSHARP_MASK_13"), ",") + 1);
			else if (strstr(buf, "UNSHARP_MASK_14"))			reg->UNSHARP_MASK[14] = atoi(strstr(strstr(buf, "UNSHARP_MASK_14"), ",") + 1);
			else if (strstr(buf, "UNSHARP_MASK_15"))			reg->UNSHARP_MASK[15] = atoi(strstr(strstr(buf, "UNSHARP_MASK_15"), ",") + 1);
			else if (strstr(buf, "UNSHARP_MASK_16"))			reg->UNSHARP_MASK[16] = atoi(strstr(strstr(buf, "UNSHARP_MASK_16"), ",") + 1);
			else if (strstr(buf, "UNSHARP_MASK_17"))			reg->UNSHARP_MASK[17] = atoi(strstr(strstr(buf, "UNSHARP_MASK_17"), ",") + 1);
			else if (strstr(buf, "UNSHARP_MASK_18"))			reg->UNSHARP_MASK[18] = atoi(strstr(strstr(buf, "UNSHARP_MASK_18"), ",") + 1);
			else if (strstr(buf, "UNSHARP_MASK_19"))			reg->UNSHARP_MASK[19] = atoi(strstr(strstr(buf, "UNSHARP_MASK_19"), ",") + 1);
			else if (strstr(buf, "UNSHARP_MASK_20"))			reg->UNSHARP_MASK[20] = atoi(strstr(strstr(buf, "UNSHARP_MASK_20"), ",") + 1);
			else if (strstr(buf, "UNSHARP_MASK_21"))			reg->UNSHARP_MASK[21] = atoi(strstr(strstr(buf, "UNSHARP_MASK_21"), ",") + 1);
			else if (strstr(buf, "UNSHARP_MASK_22"))			reg->UNSHARP_MASK[22] = atoi(strstr(strstr(buf, "UNSHARP_MASK_22"), ",") + 1);
			else if (strstr(buf, "UNSHARP_MASK_23"))			reg->UNSHARP_MASK[23] = atoi(strstr(strstr(buf, "UNSHARP_MASK_23"), ",") + 1);
			else if (strstr(buf, "UNSHARP_MASK_24"))			reg->UNSHARP_MASK[24] = atoi(strstr(strstr(buf, "UNSHARP_MASK_24"), ",") + 1);
			else;
		}
		fclose(pFile);

	}

	return reg;
}

REG2* Register_ParametersSetting_by_contrast(char* filename)
{
	REG2* reg2 = (REG2*)calloc(1, sizeof(REG2));

	reg2->HIGH_HISTOGRAM_CURVE = (int*)calloc(128, sizeof(int));
	reg2->LOW_HISTOGRAM_CURVE = (int*)calloc(128, sizeof(int));
	reg2->CONTENT_RATIO = (int*)calloc(33, sizeof(int));
	reg2->LENH_RATIO = (int*)calloc(63, sizeof(int));
	reg2->TEMPORAL_FILTER = (int*)calloc(32, sizeof(int));

	char buf[256];
	FILE* pFile;

	if ((pFile = fopen(filename, "rt")) == NULL)
	{
		printf("Open REG File Error\n");
		system("pause");
	}
	else
	{
		while (fgets(buf, 256, pFile))
		{
			if (strstr(buf, "EN_CONTRAST_ENHANCEMENT_EXTERNAL"))		reg2->EN_CONTRAST_ENHANCEMENT_EXTERNAL = atoi(strstr(strstr(buf, "EN_CONTRAST_ENHANCEMENT_EXTERNAL"), ",") + 1);
			else if (strstr(buf, "UPPER_SETTING"))					    reg2->UPPER_SETTING = atoi(strstr(strstr(buf, "UPPER_SETTING"), ",") + 1);
			else if (strstr(buf, "LOWER_SETTING"))		 	            reg2->LOWER_SETTING = atoi(strstr(strstr(buf, "LOWER_SETTING"), ",") + 1);
			else if (strstr(buf, "CONTENT_GAIN_RATIO"))		            reg2->CONTENT_GAIN_RATIO = atoi(strstr(strstr(buf, "CONTENT_GAIN_RATIO"), ",") + 1);

			else if (strstr(buf, "LENH_GAIN"))			                reg2->LENH_GAIN = atoi(strstr(strstr(buf, "LENH_GAIN"), ",") + 1);
			else if (strstr(buf, "LENH_TARGET"))	                    reg2->LENH_TARGET = atoi(strstr(strstr(buf, "LENH_TARGET"), ",") + 1);
			else if (strstr(buf, "TMP_FILTER_ENABLE"))					reg2->TMP_FILTER_ENABLE = atoi(strstr(strstr(buf, "TMP_FILTER_ENABLE"), ",") + 1);

			else if (strstr(buf, "TMP_CYCLE_NUMBER"))					reg2->TMP_CYCLE_NUMBER = atoi(strstr(strstr(buf, "TMP_CYCLE_NUMBER"), ",") + 1);

			else if (strstr(buf, "INTENSITY_SELECT"))			        reg2->INTENSITY_SELECT = atoi(strstr(strstr(buf, "INTENSITY_SELECT"), ",") + 1);
			else if (strstr(buf, "GREY_THRESHOLD"))					    reg2->GREY_THRESHOLD = atoi(strstr(strstr(buf, "GREY_THRESHOLD"), ",") + 1);
			else if (strstr(buf, "TMP_CYCLE_THRESHOLD"))			    reg2->TMP_CYCLE_THRESHOLD = atoi(strstr(strstr(buf, "TMP_CYCLE_THRESHOLD"), ",") + 1);

			else if (strstr(buf, "SATURATION_THRESHOLD"))			    reg2->SATURATION_THRESHOLD = atoi(strstr(strstr(buf, "SATURATION_THRESHOLD"), ",") + 1);
			else if (strstr(buf, "MAX_GAIN_MODE"))			            reg2->MAX_GAIN_MODE = atoi(strstr(strstr(buf, "MAX_GAIN_MODE"), ",") + 1);

			else;
		}
	}
	fclose(pFile);


	if ((pFile = fopen(filename, "rt")) == NULL)
	{
		printf("Open REG File Error\n");
		system("pause");
	}
	else
	{
		while (fgets(buf, 256, pFile))
		{
			if (strstr(buf, "HIGH_HISTOGRAM_CURVE_000"))					    reg2->HIGH_HISTOGRAM_CURVE[0] = atoi(strstr(strstr(buf, "HIGH_HISTOGRAM_CURVE_000"), ",") + 1);
			else if (strstr(buf, "HIGH_HISTOGRAM_CURVE_001"))					reg2->HIGH_HISTOGRAM_CURVE[1] = atoi(strstr(strstr(buf, "HIGH_HISTOGRAM_CURVE_001"), ",") + 1);
			else if (strstr(buf, "HIGH_HISTOGRAM_CURVE_002"))					reg2->HIGH_HISTOGRAM_CURVE[2] = atoi(strstr(strstr(buf, "HIGH_HISTOGRAM_CURVE_002"), ",") + 1);
			else if (strstr(buf, "HIGH_HISTOGRAM_CURVE_003"))					reg2->HIGH_HISTOGRAM_CURVE[3] = atoi(strstr(strstr(buf, "HIGH_HISTOGRAM_CURVE_003"), ",") + 1);
			else if (strstr(buf, "HIGH_HISTOGRAM_CURVE_004"))					reg2->HIGH_HISTOGRAM_CURVE[4] = atoi(strstr(strstr(buf, "HIGH_HISTOGRAM_CURVE_004"), ",") + 1);
			else if (strstr(buf, "HIGH_HISTOGRAM_CURVE_005"))					reg2->HIGH_HISTOGRAM_CURVE[5] = atoi(strstr(strstr(buf, "HIGH_HISTOGRAM_CURVE_005"), ",") + 1);
			else if (strstr(buf, "HIGH_HISTOGRAM_CURVE_006"))					reg2->HIGH_HISTOGRAM_CURVE[6] = atoi(strstr(strstr(buf, "HIGH_HISTOGRAM_CURVE_006"), ",") + 1);
			else if (strstr(buf, "HIGH_HISTOGRAM_CURVE_007"))					reg2->HIGH_HISTOGRAM_CURVE[7] = atoi(strstr(strstr(buf, "HIGH_HISTOGRAM_CURVE_007"), ",") + 1);
			else if (strstr(buf, "HIGH_HISTOGRAM_CURVE_008"))					reg2->HIGH_HISTOGRAM_CURVE[8] = atoi(strstr(strstr(buf, "HIGH_HISTOGRAM_CURVE_008"), ",") + 1);
			else if (strstr(buf, "HIGH_HISTOGRAM_CURVE_009"))					reg2->HIGH_HISTOGRAM_CURVE[9] = atoi(strstr(strstr(buf, "HIGH_HISTOGRAM_CURVE_009"), ",") + 1);
			else if (strstr(buf, "HIGH_HISTOGRAM_CURVE_010"))					reg2->HIGH_HISTOGRAM_CURVE[10] = atoi(strstr(strstr(buf, "HIGH_HISTOGRAM_CURVE_010"), ",") + 1);
			else if (strstr(buf, "HIGH_HISTOGRAM_CURVE_011"))					reg2->HIGH_HISTOGRAM_CURVE[11] = atoi(strstr(strstr(buf, "HIGH_HISTOGRAM_CURVE_011"), ",") + 1);
			else if (strstr(buf, "HIGH_HISTOGRAM_CURVE_012"))					reg2->HIGH_HISTOGRAM_CURVE[12] = atoi(strstr(strstr(buf, "HIGH_HISTOGRAM_CURVE_012"), ",") + 1);
			else if (strstr(buf, "HIGH_HISTOGRAM_CURVE_013"))					reg2->HIGH_HISTOGRAM_CURVE[13] = atoi(strstr(strstr(buf, "HIGH_HISTOGRAM_CURVE_013"), ",") + 1);
			else if (strstr(buf, "HIGH_HISTOGRAM_CURVE_014"))					reg2->HIGH_HISTOGRAM_CURVE[14] = atoi(strstr(strstr(buf, "HIGH_HISTOGRAM_CURVE_014"), ",") + 1);
			else if (strstr(buf, "HIGH_HISTOGRAM_CURVE_015"))					reg2->HIGH_HISTOGRAM_CURVE[15] = atoi(strstr(strstr(buf, "HIGH_HISTOGRAM_CURVE_015"), ",") + 1);
			else if (strstr(buf, "HIGH_HISTOGRAM_CURVE_016"))					reg2->HIGH_HISTOGRAM_CURVE[16] = atoi(strstr(strstr(buf, "HIGH_HISTOGRAM_CURVE_016"), ",") + 1);
			else if (strstr(buf, "HIGH_HISTOGRAM_CURVE_017"))					reg2->HIGH_HISTOGRAM_CURVE[17] = atoi(strstr(strstr(buf, "HIGH_HISTOGRAM_CURVE_017"), ",") + 1);
			else if (strstr(buf, "HIGH_HISTOGRAM_CURVE_018"))					reg2->HIGH_HISTOGRAM_CURVE[18] = atoi(strstr(strstr(buf, "HIGH_HISTOGRAM_CURVE_018"), ",") + 1);
			else if (strstr(buf, "HIGH_HISTOGRAM_CURVE_019"))					reg2->HIGH_HISTOGRAM_CURVE[19] = atoi(strstr(strstr(buf, "HIGH_HISTOGRAM_CURVE_019"), ",") + 1);
			else if (strstr(buf, "HIGH_HISTOGRAM_CURVE_020"))					reg2->HIGH_HISTOGRAM_CURVE[20] = atoi(strstr(strstr(buf, "HIGH_HISTOGRAM_CURVE_020"), ",") + 1);
			else if (strstr(buf, "HIGH_HISTOGRAM_CURVE_021"))					reg2->HIGH_HISTOGRAM_CURVE[21] = atoi(strstr(strstr(buf, "HIGH_HISTOGRAM_CURVE_021"), ",") + 1);
			else if (strstr(buf, "HIGH_HISTOGRAM_CURVE_022"))					reg2->HIGH_HISTOGRAM_CURVE[22] = atoi(strstr(strstr(buf, "HIGH_HISTOGRAM_CURVE_022"), ",") + 1);
			else if (strstr(buf, "HIGH_HISTOGRAM_CURVE_023"))					reg2->HIGH_HISTOGRAM_CURVE[23] = atoi(strstr(strstr(buf, "HIGH_HISTOGRAM_CURVE_023"), ",") + 1);
			else if (strstr(buf, "HIGH_HISTOGRAM_CURVE_024"))					reg2->HIGH_HISTOGRAM_CURVE[24] = atoi(strstr(strstr(buf, "HIGH_HISTOGRAM_CURVE_024"), ",") + 1);
			else if (strstr(buf, "HIGH_HISTOGRAM_CURVE_025"))					reg2->HIGH_HISTOGRAM_CURVE[25] = atoi(strstr(strstr(buf, "HIGH_HISTOGRAM_CURVE_025"), ",") + 1);
			else if (strstr(buf, "HIGH_HISTOGRAM_CURVE_026"))					reg2->HIGH_HISTOGRAM_CURVE[26] = atoi(strstr(strstr(buf, "HIGH_HISTOGRAM_CURVE_026"), ",") + 1);
			else if (strstr(buf, "HIGH_HISTOGRAM_CURVE_027"))					reg2->HIGH_HISTOGRAM_CURVE[27] = atoi(strstr(strstr(buf, "HIGH_HISTOGRAM_CURVE_027"), ",") + 1);
			else if (strstr(buf, "HIGH_HISTOGRAM_CURVE_028"))					reg2->HIGH_HISTOGRAM_CURVE[28] = atoi(strstr(strstr(buf, "HIGH_HISTOGRAM_CURVE_028"), ",") + 1);
			else if (strstr(buf, "HIGH_HISTOGRAM_CURVE_029"))					reg2->HIGH_HISTOGRAM_CURVE[29] = atoi(strstr(strstr(buf, "HIGH_HISTOGRAM_CURVE_029"), ",") + 1);
			else if (strstr(buf, "HIGH_HISTOGRAM_CURVE_030"))					reg2->HIGH_HISTOGRAM_CURVE[30] = atoi(strstr(strstr(buf, "HIGH_HISTOGRAM_CURVE_030"), ",") + 1);
			else if (strstr(buf, "HIGH_HISTOGRAM_CURVE_031"))					reg2->HIGH_HISTOGRAM_CURVE[31] = atoi(strstr(strstr(buf, "HIGH_HISTOGRAM_CURVE_031"), ",") + 1);
			else if (strstr(buf, "HIGH_HISTOGRAM_CURVE_032"))					reg2->HIGH_HISTOGRAM_CURVE[32] = atoi(strstr(strstr(buf, "HIGH_HISTOGRAM_CURVE_032"), ",") + 1);
			else if (strstr(buf, "HIGH_HISTOGRAM_CURVE_033"))					reg2->HIGH_HISTOGRAM_CURVE[33] = atoi(strstr(strstr(buf, "HIGH_HISTOGRAM_CURVE_033"), ",") + 1);
			else if (strstr(buf, "HIGH_HISTOGRAM_CURVE_034"))					reg2->HIGH_HISTOGRAM_CURVE[34] = atoi(strstr(strstr(buf, "HIGH_HISTOGRAM_CURVE_034"), ",") + 1);
			else if (strstr(buf, "HIGH_HISTOGRAM_CURVE_035"))					reg2->HIGH_HISTOGRAM_CURVE[35] = atoi(strstr(strstr(buf, "HIGH_HISTOGRAM_CURVE_035"), ",") + 1);
			else if (strstr(buf, "HIGH_HISTOGRAM_CURVE_036"))					reg2->HIGH_HISTOGRAM_CURVE[36] = atoi(strstr(strstr(buf, "HIGH_HISTOGRAM_CURVE_036"), ",") + 1);
			else if (strstr(buf, "HIGH_HISTOGRAM_CURVE_037"))					reg2->HIGH_HISTOGRAM_CURVE[37] = atoi(strstr(strstr(buf, "HIGH_HISTOGRAM_CURVE_037"), ",") + 1);
			else if (strstr(buf, "HIGH_HISTOGRAM_CURVE_038"))					reg2->HIGH_HISTOGRAM_CURVE[38] = atoi(strstr(strstr(buf, "HIGH_HISTOGRAM_CURVE_038"), ",") + 1);
			else if (strstr(buf, "HIGH_HISTOGRAM_CURVE_039"))					reg2->HIGH_HISTOGRAM_CURVE[39] = atoi(strstr(strstr(buf, "HIGH_HISTOGRAM_CURVE_039"), ",") + 1);
			else if (strstr(buf, "HIGH_HISTOGRAM_CURVE_040"))					reg2->HIGH_HISTOGRAM_CURVE[40] = atoi(strstr(strstr(buf, "HIGH_HISTOGRAM_CURVE_040"), ",") + 1);
			else if (strstr(buf, "HIGH_HISTOGRAM_CURVE_041"))					reg2->HIGH_HISTOGRAM_CURVE[41] = atoi(strstr(strstr(buf, "HIGH_HISTOGRAM_CURVE_041"), ",") + 1);
			else if (strstr(buf, "HIGH_HISTOGRAM_CURVE_042"))					reg2->HIGH_HISTOGRAM_CURVE[42] = atoi(strstr(strstr(buf, "HIGH_HISTOGRAM_CURVE_042"), ",") + 1);
			else if (strstr(buf, "HIGH_HISTOGRAM_CURVE_043"))					reg2->HIGH_HISTOGRAM_CURVE[43] = atoi(strstr(strstr(buf, "HIGH_HISTOGRAM_CURVE_043"), ",") + 1);
			else if (strstr(buf, "HIGH_HISTOGRAM_CURVE_044"))					reg2->HIGH_HISTOGRAM_CURVE[44] = atoi(strstr(strstr(buf, "HIGH_HISTOGRAM_CURVE_044"), ",") + 1);
			else if (strstr(buf, "HIGH_HISTOGRAM_CURVE_045"))					reg2->HIGH_HISTOGRAM_CURVE[45] = atoi(strstr(strstr(buf, "HIGH_HISTOGRAM_CURVE_045"), ",") + 1);
			else if (strstr(buf, "HIGH_HISTOGRAM_CURVE_046"))					reg2->HIGH_HISTOGRAM_CURVE[46] = atoi(strstr(strstr(buf, "HIGH_HISTOGRAM_CURVE_046"), ",") + 1);
			else if (strstr(buf, "HIGH_HISTOGRAM_CURVE_047"))					reg2->HIGH_HISTOGRAM_CURVE[47] = atoi(strstr(strstr(buf, "HIGH_HISTOGRAM_CURVE_047"), ",") + 1);
			else if (strstr(buf, "HIGH_HISTOGRAM_CURVE_048"))					reg2->HIGH_HISTOGRAM_CURVE[48] = atoi(strstr(strstr(buf, "HIGH_HISTOGRAM_CURVE_048"), ",") + 1);
			else if (strstr(buf, "HIGH_HISTOGRAM_CURVE_049"))					reg2->HIGH_HISTOGRAM_CURVE[49] = atoi(strstr(strstr(buf, "HIGH_HISTOGRAM_CURVE_049"), ",") + 1);
			else if (strstr(buf, "HIGH_HISTOGRAM_CURVE_050"))					reg2->HIGH_HISTOGRAM_CURVE[50] = atoi(strstr(strstr(buf, "HIGH_HISTOGRAM_CURVE_050"), ",") + 1);
			else if (strstr(buf, "HIGH_HISTOGRAM_CURVE_051"))					reg2->HIGH_HISTOGRAM_CURVE[51] = atoi(strstr(strstr(buf, "HIGH_HISTOGRAM_CURVE_051"), ",") + 1);
			else if (strstr(buf, "HIGH_HISTOGRAM_CURVE_052"))					reg2->HIGH_HISTOGRAM_CURVE[52] = atoi(strstr(strstr(buf, "HIGH_HISTOGRAM_CURVE_052"), ",") + 1);
			else if (strstr(buf, "HIGH_HISTOGRAM_CURVE_053"))					reg2->HIGH_HISTOGRAM_CURVE[53] = atoi(strstr(strstr(buf, "HIGH_HISTOGRAM_CURVE_053"), ",") + 1);
			else if (strstr(buf, "HIGH_HISTOGRAM_CURVE_054"))					reg2->HIGH_HISTOGRAM_CURVE[54] = atoi(strstr(strstr(buf, "HIGH_HISTOGRAM_CURVE_054"), ",") + 1);
			else if (strstr(buf, "HIGH_HISTOGRAM_CURVE_055"))					reg2->HIGH_HISTOGRAM_CURVE[55] = atoi(strstr(strstr(buf, "HIGH_HISTOGRAM_CURVE_055"), ",") + 1);
			else if (strstr(buf, "HIGH_HISTOGRAM_CURVE_056"))					reg2->HIGH_HISTOGRAM_CURVE[56] = atoi(strstr(strstr(buf, "HIGH_HISTOGRAM_CURVE_056"), ",") + 1);
			else if (strstr(buf, "HIGH_HISTOGRAM_CURVE_057"))					reg2->HIGH_HISTOGRAM_CURVE[57] = atoi(strstr(strstr(buf, "HIGH_HISTOGRAM_CURVE_057"), ",") + 1);
			else if (strstr(buf, "HIGH_HISTOGRAM_CURVE_058"))					reg2->HIGH_HISTOGRAM_CURVE[58] = atoi(strstr(strstr(buf, "HIGH_HISTOGRAM_CURVE_058"), ",") + 1);
			else if (strstr(buf, "HIGH_HISTOGRAM_CURVE_059"))					reg2->HIGH_HISTOGRAM_CURVE[59] = atoi(strstr(strstr(buf, "HIGH_HISTOGRAM_CURVE_059"), ",") + 1);
			else if (strstr(buf, "HIGH_HISTOGRAM_CURVE_060"))					reg2->HIGH_HISTOGRAM_CURVE[60] = atoi(strstr(strstr(buf, "HIGH_HISTOGRAM_CURVE_060"), ",") + 1);
			else if (strstr(buf, "HIGH_HISTOGRAM_CURVE_061"))					reg2->HIGH_HISTOGRAM_CURVE[61] = atoi(strstr(strstr(buf, "HIGH_HISTOGRAM_CURVE_061"), ",") + 1);
			else if (strstr(buf, "HIGH_HISTOGRAM_CURVE_062"))					reg2->HIGH_HISTOGRAM_CURVE[62] = atoi(strstr(strstr(buf, "HIGH_HISTOGRAM_CURVE_062"), ",") + 1);
			else if (strstr(buf, "HIGH_HISTOGRAM_CURVE_063"))					reg2->HIGH_HISTOGRAM_CURVE[63] = atoi(strstr(strstr(buf, "HIGH_HISTOGRAM_CURVE_063"), ",") + 1);
			else if (strstr(buf, "HIGH_HISTOGRAM_CURVE_064"))					reg2->HIGH_HISTOGRAM_CURVE[64] = atoi(strstr(strstr(buf, "HIGH_HISTOGRAM_CURVE_064"), ",") + 1);
			else if (strstr(buf, "HIGH_HISTOGRAM_CURVE_065"))					reg2->HIGH_HISTOGRAM_CURVE[65] = atoi(strstr(strstr(buf, "HIGH_HISTOGRAM_CURVE_065"), ",") + 1);
			else if (strstr(buf, "HIGH_HISTOGRAM_CURVE_066"))					reg2->HIGH_HISTOGRAM_CURVE[66] = atoi(strstr(strstr(buf, "HIGH_HISTOGRAM_CURVE_066"), ",") + 1);
			else if (strstr(buf, "HIGH_HISTOGRAM_CURVE_067"))					reg2->HIGH_HISTOGRAM_CURVE[67] = atoi(strstr(strstr(buf, "HIGH_HISTOGRAM_CURVE_067"), ",") + 1);
			else if (strstr(buf, "HIGH_HISTOGRAM_CURVE_068"))					reg2->HIGH_HISTOGRAM_CURVE[68] = atoi(strstr(strstr(buf, "HIGH_HISTOGRAM_CURVE_068"), ",") + 1);
			else if (strstr(buf, "HIGH_HISTOGRAM_CURVE_069"))					reg2->HIGH_HISTOGRAM_CURVE[69] = atoi(strstr(strstr(buf, "HIGH_HISTOGRAM_CURVE_069"), ",") + 1);
			else if (strstr(buf, "HIGH_HISTOGRAM_CURVE_070"))					reg2->HIGH_HISTOGRAM_CURVE[70] = atoi(strstr(strstr(buf, "HIGH_HISTOGRAM_CURVE_070"), ",") + 1);
			else if (strstr(buf, "HIGH_HISTOGRAM_CURVE_071"))					reg2->HIGH_HISTOGRAM_CURVE[71] = atoi(strstr(strstr(buf, "HIGH_HISTOGRAM_CURVE_071"), ",") + 1);
			else if (strstr(buf, "HIGH_HISTOGRAM_CURVE_072"))					reg2->HIGH_HISTOGRAM_CURVE[72] = atoi(strstr(strstr(buf, "HIGH_HISTOGRAM_CURVE_072"), ",") + 1);
			else if (strstr(buf, "HIGH_HISTOGRAM_CURVE_073"))					reg2->HIGH_HISTOGRAM_CURVE[73] = atoi(strstr(strstr(buf, "HIGH_HISTOGRAM_CURVE_073"), ",") + 1);
			else if (strstr(buf, "HIGH_HISTOGRAM_CURVE_074"))					reg2->HIGH_HISTOGRAM_CURVE[74] = atoi(strstr(strstr(buf, "HIGH_HISTOGRAM_CURVE_074"), ",") + 1);
			else if (strstr(buf, "HIGH_HISTOGRAM_CURVE_075"))					reg2->HIGH_HISTOGRAM_CURVE[75] = atoi(strstr(strstr(buf, "HIGH_HISTOGRAM_CURVE_075"), ",") + 1);
			else if (strstr(buf, "HIGH_HISTOGRAM_CURVE_076"))					reg2->HIGH_HISTOGRAM_CURVE[76] = atoi(strstr(strstr(buf, "HIGH_HISTOGRAM_CURVE_076"), ",") + 1);
			else if (strstr(buf, "HIGH_HISTOGRAM_CURVE_077"))					reg2->HIGH_HISTOGRAM_CURVE[77] = atoi(strstr(strstr(buf, "HIGH_HISTOGRAM_CURVE_077"), ",") + 1);
			else if (strstr(buf, "HIGH_HISTOGRAM_CURVE_078"))					reg2->HIGH_HISTOGRAM_CURVE[78] = atoi(strstr(strstr(buf, "HIGH_HISTOGRAM_CURVE_078"), ",") + 1);
			else if (strstr(buf, "HIGH_HISTOGRAM_CURVE_079"))					reg2->HIGH_HISTOGRAM_CURVE[79] = atoi(strstr(strstr(buf, "HIGH_HISTOGRAM_CURVE_079"), ",") + 1);
			else if (strstr(buf, "HIGH_HISTOGRAM_CURVE_080"))					reg2->HIGH_HISTOGRAM_CURVE[80] = atoi(strstr(strstr(buf, "HIGH_HISTOGRAM_CURVE_080"), ",") + 1);
			else if (strstr(buf, "HIGH_HISTOGRAM_CURVE_081"))					reg2->HIGH_HISTOGRAM_CURVE[81] = atoi(strstr(strstr(buf, "HIGH_HISTOGRAM_CURVE_081"), ",") + 1);
			else if (strstr(buf, "HIGH_HISTOGRAM_CURVE_082"))					reg2->HIGH_HISTOGRAM_CURVE[82] = atoi(strstr(strstr(buf, "HIGH_HISTOGRAM_CURVE_082"), ",") + 1);
			else if (strstr(buf, "HIGH_HISTOGRAM_CURVE_083"))					reg2->HIGH_HISTOGRAM_CURVE[83] = atoi(strstr(strstr(buf, "HIGH_HISTOGRAM_CURVE_083"), ",") + 1);
			else if (strstr(buf, "HIGH_HISTOGRAM_CURVE_084"))					reg2->HIGH_HISTOGRAM_CURVE[84] = atoi(strstr(strstr(buf, "HIGH_HISTOGRAM_CURVE_084"), ",") + 1);
			else if (strstr(buf, "HIGH_HISTOGRAM_CURVE_085"))					reg2->HIGH_HISTOGRAM_CURVE[85] = atoi(strstr(strstr(buf, "HIGH_HISTOGRAM_CURVE_085"), ",") + 1);
			else if (strstr(buf, "HIGH_HISTOGRAM_CURVE_086"))					reg2->HIGH_HISTOGRAM_CURVE[86] = atoi(strstr(strstr(buf, "HIGH_HISTOGRAM_CURVE_086"), ",") + 1);
			else if (strstr(buf, "HIGH_HISTOGRAM_CURVE_087"))					reg2->HIGH_HISTOGRAM_CURVE[87] = atoi(strstr(strstr(buf, "HIGH_HISTOGRAM_CURVE_087"), ",") + 1);
			else if (strstr(buf, "HIGH_HISTOGRAM_CURVE_088"))					reg2->HIGH_HISTOGRAM_CURVE[88] = atoi(strstr(strstr(buf, "HIGH_HISTOGRAM_CURVE_088"), ",") + 1);
			else if (strstr(buf, "HIGH_HISTOGRAM_CURVE_089"))					reg2->HIGH_HISTOGRAM_CURVE[89] = atoi(strstr(strstr(buf, "HIGH_HISTOGRAM_CURVE_089"), ",") + 1);
			else if (strstr(buf, "HIGH_HISTOGRAM_CURVE_090"))					reg2->HIGH_HISTOGRAM_CURVE[90] = atoi(strstr(strstr(buf, "HIGH_HISTOGRAM_CURVE_090"), ",") + 1);
			else if (strstr(buf, "HIGH_HISTOGRAM_CURVE_091"))					reg2->HIGH_HISTOGRAM_CURVE[91] = atoi(strstr(strstr(buf, "HIGH_HISTOGRAM_CURVE_091"), ",") + 1);
			else if (strstr(buf, "HIGH_HISTOGRAM_CURVE_092"))					reg2->HIGH_HISTOGRAM_CURVE[92] = atoi(strstr(strstr(buf, "HIGH_HISTOGRAM_CURVE_092"), ",") + 1);
			else if (strstr(buf, "HIGH_HISTOGRAM_CURVE_093"))					reg2->HIGH_HISTOGRAM_CURVE[93] = atoi(strstr(strstr(buf, "HIGH_HISTOGRAM_CURVE_093"), ",") + 1);
			else if (strstr(buf, "HIGH_HISTOGRAM_CURVE_094"))					reg2->HIGH_HISTOGRAM_CURVE[94] = atoi(strstr(strstr(buf, "HIGH_HISTOGRAM_CURVE_094"), ",") + 1);
			else if (strstr(buf, "HIGH_HISTOGRAM_CURVE_095"))					reg2->HIGH_HISTOGRAM_CURVE[95] = atoi(strstr(strstr(buf, "HIGH_HISTOGRAM_CURVE_095"), ",") + 1);
			else if (strstr(buf, "HIGH_HISTOGRAM_CURVE_096"))					reg2->HIGH_HISTOGRAM_CURVE[96] = atoi(strstr(strstr(buf, "HIGH_HISTOGRAM_CURVE_096"), ",") + 1);
			else if (strstr(buf, "HIGH_HISTOGRAM_CURVE_097"))					reg2->HIGH_HISTOGRAM_CURVE[97] = atoi(strstr(strstr(buf, "HIGH_HISTOGRAM_CURVE_097"), ",") + 1);
			else if (strstr(buf, "HIGH_HISTOGRAM_CURVE_098"))					reg2->HIGH_HISTOGRAM_CURVE[98] = atoi(strstr(strstr(buf, "HIGH_HISTOGRAM_CURVE_098"), ",") + 1);
			else if (strstr(buf, "HIGH_HISTOGRAM_CURVE_099"))					reg2->HIGH_HISTOGRAM_CURVE[99] = atoi(strstr(strstr(buf, "HIGH_HISTOGRAM_CURVE_099"), ",") + 1);
			else if (strstr(buf, "HIGH_HISTOGRAM_CURVE_100"))					reg2->HIGH_HISTOGRAM_CURVE[100] = atoi(strstr(strstr(buf, "HIGH_HISTOGRAM_CURVE_100"), ",") + 1);
			else if (strstr(buf, "HIGH_HISTOGRAM_CURVE_101"))					reg2->HIGH_HISTOGRAM_CURVE[101] = atoi(strstr(strstr(buf, "HIGH_HISTOGRAM_CURVE_101"), ",") + 1);
			else if (strstr(buf, "HIGH_HISTOGRAM_CURVE_102"))					reg2->HIGH_HISTOGRAM_CURVE[102] = atoi(strstr(strstr(buf, "HIGH_HISTOGRAM_CURVE_102"), ",") + 1);
			else if (strstr(buf, "HIGH_HISTOGRAM_CURVE_103"))					reg2->HIGH_HISTOGRAM_CURVE[103] = atoi(strstr(strstr(buf, "HIGH_HISTOGRAM_CURVE_103"), ",") + 1);
			else if (strstr(buf, "HIGH_HISTOGRAM_CURVE_104"))					reg2->HIGH_HISTOGRAM_CURVE[104] = atoi(strstr(strstr(buf, "HIGH_HISTOGRAM_CURVE_104"), ",") + 1);
			else if (strstr(buf, "HIGH_HISTOGRAM_CURVE_105"))					reg2->HIGH_HISTOGRAM_CURVE[105] = atoi(strstr(strstr(buf, "HIGH_HISTOGRAM_CURVE_105"), ",") + 1);
			else if (strstr(buf, "HIGH_HISTOGRAM_CURVE_106"))					reg2->HIGH_HISTOGRAM_CURVE[106] = atoi(strstr(strstr(buf, "HIGH_HISTOGRAM_CURVE_106"), ",") + 1);
			else if (strstr(buf, "HIGH_HISTOGRAM_CURVE_107"))					reg2->HIGH_HISTOGRAM_CURVE[107] = atoi(strstr(strstr(buf, "HIGH_HISTOGRAM_CURVE_107"), ",") + 1);
			else if (strstr(buf, "HIGH_HISTOGRAM_CURVE_108"))					reg2->HIGH_HISTOGRAM_CURVE[108] = atoi(strstr(strstr(buf, "HIGH_HISTOGRAM_CURVE_108"), ",") + 1);
			else if (strstr(buf, "HIGH_HISTOGRAM_CURVE_109"))					reg2->HIGH_HISTOGRAM_CURVE[109] = atoi(strstr(strstr(buf, "HIGH_HISTOGRAM_CURVE_109"), ",") + 1);
			else if (strstr(buf, "HIGH_HISTOGRAM_CURVE_110"))					reg2->HIGH_HISTOGRAM_CURVE[110] = atoi(strstr(strstr(buf, "HIGH_HISTOGRAM_CURVE_110"), ",") + 1);
			else if (strstr(buf, "HIGH_HISTOGRAM_CURVE_111"))					reg2->HIGH_HISTOGRAM_CURVE[111] = atoi(strstr(strstr(buf, "HIGH_HISTOGRAM_CURVE_111"), ",") + 1);
			else if (strstr(buf, "HIGH_HISTOGRAM_CURVE_112"))					reg2->HIGH_HISTOGRAM_CURVE[112] = atoi(strstr(strstr(buf, "HIGH_HISTOGRAM_CURVE_112"), ",") + 1);
			else if (strstr(buf, "HIGH_HISTOGRAM_CURVE_113"))					reg2->HIGH_HISTOGRAM_CURVE[113] = atoi(strstr(strstr(buf, "HIGH_HISTOGRAM_CURVE_113"), ",") + 1);
			else if (strstr(buf, "HIGH_HISTOGRAM_CURVE_114"))					reg2->HIGH_HISTOGRAM_CURVE[114] = atoi(strstr(strstr(buf, "HIGH_HISTOGRAM_CURVE_114"), ",") + 1);
			else if (strstr(buf, "HIGH_HISTOGRAM_CURVE_115"))					reg2->HIGH_HISTOGRAM_CURVE[115] = atoi(strstr(strstr(buf, "HIGH_HISTOGRAM_CURVE_115"), ",") + 1);
			else if (strstr(buf, "HIGH_HISTOGRAM_CURVE_116"))					reg2->HIGH_HISTOGRAM_CURVE[116] = atoi(strstr(strstr(buf, "HIGH_HISTOGRAM_CURVE_116"), ",") + 1);
			else if (strstr(buf, "HIGH_HISTOGRAM_CURVE_117"))					reg2->HIGH_HISTOGRAM_CURVE[117] = atoi(strstr(strstr(buf, "HIGH_HISTOGRAM_CURVE_117"), ",") + 1);
			else if (strstr(buf, "HIGH_HISTOGRAM_CURVE_118"))					reg2->HIGH_HISTOGRAM_CURVE[118] = atoi(strstr(strstr(buf, "HIGH_HISTOGRAM_CURVE_118"), ",") + 1);
			else if (strstr(buf, "HIGH_HISTOGRAM_CURVE_119"))					reg2->HIGH_HISTOGRAM_CURVE[119] = atoi(strstr(strstr(buf, "HIGH_HISTOGRAM_CURVE_119"), ",") + 1);
			else if (strstr(buf, "HIGH_HISTOGRAM_CURVE_120"))					reg2->HIGH_HISTOGRAM_CURVE[120] = atoi(strstr(strstr(buf, "HIGH_HISTOGRAM_CURVE_120"), ",") + 1);
			else if (strstr(buf, "HIGH_HISTOGRAM_CURVE_121"))					reg2->HIGH_HISTOGRAM_CURVE[121] = atoi(strstr(strstr(buf, "HIGH_HISTOGRAM_CURVE_121"), ",") + 1);
			else if (strstr(buf, "HIGH_HISTOGRAM_CURVE_122"))					reg2->HIGH_HISTOGRAM_CURVE[122] = atoi(strstr(strstr(buf, "HIGH_HISTOGRAM_CURVE_122"), ",") + 1);
			else if (strstr(buf, "HIGH_HISTOGRAM_CURVE_123"))					reg2->HIGH_HISTOGRAM_CURVE[123] = atoi(strstr(strstr(buf, "HIGH_HISTOGRAM_CURVE_123"), ",") + 1);
			else if (strstr(buf, "HIGH_HISTOGRAM_CURVE_124"))					reg2->HIGH_HISTOGRAM_CURVE[124] = atoi(strstr(strstr(buf, "HIGH_HISTOGRAM_CURVE_124"), ",") + 1);
			else if (strstr(buf, "HIGH_HISTOGRAM_CURVE_125"))					reg2->HIGH_HISTOGRAM_CURVE[125] = atoi(strstr(strstr(buf, "HIGH_HISTOGRAM_CURVE_125"), ",") + 1);
			else if (strstr(buf, "HIGH_HISTOGRAM_CURVE_126"))					reg2->HIGH_HISTOGRAM_CURVE[126] = atoi(strstr(strstr(buf, "HIGH_HISTOGRAM_CURVE_126"), ",") + 1);
			else if (strstr(buf, "HIGH_HISTOGRAM_CURVE_127"))					reg2->HIGH_HISTOGRAM_CURVE[127] = atoi(strstr(strstr(buf, "HIGH_HISTOGRAM_CURVE_127"), ",") + 1);

			else;
		}
	}
	fclose(pFile);




	if ((pFile = fopen(filename, "rt")) == NULL)
	{
		printf("Open REG File Error\n");
		system("pause");
	}
	else
	{
		while (fgets(buf, 256, pFile))
		{
			if (strstr(buf, "LOW_HISTOGRAM_CURVE_000"))					        reg2->LOW_HISTOGRAM_CURVE[0] = atoi(strstr(strstr(buf, "LOW_HISTOGRAM_CURVE_000"), ",") + 1);
			else if (strstr(buf, "LOW_HISTOGRAM_CURVE_001"))					    reg2->LOW_HISTOGRAM_CURVE[1] = atoi(strstr(strstr(buf, "LOW_HISTOGRAM_CURVE_001"), ",") + 1);
			else if (strstr(buf, "LOW_HISTOGRAM_CURVE_002"))					    reg2->LOW_HISTOGRAM_CURVE[2] = atoi(strstr(strstr(buf, "LOW_HISTOGRAM_CURVE_002"), ",") + 1);
			else if (strstr(buf, "LOW_HISTOGRAM_CURVE_003"))					    reg2->LOW_HISTOGRAM_CURVE[3] = atoi(strstr(strstr(buf, "LOW_HISTOGRAM_CURVE_003"), ",") + 1);
			else if (strstr(buf, "LOW_HISTOGRAM_CURVE_004"))					    reg2->LOW_HISTOGRAM_CURVE[4] = atoi(strstr(strstr(buf, "LOW_HISTOGRAM_CURVE_004"), ",") + 1);
			else if (strstr(buf, "LOW_HISTOGRAM_CURVE_005"))					    reg2->LOW_HISTOGRAM_CURVE[5] = atoi(strstr(strstr(buf, "LOW_HISTOGRAM_CURVE_005"), ",") + 1);
			else if (strstr(buf, "LOW_HISTOGRAM_CURVE_006"))					    reg2->LOW_HISTOGRAM_CURVE[6] = atoi(strstr(strstr(buf, "LOW_HISTOGRAM_CURVE_006"), ",") + 1);
			else if (strstr(buf, "LOW_HISTOGRAM_CURVE_007"))					    reg2->LOW_HISTOGRAM_CURVE[7] = atoi(strstr(strstr(buf, "LOW_HISTOGRAM_CURVE_007"), ",") + 1);
			else if (strstr(buf, "LOW_HISTOGRAM_CURVE_008"))					    reg2->LOW_HISTOGRAM_CURVE[8] = atoi(strstr(strstr(buf, "LOW_HISTOGRAM_CURVE_008"), ",") + 1);
			else if (strstr(buf, "LOW_HISTOGRAM_CURVE_009"))					    reg2->LOW_HISTOGRAM_CURVE[9] = atoi(strstr(strstr(buf, "LOW_HISTOGRAM_CURVE_009"), ",") + 1);
			else if (strstr(buf, "LOW_HISTOGRAM_CURVE_010"))					    reg2->LOW_HISTOGRAM_CURVE[10] = atoi(strstr(strstr(buf, "LOW_HISTOGRAM_CURVE_010"), ",") + 1);
			else if (strstr(buf, "LOW_HISTOGRAM_CURVE_011"))					    reg2->LOW_HISTOGRAM_CURVE[11] = atoi(strstr(strstr(buf, "LOW_HISTOGRAM_CURVE_011"), ",") + 1);
			else if (strstr(buf, "LOW_HISTOGRAM_CURVE_012"))					    reg2->LOW_HISTOGRAM_CURVE[12] = atoi(strstr(strstr(buf, "LOW_HISTOGRAM_CURVE_012"), ",") + 1);
			else if (strstr(buf, "LOW_HISTOGRAM_CURVE_013"))					    reg2->LOW_HISTOGRAM_CURVE[13] = atoi(strstr(strstr(buf, "LOW_HISTOGRAM_CURVE_013"), ",") + 1);
			else if (strstr(buf, "LOW_HISTOGRAM_CURVE_014"))					    reg2->LOW_HISTOGRAM_CURVE[14] = atoi(strstr(strstr(buf, "LOW_HISTOGRAM_CURVE_014"), ",") + 1);
			else if (strstr(buf, "LOW_HISTOGRAM_CURVE_015"))					    reg2->LOW_HISTOGRAM_CURVE[15] = atoi(strstr(strstr(buf, "LOW_HISTOGRAM_CURVE_015"), ",") + 1);
			else if (strstr(buf, "LOW_HISTOGRAM_CURVE_016"))					    reg2->LOW_HISTOGRAM_CURVE[16] = atoi(strstr(strstr(buf, "LOW_HISTOGRAM_CURVE_016"), ",") + 1);
			else if (strstr(buf, "LOW_HISTOGRAM_CURVE_017"))					    reg2->LOW_HISTOGRAM_CURVE[17] = atoi(strstr(strstr(buf, "LOW_HISTOGRAM_CURVE_017"), ",") + 1);
			else if (strstr(buf, "LOW_HISTOGRAM_CURVE_018"))					    reg2->LOW_HISTOGRAM_CURVE[18] = atoi(strstr(strstr(buf, "LOW_HISTOGRAM_CURVE_018"), ",") + 1);
			else if (strstr(buf, "LOW_HISTOGRAM_CURVE_019"))					    reg2->LOW_HISTOGRAM_CURVE[19] = atoi(strstr(strstr(buf, "LOW_HISTOGRAM_CURVE_019"), ",") + 1);
			else if (strstr(buf, "LOW_HISTOGRAM_CURVE_020"))					    reg2->LOW_HISTOGRAM_CURVE[20] = atoi(strstr(strstr(buf, "LOW_HISTOGRAM_CURVE_020"), ",") + 1);
			else if (strstr(buf, "LOW_HISTOGRAM_CURVE_021"))					    reg2->LOW_HISTOGRAM_CURVE[21] = atoi(strstr(strstr(buf, "LOW_HISTOGRAM_CURVE_021"), ",") + 1);
			else if (strstr(buf, "LOW_HISTOGRAM_CURVE_022"))					    reg2->LOW_HISTOGRAM_CURVE[22] = atoi(strstr(strstr(buf, "LOW_HISTOGRAM_CURVE_022"), ",") + 1);
			else if (strstr(buf, "LOW_HISTOGRAM_CURVE_023"))					    reg2->LOW_HISTOGRAM_CURVE[23] = atoi(strstr(strstr(buf, "LOW_HISTOGRAM_CURVE_023"), ",") + 1);
			else if (strstr(buf, "LOW_HISTOGRAM_CURVE_024"))					    reg2->LOW_HISTOGRAM_CURVE[24] = atoi(strstr(strstr(buf, "LOW_HISTOGRAM_CURVE_024"), ",") + 1);
			else if (strstr(buf, "LOW_HISTOGRAM_CURVE_025"))					    reg2->LOW_HISTOGRAM_CURVE[25] = atoi(strstr(strstr(buf, "LOW_HISTOGRAM_CURVE_025"), ",") + 1);
			else if (strstr(buf, "LOW_HISTOGRAM_CURVE_026"))					    reg2->LOW_HISTOGRAM_CURVE[26] = atoi(strstr(strstr(buf, "LOW_HISTOGRAM_CURVE_026"), ",") + 1);
			else if (strstr(buf, "LOW_HISTOGRAM_CURVE_027"))					    reg2->LOW_HISTOGRAM_CURVE[27] = atoi(strstr(strstr(buf, "LOW_HISTOGRAM_CURVE_027"), ",") + 1);
			else if (strstr(buf, "LOW_HISTOGRAM_CURVE_028"))					    reg2->LOW_HISTOGRAM_CURVE[28] = atoi(strstr(strstr(buf, "LOW_HISTOGRAM_CURVE_028"), ",") + 1);
			else if (strstr(buf, "LOW_HISTOGRAM_CURVE_029"))					    reg2->LOW_HISTOGRAM_CURVE[29] = atoi(strstr(strstr(buf, "LOW_HISTOGRAM_CURVE_029"), ",") + 1);
			else if (strstr(buf, "LOW_HISTOGRAM_CURVE_030"))					    reg2->LOW_HISTOGRAM_CURVE[30] = atoi(strstr(strstr(buf, "LOW_HISTOGRAM_CURVE_030"), ",") + 1);
			else if (strstr(buf, "LOW_HISTOGRAM_CURVE_031"))					    reg2->LOW_HISTOGRAM_CURVE[31] = atoi(strstr(strstr(buf, "LOW_HISTOGRAM_CURVE_031"), ",") + 1);
			else if (strstr(buf, "LOW_HISTOGRAM_CURVE_032"))					    reg2->LOW_HISTOGRAM_CURVE[32] = atoi(strstr(strstr(buf, "LOW_HISTOGRAM_CURVE_032"), ",") + 1);
			else if (strstr(buf, "LOW_HISTOGRAM_CURVE_033"))					    reg2->LOW_HISTOGRAM_CURVE[33] = atoi(strstr(strstr(buf, "LOW_HISTOGRAM_CURVE_033"), ",") + 1);
			else if (strstr(buf, "LOW_HISTOGRAM_CURVE_034"))					    reg2->LOW_HISTOGRAM_CURVE[34] = atoi(strstr(strstr(buf, "LOW_HISTOGRAM_CURVE_034"), ",") + 1);
			else if (strstr(buf, "LOW_HISTOGRAM_CURVE_035"))					    reg2->LOW_HISTOGRAM_CURVE[35] = atoi(strstr(strstr(buf, "LOW_HISTOGRAM_CURVE_035"), ",") + 1);
			else if (strstr(buf, "LOW_HISTOGRAM_CURVE_036"))					    reg2->LOW_HISTOGRAM_CURVE[36] = atoi(strstr(strstr(buf, "LOW_HISTOGRAM_CURVE_036"), ",") + 1);
			else if (strstr(buf, "LOW_HISTOGRAM_CURVE_037"))					    reg2->LOW_HISTOGRAM_CURVE[37] = atoi(strstr(strstr(buf, "LOW_HISTOGRAM_CURVE_037"), ",") + 1);
			else if (strstr(buf, "LOW_HISTOGRAM_CURVE_038"))					    reg2->LOW_HISTOGRAM_CURVE[38] = atoi(strstr(strstr(buf, "LOW_HISTOGRAM_CURVE_038"), ",") + 1);
			else if (strstr(buf, "LOW_HISTOGRAM_CURVE_039"))					    reg2->LOW_HISTOGRAM_CURVE[39] = atoi(strstr(strstr(buf, "LOW_HISTOGRAM_CURVE_039"), ",") + 1);
			else if (strstr(buf, "LOW_HISTOGRAM_CURVE_040"))					    reg2->LOW_HISTOGRAM_CURVE[40] = atoi(strstr(strstr(buf, "LOW_HISTOGRAM_CURVE_040"), ",") + 1);
			else if (strstr(buf, "LOW_HISTOGRAM_CURVE_041"))					    reg2->LOW_HISTOGRAM_CURVE[41] = atoi(strstr(strstr(buf, "LOW_HISTOGRAM_CURVE_041"), ",") + 1);
			else if (strstr(buf, "LOW_HISTOGRAM_CURVE_042"))					    reg2->LOW_HISTOGRAM_CURVE[42] = atoi(strstr(strstr(buf, "LOW_HISTOGRAM_CURVE_042"), ",") + 1);
			else if (strstr(buf, "LOW_HISTOGRAM_CURVE_043"))					    reg2->LOW_HISTOGRAM_CURVE[43] = atoi(strstr(strstr(buf, "LOW_HISTOGRAM_CURVE_043"), ",") + 1);
			else if (strstr(buf, "LOW_HISTOGRAM_CURVE_044"))					    reg2->LOW_HISTOGRAM_CURVE[44] = atoi(strstr(strstr(buf, "LOW_HISTOGRAM_CURVE_044"), ",") + 1);
			else if (strstr(buf, "LOW_HISTOGRAM_CURVE_045"))					    reg2->LOW_HISTOGRAM_CURVE[45] = atoi(strstr(strstr(buf, "LOW_HISTOGRAM_CURVE_045"), ",") + 1);
			else if (strstr(buf, "LOW_HISTOGRAM_CURVE_046"))					    reg2->LOW_HISTOGRAM_CURVE[46] = atoi(strstr(strstr(buf, "LOW_HISTOGRAM_CURVE_046"), ",") + 1);
			else if (strstr(buf, "LOW_HISTOGRAM_CURVE_047"))					    reg2->LOW_HISTOGRAM_CURVE[47] = atoi(strstr(strstr(buf, "LOW_HISTOGRAM_CURVE_047"), ",") + 1);
			else if (strstr(buf, "LOW_HISTOGRAM_CURVE_048"))					    reg2->LOW_HISTOGRAM_CURVE[48] = atoi(strstr(strstr(buf, "LOW_HISTOGRAM_CURVE_048"), ",") + 1);
			else if (strstr(buf, "LOW_HISTOGRAM_CURVE_049"))					    reg2->LOW_HISTOGRAM_CURVE[49] = atoi(strstr(strstr(buf, "LOW_HISTOGRAM_CURVE_049"), ",") + 1);
			else if (strstr(buf, "LOW_HISTOGRAM_CURVE_050"))					    reg2->LOW_HISTOGRAM_CURVE[50] = atoi(strstr(strstr(buf, "LOW_HISTOGRAM_CURVE_050"), ",") + 1);
			else if (strstr(buf, "LOW_HISTOGRAM_CURVE_051"))					    reg2->LOW_HISTOGRAM_CURVE[51] = atoi(strstr(strstr(buf, "LOW_HISTOGRAM_CURVE_051"), ",") + 1);
			else if (strstr(buf, "LOW_HISTOGRAM_CURVE_052"))					    reg2->LOW_HISTOGRAM_CURVE[52] = atoi(strstr(strstr(buf, "LOW_HISTOGRAM_CURVE_052"), ",") + 1);
			else if (strstr(buf, "LOW_HISTOGRAM_CURVE_053"))					    reg2->LOW_HISTOGRAM_CURVE[53] = atoi(strstr(strstr(buf, "LOW_HISTOGRAM_CURVE_053"), ",") + 1);
			else if (strstr(buf, "LOW_HISTOGRAM_CURVE_054"))					    reg2->LOW_HISTOGRAM_CURVE[54] = atoi(strstr(strstr(buf, "LOW_HISTOGRAM_CURVE_054"), ",") + 1);
			else if (strstr(buf, "LOW_HISTOGRAM_CURVE_055"))					    reg2->LOW_HISTOGRAM_CURVE[55] = atoi(strstr(strstr(buf, "LOW_HISTOGRAM_CURVE_055"), ",") + 1);
			else if (strstr(buf, "LOW_HISTOGRAM_CURVE_056"))					    reg2->LOW_HISTOGRAM_CURVE[56] = atoi(strstr(strstr(buf, "LOW_HISTOGRAM_CURVE_056"), ",") + 1);
			else if (strstr(buf, "LOW_HISTOGRAM_CURVE_057"))					    reg2->LOW_HISTOGRAM_CURVE[57] = atoi(strstr(strstr(buf, "LOW_HISTOGRAM_CURVE_057"), ",") + 1);
			else if (strstr(buf, "LOW_HISTOGRAM_CURVE_058"))					    reg2->LOW_HISTOGRAM_CURVE[58] = atoi(strstr(strstr(buf, "LOW_HISTOGRAM_CURVE_058"), ",") + 1);
			else if (strstr(buf, "LOW_HISTOGRAM_CURVE_059"))					    reg2->LOW_HISTOGRAM_CURVE[59] = atoi(strstr(strstr(buf, "LOW_HISTOGRAM_CURVE_059"), ",") + 1);
			else if (strstr(buf, "LOW_HISTOGRAM_CURVE_060"))					    reg2->LOW_HISTOGRAM_CURVE[60] = atoi(strstr(strstr(buf, "LOW_HISTOGRAM_CURVE_060"), ",") + 1);
			else if (strstr(buf, "LOW_HISTOGRAM_CURVE_061"))					    reg2->LOW_HISTOGRAM_CURVE[61] = atoi(strstr(strstr(buf, "LOW_HISTOGRAM_CURVE_061"), ",") + 1);
			else if (strstr(buf, "LOW_HISTOGRAM_CURVE_062"))					    reg2->LOW_HISTOGRAM_CURVE[62] = atoi(strstr(strstr(buf, "LOW_HISTOGRAM_CURVE_062"), ",") + 1);
			else if (strstr(buf, "LOW_HISTOGRAM_CURVE_063"))					    reg2->LOW_HISTOGRAM_CURVE[63] = atoi(strstr(strstr(buf, "LOW_HISTOGRAM_CURVE_063"), ",") + 1);
			else if (strstr(buf, "LOW_HISTOGRAM_CURVE_064"))					    reg2->LOW_HISTOGRAM_CURVE[64] = atoi(strstr(strstr(buf, "LOW_HISTOGRAM_CURVE_064"), ",") + 1);
			else if (strstr(buf, "LOW_HISTOGRAM_CURVE_065"))					    reg2->LOW_HISTOGRAM_CURVE[65] = atoi(strstr(strstr(buf, "LOW_HISTOGRAM_CURVE_065"), ",") + 1);
			else if (strstr(buf, "LOW_HISTOGRAM_CURVE_066"))					    reg2->LOW_HISTOGRAM_CURVE[66] = atoi(strstr(strstr(buf, "LOW_HISTOGRAM_CURVE_066"), ",") + 1);
			else if (strstr(buf, "LOW_HISTOGRAM_CURVE_067"))					    reg2->LOW_HISTOGRAM_CURVE[67] = atoi(strstr(strstr(buf, "LOW_HISTOGRAM_CURVE_067"), ",") + 1);
			else if (strstr(buf, "LOW_HISTOGRAM_CURVE_068"))					    reg2->LOW_HISTOGRAM_CURVE[68] = atoi(strstr(strstr(buf, "LOW_HISTOGRAM_CURVE_068"), ",") + 1);
			else if (strstr(buf, "LOW_HISTOGRAM_CURVE_069"))					    reg2->LOW_HISTOGRAM_CURVE[69] = atoi(strstr(strstr(buf, "LOW_HISTOGRAM_CURVE_069"), ",") + 1);
			else if (strstr(buf, "LOW_HISTOGRAM_CURVE_070"))					    reg2->LOW_HISTOGRAM_CURVE[70] = atoi(strstr(strstr(buf, "LOW_HISTOGRAM_CURVE_070"), ",") + 1);
			else if (strstr(buf, "LOW_HISTOGRAM_CURVE_071"))					    reg2->LOW_HISTOGRAM_CURVE[71] = atoi(strstr(strstr(buf, "LOW_HISTOGRAM_CURVE_071"), ",") + 1);
			else if (strstr(buf, "LOW_HISTOGRAM_CURVE_072"))					    reg2->LOW_HISTOGRAM_CURVE[72] = atoi(strstr(strstr(buf, "LOW_HISTOGRAM_CURVE_072"), ",") + 1);
			else if (strstr(buf, "LOW_HISTOGRAM_CURVE_073"))					    reg2->LOW_HISTOGRAM_CURVE[73] = atoi(strstr(strstr(buf, "LOW_HISTOGRAM_CURVE_073"), ",") + 1);
			else if (strstr(buf, "LOW_HISTOGRAM_CURVE_074"))					    reg2->LOW_HISTOGRAM_CURVE[74] = atoi(strstr(strstr(buf, "LOW_HISTOGRAM_CURVE_074"), ",") + 1);
			else if (strstr(buf, "LOW_HISTOGRAM_CURVE_075"))					    reg2->LOW_HISTOGRAM_CURVE[75] = atoi(strstr(strstr(buf, "LOW_HISTOGRAM_CURVE_075"), ",") + 1);
			else if (strstr(buf, "LOW_HISTOGRAM_CURVE_076"))					    reg2->LOW_HISTOGRAM_CURVE[76] = atoi(strstr(strstr(buf, "LOW_HISTOGRAM_CURVE_076"), ",") + 1);
			else if (strstr(buf, "LOW_HISTOGRAM_CURVE_077"))					    reg2->LOW_HISTOGRAM_CURVE[77] = atoi(strstr(strstr(buf, "LOW_HISTOGRAM_CURVE_077"), ",") + 1);
			else if (strstr(buf, "LOW_HISTOGRAM_CURVE_078"))					    reg2->LOW_HISTOGRAM_CURVE[78] = atoi(strstr(strstr(buf, "LOW_HISTOGRAM_CURVE_078"), ",") + 1);
			else if (strstr(buf, "LOW_HISTOGRAM_CURVE_079"))					    reg2->LOW_HISTOGRAM_CURVE[79] = atoi(strstr(strstr(buf, "LOW_HISTOGRAM_CURVE_079"), ",") + 1);
			else if (strstr(buf, "LOW_HISTOGRAM_CURVE_080"))					    reg2->LOW_HISTOGRAM_CURVE[80] = atoi(strstr(strstr(buf, "LOW_HISTOGRAM_CURVE_080"), ",") + 1);
			else if (strstr(buf, "LOW_HISTOGRAM_CURVE_081"))					    reg2->LOW_HISTOGRAM_CURVE[81] = atoi(strstr(strstr(buf, "LOW_HISTOGRAM_CURVE_081"), ",") + 1);
			else if (strstr(buf, "LOW_HISTOGRAM_CURVE_082"))					    reg2->LOW_HISTOGRAM_CURVE[82] = atoi(strstr(strstr(buf, "LOW_HISTOGRAM_CURVE_082"), ",") + 1);
			else if (strstr(buf, "LOW_HISTOGRAM_CURVE_083"))					    reg2->LOW_HISTOGRAM_CURVE[83] = atoi(strstr(strstr(buf, "LOW_HISTOGRAM_CURVE_083"), ",") + 1);
			else if (strstr(buf, "LOW_HISTOGRAM_CURVE_084"))					    reg2->LOW_HISTOGRAM_CURVE[84] = atoi(strstr(strstr(buf, "LOW_HISTOGRAM_CURVE_084"), ",") + 1);
			else if (strstr(buf, "LOW_HISTOGRAM_CURVE_085"))					    reg2->LOW_HISTOGRAM_CURVE[85] = atoi(strstr(strstr(buf, "LOW_HISTOGRAM_CURVE_085"), ",") + 1);
			else if (strstr(buf, "LOW_HISTOGRAM_CURVE_086"))					    reg2->LOW_HISTOGRAM_CURVE[86] = atoi(strstr(strstr(buf, "LOW_HISTOGRAM_CURVE_086"), ",") + 1);
			else if (strstr(buf, "LOW_HISTOGRAM_CURVE_087"))					    reg2->LOW_HISTOGRAM_CURVE[87] = atoi(strstr(strstr(buf, "LOW_HISTOGRAM_CURVE_087"), ",") + 1);
			else if (strstr(buf, "LOW_HISTOGRAM_CURVE_088"))					    reg2->LOW_HISTOGRAM_CURVE[88] = atoi(strstr(strstr(buf, "LOW_HISTOGRAM_CURVE_088"), ",") + 1);
			else if (strstr(buf, "LOW_HISTOGRAM_CURVE_089"))					    reg2->LOW_HISTOGRAM_CURVE[89] = atoi(strstr(strstr(buf, "LOW_HISTOGRAM_CURVE_089"), ",") + 1);
			else if (strstr(buf, "LOW_HISTOGRAM_CURVE_090"))					    reg2->LOW_HISTOGRAM_CURVE[90] = atoi(strstr(strstr(buf, "LOW_HISTOGRAM_CURVE_090"), ",") + 1);
			else if (strstr(buf, "LOW_HISTOGRAM_CURVE_091"))					    reg2->LOW_HISTOGRAM_CURVE[91] = atoi(strstr(strstr(buf, "LOW_HISTOGRAM_CURVE_091"), ",") + 1);
			else if (strstr(buf, "LOW_HISTOGRAM_CURVE_092"))					    reg2->LOW_HISTOGRAM_CURVE[92] = atoi(strstr(strstr(buf, "LOW_HISTOGRAM_CURVE_092"), ",") + 1);
			else if (strstr(buf, "LOW_HISTOGRAM_CURVE_093"))					    reg2->LOW_HISTOGRAM_CURVE[93] = atoi(strstr(strstr(buf, "LOW_HISTOGRAM_CURVE_093"), ",") + 1);
			else if (strstr(buf, "LOW_HISTOGRAM_CURVE_094"))					    reg2->LOW_HISTOGRAM_CURVE[94] = atoi(strstr(strstr(buf, "LOW_HISTOGRAM_CURVE_094"), ",") + 1);
			else if (strstr(buf, "LOW_HISTOGRAM_CURVE_095"))					    reg2->LOW_HISTOGRAM_CURVE[95] = atoi(strstr(strstr(buf, "LOW_HISTOGRAM_CURVE_095"), ",") + 1);
			else if (strstr(buf, "LOW_HISTOGRAM_CURVE_096"))					    reg2->LOW_HISTOGRAM_CURVE[96] = atoi(strstr(strstr(buf, "LOW_HISTOGRAM_CURVE_096"), ",") + 1);
			else if (strstr(buf, "LOW_HISTOGRAM_CURVE_097"))					    reg2->LOW_HISTOGRAM_CURVE[97] = atoi(strstr(strstr(buf, "LOW_HISTOGRAM_CURVE_097"), ",") + 1);
			else if (strstr(buf, "LOW_HISTOGRAM_CURVE_098"))					    reg2->LOW_HISTOGRAM_CURVE[98] = atoi(strstr(strstr(buf, "LOW_HISTOGRAM_CURVE_098"), ",") + 1);
			else if (strstr(buf, "LOW_HISTOGRAM_CURVE_099"))					    reg2->LOW_HISTOGRAM_CURVE[99] = atoi(strstr(strstr(buf, "LOW_HISTOGRAM_CURVE_099"), ",") + 1);
			else if (strstr(buf, "LOW_HISTOGRAM_CURVE_100"))					reg2->LOW_HISTOGRAM_CURVE[100] = atoi(strstr(strstr(buf, "LOW_HISTOGRAM_CURVE_100"), ",") + 1);
			else if (strstr(buf, "LOW_HISTOGRAM_CURVE_101"))					reg2->LOW_HISTOGRAM_CURVE[101] = atoi(strstr(strstr(buf, "LOW_HISTOGRAM_CURVE_101"), ",") + 1);
			else if (strstr(buf, "LOW_HISTOGRAM_CURVE_102"))					reg2->LOW_HISTOGRAM_CURVE[102] = atoi(strstr(strstr(buf, "LOW_HISTOGRAM_CURVE_102"), ",") + 1);
			else if (strstr(buf, "LOW_HISTOGRAM_CURVE_103"))					reg2->LOW_HISTOGRAM_CURVE[103] = atoi(strstr(strstr(buf, "LOW_HISTOGRAM_CURVE_103"), ",") + 1);
			else if (strstr(buf, "LOW_HISTOGRAM_CURVE_104"))					reg2->LOW_HISTOGRAM_CURVE[104] = atoi(strstr(strstr(buf, "LOW_HISTOGRAM_CURVE_104"), ",") + 1);
			else if (strstr(buf, "LOW_HISTOGRAM_CURVE_105"))					reg2->LOW_HISTOGRAM_CURVE[105] = atoi(strstr(strstr(buf, "LOW_HISTOGRAM_CURVE_105"), ",") + 1);
			else if (strstr(buf, "LOW_HISTOGRAM_CURVE_106"))					reg2->LOW_HISTOGRAM_CURVE[106] = atoi(strstr(strstr(buf, "LOW_HISTOGRAM_CURVE_106"), ",") + 1);
			else if (strstr(buf, "LOW_HISTOGRAM_CURVE_107"))					reg2->LOW_HISTOGRAM_CURVE[107] = atoi(strstr(strstr(buf, "LOW_HISTOGRAM_CURVE_107"), ",") + 1);
			else if (strstr(buf, "LOW_HISTOGRAM_CURVE_108"))					reg2->LOW_HISTOGRAM_CURVE[108] = atoi(strstr(strstr(buf, "LOW_HISTOGRAM_CURVE_108"), ",") + 1);
			else if (strstr(buf, "LOW_HISTOGRAM_CURVE_109"))					reg2->LOW_HISTOGRAM_CURVE[109] = atoi(strstr(strstr(buf, "LOW_HISTOGRAM_CURVE_109"), ",") + 1);
			else if (strstr(buf, "LOW_HISTOGRAM_CURVE_110"))					reg2->LOW_HISTOGRAM_CURVE[110] = atoi(strstr(strstr(buf, "LOW_HISTOGRAM_CURVE_110"), ",") + 1);
			else if (strstr(buf, "LOW_HISTOGRAM_CURVE_111"))					reg2->LOW_HISTOGRAM_CURVE[111] = atoi(strstr(strstr(buf, "LOW_HISTOGRAM_CURVE_111"), ",") + 1);
			else if (strstr(buf, "LOW_HISTOGRAM_CURVE_112"))					reg2->LOW_HISTOGRAM_CURVE[112] = atoi(strstr(strstr(buf, "LOW_HISTOGRAM_CURVE_112"), ",") + 1);
			else if (strstr(buf, "LOW_HISTOGRAM_CURVE_113"))					reg2->LOW_HISTOGRAM_CURVE[113] = atoi(strstr(strstr(buf, "LOW_HISTOGRAM_CURVE_113"), ",") + 1);
			else if (strstr(buf, "LOW_HISTOGRAM_CURVE_114"))					reg2->LOW_HISTOGRAM_CURVE[114] = atoi(strstr(strstr(buf, "LOW_HISTOGRAM_CURVE_114"), ",") + 1);
			else if (strstr(buf, "LOW_HISTOGRAM_CURVE_115"))					reg2->LOW_HISTOGRAM_CURVE[115] = atoi(strstr(strstr(buf, "LOW_HISTOGRAM_CURVE_115"), ",") + 1);
			else if (strstr(buf, "LOW_HISTOGRAM_CURVE_116"))					reg2->LOW_HISTOGRAM_CURVE[116] = atoi(strstr(strstr(buf, "LOW_HISTOGRAM_CURVE_116"), ",") + 1);
			else if (strstr(buf, "LOW_HISTOGRAM_CURVE_117"))					reg2->LOW_HISTOGRAM_CURVE[117] = atoi(strstr(strstr(buf, "LOW_HISTOGRAM_CURVE_117"), ",") + 1);
			else if (strstr(buf, "LOW_HISTOGRAM_CURVE_118"))					reg2->LOW_HISTOGRAM_CURVE[118] = atoi(strstr(strstr(buf, "LOW_HISTOGRAM_CURVE_118"), ",") + 1);
			else if (strstr(buf, "LOW_HISTOGRAM_CURVE_119"))					reg2->LOW_HISTOGRAM_CURVE[119] = atoi(strstr(strstr(buf, "LOW_HISTOGRAM_CURVE_119"), ",") + 1);
			else if (strstr(buf, "LOW_HISTOGRAM_CURVE_120"))					reg2->LOW_HISTOGRAM_CURVE[120] = atoi(strstr(strstr(buf, "LOW_HISTOGRAM_CURVE_120"), ",") + 1);
			else if (strstr(buf, "LOW_HISTOGRAM_CURVE_121"))					reg2->LOW_HISTOGRAM_CURVE[121] = atoi(strstr(strstr(buf, "LOW_HISTOGRAM_CURVE_121"), ",") + 1);
			else if (strstr(buf, "LOW_HISTOGRAM_CURVE_122"))					reg2->LOW_HISTOGRAM_CURVE[122] = atoi(strstr(strstr(buf, "LOW_HISTOGRAM_CURVE_122"), ",") + 1);
			else if (strstr(buf, "LOW_HISTOGRAM_CURVE_123"))					reg2->LOW_HISTOGRAM_CURVE[123] = atoi(strstr(strstr(buf, "LOW_HISTOGRAM_CURVE_123"), ",") + 1);
			else if (strstr(buf, "LOW_HISTOGRAM_CURVE_124"))					reg2->LOW_HISTOGRAM_CURVE[124] = atoi(strstr(strstr(buf, "LOW_HISTOGRAM_CURVE_124"), ",") + 1);
			else if (strstr(buf, "LOW_HISTOGRAM_CURVE_125"))					reg2->LOW_HISTOGRAM_CURVE[125] = atoi(strstr(strstr(buf, "LOW_HISTOGRAM_CURVE_125"), ",") + 1);
			else if (strstr(buf, "LOW_HISTOGRAM_CURVE_126"))					reg2->LOW_HISTOGRAM_CURVE[126] = atoi(strstr(strstr(buf, "LOW_HISTOGRAM_CURVE_126"), ",") + 1);
			else if (strstr(buf, "LOW_HISTOGRAM_CURVE_127"))					reg2->LOW_HISTOGRAM_CURVE[127] = atoi(strstr(strstr(buf, "LOW_HISTOGRAM_CURVE_127"), ",") + 1);
			else;
		}
	}
	fclose(pFile);



	if ((pFile = fopen(filename, "rt")) == NULL)
	{
		printf("Open REG File Error\n");
		system("pause");
	}
	else
	{
		while (fgets(buf, 256, pFile))
		{
			if (strstr(buf, "CONTENT_RATIO_00"))					    reg2->CONTENT_RATIO[0] = atoi(strstr(strstr(buf, "CONTENT_RATIO_00"), ",") + 1);
			else if (strstr(buf, "CONTENT_RATIO_01"))					    reg2->CONTENT_RATIO[1] = atoi(strstr(strstr(buf, "CONTENT_RATIO_01"), ",") + 1);
			else if (strstr(buf, "CONTENT_RATIO_02"))					    reg2->CONTENT_RATIO[2] = atoi(strstr(strstr(buf, "CONTENT_RATIO_02"), ",") + 1);
			else if (strstr(buf, "CONTENT_RATIO_03"))					    reg2->CONTENT_RATIO[3] = atoi(strstr(strstr(buf, "CONTENT_RATIO_03"), ",") + 1);
			else if (strstr(buf, "CONTENT_RATIO_04"))					    reg2->CONTENT_RATIO[4] = atoi(strstr(strstr(buf, "CONTENT_RATIO_04"), ",") + 1);
			else if (strstr(buf, "CONTENT_RATIO_05"))					    reg2->CONTENT_RATIO[5] = atoi(strstr(strstr(buf, "CONTENT_RATIO_05"), ",") + 1);
			else if (strstr(buf, "CONTENT_RATIO_06"))					    reg2->CONTENT_RATIO[6] = atoi(strstr(strstr(buf, "CONTENT_RATIO_06"), ",") + 1);
			else if (strstr(buf, "CONTENT_RATIO_07"))					    reg2->CONTENT_RATIO[7] = atoi(strstr(strstr(buf, "CONTENT_RATIO_07"), ",") + 1);
			else if (strstr(buf, "CONTENT_RATIO_08"))					    reg2->CONTENT_RATIO[8] = atoi(strstr(strstr(buf, "CONTENT_RATIO_08"), ",") + 1);
			else if (strstr(buf, "CONTENT_RATIO_09"))					    reg2->CONTENT_RATIO[9] = atoi(strstr(strstr(buf, "CONTENT_RATIO_09"), ",") + 1);
			else if (strstr(buf, "CONTENT_RATIO_10"))					    reg2->CONTENT_RATIO[10] = atoi(strstr(strstr(buf, "CONTENT_RATIO_10"), ",") + 1);
			else if (strstr(buf, "CONTENT_RATIO_11"))					    reg2->CONTENT_RATIO[11] = atoi(strstr(strstr(buf, "CONTENT_RATIO_11"), ",") + 1);
			else if (strstr(buf, "CONTENT_RATIO_12"))					    reg2->CONTENT_RATIO[12] = atoi(strstr(strstr(buf, "CONTENT_RATIO_12"), ",") + 1);
			else if (strstr(buf, "CONTENT_RATIO_13"))					    reg2->CONTENT_RATIO[13] = atoi(strstr(strstr(buf, "CONTENT_RATIO_13"), ",") + 1);
			else if (strstr(buf, "CONTENT_RATIO_14"))					    reg2->CONTENT_RATIO[14] = atoi(strstr(strstr(buf, "CONTENT_RATIO_14"), ",") + 1);
			else if (strstr(buf, "CONTENT_RATIO_15"))					    reg2->CONTENT_RATIO[15] = atoi(strstr(strstr(buf, "CONTENT_RATIO_15"), ",") + 1);
			else if (strstr(buf, "CONTENT_RATIO_16"))					    reg2->CONTENT_RATIO[16] = atoi(strstr(strstr(buf, "CONTENT_RATIO_16"), ",") + 1);
			else if (strstr(buf, "CONTENT_RATIO_17"))					    reg2->CONTENT_RATIO[17] = atoi(strstr(strstr(buf, "CONTENT_RATIO_17"), ",") + 1);
			else if (strstr(buf, "CONTENT_RATIO_18"))					    reg2->CONTENT_RATIO[18] = atoi(strstr(strstr(buf, "CONTENT_RATIO_18"), ",") + 1);
			else if (strstr(buf, "CONTENT_RATIO_19"))					    reg2->CONTENT_RATIO[19] = atoi(strstr(strstr(buf, "CONTENT_RATIO_19"), ",") + 1);
			else if (strstr(buf, "CONTENT_RATIO_20"))					    reg2->CONTENT_RATIO[20] = atoi(strstr(strstr(buf, "CONTENT_RATIO_20"), ",") + 1);
			else if (strstr(buf, "CONTENT_RATIO_21"))					    reg2->CONTENT_RATIO[21] = atoi(strstr(strstr(buf, "CONTENT_RATIO_21"), ",") + 1);
			else if (strstr(buf, "CONTENT_RATIO_22"))					    reg2->CONTENT_RATIO[22] = atoi(strstr(strstr(buf, "CONTENT_RATIO_22"), ",") + 1);
			else if (strstr(buf, "CONTENT_RATIO_23"))					    reg2->CONTENT_RATIO[23] = atoi(strstr(strstr(buf, "CONTENT_RATIO_23"), ",") + 1);
			else if (strstr(buf, "CONTENT_RATIO_24"))					    reg2->CONTENT_RATIO[24] = atoi(strstr(strstr(buf, "CONTENT_RATIO_24"), ",") + 1);
			else if (strstr(buf, "CONTENT_RATIO_25"))					    reg2->CONTENT_RATIO[25] = atoi(strstr(strstr(buf, "CONTENT_RATIO_25"), ",") + 1);
			else if (strstr(buf, "CONTENT_RATIO_26"))					    reg2->CONTENT_RATIO[26] = atoi(strstr(strstr(buf, "CONTENT_RATIO_26"), ",") + 1);
			else if (strstr(buf, "CONTENT_RATIO_27"))					    reg2->CONTENT_RATIO[27] = atoi(strstr(strstr(buf, "CONTENT_RATIO_27"), ",") + 1);
			else if (strstr(buf, "CONTENT_RATIO_28"))					    reg2->CONTENT_RATIO[28] = atoi(strstr(strstr(buf, "CONTENT_RATIO_28"), ",") + 1);
			else if (strstr(buf, "CONTENT_RATIO_29"))					    reg2->CONTENT_RATIO[29] = atoi(strstr(strstr(buf, "CONTENT_RATIO_29"), ",") + 1);
			else if (strstr(buf, "CONTENT_RATIO_30"))					    reg2->CONTENT_RATIO[30] = atoi(strstr(strstr(buf, "CONTENT_RATIO_30"), ",") + 1);
			else if (strstr(buf, "CONTENT_RATIO_31"))					    reg2->CONTENT_RATIO[31] = atoi(strstr(strstr(buf, "CONTENT_RATIO_31"), ",") + 1);
			else if (strstr(buf, "CONTENT_RATIO_32"))					    reg2->CONTENT_RATIO[32] = atoi(strstr(strstr(buf, "CONTENT_RATIO_32"), ",") + 1);

			else if (strstr(buf, "LENH_RATIO_00"))					    reg2->LENH_RATIO[0] = atoi(strstr(strstr(buf, "LENH_RATIO_00"), ",") + 1);
			else if (strstr(buf, "LENH_RATIO_01"))					    reg2->LENH_RATIO[1] = atoi(strstr(strstr(buf, "LENH_RATIO_01"), ",") + 1);
			else if (strstr(buf, "LENH_RATIO_02"))					    reg2->LENH_RATIO[2] = atoi(strstr(strstr(buf, "LENH_RATIO_02"), ",") + 1);
			else if (strstr(buf, "LENH_RATIO_03"))					    reg2->LENH_RATIO[3] = atoi(strstr(strstr(buf, "LENH_RATIO_03"), ",") + 1);
			else if (strstr(buf, "LENH_RATIO_04"))					    reg2->LENH_RATIO[4] = atoi(strstr(strstr(buf, "LENH_RATIO_04"), ",") + 1);
			else if (strstr(buf, "LENH_RATIO_05"))					    reg2->LENH_RATIO[5] = atoi(strstr(strstr(buf, "LENH_RATIO_05"), ",") + 1);
			else if (strstr(buf, "LENH_RATIO_06"))					    reg2->LENH_RATIO[6] = atoi(strstr(strstr(buf, "LENH_RATIO_06"), ",") + 1);
			else if (strstr(buf, "LENH_RATIO_07"))					    reg2->LENH_RATIO[7] = atoi(strstr(strstr(buf, "LENH_RATIO_07"), ",") + 1);
			else if (strstr(buf, "LENH_RATIO_08"))					    reg2->LENH_RATIO[8] = atoi(strstr(strstr(buf, "LENH_RATIO_08"), ",") + 1);
			else if (strstr(buf, "LENH_RATIO_09"))					    reg2->LENH_RATIO[9] = atoi(strstr(strstr(buf, "LENH_RATIO_09"), ",") + 1);
			else if (strstr(buf, "LENH_RATIO_10"))					    reg2->LENH_RATIO[10] = atoi(strstr(strstr(buf, "LENH_RATIO_10"), ",") + 1);
			else if (strstr(buf, "LENH_RATIO_11"))					    reg2->LENH_RATIO[11] = atoi(strstr(strstr(buf, "LENH_RATIO_11"), ",") + 1);
			else if (strstr(buf, "LENH_RATIO_12"))					    reg2->LENH_RATIO[12] = atoi(strstr(strstr(buf, "LENH_RATIO_12"), ",") + 1);
			else if (strstr(buf, "LENH_RATIO_13"))					    reg2->LENH_RATIO[13] = atoi(strstr(strstr(buf, "LENH_RATIO_13"), ",") + 1);
			else if (strstr(buf, "LENH_RATIO_14"))					    reg2->LENH_RATIO[14] = atoi(strstr(strstr(buf, "LENH_RATIO_14"), ",") + 1);
			else if (strstr(buf, "LENH_RATIO_15"))					    reg2->LENH_RATIO[15] = atoi(strstr(strstr(buf, "LENH_RATIO_15"), ",") + 1);
			else if (strstr(buf, "LENH_RATIO_16"))					    reg2->LENH_RATIO[16] = atoi(strstr(strstr(buf, "LENH_RATIO_16"), ",") + 1);
			else if (strstr(buf, "LENH_RATIO_17"))					    reg2->LENH_RATIO[17] = atoi(strstr(strstr(buf, "LENH_RATIO_17"), ",") + 1);
			else if (strstr(buf, "LENH_RATIO_18"))					    reg2->LENH_RATIO[18] = atoi(strstr(strstr(buf, "LENH_RATIO_18"), ",") + 1);
			else if (strstr(buf, "LENH_RATIO_19"))					    reg2->LENH_RATIO[19] = atoi(strstr(strstr(buf, "LENH_RATIO_19"), ",") + 1);
			else if (strstr(buf, "LENH_RATIO_20"))					    reg2->LENH_RATIO[20] = atoi(strstr(strstr(buf, "LENH_RATIO_20"), ",") + 1);
			else if (strstr(buf, "LENH_RATIO_21"))					    reg2->LENH_RATIO[21] = atoi(strstr(strstr(buf, "LENH_RATIO_21"), ",") + 1);
			else if (strstr(buf, "LENH_RATIO_22"))					    reg2->LENH_RATIO[22] = atoi(strstr(strstr(buf, "LENH_RATIO_22"), ",") + 1);
			else if (strstr(buf, "LENH_RATIO_23"))					    reg2->LENH_RATIO[23] = atoi(strstr(strstr(buf, "LENH_RATIO_23"), ",") + 1);
			else if (strstr(buf, "LENH_RATIO_24"))					    reg2->LENH_RATIO[24] = atoi(strstr(strstr(buf, "LENH_RATIO_24"), ",") + 1);
			else if (strstr(buf, "LENH_RATIO_25"))					    reg2->LENH_RATIO[25] = atoi(strstr(strstr(buf, "LENH_RATIO_25"), ",") + 1);
			else if (strstr(buf, "LENH_RATIO_26"))					    reg2->LENH_RATIO[26] = atoi(strstr(strstr(buf, "LENH_RATIO_26"), ",") + 1);
			else if (strstr(buf, "LENH_RATIO_27"))					    reg2->LENH_RATIO[27] = atoi(strstr(strstr(buf, "LENH_RATIO_27"), ",") + 1);
			else if (strstr(buf, "LENH_RATIO_28"))					    reg2->LENH_RATIO[28] = atoi(strstr(strstr(buf, "LENH_RATIO_28"), ",") + 1);
			else if (strstr(buf, "LENH_RATIO_29"))					    reg2->LENH_RATIO[29] = atoi(strstr(strstr(buf, "LENH_RATIO_29"), ",") + 1);
			else if (strstr(buf, "LENH_RATIO_30"))					    reg2->LENH_RATIO[30] = atoi(strstr(strstr(buf, "LENH_RATIO_30"), ",") + 1);
			else if (strstr(buf, "LENH_RATIO_31"))					    reg2->LENH_RATIO[31] = atoi(strstr(strstr(buf, "LENH_RATIO_31"), ",") + 1);
			else if (strstr(buf, "LENH_RATIO_32"))					    reg2->LENH_RATIO[32] = atoi(strstr(strstr(buf, "LENH_RATIO_32"), ",") + 1);
			else if (strstr(buf, "LENH_RATIO_33"))					    reg2->LENH_RATIO[33] = atoi(strstr(strstr(buf, "LENH_RATIO_33"), ",") + 1);
			else if (strstr(buf, "LENH_RATIO_34"))					    reg2->LENH_RATIO[34] = atoi(strstr(strstr(buf, "LENH_RATIO_34"), ",") + 1);
			else if (strstr(buf, "LENH_RATIO_35"))					    reg2->LENH_RATIO[35] = atoi(strstr(strstr(buf, "LENH_RATIO_35"), ",") + 1);
			else if (strstr(buf, "LENH_RATIO_36"))					    reg2->LENH_RATIO[36] = atoi(strstr(strstr(buf, "LENH_RATIO_36"), ",") + 1);
			else if (strstr(buf, "LENH_RATIO_37"))					    reg2->LENH_RATIO[37] = atoi(strstr(strstr(buf, "LENH_RATIO_37"), ",") + 1);
			else if (strstr(buf, "LENH_RATIO_38"))					    reg2->LENH_RATIO[38] = atoi(strstr(strstr(buf, "LENH_RATIO_38"), ",") + 1);
			else if (strstr(buf, "LENH_RATIO_39"))					    reg2->LENH_RATIO[39] = atoi(strstr(strstr(buf, "LENH_RATIO_39"), ",") + 1);
			else if (strstr(buf, "LENH_RATIO_40"))					    reg2->LENH_RATIO[40] = atoi(strstr(strstr(buf, "LENH_RATIO_40"), ",") + 1);
			else if (strstr(buf, "LENH_RATIO_41"))					    reg2->LENH_RATIO[41] = atoi(strstr(strstr(buf, "LENH_RATIO_41"), ",") + 1);
			else if (strstr(buf, "LENH_RATIO_42"))					    reg2->LENH_RATIO[42] = atoi(strstr(strstr(buf, "LENH_RATIO_42"), ",") + 1);
			else if (strstr(buf, "LENH_RATIO_43"))					    reg2->LENH_RATIO[43] = atoi(strstr(strstr(buf, "LENH_RATIO_43"), ",") + 1);
			else if (strstr(buf, "LENH_RATIO_44"))					    reg2->LENH_RATIO[44] = atoi(strstr(strstr(buf, "LENH_RATIO_44"), ",") + 1);
			else if (strstr(buf, "LENH_RATIO_45"))					    reg2->LENH_RATIO[45] = atoi(strstr(strstr(buf, "LENH_RATIO_45"), ",") + 1);
			else if (strstr(buf, "LENH_RATIO_46"))					    reg2->LENH_RATIO[46] = atoi(strstr(strstr(buf, "LENH_RATIO_46"), ",") + 1);
			else if (strstr(buf, "LENH_RATIO_47"))					    reg2->LENH_RATIO[47] = atoi(strstr(strstr(buf, "LENH_RATIO_47"), ",") + 1);
			else if (strstr(buf, "LENH_RATIO_48"))					    reg2->LENH_RATIO[48] = atoi(strstr(strstr(buf, "LENH_RATIO_48"), ",") + 1);
			else if (strstr(buf, "LENH_RATIO_49"))					    reg2->LENH_RATIO[49] = atoi(strstr(strstr(buf, "LENH_RATIO_49"), ",") + 1);
			else if (strstr(buf, "LENH_RATIO_50"))					    reg2->LENH_RATIO[50] = atoi(strstr(strstr(buf, "LENH_RATIO_50"), ",") + 1);
			else if (strstr(buf, "LENH_RATIO_51"))					    reg2->LENH_RATIO[51] = atoi(strstr(strstr(buf, "LENH_RATIO_51"), ",") + 1);
			else if (strstr(buf, "LENH_RATIO_52"))					    reg2->LENH_RATIO[52] = atoi(strstr(strstr(buf, "LENH_RATIO_52"), ",") + 1);
			else if (strstr(buf, "LENH_RATIO_53"))					    reg2->LENH_RATIO[53] = atoi(strstr(strstr(buf, "LENH_RATIO_53"), ",") + 1);
			else if (strstr(buf, "LENH_RATIO_54"))					    reg2->LENH_RATIO[54] = atoi(strstr(strstr(buf, "LENH_RATIO_54"), ",") + 1);
			else if (strstr(buf, "LENH_RATIO_55"))					    reg2->LENH_RATIO[55] = atoi(strstr(strstr(buf, "LENH_RATIO_55"), ",") + 1);
			else if (strstr(buf, "LENH_RATIO_56"))					    reg2->LENH_RATIO[56] = atoi(strstr(strstr(buf, "LENH_RATIO_56"), ",") + 1);
			else if (strstr(buf, "LENH_RATIO_57"))					    reg2->LENH_RATIO[57] = atoi(strstr(strstr(buf, "LENH_RATIO_57"), ",") + 1);
			else if (strstr(buf, "LENH_RATIO_58"))					    reg2->LENH_RATIO[58] = atoi(strstr(strstr(buf, "LENH_RATIO_58"), ",") + 1);
			else if (strstr(buf, "LENH_RATIO_59"))					    reg2->LENH_RATIO[59] = atoi(strstr(strstr(buf, "LENH_RATIO_59"), ",") + 1);
			else if (strstr(buf, "LENH_RATIO_60"))					    reg2->LENH_RATIO[60] = atoi(strstr(strstr(buf, "LENH_RATIO_60"), ",") + 1);
			else if (strstr(buf, "LENH_RATIO_61"))					    reg2->LENH_RATIO[61] = atoi(strstr(strstr(buf, "LENH_RATIO_61"), ",") + 1);
			else if (strstr(buf, "LENH_RATIO_62"))					    reg2->LENH_RATIO[62] = atoi(strstr(strstr(buf, "LENH_RATIO_62"), ",") + 1);
			else if (strstr(buf, "LENH_RATIO_63"))					    reg2->LENH_RATIO[63] = atoi(strstr(strstr(buf, "LENH_RATIO_63"), ",") + 1);

			else if (strstr(buf, "TEMPORAL_FILTER_00"))					    reg2->TEMPORAL_FILTER[0] = atoi(strstr(strstr(buf, "TEMPORAL_FILTER_00"), ",") + 1);
			else if (strstr(buf, "TEMPORAL_FILTER_01"))					    reg2->TEMPORAL_FILTER[1] = atoi(strstr(strstr(buf, "TEMPORAL_FILTER_01"), ",") + 1);
			else if (strstr(buf, "TEMPORAL_FILTER_02"))					    reg2->TEMPORAL_FILTER[2] = atoi(strstr(strstr(buf, "TEMPORAL_FILTER_02"), ",") + 1);
			else if (strstr(buf, "TEMPORAL_FILTER_03"))					    reg2->TEMPORAL_FILTER[3] = atoi(strstr(strstr(buf, "TEMPORAL_FILTER_03"), ",") + 1);
			else if (strstr(buf, "TEMPORAL_FILTER_04"))					    reg2->TEMPORAL_FILTER[4] = atoi(strstr(strstr(buf, "TEMPORAL_FILTER_04"), ",") + 1);
			else if (strstr(buf, "TEMPORAL_FILTER_05"))					    reg2->TEMPORAL_FILTER[5] = atoi(strstr(strstr(buf, "TEMPORAL_FILTER_05"), ",") + 1);
			else if (strstr(buf, "TEMPORAL_FILTER_06"))					    reg2->TEMPORAL_FILTER[6] = atoi(strstr(strstr(buf, "TEMPORAL_FILTER_06"), ",") + 1);
			else if (strstr(buf, "TEMPORAL_FILTER_07"))					    reg2->TEMPORAL_FILTER[7] = atoi(strstr(strstr(buf, "TEMPORAL_FILTER_07"), ",") + 1);
			else if (strstr(buf, "TEMPORAL_FILTER_08"))					    reg2->TEMPORAL_FILTER[8] = atoi(strstr(strstr(buf, "TEMPORAL_FILTER_08"), ",") + 1);
			else if (strstr(buf, "TEMPORAL_FILTER_09"))					    reg2->TEMPORAL_FILTER[9] = atoi(strstr(strstr(buf, "TEMPORAL_FILTER_09"), ",") + 1);
			else if (strstr(buf, "TEMPORAL_FILTER_10"))					    reg2->TEMPORAL_FILTER[10] = atoi(strstr(strstr(buf, "TEMPORAL_FILTER_10"), ",") + 1);
			else if (strstr(buf, "TEMPORAL_FILTER_11"))					    reg2->TEMPORAL_FILTER[11] = atoi(strstr(strstr(buf, "TEMPORAL_FILTER_11"), ",") + 1);
			else if (strstr(buf, "TEMPORAL_FILTER_12"))					    reg2->TEMPORAL_FILTER[12] = atoi(strstr(strstr(buf, "TEMPORAL_FILTER_12"), ",") + 1);
			else if (strstr(buf, "TEMPORAL_FILTER_13"))					    reg2->TEMPORAL_FILTER[13] = atoi(strstr(strstr(buf, "TEMPORAL_FILTER_13"), ",") + 1);
			else if (strstr(buf, "TEMPORAL_FILTER_14"))					    reg2->TEMPORAL_FILTER[14] = atoi(strstr(strstr(buf, "TEMPORAL_FILTER_14"), ",") + 1);
			else if (strstr(buf, "TEMPORAL_FILTER_15"))					    reg2->TEMPORAL_FILTER[15] = atoi(strstr(strstr(buf, "TEMPORAL_FILTER_15"), ",") + 1);
			else if (strstr(buf, "TEMPORAL_FILTER_16"))					    reg2->TEMPORAL_FILTER[16] = atoi(strstr(strstr(buf, "TEMPORAL_FILTER_16"), ",") + 1);
			else if (strstr(buf, "TEMPORAL_FILTER_17"))					    reg2->TEMPORAL_FILTER[17] = atoi(strstr(strstr(buf, "TEMPORAL_FILTER_17"), ",") + 1);
			else if (strstr(buf, "TEMPORAL_FILTER_18"))					    reg2->TEMPORAL_FILTER[18] = atoi(strstr(strstr(buf, "TEMPORAL_FILTER_18"), ",") + 1);
			else if (strstr(buf, "TEMPORAL_FILTER_19"))					    reg2->TEMPORAL_FILTER[19] = atoi(strstr(strstr(buf, "TEMPORAL_FILTER_19"), ",") + 1);
			else if (strstr(buf, "TEMPORAL_FILTER_20"))					    reg2->TEMPORAL_FILTER[20] = atoi(strstr(strstr(buf, "TEMPORAL_FILTER_20"), ",") + 1);
			else if (strstr(buf, "TEMPORAL_FILTER_21"))					    reg2->TEMPORAL_FILTER[21] = atoi(strstr(strstr(buf, "TEMPORAL_FILTER_21"), ",") + 1);
			else if (strstr(buf, "TEMPORAL_FILTER_22"))					    reg2->TEMPORAL_FILTER[22] = atoi(strstr(strstr(buf, "TEMPORAL_FILTER_22"), ",") + 1);
			else if (strstr(buf, "TEMPORAL_FILTER_23"))					    reg2->TEMPORAL_FILTER[23] = atoi(strstr(strstr(buf, "TEMPORAL_FILTER_23"), ",") + 1);
			else if (strstr(buf, "TEMPORAL_FILTER_24"))					    reg2->TEMPORAL_FILTER[24] = atoi(strstr(strstr(buf, "TEMPORAL_FILTER_24"), ",") + 1);
			else if (strstr(buf, "TEMPORAL_FILTER_25"))					    reg2->TEMPORAL_FILTER[25] = atoi(strstr(strstr(buf, "TEMPORAL_FILTER_25"), ",") + 1);
			else if (strstr(buf, "TEMPORAL_FILTER_26"))					    reg2->TEMPORAL_FILTER[26] = atoi(strstr(strstr(buf, "TEMPORAL_FILTER_26"), ",") + 1);
			else if (strstr(buf, "TEMPORAL_FILTER_27"))					    reg2->TEMPORAL_FILTER[27] = atoi(strstr(strstr(buf, "TEMPORAL_FILTER_27"), ",") + 1);
			else if (strstr(buf, "TEMPORAL_FILTER_28"))					    reg2->TEMPORAL_FILTER[28] = atoi(strstr(strstr(buf, "TEMPORAL_FILTER_28"), ",") + 1);
			else if (strstr(buf, "TEMPORAL_FILTER_29"))					    reg2->TEMPORAL_FILTER[29] = atoi(strstr(strstr(buf, "TEMPORAL_FILTER_29"), ",") + 1);
			else if (strstr(buf, "TEMPORAL_FILTER_30"))					    reg2->TEMPORAL_FILTER[30] = atoi(strstr(strstr(buf, "TEMPORAL_FILTER_30"), ",") + 1);
			else if (strstr(buf, "TEMPORAL_FILTER_31"))					    reg2->TEMPORAL_FILTER[31] = atoi(strstr(strstr(buf, "TEMPORAL_FILTER_31"), ",") + 1);

			else;
		}
	}
	fclose(pFile);

	return reg2;
}

REG3* Register_ParametersSetting_by_global(char* filename)
{
	REG3* reg3 = (REG3*)calloc(1, sizeof(REG3));

	char buf[128];
	FILE* pFile;

	if ((pFile = fopen(filename, "rt")) == NULL)
	{
		printf("Open REG File Error\n");
		system("pause");
	}
	else
	{
		while (fgets(buf, 128, pFile))
		{
			if (strstr(buf, "LENH_EXTERNAL"))		     reg3->LENH_EXTERNAL = atoi(strstr(strstr(buf, "LENH_EXTERNAL"), ",") + 1);
			//else if (strstr(buf, "LENH_INITIAL"))			 reg3->LENH_INITIAL = atoi(strstr(strstr(buf, "LENH_INITIAL"), ",") + 1);
			else if (strstr(buf, "LENH_UPDATE_NUMBER"))	 reg3->LENH_UPDATE_NUMBER = atoi(strstr(strstr(buf, "LENH_UPDATE_NUMBER"), ",") + 1);
			else;
		}
		fclose(pFile);

	}

	return reg3;
}

REG4* Register_ParametersSetting_by_cdc(char* filename)
{
	REG4* reg4 = (REG4*)calloc(1, sizeof(REG4));
	reg4->FRC = (int*)calloc(112, sizeof(int));
	reg4->DITHER = (int*)calloc(14, sizeof(int));


	char buf[256];
	FILE* pFile;

	if ((pFile = fopen(filename, "rt")) == NULL)
	{
		printf("Open REG File Error\n");
		system("pause");
	}
	else
	{
		while (fgets(buf, 256, pFile))
		{
			if (strstr(buf, "VP_VPROCCTL0"))		                reg4->VP_VPROCCTL0 = atoi(strstr(strstr(buf, "VP_VPROCCTL0"), ",") + 1);
			else if (strstr(buf, "VP_VPROCCTL1"))					reg4->VP_VPROCCTL1 = atoi(strstr(strstr(buf, "VP_VPROCCTL1"), ",") + 1);
			else if (strstr(buf, "VP_VPROCCTL2"))			        reg4->VP_VPROCCTL2 = atoi(strstr(strstr(buf, "VP_VPROCCTL2"), ",") + 1);
			else if (strstr(buf, "VP_DITH_CTRL"))		            reg4->VP_DITH_CTRL = atoi(strstr(strstr(buf, "VP_DITH_CTRL"), ",") + 1);
			else if (strstr(buf, "VP_FRC_CDEPTH"))			        reg4->VP_FRC_CDEPTH = atoi(strstr(strstr(buf, "VP_FRC_CDEPTH"), ",") + 1);
			else if (strstr(buf, "VP_FRC_CTRL"))	                reg4->VP_FRC_CTRL = atoi(strstr(strstr(buf, "VP_FRC_CTRL"), ",") + 1);
			else if (strstr(buf, "VP_CEXP_BAND0"))					reg4->VP_CEXP_BAND0 = atoi(strstr(strstr(buf, "VP_CEXP_BAND0"), ",") + 1);
			else if (strstr(buf, "VP_CEXP_BAND1"))					reg4->VP_CEXP_BAND1 = atoi(strstr(strstr(buf, "VP_CEXP_BAND1"), ",") + 1);
			else if (strstr(buf, "VP_CEXP_BAND2"))					reg4->VP_CEXP_BAND2 = atoi(strstr(strstr(buf, "VP_CEXP_BAND2"), ",") + 1);
			else if (strstr(buf, "VP_FS_START0"))					reg4->VP_FS_START0 = atoi(strstr(strstr(buf, "VP_FS_START0"), ",") + 1);
			else if (strstr(buf, "VP_FS_START1"))					reg4->VP_FS_START1 = atoi(strstr(strstr(buf, "VP_FS_START1"), ",") + 1);
			else;
		}
	}

	if ((pFile = fopen(filename, "rt")) == NULL)
	{
		printf("Open REG File Error\n");
		system("pause");
	}
	else
	{
		while (fgets(buf, 256, pFile))
		{
			if (strstr(buf, "FRC_000"))					        reg4->FRC[0] = atoi(strstr(strstr(buf, "FRC_000"), ",") + 1);
			else if (strstr(buf, "FRC_001"))					reg4->FRC[1] = atoi(strstr(strstr(buf, "FRC_001"), ",") + 1);
			else if (strstr(buf, "FRC_002"))					reg4->FRC[2] = atoi(strstr(strstr(buf, "FRC_002"), ",") + 1);
			else if (strstr(buf, "FRC_003"))					reg4->FRC[3] = atoi(strstr(strstr(buf, "FRC_003"), ",") + 1);
			else if (strstr(buf, "FRC_004"))					reg4->FRC[4] = atoi(strstr(strstr(buf, "FRC_004"), ",") + 1);
			else if (strstr(buf, "FRC_005"))					reg4->FRC[5] = atoi(strstr(strstr(buf, "FRC_005"), ",") + 1);
			else if (strstr(buf, "FRC_006"))					reg4->FRC[6] = atoi(strstr(strstr(buf, "FRC_006"), ",") + 1);
			else if (strstr(buf, "FRC_007"))					reg4->FRC[7] = atoi(strstr(strstr(buf, "FRC_007"), ",") + 1);
			else if (strstr(buf, "FRC_008"))					reg4->FRC[8] = atoi(strstr(strstr(buf, "FRC_008"), ",") + 1);
			else if (strstr(buf, "FRC_009"))					reg4->FRC[9] = atoi(strstr(strstr(buf, "FRC_009"), ",") + 1);
			else if (strstr(buf, "FRC_010"))					reg4->FRC[10] = atoi(strstr(strstr(buf, "FRC_010"), ",") + 1);
			else if (strstr(buf, "FRC_011"))					reg4->FRC[11] = atoi(strstr(strstr(buf, "FRC_011"), ",") + 1);
			else if (strstr(buf, "FRC_012"))					reg4->FRC[12] = atoi(strstr(strstr(buf, "FRC_012"), ",") + 1);
			else if (strstr(buf, "FRC_013"))					reg4->FRC[13] = atoi(strstr(strstr(buf, "FRC_013"), ",") + 1);
			else if (strstr(buf, "FRC_014"))					reg4->FRC[14] = atoi(strstr(strstr(buf, "FRC_014"), ",") + 1);
			else if (strstr(buf, "FRC_015"))					reg4->FRC[15] = atoi(strstr(strstr(buf, "FRC_015"), ",") + 1);
			else if (strstr(buf, "FRC_016"))					reg4->FRC[16] = atoi(strstr(strstr(buf, "FRC_016"), ",") + 1);
			else if (strstr(buf, "FRC_017"))					reg4->FRC[17] = atoi(strstr(strstr(buf, "FRC_017"), ",") + 1);
			else if (strstr(buf, "FRC_018"))					reg4->FRC[18] = atoi(strstr(strstr(buf, "FRC_018"), ",") + 1);
			else if (strstr(buf, "FRC_019"))					reg4->FRC[19] = atoi(strstr(strstr(buf, "FRC_019"), ",") + 1);
			else if (strstr(buf, "FRC_020"))					reg4->FRC[20] = atoi(strstr(strstr(buf, "FRC_020"), ",") + 1);
			else if (strstr(buf, "FRC_021"))					reg4->FRC[21] = atoi(strstr(strstr(buf, "FRC_021"), ",") + 1);
			else if (strstr(buf, "FRC_022"))					reg4->FRC[22] = atoi(strstr(strstr(buf, "FRC_022"), ",") + 1);
			else if (strstr(buf, "FRC_023"))					reg4->FRC[23] = atoi(strstr(strstr(buf, "FRC_023"), ",") + 1);
			else if (strstr(buf, "FRC_024"))					reg4->FRC[24] = atoi(strstr(strstr(buf, "FRC_024"), ",") + 1);
			else if (strstr(buf, "FRC_025"))					reg4->FRC[25] = atoi(strstr(strstr(buf, "FRC_025"), ",") + 1);
			else if (strstr(buf, "FRC_026"))					reg4->FRC[26] = atoi(strstr(strstr(buf, "FRC_026"), ",") + 1);
			else if (strstr(buf, "FRC_027"))					reg4->FRC[27] = atoi(strstr(strstr(buf, "FRC_027"), ",") + 1);
			else if (strstr(buf, "FRC_028"))					reg4->FRC[28] = atoi(strstr(strstr(buf, "FRC_028"), ",") + 1);
			else if (strstr(buf, "FRC_029"))					reg4->FRC[29] = atoi(strstr(strstr(buf, "FRC_029"), ",") + 1);
			else if (strstr(buf, "FRC_030"))					reg4->FRC[30] = atoi(strstr(strstr(buf, "FRC_030"), ",") + 1);
			else if (strstr(buf, "FRC_031"))					reg4->FRC[31] = atoi(strstr(strstr(buf, "FRC_031"), ",") + 1);
			else if (strstr(buf, "FRC_032"))					reg4->FRC[32] = atoi(strstr(strstr(buf, "FRC_032"), ",") + 1);
			else if (strstr(buf, "FRC_033"))					reg4->FRC[33] = atoi(strstr(strstr(buf, "FRC_033"), ",") + 1);
			else if (strstr(buf, "FRC_034"))					reg4->FRC[34] = atoi(strstr(strstr(buf, "FRC_034"), ",") + 1);
			else if (strstr(buf, "FRC_035"))					reg4->FRC[35] = atoi(strstr(strstr(buf, "FRC_035"), ",") + 1);
			else if (strstr(buf, "FRC_036"))					reg4->FRC[36] = atoi(strstr(strstr(buf, "FRC_036"), ",") + 1);
			else if (strstr(buf, "FRC_037"))					reg4->FRC[37] = atoi(strstr(strstr(buf, "FRC_037"), ",") + 1);
			else if (strstr(buf, "FRC_038"))					reg4->FRC[38] = atoi(strstr(strstr(buf, "FRC_038"), ",") + 1);
			else if (strstr(buf, "FRC_039"))					reg4->FRC[39] = atoi(strstr(strstr(buf, "FRC_039"), ",") + 1);
			else if (strstr(buf, "FRC_040"))					reg4->FRC[40] = atoi(strstr(strstr(buf, "FRC_040"), ",") + 1);
			else if (strstr(buf, "FRC_041"))					reg4->FRC[41] = atoi(strstr(strstr(buf, "FRC_041"), ",") + 1);
			else if (strstr(buf, "FRC_042"))					reg4->FRC[42] = atoi(strstr(strstr(buf, "FRC_042"), ",") + 1);
			else if (strstr(buf, "FRC_043"))					reg4->FRC[43] = atoi(strstr(strstr(buf, "FRC_043"), ",") + 1);
			else if (strstr(buf, "FRC_044"))					reg4->FRC[44] = atoi(strstr(strstr(buf, "FRC_044"), ",") + 1);
			else if (strstr(buf, "FRC_045"))					reg4->FRC[45] = atoi(strstr(strstr(buf, "FRC_045"), ",") + 1);
			else if (strstr(buf, "FRC_046"))					reg4->FRC[46] = atoi(strstr(strstr(buf, "FRC_046"), ",") + 1);
			else if (strstr(buf, "FRC_047"))					reg4->FRC[47] = atoi(strstr(strstr(buf, "FRC_047"), ",") + 1);
			else if (strstr(buf, "FRC_048"))					reg4->FRC[48] = atoi(strstr(strstr(buf, "FRC_048"), ",") + 1);
			else if (strstr(buf, "FRC_049"))					reg4->FRC[49] = atoi(strstr(strstr(buf, "FRC_049"), ",") + 1);
			else if (strstr(buf, "FRC_050"))					reg4->FRC[50] = atoi(strstr(strstr(buf, "FRC_050"), ",") + 1);
			else if (strstr(buf, "FRC_051"))					reg4->FRC[51] = atoi(strstr(strstr(buf, "FRC_051"), ",") + 1);
			else if (strstr(buf, "FRC_052"))					reg4->FRC[52] = atoi(strstr(strstr(buf, "FRC_052"), ",") + 1);
			else if (strstr(buf, "FRC_053"))					reg4->FRC[53] = atoi(strstr(strstr(buf, "FRC_053"), ",") + 1);
			else if (strstr(buf, "FRC_054"))					reg4->FRC[54] = atoi(strstr(strstr(buf, "FRC_054"), ",") + 1);
			else if (strstr(buf, "FRC_055"))					reg4->FRC[55] = atoi(strstr(strstr(buf, "FRC_055"), ",") + 1);
			else if (strstr(buf, "FRC_056"))					reg4->FRC[56] = atoi(strstr(strstr(buf, "FRC_056"), ",") + 1);
			else if (strstr(buf, "FRC_057"))					reg4->FRC[57] = atoi(strstr(strstr(buf, "FRC_057"), ",") + 1);
			else if (strstr(buf, "FRC_058"))					reg4->FRC[58] = atoi(strstr(strstr(buf, "FRC_058"), ",") + 1);
			else if (strstr(buf, "FRC_059"))					reg4->FRC[59] = atoi(strstr(strstr(buf, "FRC_059"), ",") + 1);
			else if (strstr(buf, "FRC_060"))					reg4->FRC[60] = atoi(strstr(strstr(buf, "FRC_060"), ",") + 1);
			else if (strstr(buf, "FRC_061"))					reg4->FRC[61] = atoi(strstr(strstr(buf, "FRC_061"), ",") + 1);
			else if (strstr(buf, "FRC_062"))					reg4->FRC[62] = atoi(strstr(strstr(buf, "FRC_062"), ",") + 1);
			else if (strstr(buf, "FRC_063"))					reg4->FRC[63] = atoi(strstr(strstr(buf, "FRC_063"), ",") + 1);
			else if (strstr(buf, "FRC_064"))					reg4->FRC[64] = atoi(strstr(strstr(buf, "FRC_064"), ",") + 1);
			else if (strstr(buf, "FRC_065"))					reg4->FRC[65] = atoi(strstr(strstr(buf, "FRC_065"), ",") + 1);
			else if (strstr(buf, "FRC_066"))					reg4->FRC[66] = atoi(strstr(strstr(buf, "FRC_066"), ",") + 1);
			else if (strstr(buf, "FRC_067"))					reg4->FRC[67] = atoi(strstr(strstr(buf, "FRC_067"), ",") + 1);
			else if (strstr(buf, "FRC_068"))					reg4->FRC[68] = atoi(strstr(strstr(buf, "FRC_068"), ",") + 1);
			else if (strstr(buf, "FRC_069"))					reg4->FRC[69] = atoi(strstr(strstr(buf, "FRC_069"), ",") + 1);
			else if (strstr(buf, "FRC_070"))					reg4->FRC[70] = atoi(strstr(strstr(buf, "FRC_070"), ",") + 1);
			else if (strstr(buf, "FRC_071"))					reg4->FRC[71] = atoi(strstr(strstr(buf, "FRC_071"), ",") + 1);
			else if (strstr(buf, "FRC_072"))					reg4->FRC[72] = atoi(strstr(strstr(buf, "FRC_072"), ",") + 1);
			else if (strstr(buf, "FRC_073"))					reg4->FRC[73] = atoi(strstr(strstr(buf, "FRC_073"), ",") + 1);
			else if (strstr(buf, "FRC_074"))					reg4->FRC[74] = atoi(strstr(strstr(buf, "FRC_074"), ",") + 1);
			else if (strstr(buf, "FRC_075"))					reg4->FRC[75] = atoi(strstr(strstr(buf, "FRC_075"), ",") + 1);
			else if (strstr(buf, "FRC_076"))					reg4->FRC[76] = atoi(strstr(strstr(buf, "FRC_076"), ",") + 1);
			else if (strstr(buf, "FRC_077"))					reg4->FRC[77] = atoi(strstr(strstr(buf, "FRC_077"), ",") + 1);
			else if (strstr(buf, "FRC_078"))					reg4->FRC[78] = atoi(strstr(strstr(buf, "FRC_078"), ",") + 1);
			else if (strstr(buf, "FRC_079"))					reg4->FRC[79] = atoi(strstr(strstr(buf, "FRC_079"), ",") + 1);
			else if (strstr(buf, "FRC_080"))					reg4->FRC[80] = atoi(strstr(strstr(buf, "FRC_080"), ",") + 1);
			else if (strstr(buf, "FRC_081"))					reg4->FRC[81] = atoi(strstr(strstr(buf, "FRC_081"), ",") + 1);
			else if (strstr(buf, "FRC_082"))					reg4->FRC[82] = atoi(strstr(strstr(buf, "FRC_082"), ",") + 1);
			else if (strstr(buf, "FRC_083"))					reg4->FRC[83] = atoi(strstr(strstr(buf, "FRC_083"), ",") + 1);
			else if (strstr(buf, "FRC_084"))					reg4->FRC[84] = atoi(strstr(strstr(buf, "FRC_084"), ",") + 1);
			else if (strstr(buf, "FRC_085"))					reg4->FRC[85] = atoi(strstr(strstr(buf, "FRC_085"), ",") + 1);
			else if (strstr(buf, "FRC_086"))					reg4->FRC[86] = atoi(strstr(strstr(buf, "FRC_086"), ",") + 1);
			else if (strstr(buf, "FRC_087"))					reg4->FRC[87] = atoi(strstr(strstr(buf, "FRC_087"), ",") + 1);
			else if (strstr(buf, "FRC_088"))					reg4->FRC[88] = atoi(strstr(strstr(buf, "FRC_088"), ",") + 1);
			else if (strstr(buf, "FRC_089"))					reg4->FRC[89] = atoi(strstr(strstr(buf, "FRC_089"), ",") + 1);
			else if (strstr(buf, "FRC_090"))					reg4->FRC[90] = atoi(strstr(strstr(buf, "FRC_090"), ",") + 1);
			else if (strstr(buf, "FRC_091"))					reg4->FRC[91] = atoi(strstr(strstr(buf, "FRC_091"), ",") + 1);
			else if (strstr(buf, "FRC_092"))					reg4->FRC[92] = atoi(strstr(strstr(buf, "FRC_092"), ",") + 1);
			else if (strstr(buf, "FRC_093"))					reg4->FRC[93] = atoi(strstr(strstr(buf, "FRC_093"), ",") + 1);
			else if (strstr(buf, "FRC_094"))					reg4->FRC[94] = atoi(strstr(strstr(buf, "FRC_094"), ",") + 1);
			else if (strstr(buf, "FRC_095"))					reg4->FRC[95] = atoi(strstr(strstr(buf, "FRC_095"), ",") + 1);
			else if (strstr(buf, "FRC_096"))					reg4->FRC[96] = atoi(strstr(strstr(buf, "FRC_096"), ",") + 1);
			else if (strstr(buf, "FRC_097"))					reg4->FRC[97] = atoi(strstr(strstr(buf, "FRC_097"), ",") + 1);
			else if (strstr(buf, "FRC_098"))					reg4->FRC[98] = atoi(strstr(strstr(buf, "FRC_098"), ",") + 1);
			else if (strstr(buf, "FRC_099"))					reg4->FRC[99] = atoi(strstr(strstr(buf, "FRC_099"), ",") + 1);
			else if (strstr(buf, "FRC_100"))					reg4->FRC[100] = atoi(strstr(strstr(buf, "FRC_100"), ",") + 1);
			else if (strstr(buf, "FRC_101"))					reg4->FRC[101] = atoi(strstr(strstr(buf, "FRC_101"), ",") + 1);
			else if (strstr(buf, "FRC_102"))					reg4->FRC[102] = atoi(strstr(strstr(buf, "FRC_102"), ",") + 1);
			else if (strstr(buf, "FRC_103"))					reg4->FRC[103] = atoi(strstr(strstr(buf, "FRC_103"), ",") + 1);
			else if (strstr(buf, "FRC_104"))					reg4->FRC[104] = atoi(strstr(strstr(buf, "FRC_104"), ",") + 1);
			else if (strstr(buf, "FRC_105"))					reg4->FRC[105] = atoi(strstr(strstr(buf, "FRC_105"), ",") + 1);
			else if (strstr(buf, "FRC_106"))					reg4->FRC[106] = atoi(strstr(strstr(buf, "FRC_106"), ",") + 1);
			else if (strstr(buf, "FRC_107"))					reg4->FRC[107] = atoi(strstr(strstr(buf, "FRC_107"), ",") + 1);
			else if (strstr(buf, "FRC_108"))					reg4->FRC[108] = atoi(strstr(strstr(buf, "FRC_108"), ",") + 1);
			else if (strstr(buf, "FRC_109"))					reg4->FRC[109] = atoi(strstr(strstr(buf, "FRC_109"), ",") + 1);
			else if (strstr(buf, "FRC_110"))					reg4->FRC[110] = atoi(strstr(strstr(buf, "FRC_110"), ",") + 1);
			else if (strstr(buf, "FRC_111"))					reg4->FRC[111] = atoi(strstr(strstr(buf, "FRC_111"), ",") + 1);
			else;
		}

	}


	if ((pFile = fopen(filename, "rt")) == NULL)
	{
		printf("Open REG File Error\n");
		system("pause");
	}
	else
	{
		while (fgets(buf, 256, pFile))
		{
			if (strstr(buf, "DITHER_00"))					    reg4->DITHER[0]	 = atoi(strstr(strstr(buf, "DITHER_00"), ",") + 1);
			else if (strstr(buf, "DITHER_01"))					reg4->DITHER[1]	 = atoi(strstr(strstr(buf, "DITHER_01"), ",") + 1);
			else if (strstr(buf, "DITHER_02"))					reg4->DITHER[2]	 = atoi(strstr(strstr(buf, "DITHER_02"), ",") + 1);
			else if (strstr(buf, "DITHER_03"))					reg4->DITHER[3]	 = atoi(strstr(strstr(buf, "DITHER_03"), ",") + 1);
			else if (strstr(buf, "DITHER_04"))					reg4->DITHER[4]	 = atoi(strstr(strstr(buf, "DITHER_04"), ",") + 1);
			else if (strstr(buf, "DITHER_05"))					reg4->DITHER[5]	 = atoi(strstr(strstr(buf, "DITHER_05"), ",") + 1);
			else if (strstr(buf, "DITHER_06"))					reg4->DITHER[6]	 = atoi(strstr(strstr(buf, "DITHER_06"), ",") + 1);
			else if (strstr(buf, "DITHER_07"))					reg4->DITHER[7]	 = atoi(strstr(strstr(buf, "DITHER_07"), ",") + 1);
			else if (strstr(buf, "DITHER_08"))					reg4->DITHER[8]	 = atoi(strstr(strstr(buf, "DITHER_08"), ",") + 1);
			else if (strstr(buf, "DITHER_09"))					reg4->DITHER[9]	 = atoi(strstr(strstr(buf, "DITHER_09"), ",") + 1);
			else if (strstr(buf, "DITHER_10"))					reg4->DITHER[10] = atoi(strstr(strstr(buf, "DITHER_10"), ",") + 1);
			else if (strstr(buf, "DITHER_11"))					reg4->DITHER[11] = atoi(strstr(strstr(buf, "DITHER_11"), ",") + 1);
			else if (strstr(buf, "DITHER_12"))					reg4->DITHER[12] = atoi(strstr(strstr(buf, "DITHER_12"), ",") + 1);
			else if (strstr(buf, "DITHER_13"))					reg4->DITHER[13] = atoi(strstr(strstr(buf, "DITHER_13"), ",") + 1);
			else;
		}
	}
	fclose(pFile);

	return reg4;
}

int SearchGain(int Lenh_in, REG* reg)
{
	int gain = 0;        // 12bit
	int idx = 0;         // 7bit(1~64) 
	int temp_lenh = 0;   // 12bit 
	// 
	temp_lenh = Lenh_in;

	// select zone area (1~64)
	idx = (temp_lenh / 64) + 1;


	if (idx == 64)  // zone 64 special process
		gain = interpolation_fix_point_6bit(reg->GAIN[idx - 1], reg->GAIN[idx - 1], (temp_lenh - ((idx - 1) << 6)) & 0x3f);
	else									//   12BIT                  12BIT                6BIT
		gain = interpolation_fix_point_6bit(reg->GAIN[idx - 1], reg->GAIN[idx], (temp_lenh - ((idx - 1) << 6)) & 0x3f);

	return gain;
}


void EdgeEnhancement(REG* reg, REG3* reg3, IMG* img, LENH_PARAM* lenh_param)
{
	int Y_center = 0;
	int Y_temp = 0;
	int Y_blur = 0;
	int Y_boundary = 0;
	int Y_enhance = 0;

	int idx_x, idx_y;
	int Y_max, Y_min, delta_blur;
	int threshold_smooth;
	int threshold_lum;

	int data_r, data_g, data_b;
	int enhance_ratio = 0;

	int max_value = 1023;
	int gain;

	threshold_smooth = reg->THRESHOLD_SMOOTH;	// u10.0
	threshold_lum = reg->THRESHOLD_LUM;			// u10.0

	int rgb_max, rgb_min, rgb_sat;


	gain = SearchGain(lenh_param->LENH_GLOBAL, reg);

	for (int i = 0; i < reg->VACTIVE; ++i)
	{
		for (int j = 0; j < reg->HACTIVE; ++j)
		{
			if (reg->EN_EDGE_ENHANCE_EXTERNAL && i >= 0 + MASK_SIZE / 2 && i < reg->VACTIVE - MASK_SIZE / 2 && j >= 0 + MASK_SIZE / 2 && j < reg->HACTIVE - MASK_SIZE / 2)
			{
				Y_temp = 0;
				Y_blur = 0;
				Y_max = -1 * max_value;
				Y_min = max_value;
				delta_blur = 0;

				for (int m = 0; m < MASK_SIZE; ++m)
				{
					for (int n = 0; n < MASK_SIZE; ++n)
					{
						idx_x = j - MASK_SIZE / 2 + n, idx_y = i - MASK_SIZE / 2 + m;

						data_r = img->data_contrast[idx_y * reg->HACTIVE * 3 + 3 * idx_x + 0];	// u10.0
						data_g = img->data_contrast[idx_y * reg->HACTIVE * 3 + 3 * idx_x + 1];	// u10.0
						data_b = img->data_contrast[idx_y * reg->HACTIVE * 3 + 3 * idx_x + 2];	// u10.0

						rgb_max = I_MAX(data_r, I_MAX(data_g, data_b));						    // u10.0
						rgb_min = I_MIN(data_r, I_MIN(data_g, data_b));						    // u10.0

						if (reg->EN_MIX_RGB)
							Y_temp = (((reg->RATIO[0] * data_r + reg->RATIO[1] * data_g + reg->RATIO[2] * data_b) >> 6) + 1) >> 1; 	// u1.7 * u10.0 = u10.7,  u10.7 >> 7 = u10.0
						else
							Y_temp = rgb_max; 											        // u10.0

						Y_max = (Y_temp > Y_max) ? Y_temp : Y_max;
						Y_min = (Y_temp < Y_min) ? Y_temp : Y_min;


						if (m == MASK_SIZE / 2 && n == MASK_SIZE / 2)
						{
							Y_center = Y_temp;

							if (rgb_max != 0)
								rgb_sat = 256 * (rgb_max - rgb_min) / rgb_max; 				   // u8.0 * u10.0 / u10.0 = u8.0
							else
								rgb_sat = 0;
						}


						// Y_blur = Y_blur + ((((Y_temp * reg->UNSHARP_MASK[m * MASK_SIZE + n]) >> 8) + 1) >> 1);	// u10.0 * u1.9 = u10.9,  u10.9 >> 9 = u10.0
						Y_blur = Y_blur + ((((Y_temp * reg->UNSHARP_MASK[m * MASK_SIZE + n]) >> 10) + 1) >> 1);	// u10.0 * u1.11 = u11.11,  u11.11 >> 11 = u11.0

					}
				}

				Y_blur = (Y_blur < Y_min) ? Y_min : (Y_blur > Y_max) ? Y_max : Y_blur; // u11.0 & 0x3f
				Y_boundary = Y_center - Y_blur;						// it might be a positive or negative 10bit value.

				if (reg->EN_PROTECTION_HIGH)
					Y_boundary = (Y_boundary > 0) ? 0 : Y_boundary;	// it is a negative 10bit value.

				if (reg->EN_PROTECTION_SATURATION)
				{
					if (Y_boundary > 0)
						Y_boundary = (Y_boundary * (256 - rgb_sat) + 128) / 256;	// positive case.
					else
						Y_boundary = (Y_boundary * (256 - rgb_sat) - 128) / 256;	// negative case.
				}

				if (reg->EN_PROTECTION_SMOOTH)
				{
					delta_blur = I_MAX((Y_max - Y_blur), (Y_blur - Y_min));			// u10.0

					if (delta_blur < threshold_smooth)
						Y_boundary = 0;
					else
						Y_boundary = Y_boundary;									// u10.0
				}

				if (reg->EN_PROTECTION_LUM)
				{
					if (Y_center > threshold_lum)
						Y_boundary = 0;
					else
						Y_boundary = Y_boundary;									// u10.0
				}

				if (Y_boundary == 0)
				{
					img->data_edge[i * reg->HACTIVE * 3 + 3 * j + 0] = img->data_contrast[i * reg->HACTIVE * 3 + 3 * j + 0];		// u10.0
					img->data_edge[i * reg->HACTIVE * 3 + 3 * j + 1] = img->data_contrast[i * reg->HACTIVE * 3 + 3 * j + 1];		// u10.0
					img->data_edge[i * reg->HACTIVE * 3 + 3 * j + 2] = img->data_contrast[i * reg->HACTIVE * 3 + 3 * j + 2];		// u10.0
				}
				else
				{
					if (reg->EN_GAIN)
					{
						if (Y_boundary > 0)
							Y_boundary = (Y_boundary * gain + 128) / 256;	// positive case.
						else
							Y_boundary = (Y_boundary * gain - 128) / 256;	// negative case.
					}

					Y_enhance = Y_center + Y_boundary;
					Y_enhance = (Y_enhance < 0) ? 0 : (Y_enhance > 1023) ? 1023 : Y_enhance;		// u10.0

					if (Y_center > 0)
						enhance_ratio = Y_enhance * 256 / Y_center; 								// u10.0 * 256 / u10.0 = u2.8
					else
						enhance_ratio = 0;

					// add 20240705
					enhance_ratio = (enhance_ratio < 0) ? 0 : (enhance_ratio > 1023) ? 1023 : enhance_ratio; // u2.8

					data_r = (img->data_contrast[i * reg->HACTIVE * 3 + 3 * j + 0] * enhance_ratio + 128) / 256;	// u10.0 * u2.8 / 256 = u10.0
					data_g = (img->data_contrast[i * reg->HACTIVE * 3 + 3 * j + 1] * enhance_ratio + 128) / 256;	// u10.0 * u2.8 / 256 = u10.0
					data_b = (img->data_contrast[i * reg->HACTIVE * 3 + 3 * j + 2] * enhance_ratio + 128) / 256;	// u10.0 * u2.8 / 256 = u10.0

					img->data_edge[i * reg->HACTIVE * 3 + 3 * j + 0] = I_PIXEL10B(data_r);
					img->data_edge[i * reg->HACTIVE * 3 + 3 * j + 1] = I_PIXEL10B(data_g);
					img->data_edge[i * reg->HACTIVE * 3 + 3 * j + 2] = I_PIXEL10B(data_b);
				}
			}
			else
			{
				img->data_edge[i * reg->HACTIVE * 3 + 3 * j + 0] = img->data_contrast[i * reg->HACTIVE * 3 + 3 * j + 0];
				img->data_edge[i * reg->HACTIVE * 3 + 3 * j + 1] = img->data_contrast[i * reg->HACTIVE * 3 + 3 * j + 1];
				img->data_edge[i * reg->HACTIVE * 3 + 3 * j + 2] = img->data_contrast[i * reg->HACTIVE * 3 + 3 * j + 2];
			}
		}
	}
}

// left   ,  right
// small  ,  big
int interpolation_fix_point(int left_value, int right_value, int gain) {
	// Input data list

	// left_value : 12bit
	// right_value : 12bit
	// gain : 9bit

	// Output data 
	// final_result : 12bit

	int output = 0;
	struct fixbit {

		unsigned int  value_diff : 12;
		unsigned int  temp_result : 21;
		unsigned int  temp_result2 : 13;
		unsigned int  final_result : 12;
		unsigned int  sign : 1;
	}fixbit;

	if (right_value < left_value)
		fixbit.sign = 1;
	else
		fixbit.sign = 0;


	fixbit.value_diff = I_ABS((right_value - left_value));
	fixbit.temp_result = fixbit.value_diff * gain;
	fixbit.temp_result2 = fixbit.temp_result >> 8;


	if (fixbit.sign == 0)
		fixbit.final_result = (left_value + fixbit.temp_result2) & 0xfff;
	else
		fixbit.final_result = (left_value - fixbit.temp_result2) & 0xfff;


	output = (int)fixbit.final_result;
	return output;
}




int interpolation_fix_point_6bit(int left_value, int right_value, int gain) {
	// Input data list

	// left_value : 12bit
	// right_value : 12bit
	// gain : 6bit

	// Output data 
	// final_result : 12bit

	int output = 0;
	struct fixbit {

		unsigned int  value_diff : 12;
		unsigned int  temp_result : 18;
		unsigned int  temp_result2 : 12;
		unsigned int  final_result : 12;
		unsigned int  sign : 1;
	}fixbit;

	if (right_value < left_value)
		fixbit.sign = 1;
	else
		fixbit.sign = 0;

	fixbit.value_diff = I_ABS((right_value - left_value));
	fixbit.temp_result = fixbit.value_diff * gain;
	fixbit.temp_result2 = fixbit.temp_result >> 6;

	if (fixbit.sign == 0)
		fixbit.final_result = (left_value + fixbit.temp_result2) & 0xfff;
	else
		fixbit.final_result = (left_value - fixbit.temp_result2) & 0xfff;

	output = (int)fixbit.final_result;
	return output;
}


void Temporal_Filter(REG2* reg2, TEMPORAL* temporal, int* current_content_target_curve, int* temporal_output_curve) {
	// local parameter initial 
	int target_gap = 0;											// 9bit
	int filter_ratio = 0;										// 9bit
	int filter_table[16] = { 0 };								// 9bit*16
	int rising_state = 0;                                       // 1bit
	int temporal_counter_local = temporal->TEMPORAL_COUNTER;    // 4bit

	if (current_content_target_curve[0] >= temporal->PREVIOUS_FINAL_CURVE[0])
		rising_state = 1;
	else
		rising_state = 0;

	if (rising_state == 1)	   // rising table 
	{
		for (int i = 0; i < 16; i++)
			filter_table[i] = reg2->TEMPORAL_FILTER[i];
	}
	else					   // falling table
	{
		for (int i = 0; i < 16; i++)
			filter_table[i] = reg2->TEMPORAL_FILTER[i + 16];
	}

	// temporal filter active 
	if (reg2->TMP_FILTER_ENABLE == 1)
	{
		filter_ratio = filter_table[temporal_counter_local];
		for (int i = 0; i < 128; i++)
		{
			//   12BIT                          12BIT                           9BIT
			temporal_output_curve[i] = interpolation_fix_point(temporal->PREVIOUS_FINAL_CURVE[i], current_content_target_curve[i], filter_ratio);
		}
	}
	else {
		for (int i = 0; i < 128; i++)
			temporal_output_curve[i] = current_content_target_curve[i];
	}

	temporal_counter_local++;
	temporal_counter_local = (temporal_counter_local > reg2->TMP_CYCLE_NUMBER) ? 0 : temporal_counter_local;
	temporal->TEMPORAL_COUNTER = temporal_counter_local;
}

void Curve_Initial(REG2* reg2, REG3* reg3, TEMPORAL* temporal) {

	// PREVIOUS_FINAL_CURVE[129];                // 12 bit LUT
	// FIRST_TEMPORAL_TARGET                     // 10 bit
	// TEMPORAL_COUNTER                          // 4 bit
	// PREVIOUS_TEMPORAL_TARGET                  // 10 bit

	// Temporal Initial At First 
	temporal->TEMPORAL_COUNTER = 0;
	temporal->FIRST_TEMPORAL_TARGET = reg2->LOWER_SETTING;
	//  TEMPORAL FILTER INITIAL PART
	for (int i = 0; i < 128; i++)
		temporal->PREVIOUS_FINAL_CURVE[i] = reg2->HIGH_HISTOGRAM_CURVE[i] << 2;  //u2.8 >> u2.10

	temporal->PREVIOUS_FINAL_CURVE[128] = temporal->PREVIOUS_FINAL_CURVE[127];

}

void Curve_Calculate(REG2* reg2, REG3* reg3, IMG* img, TEMPORAL* temporal, LENH_PARAM* lenh_param) {

	/*

		1. content curve mix
			output : 128 * 12bit array

		2. lenh curve mix
			output : 128 * 12bit array

		3. temporal filter
			output : 128 * 12bit array

		4. final output
			output : 129 * 12bit array
	*/


	// Initial Local Parameter
	int content_target_curve[128];                                           // 12bit LUT
	int lenh_curve[128];                                                     // 12bit LUT
	int temporal_output_curve[128];                                          // 12bit LUT

	int content_setting_range = 0;                                           // 10bit
	unsigned int content_setting_range_temp1 = 0;                            // 22bit
	unsigned int content_setting_range_temp2 = 0;                            // 11bit
	unsigned int content_setting_range_temp3 = 0;                            // 10bit
	int temp_content_ratio = 0;                                              // 6 bit
	int temp_lenh_ratio = 0;                                                 // 6 bit
	int content_ratio = 0;                                                   // 9 bit

	// lenh relationship
	int lenh_ratio = 0;                                                      // 9 bit
	int lenh = 0;                                                            // 12bit 

	for (int i = 0; i < 128; i++)
	{
		lenh_curve[i] = 0;
		temporal_output_curve[i] = 0;
	}

	lenh = lenh_param->LENH_GLOBAL;


	// Blanking Area Active
	// Content Ratio 
	if (temporal->CURRENT_TEMPORAL_TARGET <= reg2->LOWER_SETTING)
	{
		for (int i = 0; i < 128; i++)
			content_target_curve[i] = reg2->LOW_HISTOGRAM_CURVE[i] << 2;                     // 2.8 to 2.10
	}
	else if (temporal->CURRENT_TEMPORAL_TARGET >= reg2->UPPER_SETTING)
	{
		for (int i = 0; i < 128; i++)
			content_target_curve[i] = reg2->HIGH_HISTOGRAM_CURVE[i] << 2;                    // 2.8 to 2.10
	}
	else
	{
		content_setting_range = temporal->CURRENT_TEMPORAL_TARGET - reg2->LOWER_SETTING;     // u8.0 - u8.0 = u8.0 bit
		content_setting_range_temp1 = (content_setting_range * reg2->CONTENT_GAIN_RATIO);    // u8.2 * u0.12 = u8.14 
		content_setting_range_temp2 = (content_setting_range_temp1 >> 11);                   // 8.14 --> 8.3
		content_setting_range_temp3 = (content_setting_range_temp2 & 0b1) ? ((content_setting_range_temp2 >> 1) + 1) : (content_setting_range_temp2 >> 1); //8.3 round to 8.2
		temp_content_ratio = (content_setting_range_temp3 & 0x3f);                           // get valid 6bit
		temp_content_ratio = temp_content_ratio > 32 ? 32 : temp_content_ratio;              // clamp to 32 (LUT idx max)
		content_ratio = reg2->CONTENT_RATIO[temp_content_ratio];

		//     12BIT
		for (int i = 0; i < 128; i++)                                     //   12BIT                          12BIT                      9BIT
			content_target_curve[i] = interpolation_fix_point(reg2->HIGH_HISTOGRAM_CURVE[i] << 2, reg2->LOW_HISTOGRAM_CURVE[i] << 2, content_ratio);
	}

	// Lenh target curve search
	temp_lenh_ratio = ((lenh * reg2->LENH_GAIN) >> 14);            //   u12.0 * u8.0 = u20.0 ; u20.0 --> u6.0
	lenh_ratio = reg2->LENH_RATIO[temp_lenh_ratio];                //   9bit
	for (int i = 0; i < 128; i++)                                  //   12BIT                   12BIT                 9BIT
		lenh_curve[i] = interpolation_fix_point(reg2->LENH_TARGET, content_target_curve[i], lenh_ratio);

	//  Temporal Filter
	//  temporal : intput data (last frame final curve)
	//  content_target_curve : current frame (after content & lenh) output curve
	//  content_temporal_curve : 
	//                      in           in                out
	Temporal_Filter(reg2, temporal, lenh_curve, temporal_output_curve);

	// final output curve set
	for (int i = 0; i < 128; i++)
		temporal->PREVIOUS_FINAL_CURVE[i] = temporal_output_curve[i];

	temporal->PREVIOUS_FINAL_CURVE[128] = temporal->PREVIOUS_FINAL_CURVE[127];


}

void ContrastEnhancement(REG* reg, REG2* reg2, REG3* reg3, TEMPORAL* temporal, IMG* img, int frame_n, LENH_PARAM* lenh_param) {

	//                  //    cycle 1  //     // cycle 2   //     
	// Initial          F0 F1 F2 F3 F4 F5 ... F0 F1 F2 F3 F4 ...
	// Initial State
	// Cycle State
	// After Cycle State

	printf("Frame Number = %d\n", frame_n);
	/*
		Image Data & Gain
		ex 8.2 means 8bit integer  2bit decimal
	*/
	int idx_r = 0;                                                                          // 10 bit ,8.2 bit
	int idx_g = 0;                                                                          // 10 bit ,8.2 bit
	int idx_b = 0;                                                                          // 10 bit ,8.2 bit
	int r_gain = 0;                                                                         // 12 bit ,2.10 bit  
	int g_gain = 0;                                                                         // 12 bit ,2.10 bit 
	int b_gain = 0;                                                                         // 12 bit ,2.10 bit 


	int final_overall_gain = 0;                                                             // 12 bit ,2.10 bit 
	unsigned int count_y = 0;																// 10 bit ,8.2 bit

	// Counter Modify
	unsigned int Quotient = 0;                                                              // 10 bit 
	unsigned int Dividend = 0;                                                              // 24 bit(5K)
	unsigned int Divisor = reg2->INTENSITY_SELECT;                                          // 24 bit(5K)

	// Fitting Idx              
	int fitting_idx_r_1 = 0;                                                                // 7 bit
	int fitting_idx_g_1 = 0;                                                                // 7 bit
	int fitting_idx_b_1 = 0;                                                                // 7 bit

	int fitting_idx_r_2 = 0;                                                                // 3 bit
	int fitting_idx_g_2 = 0;                                                                // 3 bit
	int fitting_idx_b_2 = 0;                                                                // 3 bit

	int TEMP_FITTING_CURVE_R[8] = { 0 };                                                    // 12 bit
	int TEMP_FITTING_CURVE_G[8] = { 0 };                                                    // 12 bit
	int TEMP_FITTING_CURVE_B[8] = { 0 };                                                    // 12 bit

	// Round Temp 
	unsigned int result_temp_r1 = 0;                                                               // 22 bit
	unsigned int result_temp_g1 = 0;                                                               // 22 bit
	unsigned int result_temp_b1 = 0;                                                               // 22 bit

	unsigned int result_temp_r2 = 0;                                                               // 13 bit
	unsigned int result_temp_g2 = 0;                                                               // 13 bit
	unsigned int result_temp_b2 = 0;                                                               // 13 bit

	unsigned int result_temp_r3 = 0;                                                               // 12 bit
	unsigned int result_temp_g3 = 0;                                                               // 12 bit
	unsigned int result_temp_b3 = 0;                                                               // 12 bit

	unsigned int result_temp_r4 = 0;                                                               // 10 bit
	unsigned int result_temp_g4 = 0;                                                               // 10 bit
	unsigned int result_temp_b4 = 0;                                                               // 10 bit

	unsigned int max_rgb = 0;                                                                      // 10 bit

	// Saturation_flag 
	int saturation_flag = 0;                                                                       // 1bit

	// enable pin change will initial
	// if (temporal->PREVIOUS_ENABLE != reg2->EN_CONTRAST_ENHANCEMENT_EXTERNAL)
	// Curve_Initial(reg2, reg3, temporal);    





	if (reg2->EN_CONTRAST_ENHANCEMENT_EXTERNAL == 0)
	{
		for (int i = 0; i < reg->VACTIVE; ++i)
		{
			for (int j = 0; j < reg->HACTIVE; ++j)
			{
				img->data_contrast[i * reg->HACTIVE * 3 + 3 * j + 0] = img->data_in[i * reg->HACTIVE * 3 + 3 * j + 0];
				img->data_contrast[i * reg->HACTIVE * 3 + 3 * j + 1] = img->data_in[i * reg->HACTIVE * 3 + 3 * j + 1];
				img->data_contrast[i * reg->HACTIVE * 3 + 3 * j + 2] = img->data_in[i * reg->HACTIVE * 3 + 3 * j + 2];
			}
		}
	}
	else
	{
		for (int i = 0; i < reg->VACTIVE; ++i) {
			for (int j = 0; j < reg->HACTIVE; ++j) {
			
				saturation_flag = 0;
				idx_r = img->data_in[i * reg->HACTIVE * 3 + 3 * j + 0];
				idx_g = img->data_in[i * reg->HACTIVE * 3 + 3 * j + 1];
				idx_b = img->data_in[i * reg->HACTIVE * 3 + 3 * j + 2];

				///////////////
				count_y = ((1228 * idx_r + 2402 * idx_g + 466 * idx_b) >> 12);  // 8.2 = 8.2 * 0.12  ; 8.14 >> 12 = 8.2

				Dividend = Dividend + count_y;

				if (Dividend >= Divisor)
				{
					Quotient++;
					Dividend = Dividend - Divisor;
				}


				// 20240910 new update for special case , create new control mode
				max_rgb = I_MAX(idx_r, I_MAX(idx_g, idx_b));

				if (reg2->MAX_GAIN_MODE == 1)
				{
					idx_r = max_rgb;
					idx_g = max_rgb;
					idx_b = max_rgb;
				}

				fitting_idx_r_1 = (idx_r & 0x3f8) >> 3;                         // valid 7bit
				fitting_idx_g_1 = (idx_g & 0x3f8) >> 3;                         // valid 7bit
				fitting_idx_b_1 = (idx_b & 0x3f8) >> 3;                         // valid 7bit

				fitting_idx_r_2 = idx_r & 0x007;                                // valid 3bit
				fitting_idx_g_2 = idx_g & 0x007;                                // valid 3bit
				fitting_idx_b_2 = idx_b & 0x007;                                // valid 3bit


				TEMP_FITTING_CURVE_R[0] = temporal->PREVIOUS_FINAL_CURVE[fitting_idx_r_1];
				TEMP_FITTING_CURVE_R[1] = (7 * temporal->PREVIOUS_FINAL_CURVE[fitting_idx_r_1] + 1 * temporal->PREVIOUS_FINAL_CURVE[fitting_idx_r_1 + 1]) >> 3; // u0.3 * u2.10 + u0.3 * u2.10 = u3.13 ; u3.13 >> 3 = u3.10 ; valid bit = u2.10
				TEMP_FITTING_CURVE_R[2] = (6 * temporal->PREVIOUS_FINAL_CURVE[fitting_idx_r_1] + 2 * temporal->PREVIOUS_FINAL_CURVE[fitting_idx_r_1 + 1]) >> 3;
				TEMP_FITTING_CURVE_R[3] = (5 * temporal->PREVIOUS_FINAL_CURVE[fitting_idx_r_1] + 3 * temporal->PREVIOUS_FINAL_CURVE[fitting_idx_r_1 + 1]) >> 3;
				TEMP_FITTING_CURVE_R[4] = (4 * temporal->PREVIOUS_FINAL_CURVE[fitting_idx_r_1] + 4 * temporal->PREVIOUS_FINAL_CURVE[fitting_idx_r_1 + 1]) >> 3;
				TEMP_FITTING_CURVE_R[5] = (3 * temporal->PREVIOUS_FINAL_CURVE[fitting_idx_r_1] + 5 * temporal->PREVIOUS_FINAL_CURVE[fitting_idx_r_1 + 1]) >> 3;
				TEMP_FITTING_CURVE_R[6] = (2 * temporal->PREVIOUS_FINAL_CURVE[fitting_idx_r_1] + 6 * temporal->PREVIOUS_FINAL_CURVE[fitting_idx_r_1 + 1]) >> 3;
				TEMP_FITTING_CURVE_R[7] = (1 * temporal->PREVIOUS_FINAL_CURVE[fitting_idx_r_1] + 7 * temporal->PREVIOUS_FINAL_CURVE[fitting_idx_r_1 + 1]) >> 3;

				TEMP_FITTING_CURVE_G[0] = temporal->PREVIOUS_FINAL_CURVE[fitting_idx_g_1];
				TEMP_FITTING_CURVE_G[1] = (7 * temporal->PREVIOUS_FINAL_CURVE[fitting_idx_g_1] + 1 * temporal->PREVIOUS_FINAL_CURVE[fitting_idx_g_1 + 1]) >> 3;
				TEMP_FITTING_CURVE_G[2] = (6 * temporal->PREVIOUS_FINAL_CURVE[fitting_idx_g_1] + 2 * temporal->PREVIOUS_FINAL_CURVE[fitting_idx_g_1 + 1]) >> 3;
				TEMP_FITTING_CURVE_G[3] = (5 * temporal->PREVIOUS_FINAL_CURVE[fitting_idx_g_1] + 3 * temporal->PREVIOUS_FINAL_CURVE[fitting_idx_g_1 + 1]) >> 3;
				TEMP_FITTING_CURVE_G[4] = (4 * temporal->PREVIOUS_FINAL_CURVE[fitting_idx_g_1] + 4 * temporal->PREVIOUS_FINAL_CURVE[fitting_idx_g_1 + 1]) >> 3;
				TEMP_FITTING_CURVE_G[5] = (3 * temporal->PREVIOUS_FINAL_CURVE[fitting_idx_g_1] + 5 * temporal->PREVIOUS_FINAL_CURVE[fitting_idx_g_1 + 1]) >> 3;
				TEMP_FITTING_CURVE_G[6] = (2 * temporal->PREVIOUS_FINAL_CURVE[fitting_idx_g_1] + 6 * temporal->PREVIOUS_FINAL_CURVE[fitting_idx_g_1 + 1]) >> 3;
				TEMP_FITTING_CURVE_G[7] = (1 * temporal->PREVIOUS_FINAL_CURVE[fitting_idx_g_1] + 7 * temporal->PREVIOUS_FINAL_CURVE[fitting_idx_g_1 + 1]) >> 3;

				TEMP_FITTING_CURVE_B[0] = temporal->PREVIOUS_FINAL_CURVE[fitting_idx_b_1];
				TEMP_FITTING_CURVE_B[1] = (7 * temporal->PREVIOUS_FINAL_CURVE[fitting_idx_b_1] + 1 * temporal->PREVIOUS_FINAL_CURVE[fitting_idx_b_1 + 1]) >> 3;
				TEMP_FITTING_CURVE_B[2] = (6 * temporal->PREVIOUS_FINAL_CURVE[fitting_idx_b_1] + 2 * temporal->PREVIOUS_FINAL_CURVE[fitting_idx_b_1 + 1]) >> 3;
				TEMP_FITTING_CURVE_B[3] = (5 * temporal->PREVIOUS_FINAL_CURVE[fitting_idx_b_1] + 3 * temporal->PREVIOUS_FINAL_CURVE[fitting_idx_b_1 + 1]) >> 3;
				TEMP_FITTING_CURVE_B[4] = (4 * temporal->PREVIOUS_FINAL_CURVE[fitting_idx_b_1] + 4 * temporal->PREVIOUS_FINAL_CURVE[fitting_idx_b_1 + 1]) >> 3;
				TEMP_FITTING_CURVE_B[5] = (3 * temporal->PREVIOUS_FINAL_CURVE[fitting_idx_b_1] + 5 * temporal->PREVIOUS_FINAL_CURVE[fitting_idx_b_1 + 1]) >> 3;
				TEMP_FITTING_CURVE_B[6] = (2 * temporal->PREVIOUS_FINAL_CURVE[fitting_idx_b_1] + 6 * temporal->PREVIOUS_FINAL_CURVE[fitting_idx_b_1 + 1]) >> 3;
				TEMP_FITTING_CURVE_B[7] = (1 * temporal->PREVIOUS_FINAL_CURVE[fitting_idx_b_1] + 7 * temporal->PREVIOUS_FINAL_CURVE[fitting_idx_b_1 + 1]) >> 3;


				r_gain = TEMP_FITTING_CURVE_R[fitting_idx_r_2];
				g_gain = TEMP_FITTING_CURVE_G[fitting_idx_g_2];
				b_gain = TEMP_FITTING_CURVE_B[fitting_idx_b_2];

				if (idx_r == 0)
					r_gain = 0;

				if (idx_g == 0)
					g_gain = 0;

				if (idx_b == 0)
					b_gain = 0;

				if (r_gain == 0)
					if (g_gain == 0)
						final_overall_gain = b_gain;
					else if (b_gain == 0)
						final_overall_gain = g_gain;
					else
						final_overall_gain = I_MIN(g_gain, b_gain);
				else if (g_gain == 0)
					if (r_gain == 0)
						final_overall_gain = b_gain;
					else if (b_gain == 0)
						final_overall_gain = r_gain;
					else
						final_overall_gain = I_MIN(r_gain, b_gain);
				else if (b_gain == 0)
					if (r_gain == 0)
						final_overall_gain = g_gain;
					else if (g_gain == 0)
						final_overall_gain = r_gain;
					else
						final_overall_gain = I_MIN(r_gain, g_gain);
				else
					final_overall_gain = I_MIN(r_gain, I_MIN(g_gain, b_gain));

				// 8.2 * 2.10 = 10.12
				result_temp_r1 = img->data_in[i * reg->HACTIVE * 3 + 3 * j + 0] * final_overall_gain;
				result_temp_g1 = img->data_in[i * reg->HACTIVE * 3 + 3 * j + 1] * final_overall_gain;
				result_temp_b1 = img->data_in[i * reg->HACTIVE * 3 + 3 * j + 2] * final_overall_gain;

				// 10.12 --> 10.3
				result_temp_r2 = result_temp_r1 >> 9;
				result_temp_g2 = result_temp_g1 >> 9;
				result_temp_b2 = result_temp_b1 >> 9;

				// 10.3 round to  10.2
				result_temp_r3 = ((result_temp_r2 & 0b1) ? ((result_temp_r2 >> 1) + 1) : (result_temp_r2 >> 1));
				result_temp_g3 = ((result_temp_g2 & 0b1) ? ((result_temp_g2 >> 1) + 1) : (result_temp_g2 >> 1));
				result_temp_b3 = ((result_temp_b2 & 0b1) ? ((result_temp_b2 >> 1) + 1) : (result_temp_b2 >> 1));

				// 10.2 to 8.2
				result_temp_r4 = I_MIN(result_temp_r3, 1023) & 0x3ff;
				result_temp_g4 = I_MIN(result_temp_g3, 1023) & 0x3ff;
				result_temp_b4 = I_MIN(result_temp_b3, 1023) & 0x3ff;

				if (result_temp_r4 > reg2->SATURATION_THRESHOLD || result_temp_g4 > reg2->SATURATION_THRESHOLD || result_temp_b4 > reg2->SATURATION_THRESHOLD)
				{
					saturation_flag = 1;
				}
				else
				{
					saturation_flag = 0;
				}

				if (idx_r >= reg2->GREY_THRESHOLD || idx_g >= reg2->GREY_THRESHOLD || idx_b >= reg2->GREY_THRESHOLD || reg2->EN_CONTRAST_ENHANCEMENT_EXTERNAL == 0 || saturation_flag == 1)
				{
					img->data_contrast[i * reg->HACTIVE * 3 + 3 * j + 0] = img->data_in[i * reg->HACTIVE * 3 + 3 * j + 0];
					img->data_contrast[i * reg->HACTIVE * 3 + 3 * j + 1] = img->data_in[i * reg->HACTIVE * 3 + 3 * j + 1];
					img->data_contrast[i * reg->HACTIVE * 3 + 3 * j + 2] = img->data_in[i * reg->HACTIVE * 3 + 3 * j + 2];
				}
				else
				{
					//   8.2
					img->data_contrast[i * reg->HACTIVE * 3 + 3 * j + 0] = result_temp_r4;
					img->data_contrast[i * reg->HACTIVE * 3 + 3 * j + 1] = result_temp_g4;
					img->data_contrast[i * reg->HACTIVE * 3 + 3 * j + 2] = result_temp_b4;
				}
			}
		}
		temporal->CURRENT_TEMPORAL_TARGET = Quotient >> 2; //u8.2 to u8.0

		if (I_ABS((temporal->FIRST_TEMPORAL_TARGET - temporal->CURRENT_TEMPORAL_TARGET)) <= reg2->TMP_CYCLE_THRESHOLD)
			temporal->CURRENT_TEMPORAL_TARGET = temporal->FIRST_TEMPORAL_TARGET;
		else
			temporal->TEMPORAL_COUNTER = 0;

		if (temporal->TEMPORAL_COUNTER == 0)
			temporal->FIRST_TEMPORAL_TARGET = temporal->CURRENT_TEMPORAL_TARGET;

#ifdef CONTRAST_ENHANCEMENT_TMP_DEBUG
		printf("current_target = %d\n", temporal->CURRENT_TEMPORAL_TARGET);
#endif 

	}

	// Blanking Area.
	Curve_Calculate(reg2, reg3, img, temporal, lenh_param);

#ifdef CONTRAST_ENHANCEMENT_TMP_DEBUG
	printf("TEMPORAL_COUNTER = %d\n", temporal->TEMPORAL_COUNTER);
#endif

	temporal->PREVIOUS_ENABLE = reg2->EN_CONTRAST_ENHANCEMENT_EXTERNAL;
}

void ContrastEnhancement_debug(REG* reg, REG2* reg2, REG3* reg3, TEMPORAL* temporal, IMG* img, int frame_n, LENH_PARAM* lenh_param,int debug_array[16][1024]) {

	/*
		Image Data & Gain
		ex 8.2 means 8bit integer  2bit decimal
	*/
	int idx_r = 0;                                                                          // 10 bit ,8.2 bit
	int idx_g = 0;                                                                          // 10 bit ,8.2 bit
	int idx_b = 0;                                                                          // 10 bit ,8.2 bit
	int r_gain = 0;                                                                         // 12 bit ,2.10 bit  
	int g_gain = 0;                                                                         // 12 bit ,2.10 bit 
	int b_gain = 0;                                                                         // 12 bit ,2.10 bit 
	int final_overall_gain = 0;                                                             // 12 bit ,2.10 bit 
	unsigned int count_y = 0;																// 10 bit ,8.2 bit


	// Fitting Idx              
	int fitting_idx_r_1 = 0;                                                                // 7 bit
	int fitting_idx_g_1 = 0;                                                                // 7 bit
	int fitting_idx_b_1 = 0;                                                                // 7 bit

	int fitting_idx_r_2 = 0;                                                                // 3 bit
	int fitting_idx_g_2 = 0;                                                                // 3 bit
	int fitting_idx_b_2 = 0;                                                                // 3 bit

	int TEMP_FITTING_CURVE_R[8] = { 0 };                                                    // 12 bit
	int TEMP_FITTING_CURVE_G[8] = { 0 };                                                    // 12 bit
	int TEMP_FITTING_CURVE_B[8] = { 0 };                                                    // 12 bit
	int max_rgb = 0;

	// Round Temp 
	unsigned int result_temp_r1 = 0;                                                               // 22 bit
	unsigned int result_temp_g1 = 0;                                                               // 22 bit
	unsigned int result_temp_b1 = 0;                                                               // 22 bit

	unsigned int result_temp_r2 = 0;                                                               // 13 bit
	unsigned int result_temp_g2 = 0;                                                               // 13 bit
	unsigned int result_temp_b2 = 0;                                                               // 13 bit

	unsigned int result_temp_r3 = 0;                                                               // 12 bit
	unsigned int result_temp_g3 = 0;                                                               // 12 bit
	unsigned int result_temp_b3 = 0;                                                               // 12 bit

	unsigned int result_temp_r4 = 0;                                                               // 10 bit
	unsigned int result_temp_g4 = 0;                                                               // 10 bit
	unsigned int result_temp_b4 = 0;                                                               // 10 bit


	unsigned int input_array[1024] = { 0 };
	unsigned int result_array[1024] = { 0 };
	// Saturation_flag 
	int saturation_flag = 0;                                                                       // 1bit

	// enable pin change will initial
	//if (temporal->PREVIOUS_ENABLE != reg2->EN_CONTRAST_ENHANCEMENT_EXTERNAL)
	//	Curve_Initial(reg2, reg3, temporal);    


	for (int i = 0; i < 1024; i++)
		input_array[i] = i;


	for (int i = 0; i < 1024; i++) {

		saturation_flag = 0;
		idx_r = input_array[i];
		idx_g = input_array[i];
		idx_b = input_array[i];


		// 20240910 new update for special case , create new control mode
		max_rgb = I_MAX(idx_r, I_MAX(idx_g, idx_b));

		if (reg2->MAX_GAIN_MODE == 1)
		{
			idx_r = max_rgb;
			idx_g = max_rgb;
			idx_b = max_rgb;
		}

		fitting_idx_r_1 = (idx_r & 0x3f8) >> 3;                         // valid 7bit
		fitting_idx_g_1 = (idx_g & 0x3f8) >> 3;                         // valid 7bit
		fitting_idx_b_1 = (idx_b & 0x3f8) >> 3;                         // valid 7bit

		fitting_idx_r_2 = idx_r & 0x007;                                // valid 3bit
		fitting_idx_g_2 = idx_g & 0x007;                                // valid 3bit
		fitting_idx_b_2 = idx_b & 0x007;                                // valid 3bit

		TEMP_FITTING_CURVE_R[0] = temporal->PREVIOUS_FINAL_CURVE[fitting_idx_r_1];
		TEMP_FITTING_CURVE_R[1] = (7 * temporal->PREVIOUS_FINAL_CURVE[fitting_idx_r_1] + 1 * temporal->PREVIOUS_FINAL_CURVE[fitting_idx_r_1 + 1]) >> 3; // u0.3 * u2.10 + u0.3 * u2.10 = u3.13 ; u3.13 >> 3 = u3.10 ; valid bit = u2.10
		TEMP_FITTING_CURVE_R[2] = (6 * temporal->PREVIOUS_FINAL_CURVE[fitting_idx_r_1] + 2 * temporal->PREVIOUS_FINAL_CURVE[fitting_idx_r_1 + 1]) >> 3;
		TEMP_FITTING_CURVE_R[3] = (5 * temporal->PREVIOUS_FINAL_CURVE[fitting_idx_r_1] + 3 * temporal->PREVIOUS_FINAL_CURVE[fitting_idx_r_1 + 1]) >> 3;
		TEMP_FITTING_CURVE_R[4] = (4 * temporal->PREVIOUS_FINAL_CURVE[fitting_idx_r_1] + 4 * temporal->PREVIOUS_FINAL_CURVE[fitting_idx_r_1 + 1]) >> 3;
		TEMP_FITTING_CURVE_R[5] = (3 * temporal->PREVIOUS_FINAL_CURVE[fitting_idx_r_1] + 5 * temporal->PREVIOUS_FINAL_CURVE[fitting_idx_r_1 + 1]) >> 3;
		TEMP_FITTING_CURVE_R[6] = (2 * temporal->PREVIOUS_FINAL_CURVE[fitting_idx_r_1] + 6 * temporal->PREVIOUS_FINAL_CURVE[fitting_idx_r_1 + 1]) >> 3;
		TEMP_FITTING_CURVE_R[7] = (1 * temporal->PREVIOUS_FINAL_CURVE[fitting_idx_r_1] + 7 * temporal->PREVIOUS_FINAL_CURVE[fitting_idx_r_1 + 1]) >> 3;

		TEMP_FITTING_CURVE_G[0] = temporal->PREVIOUS_FINAL_CURVE[fitting_idx_g_1];
		TEMP_FITTING_CURVE_G[1] = (7 * temporal->PREVIOUS_FINAL_CURVE[fitting_idx_g_1] + 1 * temporal->PREVIOUS_FINAL_CURVE[fitting_idx_g_1 + 1]) >> 3;
		TEMP_FITTING_CURVE_G[2] = (6 * temporal->PREVIOUS_FINAL_CURVE[fitting_idx_g_1] + 2 * temporal->PREVIOUS_FINAL_CURVE[fitting_idx_g_1 + 1]) >> 3;
		TEMP_FITTING_CURVE_G[3] = (5 * temporal->PREVIOUS_FINAL_CURVE[fitting_idx_g_1] + 3 * temporal->PREVIOUS_FINAL_CURVE[fitting_idx_g_1 + 1]) >> 3;
		TEMP_FITTING_CURVE_G[4] = (4 * temporal->PREVIOUS_FINAL_CURVE[fitting_idx_g_1] + 4 * temporal->PREVIOUS_FINAL_CURVE[fitting_idx_g_1 + 1]) >> 3;
		TEMP_FITTING_CURVE_G[5] = (3 * temporal->PREVIOUS_FINAL_CURVE[fitting_idx_g_1] + 5 * temporal->PREVIOUS_FINAL_CURVE[fitting_idx_g_1 + 1]) >> 3;
		TEMP_FITTING_CURVE_G[6] = (2 * temporal->PREVIOUS_FINAL_CURVE[fitting_idx_g_1] + 6 * temporal->PREVIOUS_FINAL_CURVE[fitting_idx_g_1 + 1]) >> 3;
		TEMP_FITTING_CURVE_G[7] = (1 * temporal->PREVIOUS_FINAL_CURVE[fitting_idx_g_1] + 7 * temporal->PREVIOUS_FINAL_CURVE[fitting_idx_g_1 + 1]) >> 3;

		TEMP_FITTING_CURVE_B[0] = temporal->PREVIOUS_FINAL_CURVE[fitting_idx_b_1];
		TEMP_FITTING_CURVE_B[1] = (7 * temporal->PREVIOUS_FINAL_CURVE[fitting_idx_b_1] + 1 * temporal->PREVIOUS_FINAL_CURVE[fitting_idx_b_1 + 1]) >> 3;
		TEMP_FITTING_CURVE_B[2] = (6 * temporal->PREVIOUS_FINAL_CURVE[fitting_idx_b_1] + 2 * temporal->PREVIOUS_FINAL_CURVE[fitting_idx_b_1 + 1]) >> 3;
		TEMP_FITTING_CURVE_B[3] = (5 * temporal->PREVIOUS_FINAL_CURVE[fitting_idx_b_1] + 3 * temporal->PREVIOUS_FINAL_CURVE[fitting_idx_b_1 + 1]) >> 3;
		TEMP_FITTING_CURVE_B[4] = (4 * temporal->PREVIOUS_FINAL_CURVE[fitting_idx_b_1] + 4 * temporal->PREVIOUS_FINAL_CURVE[fitting_idx_b_1 + 1]) >> 3;
		TEMP_FITTING_CURVE_B[5] = (3 * temporal->PREVIOUS_FINAL_CURVE[fitting_idx_b_1] + 5 * temporal->PREVIOUS_FINAL_CURVE[fitting_idx_b_1 + 1]) >> 3;
		TEMP_FITTING_CURVE_B[6] = (2 * temporal->PREVIOUS_FINAL_CURVE[fitting_idx_b_1] + 6 * temporal->PREVIOUS_FINAL_CURVE[fitting_idx_b_1 + 1]) >> 3;
		TEMP_FITTING_CURVE_B[7] = (1 * temporal->PREVIOUS_FINAL_CURVE[fitting_idx_b_1] + 7 * temporal->PREVIOUS_FINAL_CURVE[fitting_idx_b_1 + 1]) >> 3;

		r_gain = TEMP_FITTING_CURVE_R[fitting_idx_r_2];
		g_gain = TEMP_FITTING_CURVE_G[fitting_idx_g_2];
		b_gain = TEMP_FITTING_CURVE_B[fitting_idx_b_2];

		if (idx_r == 0)
			r_gain = 0;

		if (idx_g == 0)
			g_gain = 0;

		if (idx_b == 0)
			b_gain = 0;

		if (r_gain == 0)
			if (g_gain == 0)
				final_overall_gain = b_gain;
			else if (b_gain == 0)
				final_overall_gain = g_gain;
			else
				final_overall_gain = I_MIN(g_gain, b_gain);
		else if (g_gain == 0)
			if (r_gain == 0)
				final_overall_gain = b_gain;
			else if (b_gain == 0)
				final_overall_gain = r_gain;
			else
				final_overall_gain = I_MIN(r_gain, b_gain);
		else if (b_gain == 0)
			if (r_gain == 0)
				final_overall_gain = g_gain;
			else if (g_gain == 0)
				final_overall_gain = r_gain;
			else
				final_overall_gain = I_MIN(r_gain, g_gain);
		else
			final_overall_gain = I_MIN(r_gain, I_MIN(g_gain, b_gain));

		// 8.2 * 2.10 = 10.12
		result_temp_r1 = input_array[i] * final_overall_gain;
		result_temp_g1 = input_array[i] * final_overall_gain;
		result_temp_b1 = input_array[i] * final_overall_gain;

		// 10.12 --> 10.3
		result_temp_r2 = result_temp_r1 >> 9;
		result_temp_g2 = result_temp_g1 >> 9;
		result_temp_b2 = result_temp_b1 >> 9;

		// 10.3 round to  10.2
		result_temp_r3 = ((result_temp_r2 & 0b1) ? ((result_temp_r2 >> 1) + 1) : (result_temp_r2 >> 1));
		result_temp_g3 = ((result_temp_g2 & 0b1) ? ((result_temp_g2 >> 1) + 1) : (result_temp_g2 >> 1));
		result_temp_b3 = ((result_temp_b2 & 0b1) ? ((result_temp_b2 >> 1) + 1) : (result_temp_b2 >> 1));

		// 10.2 to 8.2
		result_temp_r4 = I_MIN(result_temp_r3, 1023) & 0x3ff;
		result_temp_g4 = I_MIN(result_temp_g3, 1023) & 0x3ff;
		result_temp_b4 = I_MIN(result_temp_b3, 1023) & 0x3ff;

		if (result_temp_r4 > reg2->SATURATION_THRESHOLD || result_temp_g4 > reg2->SATURATION_THRESHOLD || result_temp_b4 > reg2->SATURATION_THRESHOLD)
		{
			saturation_flag = 1;
		}
		else
		{
			saturation_flag = 0;
		}

		if (idx_r >= reg2->GREY_THRESHOLD || idx_g >= reg2->GREY_THRESHOLD || idx_b >= reg2->GREY_THRESHOLD || reg2->EN_CONTRAST_ENHANCEMENT_EXTERNAL == 0 || saturation_flag == 1)
		{
			result_array[i] = input_array[i];
		}
		else
		{
			result_array[i] = result_temp_r4;
		}
	}



	for (int i = 0; i < 1024; i++)
		debug_array[frame_n][i] =  result_array[i];

}

/*
	Original Lenh signal is same for sunlight readable & local dimming
*/
void Lenh_Control_module(REG3* reg3, LENH_PARAM* lenh_param) {

	/*
					LENH HOST             (Write by Host)
						|
						|
				  LENH_EXTERNAL           (Filter & Take 12 bit LENH)
				 |      |      |
				 |      |      |
				IP1    IP2    IP3         (each IP take same LENH)

	*/

	// LENH_HOST simualte LENH signal from host. (signal is 16 bit) 
	// LENH UPDATE FRAME is update frequency.  For sample(filter) lenh signal.

	// LENH_EXTERNAL [11:0] 
	// LENH_HOST     [15:0] 

	if (lenh_param->LENH_COUNT == reg3->LENH_UPDATE_NUMBER)
	{
		lenh_param->LENH_GLOBAL = reg3->LENH_EXTERNAL >> 4;
		lenh_param->LENH_COUNT = 0;
	}
	else
	{
		;
	}
	lenh_param->LENH_COUNT++;
}
