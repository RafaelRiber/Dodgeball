// EPFL - Programmation Orientée Projet (en C++) - COM-112(a)
// Projet Dodgeball
// Auteurs: Rafael RIBER  - SCIPER: 296142
//          Valentin RIAT - SCIPER: 289121

#include "gui.h"

void gui_start(int mode, char *file_name){
  auto app = Gtk::Application::create();
  MyEvent eventWindow(file_name, mode);
  app->run(eventWindow);
}

void gui_start_nofile(int mode){
  auto app = Gtk::Application::create();
  char* file_name = (char*)"";
  MyEvent eventWindow(file_name, mode);
  app->run(eventWindow);
}

Simulation sim_start(char *file_name){
  Simulation simulation;
  simulation.read(file_name);
  return simulation;
}

Simulation sim_start_nofile(){
  Simulation simulation;
  return simulation;
}

void convCoords(int width, int height, Point modelPoint, int &xf, int &yf){
  double xm, ym;
  modelPoint.getCoordinates(xm,ym);
  xf = width  * (xm - (-DIM_MAX))  / (DIM_MAX - (-DIM_MAX));
  yf = height * (DIM_MAX - ym)     / (DIM_MAX - (-DIM_MAX));
}

//--------------------------------------

MyArea::MyArea(): empty(false), simLoaded(false){
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

void MyArea::drawObstacles(const Cairo::RefPtr<Cairo::Context>& cr){

  Gtk::Allocation allocation = get_allocation();
  const int width = allocation.get_width();
  const int height = allocation.get_height();

  gui_map = gui_sim.getMap();

  std::vector<std::vector<int>> obstacles(gui_map.getMap());
  int nbCell(gui_sim.getNbCell());

  for (size_t i = 0; i < obstacles.size(); ++i)
  {
    for (size_t j = 0; j < obstacles[i].size(); ++j)
    {
      if (obstacles[i][j] == 1){
        Cell c(j, i);
        Point p(c, nbCell, SIDE);

        int xf, yf;
        convCoords(width, height, p, xf, yf);

        cr->set_source_rgba(BROWN_OBSTACLES);
        cr->rectangle(yf, xf, SIDE/nbCell, SIDE/nbCell);
        cr->fill();
        cr->stroke();
      }
    }
  }
}

void MyArea::drawPlayers(const Cairo::RefPtr<Cairo::Context>& cr){

  Gtk::Allocation allocation = get_allocation();
  const int width = allocation.get_width();
  const int height = allocation.get_height();

  for (size_t i = 0; i < gui_sim.getPlayers().size(); ++i)
  {
    Player current = gui_sim.getPlayers()[i];
    if (current.getNbt() == 4) cr->set_source_rgba(GREEN_PLAYER);
    if (current.getNbt() == 3) cr->set_source_rgba(YELLOW_PLAYER);
    if (current.getNbt() == 2) cr->set_source_rgba(ORANGE_PLAYER);
    if (current.getNbt() == 1) cr->set_source_rgba(RED_PLAYER);
    int count(current.getCount());
    Point p(current.getPlayerCoordinates());
    double playerRadius(gui_sim.getPlayerRadius());

    int xf, yf;
    convCoords(width, height, p, xf, yf);

    cr->arc(xf, yf, playerRadius, CIRCLE_ANGLE_BEGIN, CIRCLE_ANGLE_END);
    cr->fill();
    cr->stroke();

    double arcAngle = (count * CIRCLE_ANGLE_END) / MAX_COUNT;
    double arcLineWidth = playerRadius / ARC_LINE_WIDTH_RATIO;
    double arcRadius = playerRadius - (arcLineWidth / ARC_LINE_WIDTH_DIVIDER);
    cr->set_line_width(arcLineWidth);
    cr->set_source_rgba(BLUE_ARCS);
    cr->arc(xf, yf, arcRadius, CIRCLE_ANGLE_BEGIN, arcAngle);
    cr->stroke();
  }
}

void MyArea::drawBalls(const Cairo::RefPtr<Cairo::Context>& cr){

  Gtk::Allocation allocation = get_allocation();
  const int width = allocation.get_width();
  const int height = allocation.get_height();

  for (size_t i = 0; i < gui_sim.getBalls().size(); ++i)
  {
    Ball current = gui_sim.getBalls()[i];
    Point p(current.getBallCoordinates());

    int xf, yf;
    convCoords(width, height, p, xf, yf);

    cr->set_source_rgba(BLUE_BALLS);
    cr->arc(xf, yf, gui_sim.getBallRadius(), CIRCLE_ANGLE_BEGIN, CIRCLE_ANGLE_END);
    cr->fill();
    cr->stroke();
  }
}

bool MyArea::on_draw(const Cairo::RefPtr<Cairo::Context>& cr){
  drawObstacles(cr);
  drawBalls(cr);
  drawPlayers(cr);
  return true;
}

void MyArea::loadSimulation(std::string filename){
  int n = filename.length();
  char file_name[n + 1];
  strcpy(file_name, filename.c_str());
  gui_sim = sim_start(file_name);
  gui_map = gui_sim.getMap();
  if(gui_sim.isReadSuccessful()) simLoaded = true;
}

void MyArea::loadSimulation(char *file_name){
  gui_sim = sim_start(file_name);
  gui_map = gui_sim.getMap();
  if(gui_sim.isReadSuccessful()) simLoaded = true;
}

bool MyArea::isSimulationLoaded(){
  if(simLoaded) return true;
  else return false;
}


//--------------------------------------


MyEvent::MyEvent(char* file_name, int mode) :
mainBox(Gtk::ORIENTATION_VERTICAL), canvas(Gtk::ORIENTATION_HORIZONTAL),
buttonBox(Gtk::ORIENTATION_HORIZONTAL),
buttonExit("Exit"), buttonOpen("Open"), buttonSave("Save"), buttonStartStop("Start"),
buttonStep("Step"), message(" No Game To Run "),
timerAdded(false), disconnect(false), timeoutValue(DELTA_T_MILLIS)
  {
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
  if (mode == NORMAL){
    myArea.loadSimulation(file_name);
    if(myArea.isSimulationLoaded()) message.set_text(" Game ready to run ");
    if(myArea.gui_sim.isOver()){
      message.set_text(" Game over ! ");
      myArea.gui_sim.stop();
      buttonStartStop.set_label("Start");
      stopTimer();
    }
    else message.set_text(" No Game To Run ");
  }
  if (mode == NOFILE){
    myArea.gui_sim = sim_start_nofile();
    myArea.gui_map = myArea.gui_sim.getMap();
  }
}

MyEvent::~MyEvent(){
}

void MyEvent::on_button_clicked_buttonExit(){
  exit(0);
}

void MyEvent::on_button_clicked_buttonOpen(){
  if (!myArea.gui_sim.isRunning()){
    Gtk::FileChooserDialog dialog("Please choose a file to open",
    Gtk::FILE_CHOOSER_ACTION_OPEN);
    dialog.set_transient_for(*this);
    dialog.add_button("_Cancel", Gtk::RESPONSE_CANCEL);
    dialog.add_button("_Open", Gtk::RESPONSE_OK);
    int result = dialog.run();

    if(result == Gtk::RESPONSE_OK){
      std::string filename = dialog.get_filename();
      myArea.loadSimulation(filename);
      if (myArea.gui_sim.isReadSuccessful()){
        message.set_text(" Game ready to run ");
      }
      else message.set_text(" No Game To Run ");
    }
  }
}

void MyEvent::on_button_clicked_buttonSave(){
  Gtk::FileChooserDialog dialog("Please choose a file to save the simulation",
  Gtk::FILE_CHOOSER_ACTION_SAVE);
  dialog.set_transient_for(*this);
  dialog.add_button("_Cancel", Gtk::RESPONSE_CANCEL);
  dialog.add_button("_Save", Gtk::RESPONSE_OK);
  int result = dialog.run();

  if (result == Gtk::RESPONSE_OK){
    std::string filename = dialog.get_filename();
    int n = filename.length();
    char file_name[n + 1];
    strcpy(file_name, filename.c_str());

    myArea.gui_sim.saveToFile(file_name);
  }
}

void MyEvent::on_button_clicked_buttonStartStop(){
  if (myArea.isSimulationLoaded()){
    if (myArea.gui_sim.isRunning()){
      myArea.gui_sim.stop();
      buttonStartStop.set_label("Start");
      stopTimer();
    }
    else if (!myArea.gui_sim.isRunning()){
      myArea.gui_sim.start();
      buttonStartStop.set_label("Stop");
      startTimer();
    }
  }
}

void MyEvent::on_button_clicked_buttonStep(){
  myArea.gui_sim.simulate_one_step();
  myArea.refresh();
}

// Timer

void MyEvent::startTimer(){
  if(not timerAdded){
	  Glib::signal_timeout().connect( sigc::mem_fun(*this, &MyEvent::onTimeout),
									  timeoutValue );
	  timerAdded = true;
  }
}

void MyEvent::stopTimer()
{
  if(timerAdded){
    disconnect  = true;
    timerAdded = false;
  }
}

bool MyEvent::onTimeout()
{
  if(disconnect) {
	  disconnect = false;
	  return false;
  }
  myArea.gui_sim.simulate_one_step();
  myArea.refresh();
  return true;
}
