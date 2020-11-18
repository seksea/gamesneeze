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

class IClientMode {
public:
	virtual			~IClientMode() {}

	virtual int ClientModeCSNormal(void *) = 0;
	// Called before the HUD is initialized.
	virtual void	InitViewport()=0;

	// One time init when .dll is first loaded.
	virtual void	Init()=0;

	// Called when vgui is shutting down.
	virtual void	VGui_Shutdown() = 0;

	// One time call when dll is shutting down
	virtual void	Shutdown()=0;

	// Called when switching from one IClientMode to another.
	// This can re-layout the view and such.
	// Note that Enable and Disable are called when the DLL initializes and shuts down.
	virtual void	Enable()=0;

	// Called when it's about to go into another client mode.
	virtual void	Disable()=0;

	// Called when initializing or when the view changes.
	// This should move the viewport into the correct position.
	virtual void	Layout(bool bForce = false)=0;

	// called every time shared client dll/engine data gets changed,
	// and gives the cdll a chance to modify the data.
	virtual void	ProcessInput( bool bActive ) = 0;

	// The mode can choose to draw/not draw entities.
	virtual bool	ShouldDrawDetailObjects( ) = 0;
	virtual bool	ShouldDrawEntity(/*C_BaseEntity*/ void* pEnt) = 0;
	virtual bool	ShouldDrawLocalPlayer(/*C_BaseEntity*/ void* pPlayer ) = 0;
	virtual bool	ShouldDrawParticles( ) = 0;

	// The mode can choose to not draw fog
	virtual bool	ShouldDrawFog( void ) = 0;

	virtual void	OverrideView( /*CViewSetup*/void* pSetup ) = 0;
	virtual int		KeyInput( int down, /*ButtonCode_t*/void* keynum, const char *pszCurrentBinding ) = 0;
	virtual void	StartMessageMode( int iMessageModeType ) = 0;
	virtual void	OverrideMouseInput( float *x, float *y ) = 0;
	virtual bool	CreateMove( float flInputSampleTime, CUserCmd *cmd ) = 0;
};