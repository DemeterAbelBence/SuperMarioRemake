#pragma once

class Timer{

private:
	int tickCounter;
	int period;

public:
	Timer();
	Timer(int p);
	void set(int p);
	void reset();
	void tick();
	bool triggerAction();
};
