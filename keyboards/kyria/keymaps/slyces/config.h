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
  // RGB too bright cause power issues
  #define RGBLIGHT_LIMIT_VAL 180
  #define RGBLIGHT_ANIMATIONS
  #define RGBLIGHT_SPLIT
  #define RGBLIGHT_LAYERS
#endif

// Flash right/left with dfu-split-right/left
#define EE_HANDS

/* ───────────────────────────────────────────── Original LED numbering ───────────────────────────────────────────── */
/*                  [back of right side]                                           [back of left side]
 *        ___--------------------------------__                           __--------------------------------___
 *  ___---                       ┌────┐        --_____             _____--        ┌────┐                       ---___
 * | ┌────┐  ┌────┐              │ 14 │     ┌────┐    \           /    ┌────┐     │ 04 │              ┌────┐  ┌────┐ |
 * | │ 19 │  │ 15 │              └────┘     │ 13 │     |         |     │ 03 │     └────┘              │ 05 │  │ 09 │ |
 * | └────┘  └────┘                         └────┘     |         |     └────┘                         └────┘  └────┘ |
 * |                                                   |         |                                                   |
 * | ┌────┐  ┌────┐                                    |         |                                    ┌────┐  ┌────┐ |
 * | │ 18 │  │ 16 │   ┌────┐     ┌────┐     ┌────┐     |         |     ┌────┐     ┌────┐     ┌────┐   │ 06 │  │ 08 │ |
 * | └────┘  └────┘   │ 17 │     │ 12 │     │ 11 │      \_     _/      │ 01 │     │ 02 │     │ 07 │   └────┘  └────┘ |
 * |_______________   └────┘     └────┘     └────┘ ┌────┐ \_ _/ ┌────┐ └────┘     └────┘     └────┘   _______________|
 *                 |_________________________      │ 10 │  / \  │ 00 │      _________________________|
 *                                           --__  └────┘ /   \ └────┘  __--
 *                                               --__    /     \    __--
 *                                                   \__/       \__/                                                  */
/* ──────────────────────────────────────────── Reordered LED numbering ───────────────────────────────────────────── */
/*                  [back of right side]                                           [back of left side]
 *        ___--------------------------------__                           __--------------------------------___
 *  ___---                       ┌────┐        --_____             _____--        ┌────┐                       ---___
 * | ┌────┐  ┌────┐           →  │ 18 │     ┌────┐    \           /    ┌────┐    ↙│ 08 │  ←           ┌────┐  ┌────┐ |
 * | │ 16 │ →│ 17 │ ↗            └────┘  →  │ 19 │     |         |     │ 09 │ ←   └────┘            ↖ │ 07 │← │ 06 │ |
 * | └────┘  └────┘                         └────┘     |         |     └────┘                         └────┘  └────┘ |
 * |   ↑                                               |         |                                               ↑   |
 * | ┌────┐  ┌────┐                                    |         |                                    ┌────┐  ┌────┐ |
 * | │ 15 │ ←│ 14 │ ↖ ┌────┐     ┌────┐     ┌────┐     |         |     ┌────┐     ┌────┐     ┌────┐ ↗ │ 04 │→ │ 05 │ |
 * | └────┘  └────┘   │ 13 │  ←  │ 12 │  ←  │ 11 │      \_     _/      │ 01 │  →  │ 02 │  →  │ 03 │   └────┘  └────┘ |
 * |_______________   └────┘     └────┘     └────┘↖┌────┐ \_ _/ ┌────┐↗└────┘     └────┘     └────┘   _______________|
 *                 |_________________________      │ 10 │  / \  │ 00 │      _________________________|
 *                                           --__  └────┘ /   \ └────┘  __--
 *                                               --__    /     \    __--
 *                                                   \__/       \__/                                                 */
#define RGBLIGHT_LED_MAP { 0, 1, 2, 9, 8, 7, 4, 3, 5, 6, 10, 11, 12, 19, 18, 17, 14, 13, 15, 16 }
