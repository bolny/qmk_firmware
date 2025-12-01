/* Copyright 2015-2017 Jack Humbert
 * Copyright 2022-2024 Brendon O'Laney (@bolny) <brendon@brendonolaney.com>
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
 *
 */

 /*
  * Compile with
  * qmk flash -kb planck/rev7 -km bolny
  *
  * TODO: figure out how to turn off audio and get RGB Working again.
  *
  * This is a planck EZ but I don't want to use the crippled JSON
  * configuration that ZSA is using.
  */

#include QMK_KEYBOARD_H

bool mjig = false;
int counter = 0;

enum planck_layers {
    _BASE,
    _NAV,
    _NUM,
    _SYM,
    _FNC,
    _ADJ
};

enum planck_keycodes {
    MJIG = SAFE_RANGE,
};

#define NAV MO(_NAV)
#define NUM MO(_NUM)
#define SYM MO(_SYM)
#define FNC MO(_FNC)
#define ADJ MO(_ADJ)


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* BASE
    * ,-----------------------------------------------------------------------------------.
    * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * | Ctrl |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  | Enter|
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  | Shift|
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * | Esc  | Alt  | GUI  | Nav  | Num  |    Space    | Sym  | Fn   | GUI  | Alt  | \    |
    * `-----------------------------------------------------------------------------------'
    * There's an extra key in the layout because my specific keyboard has a double wide space.
    */
    [_BASE] = LAYOUT_planck_grid(
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
        KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_ENT,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
        KC_ESC,  KC_LALT, KC_LGUI, NAV,     NUM,         KC_SPC,       SYM,     FNC,     KC_RGUI, KC_RALT, KC_BSLS,
        XXXXXXX
    ),

    /* NAV
    * ,-----------------------------------------------------------------------------------.
    * | Tab  | Wh U |      | M Up |      |      | PgUp | PgDn | Home | End  |  Del | Bksp |
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * | Ctrl | Wh D | M Lf | M Dn | M Rt |      | Left | Down |  Up  | Right|  Ins | Enter|
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * | Shift|      | Spd0 | Spd1 | Spd2 |      |  M5  |  M1  |  M2  |  M3  |  M4  | Shift|
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * | Esc  | Alt  | GUI  | Nav  | Num  |    Space    | Sym  | Fn   | GUI  | Alt  | \    |
    * `-----------------------------------------------------------------------------------'
    */
    [_NAV] = LAYOUT_planck_grid(
        _______, MS_WHLU, XXXXXXX, MS_UP,   XXXXXXX, XXXXXXX, KC_PGUP, KC_PGDN, KC_HOME, KC_END,  KC_DEL,  _______,
        _______, MS_WHLD, MS_LEFT, MS_DOWN, MS_RGHT, XXXXXXX, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_INS,  _______,
        _______, XXXXXXX, MS_ACL0, MS_ACL1, MS_ACL2, XXXXXXX, MS_BTN5, MS_BTN1, MS_BTN2, MS_BTN3, MS_BTN4, _______,
        _______, _______, _______, _______, _______,     _______,      _______, _______, _______, _______, _______,
        _______
     ),

    /* NUM
    * ,-----------------------------------------------------------------------------------.
    * | Tab  |   ~  |   `  |   '  |   "  |      |      |   -  |   _  |   =  |   +  | Bksp |
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * | Ctrl |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  |Enter |
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * | Shift|      |      |      |      |      |      |      |      |   .  |   /  |Shift |
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * | Esc  | Alt  | GUI  | Nav  | Num  |    Space    | Sym  | Fn   | GUI  | Alt  | \    |
    * `-----------------------------------------------------------------------------------'
    */
    [_NUM] = LAYOUT_planck_grid(
        _______, KC_TILD, KC_GRV,  KC_QUOT, KC_DQUO, XXXXXXX, XXXXXXX, KC_MINS, KC_UNDS, KC_EQL,  KC_PLUS, _______,
        _______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______,
        _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_DOT,  KC_SLSH, _______,
        _______, _______, _______, _______, _______,     _______,      _______, _______, _______, _______, _______,
        _______
    ),

    /* SYM
    * ,-----------------------------------------------------------------------------------.
    * | Tab  |   ~  |   `  |   '  |   "  |      |      |   {  |   }  |   [  |   ]  | Bksp |
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * | Ctrl |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  |Enter |
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * | Shift|      |      |      |      |      |      |      |      |      |      |Shift |
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * | Esc  | Alt  | GUI  | Nav  | Num  |    Space    | Sym  | Fn   | GUI  | Alt  | \    |
    * `-----------------------------------------------------------------------------------'
    */
    [_SYM] = LAYOUT_planck_grid(
        _______, KC_TILD, KC_GRV,  KC_QUOT, KC_DQUO, XXXXXXX, XXXXXXX, KC_LCBR, KC_RCBR, KC_LBRC, KC_RBRC, _______,
        _______, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, _______,
        _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
        _______, _______, _______, _______, _______,     _______,      _______, _______, _______, _______, _______,
        _______
    ),

    /* Function
    * ,-----------------------------------------------------------------------------------.
    * | Tab  |  F11 |  F12 |      |      |      |      |      |PrScr |ScrLk |Pause | Bksp |
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * | Ctrl |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  |  F10 |Enter |
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * | Shift|NumLk |CapLk |      |      |      |      |      |      |      |      |Shift |
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * | Esc  | Alt  | GUI  | Nav  | Num  |    Space    | Sym  | Fn   | GUI  | Alt  | \    |
    * `-----------------------------------------------------------------------------------'
    */
    [_FNC] = LAYOUT_planck_grid(
        _______, KC_F11,  KC_F12,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_PSCR, KC_SCRL, KC_PAUS, _______,
        _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  _______,
        _______, KC_NUM,  KC_CAPS, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
        _______, _______, _______, _______, _______,     _______,      _______, _______, _______, _______, _______,
        _______
    ),

    /* Adjust
    * ,-----------------------------------------------------------------------------------.
    * |      |      |      |      | Reset|      |      |EEPRes|      |      |      |      |
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * |      |      |Aud on|Audoff|Audtog|      |      | RGB  |Brght+|Brght-|      |      |
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * |      |      |Mus on|Musoff|Mustog|      |      |RGBMod| Hue+ | Hue- |      |      |
    * |------+------+------+------+------+------+------+------+------+------+------+------|
    * |      |      |      |      |      |             |      |      |      |      |      |
    * `-----------------------------------------------------------------------------------'
    */
    [_ADJ] = LAYOUT_planck_grid(
        _______, MJIG,    XXXXXXX, XXXXXXX, QK_BOOT, XXXXXXX, XXXXXXX, EE_CLR,  XXXXXXX, XXXXXXX, XXXXXXX, _______,
        _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
        _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
        _______, _______, _______, _______, _______,     _______,      _______, _______, _______, _______, _______,
        _______
    ),
};

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _NUM, _SYM, _ADJ);
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
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
        tap_code(MS_UP);
        tap_code(MS_DOWN);
    }
    counter++;
    if (counter >= 3600) counter = 0;
}


