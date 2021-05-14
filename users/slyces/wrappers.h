/* Copyright 2020 Simon Lassourreuille <slyces.coding@gmail.com>
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
#include "slyces.h"

/* Since our quirky block definitions are basically a list of comma separated
 * arguments, we need a wrapper in order for these definitions to be expanded
 * before being used as arguments to the LAYOUT_xxx macro.
 */
#if (!defined(LAYOUT) && defined(KEYMAP))
#    define LAYOUT KEYMAP
#endif

// clang-format off
#define KEYMAP_wrapper(...)                  LAYOUT(__VA_ARGS__)
#define LAYOUT_wrapper(...)                  LAYOUT(__VA_ARGS__)

/* ───────────────────────────────────────── Blank ───────────────────────────────────────── */
#define ________________BLANK________________        _______, _______, _______, _______, _______

/* ─────────────────────────────────── Homerow Modifiers ─────────────────────────────────── */
/*        ,----------------------------------.    ,----------------------------------.
 *  LEFT  | SHFT |  NUM | SYMB |      |      |    |      |      | SYMB |  NUM | SHFT |  RIGHT
 *        `----------------------------------'    `----------------------------------'
 */
// Note: those are functions that can be applied to any ___LAYOUT_L2___ / ___LAYOUT_R2___
#define HOMEROW_LEFT(X1, X2, X3, X4, X5)   SFT_T(X1), LT(_NUM, X2), LT(_SYMB, X3), X4, X5
#define HOMEROW_RIGHT(X1, X2, X3, X4, X5)  X1, X2, LT(_SYMB, X3), LT(_NUM, X4), SFT_T(X5)

#define HM_LEFT_wrapper(...)   HOMEROW_LEFT(__VA_ARGS__)
#define HM_RIGHT_wrapper(...)  HOMEROW_RIGHT(__VA_ARGS__)

/* ──────────────────────────────────────── Qwerty ───────────────────────────────────────── */
/*        ,----------------------------------.    ,----------------------------------.
 *    L1  |   Q  |   W  |   E  |   R  |   T  |    |   Y  |   U  |   I  |   O  |   P  |  R1
 *        |------+------+------+------+------|    |------+------+------+------+------|
 *    L2  |   A  |   S  |   D  |   F  |   G  |    |   H  |   J  |   K  |   L  |  ; : |  R2
 *        |------+------+------+------+------|    |------+------+------+------+------|
 *    L3  |   Z  |   X  |   C  |   V  |   B  |    |   N  |   M  |  , < |  . > |  / ? |  R3
 *        `----------------------------------'    `----------------------------------'
 */
#define ______________QWERTY_L1______________     KC_Q,    KC_W,    KC_E,    KC_R,    KC_T
#define ______________QWERTY_L2______________     KC_A,    KC_S,    KC_D,    KC_F,    KC_G
#define ______________QWERTY_L3______________     KC_Z,    KC_X,    KC_C,    KC_V,    KC_B

#define ______________QWERTY_R1______________     KC_Y,    KC_U,    KC_I,    KC_O,    KC_P
#define ______________QWERTY_R2______________     KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN
#define ______________QWERTY_R3______________     KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLASH

/* ────────────────────────────────────── Colemak Dhm ────────────────────────────────────── */
/*        ,----------------------------------.    ,----------------------------------.
 *    L1  |   Q  |   W  |   F  |   P  |   B  |    |   J  |   L  |   U  |   Y  |  ; : |  R1
 *        |------+------+------+------+------|    |------+------+------+------+------|
 *    L2  |   A  |   R  |   S  |   T  |   G  |    |   M  |   N  |   E  |   I  |   O  |  R2
 *        |------+------+------+------+------|    |------+------+------+------+------|
 *    L3  |   Z  |   X  |   C  |   D  |   V  |    |   K  |   H  |  , < |  . > |  / ? |  R3
 *        `----------------------------------'    `----------------------------------'
 */
#define ____________COLEMAK_DHM_L1___________     KC_Q,    KC_W,    KC_F,    KC_P,    KC_B
#define ____________COLEMAK_DHM_L2___________     KC_A,    KC_R,    KC_S,    KC_T,    KC_G
#define ____________COLEMAK_DHM_L3___________     KC_Z,    KC_X,    KC_C,    KC_D,    KC_V

#define ____________COLEMAK_DHM_R1___________     KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN
#define ____________COLEMAK_DHM_R2___________     KC_M,    KC_N,    KC_E,    KC_I,    KC_O
#define ____________COLEMAK_DHM_R3___________     KC_K,    KC_H,    KC_COMM, KC_DOT,  KC_SLSH

#define ________COLEMAK_Dhm_HMOD_LEFT________     HM_LEFT_wrapper(____________COLEMAK_DHM_L2___________)
#define ________COLEMAK_Dhm_HMOD_RIGHT_______     HM_RIGHT_wrapper(____________COLEMAK_DHM_R2___________)

/* ──────────────────────────────────────── Symbols ──────────────────────────────────────── */
/*        ,----------------------------------.    ,----------------------------------.
 *    L1  |   !  |   @  |   {  |   }  |   |  |    |      |   \  |   ;  |      |      |  R1
 *        |------+------+------+------+------|    |------+------+------+------+------|
 *    L2  |   #  |   $  |   (  |   )  |   `  |    |   +  |   -  |   :  |   *  |   ?  |  R2
 *        |------+------+------+------+------|    |------+------+------+------+------|
 *    L3  |   %  |   ^  |   [  |   ]  |   ~  |    |   &  |   =  |   _  |   _  |   /  |  R3
 *        `----------------------------------'    `----------------------------------'
 */
#define ________________SYMB_L1______________     KC_EXLM, UK_AT,   KC_LCBR, KC_RCBR, UK_PIPE
#define ________________SYMB_L2______________     UK_HASH, KC_DLR,  KC_LPRN, KC_RPRN, KC_GRV
#define ________________SYMB_L3______________     KC_PERC, KC_CIRC, KC_LBRC, KC_RBRC, UK_TILD

#define ________________SYMB_R1______________     _______, UK_BSLS, KC_SCLN, _______, _______
#define ________________SYMB_R2______________     KC_PLUS, KC_MINS, KC_COLN, KC_ASTR, KC_QUES
#define ________________SYMB_R3______________     KC_AMPR, KC_EQL,  KC_UNDS, KC_UNDS, KC_SLSH

/* ──────────────────────────────────────── Numbers ──────────────────────────────────────── */
/*        ,----------------------------------.    ,----------------------------------.
 *  LEFT  |   1  |   2  |   3  |   4  |   5  |    |   6  |   7  |   8  |   9  |   0  |  RIGHT
 *        `----------------------------------'    `----------------------------------'
 */
#define _______________NUM_LEFT______________     KC_1,    KC_2,    KC_3,    KC_4,    KC_5
#define _______________NUM_RIGHT_____________     KC_6,    KC_7,    KC_8,    KC_9,    KC_0

/* ─────────────────────────────────────── Functions ─────────────────────────────────────── */
/*        ,----------------------------------.    ,----------------------------------.
 *  LEFT  |  F1  |  F2  |  F3  |  F4  |  F5  |    |  F6  |  F7  |  F8  |  F9  | F10  |  RIGHT
 *        `----------------------------------'    `----------------------------------'
 */
#define ______________FUNC_LEFT______________     KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5
#define ______________FUNC_RIGHT_____________     KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10

/* ────────────────────────────────────── Miscelanous ────────────────────────────────────── */
/*        ,----------------------------------.    ,----------------------------------.
 * MSIC_1 |      |   玲 |     |   怜 |     |    |      |   ←  |   ↓  |   ↑  |   →  |  ARROWS
 *        |------+------+------+------+------|    |------+------+------+------+------|
 * MSIC_2 |      |      |      |     |     |    |      |   ← |   ↓ |   ↑ |   → |  MOUSE
 *        |------+------+------+------+------|    |------+------+------+------+------|
 *  RGB_1 |  TOG |  SA↑ |  HU↑ |  VA↑ |  MOD |    |      |      |      |      |      |
 *        |------+------+------+------+------|    |------+------+------+------+------|
 *  RGB_2 |      |  SA↓ |  HU↓ |  VA↓ | RMOD |    |      |      |      |      |      |
 *        `----------------------------------'    `----------------------------------'
 */
#define _______________MUSIC_1_______________   _______, KC_MPRV, KC_MPLY, KC_MNXT, KC_VOLU
#define _______________MUSIC_2_______________   _______, _______, _______, KC_MUTE, KC_VOLD

#define _______________ARROWS________________   _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
#define ________________MOUSE________________   _______, KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R

#define ________________RGB_1________________   RGB_TOG, RGB_SAI, RGB_HUI, RGB_VAI, RGB_MOD
#define ________________RGB_2________________   _______, RGB_SAD, RGB_HUD, RGB_VAD, RGB_RMOD

// Drashna's config layer
//#define ______________CONFIG_L1______________   RGB_MOD, RGB_HUI, RGB_SAI, RGB_VAI, RGB_TOG
//#define ______________CONFIG_L2______________   MU_TOG , CK_TOGG, AU_ON,   AU_OFF,  CG_NORM
//#define ______________CONFIG_L3______________   RGB_RMOD,RGB_HUD,RGB_SAD, RGB_VAD, KC_RGB_T

//#define ______________CONFIG_R1______________   KC_SEC1, KC_SEC2, KC_SEC3, KC_SEC4, KC_SEC5
//#define ______________CONFIG_R2______________   CG_SWAP, QWERTY,  COLEMAK, DVORAK,  WORKMAN
//#define ______________CONFIG_R3______________   MG_NKRO, KC_MUTE, KC_VOLD, KC_VOLU, KC_MNXT
// clang-format on

// vim: textwidth=95
