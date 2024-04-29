/*==============================================================================

   ���C�� [Main.cpp]
														 Author : �w�Z�z�z�A�n� �C
														 Date   : ***
--------------------------------------------------------------------------------

==============================================================================*/
#include <time.h>
#include <vector>
#include <string>
#include "Main.h"
#include "Renderer.h"
#include "Input.h"
#include "Sound.h"
#include "Camera.h"
#include "Texture.h"
#include "Sprite.h"
#include "Scene.h"
#include "SceneManager.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define CLASS_NAME		"AppClass"		// �E�C���h�E�̃N���X��
#define WINDOW_NAME		"Tosher"		// �E�C���h�E�̃L���v�V������
#define START_SCENE		(SCENE_TITLE)	//�ŏ��̃V�[��

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
void Uninit(void);
void Update(void);
void Draw(void);

//*****************************************************************************
// �O���[�o���ϐ�:
//*****************************************************************************
long g_MouseX = 0;
long g_MouseY = 0;

#ifdef _DEBUG
int		g_CountFPS;							// FPS�J�E���^
char	g_DebugStrTab[2048] = WINDOW_NAME;	// �f�o�b�O�����\���p(�E�C���h�E�̃L���v�V����)
//char	g_DebugStr[2048] = " ";	// �f�o�b�O�����\���p(�X�N���[���\���p)
std::vector<std::string> g_DebugStr(MAX_DEBUG_STRINGS);
#endif

SceneManager g_SceneManager;
HWND* g_phWnd;

//=============================================================================
// ���C���֐�
//=============================================================================
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);	// �����Ă��ǂ����ǁA�x�����o��i���g�p�錾�j
	UNREFERENCED_PARAMETER(lpCmdLine);		// �����Ă��ǂ����ǁA�x�����o��i���g�p�錾�j

	srand((unsigned int)time(NULL));
	
	// ���Ԍv���p
	DWORD dwExecLastTime;
	DWORD dwFPSLastTime;
	DWORD dwCurrentTime;
	DWORD dwFrameCount;

	WNDCLASSEX	wcex = {
		sizeof(WNDCLASSEX),
		CS_CLASSDC,
		WndProc,
		0,
		0,
		hInstance,
		NULL,
		LoadCursor(NULL, IDC_ARROW),
		(HBRUSH)(COLOR_WINDOW + 1),
		NULL,
		CLASS_NAME,
		NULL
	};
	HWND		hWnd;
	MSG			msg;
	
	// �E�B���h�E�N���X�̓o�^
	RegisterClassEx(&wcex);

	int window_width =  960 /*1280*/ /*1920*/ /*960*/;
	int window_height = 540 /*720*/ /*1080*/ /*540*/;

	// �E�B���h�E�̍쐬
	hWnd = CreateWindow(CLASS_NAME,
		WINDOW_NAME,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,																		// �E�B���h�E�̍����W
		CW_USEDEFAULT,																		// �E�B���h�E�̏���W
		window_width + GetSystemMetrics(SM_CXDLGFRAME) * 2,									// �E�B���h�E����
		window_height + GetSystemMetrics(SM_CXDLGFRAME) * 2 + GetSystemMetrics(SM_CYCAPTION),	// �E�B���h�E�c��
		NULL,
		NULL,
		hInstance,
		NULL);

	// ����������(�E�B���h�E���쐬���Ă���s��)
	if(FAILED(Init(hInstance, hWnd, TRUE)))
	{
		return -1;
	}

	// �t���[���J�E���g������
	timeBeginPeriod(1);	// ����\��ݒ�
	dwExecLastTime = dwFPSLastTime = timeGetTime();	// �V�X�e���������~���b�P�ʂŎ擾
	dwCurrentTime = dwFrameCount = 0;

	// �E�C���h�E�̕\��(�����������̌�ɌĂ΂Ȃ��Ƒʖ�)
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	g_phWnd = &hWnd;




	// ���b�Z�[�W���[�v
	while(1)
	{
        if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if(msg.message == WM_QUIT)
			{// PostQuitMessage()���Ă΂ꂽ�烋�[�v�I��
				break;
			}
			else
			{
				// ���b�Z�[�W�̖|��Ƒ��o
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
        }
		else
		{
			dwCurrentTime = timeGetTime();

			if ((dwCurrentTime - dwFPSLastTime) >= 1000)	// 1�b���ƂɎ��s
			{
#ifdef _DEBUG
				g_CountFPS = dwFrameCount;
#endif
				dwFPSLastTime = dwCurrentTime;			// FPS�𑪒肵��������ۑ�
				dwFrameCount = 0;							// �J�E���g���N���A
			}

			if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))	// 1/60�b���ƂɎ��s
			{
				dwExecLastTime = dwCurrentTime;	// ��������������ۑ�

#ifdef _DEBUG	// �f�o�b�O�ł̎�����FPS��\������
				wsprintf(g_DebugStrTab, WINDOW_NAME);
				wsprintf(&g_DebugStrTab[strlen(g_DebugStrTab)], " FPS:%d", g_CountFPS);
				SetWindowText(hWnd, g_DebugStrTab);
#endif
				Update();			// �X�V����
				Draw();				// �`�揈��

#ifdef _DEBUG	// �f�o�b�O�ł̎������\������
				//wsprintf(&g_DebugStrTab[strlen(g_DebugStrTab)], " MX:%d MY:%d", GetMousePosX(), GetMousePosY());
				//SetWindowText(hWnd, g_DebugStrTab);
#endif

				dwFrameCount++;
			}
		}
	}

	timeEndPeriod(1);				// ����\��߂�

	// �E�B���h�E�N���X�̓o�^������
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	// �I������
	Uninit();

	return (int)msg.wParam;
}

//=============================================================================
// �v���V�[�W��
//=============================================================================
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch(message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		switch(wParam)
		{
		case VK_ESCAPE:

#ifdef _DEBUG
			DestroyWindow(hWnd);

#else//�f�o�b�O�ł͂Ȃ��Ƃ�
			if (MessageBox(NULL,"�Q�[���I��","�m�F", MB_OKCANCEL) == IDOK)
				DestroyWindow(hWnd);
#endif

			break;
		}
		break;

	case WM_MOUSEMOVE:
		g_MouseX = LOWORD(lParam);
		g_MouseY = HIWORD(lParam);
		break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	InitRenderer(hInstance, hWnd, bWindow);

	// ���͏����̏�����
	InitInput(hInstance, hWnd);

	// �T�E���h�����̏�����
	InitSound(hWnd);

	// �X�v���C�g�̏�����
	InitSprite();

	// �w�ʃ|���S�����J�����O
	SetCullingMode(CULL_MODE_BACK);

	//�V�[���}�l�[�W���[������
	g_SceneManager.Init(START_SCENE);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void Uninit(void)
{
	//�V�[���}�l�[�W���[�I������
	g_SceneManager.Uninit();

	// �X�v���C�g�̏I������
	UninitSprite();

	//�e�N�X�`���̉��
	UninitTexture();

	//�T�E���h�̏I������
	StopSoundAll();
	UninitSound();

	//���͂̏I������
	UninitInput();

	//�����_�[�̏I������
	UninitRenderer();
}

//=============================================================================
// �X�V����
//=============================================================================
void Update(void)
{
	// ���͂̍X�V����
	UpdateInput();

	//�V�[���}�l�[�W���[�X�V����
	g_SceneManager.Update();
}

//=============================================================================
// �`�揈��
//=============================================================================
void Draw(void)
{
	// �o�b�N�o�b�t�@�N���A
	Clear();

	// �V�[���}�l�[�W���[�`�揈��
	g_SceneManager.Draw();

	//�f�o�b�O�\��
#ifdef _DEBUG	// �f�o�b�O�ł̎������\������
	for (int i = 0; i < MAX_STRINGS_LENGTH; i++)
	{
		DebugTextOut(GetDebugStr(i), 0, 45 * i); //�f�o�b�O�p������\��
	}

#endif

	// �o�b�N�o�b�t�@�A�t�����g�o�b�t�@����ւ�
	Present();
}

//-----------------------------------------------------------------------------
// �}�E�X���W�擾
//-----------------------------------------------------------------------------
long GetMousePosX(void)
{
	return g_MouseX;
}

long GetMousePosY(void)
{
	return g_MouseY;
}

//-----------------------------------------------------------------------------
// �E�B���h�E��N���C�A���g�̑傫�����擾����
// [����] 0: �E�B���h�E�T�C�Y, 1: �N���C�A���g�T�C�Y 
//-----------------------------------------------------------------------------
RECT GetWindowContainerSize(int option)
{
	HWND hWnd = GetActiveWindow();//�E�B���h�E���擾
	RECT rect = { 0 };//�l�p�`�\����
	if (option == 0)GetWindowRect(hWnd, &rect);//�E�B���h�E�̍�����ƉE�����̍��W���擾
	else if (option == 1)GetClientRect(hWnd, &rect);//�N���C�A���g(�A�v�����)�̍�����ƉE�����̍��W���擾
	return rect;
}

//-----------------------------------------------------------------------------
// �E�B���h�E�����擾����
//-----------------------------------------------------------------------------
LONG GetClientWidth()
{
	RECT rect = GetWindowContainerSize(0);

	return 	rect.right;
}

LONG GetClientHeight()
{
	RECT rect = GetWindowContainerSize(0);

	return 	rect.bottom;
}

//-----------------------------------------------------------------------------
// �f�o�b�O
//-----------------------------------------------------------------------------
#ifdef _DEBUG
char* GetDebugStrTab(void)
{
	return g_DebugStrTab;
}

void SetDebugStr(int index, 
	const std::string& text1, const float& value1,
	const std::string& text2, const float& value2,
	const std::string& text3, const float& value3)
{
	if (index >= 0 && index < MAX_DEBUG_STRINGS)
	{
		g_DebugStr[index] =
			text1 + " : " + std::to_string(value1) + "   " +
			text2 + " : " + std::to_string(value2) + "   " +
			text3 + " : " + std::to_string(value3);
	}
}

const char* GetDebugStr(int index)
{
	if (index >= 0 && index < MAX_DEBUG_STRINGS)
	{
		return g_DebugStr[index].c_str();//const char* �ɕϊ�
	}

	return nullptr;
}

#endif

//-----------------------------------------------------------------------------
// �f�o�b�O�̏o��
// �� ("X" + std::to_string(cursorPos.x) + "   Y" + std::to_string(cursorPos.y));
//-----------------------------------------------------------------------------
void DebugPrint(const std::string& message1)
{
	OutputDebugStringA(("�f�o�b�O: " + message1 + "\n").c_str());
}

void DebugPrint(const std::string& message1, const float& message2)
{
	OutputDebugStringA(("�f�o�b�O: " + message1 + std::to_string(message2) + "\n").c_str());
}

void DebugPrint(const std::string& message1, const float& message2, const float& message3)
{
	OutputDebugStringA(("�f�o�b�O: " + message1 + std::to_string(message2) + std::to_string(message3) + "\n").c_str());
}

void DebugPrint(const std::string& message1, const float& message2, const float& message3, const float& message4)
{
	OutputDebugStringA(("�f�o�b�O: " + message1 + std::to_string(message2) + std::to_string(message3) + std::to_string(message4) + "\n").c_str());
}

void DebugPrint(const std::string& message1, const float& message2, const float& message3, const float& message4, const float& message5)
{
	OutputDebugStringA(("�f�o�b�O: " + message1 + std::to_string(message2) + std::to_string(message3) + std::to_string(message4) + std::to_string(message5) + "\n").c_str());
}

void DebugPrint(const float& message1, const float& message2, std::string message3)
{
	OutputDebugStringA(("�f�o�b�O: " + std::to_string(message1) + "		" + std::to_string(message2) + "	:" + message3 + "\n").c_str());
}

//-----------------------------------------------------------------------------
//�E�B���h�E�̃|�C���^�[���擾
//-----------------------------------------------------------------------------
HWND* GethWnd(void)
{
	return g_phWnd;
}

//-----------------------------------------------------------------------------
//�E�B���h�E�̒������W���擾
//-----------------------------------------------------------------------------
bool GetWindowCenter(POINT& center)
{
	RECT clientRect;
	if (!GetClientRect(*g_phWnd, &clientRect)) {
		// �N���C�A���g�̈�̎擾�Ɏ��s
		return false;
	}

	center.x = clientRect.left + (clientRect.right - clientRect.left) / 2;
	center.y = clientRect.top + (clientRect.bottom - clientRect.top) / 2;

	return true;
}