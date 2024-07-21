#pragma once
#include <memory>
#include <nlohmann/json.hpp>

#include "Shapes.h"

class JSONParser {
	using json = nlohmann::json;
public:
	static std::vector<std::unique_ptr<Shape>> ParseShapesArray (const json& j);
	static std::unique_ptr<Shape> ParseShape(const json& json_shape);
	static std::unique_ptr<Point> ParsePoint (const json& j);
	static std::unique_ptr<Line> ParseLine (const json& j);
	static std::unique_ptr<struct Rectangle> ParseRectangle (const json& j);
	static std::unique_ptr<Circle> ParseCircle (const json& j);
	static std::unique_ptr<Triangle> ParseTriangle (const json& j);
	static std::unique_ptr<struct Polygon> ParsePolygon (const json& j);
	static std::unique_ptr<Text> ParseText (const json& j);

private:
	static Shape make_shape_from_json (const json& j, Shape::Type type);
};

namespace JSONParameters {
	static const char * x = "x", * y = "y",
		* x1 = "x1", * x2 = "x2", * x3 = "x3", * x4 = "x4",
		* y1 = "y1", * y2 = "y2", * y3 = "y3", * y4 = "y4",
		* width = "width", * height = "height", * radius = "radius", * text = "text",
		* line_style = "line_style", * line_width = "line_width", * color = "color",
		* shapes_array_key = "shapes", * shape_type = "type";
}