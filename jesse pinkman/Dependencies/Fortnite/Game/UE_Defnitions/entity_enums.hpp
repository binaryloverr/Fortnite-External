#include "../../../Kernel/driver.hpp"
#include "../../../../Includes/Definitions/hex_definitions.hpp"


enum EBoneIndex : int {
	Head = 110,
	Neck = 67,
	Chest = 66,
	Pelvis = 2,
	LShoulder = 9,
	LElbow = 10,
	LHand = 11,
	RShoulder = 38,
	RElbow = 39,
	RHand = 40,
	LHip = 71,
	LKnee = 72,
	LFoot = 73,
	RHip = 78,
	RKnee = 79,
	RFoot = 82,
	root = 0
};

enum bones : int
{
	HumanBase = 0,
	HumanPelvis = 2,
	HumanLThigh1 = 71,
	HumanLThigh2 = 77,
	HumanLThigh3 = 72,
	HumanLCalf = 74,
	HumanLFoot = 86,
	HumanLToe = 76,
	HumanRThigh1 = 78,
	HumanRThigh2 = 84,
	HumanRThigh3 = 79,
	HumanRCalf = 81,
	HumanRFoot = 87,
	HumanRToe = 83,
	HumanSpine1 = 7,
	HumanSpine2 = 5,
	HumanSpine3 = 2,
	HumanLCollarbone = 9,
	HumanLUpperarm = 35,
	HumanLForearm1 = 36,
	HumanLForearm23 = 10,
	HumanLForearm2 = 34,
	HumanLForearm3 = 33,
	HumanLPalm = 32,
	HumanRCollarbone = 98,
	HumanRUpperarm = 64,
	HumanRForearm1 = 65,
	HumanRForearm23 = 39,
	HumanRForearm2 = 63,
	HumanRForearm3 = 62,
	HumanRPalm = 58,
	HumanNeck = 67,
	HumanHead = 110,
	HumanChest = 66
};

enum offset {

	PrimaryPickupItemEntry = 0x350, // Class FortniteGame.FortPawn -> enum class EFortPickupSpawnSource PrimaryPickupItemEntry;
	displayname = 0x40, // Class ItemizationCoreRuntime.ItemDefinitionBase -> struct FText ItemName;
	tier = 0x9B, // Class FortniteGame.FortItemDefinition -> enum class EFortRarity Rarity;
	last_sumbit = 0x2E8, // Class Engine.Actor -> float LastSumbit; // Class Engine.SceneComponent -> struct FVector RelativeLocation;
	last_render = 0x2F0, // Class Engine.Actor -> float LastRender;
	kills = 0x1224, // Class FortniteGame.AActor -> int32_t Kills;
	levels = 0x178, // Class Engine.World -> struct TArray<struct ULevel*> Levels;
	bone_array = 0x5B8, // Class Engine.SkinnedMeshComponent -> struct TArray<int> BoneArray;
	pname = 0xAB0, // Class FortniteGame.APlayerState -> struct FName PName;
};

template< typename t >
class TArray
{
public:

	TArray() : tData(), iCount(), iMaxCount() { }
	TArray(t* data, int count, int max_count) :
		tData(tData), iCount(iCount), iMaxCount(iMaxCount) { }

public:

	auto Get(int idx) -> t
	{
		return device_().read< t >(reinterpret_cast<__int64>(this->tData) + (idx * sizeof(t)));
	}

	auto Size() -> std::uint32_t
	{
		return this->iCount;
	}

	bool IsValid()
	{
		return this->iCount != 0;
	}

	t* tData;
	int iCount;
	int iMaxCount;
};

uintptr_t TargetedFortPawn( ) {

	auto& cache = GameCache::Cache::getInstance( );

	readaddy( uintptr_t, cache.get_pcontroller( ).value_or( 0 ), 0x18c8 );
}