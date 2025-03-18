#include "../include/liblvgl/lvgl.h"
#include "../include/main.h"
#include "liblvgl/core/lv_disp.h"
#include "liblvgl/core/lv_event.h"
#include "liblvgl/core/lv_obj_pos.h"
#include "liblvgl/extra/widgets/list/lv_list.h"
#include "liblvgl/font/lv_symbol_def.h"
#include "liblvgl/misc/lv_area.h"
#include <cstdint>
#include <stdio.h>
#include "../include/auton.hpp"
#include "globle.hpp"
#include "liblvgl/widgets/lv_label.h"

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

static void negHand(lv_event_t *e) {
  lv_event_code_t code = lv_event_get_code(e);

  if (code == LV_EVENT_VALUE_CHANGED) {
    auton_state = GUI_NEG;
  }
}

void gui() {
  lv_obj_set_style_bg_color(lv_scr_act(), lv_color_hex(0x282828), LV_PART_MAIN);

  std::int32_t thing = nimu.get_rotation(), thingtwo = rimu.get_rotation();

  lv_obj_t * lable = lv_label_create(lv_scr_act());
  lv_label_set_text_fmt(lable, "imu 1's head is %i \n and imu 2's head is %i", thing,thingtwo);
  lv_obj_align(lable, LV_ALIGN_TOP_RIGHT, -60, 0);

  struct gui_btn pos;
  pos.btn = lv_btn_create(lv_scr_act());
  lv_obj_add_event_cb(pos.btn, posHand, LV_EVENT_CLICKED, NULL);
  lv_obj_align(pos.btn, LV_ALIGN_TOP_LEFT, 10, 50);
  lv_obj_set_size(pos.btn, 200,30);

  pos.text = lv_label_create(pos.btn);
  lv_label_set_text(pos.text, "1");
  lv_obj_center(pos.text);

  struct gui_btn skl;
  skl.btn = lv_btn_create(lv_scr_act());
  lv_obj_add_event_cb(skl.btn, sklHand, LV_EVENT_CLICKED, NULL);
  lv_obj_align(skl.btn, LV_ALIGN_LEFT_MID, 10, -5);
  lv_obj_set_size(skl.btn, 200,30);

  skl.text = lv_label_create(skl.btn);
  lv_label_set_text(skl.text, "SKILLS");
  lv_obj_center(skl.text);
  
  struct gui_btn neg;
  neg.btn = lv_btn_create(lv_scr_act());
  lv_obj_add_event_cb(neg.btn, negHand, LV_EVENT_CLICKED, NULL);
  lv_obj_align(neg.btn, LV_ALIGN_BOTTOM_LEFT, 10, -60);
  lv_obj_set_size(neg.btn, 200,30);
  
  neg.text = lv_label_create(neg.btn);
  lv_label_set_text(neg.text, "1 for blu +");
  lv_obj_center(neg.text);
}

void initialize() {
  gui();
}
