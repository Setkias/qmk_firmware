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

// Custom one shot layer
// https://github.com/rafaelromao/keyboards/blob/4b23eb99b35c7570394d739dd0fdf6749fd29ed1/src/qmk/users/rafaelromao/features/custom_oneshot.c#L155

// COMBOS
const uint16_t PROGMEM df_combo[]    = {KC_D, KC_F, COMBO_END};
const uint16_t PROGMEM test_combo2[] = {KC_C, KC_D, COMBO_END};
combo_t                key_combos[]  = {
    COMBO(df_combo, KC_ESC), COMBO(test_combo2, LCTL(KC_Z)), // keycodes with modifiers are possible too!
};

void leader_end_user(void) {
    if (leader_sequence_three_keys(KC_D, KC_F, KC_M)) {
        tap_code16(QK_BOOT);
    }
}

// TAP DANCE
enum {
    TD_ESC_CAPS = 0,
    TD_RALT_PLUS_MINUS,
};

// Tap Dance Definitions
tap_dance_action_t tap_dance_actions[] = {
    // Tap once for Esc, twice for Caps Lock
    [TD_ESC_CAPS]        = ACTION_TAP_DANCE_DOUBLE(KC_ESC, KC_CAPS),
    [TD_RALT_PLUS_MINUS] = ACTION_TAP_DANCE_DOUBLE(KC_PLUS, KC_MINS)};

enum layers {
    WIN_BASE,
    WIN_FN,
    SYMBOLS_L,
    SYMBOLS_R,
    NUMPAD,
};

/* ideas
TODO:
ctrl-tab
ctrl+shift+tab
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

/* left shift:
- tap for (,
- right spc hold + left shift tap for {,
- left space hold + left shift tap for [,
- hold for regular shift
*/

/* right shift:
- tap for ),
- left spc hold + right shift tap for }
- right space hold + right shift tap for ]
- hold for regular shift
*/

enum custom_keycodes {
    CUSTOM_LEADER = SAFE_RANGE,
    C_LSPC,
    C_RSPC,
};

// Grave: Tap for Esc, Shift tap for `, win tap for ~
#define qk_gesc QK_GESC

// Left Space: Tap for Space, Hold Symbol layer, Hold + right space for alt + tab
#define lt_lspc LT(SYMBOLS_L, C_LSPC)

// Right Space: Tap for Leader (we use F13), Hold for symbol layer
// #define lt_rspc MO(SYMBOLS_R)
// #define lt_rspc LT(SYMBOLS_R, KC_Q)
#define lt_rspc LT(SYMBOLS_R, CUSTOM_LEADER)

// Right Alt: Tap for +, Double tap for -
#define td_ralt TD(TD_RALT_PLUS_MINUS)

// Tab: Tap for esc, Double tap for caps lock, hold for nav
#define td_esc_caps TD(TD_ESC_CAPS)

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
        MC_1,       qk_gesc,             KC_1,     KC_2,     KC_3,     KC_4,     KC_5,      KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,            KC_PGUP,
        MC_2,       KC_TAB,             KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,      KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,  KC_BSLS,            KC_PGDN,
        CUSTOM_LEADER,       td_esc_caps,        KC_A,     KC_S,     KC_D,     KC_F,     KC_G,      KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,            KC_ENT,             KC_HOME,
        KC_F13,       SC_LSPO,            KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,      KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  SC_RSPC,  KC_UP,
        QK_LEAD,    KC_LCTL,  KC_LWIN,            KC_LALT,  lt_lspc,  mo_wn_fn,            lt_rspc,            td_ralt,  KC_LEFT,  KC_DOWN,  KC_RGHT),

    [WIN_FN] = LAYOUT_ansi_89(
        RGB_TOG,    _______,  KC_BRID,  KC_BRIU,  KC_TASK,  KC_FILE,  _______,   _______,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,  KC_VOLD,   KC_VOLU,  _______,            _______,
        QK_BOOT,    _______,  BT_HST1,  BT_HST2,  BT_HST3,  P2P4G,    _______,   _______,  _______,  _______,  _______,  _______,  _______,   _______,  _______,            _______,
        _______,    _______,  _______,  _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______,  _______,  _______,   _______,  _______,            _______,
        _______,    CW_TOGG,  _______, _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______,  _______,  _______,             _______,            KC_END,
        _______,    _______,            _______,  _______,  _______,  _______,   BAT_LVL,  BAT_LVL,  NK_TOGG,  _______,  _______,  _______,   _______,  _______,  _______,
        _______,    _______,  _______,            _______,  _______,  _______,                       _______,            _______,                       _______,  _______,  _______),
    // [WIN_FN] = LAYOUT_ansi_89(
    //     RGB_TOG,    _______,  KC_BRID,  KC_BRIU,  KC_TASK,  KC_FILE,  RGB_VAD,   RGB_VAI,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,  KC_VOLD,   KC_VOLU,  _______,            _______,
    //     QK_BOOT,    _______,  BT_HST1,  BT_HST2,  BT_HST3,  P2P4G,    _______,   _______,  _______,  _______,  _______,  _______,  _______,   _______,  _______,            _______,
    //     _______,    RGB_TOG,  RGB_MOD,  RGB_VAI,  RGB_HUI,  RGB_SAI,  RGB_SPI,   _______,  _______,  _______,  _______,  _______,  _______,   _______,  _______,            _______,
    //     _______,    CW_TOGG,  RGB_RMOD, RGB_VAD,  RGB_HUD,  RGB_SAD,  RGB_SPD,   _______,  _______,  _______,  _______,  _______,  _______,             _______,            KC_END,
    //     _______,    _______,            _______,  _______,  _______,  _______,   BAT_LVL,  BAT_LVL,  NK_TOGG,  _______,  _______,  _______,   _______,  _______,  _______,
    //     _______,    _______,  _______,            _______,  _______,  _______,                       _______,            _______,                       _______,  _______,  _______),

    [SYMBOLS_L] = LAYOUT_ansi_89(
        _______,    _______,   _______,    _______,    _______,    _______,    _______,     _______,    _______,    _______,    _______,    _______,   _______,   _______,   _______,             _______,
        _______,    _______,   _______,     _______,     _______,     _______,     _______,      _______,     _______,     _______,     _______,     _______,     _______,  _______,   _______,            _______,
        _______,    _______,   _______,     _______,     _______,     _______,     _______,      _______,     _______,     _______,     _______,     _______,  _______,  _______,  _______,            _______,
        _______,    KC_TILD,  KC_EXLM,  KC_AT,    KC_HASH,  KC_DLR,   KC_PERC,   KC_CIRC,  KC_AMPR,  KC_ASTR,  KC_LPRN,  KC_RPRN,  KC_UNDS,            KC_EQL,             _______,
        _______,    MT(MOD_LSFT, KC_LBRC),        KC_PGUP,  _______,     _______,     _______,      _______,     _______,     _______,     _______,  _______,  _______,   KC_END,   KC_RCBR,  _______,
        _______,    _______,  _______,            _______,  _______,  _______,                     C_RSPC,             _______,                      _______,  _______,  _______),



     [SYMBOLS_R] = LAYOUT_ansi_89(
        _______,    _______,   _______,    _______,    _______,    _______,    _______,     _______,    _______,    _______,    _______,    _______,   _______,   _______,   _______,             _______,
        _______,    _______,   _______,     _______,     _______,     _______,     _______,      _______,     _______,     _______,     _______,     _______,     _______,  _______,   _______,            _______,
        _______,    _______,   _______,     _______,     _______,     _______,     _______,      _______,     _______,     _______,     _______,     _______,  _______,  _______,  _______,            _______,
        MC_3,       KC_TILD,  KC_EXLM,  KC_AT,    KC_HASH,  KC_DLR,   KC_PERC,   KC_CIRC,  KC_AMPR,  KC_ASTR,  KC_LPRN,  KC_RPRN,  KC_UNDS,            KC_EQL,           _______,
        _______,    KC_LCBR,            KC_HOME,  _______,     _______,     _______,      _______,     _______,     _______,     _______,  _______,  _______,   KC_END,  KC_RBRC,  _______,
        _______,    _______,  _______,            _______,  _______,  _______,                     _______,             _______,                      _______,  _______,  _______),

    [NUMPAD] = LAYOUT_ansi_89(
        RGB_TOG,    _______,  KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,     KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   _______,            _______,
        _______,    _______,  BT_HST1,  BT_HST2,  BT_HST3,  P2P4G,    _______,   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,
        _______,    RGB_TOG,  RGB_MOD,  RGB_VAI,  RGB_HUI,  RGB_SAI,  RGB_SPI,   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,
        _______,    _______,  RGB_RMOD, RGB_VAD,  RGB_HUD,  RGB_SAD,  RGB_SPD,   _______,  _______,  _______,  _______,  _______,  _______,            _______,            KC_END,
        _______,    _______,            _______,  _______,  _______,  _______,   BAT_LVL,  BAT_LVL,  NK_TOGG,  _______,  _______,  _______,  _______,  _______,  _______,
        _______,    _______,  _______,            _______,  _______,  _______,                       _______,            _______,                      _______,  _______,  _______)
};
    
#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [WIN_BASE] = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [WIN_FN] = {ENCODER_CCW_CW(RGB_VAD, RGB_VAI)},
    [SYMBOLS_L] = {ENCODER_CCW_CW(KC_LEFT, KC_RGHT)},
    [SYMBOLS_R] = {ENCODER_CCW_CW(KC_LEFT, KC_RGHT)},
    [NUMPAD] = {ENCODER_CCW_CW(KC_DOWN, KC_UP)}
};
#endif // ENCODER_MAP_ENABLE

// clang-format on
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    static bool is_alt_active = false; // Track if Alt is activA
    switch (keycode) {
        case LT(SYMBOLS_R, CUSTOM_LEADER):
            if (record->event.pressed) {
                if (record->tap.count == 1) {
                    // Tap: Start leader key functionality
                    leader_start();
                } else {
                    // Hold: Activate SYMBOLS_R layer
                    layer_on(SYMBOLS_R);
                }
            } else {
                // Key released: Deactivate SYMBOLS_R layer
                if (!record->tap.count) {
                    layer_off(SYMBOLS_R);
                }
            }
            return false; // Skip default processing for LT()
        case LT(SYMBOLS_L, C_LSPC):
            if (record->event.pressed) {
                if (record->tap.count == 1) {
                    // Tap: Send Space
                    tap_code(KC_SPC);
                    if (is_caps_word_on()) {
                        // Caps Word is on: Turn it off
                        caps_word_off();
                    }
                } else {
                    // Hold: Activate SYMBOLS_L layer
                    layer_on(SYMBOLS_L);
                }
            } else {
                // Key released: Deactivate SYMBOLS_L layer
                layer_off(SYMBOLS_L);
                if (is_alt_active) {
                    unregister_code(KC_LALT); // Release Alt if active
                    is_alt_active = false;    // Alt is no longer active
                }
            }
            return false; // Skip default processing for LT()
        case C_RSPC:      // Handle Right Space key on SYMBOLS_L layer
            if (record->event.pressed) {
                if (!is_alt_active) {
                    register_code(KC_LALT); // Hold Alt if not active
                    is_alt_active = true;
                }
                tap_code(KC_TAB); // Send Tab

            } else {
                // Do nothing on release; Alt remains active
            }
            return false; // Skip further processing for CUSTOM_RIGHT_SPC
    }
    // Common key processing
    if (!process_record_keychron_common(keycode, record)) {
        return false;
    }
    return true;
}
