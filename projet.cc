// EPFL - Programmation Orientée Projet (en C++) - COM-112(a)
// Projet Dodgeball
// Auteurs: Rafael RIBER - SCIPER: 296142
//          Valentin RIAT - SCIPER: 289121

#include <iostream>
#include <string>
#include <cstring>
#include "simulation.h"
#include "error.h"
#include "gui.h"

int main(int argc, char *argv[]) {

  static bool errorMode = false;

  Simulation simulation;

  if (argc > 1){
    if (strcmp(argv[1], "Error") == 0){
      errorMode = true;
    }

    if (errorMode == true){
      simulation.read_error(argv[2]);
    }
    else {

      auto app = Gtk::Application::create(argc, argv, "org.gtkmm.example");
      Win win;
      return app->run(win);

    }
  }
  else {

    auto app = Gtk::Application::create(argc, argv, "org.gtkmm.example");
    Win win;
    return app->run(win);

  }
  return 0;
}
