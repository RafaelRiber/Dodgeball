// EPFL - Programmation Orientée Projet (en C++) - COM-112(a)
// Projet Dodgeball
// Auteurs: Rafael RIBER  - SCIPER: 296142
//          Valentin RIAT - SCIPER: 289121

#include <iostream>
#include <string>
#include <cstring>
#include "simulation.h"
#include "error.h"
#include "gui.h"

void gui_start(Simulation sim, Map map, int mode, int argc, char *argv[]);

int main(int argc, char *argv[]) {

  enum ModeList{ERROR,STEP,NORMAL,NOFILE};

  int mode(NOFILE);

  Simulation simulation;

  //simulation.read("C:/Users/Valentin/Documents/GitHub/Dodgeball/E02.txt"); exit(0); //debug

  if (argc > 1){
    if (strcmp(argv[1], "Error") == 0){
      mode = ERROR;
      simulation.read_error(argv[2]);
    }else if(strcmp(argv[1], "Step") == 0){
      mode = STEP;
      std::cout<<"Step mode not yet implemented"<<std::endl;
    }else{
      mode = NORMAL;
      simulation.read(argv[1]);
      gui_start(simulation, simulation.getMap(), mode, argc, argv);
    }

  }else{
    mode = NOFILE;
    simulation.read();
    gui_start(simulation, simulation.getMap(), mode, argc, argv);
  }
  return 0;
}

void gui_start(Simulation sim, Map map, int mode, int argc, char *argv[]){
  Gtk::Main app(argc, argv);
  MyEvent eventWindow;
  eventWindow.myArea.getObjects(sim, map);
  Gtk::Main::run(eventWindow);
}
