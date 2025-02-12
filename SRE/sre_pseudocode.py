



def ContrastEnhancement():
    # 根据上一帧Vblank产生的增益曲线（PREVIOUS_FINAL_CURVE）应用到当前帧
    for vcnt in range(VACTIVE):
        for hcnt in range(HACTIVE):
            max_rgb = max(pixel_r, pixel_g, pixel_b)
            if MAX_GAIN_MODE == 1:
                idx_r = idx_g = idx_b = max_rgb
            else:
                idx_r = pixel_r
                idx_g = pixel_g
                idx_b = pixel_b
            for idx in [idx_r, idx_g, idx_b]:
                fitting_idx = idx>>3
                fitting_frac = idx&0x7
                rgb_gain = degamma(PREVIOUS_FINAL_CURVE, fitting_idx, fitting_frac)
            final_overall_gain = rgb_gain中最小且不为0的值
            
            for pixel_in in [pixel_r, pixel_g, pixel_b]:
                result_r1 = pixel_in * final_overall_gain
                result_r2 = (result_r1 + (1<<9))>>10
                result_r3 = clip(result_r2, 0, 1023)
                if idx_r/g/b > GREY_THRESHOLD or result_r3 > SATURATION_THRESHOLD:
                    pixel_out = pixel_in
                else:
                    pixel_out = result_r3

    # 计算图像平均亮度值
    for vcnt in range(VACTIVE):
        for hcnt in range(HACTIVE):
            count_y = ((1228 * pixel_r + 2402 * pixel_g + 466 * pixel_b) >> 12)       #YUV_Y
            Dividend = Dividend + count_y
            if Dividend >= INTENSITY_SELECT:
                Quotient += 1
                Dividend = Dividend - INTENSITY_SELECT

    # 保存当前帧增益曲线到PREVIOUS_FINAL_CURVE
    CURRENT_TEMPORAL_TARGET = Quotient>>2
    if abs(FIRST_TEMPORAL_TARGET - CURRENT_TEMPORAL_TARGET) <= TMP_CYCLE_THRESHOLD:     # 两帧之间增益变化小于阈值, 不更新PREVIOUS_FINAL_CURVE
        CURRENT_TEMPORAL_TARGET = FIRST_TEMPORAL_TARGET
    else:   # 两帧之间增益变化大于阈值, 更新PREVIOUS_FINAL_CURVE, 重置TEMPORAL_COUNTER
        TEMPORAL_COUNTER = 0
    if TEMPORAL_COUNTER == 0:   # 两帧之间增益变化大于阈值或COUNTER溢出
        FIRST_TEMPORAL_TARGET = CURRENT_TEMPORAL_TARGET

    # VBlanking area
    # 根据当前帧平均亮度值（CURRENT_TEMPORAL_TARGET）和用户设置的亮度值（LOWER_SETTING, UPPER_SETTING）计算下一帧的增益曲线
    if CURRENT_TEMPORAL_TARGET <= LOWER_SETTING:
        content_target_curve[128] = LOW_HISTOGRAM_CURVE[128] << 2   # LUT[128]
    elif CURRENT_TEMPORAL_TARGET >= UPPER_SETTING:
        content_target_curve[128] = HIGH_HISTOGRAM_CURVE[128] << 2  # LUT[128]
    else:
        content_setting_range = CURRENT_TEMPORAL_TARGET - LOWER_SETTING
        content_setting_range_tmp1 = content_setting_range * CONTENT_GAIN_RATIO
        content_setting_range_tmp2 = (content_setting_range_tmp1 + (1<<11))>>12
        content_setting_range_tmp3 = content_setting_range_tmp2 & 0x3f
        temp_content_ratio = clip(content_setting_range_tmp3, 0, 32)
        content_ratio = CONTENT_RATIO[temp_content_ratio]       # LUT[33]
        content_target_curve[128] = interpolation(HIGH_HISTOGRAM_CURVE<<2, LOW_HISTOGRAM_CURVE<<2, content_ratio)   # LUT[128]

    # 根据环境亮度值Lenhance调整增益曲线
    temp_lenh_ratio = (LENH_GLOBAL * LENH_GAIN)>>14
    lenh_ratio = LENH_RATIO[temp_lenh_ratio]
    lenh_curve[128] = interpolation(LENH_TARGET, content_target_curve, lenh_ratio)    # LUT[128]

    # Temporal_Filter, 平滑帧间变化
    if lenh_curve[0] >= PREVIOUS_FINAL_CURVE[0]:
        rising_state = 1
    else:
        rising_state = 0
    
    if rising_state == 1:
        filter_table[16] = TEMPORAL_FILTER[0:16]        # 前16个值为rising table
    else:
        filter_table[16] = TEMPORAL_FILTER[16:32]       # 后16个值为falling table

    if TMP_FILTER_ENABLE == 1:
        filter_ratio = filter_table[TEMPORAL_COUNTER]
        temporal_output_curve[128] = interpolation(PREVIOUS_FINAL_CURVE, lenh_curve, filter_ratio)    # LUT[128]
    else:
        temporal_output_curve[128] = lenh_curve[128]
    if TEMPORAL_COUNTER < TMP_CYCLE_NUMBER:
        TEMPORAL_COUNTER += 1
    else:
        TEMPORAL_COUNTER = 0

    # 保存当前帧增益曲线到PREVIOUS_FINAL_CURVE
    for idx in range(128):
        PREVIOUS_FINAL_CURVE[idx] = temporal_output_curve[idx]
    PREVIOUS_FINAL_CURVE[128] = temporal_output_curve[127]

def EdgeEnhancement():
    # SearchGain, 根据LENH_GLOBAL查找增益值
    idx = LENH_GLOBAL>>6
    frac = LENH_GLOBAL&0x3f
    if idx == 64:
        gain = EDGE_GAIN[63]
    else:
        gain = interpolation(EDGE_GAIN[idx], EDGE_GAIN[idx+1], frac)    # LUT[64]
    
    # 边缘检测与增强
    for vcnt in range(VACTIVE):
        for hcnt in range(HACTIVE):
            if EN_EDGE_ENHANCE_EXTERNAL and vcnt >= MASK_SIZE/2 and vcnt < VACTIVE-MASK_SIZE/2 and hcnt >= MASK_SIZE/2 and hcnt < HACTIVE-MASK_SIZE/2:
                Y_blur = 0
                # 卷积核
                for m in range(MASK_SIZE):
                    for n in range(MASK_SIZE):
                        idx_x = hcnt - MASK_SIZE/2 + n  # 卷积核当前像素坐标
                        idx_y = vcnt - MASK_SIZE/2 + m
                        data_r = pixels_in[idx_y][idx_x][0]
                        data_g = pixels_in[idx_y][idx_x][1]
                        data_b = pixels_in[idx_y][idx_x][2]
                        rgb_max = max(data_r, data_g, data_b)
                        rgb_min = min(data_r, data_g, data_b)

                        if EN_MIX_RGB:
                            Y_temp = RATIO[0]*data_r + RATIO[1]*data_g + RATIO[2]*data_b ...    #LUT[3]
                        else:
                            Y_temp = rgb_max

                        Y_max = max(rgb_max, Y_temp)
                        Y_min = min(rgb_min, Y_temp)

                        if m==MASK_SIZE/2 and n==MASK_SIZE/2:
                            Y_center = Y_temp
                            if rgb_max != 0:
                                rgb_sat = 256 * (rgb_max - rgb_min) / rgb_max
                            else:
                                rgb_sat = 0
                        Y_blur += Y_temp * UNSHARP_MASK[m][n] ...    #LUT[5][5]

                Y_blur = clip(Y_blur, Y_min, Y_max)
                Y_boundary = Y_center - Y_blur      # 边缘强度, positive表示边缘增强, negative表示边缘减弱

                # 保护机制
                if EN_PROTECTION_HIGH:
                    if Y_boundary > 0:
                        Y_boundary = 0
                if EN_PROTECTION_SATURATION:
                    if Y_boundary > 0:
                        Y_boundary = (Y_boundary * (256 - rgb_sat) + 128) / 256	    # positive case
                    else:
                        Y_boundary = (Y_boundary * (256 - rgb_sat) - 128) / 256     # negative case
                if EN_PROTECTION_SMOOTH:
                    delta_blur = max(Y_max - Y_blur, Y_blur - Y_min)
                    if delta_blur < threshold_smooth:
                        Y_boundary = 0
                if EN_PROTECTION_LUM:
                    if Y_center > threshold_lum:
                        Y_boundary = 0
                
                # 边缘增强
                if Y_boundary == 0:
                    pixels_out[vcnt][hcnt] = pixels_in[vcnt][hcnt]
                else:
                    if EN_GAIN:
                        Y_boundary = Y_boundary * gain ... # 边缘增强增益, round, positive/negative
                    Y_enhance = Y_center + Y_boundary
                    Y_enhance = clip(Y_enhance, 0, 1023)
                    if Y_center != 0:
                        enhance_ratio = 256 * Y_enhance / Y_center
                    else:
                        enhance_ratio = 0
                    enhance_ratio = clip(enhance_ratio, 0, 1023)
                    pixels_out[vcnt][hcnt] = (pixels_in[vcnt][hcnt] * enhance_ratio + 128) >> 8   # round
            pixels_out[vcnt][hcnt] = pixels_in[vcnt][hcnt]
