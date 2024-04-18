/* Copyright 2020 Paul James
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

enum layers {
  _BASE = 0,
  _QWERTY,
  _EXTE,
  _FUNC,
  _SYM1
};

// Layers
#define QWERTY  TG(_QWERTY)
#define EXTE    MO(_EXTE)
#define FUNC    MO(_FUNC)
#define SYM1    MO(_SYM1)

// Left-hand home row mods
#define HOME_A  LGUI_T(KC_A)
#define HOME_R  LALT_T(KC_R)
#define HOME_S  LSFT_T(KC_S)
#define HOME_T  LCTL_T(KC_T)

// Right-hand home row mods
#define HOME_N  RCTL_T(KC_N)
#define HOME_E  RSFT_T(KC_E)
#define HOME_I  LALT_T(KC_I)
#define HOME_O  RGUI_T(KC_O)

// One-shot renaming
#define OS_ALT  OSM(KC_LALT)
#define OS_GUI  OSM(KC_LGUI)
#define OS_SFT  OSM(KC_LSFT)
#define OS_CTL  OSM(KC_LCTL)

// General renaming
#define SPACE   KC_SPC
#define SHIFT   KC_LSFT
#define CTRL    KC_LCTL
#define ALT     KC_LALT
#define WBACK   KC_WBAK
#define WFWRD   KC_WFWD
#define CALC    KC_CALC
#define PGUP    KC_PGUP
#define PGDN    KC_PGDN
#define HOME    KC_HOME
#define END     KC_END
#define ENTER   KC_ENT
#define PRINT   LSG(KC_S)

// Control renaming
#define FIND   C(KC_F)
#define COPY   C(KC_C)
#define PASTE  C(KC_V)
#define CUT    C(KC_X)
#define UNDO   C(KC_Z)

void keyboard_pre_init_user() {
    writePin(LED1, true);
    writePin(LED2, true);
}

void keyboard_post_init_user() {
    writePin(LED1, false);
    writePin(LED2, false);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    writePin(LED1, record->event.pressed);

    return true;
}

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (get_mods() & MOD_BIT(KC_LSFT)) { // left shift pressed
        if (clockwise) {
            tap_code16(C(KC_Z));
        } else {
            tap_code16(C(KC_Y));
        }
    } else { // normal function
       if (clockwise) {
          tap_code(KC_VOLD);
       } else {
          tap_code(KC_VOLU);
       }
    }
    return true;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    writePin(LED2, state);

    return state;
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* BASE COLEMAK
 * ,-----------------------------------------------------.    ,-----------------------------------------------------.
 * | Esc    | 1!     | 2@     | 3#     | 4$     | 5%     |    | 6^     | 7&     | 8*     | 9(     | 0)     | BkSp   |
 * |--------+--------+--------+--------+--------+--------|    |--------+--------+--------+--------+--------+--------|
 * | Tab    | Q      | W      | F      | P      | B      |    | J      | L      | U      | Y      | ;:     | Del    |
 * |--------+--------+--------+--------+--------+--------|    |--------+--------+--------+--------+--------+--------|
 * | Shift  | A      | R      | S      | T      | G      |    | M      | N      | E      | I      | O      |  '"    |
 * |--------+--------+--------+--------+--------+--------|    |--------+--------+--------+--------+--------+--------|
 * | Ctrl   | Z      | X      | C      | D      | V      |    | K      | H      | ,<     | .>     | /?     | ENTER  |
 * |--------+--------+--------+--------+--------+--------|    |--------+--------+--------+--------+--------+--------|
 * | QWERTY | ALT    |        | EXTE   |        | LSFT   |    | SPACE  |        | SYM1   | FUNC   |        |        |
 * `-----------------------------------------------------'    `-----------------------------------------------------'
 */
[_BASE] = LAYOUT_ortho_5x12(
    KC_ESC , KC_1   , KC_2   , KC_3   , KC_4   , KC_5   ,      KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , KC_DEL ,
    KC_TAB , KC_Q   , KC_W   , KC_F   , KC_P   , KC_B   ,      KC_J   , KC_L   , KC_U   , KC_Y   , KC_SCLN, KC_BSPC,
    SHIFT  , HOME_A , HOME_R , HOME_S , HOME_T , KC_G   ,      KC_M   , HOME_N , HOME_E , HOME_I , HOME_O , KC_QUOT,
    CTRL   , KC_Z   , KC_X   , KC_C   , KC_D   , KC_V   ,      KC_K   , KC_H   , KC_COMM, KC_DOT , KC_SLSH, ENTER  ,
    QWERTY , ALT    , _______, EXTE   , _______, SHIFT  ,      SPACE  , _______, SYM1   , FUNC   , _______, _______
),

/* QWERTY
 * ,-----------------------------------------------------.    ,-----------------------------------------------------.
 * | Esc    | 1!     | 2@     | 3#     | 4$     | 5%     |    | 6^     | 7&     | 8*     | 9(     | 0)     | BkSp   |
 * |--------+--------+--------+--------+--------+--------|    |--------+--------+--------+--------+--------+--------|
 * | Tab    | Q      | W      | E      | R      | T      |    | Y      | U      | I      | O      | P      | DEL    |
 * |--------+--------+--------+--------+--------+--------|    |--------+--------+--------+--------+--------+--------|
 * | Shift  | A      | S      | D      | F      | G      |    | H      | J      | K      | L      | ;:     | '"     |
 * |--------+--------+--------+--------+--------+--------|    |--------+--------+--------+--------+--------+--------|
 * | Ctrl   | Z      | X      | C      | V      | B      |    | N      | M      | ,<     | .>     | /?     | ENTER  |
 * |--------+--------+--------+--------+--------+--------|    |--------+--------+--------+--------+--------+--------|
 * | QWERTY | ALT    |        | EXTE   |        | SPACE  |    | SPACE  |        | SYM1   | FUNC   |        |        |
 * `-----------------------------------------------------'    `-----------------------------------------------------'
 */
[_QWERTY] = LAYOUT_ortho_5x12(
    KC_ESC , KC_1   , KC_2   , KC_3   , KC_4   , KC_5   ,      KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , KC_BSPC,
    KC_TAB , KC_Q   , KC_W   , KC_E   , KC_R   , KC_T   ,      KC_Y   , KC_U   , KC_I   , KC_O   , KC_P   , KC_DEL ,
    SHIFT  , KC_A   , KC_S   , KC_D   , KC_F   , KC_G   ,      KC_H   , KC_J   , KC_K   , KC_L   , KC_SCLN, KC_QUOT,
    CTRL   , KC_Z   , KC_X   , KC_C   , KC_V   , KC_B   ,      KC_N   , KC_M   , KC_COMM, KC_DOT , KC_SLSH, ENTER  ,
    QWERTY , ALT    , _______, EXTE   , _______, SPACE  ,      SPACE  , _______, SYM1   , FUNC   , _______, _______
),

/* EXTEND
 * ,----------------------------------------------------.    ,---------------------------------------------------.
 * |        |        |        |        |        |       |    |        |        |        |        |        |      |
 * |--------+--------+--------+--------+--------+-------|    |--------+--------+--------+--------+--------+------|
 * |        | `~     | BACK   | FIND   | FWD    |       |    | PGUP   | HOME   | UP     | END    | CAPS   |      |
 * |--------+--------+--------+--------+--------+-------|    |--------+--------+--------+--------+--------+------|
 * |        | LGUI   | LALT   | LSFT   | LCTL   |       |    | PGDN   | LEFT   | DOWN   | RGHT   | DEL    |      |
 * |--------+--------+--------+--------+--------+-------|    |--------+--------+--------+--------+--------+------|
 * |        | UNDO   | CUT    | COPY   |        | PASTE |    | PRINT  | BCKSPC | TAB    | APP    | ENTER  |      |
 * |--------+--------+--------+--------+--------+-------|    |--------+--------+--------+--------+--------+------|
 * |        |        |        |        |        |       |    | ENTER  |        | FUNC   |        |        |      |
 * `----------------------------------------------------'    `---------------------------------------------------'
 */
[_EXTE] = LAYOUT_ortho_5x12(
    _______, _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______, _______,
    _______, KC_GRV , WBACK  , FIND   , WFWRD  , _______,     PGUP   , HOME   , KC_UP  , END    , KC_CAPS, _______,
    _______, KC_LGUI, KC_LALT, KC_LSFT, KC_LCTL, _______,     PGDN   , KC_LEFT, KC_DOWN, KC_RGHT, KC_DEL , _______,
    _______, UNDO   , CUT    , COPY   , _______, PASTE  ,     PRINT  , KC_BSPC, KC_TAB , KC_APP , ENTER  , _______,
    _______, _______, _______, _______, _______, _______,     ENTER  , _______, FUNC   , _______, _______, _______
),

/* FUNCTION
 * ,-----------------------------------------------------.    ,-----------------------------------------------------.
 * |        |        |        |        |        |        |    |        |        |        |        |        |        |
 * |--------+--------+--------+--------+--------+--------|    |--------+--------+--------+--------+--------+--------|
 * |        | MUTE   | VOL-   | PLAY   | VOL+   |        |    | F12    | F7     | F8     | F9     |        |        |
 * |--------+--------+--------+--------+--------+--------|    |--------+--------+--------+--------+--------+--------|
 * |        | LGUI   | LALT   | LSFT   | LCTL   |        |    | F11    | F4     | F5     | F6     |        |        |
 * |--------+--------+--------+--------+--------+--------|    |--------+--------+--------+--------+--------+--------|
 * |        |        | PREV   | STOP   | NEXT   |        |    | F10    | F1     | F2     | F3     | CALC   |        |
 * |--------+--------+--------+--------+--------+--------|    |--------+--------+--------+--------+--------+--------|
 * |        |        |        |        |        |        |    |        |        |        |        |        |        |
 * `-----------------------------------------------------'    `-----------------------------------------------------'
 */
[_FUNC] = LAYOUT_ortho_5x12(
    _______, _______, _______, _______, _______, _______,      _______, _______, _______, _______, _______, _______,
    _______, KC_MUTE, KC_VOLD, KC_MPLY, KC_VOLU, _______,      KC_F12 , KC_F7  , KC_F8  , KC_F9  , _______, _______,
    _______, KC_LGUI, KC_LALT, KC_LSFT, KC_LCTL, _______,      KC_F11 , KC_F4  , KC_F5  , KC_F6  , _______, _______,
    _______, _______, KC_MPRV, KC_MSTP, KC_MNXT, _______,      KC_F10 , KC_F1  , KC_F2  , KC_F3  , CALC   , _______,
    _______, _______, _______, _______, _______, _______,      _______, _______, _______, _______, _______, _______
),

/* SYM1
 * ,-----------------------------------------------------.    ,-----------------------------------------------------.
 * |        |        |        |        |        |        |    |        |        |        |        |        |        |
 * |--------+--------+--------+--------+--------+--------|    |--------+--------+--------+--------+--------+--------|
 * |        | !      | @      | #      | :      | ;      |    | =      | 7      | 8      | 9      | +      |        |
 * |--------+--------+--------+--------+--------+--------|    |--------+--------+--------+--------+--------+--------|
 * |        | \      | |      | {      | (      | [      |    | *      | 4      | 5      | 6      | -      |        |
 * |--------+--------+--------+--------+--------+--------|    |--------+--------+--------+--------+--------+--------|
 * |        |        | _      | }      | )      | ]      |    | 0      | 1      | 2      | 3      | /      |        |
 * |--------+--------+--------+--------+--------+--------|    |--------+--------+--------+--------+--------+--------|
 * |        |        |        |        |        |        |    |        |        |        |        |        |        |
 * `-----------------------------------------------------'    `-----------------------------------------------------'
 */
[_SYM1] = LAYOUT_ortho_5x12(
    _______, _______, _______, _______, _______, _______,      _______, _______, _______, _______, _______, _______,
    _______, KC_EXLM, KC_AT  , KC_HASH, KC_COLN, KC_SCLN,      KC_EQL , KC_7   , KC_8   , KC_9   , KC_PPLS, _______,
    _______, KC_BSLS, KC_PIPE, KC_LCBR, KC_LPRN, KC_LBRC,      KC_PAST, KC_4   , KC_5   , KC_6   , KC_PMNS, _______,
    _______, _______, KC_UNDS, KC_RCBR, KC_RPRN, KC_RBRC,      KC_0   , KC_1   , KC_2   , KC_3   , KC_PSLS, _______,
    _______, _______, _______, _______, _______, _______,      _______, _______, _______, _______, _______, _______
)

};
