#include "JSONParser.h"

#include <spdlog/spdlog.h>

using namespace JSONParameters;
std::vector<std::unique_ptr<Shape>> JSONParser::ParseShapesArray (const json& j) {
	if (!(j.contains(shapes_array_key) && j[shapes_array_key].is_array())) {
		spdlog::error("JSON's \"{}\" key is missing or file's structure is invalid!\n", shapes_array_key);
		return {};
	}
	std::vector<std::unique_ptr<Shape>> shapes;
	for (const json& json_shape : j.at(shapes_array_key)) {
		if (std::unique_ptr<Shape> shape = ParseShape(json_shape))
			shapes.emplace_back(std::move(shape));
	}
	return shapes;
}

Shape JSONParser::make_shape_from_json(const json& j, const Shape::Type type) {
	Shape shape { .type = type };
	if (j.contains(color)) {
		if (j[color].is_string()) {
			u32 color_number = std::stoi(j[color].get<std::string>(), nullptr, 16);
			shape.color = {
				.r = u8(color_number >> 020 & 0xff),
				.g = u8(color_number >> 010 & 0xff),
				.b = u8(color_number >> 000 & 0xff)
			};
		}
		else spdlog::warn("Wrong JSON's {} value provided! Shound be hex value.\n", color);
	}
	if (j.contains(line_style)) {
		if (j[line_style].is_number_unsigned() && j[line_style] <= Shape::FL_DASHDOTDOT) {
			shape.line_style = static_cast<Shape::LineStyle>(j[line_style]);
		}
		else spdlog::warn("Wrong JSON's {} value provided! Shound be a number of 0..4 .\n", line_style);
	}
	if (j.contains(line_width)) {
		if (j[line_width].is_number_unsigned() && j[line_width] <= 255) {
			shape.line_width= static_cast<u8>(j[line_width]);
		}
		else spdlog::warn("Wrong JSON's {} value provided! Shound be a number of 0..255 .\n", line_width);
	}
	return shape;
}

std::unique_ptr<Shape> JSONParser::ParseShape(const json& json_shape) {
	std::string type;
	try {
		if (type = json_shape[shape_type];
			type == "line")
			return ParseLine(json_shape);
		else if (type == "point")
			return ParsePoint(json_shape);
		else if (type == "rectangle")
			return ParseRectangle(json_shape);
		else if (type == "circle")
			return ParseCircle(json_shape);
		else if (type == "triangle")
			return ParseTriangle(json_shape);
		else if (type == "polygon")
			return ParsePolygon(json_shape);
		else if (type == "text")
			return ParseText(json_shape);
		else {
			spdlog::error("Parsed shape with invalid {}={} from JSON!", shape_type, type);
			return {};
		}
	}
	catch (json::exception& exc) {
		spdlog::error("Couldn't parse a shape {} from JSON! Description: {}", type, exc.what());
		return {};
	}
}
std::unique_ptr<Point> JSONParser::ParsePoint(const json& j) {
	Point point({ j[x], j[y] }, make_shape_from_json(j, Shape::Point));
	return std::make_unique<Point>(point);
}
std::unique_ptr<Line> JSONParser::ParseLine(const json& j) {
	Line line({ j[x1], j[JSONParameters::y1] }, // Спасибо Майкрософт
		{ j[x2] , j[y2] },
		make_shape_from_json(j, Shape::Line));
	return std::make_unique<Line>(line);
}
std::unique_ptr<Rectangle> JSONParser::ParseRectangle(const json& j) {
	Rectangle rectangle({ j[x], j[y] },
		{ j[width] , j[height] },
		make_shape_from_json(j, Shape::Rectangle));
	return std::make_unique<Rectangle>(rectangle);
}
std::unique_ptr<Circle> JSONParser::ParseCircle (const json& j) {
	Circle circle({ j[x], j[y] }, j[radius],
		make_shape_from_json(j, Shape::Circle));
	return std::make_unique<Circle>(circle);
}
std::unique_ptr<Triangle> JSONParser::ParseTriangle (const json& j) {
	Triangle triangle({ j[x1], j[JSONParameters::y1] },
		{ j[x2], j[y2] }, { j[x3], j[y3] },
		make_shape_from_json(j, Shape::Triangle));
	return std::make_unique<Triangle>(triangle);
}
std::unique_ptr<Polygon> JSONParser::ParsePolygon (const json& j) {
	Polygon polygon({ j[x1], j[JSONParameters::y1] },
		{ j[x2], j[y2] }, { j[x3], j[y3] }, { j[x4], j[y4] },
		make_shape_from_json(j, Shape::Polygon));
	return std::make_unique<Polygon>(polygon);
}
std::unique_ptr<Text> JSONParser::ParseText(const json& j) {
	Text text1({ j[x], j[y] }, j[text],
		make_shape_from_json(j, Shape::Text));
	return std::make_unique<Text>(text1);
}
