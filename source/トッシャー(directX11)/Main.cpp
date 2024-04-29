/*==============================================================================

   メイン [Main.cpp]
														 Author : 学校配布、渡邉 修
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
// マクロ定義
//*****************************************************************************
#define CLASS_NAME		"AppClass"		// ウインドウのクラス名
#define WINDOW_NAME		"Tosher"		// ウインドウのキャプション名
#define START_SCENE		(SCENE_TITLE)	//最初のシーン

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
void Uninit(void);
void Update(void);
void Draw(void);

//*****************************************************************************
// グローバル変数:
//*****************************************************************************
long g_MouseX = 0;
long g_MouseY = 0;

#ifdef _DEBUG
int		g_CountFPS;							// FPSカウンタ
char	g_DebugStrTab[2048] = WINDOW_NAME;	// デバッグ文字表示用(ウインドウのキャプション)
//char	g_DebugStr[2048] = " ";	// デバッグ文字表示用(スクリーン表示用)
std::vector<std::string> g_DebugStr(MAX_DEBUG_STRINGS);
#endif

SceneManager g_SceneManager;
HWND* g_phWnd;

//=============================================================================
// メイン関数
//=============================================================================
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);	// 無くても良いけど、警告が出る（未使用宣言）
	UNREFERENCED_PARAMETER(lpCmdLine);		// 無くても良いけど、警告が出る（未使用宣言）

	srand((unsigned int)time(NULL));
	
	// 時間計測用
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
	
	// ウィンドウクラスの登録
	RegisterClassEx(&wcex);

	int window_width =  960 /*1280*/ /*1920*/ /*960*/;
	int window_height = 540 /*720*/ /*1080*/ /*540*/;

	// ウィンドウの作成
	hWnd = CreateWindow(CLASS_NAME,
		WINDOW_NAME,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,																		// ウィンドウの左座標
		CW_USEDEFAULT,																		// ウィンドウの上座標
		window_width + GetSystemMetrics(SM_CXDLGFRAME) * 2,									// ウィンドウ横幅
		window_height + GetSystemMetrics(SM_CXDLGFRAME) * 2 + GetSystemMetrics(SM_CYCAPTION),	// ウィンドウ縦幅
		NULL,
		NULL,
		hInstance,
		NULL);

	// 初期化処理(ウィンドウを作成してから行う)
	if(FAILED(Init(hInstance, hWnd, TRUE)))
	{
		return -1;
	}

	// フレームカウント初期化
	timeBeginPeriod(1);	// 分解能を設定
	dwExecLastTime = dwFPSLastTime = timeGetTime();	// システム時刻をミリ秒単位で取得
	dwCurrentTime = dwFrameCount = 0;

	// ウインドウの表示(初期化処理の後に呼ばないと駄目)
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	g_phWnd = &hWnd;




	// メッセージループ
	while(1)
	{
        if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if(msg.message == WM_QUIT)
			{// PostQuitMessage()が呼ばれたらループ終了
				break;
			}
			else
			{
				// メッセージの翻訳と送出
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
        }
		else
		{
			dwCurrentTime = timeGetTime();

			if ((dwCurrentTime - dwFPSLastTime) >= 1000)	// 1秒ごとに実行
			{
#ifdef _DEBUG
				g_CountFPS = dwFrameCount;
#endif
				dwFPSLastTime = dwCurrentTime;			// FPSを測定した時刻を保存
				dwFrameCount = 0;							// カウントをクリア
			}

			if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))	// 1/60秒ごとに実行
			{
				dwExecLastTime = dwCurrentTime;	// 処理した時刻を保存

#ifdef _DEBUG	// デバッグ版の時だけFPSを表示する
				wsprintf(g_DebugStrTab, WINDOW_NAME);
				wsprintf(&g_DebugStrTab[strlen(g_DebugStrTab)], " FPS:%d", g_CountFPS);
				SetWindowText(hWnd, g_DebugStrTab);
#endif
				Update();			// 更新処理
				Draw();				// 描画処理

#ifdef _DEBUG	// デバッグ版の時だけ表示する
				//wsprintf(&g_DebugStrTab[strlen(g_DebugStrTab)], " MX:%d MY:%d", GetMousePosX(), GetMousePosY());
				//SetWindowText(hWnd, g_DebugStrTab);
#endif

				dwFrameCount++;
			}
		}
	}

	timeEndPeriod(1);				// 分解能を戻す

	// ウィンドウクラスの登録を解除
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	// 終了処理
	Uninit();

	return (int)msg.wParam;
}

//=============================================================================
// プロシージャ
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

#else//デバッグではないとき
			if (MessageBox(NULL,"ゲーム終了","確認", MB_OKCANCEL) == IDOK)
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
// 初期化処理
//=============================================================================
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	InitRenderer(hInstance, hWnd, bWindow);

	// 入力処理の初期化
	InitInput(hInstance, hWnd);

	// サウンド処理の初期化
	InitSound(hWnd);

	// スプライトの初期化
	InitSprite();

	// 背面ポリゴンをカリング
	SetCullingMode(CULL_MODE_BACK);

	//シーンマネージャー初期化
	g_SceneManager.Init(START_SCENE);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void Uninit(void)
{
	//シーンマネージャー終了処理
	g_SceneManager.Uninit();

	// スプライトの終了処理
	UninitSprite();

	//テクスチャの解放
	UninitTexture();

	//サウンドの終了処理
	StopSoundAll();
	UninitSound();

	//入力の終了処理
	UninitInput();

	//レンダーの終了処理
	UninitRenderer();
}

//=============================================================================
// 更新処理
//=============================================================================
void Update(void)
{
	// 入力の更新処理
	UpdateInput();

	//シーンマネージャー更新処理
	g_SceneManager.Update();
}

//=============================================================================
// 描画処理
//=============================================================================
void Draw(void)
{
	// バックバッファクリア
	Clear();

	// シーンマネージャー描画処理
	g_SceneManager.Draw();

	//デバッグ表示
#ifdef _DEBUG	// デバッグ版の時だけ表示する
	for (int i = 0; i < MAX_STRINGS_LENGTH; i++)
	{
		DebugTextOut(GetDebugStr(i), 0, 45 * i); //デバッグ用文字列表示
	}

#endif

	// バックバッファ、フロントバッファ入れ替え
	Present();
}

//-----------------------------------------------------------------------------
// マウス座標取得
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
// ウィンドウやクライアントの大きさを取得する
// [引数] 0: ウィンドウサイズ, 1: クライアントサイズ 
//-----------------------------------------------------------------------------
RECT GetWindowContainerSize(int option)
{
	HWND hWnd = GetActiveWindow();//ウィンドウを取得
	RECT rect = { 0 };//四角形構造体
	if (option == 0)GetWindowRect(hWnd, &rect);//ウィンドウの左上隅と右下隅の座標を取得
	else if (option == 1)GetClientRect(hWnd, &rect);//クライアント(アプリ画面)の左上隅と右下隅の座標を取得
	return rect;
}

//-----------------------------------------------------------------------------
// ウィンドウ幅を取得する
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
// デバッグ
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
		return g_DebugStr[index].c_str();//const char* に変換
	}

	return nullptr;
}

#endif

//-----------------------------------------------------------------------------
// デバッグの出力
// 例 ("X" + std::to_string(cursorPos.x) + "   Y" + std::to_string(cursorPos.y));
//-----------------------------------------------------------------------------
void DebugPrint(const std::string& message1)
{
	OutputDebugStringA(("デバッグ: " + message1 + "\n").c_str());
}

void DebugPrint(const std::string& message1, const float& message2)
{
	OutputDebugStringA(("デバッグ: " + message1 + std::to_string(message2) + "\n").c_str());
}

void DebugPrint(const std::string& message1, const float& message2, const float& message3)
{
	OutputDebugStringA(("デバッグ: " + message1 + std::to_string(message2) + std::to_string(message3) + "\n").c_str());
}

void DebugPrint(const std::string& message1, const float& message2, const float& message3, const float& message4)
{
	OutputDebugStringA(("デバッグ: " + message1 + std::to_string(message2) + std::to_string(message3) + std::to_string(message4) + "\n").c_str());
}

void DebugPrint(const std::string& message1, const float& message2, const float& message3, const float& message4, const float& message5)
{
	OutputDebugStringA(("デバッグ: " + message1 + std::to_string(message2) + std::to_string(message3) + std::to_string(message4) + std::to_string(message5) + "\n").c_str());
}

void DebugPrint(const float& message1, const float& message2, std::string message3)
{
	OutputDebugStringA(("デバッグ: " + std::to_string(message1) + "		" + std::to_string(message2) + "	:" + message3 + "\n").c_str());
}

//-----------------------------------------------------------------------------
//ウィンドウのポインターを取得
//-----------------------------------------------------------------------------
HWND* GethWnd(void)
{
	return g_phWnd;
}

//-----------------------------------------------------------------------------
//ウィンドウの中央座標を取得
//-----------------------------------------------------------------------------
bool GetWindowCenter(POINT& center)
{
	RECT clientRect;
	if (!GetClientRect(*g_phWnd, &clientRect)) {
		// クライアント領域の取得に失敗
		return false;
	}

	center.x = clientRect.left + (clientRect.right - clientRect.left) / 2;
	center.y = clientRect.top + (clientRect.bottom - clientRect.top) / 2;

	return true;
}