#define SAILS_COLOR_QUANTITY				8
#define SHIP_TYPES_QUANTITY					28
#define SHIP_TYPES_QUANTITY_WITH_FORT		30	// must be (SHIP_TYPES_QUANTITY + 1)

#define SHIP_TARTANE			0

#define SHIP_WAR_TARTANE		1

//6
#define SHIP_LUGGER				2
#define SHIP_SLOOP				3

//5
#define SHIP_SCHOONER			4
#define SHIP_BARQUE				5
#define SHIP_CARAVEL			6

//4
#define SHIP_BARKENTINE			7
#define SHIP_BRIGANTINE			8
#define SHIP_FLEUT				9
#define SHIP_BRIG				10
#define SHIP_GALEON_L			11

//3
#define SHIP_CORVETTE			12
#define SHIP_GALEON_H			13
#define SHIP_PINNACE			14

//2
#define SHIP_FRIGATE			15

//1
#define SHIP_LINESHIP			16
#define SHIP_WARSHIP			17
#define SHIP_BATTLESHIP			18

#define SHIP_MANOWAR			19

#define SHIP_SOLEYRU			20

#define SHIP_BRIGQEEN			21
#define SHIP_BRIGSW				22
#define SHIP_XebekVML			23
#define SHIP_CORVETTE_QUEST		24
#define SHIP_ARABELLA			25
#define SHIP_FLYINGDUTCHMAN		26
//
#define SHIP_BOAT               27
#define SHIP_FORT               28

#define SHIP_NOTUSED			 1000
#define SHIP_NOTUSED_TYPE_NAME	"Not Used"
#define SHIP_NAME_NOTUSED		"Noname"

object  ShipsTypes[SHIP_TYPES_QUANTITY_WITH_FORT];  // RealShips
object	SailsColors[SAILS_COLOR_QUANTITY];


ref GetShipByType(int iType) { return &ShipsTypes[iType]; }  // пользовать GetRealShip