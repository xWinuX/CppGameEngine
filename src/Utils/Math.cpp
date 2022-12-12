﻿#include "Math.h"

#include <cmath>

float Math::Lerp(const float a, const float b, const float t) { return a + (b - a) * t; }

float Math::Sin01(const float x) { return (sin(x) + 1.0f) / 2.0f; }
