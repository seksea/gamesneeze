#pragma once

//https://github.com/ValveSoftware/source-sdk-2013/blob/0d8dceea4310fde5706b3ce1c70609d72a38efdf/mp/src/public/globalvars_base.h#L19
class CGlobalVars
{
public:
	// Absolute time (per frame still - Use Plat_FloatTime() for a high precision real time 
	//  perf clock, but not that it doesn't obey host_timescale/host_framerate)
	float realtime;
	// Absolute frame counter
	int framecount;
	// Non-paused frametime
	float absoluteframetime;
	float absoluteframestarttimestddev;
	// Current time 
	//
	// On the client, this (along with tickcount) takes a different meaning based on what
	// piece of code you're in:
	// 
	//   - While receiving network packets (like in PreDataUpdate/PostDataUpdate and proxies),
	//     this is set to the SERVER TICKCOUNT for that packet. There is no interval between
	//     the server ticks.
	//     [server_current_Tick * tick_interval]
	//
	//   - While rendering, this is the exact client clock 
	//     [client_current_tick * tick_interval + interpolation_amount]
	//
	//   - During prediction, this is based on the client's current tick:
	//     [client_current_tick * tick_interval]
	float curtime;
	// Time spent on last server or client frame (has nothing to do with think intervals)
	float frametime;
	// current maxplayers setting
	int maxClients;
	// Simulation ticks
	int tickcount;
	// Simulation tick interval
	float interval_per_tick;
	// interpolation amount ( client-only ) based on fraction of next tick which has elapsed
	float interpolation_amount;
	int simTicksThisFrame;
	int network_protocol;
	// current saverestore data

	void* pSaveData;
	// Set to true in client code.
	bool m_bClient;
	bool m_bRemoteClient;
private:
	// These are unused so commenting them
	// int nTimestampNetworkingBase;
	// int nTimestampRandomizeWindow;
};