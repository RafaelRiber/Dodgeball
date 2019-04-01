// EPFL - Programmation Orientée Projet (en C++) - COM-112(a)
// Projet Dodgeball
// Auteurs: Rafael RIBER  - SCIPER: 296142
//          Valentin RIAT - SCIPER: 289121

#include <iostream>
#include "gui.h"

using namespace std;

MyArea::MyArea(): empty(false)
{
}

MyArea::~MyArea()
{
}

void MyArea::clear()
{
  empty = true;
  refresh();
}

void MyArea::draw()
{
  empty = false;
  refresh();
}

void MyArea::refresh()
{
  auto win = get_window();
  if(win)
  {
	  Gdk::Rectangle r(0,0, get_allocation().get_width(), get_allocation().get_height());
	  win->invalidate_rect(r,false);
  }
}

bool MyArea::on_draw(const Cairo::RefPtr<Cairo::Context>& cr)
{
  if(not empty)
  {
	  Gtk::Allocation allocation = get_allocation();
	  const int width = allocation.get_width();
	  const int height = allocation.get_height();

	  // coordinates for the center of the window
	  int xc, yc;
	  xc = width / 2;
	  yc = height / 2;

	  cr->set_line_width(10.0);

	  // draw red lines out from the center of the window
	  cr->set_source_rgb(0.8, 0.0, 0.0);
	  cr->move_to(0, 0);
	  cr->line_to(xc, yc);
	  cr->line_to(0, height);
	  cr->move_to(xc, yc);
	  cr->line_to(width, yc);
	  cr->stroke();
  }
  else
  {
	  cout << "Empty !" << endl;
  }

  return true;
}


//--------------------------------------


MyEvent::MyEvent() :
  mainBox(Gtk::ORIENTATION_VERTICAL),
  canvas(Gtk::ORIENTATION_HORIZONTAL),
  buttonBox(Gtk::ORIENTATION_HORIZONTAL),

  buttonExit("Exit"),
  buttonOpen("Open"),
  buttonSave("Save"),
  buttonStartStop("Start"),
  buttonStep("Step")
{
  // Set title and border of the window
  set_title("Dodgeball");
  set_border_width(0);

  add(mainBox);

  mainBox.pack_start(buttonBox);
  mainBox.pack_start(separator);
  mainBox.pack_start(canvas);

  myArea.set_size_request(BOX_DIM,BOX_DIM);
  buttonBox.set_size_request(DIM_NOT_FORCED, BUTTON_BOX_HEIGHT);
  canvas.pack_start(myArea);

  buttonBox.pack_start(buttonExit,false,false);
  buttonBox.pack_start(buttonOpen,false,false);
  buttonBox.pack_start(buttonSave,false,false);
  buttonBox.pack_start(buttonStartStop,false,false);
  buttonBox.pack_start(buttonStep,false,false);

  buttonExit.signal_clicked().connect(sigc::mem_fun(*this,
              &MyEvent::on_button_clicked_buttonExit) );

  buttonOpen.signal_clicked().connect(sigc::mem_fun(*this,
              &MyEvent::on_button_clicked_buttonOpen) );

  buttonSave.signal_clicked().connect(sigc::mem_fun(*this,
              &MyEvent::on_button_clicked_buttonSave) );

  buttonStartStop.signal_clicked().connect(sigc::mem_fun(*this,
              &MyEvent::on_button_clicked_buttonStartStop) );

  buttonStep.signal_clicked().connect(sigc::mem_fun(*this,
              &MyEvent::on_button_clicked_buttonStep) );

  show_all_children();
}

MyEvent::~MyEvent()
{
}

void MyEvent::on_button_clicked_buttonExit()
{
  cout << "Exit" << endl;
  myArea.clear();
}

void MyEvent::on_button_clicked_buttonOpen()
{
  myArea.draw();
  cout << "Open" << endl;
}

void MyEvent::on_button_clicked_buttonSave()
{
  cout << "Save" << endl;
}

void MyEvent::on_button_clicked_buttonStartStop()
{
  cout << "Start/Stop" << endl;
}

void MyEvent::on_button_clicked_buttonStep()
{
  cout << "Step" << endl;
}
