#pragma once

#include "Timer.hpp"

Timer::Timer() {
	tickCounter = 0;
	period = 50;
}
Timer::Timer(int p) {
	tickCounter = 0;
	period = p;
}
void Timer::set(int p) {
	tickCounter = 0;
	period = p;
}
void Timer::reset() { tickCounter = 0; }
void Timer::tick() { tickCounter++; }
bool Timer::triggerAction() {
	if (tickCounter > period) {
		tickCounter = 0;
		return true;
	}
	return false;
}
	