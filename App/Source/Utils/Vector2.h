#pragma once

namespace Math
{
	struct Vector2
	{
		float X = 0.0f;
		float Y = 0.0f;

		Vector2() {}
		Vector2(float x, float y) : X(x), Y(y) {}
		Vector2(float value) : X(value), Y(value) {}
	};
}