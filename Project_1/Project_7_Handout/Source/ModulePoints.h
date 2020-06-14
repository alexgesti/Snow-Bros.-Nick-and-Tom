#ifndef __MODULE_POINTS_H__
#define __MODULE_POINTS_H__

#include "Module.h"

class ModulePoints : public Module
{
public:
	ModulePoints(bool startEnabled);

	//Destructor
	~ModulePoints();
	bool Start() override;
	void returnPoints();

	//Fonts 
	int score = 000;
	int scoreTotal = 000;
	int scoreFont = -1;
	char scoreText[10] = { "\0" };


};
#endif // __ModulePoints_H