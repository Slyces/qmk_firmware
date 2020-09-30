/* Copyright 2019 Thomas Baart <thomas@splitkb.com>
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

// Layers declarations
enum layers {
    _COLEMAK = 0,
    _GAMING,
    _SYMB,
    _NUM,
    _CONFIG
};

// Tap dance keycodes
enum td_keycodes {
    TD_MOVE,
    TD_SCOL
};

// Tap dance definitions
typedef struct {
    bool is_press_action;
    uint8_t state;
} tap;

// Define a type for as many tap dance states as you need
enum {
    SINGLE_TAP = 1,
    SINGLE_HOLD,
    DOUBLE_TAP
};

// rgb version of functions
#ifdef RGBLIGHT_ENABLE
void keyboard_post_init_rgb(void);
void layer_state_set_rgb(uint32_t state);
void default_layer_state_set_rgb(uint32_t default_state);
#endif // RGBLIGHT_ENABLE

// Function associated with all tap dances
uint8_t cur_dance(qk_tap_dance_state_t *state);

// Move → key
void mv_finished(qk_tap_dance_state_t *state, void *user_data);
void mv_reset(qk_tap_dance_state_t *state, void *user_data);

// Shift
void sft_finished(qk_tap_dance_state_t *state, void *user_data);
void sft_reset(qk_tap_dance_state_t *state, void *user_data);

#define _COLEMAK 0
#define _GAMING 1
#define _SYMB 3
#define _NUM 4
#define _CONFIG 5
#define __LAST 6

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
 * Base Layer: Colemak
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |  ESC   |   Q  |   W  |   F  |   P  |   B  |                              |   J  |   L  |   U  |   Y  | ;  : |  DEL   |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |  BSPC  |   A  |   R  |  S   |   T  |   G  |                              |   M  |   N  |   E  |   I  |   O  |  ' "   |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * | LSHIFT |   Z  |   X  |   C  |   D  |   V  | GAME |  ESC |  |CONFIG|Space |   K  |   H  | ,  < | . >  | /  ? | RSHIFT |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |  NUM | ESC  | ENTR | CTRL |  | CTRL | SPC  | TAB  |  NUM |      |
 *                        |      | +ALT |SHIFT |      |      |  |      |SHIFT |(RCTL)| +ALT |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_COLEMAK] = LAYOUT(
      A(KC_E), KC_Q, KC_W,      KC_F,      KC_P, KC_B,                                           KC_J, KC_L, KC_U,      KC_Y,      KC_SCLN, KC_DEL,
      KC_BSPC, KC_A, LTN(KC_R), LTS(KC_S), KC_T, KC_G,                                           KC_M, KC_N, LTS(KC_E), LTN(KC_I), KC_O,    KC_QUOT,
      KC_LSFT, KC_Z, KC_X,      KC_C,      KC_D, KC_V, DF(_GAMING), KC_ESC, MO(_CONFIG), KC_ENT, KC_K, KC_H, KC_COMM,   KC_DOT,    KC_SLSH, KC_RSFT,
         _______, LM(_NUM, MOD_LALT), ALT_T(KC_ESC), SFT_T(KC_ENT), TD(TD_MOVE), TD(TD_MOVE), SFT_T(KC_SPC), ALT_T(KC_TAB), LM(_NUM, MOD_LALT), _______
    ),

/*
 * Base Layer: Gaming
 *
 * ,-------------------------------------------.
 * |   ESC  |   1  |   2  |   3  |   4  |   5  |
 * |--------+------+------+------+------+------|
 * |   TAB  |   T  |   Q  |   W  |  E   |   R  |
 * |--------+------+------+------+------+------+-------------.
 * |        |   G  |   A  |   S  |   D  |   F  | base |      |
 * `---------------+-------------+------+------+------+------|
 *                        |      | CTRL |  ALT | SPACE| ENTR |
 *                        |      |      |      |      |      |
 *                        `----------------------------------'
 */
    [_GAMING] = LAYOUT(
      KC_ESC , KC_5, KC_1, KC_2, KC_3, KC_4,                                           _______, _______, _______, _______, _______, _______,
      KC_TAB , KC_T, KC_Q, KC_W, KC_E, KC_R,                                          _______, _______, _______, _______, _______, _______,
      _______, KC_G, KC_A, KC_S, KC_D, KC_D, DF(_COLEMAK), _______, _______, _______, _______, _______, _______, _______, _______, _______,
                           _______, _______, KC_LALT, KC_SPC , _______, _______, _______, _______, _______, _______
    ),

/*
 * Lower Layer: Symbols
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |  !   |  @   |  {   |  }   |  |   |                              |      |  _   |  ?   |      |      |  | \   |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |  #   |  $   |  (   |  )   |  `   |                              |   +  |  -   |  /   |  *   |  %   |  ' "   |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |  %   |  ^   |  [   |  ]   |  ~   |      |      |  |      |      |   &  |  =   |  ,   |  .   |  / ? | - _    |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |  :   |  =   |  |  =   |  ;   |      |      |      |
 *                        |      |      |      | SHIFT|      |  |      | SHIFT|      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_SYMB] = LAYOUT(
      _______, KC_EXLM, KC_AT,   KC_LCBR, KC_RCBR, KC_PIPE,                                     _______, S(KC_MINS), S(KC_SLASH), _______, _______, KC_BSLS,
      _______, KC_HASH, KC_DLR,  KC_LPRN, KC_RPRN, KC_GRV,                                      KC_PLUS, KC_MINS, KC_SLSH, KC_ASTR, KC_PERC, KC_QUOT,
      _______, KC_PERC, KC_CIRC, KC_LBRC, KC_RBRC, KC_TILD, _______, _______, _______, _______, KC_AMPR, KC_EQL,  KC_COMM, KC_DOT,  KC_SLSH, KC_MINS,
                        _______, _______, _______, TD(TD_SCOL), KC_EQL,  KC_EQL,  SFT_T(KC_SCLN), _______, _______, _______
    ),
/*
 * Raise Layer: Number keys, media, navigation
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |   1  |  2   |  3   |  4   |  5   |                              |  6   |  7   |  8   |  9   |  0   |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |      | Prev | Play | Next | VolUp|                              | Left | Down | Up   | Right|      |        |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |      |      |      | Mute | VolDn|      |      |  |      |      | MLeft| Mdown| MUp  |MRight|      |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_NUM] = LAYOUT(
      _______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                                        KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______,
      _______, _______, KC_MPRV, KC_MPLY, KC_MNXT, KC_VOLU,                                     _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______,
      _______, _______, _______, _______, KC_MUTE, KC_VOLD, _______, _______, _______, _______, _______, KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, _______,
                                 _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),
/*
 * Adjust Layer: Function keys, RGB
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        | F1   |  F2  | F3   | F4   | F5   |                              | F6   | F7   |  F8  | F9   | F10  |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        | TOG  | SAI  | HUI  | VAI  | MOD  |                              |      |      |      | F11  | F12  |        |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |      | SAD  | HUD  | VAD  | RMOD |      |      |  |      |      |      |      |      |      |      |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_CONFIG] = LAYOUT(
      _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                                       KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  _______,
      _______, RGB_TOG, RGB_SAI, RGB_HUI, RGB_VAI, RGB_MOD,                                     _______, _______, _______, KC_F11,  KC_F12,  _______,
      _______, _______, RGB_SAD, RGB_HUD, RGB_VAD, RGB_RMOD, TG(_CONFIG), _______, _______, _______, _______, _______, _______, _______, _______, _______,
                                 _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),
// /*
//  * Layer template
//  *
//  * ,-------------------------------------------.                              ,-------------------------------------------.
//  * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
//  * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
//  * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
//  * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
//  * |        |      |      |      |      |      |      |      |  |      |      |      |      |      |      |      |        |
//  * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
//  *                        |      |      |      |      |      |  |      |      |      |      |      |
//  *                        |      |      |      |      |      |  |      |      |      |      |      |
//  *                        `----------------------------------'  `----------------------------------'
//  */
//     [_LAYERINDEX] = LAYOUT(
//       _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
//       _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
//       _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
//                                  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
//     ),
};

void keyboard_post_init_user(void) {
#ifdef RGBLIGHT_ENABLE
    keyboard_post_init_rgb();
#endif // RGBLIGHT_ENABLE
}

uint32_t layer_state_set_user(uint32_t state) {
#ifdef RGBLIGHT_ENABLE
    layer_state_set_rgb(state);
#endif // RGBLIGHT_ENABLE
    return state;
}

uint32_t default_layer_state_set_user(uint32_t default_state) {
#if defined(RGBLIGHT_ENABLE) && ! defined(RGBLIGHT_LAYERS)
    default_layer_state_set_rgb(default_state);
#endif // RGBLIGHT_ENABLE && ! RGBLIGHT_LAYERS
    return default_state;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        default:
            return true;
    }
}

void matrix_scan_user(void) {
#ifdef RGBLIGHT_LAYERS
    led_update_user(host_keyboard_led_state());
#endif // RGBLIGHT_LAYERS
}

/* ─────────────────────────────── RGB lights ─────────────────────────────── */

#ifdef RGBLIGHT_LAYERS
const rgblight_segment_t PROGMEM rgb_gaming_layer[] = RGBLIGHT_LAYER_SEGMENTS( {0, 20, HS_RED} );
const rgblight_segment_t PROGMEM rgb_config_layer[] = RGBLIGHT_LAYER_SEGMENTS( {0, 20, HS_PURPLE} );
const rgblight_segment_t PROGMEM rgb_colemak_layer[] = RGBLIGHT_LAYER_SEGMENTS( {0, 20, HS_WHITE} );
const rgblight_segment_t PROGMEM rgb_symbols_layer[] = RGBLIGHT_LAYER_SEGMENTS( {0, 20, HS_BLUE} );
const rgblight_segment_t PROGMEM rgb_numbers_layer[] = RGBLIGHT_LAYER_SEGMENTS( {0, 20, HS_GREEN} );

const rgblight_segment_t PROGMEM rgb_alt_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {5, 2, HS_GOLD},
    {15, 2, HS_GOLD}
);

const rgblight_segment_t PROGMEM rgb_ctrl_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {2, 2, HS_GOLD},
    {12, 2, HS_GOLD}
);
const rgblight_segment_t PROGMEM rgb_shift_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 2, HS_GOLD},
    {10, 2, HS_GOLD}
);


const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    rgb_colemak_layer,
    rgb_gaming_layer,
    rgb_symbols_layer,
    rgb_numbers_layer,
    rgb_config_layer,
    rgb_alt_layer,
    rgb_ctrl_layer,
    rgb_shift_layer
);

bool led_update_user(led_t led_state) {
    rgblight_set_layer_state(5, get_mods() & MOD_MASK_ALT);
    rgblight_set_layer_state(6, get_mods() & MOD_MASK_CTRL);
    rgblight_set_layer_state(7, get_mods() & MOD_MASK_SHIFT);
    return true;
}
#endif

#ifdef RGBLIGHT_ENABLE
void keyboard_post_init_rgb(void) {
    rgblight_enable_noeeprom();
    rgblight_sethsv(rgblight_get_hue(), rgblight_get_sat(), 80);
#    ifdef RGBLIGHT_LAYERS
    rgblight_layers = my_rgb_layers;
#    else
    default_layer_rgb(default_layer_state);
#    endif // RGBLIGHT_LAYERS
}

void layer_state_set_rgb(uint32_t state) {
#    ifdef RGBLIGHT_LAYERS
    // State for normal layers
    for (int i = _SYMB; i < __LAST; i++) {
        rgblight_set_layer_state(i, layer_state_cmp(state, i));
    }
    /*send_layer_via_hid(state);*/
#    else
    uint8_t val = rgblight_get_val();
    switch (biton32(state)) {
        case _SYMB:
            rgblight_sethsv_noeeprom(HS_BLUE, val); break;
        case _NUM:
            rgblight_sethsv_noeeprom(HS_GREEN, val); break;
        case _CONFIG:
            rgblight_sethsv_noeeprom(HS_PURPLE, val); break;
        default:
            default_layer_rgb(default_layer_state); break;
    }
#    endif // RGBLIGHT_LAYERS
}

void default_layer_state_set_rgb(uint32_t default_state) {
#    ifdef RGBLIGHT_LAYERS
    // Default layers
    rgblight_set_layer_state(_COLEMAK, default_state & (1UL << _COLEMAK));
    rgblight_set_layer_state(_GAMING, default_state & (1UL << _GAMING));
#    else
    default_layer_rgb(default_state);
#    endif // ! RGBLIGHT_LAYERS
}

#    ifndef RGBLIGHT_LAYERS
void default_layer_rgb(uint32_t default_state) {
    uint8_t val = rgblight_get_val();
    switch (biton32(default_state)) {
        case _COLEMAK:
            rgblight_sethsv_noeeprom(HS_WHITE, val); break;
        case _GAMING:
            rgblight_sethsv_noeeprom(HS_RED, val); break;
        default:
            rgblight_sethsv_noeeprom(HS_WHITE, val); break;
    }
}
#    endif // ! RGBLIGHT_LAYERS
#endif // RGBLIGHT_ENABLE


/* ─────────────────────────────── Tap Dance ──────────────────────────────── */
// Determine the current tap dance state
uint8_t cur_dance(qk_tap_dance_state_t *state) {
    if (state->count == 1) {
        if (!state->pressed) {
            return SINGLE_TAP;
        } else {
            return SINGLE_HOLD;
        }
    } else if (state->count == 2) {
        return DOUBLE_TAP;
    }
    else return 8;
}

static tap mv_state = {
    .is_press_action = true,
    .state = 0
};
static tap sft_state = {
    .is_press_action = true,
    .state = 0
};

// Functions that control what our tap dance key does
void mv_finished(qk_tap_dance_state_t *state, void *user_data) {
    mv_state.state = cur_dance(state);
    switch (mv_state.state) {
        case SINGLE_HOLD:  // Hold → CTRL
            register_code(KC_LCTL);
            break;
        case SINGLE_TAP:  // 1 Tap → OSM(ALT) + OSL(_NUM)
            set_oneshot_layer(_NUM, ONESHOT_START);
            clear_oneshot_layer_state(ONESHOT_PRESSED);
            set_oneshot_mods(MOD_LALT);
            break;
        case DOUBLE_TAP:  // 2 Tap → CTRL_A + OSL(_NUM)
            SEND_STRING(SS_DOWN(X_LCTRL) SS_TAP(X_A) SS_UP(X_LCTRL));
            set_oneshot_layer(_NUM, ONESHOT_START);
            clear_oneshot_layer_state(ONESHOT_PRESSED);
            break;
    }
}

void mv_reset(qk_tap_dance_state_t *state, void *user_data) {
    // If the key was held down and now is released then switch off the mod
    switch (mv_state.state) {
        case SINGLE_TAP: break;
        case SINGLE_HOLD: unregister_code(KC_LCTRL); break;
        case DOUBLE_TAP: break;
    }
    mv_state.state = 0;
}

// Functions that control what our tap dance key does
void sft_finished(qk_tap_dance_state_t *state, void *user_data) {
    sft_state.state = cur_dance(state);
    switch (sft_state.state) {
        case SINGLE_HOLD: register_code(KC_LSFT); break;
        case SINGLE_TAP: register_code16(KC_COLN); break;
    }
}

void sft_reset(qk_tap_dance_state_t *state, void *user_data) {
    // If the key was held down and now is released then switch off the mod
    switch (sft_state.state) {
        case SINGLE_HOLD: unregister_code(KC_LSFT); break;
        case SINGLE_TAP: unregister_code16(KC_COLN); break;
    }
    sft_state.state = 0;
}

// Associate our tap dance key with its functionality
qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_MOVE] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, mv_finished, mv_reset),
    [TD_SCOL] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, sft_finished, sft_reset),

};

bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {

    switch (keycode) {
        case KC_NO:
            /* Always cancel one-shot layer when another key gets pressed */
            if (record->event.pressed && is_oneshot_layer_active())
                clear_oneshot_layer_state(ONESHOT_OTHER_KEY_PRESSED);
            return true;
        case RESET:
            /* Don't allow reset from oneshot layer state */
            if (record->event.pressed && is_oneshot_layer_active()){
                clear_oneshot_layer_state(ONESHOT_OTHER_KEY_PRESSED);
                return false;
            }
            return true;
        default:
            return true;
    }
    return true;
}
