#ifndef GUI_H
#define GUI_H

#include <gtkmm.h>
#include "define.h"

#define BUTTON_BOX_HEIGHT 20
#define BOX_DIM (2*DIM_MAX)
#define DIM_NOT_FORCED -1

class MyArea : public Gtk::DrawingArea
{
public:
  MyArea();
  virtual ~MyArea();
  void clear();
  void draw();

protected:
  bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override;

private:
  bool empty;
  void refresh();
};

/////////////////////////////////////////////////////////////////////////

class MyEvent : public Gtk::Window
{
public:
  MyEvent();
  virtual ~MyEvent();

protected:
  //Button Signal handlers:
  void on_button_clicked_buttonExit();
  void on_button_clicked_buttonOpen();
  void on_button_clicked_buttonSave();
  void on_button_clicked_buttonStartStop();
  void on_button_clicked_buttonStep();

  MyArea            myArea;
  Gtk::Box          mainBox,  canvas,    buttonBox;
  Gtk::Button 		  buttonExit;
  Gtk::Button 		  buttonOpen;
  Gtk::Button 		  buttonSave;
  Gtk::Button 		  buttonStartStop;
  Gtk::Button 		  buttonStep;
  Gtk::Separator    separator;
};

#endif
