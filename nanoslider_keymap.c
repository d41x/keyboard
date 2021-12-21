/* Copyright 2020 Duckle
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
#include "analog.h"
#include "qmk_midi.h"

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _BASE,
    _FN,
    _MEDIA
};

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
    MAILAD = SAFE_RANGE,
    SCRP
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base */
    [_BASE] = LAYOUT(
        TO(_FN),
        KC_F4,    KC_F5,    KC_F6,
        KC_F1,    KC_F2,    KC_F3,    KC_F11
    ),
    [_FN] = LAYOUT(
        TO(_MEDIA),
        RGB_TOG, RGB_MOD,  RGB_VAI,
        SCRP,  RGB_RMOD, RGB_VAD, MAILAD
    ),
    [_MEDIA] = LAYOUT(
        TO(_BASE),
        KC_VOLD, KC_VOLU, KC_F24,
        KC_MRWD, KC_MFFD, KC_F23, KC_MPLY
    )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case MAILAD:
            if (record->event.pressed) {
                // when keycode MAILAD is pressed
                SEND_STRING("*****@******");
            } else {
                // when keycode MAILAD is released
            }
            break;
        case SCRP:
            if (record->event.pressed) {
                // when keycode SCRP is pressed
                SEND_STRING("https://scrapbox.io/41keebs/");
            } else {
                // when keycode SCRP is released
            }
            break;
    }
    return true;
}

uint8_t divisor = 0;

void slider(void) {
    if (divisor++) { // only run the slider function 1/256 times it's called
        return;
    }

    midi_send_cc(&midi_device, 2, 0x3E, 0x7F - (analogReadPin(SLIDER_PIN) >> 3));
}

void matrix_scan_user(void) {
    slider();
}
