// EPFL - Programmation Orientée Projet (en C++) - COM-112(a)
// Projet Dodgeball
// Auteurs: Rafael RIBER  - SCIPER: 296142
//          Valentin RIAT - SCIPER: 289121

#ifndef GUI_H
#define GUI_H

#include <gtkmm/drawingarea.h>
#include <gtkmm/window.h>
#include <gtkmm/application.h>
#include <gtkmm/box.h>
#include <gtkmm/button.h>
#include <gtkmm/separator.h>
#include <gtkmm/label.h>
#include <gtkmm/filechooserdialog.h>
#include <cairomm/context.h>
#include <glibmm/main.h>

#include <iostream>
#include "simulation.h"
#include "tools.h"
#include "define.h"

void gui_start(int mode, char* file_name);
void gui_start_nofile(int mode);
Simulation sim_start(char *file_name);

void convCoords(int width, int height, Point modelPoint, int &xf, int &yf);

class MyArea : public Gtk::DrawingArea
{
public:
  MyArea();
  virtual ~MyArea();
  void clear();
  void draw();
  void refresh();
  void drawObstacles(const Cairo::RefPtr<Cairo::Context>& cr);
  void drawPlayers(const Cairo::RefPtr<Cairo::Context>& cr);
  void drawBalls(const Cairo::RefPtr<Cairo::Context>& cr);
  void loadSimulation(std::string filename);
  void loadSimulation(char *file_name);
  bool isSimulationLoaded();

  Map gui_map;
  Simulation gui_sim;

protected:
  bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override;

private:
  bool empty;
  bool simLoaded;
};

/////////////////////////////////////////////////////////////////////////

class MyEvent : public Gtk::Window
{
public:
  MyEvent(char *file_name, int mode);
  virtual ~MyEvent();
  MyArea            myArea;

protected:
  //Button Signal handlers:
  void on_button_clicked_buttonExit();
  void on_button_clicked_buttonOpen();
  void on_button_clicked_buttonSave();
  void on_button_clicked_buttonStartStop();
  void on_button_clicked_buttonStep();

  Gtk::Box          mainBox,  canvas,    buttonBox;
  Gtk::Button 		  buttonExit;
  Gtk::Button 		  buttonOpen;
  Gtk::Button 		  buttonSave;
  Gtk::Button 		  buttonStartStop;
  Gtk::Button 		  buttonStep;
  Gtk::Separator    separator;
  Gtk::Label        message;


  //Timer
  void startTimer();
  void stopTimer();

  bool onTimeout();
  bool timerAdded;
  bool disconnect;
  const double timeoutValue;
};

#endif
