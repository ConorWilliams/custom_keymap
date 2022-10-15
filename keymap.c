#include QMK_KEYBOARD_H

#include "features/achordion.h"
#include "features/layer_lock.h"

#define __NON__ KC_NO

#define LG LGUI_T
#define LA LALT_T
#define   LS LSFT_T
#define LC LCTL_T

#define RG RGUI_T
#define RA RALT_T
#define RS RSFT_T
#define RC RCTL_T


enum custom_keycodes {
  L_LOCK = SAFE_RANGE, // Layer lock key
  D_COLN,              // Double colon '::' macro
};

enum layers {
  BASE = 0,
  SYM,
  NUM,
  NAV,
};

#define LT_ENT LT(NAV, KC_ENT)


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [BASE] = LAYOUT(
                               KC_W,       KC_F,       KC_P,      KC_B,        KC_J,        KC_L,       KC_U,       KC_Y,     
     KC_TAB,   LG(KC_A),   LA(KC_R),   LS(KC_S),   LC(KC_T),      KC_G,        KC_M,    RC(KC_N),   RS(KC_E),   RA(KC_I),   RG(KC_O),   KC_BSPC,    
                   KC_Z,       KC_X,       KC_C,       KC_D,      KC_V,        KC_K,        KC_H,    KC_COMM,     KC_DOT,    KC_SLSH,
                                                    MO(NUM),    LT_ENT,      KC_SPC,     MO(SYM)
    ),
    [SYM] = LAYOUT(
                              KC_AT,     D_COLN,     KC_GRV,    __NON__,     __NON__,    KC_RCBR,    KC_RPRN,    KC_RBRC,    
    _______,    KC_QUES,    KC_BSLS,    KC_COLN,    KC_UNDS,    __NON__,     __NON__,    KC_LCBR,    KC_LPRN,    KC_LBRC,    KC_DQUO, _______, 
                __NON__,    KC_PERC,    KC_PIPE,    KC_AMPR,    __NON__,     __NON__,    KC_HASH,     KC_DLR,    KC_TILD,    _______,
                                                    _______,    _______,     _______,    _______
    ),
    [NUM] = LAYOUT(
                               KC_4,       KC_5,       KC_6,    __NON__,     __NON__,    KC_CIRC,    KC_LABK,    KC_RABK, 
    _______, LG(KC_DOT),   LA(KC_1),   LS(KC_2),   LC(KC_3),    __NON__,     __NON__, RC(KC_EQL),RS(KC_SCLN),RA(KC_MINS),RG(KC_QUOT), _______, 
                __NON__,       KC_7,       KC_8,       KC_9,    __NON__,     __NON__,    KC_PLUS,    KC_EXLM,    KC_ASTR,    _______,
                                                     _______,   _______,     _______,       KC_0
    ),
    [NAV] = LAYOUT(
                            __NON__,    __NON__,    __NON__,    KC_VOLD,     KC_VOLU,    __NON__,    __NON__,    __NON__,   
    _______,    KC_LGUI,    KC_LALT,    KC_LSFT,    KC_LCTL,    __NON__,     __NON__,    KC_LEFT,      KC_UP,    KC_RGHT,    __NON__, __NON__, 
                C(KC_Z),    C(KC_X),    C(KC_C),    C(KC_V),    __NON__,     __NON__,    KC_HOME,    KC_DOWN,     KC_END,    __NON__,
                                                    __NON__,    _______,      L_LOCK,    __NON__    
    )
};

const uint16_t PROGMEM xc_low_left[] = {KC_X, KC_C, COMBO_END};
const uint16_t PROGMEM cd_low_right[] = {KC_COMM, KC_DOT, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
    COMBO(xc_low_left, KC_Q),
    COMBO(cd_low_right, KC_ESC), 
};

// Use bilateral combinations, this requires opposite hands for home row mods.
bool process_record_user(uint16_t keycode, keyrecord_t* record) {
  // Must be first
  if (!process_achordion(keycode, record)) {
     return false; 
  }
  if (!process_layer_lock(keycode, record, L_LOCK)) { 
    return false; 
  }
  // Macros
  switch (keycode) {
    case D_COLN: 
      if (record->event.pressed) {
        SEND_STRING("::");
      }
      return false;

    default:
      return true;
  }
}

// Eagerly apply left: Shift, Ctrl and Alt mods for use with mouse.
bool achordion_eager_mod(uint8_t mod) {
  switch (mod) {
    case MOD_LSFT:
    case MOD_LCTL:
    case MOD_LALT:
      return true;  
    default:
      return false;
  }
}

void matrix_scan_user(void) {
  achordion_task();
  layer_lock_task();
}

