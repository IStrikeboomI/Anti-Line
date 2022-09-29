#pragma once
#include "../../ITickable.h"
#include "../../Paintable.h"
#include "../Pos.h"
class LoseText : public ITickable, public Paintable {
private:
	Pos pos;
	int fadeTime = 0;
public:
	static constexpr int DISPLAY_TIME = 60;
	LoseText();

	void update() override;
	//we only want to draw when the game is not in round and a loss
	bool canDraw() override;
	void draw(Gdiplus::Graphics& g) const override;
};

