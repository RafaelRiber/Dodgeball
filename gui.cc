// EPFL - Programmation Orientée Projet (en C++) - COM-112(a)
// Projet Dodgeball
// Auteurs: Rafael RIBER  - SCIPER: 296142
//          Valentin RIAT - SCIPER: 289121

#include "gui.h"

void gui_start(char* file_name, int argc, char *argv[]){
  Simulation simulation;
  simulation.read(file_name);

  Gtk::Main app(argc, argv);
  MyEvent eventWindow;
  eventWindow.myArea.getObjects(simulation);
  Gtk::Main::run(eventWindow);
}

void gui_start_nofile(int argc, char *argv[]){
  Simulation simulation;

  simulation.read();

  Gtk::Main app(argc, argv);
  MyEvent eventWindow;
  eventWindow.myArea.getObjects(simulation);
  Gtk::Main::run(eventWindow);
}

//--------------------------------------

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

void MyArea::getObjects(Simulation sim){
  mapCopy = sim.getMap();
  simCopy = sim;
}

void MyArea::drawObstacles(const Cairo::RefPtr<Cairo::Context>& cr){

  Gtk::Allocation allocation = get_allocation();
  const int width = allocation.get_width();
  const int height = allocation.get_height();

  std::vector<std::vector<int>> obstacles(mapCopy.getMap());
  int nbCell(simCopy.getNbCell());

  for (int i = 0; i < obstacles.size(); ++i)
  {
    for (int j = 0; j < obstacles[i].size(); ++j)
    {
      if (obstacles[i][j] == 1){
        Cell c(i, j);
        Point p(c, nbCell, SIDE);

        double xm, ym;

        p.getCoordinates(xm,ym);

        int xf, yf;
        xf = width  * (xm - (-DIM_MAX))  / (DIM_MAX - (-DIM_MAX));
        yf = height * (DIM_MAX - ym) / (DIM_MAX - (-DIM_MAX));

        cr->set_source_rgba(0.43, 0, 0, 1);
        cr->rectangle(yf, xf, SIDE/nbCell, SIDE/nbCell);
        cr->fill();
      }
    }
  }
}

void MyArea::drawPlayers(const Cairo::RefPtr<Cairo::Context>& cr){

  Gtk::Allocation allocation = get_allocation();
  const int width = allocation.get_width();
  const int height = allocation.get_height();

  for (size_t i = 0; i < simCopy.getPlayers().size(); ++i)
  {
    Player current = simCopy.getPlayers()[i];
    Point p(current.getPlayerCoordinates());

    double xm, ym;

    p.getCoordinates(xm,ym);

    int xf, yf;
    xf = width  * (xm - (-DIM_MAX))  / (DIM_MAX - (-DIM_MAX));
    yf = height * (DIM_MAX - ym) / (DIM_MAX - (-DIM_MAX));

    if (current.getNbt() == 4){
      cr->set_source_rgba(0, 1.0, 0, 1);
    }
    if (current.getNbt() == 3){
      cr->set_source_rgba(0.92, 1.0, 0, 1);
    }
    if (current.getNbt() == 2){
      cr->set_source_rgba(1, 0.62, 0, 1);
    }
    if (current.getNbt() == 1){
      cr->set_source_rgba(1, 0, 0, 1);
    }

    cr->arc(xf, yf, simCopy.getPlayerRadius(), 0.0, 2.0 * M_PI);
    cr->fill();
  }
}

void MyArea::drawBalls(const Cairo::RefPtr<Cairo::Context>& cr){

  Gtk::Allocation allocation = get_allocation();
  const int width = allocation.get_width();
  const int height = allocation.get_height();

  for (size_t i = 0; i < simCopy.getBalls().size(); ++i)
  {
    Ball current = simCopy.getBalls()[i];
    Point p(current.getBallCoordinates());

    double xm, ym;

    p.getCoordinates(xm,ym);

    int xf, yf;
    xf = width  * (xm - (-DIM_MAX))  / (DIM_MAX - (-DIM_MAX));
    yf = height * (DIM_MAX - ym) / (DIM_MAX - (-DIM_MAX));

    cr->set_source_rgba(0, 0, 1, 1);
    cr->arc(xf, yf, simCopy.getBallRadius(), 0.0, 2.0 * M_PI);
    cr->fill();
  }
}

bool MyArea::on_draw(const Cairo::RefPtr<Cairo::Context>& cr){

  drawPlayers(cr);
  drawObstacles(cr);
  drawBalls(cr);

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
  std::cout << "Exit" << std::endl;
  myArea.clear();
  exit(0);
}

void MyEvent::on_button_clicked_buttonOpen(){
  Gtk::FileChooserDialog dialog("Please choose a file",
  Gtk::FILE_CHOOSER_ACTION_OPEN);
  dialog.set_transient_for(*this);
  dialog.add_button("_Cancel", Gtk::RESPONSE_CANCEL);
  dialog.add_button("_Open", Gtk::RESPONSE_OK);
  int result = dialog.run();

  switch(result)
  {
    case(Gtk::RESPONSE_OK):
    {
      std::cout << "Open clicked." << std::endl;
      std::string filename = dialog.get_filename();
      std::cout << "File selected: " <<  filename << std::endl;
      //gui_start(filename, argc, argv);

      break;
    }
    case(Gtk::RESPONSE_CANCEL):
    {
      std::cout << "Cancel clicked." << std::endl;
      break;
    }
    default:
    {
      std::cout << "Unexpected button clicked." << std::endl;
      break;
    }
  }
}

  void MyEvent::on_button_clicked_buttonSave(){
    std::cout << "Save" << std::endl;
  }

  void MyEvent::on_button_clicked_buttonStartStop(){
    std::cout << "Start/Stop" << std::endl;
  }

  void MyEvent::on_button_clicked_buttonStep(){
    std::cout << "Step" << std::endl;
  }
