#pragma once

#include "../../stdafx.h"

void DrawTransistion(void* UGameViewPortClient, void* Canvas);

static float lastFireTime = 0;
static bool isHooked = true;
static uint64_t OldCurrentWeapon = NULL;
static bool InitRecoil = false;
static FKey KeyBind;
static bool PanicEnabled = false;