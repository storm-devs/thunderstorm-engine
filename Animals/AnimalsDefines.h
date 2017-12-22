#ifndef _ANIMALSDEFINES_
#define _ANIMALSDEFINES_

#define PI 3.14159265358979323846f

extern char		  ANIMALS_INI_FILENAME[];
extern const char ANIMALS_SEAGULL_FILENAME[];
extern char		  ANIMALS_SEAGULLS_SECTION[];
extern char		  ANIMALS_SEAGULLS_SCREAM_FILENAME[];
extern const char ANIMALS_SHARK_FILENAME[];
extern char		  ANIMALS_SHARKS_SECTION[];
extern const char ANIMALS_FISHSCHOOL_FILENAME[];
extern char		  ANIMALS_FISHSCHOOLS_SECTION[];
extern const char ANIMALS_BUTTERFLY_FILENAME[];
extern char		  ANIMALS_BUTTERFLIES_SECTION[];

#define RESPAWN_DISTANCE			 70.0f
//seagull
#define SEAGULL_COUNT				 300
#define SEAGULL_ADD_COUNT			 20
#define SEAGULL_DISTANCE			 100.0f //mean distance between seagulls
#define SEAGULL_MAX_RADIUS			 60
#define SEAGULL_MAX_SPEED			 30
#define SEAGULL_MAX_HEIGHT			 50
#define SEAGULL_MAX_CIRCLE_TIME      1000
#define SEAGULL_LONG_DISTANCE_CHANCE 4 
#define SEAGULL_RELAX_TIME			 20000
#define SEAGULL_SCREAM_TIME			 15000
#define SEAGULL_SCREAM_MAX_DISTANCE  350.0f
#define SEAGULL_SCREAM_MIN_DISTANCE  35.0f
#define SEAGULL_MIN_HEIGHT			 40.0f
#define SEAGULL_MIN_RADIUS			 2.0f

//shark
#define SHARK_COUNT				   200
#define SHARK_DISTANCE			   30.0f 
#define SHARK_MAX_RADIUS		   30
#define SHARK_MAX_SPEED			   30
#define SHARK_MAX_HEIGHT		   10
#define SHARK_MAX_CIRCLE_TIME	   1000
#define SHARK_LONG_DISTANCE_CHANCE 4 
#define SHARK_MAX_CHANGE_TICKS	   1000
#define SHARK_CHANGE_Y			   0.08f
#define SHARK_MIN_RADIUS		   60.0f
#define SHARK_MAX_SHIPS			   50

//fish school
#define FISHSCHOOL_COUNT			    200
#define FISHSCHOOL_DISTANCE			    100.0f 
#define FISHSCHOOL_MAX_RADIUS		    60
#define FISHSCHOOL_MAX_SPEED		    30
#define FISHSCHOOL_MAX_HEIGHT		    50
#define FISHSCHOOL_MAX_CIRCLE_TIME	    1000
#define FISHSCHOOL_LONG_DISTANCE_CHANCE 4 
#define FISHSCHOOL_FISH_COUNT           10
#define FISHSCHOOL_FISH_MAX_RADIUS      4.0f

//butterfly
#define BUTTERFLY_COUNT					200
#define BUTTERFLY_DISTANCE			    100.0f 
#define BUTTERFLY_MAX_RADIUS		    60

#endif