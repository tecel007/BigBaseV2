#include "common.hpp"
#include "features.hpp"
#include "fiber_pool.hpp"
#include "script.hpp"

namespace big
{
	void Features::SpawnVehicle(const char* name)
	{
		g_fiber_pool->queue_job([name]
		{
			auto me_ped = PLAYER::PLAYER_PED_ID();
			auto me_player = PLAYER::PLAYER_ID();
			auto me_pos = ENTITY::GET_ENTITY_COORDS(me_ped, TRUE);
			auto me_forward = ENTITY::GET_ENTITY_FORWARD_VECTOR(me_ped);
			auto me_heading = ENTITY::GET_ENTITY_HEADING(me_ped);
			auto me_group = PLAYER::GET_PLAYER_GROUP(me_player);

			rage::joaat_t hash = rage::joaat(name);

			Vector3 spawn_pos;

			spawn_pos.x = me_pos.x + DISTANCE_SPAWN * me_forward.x;
			spawn_pos.y = me_pos.y + DISTANCE_SPAWN * me_forward.y;

			auto vehicle = CreateVehicle(hash, spawn_pos, me_heading + 90);
		});
	}

	Vehicle Features::CreateVehicle(rage::joaat_t hash, Vector3 pos, float heading)
	{
		while (!STREAMING::HAS_MODEL_LOADED(hash))
		{
			STREAMING::REQUEST_MODEL(hash);
			script::get_current()->yield();
		}

		GAMEPLAY::GET_GROUND_Z_FOR_3D_COORD(pos.x, pos.y, pos.z, &pos.z, 0);

		auto vehicle = VEHICLE::CREATE_VEHICLE(hash, pos.x, pos.y, pos.z, heading, TRUE, TRUE);

		ENTITY::SET_ENTITY_INVINCIBLE(vehicle, TRUE);

		ENTITY::SET_ENTITY_CAN_BE_DAMAGED(vehicle, FALSE);

		VEHICLE::SET_VEHICLE_CAN_BE_TARGETTED(vehicle, FALSE);

		VEHICLE::SET_VEHICLE_CAN_BREAK(vehicle, FALSE);

		VEHICLE::SET_VEHICLE_ENGINE_CAN_DEGRADE(vehicle, FALSE);

		VEHICLE::SET_VEHICLE_CAN_BE_VISIBLY_DAMAGED(vehicle, FALSE);

		//STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(hash);

		return vehicle;
	}

	void Features::God() 
	{
		g_fiber_pool->queue_job([]
		{
			PLAYER::SET_PLAYER_INVINCIBLE(PLAYER::PLAYER_ID(), TRUE);
		});
	}
	
	void Features::Mortal() 
	{
		g_fiber_pool->queue_job([]
		{
			PLAYER::SET_PLAYER_INVINCIBLE(PLAYER::PLAYER_ID(), FALSE);
		});
	}

	void Features::script_func()
	{
		God();

		while (true)
		{
			script::get_current()->yield();
		}
	}
}