#pragma once
#include <Fl/Fl.H>
#include <FL/Fl_draw.H>

class FlDrawParametersManager {
	bool to_restore_color = false;
	bool to_restore_style = false;

public:
	FlDrawParametersManager(const Shape& shape) {
		if (shape.color != Shape::Color {}) {
			to_restore_color = true;
			fl_color(shape.color.r, shape.color.g, shape.color.b);
		}
		if (shape.line_width > 0 or shape.line_style != Shape::FL_SOLID) {
			to_restore_style = true;
			fl_line_style(shape.line_style, shape.line_width);
		}
	}
	~FlDrawParametersManager() {
		if (to_restore_color) {
			fl_color(FL_BLACK);
		}
		if (to_restore_style) {
			fl_line_style(FL_SOLID, 0);
		}
	}
};