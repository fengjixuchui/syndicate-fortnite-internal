#pragma once
#include "../../../stdafx.h"

static int total_open_popups = 0;
namespace color
{
	static float add(float current, float white)
	{
		current += white;

		if (current >= 255.f) return 255.f;

		return current;
	}
}

class gui
{
public:
	void run();
	void init();
	
	bool is_hovered(FVector2D pos, FVector2D size);
	void combo(wchar_t* text, bool* active, int* value, wchar_t* arg[], int num_args);
	void checkbox(wchar_t* text, bool* option);
	void color_picker(wchar_t* text, FLinearColor* color, bool* active);
	void slider(wchar_t* text, double min, double max, double* value);
	bool button(wchar_t* text, bool active);
	bool button_2(wchar_t* text);
	void text(wchar_t* text);
	void space(double x, double y);
	void set_x(double value);
	void set_y(double value);
	void draw_card(const wchar_t* header_text, FVector2D card_position, FVector2D card_size, FVector2D main_menu_size);
	bool begin(wchar_t* title, FVector2D start_position, FVector2D size);
	bool end();
	
private:
	bool initialized, left_mouse_clicked, right_mouse_clicked, left_mouse_down, right_mouse_down;
	double item_spacing;
	FVector2D position, size, offset, cursor, screen_center;
	FLinearColor background_color, main_color, frame_color, frame_hovered_color, frame_pressed_color, text_color;
	bool isComboActive = false;
	int selectedAimBone = 1;
};
