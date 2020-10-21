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

/* ──────────────────────────── UK vs US layout ───────────────────────────── */
#define UK_LAYOUT

/* ───────────────────────────── combos options ───────────────────────────── */
#ifdef COMBO_ENABLE
    #define COMBO_COUNT 1
    #define COMBO_TERM 150
#endif

/* ──────────────────────────── mod tap options ───────────────────────────── */
#ifdef TAP_DANCE_ENABLE
    #define TAPPING_TERM_PER_KEY
    #define TAPPING_TERM 225
    #define IGNORE_MOD_TAP_INTERRUPT
    #define PERMISSIVE_HOLD
#endif

/* ────────────────────────── generic RGB options ─────────────────────────── */
#ifdef RGBLIGHT_ENABLE
    // RGB steps for manual color/intendity change
    #define RGBLIGHT_HUE_STEP 8
    #define RGBLIGHT_SAT_STEP 8
    #define RGBLIGHT_VAL_STEP 8
#endif

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

/* ───────────────────────── saving firmware space ────────────────────────── */
#ifdef LOCKING_SUPPORT_ENABLE
#    undef LOCKING_SUPPORT_ENABLE
#endif
#ifdef LOCKING_RESYNC_ENABLE
#    undef LOCKING_RESYNC_ENABLE
#endif

