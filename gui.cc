// EPFL - Programmation Orientée Projet (en C++) - COM-112(a)
// Projet Dodgeball
// Auteurs: Rafael RIBER - SCIPER: 296142
//          Valentin RIAT - SCIPER: 289121

#include "gui.h"
#include <iostream>

MyArea::MyArea()
{
}

MyArea::~MyArea()
{
}

bool MyArea::on_draw(const Cairo::RefPtr<Cairo::Context>& cr)
{
  Gtk::Allocation allocation = get_allocation();
  const int width = allocation.get_width();
  const int height = allocation.get_height();

  return true;
}


////////////////////////////////////////////////////////////////////////////////


Win::Win()
: m_button("Hello World")   // creates a new button with label "Hello World".
{
  // Sets the border width of the window. // cosmetique
  set_border_width(10);

  // When the button receives the "clicked" signal, it will call the
  // on_button_clicked() method defined below.
  m_button.signal_clicked().connect(sigc::mem_fun(*this,
              &Win::on_button_clicked));

  // This packs the button into the Window (a container).
  add(m_button);

  // The final step is to display this newly created widget...
  m_button.show();
}

Win::~Win()
{
}

void Win::on_button_clicked()
{
  std::cout << "Goodbye World \a" << std::endl;
  exit(0);
}
