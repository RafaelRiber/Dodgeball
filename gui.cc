// EPFL - Programmation Orientée Projet (en C++) - COM-112(a)
// Projet Dodgeball
// Auteurs: Rafael RIBER  - SCIPER: 296142
//          Valentin RIAT - SCIPER: 289121

#include "gui.h"

using namespace std;

MyArea::MyArea(): empty(false){
}

MyArea::~MyArea(){
}

void MyArea::clear(){
  empty = true;
  refresh();
}

void MyArea::draw(){
  empty = false;
  refresh();
}

void MyArea::refresh(){
  auto win = get_window();
  if(win)
  {
    Gdk::Rectangle r(0,0, get_allocation().get_width(), get_allocation().get_height());
    win->invalidate_rect(r,false);
  }
}

void MyArea::getObjects(Simulation sim, Map m){
  mapCopy = m;
  simCopy = sim;
}

void MyArea::drawObstacles(const Cairo::RefPtr<Cairo::Context>& cr){

  std::vector<std::vector<int>> obstacles = mapCopy.getMap();

  for (int i = 0; i < obstacles.size(); i++)
  {
    for (int j = 0; j < obstacles[i].size(); j++)
    {
      if (obstacles[i][j] == 1){
        cout << "Obstacle at " << i << "; " << j << endl;
      }
    }
    std::cout << std::endl;
  }

  cout << "-------------------------------------" << endl;



  // xf = width  * (xm - (-DIM_MAX))  / (DIM_MAX - (-DIM_MAX));
  // yf = height * (DIM_MAX - ym) / (DIM_MAX - (-DIM_MAX));
  //
  // cr->set_source_rgba(1, 0, 0, 1);
  // cr->rectangle(xf, yf, SIDE/nbCells, SIDE/nbCells);
  // cr->fill();
  //
  // cr->stroke();

  cr->move_to(0,0);
  cr->line_to(100,100);
  cr->stroke();
}

bool MyArea::on_draw(const Cairo::RefPtr<Cairo::Context>& cr){
  // Gtk::Allocation allocation = get_allocation();
  // const int width = allocation.get_width();
  // const int height = allocation.get_height();
  //
  // double xm(0);
  // double ym(0);
  //
  // int xf, yf;
  // xf = width  * (xm - (-DIM_MAX))  / (DIM_MAX - (-DIM_MAX));
  // yf = height * (DIM_MAX - ym) / (DIM_MAX - (-DIM_MAX));
  //
  // cr->set_source_rgba(1, 0, 0, 1);
  // cr->rectangle(xf, yf, SIDE/nbCells, SIDE/nbCells);
  // cr->fill();
  //
  // cr->stroke();

  drawObstacles(cr);

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
buttonStep("Step"),
message(" No Game To Run")
{
  // Set title and border of the window
  set_title("Dodgeball - Rafael RIBER - Valentin RIAT");
  set_border_width(0);
  set_resizable(false);

  add(mainBox);

  mainBox.pack_start(buttonBox);
  mainBox.pack_start(separator);
  mainBox.pack_start(canvas);

  myArea.set_size_request(SIDE,SIDE);
  buttonBox.set_size_request(DIM_NOT_FORCED, BUTTON_BOX_HEIGHT);
  canvas.pack_start(myArea);

  buttonBox.pack_start(buttonExit,      false, false);
  buttonBox.pack_start(buttonOpen,      false, false);
  buttonBox.pack_start(buttonSave,      false, false);
  buttonBox.pack_start(buttonStartStop, false, false);
  buttonBox.pack_start(buttonStep,      false, false);
  buttonBox.pack_start(message,         false, false);

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

          MyEvent::~MyEvent(){
          }

          void MyEvent::on_button_clicked_buttonExit(){
            cout << "Exit" << endl;
            myArea.clear();
            exit(0);
          }

          void MyEvent::on_button_clicked_buttonOpen(){
            myArea.draw();
            message.set_label(" Draw");
            cout << "Open" << endl;
          }

          void MyEvent::on_button_clicked_buttonSave(){
            cout << "Save" << endl;
          }

          void MyEvent::on_button_clicked_buttonStartStop(){
            cout << "Start/Stop" << endl;
          }

          void MyEvent::on_button_clicked_buttonStep(){
            cout << "Step" << endl;
          }
