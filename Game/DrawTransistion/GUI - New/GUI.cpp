#include "GUI.h"

wchar_t* aimOptions[] = { xor_w(L"Neck"), xor_w(L"Lower Neck"), xor_w(L"Chest") };
int numOptions = sizeof(aimOptions) / sizeof(aimOptions[0]);

void gui::init()
{
	this->background_color = FLinearColor(2.55f, 2.55f, 2.55f, 1.0f);
	this->main_color = FLinearColor(0.0f, 255.0f, 255.0f, 1.0f);
	this->frame_color = FLinearColor(7.65f, 7.65f, 7.65f, 1.0f);
	this->frame_hovered_color = FLinearColor(10.2f, 10.2f, 10.2f, 1.0f);
	this->frame_pressed_color = FLinearColor(12.75f, 12.75f, 12.75f, 1.0f);
	this->text_color = FLinearColor(255.0f, 255.0f, 255.0f, 1.0f);

	this->position = position;
	this->size = size;

	this->item_spacing = 11;
}

bool gui::is_hovered(FVector2D pos, FVector2D size)
{
	if (this->cursor.X > pos.X && this->cursor.Y > pos.Y)
		if (this->cursor.X < pos.X + size.X && this->cursor.Y < pos.Y + size.Y)
			return true;

	return false;
}

void gui::combo(wchar_t* text, bool* active, int* value, wchar_t* arg[], int num_args)
{
	FVector2D current = this->position + this->offset;
	FVector2D size = FVector2D(100, 20);

	bool any_hovered = false;
	bool hovered = is_hovered(current, size);
	bool clicked = left_mouse_clicked && hovered;

	if (clicked)
	{
		if (*active)
		{
			*active = false;
		}
		else if (!total_open_popups)
		{
			*active = true;
		}
	}

	if (hovered && !any_hovered)
		any_hovered = true;

	Functions().DrawFilledRect(current, size.X, size.Y, this->frame_color);
	SDK().K2_DrawBox(current, size, 1.f, FLinearColor(0.f, 0.f, 0.f, 1.f));
	SDK().K2_DrawText(Globals::Roboto, arg[*value], FVector2D(current.X + (size.X / 2), current.Y + 2), FVector2D(1.0f, 1.0f), this->text_color, 1.0f, FLinearColor(0, 0, 0, 1.0f), FVector2D(), true, false, false, FLinearColor(0, 0, 0, 1.0f));
	SDK().K2_DrawText(Globals::Roboto, text, FVector2D(current.X + size.X + 5, current.Y + 1), FVector2D(1.0f, 1.0f), this->text_color, 1.0f, FLinearColor(0, 0, 0, 1.0f), FVector2D(), false, false, false, FLinearColor(0, 0, 0, 1.0f));

	if (*active)
	{
		total_open_popups += 1;

		int differ = 6;
		current.X += differ;
		size.X -= differ * 2;
		current.Y += 1;

		for (int i = 0; i < num_args; i++)
		{
			current.Y += size.Y;

			FLinearColor color = this->frame_color;

			bool item_hovered = is_hovered(current, size);
			bool item_clicked = left_mouse_clicked && item_hovered;
			bool item_down = left_mouse_down && item_hovered;

			if (item_hovered && !any_hovered)
				any_hovered = true;

			if (item_clicked)
			{
				LI_FN(Sleep).safe_cached()(30);
				*value = i;
			}

			if (item_hovered)
			{
				color = this->frame_hovered_color;
			}
			else if (*value == i)
			{
				color = this->frame_pressed_color;
			}

			Functions().DrawFilledRect(current, size.X, size.Y, color);

			SDK().K2_DrawText(Globals::Roboto, arg[i], FVector2D(current.X + (size.X / 2), current.Y + 2), FVector2D(1.0f, 1.0f), this->text_color, 1.0f, FLinearColor(0, 0, 0, 1.0f), FVector2D(), true, false, false, FLinearColor(0, 0, 0, 1.0f));
		}
	}

	bool clicked_somewhere_else = !any_hovered && left_mouse_clicked;

	if (clicked_somewhere_else && *active)
		*active = false;

	this->offset.Y += size.Y + this->item_spacing - 1;
}

void gui::checkbox(wchar_t* text, bool* option)
{
	FVector2D current = this->position + this->offset;
	FVector2D size = FVector2D(8, 8);
	FLinearColor draw_color = FLinearColor();

	bool hovered = is_hovered(current, FVector2D(size.X + 80, size.Y));
	bool clicked = left_mouse_clicked && hovered;

	if (*option)
		draw_color = this->main_color;
	else if (hovered)
		draw_color = this->frame_hovered_color;
	else
		draw_color = this->frame_color;

	if (clicked && !total_open_popups)
		*option = !*option;

	Functions().DrawFilledRect(current, size.X, size.Y, draw_color);
	SDK().K2_DrawBox(current, size, 1.f, FLinearColor(0.f, 0.f, 0.f, 1.f));
	SDK().K2_DrawText(Globals::Roboto, text, FVector2D(current.X + size.X + 4, current.Y + (size.Y / 2) - 2), FVector2D(1.0f, 1.0f), this->text_color, 1.0f, FLinearColor(0, 0, 0, 1.0f), FVector2D(), false, true, false, FLinearColor(0, 0, 0, 1.0f));

	this->offset.Y += size.Y + this->item_spacing + 1;
}

void gui::color_picker(wchar_t* text, FLinearColor* color, bool* active)
{
	FVector2D current = this->position + this->offset;
	FVector2D size = FVector2D(8, 8);

	bool hovered = is_hovered(current, FVector2D(size.X + 80, size.Y));
	bool big_hovered = hovered || (*active && is_hovered(current, FVector2D(160, 115)));
	bool clicked = left_mouse_clicked && hovered;
	bool any_other_clicked = left_mouse_clicked && !big_hovered;

	Functions().DrawFilledRect(current, size.X, size.Y, *color);
	SDK().K2_DrawBox(current, size, 1.f, FLinearColor(0.f, 0.f, 0.f, 1.f));
	SDK().K2_DrawText(Globals::Roboto, text, FVector2D(current.X + size.X + 4, current.Y + (size.Y / 2) - 2), FVector2D(1.0f, 1.0f), this->text_color, 1.0f, FLinearColor(0, 0, 0, 1.0f), FVector2D(), false, true, false, FLinearColor(0, 0, 0, 1.0f));

	if (clicked)
	{
		if (*active)
		{
			*active = false;
		}
		else if (!total_open_popups)
		{
			*active = true;
		}
	}

	if (any_other_clicked && *active)
		*active = false;

	//picker
	if (*active)
	{
		total_open_popups += 1;

		current = FVector2D(current.X + size.X, current.Y + size.Y);
		double current_x_backup = current.X;

		//up/down (white)
		for (float c = 0; c < 10.f; c++)
		{
			float c_percentage = c / 10.f;

			float c_hx = 200.f * c_percentage;

			//red to green
			for (float i = 0; i < 5.f; i++)
			{
				float percentage = i / 5.f;

				float hx = 255.f * percentage;

				float red = 255.f - hx;
				float green = 255.f - red;
				float blue = 0.f;

				red = color::add(red, c_hx);
				green = color::add(green, c_hx);
				blue = color::add(blue, c_hx);

				FLinearColor converted_color = FLinearColor(red / 255.f, green / 255.f, blue / 255.f, 1.f);

				bool this_color_hovered = is_hovered(current, FVector2D(10, 10));
				bool this_color_clicked = left_mouse_clicked && this_color_hovered;

				if (this_color_clicked)
				{
					*color = converted_color;
					*active = false;
				}

				Functions().DrawFilledRect(current, 10, 10, converted_color);
				current.X += 10;
			}

			//green to blue
			for (float i = 0; i < 5.f; i++)
			{
				float percentage = i / 5.f;

				float hx = 255.f * percentage;

				float red = 0.f;
				float green = 255.f - hx;
				float blue = 255.f - green;

				red = color::add(red, c_hx);
				green = color::add(green, c_hx);
				blue = color::add(blue, c_hx);

				FLinearColor converted_color = FLinearColor(red / 255.f, green / 255.f, blue / 255.f, 1.f);

				bool this_color_hovered = is_hovered(current, FVector2D(10, 10));
				bool this_color_clicked = left_mouse_clicked && this_color_hovered;

				if (this_color_clicked)
				{
					*color = converted_color;
					*active = false;
				}

				Functions().DrawFilledRect(current, 10, 10, converted_color);
				current.X += 10;
			}

			//blue to red
			for (float i = 0; i < 5.f; i++)
			{
				float percentage = i / 5.f;

				float hx = 255.f * percentage;

				float green = 0.f;
				float blue = 255.f - hx;
				float red = 255.f - blue;

				red = color::add(red, c_hx);
				green = color::add(green, c_hx);
				blue = color::add(blue, c_hx);

				FLinearColor converted_color = FLinearColor(red / 255.f, green / 255.f, blue / 255.f, 1.f);

				bool this_color_hovered = is_hovered(current, FVector2D(10, 10));
				bool this_color_clicked = left_mouse_clicked && this_color_hovered;

				if (this_color_clicked)
				{
					*color = converted_color;
					*active = false;
				}

				Functions().DrawFilledRect(current, 10, 10, converted_color);
				current.X += 10;
			}

			current.X = current_x_backup;
			current.Y += 10;
		}

		current.X = current_x_backup;

		//white to black
		for (float i = 0; i < 15.f; i++)
		{
			float percentage = i / 15.f;

			float hx = 255.f * percentage;

			float green = 255.f - hx;
			float blue = 255.f - hx;
			float red = 255.f - hx;

			FLinearColor converted_color = FLinearColor(red / 255.f, green / 255.f, blue / 255.f, 1.f);

			bool this_color_hovered = is_hovered(current, FVector2D(10, 10));
			bool this_color_clicked = left_mouse_clicked && this_color_hovered;

			if (this_color_clicked)
			{
				*color = converted_color;
				*active = false;
			}

			Functions().DrawFilledRect(current, 10, 10, converted_color);
			current.X += 10;
		}
	}

	this->offset.Y += size.Y + this->item_spacing + 1;
}

void gui::slider(wchar_t* text, double min, double max, double* value)
{
	FVector2D current = this->position + this->offset;
	FVector2D size = FVector2D(100, 7);
	FLinearColor draw_color = FLinearColor();

	auto converted_text = SDK().BuildString_Double(text, FString(xor_w(L" (")), *value, FString(xor_w(L")")));
	SDK().K2_DrawText(Globals::Roboto, converted_text.c_str(), FVector2D(current.X + size.X + 5, current.Y + 1), FVector2D(1.0f, 1.0f), this->text_color, 1.0f, FLinearColor(0, 0, 0, 1.0f), FVector2D(), false, true, false, FLinearColor(0, 0, 0, 1.0f));

	bool hovered = is_hovered(FVector2D(current.X, current.Y - 1), FVector2D(size.X, size.Y + 2));
	bool down = left_mouse_down && hovered;

	if (hovered && down && !total_open_popups) {
		*value = ((this->cursor.X - current.X) * ((max - min) / size.Y)) + min;
		*value = static_cast<int>(*value);
		if (*value < min) *value = min;
		if (*value > max) *value = max;
	}

	if (hovered)
		draw_color = this->frame_hovered_color;
	else if (down)
		draw_color = this->frame_pressed_color;
	else
		draw_color = this->frame_color;

	Functions().DrawFilledRect(FVector2D(current.X, current.Y + 1), size.X, size.Y - 2, draw_color);
	SDK().K2_DrawBox(FVector2D(current.X, current.Y + 1), FVector2D(size.X, size.Y - 2), 1.f, FLinearColor(0.f, 0.f, 0.f, 1.f));

	double percent = size.X / (max - min);
	double point_differ = 2;

	FVector2D point = FVector2D(percent * (*value - min), size.Y);
	Functions().DrawFilledRect(FVector2D(current.X + point.X - 2, current.Y - point_differ + 1), 2, size.Y + (point_differ * 2), this->main_color);

	this->offset.Y += size.Y + this->item_spacing + 6;
}

bool gui::button(wchar_t* text, bool active)
{
	FVector2D current = this->position + this->offset;
	FVector2D size = FVector2D(100, 30);
	FLinearColor draw_color = FLinearColor();

	bool hovered = is_hovered(current, size);
	bool clicked = left_mouse_clicked && hovered;

	if (active)
		draw_color = this->main_color;
	else if (hovered)
		draw_color = this->frame_hovered_color;
	else
		draw_color = this->frame_color;

	Functions().DrawFilledRect(current, 4, size.Y, draw_color);
	SDK().K2_DrawBox(current, FVector2D(4, size.Y), 1.f, FLinearColor(0.f, 0.f, 0.f, 1.f));
	SDK().K2_DrawText(Globals::Roboto, text, FVector2D(current.X + 9, current.Y + (size.Y / 2) - 1), FVector2D(1.0f, 1.0f), this->text_color, 1.0f, FLinearColor(0, 0, 0, 1.0f), FVector2D(), false, true, false, FLinearColor(0, 0, 0, 1.0f));

	this->offset.Y += size.Y + 9;

	return clicked;
}

bool gui::button_2(wchar_t* text)
{
	FVector2D current = this->position + this->offset;
	FVector2D size = FVector2D(120, 20);

	bool hovered = is_hovered(current, size);
	bool clicked = left_mouse_clicked && hovered;

	Functions().DrawFilledRect(current, size.X, size.Y, this->frame_color);
	SDK().K2_DrawBox(current, size, 1.f, FLinearColor(0.f, 0.f, 0.f, 1.f));

	SDK().K2_DrawText(Globals::Roboto, text, FVector2D(current.X + (size.X / 2), current.Y + 2), FVector2D(1.0f, 1.0f), this->text_color, 1.0f, FLinearColor(0, 0, 0, 1.0f), FVector2D(), true, false, false, FLinearColor(0, 0, 0, 1.0f));

	this->offset.Y += size.Y + 9;

	return clicked;
}

void gui::text(wchar_t* text)
{
	FVector2D current = this->position + this->offset;

	SDK().K2_DrawText(Globals::Roboto, text, FVector2D(current.X - 1, current.Y - 4), FVector2D(1.0f, 1.0f), this->text_color, 1.0f, FLinearColor(0, 0, 0, 1.0f), FVector2D(), false, false, false, FLinearColor(0, 0, 0, 1.0f));

	this->offset.Y += 6 + this->item_spacing;
}

void gui::space(double x, double y)
{
	this->offset += FVector2D(x, y);
}

void gui::set_x(double value)
{
	this->offset.X = value;
}
void gui::set_y(double value)
{
	this->offset.Y = value;
}

void gui::draw_card(const wchar_t* header_text, FVector2D card_position, FVector2D card_size, FVector2D main_menu_size) {
	FLinearColor card_background_color = FLinearColor(15.0f, 15.0f, 15.0f, 1.0f); // Slightly lighter than main menu
	FLinearColor card_header_color = FLinearColor(20.0f, 20.0f, 20.0f, 1.0f); // Card header color
	float header_height = 20.0f; // Height of the header

	// Calculate the width of the header text and set the position to center it
	float text_width = SDK().K2_StrLen(Globals::Roboto, header_text);
	FVector2D header_text_position = FVector2D(
		card_position.X + (card_size.X - text_width) / 2,
		card_position.Y + (header_height / 2) - (SDK().K2_TextSize(Globals::Roboto, header_text, FVector2D(1.0f, 1.0f)).Y / 2)
	);

	// Draw the card header
	Functions().DrawFilledRect(card_position, card_size.X, header_height, card_header_color);

	// Draw the header text centered
	SDK().K2_DrawText(Globals::Roboto, header_text, header_text_position, FVector2D(1.0f, 1.0f), this->text_color, 1.0f, FLinearColor(), FVector2D(), true, false, false, FLinearColor());

	// Offset the background position below the header
	FVector2D background_position = card_position + FVector2D(0, header_height);

	// Reduce the card height by the header height to fit the background in the remaining space
	FVector2D background_size = FVector2D(card_size.X, card_size.Y - header_height);

	// Draw the card background below the header
	Functions().DrawFilledRect(background_position, background_size.X, background_size.Y, card_background_color);
}

bool gui::begin(wchar_t* title, FVector2D start_position, FVector2D size)
{
	if (!this->initialized)
	{
		this->init();
		this->position = start_position;
		this->size = size;

		this->initialized = true;
	}

	total_open_popups = 0;

	bool insert_down = SDK().WasInputKeyJustPressed(Globals::Insert);

	this->cursor = SDK().VectorGetMousePosition();//render::controller->get_mouse_position();
	this->left_mouse_clicked = SDK().WasInputKeyJustPressed(Globals::LeftClick);
	this->left_mouse_down = SDK().IsInputKeyDown(Globals::LeftClick);
	this->right_mouse_clicked = SDK().WasInputKeyJustPressed(Globals::RightClick);
	this->right_mouse_down = SDK().IsInputKeyDown(Globals::RightClick);
	this->offset = FVector2D(10, 20);

	static FVector2D static_cursor = FVector2D();
	static FVector2D static_calculated = FVector2D();

	if (this->is_hovered(this->position, FVector2D(this->size.X, 20)) && left_mouse_down)
	{
		if (!static_cursor)
		{
			static_cursor = this->cursor;
		}

		if (!static_calculated)
		{
			static_calculated = static_cursor - this->position;
		}
	}

	if (static_cursor && static_calculated)
	{
		this->position = this->cursor - static_calculated;
	}

	if (!this->left_mouse_down)
	{
		static_cursor = FVector2D();
		static_calculated = FVector2D();
	}

	Functions().DrawFilledRect(this->position, this->size.X, this->size.Y, this->background_color);
	SDK().K2_DrawBox(this->position, this->size, 1.f, FLinearColor(0.f, 0.f, 0.f, 1.f));
	FVector2D loc = FVector2D(this->position.X + this->size.X - 55, this->position.Y + 5);
	SDK().K2_DrawText(Globals::Roboto, title, loc, FVector2D(1.0f, 1.0f), this->text_color, 1.0f, FLinearColor(0, 0, 0, 1.0f), FVector2D(), false, false, false, FLinearColor(0, 0, 0, 1.0f));

	return true;
}
bool gui::end()
{
	Functions().DrawFilledRect(FVector2D(this->cursor.X - 4, this->cursor.Y - 4), 4, 4, this->text_color);

	return true;
}

void gui::run() {
	static auto menu_tab = int(0);
	//////////////////////////////////////////x//////y
	begin((L""), FVector2D(100, 200), FVector2D(650, 310));

	set_y(65);

	if (button(xor_w(L"Aimbot"), menu_tab == 0)) menu_tab = 0;
	if (button(xor_w(L"Player"), menu_tab == 1)) menu_tab = 1;
	if (button(xor_w(L"World"), menu_tab == 2)) menu_tab = 2;
	if (button(xor_w(L"Miscellaneous"), menu_tab == 3)) menu_tab = 3;

	set_x(130);
	set_y(30);

	if (menu_tab == 0)
	{
		FVector2D card1_position = FVector2D(130, 65);
		FVector2D card1_size = FVector2D(200, 200);

		// Child 1
		draw_card(xor_w(L"Aimbot Options:"), card1_position, card1_size, this->size);
		this->offset = card1_position + FVector2D(10, 30);

		checkbox(xor_w(L"Enable Aimbot (F1)"), &Config.Aimbot.Enabled);
		if (Config.Aimbot.Enabled) {
			checkbox(xor_w(L"Disable On Spectate"), &Config.Aimbot.DisableOnSpectate);
			checkbox(xor_w(L"Aim Prediction"), &Config.Aimbot.ProjectilePrediction);
		}
		checkbox(xor_w(L"TriggerBot"), &Config.Aimbot.Triggerbot);
		checkbox(xor_w(L"FOV Circle"), &Config.Aimbot.DrawFOV);
			
		set_x(370);
		set_y(30);

		// Child 2
		FVector2D card2_position = FVector2D(370, 65);
		FVector2D card2_size = FVector2D(200, 200);

		draw_card(xor_w(L"Configuration:"), card2_position, card2_size, this->size);
		this->offset = card2_position + FVector2D(10, 30);

		slider(xor_w(L"Smooth (F3/F4)"), 1, 30, &Config.Aimbot.Smooth);

		if (Config.Aimbot.Triggerbot) {
			slider(xor_w(L"Triggerbot Delay"), 0, 5, &Config.Aimbot.TriggerbotDelay);
		}

		/*combo(xor_w(L"AimBone"), &isComboActive, &selectedAimBone, aimOptions, numOptions);
		Config.Aimbot.BoneTarget = selectedAimBone;*/
	}
	else if (menu_tab == 1)
	{
		// Child 1
		text(xor_w(L"Visual Options:"));
		space(5, 5);

		//switch
		set_x(370);
		set_y(30);

		// Child 2
		text(xor_w(L"Configuration:"));
		space(5, 5);

	}
	else if (menu_tab == 2)
	{
		// Child 1
		text(xor_w(L"World Options:"));
		space(5, 5);
	
		set_x(370);
		set_y(30);

		// Child 2
		text(xor_w(L"Configuration:"));
		space(5, 5);	
	}

	else if (menu_tab == 3)
	{
		// Child 1
		text(xor_w(L"Misc Options:"));
		space(5, 5);	

		set_x(370);
		set_y(30);

		// Child 2
		text(xor_w(L"Configuration:"));
		space(5, 5);
	}

	end();
}