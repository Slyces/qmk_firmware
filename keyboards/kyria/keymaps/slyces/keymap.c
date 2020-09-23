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

// Function associated with all tap dances
uint8_t cur_dance(qk_tap_dance_state_t *state);

// Functions associated with [move → key]
void mtd_finished(qk_tap_dance_state_t *state, void *user_data);
void mtd_reset(qk_tap_dance_state_t *state, void *user_data);

void scol_finished(qk_tap_dance_state_t *state, void *user_data);
void scol_reset(qk_tap_dance_state_t *state, void *user_data);

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
 * |   TAB  |   1  |   2  |   3  |   4  |   5  |
 * |--------+------+------+------+------+------|
 * |   NAV  |   Q  |   W  |  E   |   R  |   T  |
 * |--------+------+------+------+------+------+-------------.
 * | LShift |   A  |   S  |   D  |   F  |   G  | Enter|  ESC |
 * `----------------------+------+------+------+      +------|
 *                        | LCTL | GUI  | RALT |      | NUM  |
 *                        |      |      |      |      |      |
 *                        `----------------------------------'
 */
    [_GAMING] = LAYOUT(
      KC_ESC , KC_1, KC_2, KC_3, KC_4, KC_5,                                           _______, _______, _______, _______, _______, _______,
      KC_TAB , KC_Q, KC_W, KC_E, KC_R, KC_T,                                          _______, _______, _______, _______, _______, _______,
      _______, KC_A, KC_S, KC_D, KC_D, KC_G, DF(_COLEMAK), _______, _______, _______, _______, _______, _______, _______, _______, _______,
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


#ifdef RGBLIGHT_ENABLE
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
#endif // RGBLIGHT_ENABLE

uint32_t layer_state_set_user(uint32_t state) {
#ifdef RGBLIGHT_ENABLE
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
#endif // RGBLIGHT_ENABLE
    return state;
}

uint32_t default_layer_state_set_user(uint32_t default_state) {
#ifdef RGBLIGHT_ENABLE
    default_layer_rgb(default_state);
#endif // RGBLIGHT_ENABLE
    return default_state;
}

void keyboard_post_init_user(void) {
#ifdef RGBLIGHT_ENABLE
    rgblight_enable_noeeprom();
    rgblight_sethsv(rgblight_get_hue(), rgblight_get_sat(), 80);
    default_layer_rgb(default_layer_state);
    /*rgblight_sethsv_range(HS_BLUE, rgblight_get_val(), 4, 8);*/
    /*rgblight_sethsv_range(HS_BLUE, rgblight_get_val(), 14, 18);*/
#endif // RGBLIGHT_ENABLE
}


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

static tap mtd_state = {
    .is_press_action = true,
    .state = 0
};
static tap scol_state = {
    .is_press_action = true,
    .state = 0
};

// Functions that control what our tap dance key does
void mtd_finished(qk_tap_dance_state_t *state, void *user_data) {
    mtd_state.state = cur_dance(state);
    switch (mtd_state.state) {
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

void mtd_reset(qk_tap_dance_state_t *state, void *user_data) {
    // If the key was held down and now is released then switch off the mod
    switch (mtd_state.state) {
        case SINGLE_TAP: break;
        case SINGLE_HOLD: unregister_code(KC_LCTRL); break;
        case DOUBLE_TAP: break;
    }
    mtd_state.state = 0;
}

// Functions that control what our tap dance key does
void scol_finished(qk_tap_dance_state_t *state, void *user_data) {
    scol_state.state = cur_dance(state);
    switch (scol_state.state) {
        case SINGLE_HOLD: register_code(KC_LSFT); break;
        case SINGLE_TAP: register_code16(KC_COLN); break;
    }
}

void scol_reset(qk_tap_dance_state_t *state, void *user_data) {
    // If the key was held down and now is released then switch off the mod
    switch (scol_state.state) {
        case SINGLE_HOLD: unregister_code(KC_LSFT); break;
        case SINGLE_TAP: unregister_code16(KC_COLN); break;
    }
    scol_state.state = 0;
}

// Associate our tap dance key with its functionality
qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_MOVE] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, mtd_finished, mtd_reset),
    [TD_SCOL] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, scol_finished, scol_reset),

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
