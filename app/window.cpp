#include "window.hpp"

bool CasWindow::key_controller_cb(guint keyval, guint, Gdk::ModifierType state)
{
	if (keyval == GDK_KEY_Return)
  	{
		int current_page = notebook.get_current_page();
	    CommonMode* widget = (CommonMode*)notebook.get_nth_page(current_page);
	    
	    widget->evaluate();
	    
    	return true;
  	}
	
  	return false;
}

CasWindow::CasWindow()
{
    using Glib::ustring;

	auto controller = Gtk::EventControllerKey::create();
	controller->signal_key_pressed().connect(sigc::mem_fun(*this, &CasWindow::key_controller_cb), false);
	add_controller(controller);

    set_resizable(false);
    set_title("Computer Algebra System");

    notebook.append_page(natural, "\xE2\x84\x95");
    notebook.append_page(integer, "\xE2\x84\xA4");
    notebook.append_page(rational, "\xE2\x84\x9A");
    notebook.append_page(polynomial, "\xE2\x84\x99");
    notebook.set_current_page(0);

    set_child(notebook);
}
