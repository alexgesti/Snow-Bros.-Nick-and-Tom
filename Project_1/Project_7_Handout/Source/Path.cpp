#include "Path.h"

#include "Animation.h"

void Path::PushBack(fPoint speed, uint frames, Animation* animation)
{
	steps[totalSteps].animation = animation;
	steps[totalSteps].framesDuration = frames;
	steps[totalSteps].speed = speed;
	totalSteps++;
}

void Path::Update(int ran, bool SL, bool SR, bool clear)
{
	currentStepFrame += 1;

	if (currentStepFrame > steps[currentStep].framesDuration)
	{
		if (ran == 0) {
			if (SR) {
				currentStep = totalSteps;
			}
			if (SL) {
				currentStep = 0;
			}
		}
		if (ran == 1) {
			if (SL) {
				currentStep = totalSteps;
			}
			if (SR) {
				currentStep = 0;
			}
		}

		if (currentStep < totalSteps - 1) // If it is not the last step, advance
		{
			currentStep++;
		}
		else if (loop) // Otherwise, if the path loops, go back to the beginning
		{
			currentStep = 0;
		}
		currentStepFrame = 0;
	}

	if (clear == false) {
		relativePosition += steps[currentStep].speed;
	}
}

iPoint Path::GetRelativePosition() const
{
	return iPoint((int)relativePosition.x, (int)relativePosition.y);
}

Animation* Path::GetCurrentAnimation()
{
	return steps[currentStep].animation;
}

void Path::Reset()
{
	currentStepFrame = 0;
	currentStep = 0;
}