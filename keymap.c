#include QMK_KEYBOARD_H

#include "features/achordion.h"
#include "features/layer_lock.h"

#define __NON__ KC_NO

#define MG LGUI_T
#define MA LALT_T
#define MS LSFT_T
#define MC LCTL_T

#define SYM_D LT(SYM, KC_D)
#define SYM_H LT(SYM, KC_H)

#define SPACE LT(NAV, KC_SPC)
#define ENTER LT(NUM, KC_ENT)

enum custom_keycodes {
    LL_LOCK = SAFE_RANGE, // Layer lock key
    DB_COLN,              // Double colon '::' macro
    TUP_DIR,              // Macro '../'
    TIL_DIR,              // Macro '~/'
};

enum layers {
    BASE = 0,
    SYM,
    NUM,
    NAV,
};

// clang-format off

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [BASE] = LAYOUT(
                              KC_W,     KC_F,     KC_P,   KC_B,        KC_J,        KC_L,        KC_U,        KC_Y,     
     KC_TAB,    MG(KC_A), MA(KC_R), MS(KC_S), MC(KC_T),   KC_G,        KC_M,    MC(KC_N),    MS(KC_E),    MA(KC_I),    MG(KC_O), KC_BSPC,    
                    KC_Z,     KC_X,     KC_C,    SYM_D,   KC_V,        KC_K,       SYM_H,     KC_COMM,      KC_DOT,     KC_SLSH,
                                                 ENTER,  SPACE,       SPACE,       ENTER
    ),
    [NAV] = LAYOUT(
                           __NON__,  __NON__,  __NON__, KC_VOLD,     KC_VOLU,    __NON__,     __NON__,     __NON__,   
    _______,     KC_LGUI,  KC_LALT,  KC_LSFT,  KC_LCTL, __NON__,     __NON__,    KC_LEFT,       KC_UP,     KC_RGHT,     CAPSWRD, _______, 
                 C(KC_Z),  C(KC_X),  C(KC_C),  __NON__, C(KC_V),     __NON__,    __NON__,     KC_DOWN,     __NON__,     __NON__,
                                               _______, _______,     _______,    _______    
    ),
    [SYM] =  LAYOUT(
                             KC_AT,  DB_COLN,   KC_GRV, __NON__,     __NON__,    KC_RCBR,     KC_RPRN,     KC_RBRC,    
    _______,     KC_QUES,  KC_BSLS,  KC_COLN,  KC_UNDS, TUP_DIR,     TIL_DIR,    KC_LCBR,     KC_LPRN,     KC_LBRC,     KC_DQUO, _______, 
                 __NON__,  KC_PERC,  KC_PIPE,  KC_AMPR, __NON__,     __NON__,    KC_HASH,      KC_DLR,     KC_TILD,     __NON__,
                                               _______, _______,     _______,    _______
    ), 
    [NUM] = LAYOUT(
                              KC_4,     KC_5,     KC_6, __NON__,     __NON__,    KC_CIRC,     KC_LABK,     KC_RABK, 
    _______,    MG(KC_0), MA(KC_1), MS(KC_2), MC(KC_3),  KC_DOT,     __NON__, MC(KC_EQL), MS(KC_SCLN), MA(KC_MINS), MG(KC_QUOT), _______, 
                 __NON__,     KC_7,     KC_8,     KC_9, __NON__,     __NON__,    KC_PLUS,     KC_EXLM,     KC_ASTR,     KC_SLSH,
                                               _______, _______,     _______,    _______    
    )
};

// clang-format on

const uint16_t PROGMEM lo_left_mid[]  = {KC_X, KC_C, COMBO_END};
const uint16_t PROGMEM lo_right_mid[] = {KC_COMM, KC_DOT, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
    COMBO(lo_left_mid, KC_Q),
    COMBO(lo_right_mid, KC_ESC),
};

// Use bilateral combinations, this requires opposite hands for home row mods.
bool process_record_user(uint16_t keycode, keyrecord_t* record) {
    // Must be first
    if (!process_achordion(keycode, record)) {
        return false;
    }
    if (!process_layer_lock(keycode, record, LL_LOCK)) {
        return false;
    }
    // Macros
    switch (keycode) {
        case DB_COLN:
            if (record->event.pressed) {
                SEND_STRING("::");
            }
            return false;

        case TIL_DIR:
            if (record->event.pressed) {
                SEND_STRING("~/");
            }
            return false;

        case TUP_DIR:
            if (record->event.pressed) {
                SEND_STRING("../");
            }
            return false;

        default:
            return true;
    }
}

bool achordion_chord(uint16_t tap_hold_keycode, keyrecord_t* tap_hold_record, uint16_t other_keycode, keyrecord_t* other_record) {
    if (tap_hold_keycode == SPACE) {
        // Bypass achordian for nav layer, This alows single hand copy/paste amd MOD+click
        return true;
    } else {
        // Otherwise, follow the opposite hands rule.
        return achordion_opposite_hands(tap_hold_record, other_record);
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
