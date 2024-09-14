/*
 * Copyright 2022 Kevin Gee <info@controller.works>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H

// Left-hand home row mods
#define CTL_A LCTL_T(KC_A)
#define GUI_S LGUI_T(KC_S)
#define ALT_D LALT_T(KC_D)
#define SFT_F LSFT_T(KC_F)

// Right-hand home row mods
#define SFT_J RSFT_T(KC_J)
#define ALT_K RALT_T(KC_K)
#define GUI_L RGUI_T(KC_L)
#define CTL_SCLN LCTL_T(KC_SCLN)

// One shod mods (toggles)
#define TG_LSFT OSM(MOD_LSFT)
#define TG_LALT OSM(MOD_LALT)
#define TG_LGUI OSM(MOD_LGUI)
#define TG_LCTL OSM(MOD_LCTL)

#define ESC_LCTL LCTL_T(KC_ESC)
#define CTL_TAB LCTL(KC_TAB)
#define C_S_TAB LCTL(LSFT(KC_TAB))
#define SFT_ALT LSFT(KC_LALT)
#define SFT_INS LSFT(KC_INS)
#define C_S_PUP LCTL(LSFT(KC_PAGE_UP))
#define C_S_PDN LCTL(LSFT(KC_PAGE_DOWN))
#define C_SCLN  LCTL(KC_SCLN)
#define C_QUOTE LCTL(KC_QUOT)

#define VIM_ESC SS_LCTL("\\n")

#define l_qwt 0
#define l_ls1 1
#define l_arw 2
#define l_sym 3
#define l_del 4
#define l_fig 5
#define l_fun 6
#define l_rs1 7
#define l_vim 8
#define l_med 9
#define l_nav 11
#define l_ctl 12

#define spc_ls1 LT(l_ls1, KC_SPC)
#define ent_rs1 LT(l_rs1, KC_ENT)

enum tap_dance_codes {
  D_PRN,
  D_ABK,
  D_CBR,
  D_BRC,
  D_MTH,
};

tap_dance_action_t tap_dance_actions[] = {
  [D_PRN] = ACTION_TAP_DANCE_DOUBLE(KC_LPRN, KC_RPRN),
  [D_ABK] = ACTION_TAP_DANCE_DOUBLE(KC_LABK, KC_RABK),
  [D_CBR] = ACTION_TAP_DANCE_DOUBLE(KC_LCBR, KC_RCBR),
  [D_BRC] = ACTION_TAP_DANCE_DOUBLE(KC_LBRC, KC_RBRC),
  [D_MTH] = ACTION_TAP_DANCE_DOUBLE(KC_SLASH, KC_ASTR),
};

enum combos {
  L_ARW,
  L_SYM,
  L_DEL,
  L_FIG,
  L_FUN,
  L_VIM,
  L_MED,
  L_NAV,
  L_CTL,
  L_CTR,
  JK_ESC,
  FJ_CAPS,
};

const uint16_t PROGMEM l_arw_combo[] = {CTL_A, spc_ls1, COMBO_END};
const uint16_t PROGMEM l_sym_combo[] = {GUI_S, spc_ls1, COMBO_END};
const uint16_t PROGMEM l_del_combo[] = {ALT_D, spc_ls1, COMBO_END};
const uint16_t PROGMEM l_fig_combo[] = {SFT_F, spc_ls1, COMBO_END};
const uint16_t PROGMEM l_fun_combo[] = {KC_R, spc_ls1, COMBO_END};
const uint16_t PROGMEM l_vim_combo[] = {SFT_J, ent_rs1, COMBO_END};
const uint16_t PROGMEM l_med_combo[] = {ALT_K, ent_rs1, COMBO_END};
const uint16_t PROGMEM l_nav_combo[] = {CTL_SCLN, ent_rs1, COMBO_END};
const uint16_t PROGMEM l_ctl_combo[] = {KC_T, spc_ls1, COMBO_END};
const uint16_t PROGMEM l_ctr_combo[] = {KC_Y, ent_rs1, COMBO_END};
const uint16_t PROGMEM jk_esc_combo[] = {SFT_J, ALT_K, COMBO_END};
const uint16_t PROGMEM fj_caps_combo[] = {SFT_F, SFT_J, COMBO_END};

combo_t key_combos[] = {
  [L_ARW] = COMBO(l_arw_combo, MO(l_arw)),
  [L_SYM] = COMBO(l_sym_combo, MO(l_sym)),
  [L_DEL] = COMBO(l_del_combo, MO(l_del)),
  [L_FIG] = COMBO(l_fig_combo, MO(l_fig)),
  [L_FUN] = COMBO(l_fun_combo, MO(l_fun)),
  [L_VIM] = COMBO(l_vim_combo, MO(l_vim)),
  [L_MED] = COMBO(l_med_combo, MO(l_med)),
  [L_NAV] = COMBO(l_nav_combo, MO(l_nav)),
  [L_CTL] = COMBO(l_ctl_combo, MO(l_ctl)),
  [L_CTR] = COMBO(l_ctr_combo, MO(l_ctl)),
  [JK_ESC] = COMBO(jk_esc_combo, KC_ESC),
  [FJ_CAPS] = COMBO(fj_caps_combo, CW_TOGG),
};

enum custom_keycodes {
  A_TMXCP = SAFE_RANGE,
  A_VIMNM,
  A_VIMEX,
  A_VIMWQ,
  A_VIMWR,
  A_VIMTE,
  A_VIMCW,
  A_VIMNT,
  A_VIMGD,
  A_VIMWD,
  A_VIMND,
  A_VIMPD,
  A_VIMPT,
  K_JIGGL,
};

bool is_gui_tab_active = false;
bool is_mouse_jiggle_active = false;
bool is_caps_word_active = false;
uint16_t gui_tab_timer = 0;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case A_TMXCP:
      if (record->event.pressed) SEND_STRING(SS_LCTL(" ") "[");
      break;
    case A_VIMNM:
      if (record->event.pressed) SEND_STRING(VIM_ESC);
      break;
    case A_VIMEX:
      if (record->event.pressed) SEND_STRING(VIM_ESC ":qa\n");
      break;
    case A_VIMWQ:
      if (record->event.pressed) SEND_STRING(VIM_ESC ":wq\n");
      break;
    case A_VIMWR:
      if (record->event.pressed) SEND_STRING(VIM_ESC ":w\n");
      break;
    case A_VIMTE:
      if (record->event.pressed) SEND_STRING(VIM_ESC ":OpenMainTerm\n");
      break;
    case A_VIMCW:
      if (record->event.pressed) SEND_STRING(VIM_ESC SS_LCTL("w") "c");
      break;
    case A_VIMGD:
      if (record->event.pressed) SEND_STRING(SS_LCTL("]"));
      break;
    case A_VIMWD:
      if (record->event.pressed) SEND_STRING(SS_LCTL("w") "]");
      break;
    case A_VIMND:
      if (record->event.pressed) SEND_STRING("]d");
      break;
    case A_VIMPD:
      if (record->event.pressed) SEND_STRING("[d");
      break;
    case A_VIMNT:
      if (record->event.pressed) SEND_STRING(VIM_ESC ":tabnext\n");
      break;
    case A_VIMPT:
      if (record->event.pressed) SEND_STRING(VIM_ESC ":tabprevious\n");
      break;
    case K_JIGGL:
      if (record->event.pressed) {
        is_mouse_jiggle_active = !is_mouse_jiggle_active;
      }
  }
  return true;
}

void matrix_scan_user(void) {
  if (is_mouse_jiggle_active) {
    tap_code(KC_MS_UP);
    tap_code(KC_MS_DOWN);
  }
}

void caps_word_set_user(bool active) {
  is_caps_word_active = active;
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  // qwerty layout
  [l_qwt] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------------.                      ,-----------------------------------------------------------.
       XXXXXXX,     KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,                            KC_Y,     KC_U,     KC_I,     KC_O,    KC_P,   XXXXXXX,
  //|---------+---------+---------+---------+---------+---------|                      |---------+---------+---------+---------+---------+---------|
       XXXXXXX,    CTL_A,    GUI_S,    ALT_D,    SFT_F,     KC_G,                            KC_H,    SFT_J,    ALT_K,    GUI_L, CTL_SCLN,  XXXXXXX,
  //|---------+---------+---------+---------+---------+---------|                      |---------+---------+---------+---------+---------+---------|
       XXXXXXX,     KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,                            KC_N,     KC_M,  KC_COMM,   KC_DOT,  KC_SLSH,  XXXXXXX,
  //|---------+---------+---------+---------+---------+---------+---------|  |---------+---------+---------+---------+---------+---------+---------|
                                                KC_TAB,   QK_REP,  spc_ls1,     ent_rs1,  KC_BSPC,   KC_TAB
                                          //`-----------------------------'  `-----------------------------'

  ),

  // Left board layer shortuts
  [l_ls1] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------------.                      ,-----------------------------------------------------------.
       XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,TT(l_fun),TT(l_ctl),                         XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
  //|---------+---------+---------+---------+---------+---------|                      |---------+---------+---------+---------+---------+---------|
       XXXXXXX,TT(l_arw),TT(l_sym),TT(l_del),TT(l_fig),  XXXXXXX,                         XXXXXXX,  XXXXXXX,  XXXXXXX,   C_SCLN,  C_QUOTE,  XXXXXXX,
  //|---------+---------+---------+---------+---------+---------|                      |---------+---------+---------+---------+---------+---------|
       XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,                         XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
  //|---------+---------+---------+---------+---------+---------+---------|  |---------+---------+---------+---------+---------+---------+---------|
                                             TO(l_qwt),  _______,  _______,     _______,   KC_DEL,TO(l_qwt)
                                          //`-----------------------------'  `-----------------------------'
  ),

  // Arrows and mouse keys
  [l_arw] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------------.                      ,-----------------------------------------------------------.
       XXXXXXX,  XXXXXXX,  KC_BTN1,  KC_BTN2,  SFT_ALT,  KC_BTN3,                         KC_LEFT,  KC_DOWN,    KC_UP,  KC_RGHT,   KC_ESC,  XXXXXXX,
  //|---------+---------+---------+---------+---------+---------|                      |---------+---------+---------+---------+---------+---------|
       XXXXXXX,TT(l_arw),  KC_LCTL,  KC_LGUI,  KC_LALT,  KC_LSFT,                         KC_MS_L,  KC_MS_D,  KC_MS_U,  KC_MS_R,   KC_TAB,  XXXXXXX,
  //|---------+---------+---------+---------+---------+---------|                      |---------+---------+---------+---------+---------+---------|
       XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  K_JIGGL,                         KC_WH_L,  KC_WH_U,  KC_WH_D,  KC_WH_R,  KC_BTN3,  XXXXXXX,
  //|---------+---------+---------+---------+---------+---------+---------|  |---------+---------+---------+---------+---------+---------+---------|
                                             TO(l_qwt),  _______,  _______,     KC_BTN1,  KC_BTN2,TO(l_qwt)
                                          //`-----------------------------'  `-----------------------------'
  ),

  // Symbols
  [l_sym] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------------.                      ,-----------------------------------------------------------.
       XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  SFT_ALT,  XXXXXXX,                         KC_TILD,  KC_HASH,  KC_ASTR,  KC_PERC,  XXXXXXX,  XXXXXXX,
  //|---------+---------+---------+---------+---------+---------|                      |---------+---------+---------+---------+---------+---------|
       XXXXXXX,  KC_LCTL,TT(l_sym),  KC_LGUI,  KC_LALT,  KC_LSFT,                         KC_CIRC,    KC_AT,  KC_EXLM,  KC_AMPR,   KC_DLR,  XXXXXXX,
  //|---------+---------+---------+---------+---------+---------|                      |---------+---------+---------+---------+---------+---------|
       XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,                         KC_PLUS,  KC_MINS,   KC_EQL,  KC_UNDS,  XXXXXXX,  XXXXXXX,
  //|---------+---------+---------+---------+---------+---------+---------|  |---------+---------+---------+---------+---------+---------+---------|
                                             TO(l_qwt),  _______,  _______,     ent_rs1,  KC_BSPC,TO(l_qwt)
                                          //`-----------------------------'  `-----------------------------'
  ),

  // Delimiters
  [l_del] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------------.                      ,-----------------------------------------------------------.
       XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  SFT_ALT,  XXXXXXX,                         KC_PERC,  KC_QUOT,  KC_DQUO,   KC_GRV,  KC_PIPE,  XXXXXXX,
  //|---------+---------+---------+---------+---------+---------|                      |---------+---------+---------+---------+---------+---------|
       XXXXXXX,  KC_LCTL,  KC_LGUI,TT(l_del),  KC_LALT,  KC_LSFT,                       TD(D_ABK),TD(D_PRN),TD(D_CBR),TD(D_BRC),  KC_BSLS,  XXXXXXX,
  //|---------+---------+---------+---------+---------+---------|                      |---------+---------+---------+---------+---------+---------|
       XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,                         KC_ASTR,  XXXXXXX,  XXXXXXX,  XXXXXXX,  KC_SLSH,  XXXXXXX,
  //|---------+---------+---------+---------+---------+---------+---------|  |---------+---------+---------+---------+---------+---------+---------|
                                             TO(l_qwt),  _______,  _______,     _______,  _______,TO(l_qwt)
                                          //`-----------------------------'  `-----------------------------'
  ),

  // Numpad (figures)
  [l_fig] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------------.                      ,-----------------------------------------------------------.
       XXXXXXX,  XXXXXXX,  XXXXXXX,  SFT_ALT,  XXXXXXX,  XXXXXXX,                         KC_PLUS,     KC_7,     KC_8,     KC_9,   KC_EQL,  XXXXXXX,
  //|---------+---------+---------+---------+---------+---------|                      |---------+---------+---------+---------+---------+---------|
       XXXXXXX,  KC_LCTL,  KC_LGUI,  KC_LALT,TT(l_fig),  KC_LSFT,                         KC_MINS,     KC_4,     KC_5,     KC_6,     KC_0,  XXXXXXX,
  //|---------+---------+---------+---------+---------+---------|                      |---------+---------+---------+---------+---------+---------|
       XXXXXXX,  XXXXXXX,  XXXXXXX,  KC_LSFT,  XXXXXXX,  XXXXXXX,                          KC_DOT,     KC_1,     KC_2,     KC_3,TD(D_MTH),  XXXXXXX,
  //|---------+---------+---------+---------+---------+---------+---------|  |---------+---------+---------+---------+---------+---------+---------|
                                             TO(l_qwt),  _______,  _______,     _______,  _______,TO(l_qwt)
                                          //`-----------------------------'  `-----------------------------'
  ),

  // FN keys
  [l_fun] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------------.                      ,-----------------------------------------------------------.
       XXXXXXX,  XXXXXXX,  XXXXXXX,  SFT_ALT,TT(l_fun),  XXXXXXX,                         XXXXXXX,    KC_F7,    KC_F8,    KC_F9,   KC_F12,  XXXXXXX,
  //|---------+---------+---------+---------+---------+---------|                      |---------+---------+---------+---------+---------+---------|
       XXXXXXX,  KC_LCTL,  KC_LGUI,  KC_LALT,  KC_LSFT,  XXXXXXX,                         XXXXXXX,    KC_F4,    KC_F5,    KC_F6,   KC_F11,  XXXXXXX,
  //|---------+---------+---------+---------+---------+---------|                      |---------+---------+---------+---------+---------+---------|
       XXXXXXX,  XXXXXXX,  XXXXXXX,  KC_LSFT,  XXXXXXX,  XXXXXXX,                         XXXXXXX,    KC_F1,    KC_F2,    KC_F3,   KC_F10,  XXXXXXX,
  //|---------+---------+---------+---------+---------+---------+---------|  |---------+---------+---------+---------+---------+---------+---------|
                                             TO(l_qwt),  _______,  _______,     _______,  _______,TO(l_qwt)
                                          //`-----------------------------'  `-----------------------------'
  ),

  // Right board layer shortuts
  [l_rs1] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------------.                      ,-----------------------------------------------------------.
       XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,                       TT(l_ctl),  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
  //|---------+---------+---------+---------+---------+---------|                      |---------+---------+---------+---------+---------+---------|
       XXXXXXX,  TG_LCTL,  TG_LGUI,  TG_LALT,  TG_LSFT,  XXXXXXX,                         XXXXXXX,TT(l_vim),TT(l_med),  XXXXXXX,TT(l_nav),  XXXXXXX,
  //|---------+---------+---------+---------+---------+---------|                      |---------+---------+---------+---------+---------+---------|
       XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,                         XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
  //|---------+---------+---------+---------+---------+---------+---------|  |---------+---------+---------+---------+---------+---------+---------|
                                             TO(l_qwt),  _______,  _______,     _______,  _______,TO(l_qwt)
                                          //`-----------------------------'  `-----------------------------'
  ),

  // Vim macros
  [l_vim] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------------.                      ,-----------------------------------------------------------.
       XXXXXXX,  A_VIMEX,  A_VIMWQ,  A_VIMPD,  A_VIMND,  A_VIMTE,                         XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
  //|---------+---------+---------+---------+---------+---------|                      |---------+---------+---------+---------+---------+---------|
       XXXXXXX,  A_VIMNM,  A_VIMWR,  A_VIMPT,  A_VIMNT,  A_VIMGD,                         XXXXXXX,TT(l_vim),  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
  //|---------+---------+---------+---------+---------+---------|                      |---------+---------+---------+---------+---------+---------|
       XXXXXXX,  XXXXXXX,  XXXXXXX,  A_VIMCW,  XXXXXXX,  A_VIMWD,                         XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
  //|---------+---------+---------+---------+---------+---------+---------|  |---------+---------+---------+---------+---------+---------+---------|
                                             TO(l_qwt),  _______,  _______,     _______,  _______,TO(l_qwt)
                                          //`-----------------------------'  `-----------------------------'
  ),

  // Media controls
  [l_med] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------------.                      ,-----------------------------------------------------------.
       XXXXXXX,  XXXXXXX,  KC_VOLD,  KC_VOLU,  KC_MUTE,  KC_BRIU,                         XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
  //|---------+---------+---------+---------+---------+---------|                      |---------+---------+---------+---------+---------+---------|
       XXXXXXX,  XXXXXXX,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_BRID,                         XXXXXXX,  XXXXXXX,TT(l_med),  XXXXXXX,  XXXXXXX,  XXXXXXX,
  //|---------+---------+---------+---------+---------+---------|                      |---------+---------+---------+---------+---------+---------|
       XXXXXXX,  XXXXXXX,  KC_MRWD,  KC_MSTP,  KC_MFFD,  XXXXXXX,                         XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
  //|---------+---------+---------+---------+---------+---------+---------|  |---------+---------+---------+---------+---------+---------+---------|
                                             TO(l_qwt),  _______,  _______,     _______,  _______,TO(l_qwt)
                                          //`-----------------------------'  `-----------------------------'
  ),

  // Navigation layer
  [l_nav] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------------.                      ,-----------------------------------------------------------.
       XXXXXXX,  XXXXXXX,  XXXXXXX,  C_S_PUP,  C_S_PDN,  XXXXXXX,                         XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
  //|---------+---------+---------+---------+---------+---------|                      |---------+---------+---------+---------+---------+---------|
       XXXXXXX,MEH(KC_H),MEH(KC_L),  C_S_TAB,  CTL_TAB,MEH(KC_F),                         KC_LEFT,  KC_DOWN,    KC_UP,  KC_RGHT,TT(l_nav),  XXXXXXX,
  //|---------+---------+---------+---------+---------+---------|                      |---------+---------+---------+---------+---------+---------|
       XXXXXXX,  XXXXXXX,  XXXXXXX,  A_TMXCP,  SFT_INS,MEH(KC_T),                         XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
  //|---------+---------+---------+---------+---------+---------+---------|  |---------+---------+---------+---------+---------+---------+---------|
                                             TO(l_qwt),  _______,  _______,     _______,  _______,TO(l_qwt)
                                          //`-----------------------------'  `-----------------------------'
  ),

  // Board control layer
  [l_ctl] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------------.                      ,-----------------------------------------------------------.
       XXXXXXX,  XXXXXXX,  DT_DOWN,    DT_UP,  RGB_TOG,TT(l_ctl),                       TT(l_ctl),  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
  //|---------+---------+---------+---------+---------+---------|                      |---------+---------+---------+---------+---------+---------|
       XXXXXXX,  RGB_HUI,  RGB_SAI,  RGB_VAI,  RGB_SPI,  QK_BOOT,                         QK_BOOT,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
  //|---------+---------+---------+---------+---------+---------|                      |---------+---------+---------+---------+---------+---------|
       XXXXXXX,  RGB_HUD,  RGB_SAD,  RGB_VAD,  RGB_SPD,  RGB_MOD,                         XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
  //|---------+---------+---------+---------+---------+---------+---------|  |---------+---------+---------+---------+---------+---------+---------|
                                             TO(l_qwt),  _______,  _______,     _______,  _______,TO(l_qwt)
                                          //`-----------------------------'  `-----------------------------'
  ),
};

#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  return OLED_ROTATION_90;
}

void render_layer_status(void) {
  bool is_control_layer = false;
  switch (get_highest_layer(layer_state)) {
    case l_qwt:
      oled_write_ln_P(PSTR("     "), false);
      break;
    case l_ls1:
      oled_write_ln_P(PSTR("<- L "), false);
      break;
    case l_rs1:
      oled_write_ln_P(PSTR(" L ->"), false);
      break;
    case l_arw:
      oled_write_ln_P(PSTR("mouse"), false);
      break;
    case l_sym:
      oled_write_ln_P(PSTR("symbl"), false);
      break;
    case l_del:
      oled_write_ln_P(PSTR("delim"), false);
      break;
    case l_fig:
      oled_write_ln_P(PSTR(" num "), false);
      break;
    case l_fun:
      oled_write_ln_P(PSTR("funct"), false);
      break;
    case l_vim:
      oled_write_ln_P(PSTR(" vim "), false);
      break;
    case l_med:
      oled_write_ln_P(PSTR("media"), false);
      break;
    case l_nav:
      oled_write_ln_P(PSTR("nvgtn"), false);
      break;
    case l_ctl:
      oled_write_ln_P(PSTR("cntrl"), false);
      is_control_layer = true;
      break;
    default:
      oled_write_ln_P(PSTR("unkwn"), false);
  }
  uint8_t modifiers = get_mods();
  uint8_t oneshot_modifiers = get_oneshot_mods();
  if (is_keyboard_master()) {
    char modifier_str[5] = {
      (modifiers & MOD_MASK_SHIFT) ? 'S' : ' ',
      (modifiers & MOD_MASK_ALT) ? 'A' : ' ',
      (modifiers & MOD_MASK_GUI) ? 'G' : ' ',
      (modifiers & MOD_MASK_CTRL) ? 'C' : ' ',
      '\0'
    };
    oled_write_ln(modifier_str, false);
    char oneshot_modifier_str[5] = {
      (oneshot_modifiers & MOD_MASK_SHIFT) ? 's' : ' ',
      (oneshot_modifiers & MOD_MASK_ALT) ? 'a' : ' ',
      (oneshot_modifiers & MOD_MASK_GUI) ? 'g' : ' ',
      (oneshot_modifiers & MOD_MASK_CTRL) ? 'c' : ' ',
      '\0'
    };
    oled_write_ln(oneshot_modifier_str, false);
    if (is_control_layer) {
      const char *tapping_term_str = get_u16_str(g_tapping_term, ' ');
      // Skip padding spaces
      while (*tapping_term_str == ' ') {
        tapping_term_str++;
      }
      oled_write_ln(tapping_term_str, false);
    } else {
      oled_write_ln_P(PSTR("     "), false);
    }
    char feature_str[5] = {
      (is_caps_word_active) ? 'W' : ' ',
      (is_mouse_jiggle_active) ? 'M' : ' ',
      '\0'
    };
    oled_write_ln(feature_str, false);
  } else {
    char modifier_str[5] = {
      (modifiers & MOD_MASK_CTRL) ? 'C' : ' ',
      (modifiers & MOD_MASK_GUI) ? 'G' : ' ',
      (modifiers & MOD_MASK_ALT) ? 'A' : ' ',
      (modifiers & MOD_MASK_SHIFT) ? 'S' : ' ',
      '\0'
    };
    oled_write_ln(modifier_str, false);
    char oneshot_modifier_str[5] = {
      (oneshot_modifiers & MOD_MASK_CTRL) ? 'c' : ' ',
      (oneshot_modifiers & MOD_MASK_GUI) ? 'g' : ' ',
      (oneshot_modifiers & MOD_MASK_ALT) ? 'a' : ' ',
      (oneshot_modifiers & MOD_MASK_SHIFT) ? 's' : ' ',
      '\0'
    };
    oled_write_ln(oneshot_modifier_str, false);
    oled_write_ln_P(PSTR("     "), false);
  }
}

bool oled_task_user(void) {
  render_layer_status();
  return false;
}
#endif
