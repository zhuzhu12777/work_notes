
# ContrastEnhancement

## FRM_AVG
计算图像平均亮度值
Y = (1228 * R + 2402 * G + 466 * B) / 4096
avg = Y_sum / INTENSITY_SELECT

## CONTRAST_RGB_GAIN
根据上一帧Vblank产生的增益曲线（PREVIOUS_FINAL_CURVE）计算增益
r_gain / g_gain / b_gain

## CURVE_CALC
更新PREVIOUS_FINAL_CURVE曲线，包括CONTENT_TARGET_CURVE，LENH_CURVE，TEMPORAL_FILTER

### CONTENT_TARGET_CURVE
LOW_HISTOGRAM_CURVE / HIGH_HISTOGRAM_CURVE 插值得到

### LENH_CURVE

### TEMPORAL_FILTER

## HISTOGRAM_CURVE_UPDATE
always @(posedge HVCLK or negedge HV_RSTB)
begin
    if(!HV_RSTB)
        HISTOGRAM_CURVE_UPDATE_D <= 1'b0;
    else if(VS_IN)
        HISTOGRAM_CURVE_UPDATE_D <= 1'b0;
    else if(HISTOGRAM_CURVE_UPDATE_V) 
        HISTOGRAM_CURVE_UPDATE_D <= 1'b1;
end

always@(*)
begin
    HISTOGRAM_CURVE_UPDATE_SW = HISTOGRAM_CURVE_UPDATE_D & VS_IN;
end

当VS_IN和HISTOGRAM_CURVE_UPDATE_V在同一个时钟触发，不会update？？？

# EdgeEnhancement

## EDGE_SEARCH_GAIN

## EDGE_LBUF_TOP
一个时钟两个像素pack成一个时钟四个像素，DE间隔分开，然后奇数时钟写入数据，偶数时钟读出数据，然后再将读出的像素值unpack成一个时钟两个像素，这样就能使用四块SPRAM进行5x5的卷积。

## EDGE_FILTER_OP

### EDGE_FILTER_TEMP
rgb_max RATIO

### EDGE_SORT
find the max and min value of 5 data

### EDGE_FILTER_SAT
rgb_sat = 256 * (rgb_max - rgb_min) / rgb_max

### EDGE_FILTER_BLUR
Y_blur += Y_temp * UNSHARP_MASK[m][n]

## RGB_ENH_TOP



# DIEDOP II
DIE: Dynamic Image Enhancement
DOP: Daylight Optimization

# LUT
GAIN[64]
UNSHARP_MASK[25]
HIGH_HISTOGRAM_CURVE[128]
LOW_HISTOGRAM_CURVE[128]
CONTENT_RATIO[33]
LENH_RATIO[64]
TEMPORAL_FILTER[32]

