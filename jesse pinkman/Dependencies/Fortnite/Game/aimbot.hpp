#include <cmath>
#include <chrono>
#include <thread>
#include <windows.h> // For PostMessage and GetAsyncKeyState|
#include "../../Fortnite/Game/UE_Functions\entity_utils.hpp"
#include "C:\Users\duh\Desktop\niger\jesse pinkman\Includes\Definitions\xorst.h"
#include <codecvt>
#include <locale>
#include <string>
#include <mutex>
std::mutex PlayerMutex_;

typedef int(*pDD_btn)(int btn);
typedef int(*pDD_whl)(int whl);
typedef int(*pDD_key)(int keycode, int flag);
typedef int(*pDD_mov)(int x, int y);
typedef int(*pDD_str)(char* str);
typedef int(*pDD_todc)(int vk);
typedef int(*pDD_movR)(int dx, int dy);

pDD_btn      DD_btn;
pDD_whl      DD_whl;
pDD_key      DD_key;
pDD_mov    DD_mov;
pDD_str       DD_str;
pDD_todc    DD_todc;
pDD_movR   DD_movR;
HMODULE hDll;



__declspec(noinline) auto initMouse_() -> call::status {

	hDll = LoadLibraryW(_(L"C:\\dd43390.dll"));

	if (hDll == nullptr)
	{

	}

	DD_btn = (pDD_btn)GetProcAddress(hDll, "DD_btn");
	DD_whl = (pDD_whl)GetProcAddress(hDll, "DD_whl");
	DD_key = (pDD_key)GetProcAddress(hDll, "DD_key");
	DD_mov = (pDD_mov)GetProcAddress(hDll, "DD_mov");
	DD_str = (pDD_str)GetProcAddress(hDll, "DD_str");
	DD_todc = (pDD_todc)GetProcAddress(hDll, "DD_todc");
	DD_movR = (pDD_movR)GetProcAddress(hDll, "DD_movR");

	if (!(DD_btn && DD_whl && DD_key && DD_mov && DD_str && DD_todc && DD_movR))
	{

	}

	int st = DD_btn(0);
	if (st != 1)
	{

	}

	return call_success;
}

double get_cross_distance1(double x_, double y_)
{
	return sqrtf(powf((c_screen_width - x_), 2) + powf((c_screen_height - y_), 2));
}

float RandomFloat(float a, float b)
{
	float random = ((float)rand()) / (float)RAND_MAX;
	float diff = b - a;
	float r = random * diff;
	return a + r;
}

void perform(fvector2d Head2D)
{
	float x = Head2D.x; float y = Head2D.y;
	float AimSpeed = c_smooth;

	fvector2d Target;


	if (x != 0.f)
	{
		Target.x = (x > c_screen_width / 2) ? -(c_screen_width / 2 - x) : x - c_screen_width / 2;
		Target.x /= AimSpeed;
		Target.x = (x > c_screen_width / 2 && Target.x + c_screen_width / 2 > c_screen_width / 2 * 2) ? 0 : Target.x;
		Target.x = (x < c_screen_width / 2 && Target.x + c_screen_width / 2 < 0) ? 0 : Target.x;
	}

	if (y != 0.f)
	{
		Target.y = (y > c_screen_height / 2) ? -(c_screen_height / 2 - y) : y - c_screen_height / 2;
		Target.y /= AimSpeed;
		Target.y = (y > c_screen_height / 2 && Target.y + c_screen_height / 2 > c_screen_height / 2 * 2) ? 0 : Target.y;
		Target.y = (y < c_screen_height / 2 && Target.y + c_screen_height / 2 < 0) ? 0 : Target.y;
	}

	switch (C_Aimbot::c_aim1) {
	case 0:
		if (C_Aimbot::c_dead_zone) {
			if (abs(Target.x) > C_Aimbot::c_custom_dead_zone || abs(Target.x) > C_Aimbot::c_custom_dead_zone) {
				DD_movR(Target.x, Target.y);
			}

		}
		else {
			DD_movR(Target.x, Target.y);
		} break;
	case 1:
		float targetx_min = Target.x - 1;
		float targetx_max = Target.x + 1;

		float targety_min = Target.y - 1;
		float targety_max = Target.y + 1;

		float offset_x = RandomFloat(targetx_min, targetx_max);
		float offset_y = RandomFloat(targety_min, targety_max);

		DD_movR(static_cast<int> ((float)offset_x), static_cast<int>((float)offset_y / 1)); break;
	}
}


