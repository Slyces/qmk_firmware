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
#include "tap_dances.h"

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

static tap mv_state = {
    .is_press_action = true,
    .state = 0
};
static tap sft_state = {
    .is_press_action = true,
    .state = 0
};

/* ──────────────────────── tapping terms - per key ───────────────────────── */
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case SFT_T(KC_O):
            return TAPPING_TERM + 125;
        case SFT_T(KC_A):
            return TAPPING_TERM + 125;
        default:
            return TAPPING_TERM;
    }
}

/* ────────────────────────── tap dance functions ─────────────────────────── */
// Functions that control what our tap dance key does
void mv_finished(qk_tap_dance_state_t *state, void *user_data) {
    mv_state.state = cur_dance(state);
    switch (mv_state.state) {
        case SINGLE_HOLD:  // Hold → CTRL
            layer_on(_NUM);
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

void mv_reset(qk_tap_dance_state_t *state, void *user_data) {
    // If the key was held down and now is released then switch off the mod
    switch (mv_state.state) {
        case SINGLE_TAP: break;
        case SINGLE_HOLD: layer_off(_NUM); break;
        case DOUBLE_TAP: break;
    }
    mv_state.state = 0;
}

// Functions that control what our tap dance key does
void sft_finished(qk_tap_dance_state_t *state, void *user_data) {
    sft_state.state = cur_dance(state);
    switch (sft_state.state) {
        case SINGLE_HOLD: register_code(KC_LSFT); break;
        case SINGLE_TAP: register_code16(KC_COLN); break;
    }
}

void sft_reset(qk_tap_dance_state_t *state, void *user_data) {
    // If the key was held down and now is released then switch off the mod
    switch (sft_state.state) {
        case SINGLE_HOLD: unregister_code(KC_LSFT); break;
        case SINGLE_TAP: unregister_code16(KC_COLN); break;
    }
    sft_state.state = 0;
}

// Associate our tap dance key with its functionality
qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_MOVE] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, mv_finished, mv_reset),
    [TD_SCOL] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, sft_finished, sft_reset),
};
