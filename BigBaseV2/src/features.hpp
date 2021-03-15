#pragma once
#include "common.hpp"
#include "gta_util.hpp"
#include "natives.hpp"

namespace big
{
	const int PED_MAX = 1000;
	const int TIME_THINK = 10000;
	const int MIN_FOLLOW = 100;
	const int SPEED_FAST = 100;
	const int DISTANCE_SPAWN = 20;
	const int PLANE_ATTACK = 6;
	const int PLANE_FOLLOW = 7;
	const int MAX_SWARM = 100;

	//const int SWARM = 1;
	//const int PED_PLAYER = 1;
	//const int PED_DISTANCE = 1000;
	//const int TIME_OUT = 60000;
	//const int DISTANCE_TARGET = 100;
	//const int PED_FOLLOW = 7;

	struct PedList {
		int32_t size;//still 32 bit integer
		Entity entities[PED_MAX];
	};

	class Me
	{
	public:
		Ped me_ped = PLAYER::PLAYER_PED_ID();
		Player me_player = PLAYER::PLAYER_ID();
		Vector3 me_pos = ENTITY::GET_ENTITY_COORDS(me_ped, true);
		Vector3 me_forward = ENTITY::GET_ENTITY_FORWARD_VECTOR(me_ped);
		float me_heading = ENTITY::GET_ENTITY_HEADING(me_ped);
		int me_group = PLAYER::GET_PLAYER_GROUP(me_player);

		Me() {}
	};

	class Swarm
	{
	public:
		Ped ped;
		Vehicle vehicle;
		Ped target = -1;
		bool is_plane;
		bool is_first = true;
		bool is_gearup = false;

		Swarm(Ped _ped, Vehicle _vehicle, bool _is_plane)
		{
			ped = _ped;
			vehicle = _vehicle;
			is_plane = _is_plane;
		}
	};

	class Features
	{
	public:
		static void script_func();
	public:
		bool m_opened{};

		Features() {};

		static int iSwarm;
		static Swarm *aSwarm[MAX_SWARM];

		static int iEntity;
		static Entity aEntity[MAX_SWARM];

		static bool IsFriendly(Ped ped, Ped me_ped);
		static Ped GetTarget(Ped ped, Ped me_ped);

		static void SpawnVehicle(const char* name);
		//static void SwarmPed(const char* name);
		static void SwarmVehicle(const char* tank_name, const char* ped_name, bool plane);

		static Vehicle CreateVehicle(rage::joaat_t hash, Vector3 pos, float heading);
		static Ped CreatePed(rage::joaat_t hash, Vector3 pos, int group, Vehicle vehicle = 0);

		static void God();
		static void Mortal();

		static void Features::UpdateAI();
	};
	inline Features g_features;
}
