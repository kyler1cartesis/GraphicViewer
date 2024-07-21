#include "MainWindow.h"

#include <FL/Fl_draw.H>

#include "ShapesVectorSingleton.h"

MainWindow::MainWindow (u16 width, u16 height, C_str title):
	Fl_Window(width, height, title),
	m_menu_bar(Fl_Menu_Bar(0, 0, w(), 22)),
	m_client_area (0, m_menu_bar.h(), w(), h() - m_menu_bar.h(), "")
{
	m_menu_bar.copy(default_menuitems());
	resizable(&m_client_area);
	end();
}

void MainWindow::callback_for_command_quit (Fl_Widget* menubar, void*) {
	menubar->top_window()->hide();
}
const Fl_Menu_Item* MainWindow::default_menuitems () {
	static constexpr Fl_Menu_Item the_items[] =
	{
		{ "App", 0, nullptr, nullptr, FL_SUBMENU },
		{ "Exit", FL_COMMAND + 'q', callback_for_command_quit },
		{ nullptr },
		{ nullptr }
	};
	return the_items;
}

void MainWindow::Client_area::draw () {
	fl_push_clip(x(), y(), w(), h());
	{
		ShapesVectorSingleton::DrawShapes({ dim_t(x()), dim_t(y()) });
	}
	fl_pop_clip();
}
