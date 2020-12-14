#pragma once
#include "../vector.h"

struct CUserCmd
{
	virtual ~CUserCmd() {};
	int command_number;
	int tick_count;
	QAngle viewangles;
	QAngle aimdirection;
	float forwardmove;
	float sidemove;
	float upmove;
	int buttons;
	unsigned char impulse;
	int weaponselect;
	int weaponsubtype;
	int random_seed;
	short mousedx;
	short mousedy;
	bool hasbeenpredicted;
	QAngle headangles;
	Vector headoffset;
};

class IClientMode {};