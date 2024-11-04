#include <xmmintrin.h>
#include <immintrin.h>
#include <d3d9types.h>
#include <corecrt_math_defines.h>
#include <mutex>
#include <thread>
#include <vector>
#include <optional>
#include <cstdint>
#include <chrono>
#include <cstdio>
#include <iostream>
#define PI 3.14159265358979323846f

class fvector2d
{
public:
	double x;
	double y;
	double z;
	bool is_Zero( ) {
		return ( x == 0 ) && ( y == 0 );
	}
	fvector2d() : x(0), y(0) {}
	fvector2d(double _x, double _y) : x(_x), y(_y) {}

	// Add a constructor from ImVec2
	fvector2d(const ImVec2& vec) : x(vec.x), y(vec.y) {}

	// Addition
	fvector2d operator+(const fvector2d& other) const {
		return fvector2d(x + other.x, y + other.y);
	}

	// Subtraction
	fvector2d operator-(const fvector2d& other) const {
		return fvector2d(x - other.x, y - other.y);
	}

	// Multiplication by scalar
	fvector2d operator*(double scalar) const {
		return fvector2d(x * scalar, y * scalar);
	}

	// Division by scalar
	fvector2d operator/(double scalar) const {
		return fvector2d(x / scalar, y / scalar);
	}

	// Conversion to ImVec2
	operator ImVec2() const {
		return ImVec2(static_cast<float>(x), static_cast<float>(y));
	}

	bool is_zero()
	{
		if (x == 0 && y == 0 && z == 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
};

class fvector
{
public:
	fvector( ) : x( 0.f ), y( 0.f ), z( 0.f )
	{

	}

	fvector( double _x, double _y, double _z ) : x( _x ), y( _y ), z( _z )
	{

	}
	~fvector( )
	{

	}

	double x;
	double y;
	double z;

	bool operator==(const fvector& v) const {
		return (x == v.x) && (y == v.y) && (z == v.z);
	}

	// Inequality operator
	bool operator!=(const fvector& v) const {
		return !(*this == v);
	}

	 double Dot( fvector v )
	{
		return x * v.x + y * v.y + z * v.z;
	}
	 double distance( fvector v )
	{
		return double( sqrtf( powf( v.x - x, 2.0 ) + powf( v.y - y, 2.0 ) + powf( v.z - z, 2.0 ) ) );
	}

	 double Length( fvector v )
	{
		return sqrt( x * x + y * y + z * z );
	}

	fvector operator+( fvector v )
	{
		return fvector( x + v.x, y + v.y, z + v.z );
	}

	fvector operator-( fvector v )
	{
		return fvector( x - v.x, y - v.y, z - v.z );
	}

	fvector operator*( double number ) const
	{
		return fvector( x * number, y * number, z * number );
	}

	void print() const {
		std::cout << "x: " << x << ", y: " << y << ", z: " << z << std::endl;
	}
};


struct fplane : fvector
{
	double W = 0;


	fvector ToVector3( )
	{
		fvector value;
		value.x = this->x;
		value.y = this->y;
		value.z = this->y;

		return value;
	}
};

struct fquat
{
	double x;
	double y;
	double z;
	double w;
};

struct fmatrix
{
	fplane XPlane;
	fplane YPlane;
	fplane ZPlane;
	fplane WPlane;
};

struct ftransform
{
	fplane  rot;
	fvector translation;
	char    pad[8];
	fvector scale;

	D3DMATRIX ToMatrixWithScale( )
	{
		D3DMATRIX m;
		m._41 = translation.x;
		m._42 = translation.y;
		m._43 = translation.z;

		double x2 = rot.x + rot.x;
		double y2 = rot.y + rot.y;
		double z2 = rot.z + rot.z;

		double xx2 = rot.x * x2;
		double yy2 = rot.y * y2;
		double zz2 = rot.z * z2;
		m._11 = ( 1.0f - ( yy2 + zz2 ) ) * scale.x;
		m._22 = ( 1.0f - ( xx2 + zz2 ) ) * scale.y;
		m._33 = ( 1.0f - ( xx2 + yy2 ) ) * scale.z;

		double yz2 = rot.y * z2;
		double wx2 = rot.W * x2;
		m._32 = ( yz2 - wx2 ) * scale.z;
		m._23 = ( yz2 + wx2 ) * scale.y;

		double xy2 = rot.x * y2;
		double wz2 = rot.W * z2;
		m._21 = ( xy2 - wz2 ) * scale.y;
		m._12 = ( xy2 + wz2 ) * scale.x;

		double xz2 = rot.x * z2;
		double wy2 = rot.W * y2;
		m._31 = ( xz2 + wy2 ) * scale.z;
		m._13 = ( xz2 - wy2 ) * scale.x;

		m._14 = 0.0f;
		m._24 = 0.0f;
		m._34 = 0.0f;
		m._44 = 1.0f;

		return m;
	}
};

D3DMATRIX MatrixMultiplication( D3DMATRIX pM1, D3DMATRIX pM2 )
{
	D3DMATRIX pOut;
	pOut._11 = pM1._11 * pM2._11 + pM1._12 * pM2._21 + pM1._13 * pM2._31 + pM1._14 * pM2._41;
	pOut._12 = pM1._11 * pM2._12 + pM1._12 * pM2._22 + pM1._13 * pM2._32 + pM1._14 * pM2._42;
	pOut._13 = pM1._11 * pM2._13 + pM1._12 * pM2._23 + pM1._13 * pM2._33 + pM1._14 * pM2._43;
	pOut._14 = pM1._11 * pM2._14 + pM1._12 * pM2._24 + pM1._13 * pM2._34 + pM1._14 * pM2._44;
	pOut._21 = pM1._21 * pM2._11 + pM1._22 * pM2._21 + pM1._23 * pM2._31 + pM1._24 * pM2._41;
	pOut._22 = pM1._21 * pM2._12 + pM1._22 * pM2._22 + pM1._23 * pM2._32 + pM1._24 * pM2._42;
	pOut._23 = pM1._21 * pM2._13 + pM1._22 * pM2._23 + pM1._23 * pM2._33 + pM1._24 * pM2._43;
	pOut._24 = pM1._21 * pM2._14 + pM1._22 * pM2._24 + pM1._23 * pM2._34 + pM1._24 * pM2._44;
	pOut._31 = pM1._31 * pM2._11 + pM1._32 * pM2._21 + pM1._33 * pM2._31 + pM1._34 * pM2._41;
	pOut._32 = pM1._31 * pM2._12 + pM1._32 * pM2._22 + pM1._33 * pM2._32 + pM1._34 * pM2._42;
	pOut._33 = pM1._31 * pM2._13 + pM1._32 * pM2._23 + pM1._33 * pM2._33 + pM1._34 * pM2._43;
	pOut._34 = pM1._31 * pM2._14 + pM1._32 * pM2._24 + pM1._33 * pM2._34 + pM1._34 * pM2._44;
	pOut._41 = pM1._41 * pM2._11 + pM1._42 * pM2._21 + pM1._43 * pM2._31 + pM1._44 * pM2._41;
	pOut._42 = pM1._41 * pM2._12 + pM1._42 * pM2._22 + pM1._43 * pM2._32 + pM1._44 * pM2._42;
	pOut._43 = pM1._41 * pM2._13 + pM1._42 * pM2._23 + pM1._43 * pM2._33 + pM1._44 * pM2._43;
	pOut._44 = pM1._41 * pM2._14 + pM1._42 * pM2._24 + pM1._43 * pM2._34 + pM1._44 * pM2._44;

	return pOut;
}

D3DMATRIX Matrix( fvector rot, fvector origin = fvector( 0, 0, 0 ) )
{
	float radPitch = ( rot.x * float( M_PI ) / 180.f );
	float radYaw = ( rot.y * float( M_PI ) / 180.f );
	float radRoll = ( rot.z * float( M_PI ) / 180.f );

	float SP = sinf( radPitch );
	float CP = cosf( radPitch );
	float SY = sinf( radYaw );
	float CY = cosf( radYaw );
	float SR = sinf( radRoll );
	float CR = cosf( radRoll );

	D3DMATRIX matrix;
	matrix.m[0][0] = CP * CY;
	matrix.m[0][1] = CP * SY;
	matrix.m[0][2] = SP;
	matrix.m[0][3] = 0.f;

	matrix.m[1][0] = SR * SP * CY - CR * SY;
	matrix.m[1][1] = SR * SP * SY + CR * CY;
	matrix.m[1][2] = -SR * CP;
	matrix.m[1][3] = 0.f;

	matrix.m[2][0] = -(CR * SP * CY + SR * SY);
	matrix.m[2][1] = CY * SR - CR * SP * SY;
	matrix.m[2][2] = CR * CP;
	matrix.m[2][3] = 0.f;

	matrix.m[3][0] = origin.x;
	matrix.m[3][1] = origin.y;
	matrix.m[3][2] = origin.z;
	matrix.m[3][3] = 1.f;

	return matrix;
}

class frotator
{
public:
	frotator( ) : Pitch( 0.f ), Yaw( 0.f ), Roll( 0.f )
	{

	}

	frotator( double _Pitch, double _Yaw, double _Roll) : Pitch( _Pitch ), Yaw( _Yaw ), Roll( _Roll )
	{

	}
	~frotator( )
	{

	}

	double Pitch;
	double Yaw;
	double Roll;
	frotator get( ) {
		return frotator( Pitch, Yaw, Roll );
	}
	void set( double _Pitch, double _Yaw, double _Roll ) {
		Pitch = _Pitch;
		Yaw = _Yaw;
		Roll = _Roll;
	}

	frotator Clamp( ) {
		frotator result = get( );
		if ( result.Pitch > 180 )
			result.Pitch -= 360;
		else if ( result.Pitch < -180 )
			result.Pitch += 360;
		if ( result.Yaw > 180 )
			result.Yaw -= 360;
		else if ( result.Yaw < -180 )
			result.Yaw += 360;
		if ( result.Pitch < -89 )
			result.Pitch = -89;
		if ( result.Pitch > 89 )
			result.Pitch = 89;
		while ( result.Yaw < -180.0f )
			result.Yaw += 360.0f;
		while ( result.Yaw > 180.0f )
			result.Yaw -= 360.0f;

		result.Roll = 0;
		return result;

	}
	double Length( ) {
		return sqrt( Pitch * Pitch + Yaw * Yaw + Roll * Roll );
	}

	frotator operator+( frotator angB ) { return frotator( Pitch + angB.Pitch, Yaw + angB.Yaw, Roll + angB.Roll ); }
	frotator operator-( frotator angB ) { return frotator( Pitch - angB.Pitch, Yaw - angB.Yaw, Roll - angB.Roll ); }
	frotator operator/( float flNum ) { return frotator( Pitch / flNum, Yaw / flNum, Roll / flNum ); }
	frotator operator*( float flNum ) { return frotator( Pitch * flNum, Yaw * flNum, Roll * flNum ); }
	bool operator==( frotator angB ) { return Pitch == angB.Pitch && Yaw == angB.Yaw && Yaw == angB.Yaw; }
	bool operator!=( frotator angB ) { return Pitch != angB.Pitch || Yaw != angB.Yaw || Yaw != angB.Yaw; }

};

static double get_cross_distance( double x1, double y1, double x2, double y2 ) {
	return sqrtf( powf ( ( x2 - x1 ), 2 ) + powf ( ( y2 - y1 ), 2 ) );
}

struct entities
{

	uintptr_t
		entity_,
		mesh_,
		root_,
		pstate_,
		local_player_state_;
	entities( )
		: entity_(0), mesh_(0), root_(0), pstate_(0), local_player_state_(0) {}
};
std::vector<entities> cached_list;

std::vector<entities> entity_list;

#define read_addy( TYPE, ADDRESS, OFFSET ) ( device_( ).read<TYPE>((ADDRESS) + (OFFSET)))

#define readaddy( TYPE, BASE, OFFSET ) \
    return device_( ).read<TYPE>( (BASE) + (OFFSET));

namespace GameCache {

	class publici {
	public:
		class apply_offsets {
		public:
			static apply_offsets& getInstance() {
				static apply_offsets Instance;
				return Instance;
			}

				uintptr_t uworld_() { return 0x11ECD148; }
				uintptr_t game_instance_() { return 0x1D8; }
				uintptr_t game_state_() { return 0x160; }
				uintptr_t local_player_() { return 0x38; }
				uintptr_t player_controller_() { return 0x30; }
				uintptr_t local_pawn_() { return 0x338; }
				uintptr_t mesh_() { return 0x310; }
				uintptr_t pstate_() { return 0x2B0; }
				uintptr_t root_() { return 0x198; }
				uintptr_t relative_loc_() { return 0x120; }
				uintptr_t team_id_() { return 0x11d1; }
				uintptr_t location_ptr_() { return 0x110; }
				uintptr_t rotation_ptr_() { return 0x120; }
				uintptr_t velocity_() { return 0x168; }
				uintptr_t player_array_() { return 0x2A8; }
				uintptr_t pawn_private_() { return 0x308; }
				uintptr_t comp_2_world_() { return 0x1c0; }
				uintptr_t WeaponData() { return 0x510; }
				uintptr_t CurrentWeapon() { return 0x9d8; }
		};

		apply_offsets& get_apply_offsets( ) {
			return apply_offsets::getInstance( );
		}
	};

	uintptr_t reada(uintptr_t baseAddress, uintptr_t offset);

	class Cache {
	public:
		static Cache& getInstance( ) {
			static Cache instance;
			return instance;
		}

		void data();
		void entities_();
		Cache(const Cache&) = delete;
		Cache& operator=(const Cache&) = delete;

		auto get_uworld( ) const noexcept -> std::optional<uintptr_t> { return uworld_; }
		auto get_location_ptr( ) const noexcept -> std::optional<uintptr_t> { return locationPtr_; }
		auto get_rotation_ptr( ) const noexcept -> std::optional<uintptr_t> { return rotationPtr_; }
		auto get_game_instance( ) const noexcept -> std::optional<uintptr_t> { return gameInstance_; }
		auto get_local_player( ) const noexcept -> std::optional<uintptr_t> { return localPlayer_; }
		auto get_pcontroller( ) const noexcept -> std::optional<uintptr_t> { return playerController_; }
		auto get_local_pawn( ) const noexcept -> std::optional<uintptr_t> { return acknowledgedPawn_; }
		auto get_mesh( ) const noexcept -> std::optional<uintptr_t> { return skeletalMesh_; }
		auto get_pstate( ) const noexcept -> std::optional<uintptr_t> { return playerState_; }
		auto get_rcomponent( ) const noexcept -> std::optional<uintptr_t> { return rootComponent_; }
		auto get_relativeloc( ) const noexcept -> std::optional<uintptr_t> { return relativeLocation_; }
		auto get_teamid( ) const noexcept -> std::optional<char> { return teamIndex_; }
		auto get_gamestate( ) const noexcept -> std::optional<uintptr_t> { return gameState_; }
		auto get_playerarray( ) const noexcept -> std::optional<uintptr_t> { return playerArray_; }
		auto get_playersize( ) const noexcept -> std::optional<int> { return playerArraySize_; }

		void cache();

		void print_pointers() {
			/*std::cout << "locationPtr_: " << locationPtr_ << std::endl;
			std::cout << "rotationPtr_: " << rotationPtr_ << std::endl;
			std::cout << "gameInstance_: " << gameInstance_ << std::endl;
			std::cout << "localPlayer_: " << localPlayer_ << std::endl;
			std::cout << "playerController_: " << playerController_ << std::endl;
			std::cout << "acknowledgedPawn_: " << acknowledgedPawn_ << std::endl;
			std::cout << "skeletalMesh_: " << skeletalMesh_ << std::endl;
			std::cout << "playerState_: " << playerState_ << std::endl;
			std::cout << "rootComponent_: " << rootComponent_ << std::endl;
			std::cout << "teamIndex_: " << teamIndex_ << std::endl;
			std::cout << "gameState_: " << gameState_ << std::endl;
			std::cout << "playerArray_: " << playerArray_ << std::endl;*/
		}

		std::optional<uintptr_t> uworld_;
		std::optional<uintptr_t> locationPtr_;
		std::optional<uintptr_t> rotationPtr_;
		std::optional<uintptr_t> gameInstance_;
		std::optional<uintptr_t> localPlayer_;
		std::optional<uintptr_t> playerController_;
		std::optional<uintptr_t> acknowledgedPawn_;
		std::optional<uintptr_t> skeletalMesh_;
		std::optional<uintptr_t> playerState_;
		std::optional<uintptr_t> rootComponent_;
		std::optional<uintptr_t> relativeLocation_;
		std::optional<char> teamIndex_;
		std::optional<uintptr_t> gameState_;
		std::optional<uintptr_t> playerArray_;
		std::optional<int> playerArraySize_;

		mutable std::mutex cacheMutex_;
		Cache() = default;

		template<typename T>
		void update_cache_val(std::optional<T>& cachevar, uintptr_t base, uintptr_t offset);
	private:

	};
}




GameCache::publici global_publici;

GameCache::publici* get_global_publici() {
	return &global_publici;
}

GameCache::publici* (*offset_)() = get_global_publici;

GameCache::publici::apply_offsets& apply_offset_() {
	return offset_()->get_apply_offsets();
}

GameCache::Cache global_cache;

GameCache::Cache* get_global_cache() {
	return &global_cache;
}

GameCache::Cache* (*cache_)() = get_global_cache;

GameCache::Cache& cache_instance_() {
	return cache_()->getInstance();
}

struct FTransform
{
	fquat rot;
	fvector translation;
	char pad[4];
	fvector scale;
	char pad1[4];
	D3DMATRIX ToMatrixWithScale( )
	{
		D3DMATRIX m;
		m._41 = translation.x;
		m._42 = translation.y;
		m._43 = translation.z;

		float x2 = rot.x + rot.x;
		float y2 = rot.y + rot.y;
		float z2 = rot.z + rot.z;

		float xx2 = rot.x * x2;
		float yy2 = rot.y * y2;
		float zz2 = rot.z * z2;
		m._11 = ( 1.0f - ( yy2 + zz2 ) ) * scale.x;
		m._22 = ( 1.0f - ( xx2 + zz2 ) ) * scale.y;
		m._33 = ( 1.0f - ( xx2 + yy2 ) ) * scale.z;

		float yz2 = rot.y * z2;
		float wx2 = rot.w * x2;
		m._32 = ( yz2 - wx2 ) * scale.z;
		m._23 = ( yz2 + wx2 ) * scale.y;

		float xy2 = rot.x * y2;
		float wz2 = rot.w * z2;
		m._21 = ( xy2 - wz2 ) * scale.y;
		m._12 = ( xy2 + wz2 ) * scale.x;

		float xz2 = rot.x * z2;
		float wy2 = rot.w * y2;
		m._31 = ( xz2 + wy2 ) * scale.z;
		m._13 = ( xz2 - wy2 ) * scale.x;

		m._14 = 0.0f;
		m._24 = 0.0f;
		m._34 = 0.0f;
		m._44 = 1.0f;

		return m;
	}
};

struct _MATRIX {
	union {
		struct {
			float        _11, _12, _13, _14;
			float        _21, _22, _23, _24;
			float        _31, _32, _33, _34;
			float        _41, _42, _43, _44;

		};
		float m[4][4];
	};
};
_MATRIX Matrix1( frotator Vec4, fvector origin = fvector( 0, 0, 0 ) )
{
	double radPitch = ( Vec4.Pitch * double( PI ) / 180.f );
	double radYaw = ( Vec4.Yaw * double( PI ) / 180.f );
	double radRoll = ( Vec4.Roll * double( PI ) / 180.f );

	double SP = sinf( radPitch );
	double CP = cosf( radPitch );
	double SY = sinf( radYaw );
	double CY = cosf( radYaw );
	double SR = sinf( radRoll );
	double CR = cosf( radRoll );

	_MATRIX matrix;
	matrix.m[0][0] = CP * CY;
	matrix.m[0][1] = CP * SY;
	matrix.m[0][2] = SP;
	matrix.m[0][3] = 0.f;

	matrix.m[1][0] = SR * SP * CY - CR * SY;
	matrix.m[1][1] = SR * SP * SY + CR * CY;
	matrix.m[1][2] = -SR * CP;
	matrix.m[1][3] = 0.f;

	matrix.m[2][0] = -(CR * SP * CY + SR * SY);
	matrix.m[2][1] = CY * SR - CR * SP * SY;
	matrix.m[2][2] = CR * CP;
	matrix.m[2][3] = 0.f;

	matrix.m[3][0] = origin.x;
	matrix.m[3][1] = origin.y;
	matrix.m[3][2] = origin.z;
	matrix.m[3][3] = 1.f;

	return matrix;
}
