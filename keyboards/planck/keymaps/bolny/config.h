/* Copyright 2015-2017 Jack Humbert
 * Copyright 2022 Brendon O'Laney (@bolny) <brendon@brendonolaney.com>
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

#pragma once

#define ORYX_CONFIGURATOR
#define PLANCK_EZ_LED_LOWER 2
#define PLANCK_EZ_LED_RAISE 3
#define PLANCK_EZ_LED_ADJUST 8

#ifdef AUDIO_ENABLE
    #define STARTUP_SONG SONG(PLANCK_SOUND)
#endif

