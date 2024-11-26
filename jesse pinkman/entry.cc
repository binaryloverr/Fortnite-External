#include "Includes/includes.hpp"
#include "Includes/call.hh"
#include "Dependencies/Fortnite/loop.hpp"
#include "Dependencies/UI/Renderer/c_overlay.h"
#include "Dependencies/Console/CCli.hpp"
#include <tchar.h>
#include <ntstatus.h>
#include "Includes/Definitions/xorst.h"
#include "Includes/Definitions/skcrypt.h"
#include <thread>
#include <urlmon.h>
#include "auth.hpp"

Overlay::DX11Overlay* D11Overlay = nullptr;
bool developer_mode = true;

__declspec(noinline) void log( ) {

 #define LOG printf("success");
   
}

__declspec(noinline) auto initServer_( ) -> call::status {

    char title[256];

    sprintf_s(title, _(" "));

    if ( developer_mode )
    {
        sprintf_s( title, _( " Paracetamol | Development Version" ) );
    };
    
    ( SetConsoleTitleA )( title );

    return call_success;
}

std::uint32_t get_process_id( const wchar_t* process_name ) {
    std::uint32_t process_id = 0;

    HANDLE snap_shot = CreateToolhelp32Snapshot( TH32CS_SNAPPROCESS, NULL );

    if ( snap_shot == INVALID_HANDLE_VALUE )

        return process_id;

    PROCESSENTRY32W entry = { };
    entry.dwSize = sizeof( decltype( entry ) );

    if ( Process32FirstW( snap_shot, &entry ) == TRUE ) {
        if ( _wcsicmp( process_name, entry.szExeFile ) == 0 ) {
            process_id = entry.th32ProcessID;
        }
        else {
            while ( Process32NextW( snap_shot, &entry ) == TRUE ) {
                if ( _wcsicmp( process_name, entry.szExeFile ) == 0 ) {
                    process_id = entry.th32ProcessID;
                    break;
                }
            }
        }
    }

    CloseHandle( snap_shot );
    return process_id;
}

__declspec( noinline ) auto init_overlay( ) -> call::status {
    
    Overlay::DX11Overlay::GetWindow(FindWindow(0, (_("Fortnite  "))));
    
    auto overlay = D11Overlay->InitOverlay( );

    std::thread( []( ) {
        for ( ;; ) {
            GameCache::cachep( );
        }
     }).detach( );

  
    switch (overlay) {
    case 0: {
        break;
    }
    case 1: {

        while ( D11Overlay -> MainLoop( actor_loop ) ) {

        }
        break;
    }
    }

    return call_success;
}


int main( )
{
    m_vm& device = device_();
    initServer_( );

    initMouse_();

    accesseac();
    device.init_();

    hwndd = FindWindowA( NULL, ( "Fortnite  " ));

    device.m_pid = device.isruning_( "FortniteClient-Win64-Shipping.exe" );

    device.m_base = device.get_base_address_( );

    printf( "Base: 0x%p\n", device.m_base );
 
 
    device.cr3_( );

    __int64 va_teee = 0;
    va_text = va_teee;

    for (auto i = 0; i < 25; i++) {
        if (device_().read<__int32>(device.m_base + (i * 0x1000) + 0x250) == 0x6F41C00) {
            va_text = device.m_base + ((i + 1) * 0x1000);
        }
    }

    init_overlay( );
}

//this is binarylover propriety:)
