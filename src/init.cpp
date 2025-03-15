#include "../include/liblvgl/lvgl.h"
#include "../include/main.h"
#include "liblvgl/core/lv_event.h"
#include "liblvgl/core/lv_obj_pos.h"
#include "liblvgl/extra/widgets/list/lv_list.h"
#include "liblvgl/font/lv_symbol_def.h"
#include "liblvgl/misc/lv_area.h"
#include <cstdint>
#include <stdio.h>
struct gui_btn {
  lv_obj_t *btn;
  lv_obj_t *text;
};

typedef enum {
  GUI_UNUSED = -1, /*will never use -1 as an auton*/
  GUI_POS, /*this enum will count up and start at 0 so it has not default
              auton*/
  GUI_NEG,
  GUI_SKL
} BtnState;

int8_t auton_state = GUI_UNUSED;

char *autonNameState;

static void posHand(lv_event_t *e) {
  lv_event_code_t code = lv_event_get_code(e);

  if (code == LV_EVENT_VALUE_CHANGED) {
    auton_state = GUI_POS;
  }
}

static void sklHand(lv_event_t *e) {
  lv_event_code_t code = lv_event_get_code(e);

  if (code == LV_EVENT_VALUE_CHANGED) {
    auton_state = GUI_SKL;
  }
}

typedef enum {
  GRAY = 0, /* skills and defult */
  BLUE,
  RED,
} ColorSel;

void gui() {
  lv_obj_set_style_bg_color(lv_scr_act(), lv_color_hex(0x282828), LV_PART_MAIN);

  struct gui_btn pos;
  pos.btn = lv_btn_create(lv_scr_act());
  lv_obj_add_event_cb(pos.btn, posHand, LV_EVENT_CLICKED, NULL);
  lv_obj_align(pos.btn, LV_ALIGN_LEFT_MID, 10, 40);
  lv_obj_add_flag(pos.btn, LV_OBJ_FLAG_CHECKABLE);

  pos.text = lv_label_create(pos.btn);
  lv_label_set_text(pos.text, "+");
  lv_obj_center(pos.text);

  struct gui_btn skl;
  skl.btn = lv_btn_create(lv_scr_act());
  lv_obj_add_event_cb(skl.btn, sklHand, LV_EVENT_CLICKED, NULL);
  lv_obj_align(skl.btn, LV_ALIGN_LEFT_MID, 10, 20);
  lv_obj_add_flag(skl.btn, LV_OBJ_FLAG_CHECKABLE);

  skl.text = lv_label_create(skl.btn);
  lv_label_set_text(skl.text, "SKILLS");
  lv_obj_center(skl.text);
}

void initialize() {
  gui();
}
