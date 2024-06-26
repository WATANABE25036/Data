//===================================================
//tF[h(fade.h)
//Auhor:nç³ C	Date:2023.8.11
//===================================================
#pragma once
#ifndef _FADE_H_
#define _FADE_H_
#include "main.h"

//---------------------------------------------------
//}Nè`
//---------------------------------------------------

//---------------------------------------------------
//ñÌé¾
//---------------------------------------------------
typedef enum
{
	FADE_STATE_NONE = 0,
	FADE_STATE_IN,
	FADE_STATE_OUT
}FADE_STATE;

//---------------------------------------------------
//\¢Ìé¾
//---------------------------------------------------
typedef struct 
{


}Fade;

//---------------------------------------------------
//vg^Cvé¾
//---------------------------------------------------
void InitFade();
void UninitFade();
void UpdateFade();
void DrawFade();
void SetFade(FADE_STATE st);
void SetFadeTime(float time);
void SceneTransition(SCENE NextScene);
void SceneFadeIn(SCENE nextScene);
void SetFadeColor(float r, float g, float b);
FADE_STATE GetFadeState();

#endif