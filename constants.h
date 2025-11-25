#pragma once
#include "raylib.h"

// Grid
const int GRID_WIDTH = 10;
const int GRID_HEIGHT = 20;
const int BLOCK_SIZE = 35;

// Window
const int SCREEN_WIDTH = GRID_WIDTH * BLOCK_SIZE + 200; // extra space for UI
const int SCREEN_HEIGHT = GRID_HEIGHT * BLOCK_SIZE + 50;

// Aesthetic color palette
const Color COLORS[7] = {
    {0, 180, 240, 255},   // cyan
    {255, 140, 0, 255},   // orange
    {255, 230, 0, 255},   // yellow
    {180, 0, 255, 255},   // purple
    {0, 200, 0, 255},     // green
    {255, 0, 0, 255},     // red
    {0, 0, 255, 255}      // blue
};

// Background & UI colors
const Color BG_COLOR = {30, 30, 30, 255};
const Color GRID_LINE_COLOR = {50, 50, 50, 255};
const Color UI_BG_COLOR = {40, 40, 40, 200};

// Game settings
const float BASE_FALL_SPEED = 0.5f;
