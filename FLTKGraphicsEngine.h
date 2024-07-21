#pragma once
#include "defines.h"
#include "Shapes.h"

class FLTKGraphicsEngine {
public:
	static void InitializeWindow (dim_t w, dim_t h);
	static void DrawShape (const Shape& shape, Coordinates offset = {0, 0});

	static void DrawLine      (dim_t x1, dim_t y1, dim_t x2, dim_t y2);
	static void DrawRectangle (dim_t x, dim_t y, dim_t w, dim_t h);
	static void DrawTriangle  (dim_t x1, dim_t y1, dim_t x2, dim_t y2, dim_t x3, dim_t y3);
	static void DrawPolygon   (dim_t x1, dim_t y1, dim_t x2, dim_t y2, dim_t x3, dim_t y3, dim_t x4, dim_t y4);
	static void DrawCircle    (dim_t x, dim_t y, dim_t r);
	static void DrawEllipse   (dim_t x, dim_t y, dim_t w, dim_t h, f64 a1, f64 a2);
	static void DrawText1     (dim_t x, dim_t y, const std::string_view text);
	static void DrawPoint     (dim_t x, dim_t y);
};
