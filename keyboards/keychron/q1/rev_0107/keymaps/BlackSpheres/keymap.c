/* Copyright 2021 @ Keychron (https://www.keychron.com)
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
#include "keymap_user.h"
#ifdef RGB_MATRIX_ENABLE
#    include "rgb_matrix_user.h"
#endif

typedef union {
  uint32_t raw;
  struct {
    bool caps_lock_light_tab :1;
    bool caps_lock_light_alphas :1;
    bool fn_layer_transparent_keys_off :1;
    bool fn_layer_color_enable :1;
  };
} user_config_t;

user_config_t user_config;

#ifdef VIA_ENABLE
    #define USER_START USER00
#else
    #define USER_START SAFE_RANGE
#endif

enum custom_keycodes {
    KC_MISSION_CONTROL = USER_START,
    KC_LAUNCHPAD,
    KC_LOPTN,
    KC_ROPTN,
    KC_LCMMD,
    KC_RCMMD,
    KC_TASK_VIEW,
    KC_FILE_EXPLORER,
    KC_LIGHT_TAB_TOGGLE,
    KC_LIGHT_ALPHAS_TOGGLE,
    KC_FN_LAYER_TRANSPARENT_KEYS_TOGGLE,
    KC_FN_LAYER_COLOR_TOGGLE

};


bool is_alt_tab_active = false; // ADD this near the begining of keymap.c
bool is_alt_shift_tab_active = false; // ADD this near the begining of keymap.c
uint16_t alt_tab_timer = 0;     // we will be using them soon.


#define KC_MCTL KC_MISSION_CONTROL
#define KC_LPAD KC_LAUNCHPAD
#define KC_TASK KC_TASK_VIEW
#define KC_FLXP KC_FILE_EXPLORER
#define KC_LTTOG KC_LIGHT_TAB_TOGGLE
#define KC_LATOG KC_LIGHT_ALPHAS_TOGGLE
#define KC_TKTOG KC_FN_LAYER_TRANSPARENT_KEYS_TOGGLE
#define KC_FCTOG KC_FN_LAYER_COLOR_TOGGLE


typedef struct PACKED {
    uint8_t len;
    uint8_t keycode[2];
} key_combination_t;

key_combination_t key_comb_list[2] = {
    {2, {KC_LWIN, KC_TAB}},
    {2, {KC_LWIN, KC_E}}
};

static uint8_t mac_keycode[4] = { KC_LOPT, KC_ROPT, KC_LCMD, KC_RCMD };

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [MAC_BASE] = LAYOUT_all(
        KC_ESC,   KC_BRID,  KC_BRIU,  KC_MCTL,  KC_LPAD,  RGB_VAD,  RGB_VAI,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,  KC_VOLD,   KC_VOLU,  KC_DEL,             KC_MUTE,
        KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,   KC_EQL,   KC_BSPC,            KC_PGUP,
        KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,   KC_RBRC,  KC_BSLS,            KC_PGDN,
        KC_CAPS,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,             KC_ENT,             KC_HOME,
        KC_LSFT,            KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,             KC_RSFT,  KC_UP,
        KC_LCTL,  KC_LOPTN, KC_LCMMD,                               KC_SPC,   KC_VOLD,  KC_VOLU,            KC_RCMMD,MO(MAC_FN), KC_RCTL,  KC_LEFT,  KC_DOWN,  KC_RGHT),

    [MAC_FN] = LAYOUT_all(
        KC_TRNS,  KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,    KC_F12,   KC_TRNS,            RGB_TOG,
        KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,   KC_TRNS,  KC_TRNS,            KC_TRNS,
        RGB_TOG,  RGB_MOD,  RGB_VAI,  RGB_HUI,  RGB_SAI,  RGB_SPI,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,   KC_TRNS,  KC_TRNS,            KC_TRNS,
        KC_TRNS,  RGB_RMOD, RGB_VAD,  RGB_HUD,  RGB_SAD,  RGB_SPD,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,             KC_TRNS,            KC_TRNS,
        KC_TRNS,            KC_LTTOG, KC_LATOG, KC_TKTOG, KC_FCTOG,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,             KC_TRNS,  KC_TRNS,
        KC_TRNS,  KC_TRNS,  KC_TRNS,                                KC_TRNS,  RGB_VAD,  RGB_VAI,            KC_TRNS,  KC_TRNS,   KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS),

    [WIN_BASE] = LAYOUT_all(
        KC_ESC,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,    KC_F12,   KC_DEL,             KC_MEDIA_PLAY_PAUSE,
        KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,   KC_EQL,   KC_BSPC,            KC_INSERT,
        KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,   KC_RBRC,  KC_BSLS,            KC_PGUP,
        KC_CAPS,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,             KC_ENT,             KC_PGDN,
        KC_LSFT,            KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,             KC_RSFT,  KC_UP,
        KC_LCTL,  KC_LGUI,  KC_LALT,                                KC_SPC,   KC_VOLD,  KC_VOLU,            KC_RALT, MO(WIN_FN), KC_RCTL,  KC_LEFT,  KC_DOWN,  KC_RIGHT),

    [WIN_FN] = LAYOUT_all(
        RESET,  KC_BRID,  KC_BRIU,  KC_TASK,  KC_FLXP,  RGB_VAD,  RGB_VAI,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,  KC_VOLD,   KC_VOLU,  KC_TRNS,            RGB_TOG,
        KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,   KC_TRNS,  KC_TRNS,            KC_PSCR,
        RGB_TOG,  RGB_MOD,  RGB_VAI,  RGB_HUI,  RGB_SAI,  RGB_SPI,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,   KC_TRNS,  KC_TRNS,            C(KC_TAB),
        KC_TRNS,  RGB_RMOD, RGB_VAD,  RGB_HUD,  RGB_SAD,  RGB_SPD,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,             KC_TRNS,            C(S(KC_TAB)),
        KC_TRNS,            KC_LTTOG, KC_LATOG, KC_TKTOG, KC_FCTOG,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,             KC_TRNS,  KC_TRNS,
        KC_TRNS,  KC_TRNS,  KC_TRNS,                                RGB_TOG,  RGB_VAD,  RGB_VAI,            KC_TRNS,  KC_TRNS,   KC_TRNS,  KC_MPRV,  KC_TRNS,  KC_MNXT),
};

#if defined(VIA_ENABLE) && defined(ENCODER_ENABLE)
bool encoder_update_user(uint8_t index, bool clockwise) {
    if (get_mods() & MOD_BIT(KC_LCTRL)) {
           if (clockwise) {
            if (!is_alt_tab_active) {
                is_alt_tab_active = true;
                unregister_code(KC_LSHIFT);
                register_code(KC_LALT);
            }
            alt_tab_timer = timer_read();
            tap_code(KC_TAB);
        } else {
            if (!is_alt_shift_tab_active) {
                is_alt_shift_tab_active = true;
                register_code(KC_LALT);
                register_code(KC_LSHIFT);
            }
            alt_tab_timer = timer_read();
            tap_code(KC_TAB);
        }
    } else if (get_mods() & MOD_BIT(KC_LSFT)) {
     if (clockwise) {
            tap_code(KC_F3);
        } else {
            tap_code16(S(KC_F3));
        }
    }

    else {
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    }
    return false;
}

void matrix_scan_user(void) {
  if (is_alt_tab_active) {
    if (timer_elapsed(alt_tab_timer) > 1000) {
      unregister_code(KC_LALT);
      unregister_code(KC_LSHIFT);
      is_alt_tab_active = false;
      is_alt_shift_tab_active = false;
    }
  }
}


#endif

void matrix_init_user(void) {
#ifdef RGB_MATRIX_ENABLE
    rgb_matrix_init_user();
#endif
}

void keyboard_post_init_user(void) {
    // debug_enable=true;
    // debug_matrix=true;
    rgblight_enable_noeeprom(); // Enables RGB, without saving settings
    rgblight_sethsv_noeeprom(HSV_BLUE);
    rgblight_mode_noeeprom(1);
    user_config.raw = eeconfig_read_user();
}

void eeconfig_init_user(void) {
    user_config.raw = 0;
    rgblight_enable_noeeprom(); // Enables RGB, without saving settings
    rgblight_sethsv_noeeprom(HSV_BLUE);
    rgblight_mode_noeeprom(1);
    user_config.caps_lock_light_tab = true;
    user_config.caps_lock_light_alphas = true;
    user_config.fn_layer_transparent_keys_off = true;
    user_config.fn_layer_color_enable = true;
    eeconfig_update_user(user_config.raw);
}


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_LOPTN:
        case KC_ROPTN:
        case KC_LCMMD:
        case KC_RCMMD:
            if (record->event.pressed) {
                register_code(mac_keycode[keycode - KC_LOPTN]);
            } else {
                unregister_code(mac_keycode[keycode - KC_LOPTN]);
            }
            return false;
        case KC_MCTL:
            if (record->event.pressed) {
                host_consumer_send(0x29F);
            } else {
                host_consumer_send(0);
            }
            return false;  // Skip all further processing of this key
        case KC_LPAD:
            if (record->event.pressed) {
                host_consumer_send(0x2A0);
            } else {
                host_consumer_send(0);
            }
            return false;  // Skip all further processing of this key
        case KC_TASK:
        case KC_FLXP:
            if (record->event.pressed) {
                for (uint8_t i = 0; i < key_comb_list[keycode - KC_TASK].len; i++) {
                    register_code(key_comb_list[keycode - KC_TASK].keycode[i]);
                }
            } else {
                for (uint8_t i = 0; i < key_comb_list[keycode - KC_TASK].len; i++) {
                    unregister_code(key_comb_list[keycode - KC_TASK].keycode[i]);
                }
            }
            return false;  // Skip all further processing of this key
        case KC_LIGHT_TAB_TOGGLE:
            if (record->event.pressed) {
                user_config.caps_lock_light_tab ^= 1; // bitwise xor to toggle status bit
                eeconfig_update_user(user_config.raw);
            }
            return false;  // Skip all further processing of this key
        case KC_LIGHT_ALPHAS_TOGGLE:
            if (record->event.pressed) {
                user_config.caps_lock_light_alphas ^= 1;
                eeconfig_update_user(user_config.raw);
            }
            return false;  // Skip all further processing of this key
        case KC_FN_LAYER_TRANSPARENT_KEYS_TOGGLE:
            if (record->event.pressed) {
                user_config.fn_layer_transparent_keys_off ^= 1;
                eeconfig_update_user(user_config.raw);
            }
            return false;  // Skip all further processing of this key
        case KC_FN_LAYER_COLOR_TOGGLE:
            if (record->event.pressed) {
                user_config.fn_layer_color_enable ^= 1;
                eeconfig_update_user(user_config.raw);
            }
            return false;  // Skip all further processing of this key

        default:
            return true;  // Process all other keycodes normally
    }
}



bool get_caps_lock_light_tab(void) {
    return user_config.caps_lock_light_tab;
}

bool get_caps_lock_light_alphas(void) {
    return user_config.caps_lock_light_alphas;
}

bool get_fn_layer_transparent_keys_off(void) {
    return user_config.fn_layer_transparent_keys_off;
}

bool get_fn_layer_color_enable(void) {
    return user_config.fn_layer_color_enable;
}


// typedef enum {
//     TD_NONE,
//     TD_UNKNOWN,
//     TD_SINGLE_TAP,
//     TD_SINGLE_HOLD,
//     TD_DOUBLE_TAP,
//     TD_DOUBLE_HOLD,
//     TD_DOUBLE_SINGLE_TAP, // Send two single taps
//     TD_TRIPLE_TAP,
//     TD_TRIPLE_HOLD
// } td_state_t;

// typedef struct {
//     bool is_press_action;
//     td_state_t state;
// } td_tap_t;

// // Tap dance enum definitions
// enum {
//     X_CTL,
//     SOME_OTHER_DANCE
// };


// td_state_t cur_dance(qk_tap_dance_state_t *state);

// // For the x tap dance. Put it here so it can be used in any keymap
// void x_finished(qk_tap_dance_state_t *state, void *user_data);
// void x_reset(qk_tap_dance_state_t *state, void *user_data);

// td_state_t cur_dance(qk_tap_dance_state_t *state) {
//     if (state->count == 1) {
//         if (state->interrupted || !state->pressed) return TD_SINGLE_TAP;
//         // Key has not been interrupted, but the key is still held. Means you want to send a 'HOLD'.
//         else return TD_SINGLE_HOLD;
//     } else if (state->count == 2) {
//         // TD_DOUBLE_SINGLE_TAP is to distinguish between typing "pepper", and actually wanting a double tap
//         // action when hitting 'pp'. Suggested use case for this return value is when you want to send two
//         // keystrokes of the key, and not the 'double tap' action/macro.
//         if (state->interrupted) return TD_DOUBLE_SINGLE_TAP;
//         else if (state->pressed) return TD_DOUBLE_HOLD;
//         else return TD_DOUBLE_TAP;
//     }

//     // Assumes no one is trying to type the same letter three times (at least not quickly).
//     // If your tap dance key is 'KC_W', and you want to type "www." quickly - then you will need to add
//     // an exception here to return a 'TD_TRIPLE_SINGLE_TAP', and define that enum just like 'TD_DOUBLE_SINGLE_TAP'
//     if (state->count == 3) {
//         if (state->interrupted || !state->pressed) return TD_TRIPLE_TAP;
//         else return TD_TRIPLE_HOLD;
//     } else return TD_UNKNOWN;
// }

// // Create an instance of 'td_tap_t' for the 'x' tap dance.
// static td_tap_t xtap_state = {
//     .is_press_action = true,
//     .state = TD_NONE
// };

// void x_finished(qk_tap_dance_state_t *state, void *user_data) {
//     xtap_state.state = cur_dance(state);
//     switch (xtap_state.state) {
//         case TD_SINGLE_TAP: register_code(KC_RIGHT); break;
//         case TD_SINGLE_HOLD: register_code(KC_RIGHT); break;
//         case TD_DOUBLE_TAP: register_code(KC_KP_ENTER); break;
//         case TD_DOUBLE_HOLD: register_code(KC_KP_ENTER); break;
//         // Last case is for fast typing. Assuming your key is `f`:
//         // For example, when typing the word `buffer`, and you want to make sure that you send `ff` and not `Esc`.
//         // In order to type `ff` when typing fast, the next character will have to be hit within the `TAPPING_TERM`, which by default is 200ms.
//         case TD_DOUBLE_SINGLE_TAP: tap_code(KC_RIGHT); register_code(KC_RIGHT);
//         case TD_UNKNOWN: register_code(KC_RIGHT);
//         default: break;
//     }
// }

// void x_reset(qk_tap_dance_state_t *state, void *user_data) {
//     switch (xtap_state.state) {
//         case TD_SINGLE_TAP: unregister_code(KC_RIGHT); break;
//         case TD_SINGLE_HOLD: unregister_code(KC_RIGHT); break;
//         case TD_DOUBLE_TAP: unregister_code(KC_KP_ENTER); break;
//         case TD_DOUBLE_HOLD: unregister_code(KC_KP_ENTER);
//         case TD_DOUBLE_SINGLE_TAP: unregister_code(KC_RIGHT);
//         case TD_UNKNOWN: unregister_code(KC_RIGHT);
//         default: break;
//     }
//     xtap_state.state = TD_NONE;
// }

// qk_tap_dance_action_t tap_dance_actions[] = {
//     [X_CTL] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, x_finished, x_reset)
// };