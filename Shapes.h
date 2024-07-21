#pragma once
#include <array>
#include <bitset>
#include <optional>
#include <string>

#include "defines.h"

using dim_t = u16;
struct Coordinates { dim_t x = 0, y = 0; };
struct Dimensions { dim_t width = 0, height = 0; };

struct Shape {
	struct Color {
		u8 r = 255, g = 255, b = 255;
		std::strong_ordering operator<=> (const Shape::Color& color) const = default;
	}
	//union {
	color { 255, 255, 255 };
		//std::array<u8, 3> rgb_array = { 255, 255, 255 };
	//};
	enum Type : u8 {
		Unknown,
		Point,
		Line,
		Rectangle,
		Triangle,
		Circle,
		Polygon,
		Text
	} type {};
	// See fl_draw.h/fl_line_style()
	enum LineStyle : u8 {
		FL_SOLID = 0,		///< line style: <tt>___________</tt>
		FL_DASH = 1,		///< line style: <tt>_ _ _ _ _ _</tt>
		FL_DOT = 2,		    ///< line style: <tt>. . . . . .</tt>
		FL_DASHDOT = 3,		///< line style: <tt>_ . _ . _ .</tt>
		FL_DASHDOTDOT = 4	///< line style: <tt>_ . . _ . .</tt>
	} line_style {};
	u8 line_width = 0;
};
struct Point      : Shape {
	Coordinates start_point;
	Point(Coordinates _start_point, Shape _shape = Shape{}):
		Shape(_shape), start_point(_start_point) {}
};
struct Line      : Shape {
	Coordinates start_point; Coordinates end_point;
	Line(Coordinates _start_point, Coordinates _end_point, Shape _shape = Shape{}):
		Shape(_shape), start_point(_start_point), end_point(_end_point) {}
};
struct Rectangle : Shape {
	Coordinates position; Dimensions dimensions;
	Rectangle(Coordinates _position, Dimensions _dimensions, Shape _shape = Shape{}):
		Shape(_shape), position(_position), dimensions(_dimensions) {}
};
struct Circle    : Shape {
	Coordinates position; dim_t radius;
	Circle(Coordinates _position, dim_t _radius, Shape _shape = Shape{}):
		Shape(_shape), position(_position), radius(_radius) {}
};
struct Triangle  : Shape {
	Coordinates point1, point2, point3;
	Triangle(Coordinates _point1, Coordinates _point2, Coordinates _point3, Shape _shape = Shape{}):
		Shape(_shape), point1(_point1), point2(_point2), point3(_point3) {}	
};
struct Polygon   : Shape {
	Coordinates point1, point2, point3, point4;
	Polygon(Coordinates _point1, Coordinates _point2, Coordinates _point3, Coordinates _point4, Shape _shape = Shape{}):
		Shape(_shape), point1(_point1), point2(_point2), point3(_point3), point4(_point4) {}
};
struct Text      : Shape {
	Coordinates position; std::string text;
	Text(Coordinates _position, std::string _text, Shape _shape = Shape{}):
		Shape(_shape), position(_position), text(std::move(_text)) {}
};