#include "../include/main.h"
#include <stdio.h>

void initialize() {
    /*Change the active screen's background color*/
    lv_obj_set_style_bg_color(lv_scr_act(), lv_color_hex(0x003a57), LV_PART_MAIN);

/*Create a white label, set its text and align it to the center*/
    lv_obj_t * label = lv_label_create(lv_scr_act());
    lv_label_set_text(label, "Hello world");
    lv_obj_set_style_text_color(label, lv_color_hex(0xffffff), LV_PART_MAIN);
    lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);
}
