#include "FLTKGraphicsEngine.h"
#include "Shapes.h"
#include "defines.h"
#include "FlDrawParametersManager.h"

#include "Fl/Fl.H"
#include "FL/fl_draw.H"

void FLTKGraphicsEngine::InitializeWindow (dim_t w, dim_t h) {}
void FLTKGraphicsEngine::DrawShape(const Shape& shape, const Coordinates offset) {
	FlDrawParametersManager manager(shape);
	switch (shape.type) {
	case Shape::Line: {
		auto& line = reinterpret_cast<const Line&>(shape);
		return DrawLine(line.start_point.x + offset.x, line.start_point.y + offset.y, line.end_point.x, line.end_point.y + offset.y);
	}
	case Shape::Rectangle: {
		auto& rectangle = reinterpret_cast<const struct Rectangle&>(shape);
		return DrawRectangle(rectangle.position.x + offset.x, rectangle.position.y + offset.y, rectangle.dimensions.width, rectangle.dimensions.height);
	}
	case Shape::Triangle: {
		auto& triangle = reinterpret_cast<const Triangle&>(shape);
		return DrawTriangle(triangle.point1.x + offset.x, triangle.point1.y + offset.y, triangle.point2.x + offset.x, triangle.point2.y + offset.y, triangle.point3.x + offset.x, triangle.point3.y + offset.y);
	}
	case Shape::Circle: {
		auto& circle = reinterpret_cast<const Circle&>(shape);
		return DrawCircle(circle.position.x + offset.x, circle.position.y + offset.y, circle.radius);
	}
	case Shape::Polygon: {
		auto& polygon = reinterpret_cast<const struct Polygon&>(shape);
		return DrawPolygon(polygon.point1.x + offset.x, polygon.point1.y + offset.y, polygon.point2.x + offset.x, polygon.point2.y + offset.y, polygon.point3.x + offset.x, polygon.point3.y + offset.y, polygon.point4.x + offset.x, polygon.point4.y + offset.y);
	}
	case Shape::Unknown:
		break;
	case Shape::Text:
		auto& text = reinterpret_cast<const Text&>(shape);
		return DrawText1(text.position.x, text.position.y, text.text);	
	}
}
void FLTKGraphicsEngine::DrawLine (dim_t x1, dim_t y1, dim_t x2, dim_t y2) {
	fl_line(x1, y1, x2, y2);
}
void FLTKGraphicsEngine::DrawRectangle (dim_t x, dim_t y, dim_t w, dim_t h) {
	fl_rectf(x, y, w, h);
}
void FLTKGraphicsEngine::DrawTriangle (dim_t x1, dim_t y1, dim_t x2, dim_t y2, dim_t x3, dim_t y3) {
	fl_polygon(x1, y1, x2, y2, x3, y3);
}
void FLTKGraphicsEngine::DrawPolygon (dim_t x1, dim_t y1, dim_t x2, dim_t y2, dim_t x3, dim_t y3, dim_t x4, dim_t y4) {
	fl_polygon(x1, y1, x2, y2, x3, y3, x4, y4);
}
void FLTKGraphicsEngine::DrawCircle(dim_t x, dim_t y, dim_t r) {
	fl_circle(x, y, r);
}
void FLTKGraphicsEngine::DrawEllipse (dim_t x, dim_t y, dim_t w, dim_t h, f64 a1, f64 a2) {
	fl_arc(x, y, w, h, a1, a2);
}
void FLTKGraphicsEngine::DrawText1 (dim_t x, dim_t y, const std::string_view text) {
	fl_draw(text.data(), x, y);
}
void FLTKGraphicsEngine::DrawPoint (dim_t x, dim_t y) {
	fl_point(x, y);
}