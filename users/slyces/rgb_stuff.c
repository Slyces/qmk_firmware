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
#include "rgb_stuff.h"
#include <print.h>


/* ────────────────────────────── matrix scan ─────────────────────────────── */
void matrix_scan_rgb(void) {
#ifdef RGBLIGHT_LAYERS
    led_update_user(host_keyboard_led_state());
#endif // RGBLIGHT_LAYERS
}

/* ───────────────────────────── keyboard init ────────────────────────────── */
void keyboard_post_init_rgb(void) {
    rgblight_enable_noeeprom();
    rgblight_sethsv(rgblight_get_hue(), rgblight_get_sat(), 80);
    default_layer_state_set_rgb(default_layer_state);
}

/* ──────────────────────────── layer state set ───────────────────────────── */
void layer_state_set_rgb(uint32_t state) {
#ifdef RGBLIGHT_LAYERS
    // Last default layer is also the first normal layer
    for (int i = __LAST_DEFAULT; i < __LAST; i++) {
        rgblight_set_layer_state(i, layer_state_cmp(state, i));
    }
    default_layer_state_set_rgb(default_layer_state);
#else
    uint8_t val = rgblight_get_val();
    switch (biton32(state)) {
        case _SYMB:
            rgblight_sethsv_noeeprom(HS_BLUE, val); break;
        case _NUM:
            rgblight_sethsv_noeeprom(HS_GREEN, val); break;
        case _CONFIG:
            rgblight_sethsv_noeeprom(HS_PURPLE, val); break;
        default:
            default_layer_state_set_rgb(default_layer_state); break;
    }
#endif // RGBLIGHT_LAYERS
}

/* ──────────────────────── default layer state set ───────────────────────── */
void default_layer_state_set_rgb(uint32_t default_state) {
#ifdef RGBLIGHT_LAYERS
    // Default layers
    for (int i = 0; i < __LAST_DEFAULT; i++) {
        rgblight_set_layer_state(i, layer_state_cmp(default_state, i));
    }
#else
    uint8_t val = rgblight_get_val();
    switch (biton32(default_state)) {
        case _COLEMAK:
            rgblight_sethsv_noeeprom(HS_WHITE, val); break;
        case _GAMING:
            rgblight_sethsv_noeeprom(HS_RED, val); break;
        default:
            rgblight_sethsv_noeeprom(HS_WHITE, val); break;
    }
#endif // ! RGBLIGHT_LAYERS
}
