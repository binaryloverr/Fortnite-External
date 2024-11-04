#pragma once
namespace C_Overlay
{
	inline bool c_show_menu = true;
	inline bool c_fullscreen = false;
	inline float c_center_y;
	inline float c_center_x;
	inline int c_screen_width = GetSystemMetrics(SM_CXSCREEN);
	inline int c_screen_height = GetSystemMetrics(SM_CYSCREEN);
	inline bool c_enable_vsync = true;
}

namespace C_Players
{
	inline bool c_enable_esp = true;
	inline bool c_enable_box = true;
	inline int c_box = 0;
	inline bool c_static_box = true;
	inline bool c_cornered_box = false;
	inline bool c_seconds_alive = false;
	inline bool c_rank_esp = false;
	inline bool c_platform = false;
	inline bool c_skeleton = false;
	inline bool c_filled_box = false;
	inline int skele_type = 0;
	inline bool c_username = true;
	inline bool c_distance = true;
	inline bool c_weapon = false;
	inline bool c_threat = false;
	inline bool c_health = true;
	inline bool c_arrows = false;
	static float c_color_visible[3] = { 255 / 255.0f, 0 / 255.0f, 255 / 255.0f / 255 / 255.f};
	static float c_color_invisible[3] = { 255 / 255.0f, 140 / 255.0f, 0 / 255.0f / 255 / 255.f };
}

inline bool c_trigger = true;

namespace C_Aimbot
{
	inline bool c_enable = true;
	inline bool c_dead_zone = false;
	inline int c_trig_key = 1;
	inline float c_custom_dead_zone = 0.1f;
	inline bool c_enable_deafult = true;
	inline bool c_triggggger = false;
	inline bool c_shotgun_only = false;
	inline int max_trig_distance = 30;
	inline int trig_delay = 1;
	inline bool c_enable_memory = true;
	inline bool c_circle = true;
	inline bool c_humanized = false;
	inline float c_fov = 85;
	inline float c_max_render_distance = 275;
	inline bool c_visible_check = false;
	inline int c_aim_key = 1;
	inline int c_aim1 = 0;
	inline float c_smooth = 7;
	inline int c_hitbox = 3;
	inline bool c_knocked = 1;
	inline int c_mouse_type = 0;
	inline bool c_target = 1;
	inline bool c_ignore_downed = false;
	inline bool c_ignore_bots = false;

}

namespace C_Misc {

	inline bool c_performance_mode = false;
	inline bool c_show_fps = false;
}

namespace C_Exploits {
	inline bool freecam = false;
	inline bool wireframe = false;
}

namespace C_Radar
{
	inline bool enable = false;

}
