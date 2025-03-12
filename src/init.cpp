#include "../include/liblvgl/lvgl.h"
#include "liblvgl/core/lv_event.h"
#include "liblvgl/core/lv_obj_pos.h"
#include "liblvgl/extra/widgets/list/lv_list.h"
#include "liblvgl/font/lv_symbol_def.h"
#include "liblvgl/misc/lv_area.h"
#include <cstdint>
#include <stdio.h>

typedef struct {
	int32_t width;
	int32_t height;
	bool checkable;
	char *text;
} gui_btn;

typedef enum { GUI_UNUSED = -1, /*will never use -1 as an auton*/
               GUI_POS, /*this enum will count up and start at 0 so it has not default auton*/
               GUI_NEG,
               GUI_SKL
} BtnState;

int8_t auton_state = GUI_UNUSED;

static void btnHand(lv_event_t *e) {
    lv_event_code_t code = lv_event_get_code(e);
    
    int32_t btnID = 2; // fix var

    switch (btnID) {
    
    }
}

void initialize() {
    lv_obj_set_style_bg_color(lv_scr_act(), lv_color_hex(0x282828), LV_PART_MAIN);
    

}
