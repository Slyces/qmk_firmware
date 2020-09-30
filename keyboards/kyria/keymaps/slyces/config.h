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

#pragma once

#ifdef RGBLIGHT_ENABLE
  // RGB steps for manual color/intendity change
  #define RGBLIGHT_HUE_STEP 8
  #define RGBLIGHT_SAT_STEP 8
  #define RGBLIGHT_VAL_STEP 8
  // RGB too bright cause power issues
  #define RGBLIGHT_LIMIT_VAL 180
  #define RGBLIGHT_ANIMATIONS
  #define RGBLIGHT_SPLIT
  #define RGBLIGHT_LAYERS
#endif

// Home row mods
#define TAPPING_TERM 225
#define IGNORE_MOD_TAP_INTERRUPT
#define PERMISSIVE_HOLD

// Flash right/left with dfu-split-right/left
#define EE_HANDS

/* ──────────────────────────── Shortcut Macros ───────────────────────────── */
#define LTN(KC) LT(_NUM, KC)
#define LTS(KC) LT(_SYMB, KC)

/* ────────────────────── HS (Hue, Saturation) colors ─────────────────────── */
#define HS_WHITE          0,   0
#define HS_RED            0, 255
#define HS_CORAL         11, 176
#define HS_ORANGE        28, 255
#define HS_GOLDENROD     30, 218
#define HS_GOLD          36, 255
#define HS_YELLOW        43, 255
#define HS_CHARTREUSE    64, 255
#define HS_GREEN         85, 255
#define HS_SPRINGGREEN  106, 255
#define HS_TURQUOISE    123,  90
#define HS_TEAL         128, 255
#define HS_CYAN         128, 255
#define HS_AZURE        132, 102
#define HS_BLUE         170, 255
#define HS_PURPLE       191, 255
#define HS_MAGENTA      213, 255
#define HS_PINK         234, 128

/* ─────────────────────────────── LED Layout ─────────────────────────────── */

/* Back of LEFT half, order of the leds on the PCB
 *                __--------------------------------___
 *         _____--        ┌───┐                        ---___
 *        /     ┌───┐     │ 4 │               ┌───┐    ┌───┐ |
 *       |      │ 3 │     └───┘               │ 5 │    │ 9 │ |
 *       |      └───┘                         └───┘    └───┘ |
 *       |                                                   |
 *       |                                    ┌───┐    ┌───┐ |
 *       |      ┌───┐     ┌───┐      ┌───┐    │ 6 │    │ 8 │ |
 *     _/       │ 1 │     │ 2 │      │ 7 │    └───┘    └───┘ |
 *   _/  ┌───┐  └───┘     └───┘      └───┘    _______________|
 *   \   │ 0 │      _________________________|
 *    \  └───┘  __--
 *     \    __--
 *      \__/
 *
 * Redefining this for an easier to remember layout
 *                __--------------------------------___
 *         _____--        ┌───┐                        ---___
 *        /     ┌───┐     │ 8 │               ┌───┐    ┌───┐ |
 *       |      │ 9 │     └───┘               │ 7 │    │ 6 │ |
 *       |      └───┘                         └───┘    └───┘ |
 *       |                                                   |
 *       |                                    ┌───┐    ┌───┐ |
 *       |      ┌───┐     ┌───┐      ┌───┐    │ 4 │    │ 5 │ |
 *     _/       │ 1 │     │ 2 │      │ 3 │    └───┘    └───┘ |
 *   _/  ┌───┐  └───┘     └───┘      └───┘    _______________|
 *   \   │ 0 │      _________________________|
 *    \  └───┘  __--
 *     \    __--
 *      \__/
 * */
#define RGBLIGHT_LED_MAP { 0, 1, 2, 9, 8, 7, 4, 3, 5, 6, 10, 11, 12, 19, 18, 17, 14, 13, 15, 16 }
