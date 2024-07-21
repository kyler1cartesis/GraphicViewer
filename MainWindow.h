#pragma once
#include <string>
#include "defines.h"

#include <FL/Fl.H>              // “All programs must include the file <FL/Fl.H>.”
#include <FL/Fl_Box.H>          // Fl_Box
#include <FL/Fl_Menu_Item.H>    // Fl_Menu_Item
#include <FL/Fl_Menu_Bar.H>     // Fl_Menu_Bar
#include <FL/Fl_Window.H>       // Fl_Window

using C_str = const char*;

class MainWindow : public Fl_Window {
public:
    MainWindow(u16 width, u16 height, const char* title);

private:
    static void callback_for_command_quit(Fl_Widget* menubar, void*);

    static const Fl_Menu_Item* default_menuitems ();

    class Client_area : public Fl_Box
    {
        void draw() override;

    public:
        using Fl_Box::Fl_Box;
    };

    Fl_Menu_Bar m_menu_bar;
public:
    Client_area m_client_area;
};