/*==============================================================================

   ���C�� [Main.h]
														 Author : 
														 Date   : 
--------------------------------------------------------------------------------

==============================================================================*/
#pragma once


#pragma warning(push)
#pragma warning(disable:4005)

#define _CRT_SECURE_NO_WARNINGS			// scanf ��warning�h�~
#include <stdio.h>

#include <d3d11.h>
#include <d3dx11.h>
#include <d3dcompiler.h>
#include <d3dx9.h>

#define DIRECTINPUT_VERSION 0x0800		// �x���Ώ�
#include "dinput.h"
#include "mmsystem.h"

#pragma warning(pop)

#include <string>

//*****************************************************************************
// ���C�u�����̃����N
//*****************************************************************************
#pragma comment (lib, "d3d11.lib")		
#pragma comment (lib, "d3dcompiler.lib")
#pragma comment (lib, "d3dx11.lib")	
#pragma comment (lib, "d3dx9.lib")	
#pragma comment (lib, "winmm.lib")
#pragma comment (lib, "dxerr.lib")
#pragma comment (lib, "dxguid.lib")
#pragma comment (lib, "dinput8.lib")


//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define SCREEN_WIDTH	(1920)			// �E�C���h�E�̕�
#define SCREEN_HEIGHT	(1080)			// �E�C���h�E�̍���
#define SCREEN_CENTER_X	(SCREEN_WIDTH / 2)	// �E�C���h�E�̒��S�w���W
#define SCREEN_CENTER_Y	(SCREEN_HEIGHT / 2)	// �E�C���h�E�̒��S�x���W
#define START_SCENE	(SCENE_TITLE)
#define MAX_DEBUG_STRINGS	(2048)
#define MAX_STRINGS_LENGTH	(30)

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
long GetMousePosX(void);
long GetMousePosY(void);
RECT GetWindowContainerSize(int option);
LONG GetClientWidth();
LONG GetClientHeight();
char* GetDebugStrTab(void);
void SetDebugStr(int index,
	const std::string& text1 = "---", const float& value1 = 0.0f,
	const std::string& text2 = "---", const float& value2 = 0.0f,
	const std::string& text3 = "---", const float& value3 = 0.0f);
const char* GetDebugStr(int index);
void DebugPrint(const std::string& message1);
void DebugPrint(const std::string& message1, const float& message2);
void DebugPrint(const std::string& message1, const float& message2, const float& message3);
void DebugPrint(const std::string& message1, const float& message2, const float& message3, const float& message4);
void DebugPrint(const std::string& message1, const float& message2, const float& message3, const float& message4, const float& message5);
void DebugPrint(const float& message1, const float& message2 = 0.00f, std::string message3 = " ");
HWND* GethWnd(void);
bool GetWindowCenter(POINT& center);

//*****************************************************************************
// �f�o�b�O�\������
//*****************************************************************************
#define DEBUG_DISP_TEXTOUT //���̍s������ƃf�o�b�O�@�\�������悤�ɂȂ�
