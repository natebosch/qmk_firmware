/*
 * Copyright 2022 Kevin Gee <info@controller.works>
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
#define PERMISSIVE_HOLD
#define TAPPING_TOGGLE 1
#define TAP_CODE_DELAY 5
#define TAPPING_TERM 160

#define MK_KINETIC_SPEED
#define MOUSEKEY_INITIAL_SPEED 400
#define MOUSEKEY_BASE_SPEED 4000

#define SPLIT_ACTIVITY_ENABLE
#define SPLIT_USB_DETECT
#define EE_HANDS

#ifdef RGB_MATRIX_ENABLE
#    define RGB_MATRIX_KEYPRESSES // reacts to keypresses
#    define RGB_MATRIX_TIMEOUT 120000 // number of ticks to wait until disabling effects
#    define RGB_DISABLE_WHEN_USB_SUSPENDED // turn off effects when suspended
#    define RGB_MATRIX_FRAMEBUFFER_EFFECTS
#    define RGB_MATRIX_LED_FLUSH_LIMIT 16 // limits in milliseconds how frequently an animation will update the LEDs. 16 (16ms) is equivalent to limiting to 60fps (increases keyboard responsiveness)
#    define RGB_MATRIX_MAXIMUM_BRIGHTNESS 150 // limits maximum brightness of LEDs to 150 out of 255. Higher may cause the controller to crash.
#    define RGB_MATRIX_HUE_STEP 8
#    define RGB_MATRIX_SAT_STEP 8
#    define RGB_MATRIX_VAL_STEP 8
#    define RGB_MATRIX_SPD_STEP 10

#    define ENABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT
#    define ENABLE_RGB_MATRIX_JELLYBEAN_RAINDROPS
#    define ENABLE_RGB_MATRIX_TYPING_HEATMAP

#    define RGB_MATRIX_DEFAULT_MODE RGB_MATRIX_TYPING_HEATMAP
#endif
