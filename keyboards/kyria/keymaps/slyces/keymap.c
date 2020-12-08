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
#include "slyces.h"
#include "wrappers.h"

/* ──────────────────────────────────── kyria specific layout ──────────────────────────────────── */
/* For personal convenience, I chose to reorder the keys to have a slightly more compact display of
 * each keymap.
 * --------------------------------------------------------------------------------------------------
 * → Original layout:
 * ,------------------------------------.                          ,------------------------------------.
 * |  K00 | K01 | K02 | K03 | K04 | K05 |                          | K06 | K07 | K08 | K09 | K10 |  K11 |
 * |------+-----+-----+-----+-----+-----|                          |-----+-----+-----+-----+-----+------|
 * |  K12 | K13 | K14 | K15 | K16 | K17 |                          | K18 | K19 | K20 | K21 | K22 |  K23 |
 * |------+-----+-----+-----+-----+-----+-----------.  ,-----------+-----+-----+-----+-----+-----+------|
 * |  K24 | K25 | K26 | K27 | K28 | K29 | K30 | K31 |  | K32 | K33 | K34 | K35 | K36 | K37 | K38 |  K39 |
 * `------------------+-----+-----+-----+-----+-----|  |-----+-----+-----+-----+-----+------------------'
 *                    | K40 | K41 | K42 | K43 | K44 |  | K45 | K46 | K47 | K48 | K49 |
 *                    `-----------------------------'  `-----------------------------'
 * corresponding code:
 *
 *  [_LAYER] = LAYOUT(
   KC_00, KC_01, KC_02, KC_03, KC_04, KC_05,                             KC_06, KC_07, KC_08, KC_09, KC_10, KC_11, \
   KC_12, KC_13, KC_14, KC_15, KC_16, KC_17,                             KC_18, KC_19, KC_20, KC_21, KC_22, KC_23, \
   KC_24, KC_25, KC_26, KC_27, KC_28, KC_29, KC_30, KC_31, KC_32, KC_33, KC_34, KC_35, KC_36, KC_37, KC_38, KC_39, \
                        KC_40, KC_41, KC_42, KC_43, KC_44, KC_45, KC_46, KC_47, KC_48, KC_49 \
 *  ),
 *
 * I find this code impractical because the bottom row (K40 - K49), and the middle 4 buttons of the
 * 3rd row (K30 - K33) tend to be non-alphanumeric keycodes, quite longer than most, thus stretching
 * the space in the middle and creating very long lines.
 *
 * --------------------------------------------------------------------------------------------------
 * → New custom layout:
 * ,--------. ,----------------------------------.    ,----------------------------------. ,--------.
 * |  K00   | |  K01 |  K02 |  K03 |  K04 |  K05 |    |  K06 |  K07 |  K08 |  K09 |  K10 | |  K11   |
 * |--------| |------+------+------+------+------|    |------+------+------+------+------| |--------|
 * |  K12   | |  K13 |  K14 |  K15 |  K16 |  K17 |    |  K18 |  K19 |  K20 |  K21 |  K22 | |  K23   |
 * |--------| |------+------+------+------+------|    |------+------+------+------+------| |--------|
 * |  K24   | |  K25 |  K26 |  K27 |  K28 |  K29 |    |  K34 |  K35 |  K36 |  K37 |  K38 | |  K39   |
 * `--------' `----------------------------------'    `----------------------------------' `--------'
 *                                 ,-------------.    ,-------------.
 *                                 |  K30 |  K31 |    |  K32 |  K33 |
 *            ,--------------------+------+------|    |------+------+------+------+------.
 *            |  K40 |  K41 |  K42 |  K43 |  K44 |    |  K45 |  K46 |  K47 |  K48 |  K49 |
 *            `----------------------------------'    `----------------------------------'
 *
 * corresponding code:
 *
 *  [_Layer] = LAYOUT(
 *     KC_00, KC_01, KC_02, KC_03, KC_04, KC_05,  KC_06, KC_07, KC_08, KC_09, KC_10, KC_11, \
 *     KC_12, KC_13, KC_14, KC_15, KC_16, KC_17,  KC_18, KC_19, KC_20, KC_21, KC_22, KC_23, \
 *     KC_24, KC_25, KC_26, KC_27, KC_28, KC_29,  KC_34, KC_35, KC_36, KC_37, KC_38, KC_39, \
 *                                 KC_30, KC_31,  KC_32, KC_33, \
 *            KC_40, KC_41, KC_42, KC_43, KC_44,  KC_45, KC_46, KC_47, KC_48, KC_49 \
 *  ),
 *
 * The code allows for more compact definitions by keeping logical sections separated:
 * - alphanumeric rows (3x5 keys left, 3x5 keys right) are adjacent
 * - thumb cluster split on its own lines
 * - never more than 12 keys on a single line
 */
#define LAYOUT_kyria_custom( \
   KC_00, KC_01, KC_02, KC_03, KC_04, KC_05,  KC_06, KC_07, KC_08, KC_09, KC_10, KC_11, \
   KC_12, KC_13, KC_14, KC_15, KC_16, KC_17,  KC_18, KC_19, KC_20, KC_21, KC_22, KC_23, \
   KC_24, KC_25, KC_26, KC_27, KC_28, KC_29,  KC_34, KC_35, KC_36, KC_37, KC_38, KC_39, \
                               KC_30, KC_31,  KC_32, KC_33, \
          KC_40, KC_41, KC_42, KC_43, KC_44,  KC_45, KC_46, KC_47, KC_48, KC_49 \
  ) \
  LAYOUT_wrapper( \
   KC_00, KC_01, KC_02, KC_03, KC_04, KC_05,                             KC_06, KC_07, KC_08, KC_09, KC_10, KC_11, \
   KC_12, KC_13, KC_14, KC_15, KC_16, KC_17,                             KC_18, KC_19, KC_20, KC_21, KC_22, KC_23, \
   KC_24, KC_25, KC_26, KC_27, KC_28, KC_29, KC_30, KC_31, KC_32, KC_33, KC_34, KC_35, KC_36, KC_37, KC_38, KC_39, \
                        KC_40, KC_41, KC_42, KC_43, KC_44, KC_45, KC_46, KC_47, KC_48, KC_49 \
    )

/* Re-pass though to allow templates to be used */
#define LAYOUT_kyria_custom_wrapper(...)       LAYOUT_kyria_custom(__VA_ARGS__)

/* ───────────────────────────────────── Tap dance Shortcuts ───────────────────────────────────── */
#ifdef TAP_DANCE_ENABLE
    #define TD_M TD(TD_MOVE)
#else
    #define TD_M _______
#endif

/* ─────────────────────────────────────── Thumb Clusters ──────────────────────────────────────── */
/*                                 ,-------------.    ,-------------.
 *                                 |      |      |    |      |      |
 *            ,--------------------+------+------|    |------+------+--------------------.
 *            |      |      |      |      |      |    |      |      |      |      |      |
 *            |      |      |      |      |      |    |      |      |      |      |      |
 *            `----------------------------------'    `----------------------------------'
 */
#define ______________BLANK_THUMBS_CLUSTER_____________ \
                              _______, _______,   _______, _______, \
   _______, _______, _______, _______, _______,   _______, _______, _______, _______, _______


/*                                 ,-------------.    ,-------------.
 *                                 |GAMING|CONFIG|    |CONFIG|GAMING|
 *            ,--------------------+------+------|    |------+------+--------------------.
 *            |      |      | ESC  | ENTR |  i3  |    |  i3  | SPC  |  TAB |      |      |
 *            |      |      |[ALT] |[CTRL]| tmux |    | tmux |[CTRL]| [ALT]|      |      |
 *            `----------------------------------'    `----------------------------------'
 */
#define _____________DEFAULT_THUMBS_CLUSTER____________ \
                             DF(_GAMING), MO(_CONFIG), MO(_CONFIG), DF(_GAMING), \
 _______, _______, ALT_T(KC_ESC), CTL_T(KC_ENT), TD_M, TD_M, CTL_T(KC_SPC), ALT_T(KC_TAB), _______, _______


/* ───────────────────────────────────────── shortcuts ────────────────────────────────────────── */
#define OS_SFT OSM(MOD_LSFT)

/* ─────────────────────────────────────────── layers ──────────────────────────────────────────── */
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
 * Base Layer: Colemak
 *
 * ,--------. ,----------------------------------.    ,----------------------------------. ,--------.
 * |  ESC   | |   Q  |   W  |   F  |   P  |   B  |    |   J  |   L  |   U  |   Y  |  ; : | |  DEL   |
 * |--------| |------+------+------+------+------|    |------+------+------+------+------| |--------|
 * |  TAB   | |   A  |   R  |   S  |   T  |   G  |    |   M  |   N  |   E  |   I  |   O  | | BACKSP |
 * |--------| |------+------+------+------+------|    |------+------+------+------+------| |--------|
 * |OS_SHIFT| |   Z  |   X  |   C  |   D  |   V  |    |   K  |   H  |  , < |  . > |  / ? | |OS_SHIFT|
 * `--------' `----------------------------------'    `----------------------------------' `--------'
 *                                 ,-------------.    ,-------------.
 *                                 |GAMING|CONFIG|    |CONFIG|GAMING|
 *            ,--------------------+------+------|    |------+------+--------------------.
 *            |      |      | ESC  | ENTR |  i3  |    |  i3  | SPC  |  TAB |      |      |
 *            |      |      |[ALT] |[CTRL]| tmux |    | tmux |[CTRL]| [ALT]|      |      |
 *            `----------------------------------'    `----------------------------------'
 */
    [_COLEMAK] = LAYOUT_kyria_custom_wrapper(
      KC_ESC, ____________COLEMAK_DHM_L1___________, ____________COLEMAK_DHM_R1___________, KC_DEL,
      KC_TAB, ________COLEMAK_Dhm_HMOD_LEFT________, ________COLEMAK_Dhm_HMOD_RIGHT_______, KC_BSPC,
      OS_SFT, ____________COLEMAK_DHM_L3___________, ____________COLEMAK_DHM_R3___________, OS_SFT,
                              _____________DEFAULT_THUMBS_CLUSTER____________
    ),

/*
 * Base Layer: Gaming [ {/!\} in progress {/!\} ]
 * ,--------. ,----------------------------------.    ,----------------------------------. ,--------.
 * |  ESC   | |   5  |   1  |   2  |   3  |   4  |    |      |      |      |      |      | |        |
 * |--------| |------+------+------+------+------|    |------+------+------+------+------| |--------|
 * |  TAB   | |   T  |   Q  |   W  |   E  |   R  |    |      |      |      |      |      | |        |
 * |--------| |------+------+------+------+------|    |------+------+------+------+------| |--------|
 * |        | |   R  |   T  |   Q  |   W  |   E  |    |      |      |      |      |      | |        |
 * `--------' `----------------------------------'    `----------------------------------' `--------'
 *                                 ,-------------.    ,-------------.
 *                                 | BASE |      |    |      | BASE |
 *            ,--------------------+------+------|    |------+------+--------------------.
 *            |      |      |  ALT | SPACE| ENTR |    |      |      |      |      |      |
 *            |      |      |      |[CTRL]|      |    |      |      |      |      |      |
 *            `----------------------------------'    `----------------------------------'
 */
    [_GAMING] = LAYOUT_kyria_custom_wrapper(
      KC_ESC ,         KC_5, KC_1, KC_2, KC_3, KC_4,  ________________BLANK________________, _______,
      KC_TAB ,         KC_T, KC_Q, KC_W, KC_E, KC_R,  ________________BLANK________________, _______,
      _______,         KC_G, KC_A, KC_S, KC_D, KC_D,  ________________BLANK________________, _______,
                              DF(_COLEMAK), _______,  _______, DF(_COLEMAK),
_______, _______, _______, KC_LALT, CTL_T(KC_SPACE),  ________________BLANK________________
    ),

/*
 * Lower Layer: Symbols
 *
 * ,--------. ,----------------------------------.    ,----------------------------------. ,--------.
 * |        | |   !  |   @  |   {  |   }  |   |  |    |      |   \  |   ;  |      |      | |        |
 * |--------| |------+------+------+------+------|    |------+------+------+------+------| |--------|
 * |    "   | |   #  |   $  |   (  |   )  |   `  |    |   +  |   -  |   :  |   *  |   ?  | |    '   |
 * |--------| |------+------+------+------+------|    |------+------+------+------+------| |--------|
 * |        | |   %  |   ^  |   [  |   ]  |   ~  |    |   &  |   =  |   _  |   _  |   /  | |        |
 * `--------' `----------------------------------'    `----------------------------------' `--------'
 */
    [_SYMB] = LAYOUT_kyria_custom_wrapper(
      _______, ________________SYMB_L1______________,  ________________SYMB_R1______________, _______,
      KC_DQUO, ________________SYMB_L2______________,  ________________SYMB_R2______________, KC_QUOT,
      _______, ________________SYMB_L3______________,  ________________SYMB_R3______________, _______,
                            ______________BLANK_THUMBS_CLUSTER_____________
    ),
/*
 * Raise Layer: Number keys, media, navigation
 *
 * ,--------. ,----------------------------------.    ,----------------------------------. ,--------.
 * |        | |   1  |   2  |   3  |   4  |   5  |    |   6  |   7  |   8  |   9  |   0  | |        |
 * |--------| |------+------+------+------+------|    |------+------+------+------+------| |--------|
 * |        | |      |   玲 |     |   怜 |     |    |      |   ←  |   ↓  |   ↑  |   →  | |        |
 * |--------| |------+------+------+------+------|    |------+------+------+------+------| |--------|
 * |        | |      |      |      |     |     |    |      |   ← |   ↓ |   ↑ |   → | |        |
 * `--------' `----------------------------------'    `----------------------------------' `--------'
 */
    [_NUM] = LAYOUT_kyria_custom_wrapper(
      _______, _______________NUM_LEFT______________,  _______________NUM_RIGHT_____________, _______,
      _______, _______________MUSIC_1_______________,  _______________ARROWS________________, _______,
      _______, _______________MUSIC_2_______________,  ________________MOUSE________________, _______,
                            /*______________BLANK_THUMBS_CLUSTER_____________*/
                                    _______, _______,   _______, _______, \
        _______, _______, _______, _______, MO(_NUM),   MO(_NUM), _______, _______, _______, _______
    ),
/*
 * Adjust Layer: Function keys, RGB
 *
 * ,--------. ,----------------------------------.    ,----------------------------------. ,--------.
 * |        | |  F1  |  F2  |  F3  |  F4  |  F5  |    |  F6  |  F7  |  F8  |  F9  | F10  | |        |
 * |--------| |------+------+------+------+------|    |------+------+------+------+------| |--------|
 * |        | |  TOG |  SA↑ |  HU↑ |  VA↑ |  MOD |    |      |      |      |      |      | |        |
 * |--------| |------+------+------+------+------|    |------+------+------+------+------| |--------|
 * |        | |      |  SA↓ |  HU↓ |  VA↓ | RMOD |    |      |      |      |      |      | |        |
 * `--------' `----------------------------------'    `----------------------------------' `--------'
 */
    [_CONFIG] = LAYOUT_kyria_custom_wrapper(
      _______, ______________FUNC_LEFT______________,  ______________FUNC_RIGHT_____________, _______,
      _______, ________________RGB_1________________,  ________________BLANK________________, _______,
      _______, ________________RGB_2________________,  ________________BLANK________________, _______,
                            ______________BLANK_THUMBS_CLUSTER_____________
    ),
};

/* ────────────────────── RGB color layers definition ─────────────────────── */
#ifdef RGBLIGHT_LAYERS
const rgblight_segment_t PROGMEM rgb_colemak_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 20, HS_WHITE}
);
const rgblight_segment_t PROGMEM rgb_gaming_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 20, HS_RED}
);
const rgblight_segment_t PROGMEM rgb_symbols_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 20, HS_BLUE}
);
const rgblight_segment_t PROGMEM rgb_numbers_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 20, HS_GREEN}
);
const rgblight_segment_t PROGMEM rgb_config_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 20, HS_PURPLE}
);
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

const rgblight_segment_t* const PROGMEM rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    rgb_colemak_layer,
    rgb_gaming_layer,
    rgb_symbols_layer,
    rgb_numbers_layer,
    rgb_config_layer,
    rgb_alt_layer,
    rgb_ctrl_layer,
    rgb_shift_layer
);
#endif // RGBLIGHT_LAYERS

void keyboard_post_init_keymap(void) {
#ifdef RGBLIGHT_LAYERS
    rgblight_layers = rgb_layers;
    debug_enable=true;
#endif // RGBLIGHT_LAYERS
}

bool led_update_keymap(led_t led_state) {
#ifdef RGBLIGHT_LAYERS
    rgblight_set_layer_state(__LAST, get_mods() & MOD_MASK_ALT);
    rgblight_set_layer_state(__LAST + 1, get_mods() & MOD_MASK_CTRL);
    rgblight_set_layer_state(__LAST + 2, get_mods() & MOD_MASK_SHIFT);
#endif // RGBLIGHT_LAYERS
    return true;
}

// vim: textwidth=101
