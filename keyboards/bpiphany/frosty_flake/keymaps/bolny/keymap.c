/* Copyright 2021 Brendon O'Laney (@bolny) <brendon@brendonolaney.com>
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

#include QMK_KEYBOARD_H

enum frosty_flake_layers {
    _BASE,
    _CAPS,
    _FNC,
};

enum planck_keycodes {
    MJIG = SAFE_RANGE,
};

bool mjig = false;
int counter = 0;

#define FNC MO(_FNC)
#define TG_CAPS TG(_CAPS)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT_tkl(\
    KC_ESC,           KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,     KC_PSCR, KC_SCRL, KC_PAUS, \
    KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,    KC_INS,  KC_HOME, KC_PGUP, \
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,    KC_DEL,  KC_END,  KC_PGDN, \
    KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,                                \
    KC_LSFT, XXXXXXX, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT,             KC_UP,            \
    KC_LCTL, KC_LALT, KC_LGUI,                            KC_SPC,                             KC_RGUI, KC_RALT, FNC,     KC_RCTL,    KC_LEFT, KC_DOWN, KC_RGHT  \
  ),
  [_CAPS] = LAYOUT_tkl(\
    _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,    _______, _______, _______, \
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,    _______, _______, _______, \
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,    _______, _______, _______, \
    KC_CAPS, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,                               \
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,             _______,          \
    _______, _______, _______,                            _______,                            _______, _______, _______, _______,    _______, _______, _______  \
  ),
  [_FNC] = LAYOUT_tkl(\
    MJIG,             TG_CAPS, XXXXXXX, XXXXXXX, XXXXXXX, KC_MPLY, KC_MSTP, KC_MPRV, KC_MNXT, XXXXXXX, KC_MUTE, KC_VOLD, KC_VOLU,    XXXXXXX, EE_CLR,  QK_BOOT, \
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_P7,   KC_P8,   KC_P9,   XXXXXXX, XXXXXXX, XXXXXXX, _______,    XXXXXXX, XXXXXXX, XXXXXXX, \
    _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_P4,   KC_P5,   KC_P6,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, \
    _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_P1,   KC_P2,   KC_P3,   XXXXXXX, XXXXXXX,          _______,                               \
    _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_P0,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          _______,             XXXXXXX,          \
    _______, _______, _______,                            _______,                            _______, _______, _______, _______,    XXXXXXX, XXXXXXX, XXXXXXX  \
  ),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch(keycode) {
        case MJIG:
            if (record->event.pressed) {
               if (mjig) {
                   mjig = false;
                   SEND_STRING("OFF");
               } else {
                   mjig = true;
                   SEND_STRING("ON");
               }
            }

            break;
    }

    return true;
}

void matrix_scan_user(void) {
    if (counter == 0 && mjig) {
        tap_code(KC_MS_UP);
        tap_code(KC_MS_DOWN);
    }
    counter++;
    if (counter >= 3600) counter = 0;
}
