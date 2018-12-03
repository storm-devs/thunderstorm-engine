#define MAX_RUMOURS 30  // длина стека слухов
#include "scripts\Rumour_templates.c"
#include "scripts\Rumour_func.c"
#include "scripts\Rumour_generate.c"
#include "TEXT\scripts\Rumour_Data.h"
#include "scripts\GoldFleet.c"

object	Rumour[MAX_RUMOURS]; // стек слухов
object RumourParams;         // дерево переменных дл€ шаблонных слухов

int id_counter;




void SetRumourDefaults()// заполн€ем стек начальными - простыми слухами
{
	int i;
	ref CurrentRumour;
	id_counter = 0;

	for(i = 0; i < MAX_RUMOURS; i++)
	{
		makeref(CurrentRumour, Rumour[i]);
		CurrentRumour.id = id_counter;  // ID слуха
		CurrentRumour.text = DEFAULT_TEXT[i];// ѕодгружаем начальные слухи в очередь
		CurrentRumour.state = "1"; // —колько раз может повтор€ть с€ один и тот же слух
		CurrentRumour.tip = "citizen,capitan"; // типаж
		CurrentRumour.rep = "none" // репутаци€
		CurrentRumour.starttime = (DateToInt(0));// через сколько дней активировать слух
		CurrentRumour.actualtime = (DateToInt(40));//  ак долго могут ходить слухи = 40 дней
		CurrentRumour.event = "none"; // ƒействие - нет
		CurrentRumour.next = "none"; // ѕродолжение - нет
		id_counter++; // счетчик слухов
	}
	for(i = 0; i < 9; i++)
	{
		makeref(CurrentRumour, Rumour[i]);
		CurrentRumour.id = id_counter;  // ID слуха
		CurrentRumour.text = POOR_RUMOUR_TEXT[i];// ѕодгружаем начальные слухи в очередь
		CurrentRumour.state = "5"; // —колько раз может повтор€ть с€ один и тот же слух
		CurrentRumour.tip = "poor"; // типаж
		CurrentRumour.rep = "none" // репутаци€
		CurrentRumour.starttime = (DateToInt(0));// через сколько дней активировать слух
		CurrentRumour.actualtime = (DateToInt(300));//  ак долго могут ходить слухи = 300 дней
		CurrentRumour.event = "none"; // ƒействие - нет
		CurrentRumour.next = "none"; // ѕродолжение - нет
		id_counter++; // счетчик слухов
	}
	makeref(CurrentRumour, Rumour[i]);
	CurrentRumour.id = id_counter;  // ID слуха
	CurrentRumour.text = xiDStr("Rummor_1");
	CurrentRumour.state = "1"; // —колько раз может повтор€ть с€ один и тот же слух
	CurrentRumour.tip = "citizen"; // типаж
	CurrentRumour.City = "PortSpein";
	CurrentRumour.rep = "none" // репутаци€
	CurrentRumour.starttime = (DateToInt(0));// через сколько дней активировать слух
	CurrentRumour.actualtime = (DateToInt(500));
	CurrentRumour.event = "none"; // ƒействие - нет
	CurrentRumour.next = "none"; // ѕродолжение - нет
	id_counter++; // счетчик слухов
}

void RumourInit();
{
	trace("RumourInit!");
	TemplateLoad();
	SetRumourDefaults();
	// ==> отметка времени дл€ осад homo 05/11/06
	SaveCurrentQuestDateParam("Siege_DailyUpdate");
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////