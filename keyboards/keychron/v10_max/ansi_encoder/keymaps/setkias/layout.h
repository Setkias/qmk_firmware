#define __VOL__ KC_TRNS
#define __LSPC___________ KC_TRNS
#define __RSPC___________ KC_TRNS

#define __M1___ KC_TRNS
#define __M2___ KC_TRNS
#define __M3___ KC_TRNS
#define __M4___ KC_TRNS
#define __M5___ KC_TRNS

#define __ESC__ KC_TRNS
#define __TAB__ KC_TRNS
#define __CAPS_ KC_TRNS
#define __LCTL_ KC_TRNS
#define __LALT_ KC_TRNS
#define __LGUI_ KC_TRNS
#define __RCTL_ KC_TRNS
#define __RALT_ KC_TRNS
#define __RGUI_ KC_TRNS

#define __LSFT_ KC_TRNS
#define __RSFT_ KC_TRNS
#define __LFN__ KC_TRNS

#define __LEFT_ KC_TRNS
#define __DOWN_ KC_TRNS
#define __UP___ KC_TRNS
#define __RGHT_ KC_TRNS

#define __DEL__ KC_TRNS
#define __BSPC__________ KC_TRNS
#define __ENTER_________ KC_TRNS
#define __PGUP_ KC_TRNS
#define __PGDN_ KC_TRNS
#define __HOME_ KC_TRNS
#define __INS_ KC_TRNS

#define __F1___ KC_TRNS
#define __F2___ KC_TRNS
#define __F3___ KC_TRNS
#define __F4___ KC_TRNS
#define __F5___ KC_TRNS
#define __F6___ KC_TRNS
#define __F7___ KC_TRNS
#define __F8___ KC_TRNS
#define __F9___ KC_TRNS
#define __F10__ KC_TRNS
#define __F11__ KC_TRNS
#define __F12__ KC_TRNS

#define ___A___ KC_TRNS
#define ___B___ KC_TRNS
#define ___C___ KC_TRNS
#define ___D___ KC_TRNS
#define ___E___ KC_TRNS
#define ___F___ KC_TRNS
#define ___G___ KC_TRNS
#define ___H___ KC_TRNS
#define ___I___ KC_TRNS
#define ___J___ KC_TRNS
#define ___K___ KC_TRNS
#define ___L___ KC_TRNS
#define ___M___ KC_TRNS
#define ___N___ KC_TRNS
#define ___O___ KC_TRNS
#define ___P___ KC_TRNS
#define ___Q___ KC_TRNS
#define ___R___ KC_TRNS
#define ___S___ KC_TRNS
#define ___T___ KC_TRNS
#define ___U___ KC_TRNS
#define ___V___ KC_TRNS
#define ___W___ KC_TRNS
#define ___X___ KC_TRNS
#define ___Y___ KC_TRNS
#define ___Z___ KC_TRNS

#define ___0___ KC_TRNS
#define ___1___ KC_TRNS
#define ___2___ KC_TRNS
#define ___3___ KC_TRNS
#define ___4___ KC_TRNS
#define ___5___ KC_TRNS
#define ___6___ KC_TRNS
#define ___7___ KC_TRNS
#define ___8___ KC_TRNS
#define ___9___ KC_TRNS

#define __TILD_ KC_TRNS
#define __MINS_ KC_TRNS
#define __EQL__ KC_TRNS
#define __LCBR_ KC_TRNS          // {}
#define __RCBR_ KC_TRNS          // {}
#define __LABR_ KC_TRNS          // []
#define __RABR_ KC_TRNS          // []
#define __BSLS__________ KC_TRNS // backslash
#define __SLSH_ KC_TRNS          // /
#define __QUOT_ KC_TRNS          // '
#define __SCLN_ KC_TRNS          // ;
#define __DOT__ KC_TRNS          // .
#define __COMM_ KC_TRNS          // ,

// clang-format off
const uint16_t /*PROGMEM*/ ex[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_ansi_89(
        __VOL__,    __ESC__,  __F1___,  __F2___,  __F3___,  __F4___,  __F5___,  __F6___,               __F7___,  __F8___,  __F9___,  __F10__,  __F11__,  __F12__,  __INS_,            __DEL__,

        __M1___,    __TILD_,  ___1___,  ___2___,  ___3___,  ___4___,  ___5___,  ___6___,               ___7___,  ___8___,  ___9___,  ___0___,  __MINS_,  __EQL__,  __BSPC__________,  __PGUP_, 
        __M2___,    __TAB__,  ___Q___,  ___W___,  ___E___,  ___R___,  ___T___,               ___Y___,  ___U___,  ___I___,  ___O___,  ___P___,  __LABR_,  __RABR_,  __BSLS__________,  __PGDN_,
        __M3___,    __CAPS_,  ___A___,  ___S___,  ___D___,  ___F___,  ___G___,               ___H___,  ___J___,  ___K___,  ___L___,  __SCLN_,  __QUOT_,  __ENTER_________,            __HOME_,
        __M4___,    __LSFT_,  ___Z___,  ___X___,  ___C___,  ___V___,  ___B___,     ___B___,  ___N___,  ___M___,  __COMM_,  __DOT__,  __SLSH_,  __RSFT_,           __UP___,  
        __M5___,    __LCTL_,  __LGUI_,  __LALT_,  __LSPC___________,  __LFN__,               __RSPC___________,  __RALT_,                               __LEFT_,  __DOWN_,  __RGHT_),
};

// An arr