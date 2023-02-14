#include "Math.h"
#include "GameEngine/Utils/Math.h"

#include <cmath>
#include <limits>

using namespace GameEngine::Utils;

// The physics system doesn't like the min value from std::numeric_limits
const float Math::MinValue = 0.0000001f;

float Math::Lerp(const float a, const float b, const float t) { return a + (b - a) * t; }

float Math::Sin01(const float x) { return (sin(x) + 1.0f) / 2.0f; }
