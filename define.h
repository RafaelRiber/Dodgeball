// EPFL - Programmation Orientée Projet (en C++) - COM-112(a)
// Projet Dodgeball
// Auteurs: Rafael RIBER  - SCIPER: 296142
//          Valentin RIAT - SCIPER: 289121

#ifndef HEADER_DEFINE_H
#define HEADER_DEFINE_H


#define MIN_CELL			3
#define MAX_TOUCH			4
#define MAX_COUNT			20
#define DELTA_T				0.0625

#define DIM_MAX 			400
#define SIDE				(2. * DIM_MAX)

#define COEF_RAYON_JOUEUR 	0.25
#define COEF_VITESSE_JOUEUR 1.0
#define COEF_RAYON_BALLE 	0.125
#define COEF_VITESSE_BALLE	1.25

#define COEF_MARGE_JEU		(1./256)

#define MAXLINE				80

#define DELTA_L_DIVIDER		10	

#define READING_SUCCESS true
#define READING_FAIL    false
#define MARGIN_DIVIDER  2
#define FIRST_ARG   1
#define SECOND_ARG  2
#define THIRD_ARG   3
enum ModeList{ERROR,STEP,NORMAL,NOFILE};
enum ReadState {NBCELL,NBPLAYERS,PLAYERPOS,NBOBST,OBSTPOS,NBBALLS,BALLS};

#define MAX_TARGET_DISTANCE 2000

// Define colors for GUI
#define BROWN_OBSTACLES 0.43,0.00,0.00,1.00
#define GREEN_PLAYER    0.00,1.00,0.00,1.00
#define YELLOW_PLAYER   0.92,1.00,0.00,1.00
#define ORANGE_PLAYER   1.00,0.62,0.00,1.00
#define RED_PLAYER      1.00,0.00,0.00,1.00
#define BLUE_BALLS      0.00,0.00,1.00,1.00

// Define GUI constants
#define CIRCLE_ANGLE_BEGIN 0.0
#define CIRCLE_ANGLE_END 2.0 * M_PI
#define BUTTON_BOX_HEIGHT 20
#define DIM_NOT_FORCED    -1

#endif
