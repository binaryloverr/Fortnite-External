#include "Game/aimbot.hpp"
#include <iomanip>
#include <sstream>
#include <algorithm>
std::atomic<bool> aimbot_running(false);
std::thread aimbot_thread;


float  target_dist = FLT_MAX;
uintptr_t target_entity = NULL;

void draw_esp_elements(const entities& Player, const fvector& camera_location) {
    auto& cache = GameCache::Cache::getInstance();

    bone_manager.get_bone_array(Player.mesh_);

    auto root_bone = bone_manager.get_bone(root);
    auto head_bone = bone_manager.get_bone(Head);

    auto root = camera_manager.w2s(fvector(root_bone.x, root_bone.y, root_bone.z - 15));
    auto head = camera_manager.w2s(head_bone);
    auto head_box = camera_manager.w2s(fvector(head_bone.x, head_bone.y, head_bone.z + 15));
    auto root_box = camera_manager.w2s(root_bone);

    float distance = location.distance(root_bone) * 0.01f;
    float box_height = abs(head.y - root.y);
    float box_width = box_height * 0.38f;

    if (distance > c_max_render_distance && cache.get_local_pawn().value_or(0)) return;

    const ImColor viscolor = player_manager.is_visible(Player.mesh_) ? ImColor(255, 157, 71) : ImColor(220, 20, 60);
    const ImColor filldecolor = player_manager.is_visible(Player.mesh_) ? ImColor(35, 122, 87, 75) : ImColor(9, 48, 40, 125);

    ImColor color1 = ImColor(21, 153, 87, 175);
    ImColor color2 = ImColor(21, 87, 153, 175);

    if (c_enable) {
        auto dx = head.x - (C_Overlay::c_screen_width / 2);
        auto dy = head.y - (C_Overlay::c_screen_height / 2);
        auto dist = sqrtf(dx * dx + dy * dy);

        if (dist < C_Aimbot::c_fov && dist < target_dist) {
            target_dist = dist;
            target_entity = Player.entity_;
        }
    }

        if (c_enable_esp) {
            if (c_enable_box) {
                switch (c_box) {
                case 0: drawstatic_(head_box, box_width, box_height, viscolor); break;
                case 1: drawfilled_(head_box, box_width, box_height, color1, color2); break;
                case 2: drawcorner_(head_box, box_width, box_height, viscolor); break;
                }
            }

            if (c_skeleton) {
                auto bone_id = bone_manager.get_skeleton(bone_pairs);

                for (const auto& pair : bone_pairs) {
                    const auto start_iter = bone_id.find(pair.first);
                    const auto end_iter = bone_id.find(pair.second);

                    if (start_iter != bone_id.end() && end_iter != bone_id.end()) {
                        const auto start = camera_manager.w2s(start_iter->second);
                        const auto end = camera_manager.w2s(end_iter->second);

                        GetBackgroundDrawList()->AddLine(ImVec2(start.x, start.y), ImVec2(end.x, end.y), viscolor, 2);
                    }
                }
            }

            if ( c_username ) {
                std::string username_str = player_manager.get_player_name( Player.pstate_ );

                if (!username_str.empty( ) ) {
                    drawoutlined_(
                        username_str,
                        ImVec2
                        (head_box.x, head_box.y - 20),
                        ImColor(255, 255, 255),
                        -20);
                }
            }
         
            if ( c_platform ) {
                std::string platform = player_manager.get_platform( Player.local_player_state_ );

                drawoutlined_(
                    platform,
                    ImVec2(head_box.x, head_box.y - 30),
                    ImColor(255, 255, 255),
                    -0);
            }

            if ( c_rank_esp ) {

                uintptr_t habanero = device_( ).read<uintptr_t>( Player.local_player_state_ + 0x9F0 );

                int32_t rankProgress = device_( ).read<int32_t>( habanero + 0xb8 + 0x10 );

                std::string rankType = player_manager.get_rank( rankProgress );

                std::string finalRank = wstring_to_utf8( string_to_wstring( rankType ) );

                ImVec2 textSize = CalcTextSize( finalRank.c_str( ) );

                outlined_text(
                    GetBackgroundDrawList( ),
                    root_box.x - ( textSize.x / 2), root_box.y + 41,
                    player_manager.get_rank_color( rankProgress ),
                    finalRank.c_str( ) );
            }

            if ( c_weapon ) {
                weapon_info_ weapon_info = weapon_manager.get_weapon_name( Player.entity_ );

                std::string weapon_name = weapon_info.weapon_name;

                if ( weapon_name == "" ) weapon_name = "null";

                drawoutlined_(
                    weapon_name,
                    ImVec2
                    (root_box.x, root_box.y + 10),
                    viscolor,
                    15);
            }

            if ( c_distance ) {
                std::ostringstream oss;
                oss << std::fixed << std::setprecision( 2 ) << distance << "m";
                std::string distance_str = oss.str();
                drawoutlined_(
                    distance_str,
                    ImVec2
                    (
                        root_box.x, root_box.y + 5
                    ),
                    ImColor(255, 255, 255),
                    5);
            }

            if ( c_arrows ) {

                float fov_radius = static_cast<float>( c_fov );
                float arrow_size = 20.0f;
                float arrow_offset = 30.0f;

                ImVec2 screen_center( C_Overlay::c_screen_width / 2, C_Overlay::c_screen_height / 2 );

                auto player_screen_pos = camera_manager.w2s( head_bone );

                ImVec2 direction( player_screen_pos.x - screen_center.x, player_screen_pos.y - screen_center.y );

                float length = sqrt( direction.x * direction.x + direction.y * direction.y );
                direction.x /= length;
                direction.y /= length;

                float arrow_distance = fov_radius + arrow_offset;
                ImVec2 arrow_position(
                    screen_center.x + direction.x * arrow_distance,
                    screen_center.y + direction.y * arrow_distance
                );

                ImVec2 perp_direction( -direction.y, direction.x );

                ImVec2 p1( arrow_position.x, arrow_position.y );
                ImVec2 p2(
                    arrow_position.x - direction.x * arrow_size + perp_direction.x * arrow_size / 2,
                    arrow_position.y - direction.y * arrow_size + perp_direction.y * arrow_size / 2
                );
                ImVec2 p3(
                    arrow_position.x - direction.x * arrow_size - perp_direction.x * arrow_size / 2,
                    arrow_position.y - direction.y * arrow_size - perp_direction.y * arrow_size / 2
                );

                GetBackgroundDrawList( )->AddTriangleFilled( p1, p2, p3, viscolor );
            }

            if ( c_threat ) {

                

            }


        }
        if (!TargetedFortpawn) { TargetedFortpawn = TargetedFortPawn(); }


        if (c_triggggger) {
            if (TargetedFortpawn) {
                int keyid1 = VK_LSHIFT;
                switch (c_trig_key) {
                case 0:	keyid1 = VK_LBUTTON; break;
                case 1:	keyid1 = VK_RBUTTON; break;
                case 2:	keyid1 = VK_XBUTTON2; break;
                case 3:	keyid1 = VK_XBUTTON1; break;
                case 4:	keyid1 = VK_LSHIFT; break;
                case 5:	keyid1 = VK_LCONTROL; break;
                case 6: keyid1 = VK_MENU; break;
                }

                weapon_info_ local_held_weapon = weapon_manager.get_weapon_name(cache.get_local_pawn().value_or(0));
                local_player_weapon = local_held_weapon.weapon_name;

                if (strstr(local_held_weapon.weapon_name.c_str(), xorstr("Pump Shotgun").c_str()) ||
                    strstr(local_held_weapon.weapon_name.c_str(), xorstr("Pump").c_str()) ||
                    strstr(local_held_weapon.weapon_name.c_str(), xorstr("Shotgun").c_str())) {

                    if (GetAsyncKeyState(keyid1)) {
                        float distance = location.distance(root_bone) * 0.01f;
                        if (distance <= max_trig_distance) {

                            if (has_clicked) {
                                tb_begin = std::chrono::steady_clock::now();
                                has_clicked = false;
                            }

                            tb_end = std::chrono::steady_clock::now();
                            tb_time_since = std::chrono::duration_cast<std::chrono::milliseconds>(tb_end - tb_begin).count();

                            if (tb_time_since >= trig_delay) {
                                TargetedFortpawn = NULL;
                                POINT cursor;
                                GetCursorPos(&cursor);
                                PostMessage(hwndd, WM_LBUTTONDOWN | MK_LBUTTON, 0, MAKELPARAM(cursor.x, cursor.y));
                                PostMessage(hwndd, WM_LBUTTONUP, 0, MAKELPARAM(cursor.x, cursor.y));
                                has_clicked = true;
                            }
                        }
                    }
                }
            }
        }
       
       
}

auto actor_loop() -> void {
    auto& cache = GameCache::Cache::getInstance();

    target_dist = FLT_MAX;
    target_entity = NULL;

    utilites_manager.render_elements( );

    if (!cache.get_uworld( ).value( ) || entity_list.empty( ) ) return;

    auto camera_location = location;
    for (auto& Player : entity_list) {
        draw_esp_elements(Player, camera_location);
    }

    if (c_enable && target_entity) {

        auto root_bone = bone_manager.get_bone(root);
        auto head_bone = bone_manager.get_bone(Head);
        auto root = camera_manager.w2s(fvector(root_bone.x, root_bone.y, root_bone.z - 15));
        auto head = camera_manager.w2s(head_bone);

        auto dx = head.x - (C_Overlay::c_screen_width / 2);
        auto dy = head.y - (C_Overlay::c_screen_height / 2);
        auto dist = sqrtf(dx * dx + dy * dy);

        auto closest_mesh = device_().read <std::uint64_t>(target_entity + 0x318); //skeletal mesh
        bone_manager.get_bone_array(closest_mesh);

        fvector hitbox;
        switch (c_hitbox) {
        case 0:
            hitbox = bone_manager.get_bone(HumanHead);
            break;
        case 1:
            hitbox = bone_manager.get_bone(Chest);
            break;
        case 2:
            hitbox = bone_manager.get_bone(Pelvis);
            break;
        case 3:
            srand((unsigned)time(NULL));
            int Random = (rand() % 4);
            switch (Random) {
            case 0:
                hitbox = bone_manager.get_bone(HumanHead);
                break;
            case 1:
                hitbox = bone_manager.get_bone(HumanNeck);
                break;
            case 2:
                hitbox = bone_manager.get_bone(HumanChest);
                break;
            case 3:
                hitbox = bone_manager.get_bone(HumanPelvis);
                break;
            }
            break;
        }

        int keyid = VK_LSHIFT;

        switch (c_aim_key) {
        case 0:	keyid = VK_LBUTTON;	break;
        case 1:	keyid = VK_RBUTTON;	break;
        case 2:	keyid = VK_XBUTTON2; break;
        case 3:	keyid = VK_XBUTTON1; break;
        case 4:	keyid = VK_LSHIFT; break;
        case 5:	keyid = VK_LCONTROL; break;
        case 6: keyid = VK_MENU; break;
        }


        fvector2d hitbox_screen = camera_manager.w2s(hitbox);

        if ( c_target )
        {
            ImGui::GetBackgroundDrawList()->AddLine(ImVec2(c_screen_width, c_screen_height), ImVec2(hitbox_screen.x, hitbox_screen.y), ImColor(255, 255, 255, 255), 2);
        }

        if (hitbox.x != 0 || hitbox.y != 0 && (get_cross_distance(hitbox.x, hitbox.y, c_screen_width / 2, c_screen_height / 2) <= c_fov))
        {
            if ( c_visible_check ) {
                if ( player_manager.is_visible( closest_mesh ) )
                {
                    if (GetAsyncKeyState( keyid ) ) {
                        perform(hitbox_screen);
                    }
                }
            }
            else
            {

                if (GetAsyncKeyState( keyid ) ) {
                    perform(hitbox_screen);
                }

            }
        }
    }
    else {
        target_dist = FLT_MAX;
        target_entity = NULL;
    }
}


//this is binarylover propriety:)