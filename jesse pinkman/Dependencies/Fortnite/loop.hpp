#include "drawing.hpp"
#include <iostream>
#include <vector>
#include <memory>
#include <optional>
#include <thread>
#include <chrono>
#include "../../m_world.hpp"
#include <optional>
#include <mutex>
#include <stdexcept>
#include <future>
using namespace std;
__int64 va_text;
vector<fvector> chestloc;
vector<fvector> ammo;

namespace GameCache {

    Cache& cache = Cache::getInstance( );

    uintptr_t local_player_( ) {
        return device_( ).read<uintptr_t>( device_( ).read<uintptr_t>( cache.gameInstance_.value_or( 0 ) + 0x38 ) );
    }

    int array_size_( ) {

        return device_( ).read<int>( cache.gameState_.value_or( 0 ) + apply_offset_().player_array_() + sizeof( uintptr_t ) );
    }

    char team_id_( ) {
        return device_( ).read<char>( cache.playerState_.value_or( 0 ) + apply_offset_().team_id_());
    }

    uintptr_t apply_offset(uintptr_t base, uintptr_t offset) {
        return base + offset;
    }

    template<typename T>
    
    
    
    optional<T> readd( uintptr_t address ) {
        try {
            return device_( ).read<T>( address );
        }
        catch ( const exception& e ) {
            cerr << "read issue" << hex << address << ": " << e.what( ) << endl;
            return nullopt;
        }
    }

    template<typename T>
    void Cache::update_cache_val( optional<T>& cachevar, uintptr_t base, uintptr_t offset ) {
        if (auto value = readd<T>( apply_offset ( base, offset ) ) ) {
            cachevar = move( value );
        }
    }

    auto GetPlayerArray() -> TArray<uintptr_t*>
    {
        return device_().read<TArray<uintptr_t*>>(cache.gameState_.value() + 0x2a8);
    }

    void Cache::cache( ) {
        lock_guard < mutex > lock( cacheMutex_ );

        try {
            uworld_ = device_( ).read < uintptr_t > ( apply_offset ( offset_()->get_apply_offsets( ).uworld_( ), va_text ) );
            if ( !uworld_ ) return;

            auto futures = vector< future < void > >{ };

            futures.emplace_back( async( launch::async, &Cache::update_cache_val < uintptr_t > , this , ref( locationPtr_ ), uworld_.value( ), offset_( )->get_apply_offsets( ).location_ptr_( ) ) );
            futures.emplace_back( async( launch::async, &Cache::update_cache_val < uintptr_t > , this , ref( rotationPtr_ ), uworld_.value( ), offset_( )->get_apply_offsets( ).rotation_ptr_( ) ) );
            futures.emplace_back( async( launch::async, &Cache::update_cache_val < uintptr_t > , this , ref( gameInstance_ ), uworld_.value( ), offset_( )->get_apply_offsets( ).game_instance_( ) ) );

            localPlayer_ = local_player_( );

            futures.emplace_back( async( launch::async, &Cache::update_cache_val < uintptr_t > , this , ref( playerController_ ), localPlayer_.value( ), offset_( )->get_apply_offsets( ).player_controller_( ) ) );
            futures.emplace_back( async( launch::async, &Cache::update_cache_val < uintptr_t > , this , ref( acknowledgedPawn_ ), playerController_.value( ), offset_( )->get_apply_offsets( ).local_pawn_( ) ) );

            auto localpawn_val = acknowledgedPawn_.value_or( 0 );

            futures.emplace_back( async( launch::async, &Cache::update_cache_val < uintptr_t > , this , ref( skeletalMesh_ ), localpawn_val, offset_( )->get_apply_offsets( ).mesh_( ) ) );
            futures.emplace_back( async( launch::async, &Cache::update_cache_val < uintptr_t > , this , ref( playerState_ ), localpawn_val, offset_( )->get_apply_offsets( ).pstate_( ) ) );
            futures.emplace_back( async( launch::async, &Cache::update_cache_val < uintptr_t > , this , ref( rootComponent_ ), localpawn_val, offset_( )->get_apply_offsets( ).root_( ) ) );

            teamIndex_ = team_id_( );
            futures.emplace_back( async( launch::async, &Cache::update_cache_val < uintptr_t > , this , ref( gameState_ ), uworld_.value( ), offset_( )->get_apply_offsets( ).game_state_( ) ) );
            futures.emplace_back( async( launch::async, &Cache::update_cache_val < uintptr_t > , this , ref( playerArray_ ), gameState_.value_or( 0 ), offset_( )->get_apply_offsets( ).player_array_( ) ) );
            playerArraySize_ = array_size_( );

            
            for ( auto& future : futures ) {
                future.get( ); 
            }
        }
        catch ( ... ) {
            
        }
    }

    void cachep() {

        Cache& cache = Cache::getInstance( );
        cache.cache( );

        vector<entities> temp_entity_list;
       
        auto player_array_ = cache.get_playerarray( );

        auto array_size_ = cache.get_playersize( ).value_or(0);

        temp_entity_list.reserve ( array_size_ );

        for ( int i = 0; i < array_size_; ++i ) {
            uintptr_t pstate_ = reada( player_array_.value_or( 0 ), i * sizeof( uintptr_t ) );

            uintptr_t aactor = reada( pstate_, static_cast<uintptr_t>( offset_( )->get_apply_offsets( ).pawn_private_( ) ) );

            if ( aactor == cache.get_local_pawn( ).value_or( 0 ) )
                continue;

            uintptr_t mesh = reada( aactor, static_cast<uintptr_t>( offset_( )->get_apply_offsets( ).mesh_( ) ) );
            if ( !mesh )
                continue;

            uintptr_t array_p = reada( player_array_.value_or( 0 ), i * 0x8);
            uintptr_t local_actor = reada( array_p, 0x308 );

            int teamid = static_cast<int>( reada( pstate_, static_cast <uintptr_t> ( offset_( )->get_apply_offsets( ).team_id_( ) ) ) );
            uint64_t local_player_state = reada( local_actor, static_cast <uintptr_t> ( offset_( )->get_apply_offsets( ).pstate_( ) ) );

            if ( cache.get_local_pawn( ).value_or( 0 ) )
                if ( teamid == cache.get_teamid( ).value_or( 0 ) ) continue;

            entities storedentity;
            storedEntity.entity_ = aactor;
            storedEntity.mesh_ = mesh;
            storedEntity.pstate_ = pstate_;
            storedEntity.local_player_state_ = local_player_state;
            temp_entity_list.push_back( storedentity );
        }

        {
            lock_guard<mutex> lock( cache.cacheMutex_ );
            entity_list.swap( temp_entity_list );
        }

        sleep_for(milliseconds(700));

    }

    uintptr_t reada(uintptr_t baseAddress, uintptr_t offset) {
        return read_addy(uintptr_t, baseAddress, offset);
    }
} 
//this is binarylover propriety:)

