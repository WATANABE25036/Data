/*==============================================================================

   サウンド処理 [Sound.h]
														 Author : 学校配布
														 Date   : ***
--------------------------------------------------------------------------------

==============================================================================*/
#pragma once

#include <windows.h>
#include "xaudio2.h"


bool InitSound(HWND hWnd);
void UninitSound(void);

int LoadSound(char* pFilename);
void PlaySound(int index, int loopCount);
void PlaySound(int index, int loopCount, float volume);
void StopSound(int index);
void StopSoundAll(void);
void SetVolume(int index, float vol);
