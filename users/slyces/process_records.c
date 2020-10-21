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
#include "process_records.h"

/* ───────────────────────────── process record ───────────────────────────── */
bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
    return true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
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
