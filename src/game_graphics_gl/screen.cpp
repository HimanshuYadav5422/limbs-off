/*
 * Copyright (C) 2011 Stian Ellingsen <stiell@stiell.org>
 *
 * This file is part of Limbs Off.
 *
 * Limbs Off is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Limbs Off is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Limbs Off.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <SDL/SDL.h>
#include "game_graphics_gl.h"

Screen* Screen::instance_ = 0;

Screen* Screen::getInstance() {
    if (!instance_ && initialize())
        instance_ = new Screen();
    return instance_;
}

const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 768;
const int SCREEN_DEPTH = 32;

bool Screen::initialize() {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
        return false;
    if (!SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_DEPTH, SDL_OPENGL))
        return false;
    SDL_WM_SetCaption("OpenGL Test", 0);
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    const float R = 15.0;
    const float W = R * SCREEN_WIDTH / SCREEN_HEIGHT;
    glOrtho(-W, W, -R, R, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_FASTEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
    printf("%x", glGetError());
    return glGetError() == GL_NO_ERROR;
}

Screen::Screen() {
}