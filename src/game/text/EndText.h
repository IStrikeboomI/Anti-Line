#pragma once
#include "../GameObject.h"
#include "../Pos.h"
#include "../RoundStatus.h"
//an abstract class used for the text shown when a round is beaten
//inherited by LoseText and WinText
class EndText : public GameObject{
protected:
	Pos pos;
	int fadeTime = 0;
	RoundStatus statusToShowOn;
public:
	static constexpr int DISPLAY_TIME = 60;
	EndText(RoundStatus statusToShowOn);

	void update() override;
	//we only want to draw when the game is not in round and the desired status is on
	bool canDraw() override;
	virtual void draw(Gdiplus::Graphics& g) const = 0;
};

