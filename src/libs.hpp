#pragma once

// STD Libraries
#include <algorithm>
#include <iostream>
#include <array>
#include <vector>
#include <memory>
#include <exception>
#include <string>
#include <set>

// Custom headers
#include "enums.hpp"
#include "constants.hpp"

// SDL
#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

// Using ...
using std::string;
using std::string_view;
using std::array;
using std::set;
using std::vector;
using std::unique_ptr;
using std::shared_ptr;

// TODO refactor this files and libs.hpp includes
