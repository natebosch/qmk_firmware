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
#define ALT_A LALT_T(KC_A)
#define CTL_S LCTL_T(KC_S)
#define GUI_D LGUI_T(KC_D)
#define SFT_F LSFT_T(KC_F)

// Right-hand home row mods
#define SFT_J RSFT_T(KC_J)
#define GUI_K RGUI_T(KC_K)
#define CTL_L RCTL_T(KC_L)
#define ALT_SCLN LALT_T(KC_SCLN)

#define ESC_LCTL LCTL_T(KC_ESC)
#define CTL_TAB LCTL(KC_TAB)
#define C_S_TAB LCTL(LSFT(KC_TAB))

#define l_qwt 0
#define l_ls1 1
#define l_rs1 2
#define l_ls2 3
#define l_arw 4
#define l_sym 5
#define l_del 6
#define l_fig 7
#define l_fun 8
#define l_nav 9
#define l_ctl 10

enum tap_dance_codes {
  D_PRN,
  D_ABK,
  D_CBR,
  D_BRC,
};

tap_dance_action_t tap_dance_actions[] = {
  [D_PRN] = ACTION_TAP_DANCE_DOUBLE(KC_LPRN, KC_RPRN),
  [D_ABK] = ACTION_TAP_DANCE_DOUBLE(KC_LABK, KC_RABK),
  [D_CBR] = ACTION_TAP_DANCE_DOUBLE(KC_LCBR, KC_RCBR),
  [D_BRC] = ACTION_TAP_DANCE_DOUBLE(KC_LBRC, KC_RBRC),
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [l_qwt] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------------.                      ,-----------------------------------------------------------.
        KC_TAB,     KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,                            KC_Y,     KC_U,     KC_I,     KC_O,    KC_P,   KC_BSPC,
  //|---------+---------+---------+---------+---------+---------|                      |---------+---------+---------+---------+---------+---------|
      ESC_LCTL,    ALT_A,    CTL_S,    GUI_D,    SFT_F,     KC_G,                            KC_H,    SFT_J,    GUI_K,    CTL_L, ALT_SCLN,  KC_QUOT,
  //|---------+---------+---------+---------+---------+---------|                      |---------+---------+---------+---------+---------+---------|
       KC_LSFT,     KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,                            KC_N,     KC_M,  KC_COMM,   KC_DOT,  KC_SLSH,   RSFT_T(KC_ENT),
  //|---------+---------+---------+---------+---------+---------+---------|  |---------+---------+---------+---------+---------+---------+---------|
                                               KC_LGUI,MO(l_ls1),   KC_SPC,      KC_ENT,MO(l_rs1),  KC_RALT
                                          //`-----------------------------'  `-----------------------------'

  ),

  // Left board layer shortucts
  [l_ls1] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------------.                      ,-----------------------------------------------------------.
       XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,                         XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
  //|---------+---------+---------+---------+---------+---------|                      |---------+---------+---------+---------+---------+---------|
     MO(l_ls2),TT(l_arw),TT(l_sym),TT(l_del),TT(l_fig),  XXXXXXX,                         XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
  //|---------+---------+---------+---------+---------+---------|                      |---------+---------+---------+---------+---------+---------|
       XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,                         XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
  //|---------+---------+---------+---------+---------+---------+---------|  |---------+---------+---------+---------+---------+---------+---------|
                                               XXXXXXX,  _______,  XXXXXXX,     KC_BSPC,  XXXXXXX,    TO(0)
                                          //`-----------------------------'  `-----------------------------'
  ),
  [l_ls2] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------------.                      ,-----------------------------------------------------------.
       XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,                         XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
  //|---------+---------+---------+---------+---------+---------|                      |---------+---------+---------+---------+---------+---------|
       _______,  XXXXXXX,  XXXXXXX,  XXXXXXX,TT(l_fun),  XXXXXXX,                         XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
  //|---------+---------+---------+---------+---------+---------|                      |---------+---------+---------+---------+---------+---------|
       XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,                         XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
  //|---------+---------+---------+---------+---------+---------+---------|  |---------+---------+---------+---------+---------+---------+---------|
                                               XXXXXXX,  _______,  XXXXXXX,     _______,  XXXXXXX,  _______
                                          //`-----------------------------'  `-----------------------------'
  ),

  // Right board layer shortucts
  [l_rs1] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------------.                      ,-----------------------------------------------------------.
       XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,                         XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
  //|---------+---------+---------+---------+---------+---------|                      |---------+---------+---------+---------+---------+---------|
       XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,                         XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,TT(l_nav),TT(l_ctl),
  //|---------+---------+---------+---------+---------+---------|                      |---------+---------+---------+---------+---------+---------|
       XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,                         XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
  //|---------+---------+---------+---------+---------+---------+---------|  |---------+---------+---------+---------+---------+---------+---------|
                                               XXXXXXX,  XXXXXXX,  XXXXXXX,     XXXXXXX,  _______,  _______
                                          //`-----------------------------'  `-----------------------------'
  ),

  // Arrows and mouse keys
  [l_arw] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------------.                      ,-----------------------------------------------------------.
       XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,                         KC_LEFT,  KC_DOWN,    KC_UP,  KC_RGHT,  XXXXXXX,  XXXXXXX,
  //|---------+---------+---------+---------+---------+---------|                      |---------+---------+---------+---------+---------+---------|
       XXXXXXX,    TO(0),  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,                         KC_MS_L,  KC_MS_D,  KC_MS_U,  KC_MS_R,  XXXXXXX,  XXXXXXX,
  //|---------+---------+---------+---------+---------+---------|                      |---------+---------+---------+---------+---------+---------|
       XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,                         KC_WH_L,  KC_WH_D,  KC_WH_U,  KC_WH_R,  XXXXXXX,  XXXXXXX,
  //|---------+---------+---------+---------+---------+---------+---------|  |---------+---------+---------+---------+---------+---------+---------|
                                               XXXXXXX,  _______,  XXXXXXX,     KC_BTN1,  KC_BTN2,  _______
                                          //`-----------------------------'  `-----------------------------'
  ),

  // Symbols
  [l_sym] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------------.                      ,-----------------------------------------------------------.
       XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,                         KC_TILD,  KC_HASH,  KC_ASTR,  KC_PERC,  KC_AMPR,  XXXXXXX,
  //|---------+---------+---------+---------+---------+---------|                      |---------+---------+---------+---------+---------+---------|
       XXXXXXX,  XXXXXXX,    TO(0),  XXXXXXX,  XXXXXXX,  XXXXXXX,                         KC_CIRC,    KC_AT,  KC_EXLM,   KC_DLR,  XXXXXXX,  XXXXXXX,
  //|---------+---------+---------+---------+---------+---------|                      |---------+---------+---------+---------+---------+---------|
       XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,                         KC_MINS,   KC_EQL,  KC_UNDS,  KC_PLUS,  XXXXXXX,  XXXXXXX,
  //|---------+---------+---------+---------+---------+---------+---------|  |---------+---------+---------+---------+---------+---------+---------|
                                               XXXXXXX,  _______,  XXXXXXX,     XXXXXXX,  XXXXXXX,  _______
                                          //`-----------------------------'  `-----------------------------'
  ),

  // Delimiters
  [l_del] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------------.                      ,-----------------------------------------------------------.
       XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,                         KC_PERC,  KC_QUOT,  KC_DQUO,   KC_GRV,  KC_BSLS,  XXXXXXX,
  //|---------+---------+---------+---------+---------+---------|                      |---------+---------+---------+---------+---------+---------|
       XXXXXXX,  XXXXXXX,  XXXXXXX,    TO(0),  XXXXXXX,  XXXXXXX,                       TD(D_ABK),TD(D_PRN),TD(D_CBR),TD(D_BRC),  XXXXXXX,  XXXXXXX,
  //|---------+---------+---------+---------+---------+---------|                      |---------+---------+---------+---------+---------+---------|
       XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,                         KC_ASTR,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
  //|---------+---------+---------+---------+---------+---------+---------|  |---------+---------+---------+---------+---------+---------+---------|
                                               XXXXXXX,  _______,  XXXXXXX,     XXXXXXX,  XXXXXXX,  _______
                                          //`-----------------------------'  `-----------------------------'
  ),

  // Numpad (figures)
  [l_fig] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------------.                      ,-----------------------------------------------------------.
       XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,                          KC_EQL,     KC_7,     KC_8,     KC_9,  XXXXXXX,  XXXXXXX,
  //|---------+---------+---------+---------+---------+---------|                      |---------+---------+---------+---------+---------+---------|
     MO(l_fun),  XXXXXXX,  XXXXXXX,  XXXXXXX,    TO(0),  XXXXXXX,                            KC_0,     KC_4,     KC_5,     KC_6,  XXXXXXX,  XXXXXXX,
  //|---------+---------+---------+---------+---------+---------|                      |---------+---------+---------+---------+---------+---------|
       XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,                         KC_MINS,     KC_1,     KC_2,     KC_3,  XXXXXXX,  XXXXXXX,
  //|---------+---------+---------+---------+---------+---------+---------|  |---------+---------+---------+---------+---------+---------+---------|
                                               XXXXXXX,  _______,  XXXXXXX,     XXXXXXX,  XXXXXXX,  _______
                                          //`-----------------------------'  `-----------------------------'
  ),

  // FN keys
  [l_fun] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------------.                      ,-----------------------------------------------------------.
       XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,                         XXXXXXX,    KC_F7,    KC_F8,    KC_F9,   KC_F12,  XXXXXXX,
  //|---------+---------+---------+---------+---------+---------|                      |---------+---------+---------+---------+---------+---------|
       _______,  XXXXXXX,  XXXXXXX,  XXXXXXX,    TO(0),  XXXXXXX,                         XXXXXXX,    KC_F4,    KC_F5,    KC_F6,   KC_F11,  XXXXXXX,
  //|---------+---------+---------+---------+---------+---------|                      |---------+---------+---------+---------+---------+---------|
       XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,                         XXXXXXX,    KC_F1,    KC_F2,    KC_F3,   KC_F10,  XXXXXXX,
  //|---------+---------+---------+---------+---------+---------+---------|  |---------+---------+---------+---------+---------+---------+---------|
                                               XXXXXXX,  _______,  XXXXXXX,     XXXXXXX,  XXXXXXX,  _______
                                          //`-----------------------------'  `-----------------------------'
  ),

  // Navigation layer
  [l_nav] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------------.                      ,-----------------------------------------------------------.
       XXXXXXX,  XXXXXXX,  XXXXXXX,  C_S_TAB,  CTL_TAB,  XXXXXXX,                         XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
  //|---------+---------+---------+---------+---------+---------|                      |---------+---------+---------+---------+---------+---------|
       XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,                         XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,    TO(0),  XXXXXXX,
  //|---------+---------+---------+---------+---------+---------|                      |---------+---------+---------+---------+---------+---------|
       XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,                         XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
  //|---------+---------+---------+---------+---------+---------+---------|  |---------+---------+---------+---------+---------+---------+---------|
                                               XXXXXXX,  XXXXXXX,  XXXXXXX,     XXXXXXX,  _______,  _______
                                          //`-----------------------------'  `-----------------------------'
  ),

  // Board control layer
  [l_ctl] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------------.                      ,-----------------------------------------------------------.
       QK_BOOT,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,                         XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
  //|---------+---------+---------+---------+---------+---------|                      |---------+---------+---------+---------+---------+---------|
       RGB_TOG,  RGB_HUI,  RGB_SAI,  RGB_VAI,  RGB_SPI,  XXXXXXX,                         XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,    TO(0),
  //|---------+---------+---------+---------+---------+---------|                      |---------+---------+---------+---------+---------+---------|
       RGB_MOD,  RGB_HUD,  RGB_SAD,  RGB_VAD,  RGB_SPD,  XXXXXXX,                         XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
  //|---------+---------+---------+---------+---------+---------+---------|  |---------+---------+---------+---------+---------+---------+---------|
                                               XXXXXXX,  XXXXXXX,  XXXXXXX,      KC_ENT,  _______,  _______
                                          //`-----------------------------'  `-----------------------------'
  ),
};

#ifdef OLED_ENABLE
void render_layer_status(void) {
  oled_write_P(PSTR("Layer: "), false);

  switch (get_highest_layer(layer_state)) {
    case l_qwt:
      oled_write_ln_P(PSTR("qwerty"), false);
      break;
    case l_ls1:
      oled_write_ln_P(PSTR("left shortcuts"), false);
      break;
    case l_rs1:
      oled_write_ln_P(PSTR("right shortcuts"), false);
      break;
    case l_ls2:
      oled_write_ln_P(PSTR("left shortcuts+"), false);
      break;
    case l_arw:
      oled_write_ln_P(PSTR("mouse/arrows"), false);
      break;
    case l_sym:
      oled_write_ln_P(PSTR("symbols"), false);
      break;
    case l_del:
      oled_write_ln_P(PSTR("delimiters"), false);
      break;
    case l_fig:
      oled_write_ln_P(PSTR("numpad"), false);
      break;
    case l_fun:
      oled_write_ln_P(PSTR("function keys"), false);
      break;
    case l_nav:
      oled_write_ln_P(PSTR("navigation"), false);
      break;
    case l_ctl:
      oled_write_ln_P(PSTR("board control"), false);
      break;
    default:
      oled_write_ln_P(PSTR("Undefined"), false);
  }
}

bool oled_task_user(void) {
  render_layer_status();
  return false;
}
#endif
