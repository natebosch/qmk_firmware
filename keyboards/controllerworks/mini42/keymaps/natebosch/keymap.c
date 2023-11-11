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

#define ESC_LCTL LCTL_T(KC_ESC)
#define CTL_TAB LCTL(KC_TAB)
#define C_S_TAB LCTL(LSFT(KC_TAB))
#define SFT_ALT LSFT(KC_LALT)

#define l_qwt 0
#define l_ls1 1
#define l_ls2 2
#define l_arw 3
#define l_sym 4
#define l_del 5
#define l_fig 6
#define l_fun 7
#define l_rs1 8
#define l_abr 9
#define l_nav 10
#define l_ctl 11

#define spc_ls1 LT(l_ls1, KC_SPC)
#define ent_rs1 LT(l_rs1, KC_ENT)

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

enum combos {
  L_ARW,
  L_SYM,
  L_DEL,
  L_FIG,
  L_FUN,
  L_ABR,
  L_NAV,
  L_CTL,
  JK_ESC,
  FJ_CAPS,
};

const uint16_t PROGMEM l_arw_combo[] = {CTL_A, spc_ls1, COMBO_END};
const uint16_t PROGMEM l_sym_combo[] = {GUI_S, spc_ls1, COMBO_END};
const uint16_t PROGMEM l_del_combo[] = {ALT_D, spc_ls1, COMBO_END};
const uint16_t PROGMEM l_fig_combo[] = {SFT_F, spc_ls1, COMBO_END};
const uint16_t PROGMEM l_fun_combo[] = {SFT_F, ESC_LCTL, spc_ls1, COMBO_END};
const uint16_t PROGMEM l_abr_combo[] = {GUI_L, ent_rs1, COMBO_END};
const uint16_t PROGMEM l_nav_combo[] = {CTL_SCLN, ent_rs1, COMBO_END};
const uint16_t PROGMEM l_ctl_combo[] = {KC_QUOT, ent_rs1, COMBO_END};
const uint16_t PROGMEM jk_esc_combo[] = {SFT_J, ALT_K, COMBO_END};
const uint16_t PROGMEM fj_caps_combo[] = {SFT_F, SFT_J, COMBO_END};

combo_t key_combos[] = {
  [L_ARW] = COMBO(l_arw_combo, MO(l_arw)),
  [L_SYM] = COMBO(l_sym_combo, MO(l_sym)),
  [L_DEL] = COMBO(l_del_combo, MO(l_del)),
  [L_FIG] = COMBO(l_fig_combo, MO(l_fig)),
  [L_FUN] = COMBO(l_fun_combo, MO(l_fun)),
  [L_ABR] = COMBO(l_abr_combo, MO(l_abr)),
  [L_NAV] = COMBO(l_nav_combo, MO(l_nav)),
  [L_CTL] = COMBO(l_ctl_combo, MO(l_ctl)),
  [JK_ESC] = COMBO(jk_esc_combo, KC_ESC),
  [FJ_CAPS] = COMBO(fj_caps_combo, CW_TOGG),
};

enum custom_keycodes {
  GUI_TAB = SAFE_RANGE,
  A_DARRW,
  A_SARRW,
  A_VIMEX,
  A_VIMWQ,
  K_JIGGL,
};

bool is_gui_tab_active = false;
bool is_mouse_jiggle_active = false;
bool is_caps_word_active = false;
uint16_t gui_tab_timer = 0;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case GUI_TAB:
      if (record->event.pressed) {
        if (!is_gui_tab_active) {
          is_gui_tab_active = true;
          register_code(KC_LGUI);
        }
        gui_tab_timer = timer_read();
        register_code(KC_TAB);
      } else {
        unregister_code(KC_TAB);
      }
      break;
    case A_DARRW:
      if (record->event.pressed) SEND_STRING("=>");
      break;
    case A_SARRW:
      if (record->event.pressed) SEND_STRING("->");
      break;
    case A_VIMEX:
      if (record->event.pressed) SEND_STRING("\e:qa\n");
      break;
    case A_VIMWQ:
      if (record->event.pressed) SEND_STRING("\e:wq\n");
      break;
    case K_JIGGL:
      if (record->event.pressed) {
        is_mouse_jiggle_active = !is_mouse_jiggle_active;
      }
      break;
    default:
      if (is_gui_tab_active && record->event.pressed) {
        is_gui_tab_active = false;
        unregister_code(KC_LGUI);
      }
  }
  return true;
}

void matrix_scan_user(void) {
  if (is_gui_tab_active && timer_elapsed(gui_tab_timer) > 1000) {
    unregister_code(KC_LGUI);
    is_gui_tab_active = false;
  }
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
        KC_TAB,     KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,                            KC_Y,     KC_U,     KC_I,     KC_O,    KC_P,   KC_BSPC,
  //|---------+---------+---------+---------+---------+---------|                      |---------+---------+---------+---------+---------+---------|
      ESC_LCTL,    CTL_A,    GUI_S,    ALT_D,    SFT_F,     KC_G,                            KC_H,    SFT_J,    ALT_K,    GUI_L, CTL_SCLN,  KC_QUOT,
  //|---------+---------+---------+---------+---------+---------|                      |---------+---------+---------+---------+---------+---------|
       KC_LSFT,     KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,                            KC_N,     KC_M,  KC_COMM,   KC_DOT,  KC_SLSH,RSFT_T(KC_ENT),
  //|---------+---------+---------+---------+---------+---------+---------|  |---------+---------+---------+---------+---------+---------+---------|
                                               XXXXXXX,   KC_DEL,  spc_ls1,     ent_rs1,  KC_BSPC,    TO(0)
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
                                               XXXXXXX,  _______,  _______,     _______,  _______,  _______
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
                                               XXXXXXX,  _______,  _______,     _______,  _______,  _______
                                          //`-----------------------------'  `-----------------------------'
  ),

  // Arrows and mouse keys
  [l_arw] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------------.                      ,-----------------------------------------------------------.
       XXXXXXX,  XXXXXXX,  KC_BTN1,  KC_BTN2,  SFT_ALT,  XXXXXXX,                         KC_LEFT,  KC_DOWN,    KC_UP,  KC_RGHT,  XXXXXXX,  XXXXXXX,
  //|---------+---------+---------+---------+---------+---------|                      |---------+---------+---------+---------+---------+---------|
       XXXXXXX,TT(l_arw),  KC_LCTL,  KC_LGUI,  KC_LALT,  KC_LSFT,                         KC_MS_L,  KC_MS_D,  KC_MS_U,  KC_MS_R,   KC_TAB,  XXXXXXX,
  //|---------+---------+---------+---------+---------+---------|                      |---------+---------+---------+---------+---------+---------|
       XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  K_JIGGL,                         KC_WH_L,  KC_WH_U,  KC_WH_D,  KC_WH_R,  XXXXXXX,  XXXXXXX,
  //|---------+---------+---------+---------+---------+---------+---------|  |---------+---------+---------+---------+---------+---------+---------|
                                               XXXXXXX,  _______,  _______,     KC_BTN1,  KC_BTN2,  _______
                                          //`-----------------------------'  `-----------------------------'
  ),

  // Symbols
  [l_sym] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------------.                      ,-----------------------------------------------------------.
       XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  SFT_ALT,  XXXXXXX,                         KC_TILD,  KC_HASH,  KC_ASTR,  KC_PERC,  XXXXXXX,  XXXXXXX,
  //|---------+---------+---------+---------+---------+---------|                      |---------+---------+---------+---------+---------+---------|
       XXXXXXX,  KC_LCTL,TT(l_sym),  KC_LGUI,  KC_LALT,  KC_LSFT,                         KC_CIRC,    KC_AT,  KC_EXLM,   KC_AMPR,  KC_DLR,  XXXXXXX,
  //|---------+---------+---------+---------+---------+---------|                      |---------+---------+---------+---------+---------+---------|
       XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,                         KC_MINS,   KC_EQL,  KC_UNDS,  KC_PLUS,  XXXXXXX,  XXXXXXX,
  //|---------+---------+---------+---------+---------+---------+---------|  |---------+---------+---------+---------+---------+---------+---------|
                                               XXXXXXX,  _______,  _______,     ent_rs1,  KC_BSPC,  _______
                                          //`-----------------------------'  `-----------------------------'
  ),

  // Delimiters
  [l_del] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------------.                      ,-----------------------------------------------------------.
       XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  SFT_ALT,  XXXXXXX,                         KC_PERC,  KC_QUOT,  KC_DQUO,   KC_GRV,  XXXXXXX,  XXXXXXX,
  //|---------+---------+---------+---------+---------+---------|                      |---------+---------+---------+---------+---------+---------|
       XXXXXXX,  KC_LCTL,  KC_LGUI,TT(l_del),  KC_LALT,  KC_LSFT,                       TD(D_ABK),TD(D_PRN),TD(D_CBR),TD(D_BRC),  KC_BSLS,  XXXXXXX,
  //|---------+---------+---------+---------+---------+---------|                      |---------+---------+---------+---------+---------+---------|
       XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,                         KC_ASTR,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
  //|---------+---------+---------+---------+---------+---------+---------|  |---------+---------+---------+---------+---------+---------+---------|
                                               XXXXXXX,  _______,  _______,     _______,  _______,  _______
                                          //`-----------------------------'  `-----------------------------'
  ),

  // Numpad (figures)
  [l_fig] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------------.                      ,-----------------------------------------------------------.
       XXXXXXX,  XXXXXXX,  XXXXXXX,  SFT_ALT,  XXXXXXX,  XXXXXXX,                         KC_PLUS,     KC_7,     KC_8,     KC_9,   KC_EQL,  XXXXXXX,
  //|---------+---------+---------+---------+---------+---------|                      |---------+---------+---------+---------+---------+---------|
     MO(l_fun),  KC_LCTL,  KC_LGUI,  KC_LALT,TT(l_fig),  XXXXXXX,                         KC_ASTR,     KC_4,     KC_5,     KC_6,     KC_0, KC_SLASH,
  //|---------+---------+---------+---------+---------+---------|                      |---------+---------+---------+---------+---------+---------|
       XXXXXXX,  XXXXXXX,  XXXXXXX,  KC_LSFT,  XXXXXXX,  XXXXXXX,                         KC_MINS,     KC_1,     KC_2,     KC_3,   KC_DOT,  XXXXXXX,
  //|---------+---------+---------+---------+---------+---------+---------|  |---------+---------+---------+---------+---------+---------+---------|
                                               XXXXXXX,  _______,  _______,     _______,  _______,  _______
                                          //`-----------------------------'  `-----------------------------'
  ),

  // FN keys
  [l_fun] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------------.                      ,-----------------------------------------------------------.
       XXXXXXX,  XXXXXXX,  XXXXXXX,  SFT_ALT,  XXXXXXX,  XXXXXXX,                         XXXXXXX,    KC_F7,    KC_F8,    KC_F9,   KC_F12,  XXXXXXX,
  //|---------+---------+---------+---------+---------+---------|                      |---------+---------+---------+---------+---------+---------|
       _______,  KC_LCTL,  KC_LGUI,  KC_LALT,TT(l_fun),  XXXXXXX,                         XXXXXXX,    KC_F4,    KC_F5,    KC_F6,   KC_F11,  XXXXXXX,
  //|---------+---------+---------+---------+---------+---------|                      |---------+---------+---------+---------+---------+---------|
       XXXXXXX,  XXXXXXX,  XXXXXXX,  KC_LSFT,  XXXXXXX,  XXXXXXX,                         XXXXXXX,    KC_F1,    KC_F2,    KC_F3,   KC_F10,  XXXXXXX,
  //|---------+---------+---------+---------+---------+---------+---------|  |---------+---------+---------+---------+---------+---------+---------|
                                               XXXXXXX,  _______,  _______,     _______,  _______,  _______
                                          //`-----------------------------'  `-----------------------------'
  ),

  // Right board layer shortucts
  [l_rs1] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------------.                      ,-----------------------------------------------------------.
       XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,                         XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
  //|---------+---------+---------+---------+---------+---------|                      |---------+---------+---------+---------+---------+---------|
       XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,                         XXXXXXX,  XXXXXXX,  XXXXXXX,TT(l_abr),TT(l_nav),TT(l_ctl),
  //|---------+---------+---------+---------+---------+---------|                      |---------+---------+---------+---------+---------+---------|
       XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,                         XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
  //|---------+---------+---------+---------+---------+---------+---------|  |---------+---------+---------+---------+---------+---------+---------|
                                               XXXXXXX,  _______,  KC_BSPC,     _______,  _______,  _______
                                          //`-----------------------------'  `-----------------------------'
  ),

  // Right board layer shortucts
  [l_abr] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------------.                      ,-----------------------------------------------------------.
       XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  A_SARRW,  XXXXXXX,                         XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
  //|---------+---------+---------+---------+---------+---------|                      |---------+---------+---------+---------+---------+---------|
       XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  A_DARRW,  XXXXXXX,                         XXXXXXX,  XXXXXXX,  XXXXXXX,TT(l_abr),  XXXXXXX,  XXXXXXX,
  //|---------+---------+---------+---------+---------+---------|                      |---------+---------+---------+---------+---------+---------|
       XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,                         XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
  //|---------+---------+---------+---------+---------+---------+---------|  |---------+---------+---------+---------+---------+---------+---------|
                                               XXXXXXX,  _______,  _______,     _______,  _______,  _______
                                          //`-----------------------------'  `-----------------------------'
  ),

  // Navigation layer
  [l_nav] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------------.                      ,-----------------------------------------------------------.
       XXXXXXX,  A_VIMEX,  A_VIMWQ,  XXXXXXX,  GUI_TAB,  XXXXXXX,                         XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
  //|---------+---------+---------+---------+---------+---------|                      |---------+---------+---------+---------+---------+---------|
       XXXXXXX,MEH(KC_H),MEH(KC_L),  C_S_TAB,  CTL_TAB,MEH(KC_F),                         KC_LEFT,  KC_DOWN,    KC_UP,  KC_RGHT,TT(l_nav),  XXXXXXX,
  //|---------+---------+---------+---------+---------+---------|                      |---------+---------+---------+---------+---------+---------|
       XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,MEH(KC_T),                         XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
  //|---------+---------+---------+---------+---------+---------+---------|  |---------+---------+---------+---------+---------+---------+---------|
                                               XXXXXXX,  _______,  _______,     _______,  _______,  _______
                                          //`-----------------------------'  `-----------------------------'
  ),

  // Board control layer
  [l_ctl] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------------.                      ,-----------------------------------------------------------.
       QK_BOOT,  XXXXXXX,  DT_DOWN,    DT_UP,  XXXXXXX,  XXXXXXX,                         QK_BOOT,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
  //|---------+---------+---------+---------+---------+---------|                      |---------+---------+---------+---------+---------+---------|
       RGB_TOG,  RGB_HUI,  RGB_SAI,  RGB_VAI,  RGB_SPI,  XXXXXXX,                         XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,TT(l_ctl),
  //|---------+---------+---------+---------+---------+---------|                      |---------+---------+---------+---------+---------+---------|
       RGB_MOD,  RGB_HUD,  RGB_SAD,  RGB_VAD,  RGB_SPD,  XXXXXXX,                         XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
  //|---------+---------+---------+---------+---------+---------+---------|  |---------+---------+---------+---------+---------+---------+---------|
                                               XXXXXXX,  _______,  _______,     _______,  _______,  _______
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
    case l_ls2:
      oled_write_ln_P(PSTR("<- L+"), false);
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
    case l_abr:
      oled_write_ln_P(PSTR("abbrv"), false);
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
  if (is_keyboard_master()) {
    char modifier_str[5] = {
      (modifiers & MOD_MASK_SHIFT) ? 's' : ' ',
      (modifiers & MOD_MASK_ALT) ? 'a' : ' ',
      (modifiers & MOD_MASK_GUI) ? 'g' : ' ',
      (modifiers & MOD_MASK_CTRL) ? 'c' : ' ',
      '\0'
    };
    oled_write_ln(modifier_str, false);
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
      (is_gui_tab_active) ? 'A' : ' ',
      (is_mouse_jiggle_active) ? 'M' : ' ',
      '\0'
    };
    oled_write_ln(feature_str, false);
  } else {
    char modifier_str[5] = {
      (modifiers & MOD_MASK_CTRL) ? 'c' : ' ',
      (modifiers & MOD_MASK_GUI) ? 'g' : ' ',
      (modifiers & MOD_MASK_ALT) ? 'a' : ' ',
      (modifiers & MOD_MASK_SHIFT) ? 's' : ' ',
      '\0'
    };
    oled_write_ln(modifier_str, false);
    oled_write_ln_P(PSTR("     "), false);
  }
}

bool oled_task_user(void) {
  render_layer_status();
  return false;
}
#endif
