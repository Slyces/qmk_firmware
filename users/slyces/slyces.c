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

/* ───────────────────────────── keyboard init ────────────────────────────── */
// pre-init
__attribute__((weak))
void keyboard_pre_init_keymap(void) {}

void keyboard_pre_init_user(void) {
    keyboard_pre_init_keymap();
}

// post-init
__attribute__((weak))
void keyboard_post_init_keymap(void) {}

void keyboard_post_init_user(void) {
#if defined(RGBLIGHT_ENABLE)
    keyboard_post_init_rgb();
#endif
    keyboard_post_init_keymap();
}

/* ────────────────────────────── matrix init ─────────────────────────────── */
__attribute__((weak))
void matrix_init_keymap(void) {}

void matrix_init_user(void) {
    matrix_init_keymap();
}

/* ────────────────────────────── matrix scan ─────────────────────────────── */
__attribute__((weak))
void matrix_scan_keymap(void) {}

void matrix_scan_user(void) {
#if defined(RGBLIGHT_ENABLE)
    matrix_scan_rgb();
#endif  // RGBLIGHT_ENABLE
    matrix_scan_keymap();
}

/* ──────────────────────────── layer state set ───────────────────────────── */
__attribute__((weak))
layer_state_t layer_state_set_keymap(layer_state_t state) {
    return state;
}

layer_state_t layer_state_set_user(layer_state_t state) {
#if defined(RGBLIGHT_ENABLE)
    layer_state_set_rgb(state);
#endif  // RGBLIGHT_ENABLE
    return layer_state_set_keymap(state);
}

/* ──────────────────────── default layer state set ───────────────────────── */
__attribute__((weak))
layer_state_t default_layer_state_set_keymap(layer_state_t state) {
    return state;
}

// Runs state check and changes underglow color and animation
layer_state_t default_layer_state_set_user(layer_state_t state) {
#ifdef RGBLIGHT_ENABLE
    default_layer_state_set_rgb(state);
#endif // RGBLIGHT_ENABLE
    return default_layer_state_set_keymap(state);
}

/* ──────────────────────────────── led set ───────────────────────────────── */
__attribute__((weak))
void led_set_keymap(uint8_t usb_led) {}

void led_set_user(uint8_t usb_led) {
    led_set_keymap(usb_led);
}

/* ─────────────────────────────── led update ─────────────────────────────── */
__attribute__((weak))
bool led_update_keymap(led_t led_state) {
    return true;
}

bool led_update_user(led_t led_state) {
    return led_update_keymap(led_state);
}

