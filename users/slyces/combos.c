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
#include "combos.h"

/* ─────────────────────────── combos definition ──────────────────────────── */
const uint16_t PROGMEM ei_combo[] = {LT(_SYMB, KC_E), LT(_NUM, KC_I), COMBO_END};
const uint16_t PROGMEM rs_combo[] = {LT(_NUM, KC_R), LT(_SYMB, KC_S), COMBO_END};
const uint16_t PROGMEM ne_combo[] = {KC_N, LT(_SYMB, KC_E), COMBO_END};
const uint16_t PROGMEM st_combo[] = {LT(_SYMB, KC_S), KC_T, COMBO_END};

/* ────────────────────────────── combos list ─────────────────────────────── */
combo_t key_combos[COMBO_COUNT] = {
  [HOME_RIGHT_ESC] = COMBO(ei_combo, KC_ESC),
  [HOME_LEFT_ESC] = COMBO(rs_combo, KC_ESC),
  [HOME_RIGHT_SFT] = COMBO_ACTION(ne_combo),
  [HOME_LEFT_SFT] = COMBO_ACTION(st_combo),
};

void process_combo_event(uint16_t combo_index, bool pressed) {
  switch(combo_index) {
    case HOME_LEFT_SFT:
    case HOME_RIGHT_SFT:
      if (pressed) {
          set_oneshot_mods(MOD_LSFT);
      }
      break;
  }
}
