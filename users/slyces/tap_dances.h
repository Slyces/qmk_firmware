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
#include "slyces.h"

/* ---------------------------- tap dance states ---------------------------- */
enum {
    SINGLE_TAP = 1,
    SINGLE_HOLD,
    DOUBLE_TAP
};

/* -------------------------- tap dance structures -------------------------- */
typedef struct {
    bool is_press_action;
    uint8_t state;
} tap;

/* -------------------------------- keycodes -------------------------------- */
enum td_keycodes {
    TD_MOVE,
    TD_SCOL
};


/* ------------------------------- functions -------------------------------- */
// Move → key
void mv_finished(qk_tap_dance_state_t *state, void *user_data);
void mv_reset(qk_tap_dance_state_t *state, void *user_data);

// Shift
void sft_finished(qk_tap_dance_state_t *state, void *user_data);
void sft_reset(qk_tap_dance_state_t *state, void *user_data);

/* --------------------------------- utils ---------------------------------- */
uint8_t cur_dance(qk_tap_dance_state_t *state);
