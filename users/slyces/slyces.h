/* Copyright 2019 Simon Lassourreuille <slyces.coding@gmail.com>
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
#include QMK_KEYBOARD_H

// Always included files
#include "wrappers.h"
#include "process_records.h"

#ifdef COMBO_ENABLE
#    include "combos.h"
#endif  // TAP_DANCE_ENABLE

#ifdef TAP_DANCE_ENABLE
#    include "tap_dances.h"
#endif  // TAP_DANCE_ENABLE

#ifdef RGBLIGHT_ENABLE
#    include "rgb_stuff.h"
#endif  // RGBLIGHT_ENABLE

/* ─────────────────── define UK variants of symbol keys ──────────────────── */
#ifdef UK_LAYOUT
#    include "keymap_uk.h"
#endif


/* ──────────────────── define [userspace] layers names ───────────────────── */
enum userspace_layers {
    _COLEMAK = 0,
    _GAMING,
    _SYMB,
    _NUM,
    _CONFIG,
    __LAST
};

enum layer_thresholds {
    __LAST_DEFAULT = _SYMB
};

/* ─────────────────────── user and keymap functions ──────────────────────── */
void          matrix_init_keymap(void);
void          matrix_scan_keymap(void);
layer_state_t layer_state_set_keymap(layer_state_t state);
layer_state_t default_layer_state_set_keymap(layer_state_t state);
void          led_set_keymap(uint8_t usb_led);
bool          led_update_keymap(led_t led_state);
bool          process_record_keymap(uint16_t keycode, keyrecord_t *record);
