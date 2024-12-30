/* Copyright 2024 @ Keychron (https://www.keychron.com)
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
#include "keychron_common.h"
#include "layout.h"

enum custom_keycodes {
    CUSTOM_LEADER = SAFE_RANGE,
    C_ATAB, // for alt tab on left space layer
    C_CTAB, // for ctrl tab on fn layer
};

enum layers {
    WIN_BASE,
    WIN_FN,
    SYMBOLS_L,
    SYMBOLS_R,
    NUMPAD,
    FUNCTION,
    NAV,

};
// Vim in qmk
// https://github.com/andrewjrae/qmk-vim?tab=readme-ov-file#visual-mode

// Custom one shot layer
// https://github.com/rafaelromao/keyboards/blob/4b23eb99b35c7570394d739dd0fdf6749fd29ed1/src/qmk/users/rafaelromao/features/custom_oneshot.c#L155

// COMBOS
const uint16_t PROGMEM df_combo[]   = {KC_D, KC_F, COMBO_END}; // DF for ESC
const uint16_t PROGMEM nav_combo[]  = {KC_S, KC_F, COMBO_END}; // SF for [NAV]
const uint16_t PROGMEM num_combo[]  = {KC_A, KC_D, COMBO_END}; // AD for [NUMPAD]
const uint16_t PROGMEM f_combo[]    = {KC_F, KC_K, COMBO_END}; // FK for [FUNCTION]
combo_t                key_combos[] = {
    COMBO(df_combo, KC_ESC), COMBO(nav_combo, TT(NAV)), COMBO(num_combo, TT(NUMPAD)), COMBO(f_combo, OSL(FUNCTION)),
    // keycodes with modifiers are possible too!
};

void leader_end_user(void) {
    if (leader_sequence_one_key(KC_D)) {
        tap_code(KC_DEL);
    }
    if (leader_sequence_one_key(KC_V)) {
        SEND_STRING(SS_LCTL("v"));
    } else if (leader_sequence_one_key(KC_S)) {
        // Send CTRL-S
        SEND_STRING(SS_LCTL("s"));
    } else if (leader_sequence_one_key(KC_X)) {
        // Send CTRL-X
        SEND_STRING(SS_LCTL("x"));
    } else if (leader_sequence_one_key(KC_R)) {
        // Send CTRL-R
        layer_on(WIN_BASE); // XXX does not work
    } else if (leader_sequence_one_key(KC_A)) {
        // Send CTRL-A
        SEND_STRING(SS_LCTL("a"));
    } else if (leader_sequence_two_keys(KC_A, KC_C)) {
        // Send CTRL-A CTRL-C
        SEND_STRING(SS_LCTL("ac"));
    } else if (leader_sequence_two_keys(KC_A, KC_X)) {
        // Send CTRL-A CTRL-X
        SEND_STRING(SS_LCTL("ax"));
    } else if (leader_sequence_three_keys(KC_D, KC_F, KC_M)) {
        tap_code16(QK_BOOT);
    }
}

// TAP DANCE
enum {
    // TD_ESC_CAPS = 0,
    TD_RALT_PLUS_MINUS, // XXX imperfect
};

// Tap Dance Definitions
tap_dance_action_t tap_dance_actions[] = {
    // Tap once for Esc, twice for Caps Lock
    // [TD_ESC_CAPS]        = ACTION_TAP_DANCE_DOUBLE(KC_ESC, KC_CAPS),
    [TD_RALT_PLUS_MINUS] = ACTION_TAP_DANCE_DOUBLE(KC_PLUS, KC_MINS)};

/* ideas
TODO:
Perhaps #define LEADER_KEY_STRICT_KEY_PROCESSING might allow us to use QK_LEAD in LT and MO
switch enter and leader
ins
del?
ctrl-larrow
ctrr-rarrow
nav keys
Supply
Caps lock + ' combo => escape
=====================
Free keys:
Win tap
ctrl+win combo (tap and/or hold)
Demand
=====================

Temp:
4 ways to input esc now: esc, df combo, caps lock tap, grave tap

*/
// Documentation

// Backspace on leftspace + I
// Enter: right alt
// Combo S F: Toggle NAV layer
// Combo D F: Esc
// Combo A D for NUMPAD
// Combo F K for function keys
// Left space and then (shift) right space for alt (shift) tab
// Left space and then (shift) right alt for ctrl tab

// ( left shift (or left space + L and left space + ;)
// { right space + left shift
// [ left space + left shift

// + Left space + p
// - Left space + m
// = Left space + e (or left space enter)

// Leftspace+caps: Tap for back space, hold for numlock
/// XXX no. clean up we have also a backspace on leftspace + ;
/// XXX no. and a numpad on A D combo
/// use for something better

// Left Space: Tap for Space, Hold Symbol layer, Hold + right space for alt + tab
// #define lt_lspc LT(SYMBOLS_L, C_LSPC)

// Right Space: Tap for Leader (we use F13), Hold for symbol layer
// #define lt_rspc MO(SYMBOLS_R)
// #define lt_rspc LT(SYMBOLS_R, KC_Q)
#define lt_rspc LT(SYMBOLS_R, CUSTOM_LEADER)

// Right Alt: Tap for +, Double tap for -
#define td_ralt TD(TD_RALT_PLUS_MINUS) // Not used. Just an example

// Tab: Tap for esc, Double tap for caps lock, hold for nav
// #define td_esc_caps TD(TD_ESC_CAPS)

// Fn: Hold for Win Fn layer // XXX Do more
#define mo_wn_fn MO(WIN_FN)

// Fn Caps: Caps word toggle

// Left SPC + /: end
// Right SPC + Z: home
// Left SPC + Z: pgup
// Right SPC + /: pgdn

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [WIN_BASE] = LAYOUT_ansi_89(
        KC_MUTE,    KC_ESC,            KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,     KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   KC_INS,             KC_DEL,
        TT(NUMPAD),       KC_GRAVE,             KC_1,     KC_2,     KC_3,     KC_4,     KC_5,      KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,            KC_PGUP,
        MC_2,       KC_TAB,             KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,      KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,  KC_BSLS,            KC_PGDN,
        CUSTOM_LEADER,       MT(MOD_LCTL, KC_CAPS),        KC_A,     KC_S,     KC_D,     KC_F,     KC_G,      KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,            KC_ENT,             KC_HOME,
        KC_F13,       SC_LSPO,            KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,      KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  SC_RSPC,  KC_UP,
        QK_LEAD,    KC_LCTL,  KC_LWIN,            KC_LALT,  LT(SYMBOLS_L, KC_SPC),  mo_wn_fn,            LT(SYMBOLS_R, KC_ENTER),            MT(MOD_RCTL, CUSTOM_LEADER),  KC_LEFT,  KC_DOWN,  KC_RGHT),

    [WIN_FN] = LAYOUT_ansi_89(
        RGB_TOG,    _______,  KC_BRID,  KC_BRIU,  KC_TASK,  KC_FILE,  _______,   _______,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,  KC_VOLD,   KC_VOLU,  _______,            _______,
        QK_BOOT,    _______,  BT_HST1,  BT_HST2,  BT_HST3,  P2P4G,    _______,   _______,  _______,  _______,  _______,  _______,  _______,   _______,  _______,            _______,
        _______,    _______,  _______,  _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______,  _______,  _______,   _______,  _______,            _______,
        _______,    CW_TOGG,  _______, _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______,  _______,  _______,             _______,            KC_END,
        _______,    _______,            _______,  _______,  _______,  _______,   BAT_LVL,  BAT_LVL,  NK_TOGG,  _______,  _______,  _______,   _______,  _______,  _______,
        _______,    _______,  _______,            _______,  _______,  _______,                       _______,            _______,                       _______,  _______,  _______),

    [SYMBOLS_L] = LAYOUT_ansi_89(
        _______,    _______,   _______,    _______,    _______,    _______,    _______,     _______,    _______,    _______,    _______,    _______,   _______,   _______,   _______,             _______,
        _______,    _______,   _______,     _______,     _______,     _______,     _______,      _______,     _______,     _______,     _______,     _______,     _______,  _______,   _______,            _______,
        _______,    _______,   _______,     _______,     _______,     _______,     _______,      _______,     _______,     KC_BSPC,     _______,     KC_PLUS,  _______,  _______,  _______,            _______,
        _______,    LT(NUMPAD,KC_BSPC),  KC_EXLM,  KC_AT,    KC_HASH,  KC_DLR,   KC_PERC,   KC_CIRC,  KC_AMPR,  KC_ASTR,  KC_LPRN,  KC_RPRN,  KC_UNDS,            KC_EQL,             _______,
        _______,    MT(MOD_LSFT, KC_LBRC),        KC_PGUP,  _______,     _______,     _______,      _______,     _______,     _______,     KC_MINS,  _______,  _______,   KC_END,   KC_RCBR,  _______,
        _______,    _______,  _______,            _______,  _______,  _______,                     C_ATAB,             C_CTAB,                      _______,  _______,  _______),


     [SYMBOLS_R] = LAYOUT_ansi_89(
        _______,    _______,   _______,    _______,    _______,    _______,    _______,     _______,    _______,    _______,    _______,    _______,   _______,   _______,   _______,             _______,
        _______,    _______,   _______,     _______,     _______,     _______,     _______,      _______,     _______,     _______,     _______,     _______,     _______,  _______,   _______,            _______,
        _______,    _______,   _______,     _______,     KC_EQL,     _______,     _______,      _______,     _______,     _______,     _______,     _______,  _______,  _______,  _______,            _______,
        MC_3,       KC_TILD,  KC_EXLM,  KC_AT,    KC_HASH,  KC_DLR,   KC_PERC,   KC_CIRC,  KC_AMPR,  KC_ASTR,  KC_LPRN,  KC_RPRN,  KC_UNDS,            KC_EQL,           _______,
        _______,    KC_LCBR,            KC_HOME,  _______,     _______,     _______,      _______,     _______,     _______,     _______,  _______,  _______,   KC_PGDN,  KC_RBRC,  _______,
        _______,    _______,  _______,            _______,  _______,  _______,                     _______,             _______,                      _______,  _______,  _______),

    [NUMPAD] = LAYOUT_ansi_89(
        _______,    _______,  _______,    _______,    _______,    _______,    _______,     _______,    _______,    _______,    _______,    _______,   _______,   _______,   _______,            _______,
        _______,    _______,  _______,  _______,  _______,  _______, _______,   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,
        _______,    _______,  _______,  _______,  _______,  _______, _______,   KC_SLASH,  KC_7,  KC_8, KC_9,  KC_MINS,  _______,  _______,  _______,            _______,
        _______,    _______,  _______, _______,  _______,  _______,  _______,   KC_ASTR,  KC_4,  KC_5,  KC_6,  KC_PLUS,  KC_ENTER,            _______,            _______,
        _______,    _______,  _______,  _______,  _______,  _______, _______,  _______, _______,  KC_1,  KC_2,  KC_3,  KC_DOT,  KC_ENTER,  _______,
        _______,    _______,  _______,            _______,  _______,  _______,                       _______,            _______,                      _______,  _______,  _______),
    

    [FUNCTION] = LAYOUT_ansi_89(
        __VOL__,    __ESC__,  __F1___,  __F2___,  __F3___,  __F4___,  __F5___,  __F6___,               __F7___,  __F8___,  __F9___,  __F10__,  __F11__,  __F12__,  __INS_,            __DEL__,

        __M1___,    __TILD_,  ___1___,  ___2___,  ___3___,  ___4___,  ___5___,  ___6___,               ___7___,  ___8___,  ___9___,  ___0___,  __MINS_,  __EQL__,  __BSPC__________,  __PGUP_, 
        __M2___,    __TAB__,  ___Q___,  ___W___,  ___E___,  ___R___,  ___T___,               ___Y___,  ___U___,  ___I___,  ___O___,  ___P___,  __LABR_,  __RABR_,  __BSLS__________,  __PGDN_,
        __M3___,    __CAPS_,  KC_F1,  KC_F2,    KC_F3,    KC_F4,    KC_F5,                 KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,            __HOME_,
        __M4___,    __LSFT_,  ___Z___,  ___X___,  ___C___,  ___V___,  ___B___,     ___B___,  ___N___,  ___M___,  __COMM_,  __DOT__,  __SLSH_,  __RSFT_,           __UP___,  
        __M5___,    __LCTL_,  __LGUI_,  __LALT_,  __LSPC___________,  __LFN__,               __RSPC___________,  __RALT_,                               __LEFT_,  __DOWN_,  __RGHT_),

    [NAV] = LAYOUT_ansi_89(
        __VOL__,    __ESC__,  __F1___,  __F2___,  __F3___,  __F4___,  __F5___,  __F6___,               __F7___,  __F8___,  __F9___,  __F10__,  __F11__,  __F12__,  __INS_,            __DEL__,

        __M1___,    __TILD_,  ___1___,  ___2___,  ___3___,  ___4___,  ___5___,  ___6___,               ___7___,  ___8___,  ___9___,  ___0___,  __MINS_,  __EQL__,  __BSPC__________,  __PGUP_, 
        __M2___,    __TAB__,  ___Q___,  LCTL(KC_RGHT),  ___E___,  ___R___,  ___T___,               LCTL(KC_INS),  ___U___,  ___I___,  ___O___,  LSFT(KC_INS),  __LABR_,  __RABR_,  __BSLS__________,  __PGDN_,
        __M3___,    __CAPS_,  ___A___,  ___S___,  ___D___,  ___F___,  ___G___,               KC_LEFT,  KC_DOWN,  KC_UP,    KC_RIGHT, __SCLN_,  __QUOT_,  __ENTER_________,            __HOME_,
        __M4___,    __LSFT_,  ___Z___,  ___X___,  ___C___,  ___V___,  LCTL(KC_LEFT),     ___B___,  ___N___,  ___M___,  __COMM_,  __DOT__,  __SLSH_,  __RSFT_,           __UP___,  
        __M5___,    __LCTL_,  __LGUI_,  __LALT_,  __LSPC___________,  __LFN__,               __RSPC___________,  __RALT_,                               __LEFT_,  __DOWN_,  __RGHT_),
};

// TIMINGS
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        default:
            return TAPPING_TERM;
    }
}

bool get_permissive_hold(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        default:
            // Do not select the hold action when another key is tapped.
            return false;
    }
}

uint16_t get_quick_tap_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        // case SFT_T(KC_SPC):
        //     return QUICK_TAP_TERM - 20;
        default:
            return QUICK_TAP_TERM;
    }
}
    
#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [WIN_BASE] = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [WIN_FN] = {ENCODER_CCW_CW(RGB_VAD, RGB_VAI)},
    [SYMBOLS_L] = {ENCODER_CCW_CW(KC_LEFT, KC_RGHT)},
    [SYMBOLS_R] = {ENCODER_CCW_CW(KC_LEFT, KC_RGHT)},
    [NUMPAD] = {ENCODER_CCW_CW(KC_DOWN, KC_UP)},
    [NAV] = {ENCODER_CCW_CW(KC_DOWN, KC_UP)}
};
#endif // ENCODER_MAP_ENABLE

// clang-format on
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    static bool is_alt_active  = false; // Track if Alt is activA
    static bool is_ctrl_active = false;
    switch (keycode) {
        case MT(MOD_RCTL, CUSTOM_LEADER):
            if (record->event.pressed) {
                if (record->tap.count == 1) {
                    // Tap: Start leader key functionality
                    leader_start();
                    return false;
                };
            }
            return true; // Further MT() processing
        case LT(SYMBOLS_L, KC_SPC):
            if (!record->event.pressed) { // Release
                if (is_alt_active) {
                    unregister_code(KC_LALT); // Release Alt if active
                    is_alt_active = false;    // Alt is no longer active
                }
                if (is_ctrl_active) {
                    unregister_code(KC_LCTL); // Release Ctrl if active
                    is_ctrl_active = false;   // Ctrl is no longer active
                }
            }
            return true; // Further LT() processing
        case C_ATAB:     // Handle Right Space key on SYMBOLS_L layer
            if (record->event.pressed) {
                if (!is_alt_active) {
                    register_code(KC_LALT); // Hold Alt if not active
                    is_alt_active = true;
                }
                tap_code(KC_TAB); // Send Tab
            }
            return false; // Skip further processing for CUSTOM_RIGHT_SPC
        case C_CTAB:
            if (record->event.pressed) {
                if (!is_ctrl_active) {
                    register_code(KC_LCTL); // Hold Ctrl if not active
                    is_ctrl_active = true;
                }
                tap_code(KC_TAB); // Send Tab
            }
            return false; // Skip further
        case MO(WIN_FN):
            if (!record->event.pressed) { // Release
                if (is_ctrl_active) {
                    unregister_code(KC_LCTL); // Release Alt if active
                    is_ctrl_active = false;   // Alt is no longer active
                }
            }
            return true; // Process MO()
    }
    // Common key processing
    if (!process_record_keychron_common(keycode, record)) {
        return false;
    }
    return true;
}
