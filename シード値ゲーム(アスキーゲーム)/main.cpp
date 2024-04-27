//====================================================
//課題CP18 №09(ネームバトラー)
//main.cpp
//製作者:渡邉 修 日付:2022/12/16
//====================================================
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <windows.h>
#include "conioex.h"

//----------------------------------------------------
//マクロ定義
//----------------------------------------------------
#define MAP_WIDTH		30		//マップの横の長さ
#define MAP_HIGHT		30		//マップの縦の高さ
#define ENTITY_MAX		10		//マップに表示するエンティティ(タイル)の種類
#define PLAYER_SPEED	4000	//プレイヤーのスピード(小さいほど速い)

//----------------------------------------------------
//列挙体宣言
//----------------------------------------------------
enum//タイル№
{
	TILE_AIR = 0,
	TILE_PLAYER,
	TILE_ENEMY,
	TILE_ENEMY_DETECTION_RED,
	TILE_ENEMY_DETECTION_YELLOW,
	TILE_TREASURE,
	TILE_WALL,
};

//----------------------------------------------------
//構造体宣言
//----------------------------------------------------
typedef struct//すべてのタイルの番号と見た目
{
	int number;
	char visual[64];
}OBJECT;

typedef struct//プレイヤーやエネミーなどの座標
{
	int x;
	int y;
	int oldX;
	int oldY;
}OBJECT_MOVE;

typedef struct//プレイした回のプレイヤーのスコアを入れる
{
	int score;
	char name[20];
}SCORE;

//----------------------------------------------------
//グローバル変数
//----------------------------------------------------
int map[MAP_HIGHT][MAP_WIDTH] =
{//   1           5              10             15             20             25             30             35             40             45             50
 //   |           |              |              |              |              |              |              |              |              |              | 
	{ 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6},/* 1 */
	{ 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6},
	{ 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6},
	{ 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6},
	{ 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6},/* 5 */
	{ 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6},
	{ 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6},
	{ 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6},
	{ 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6},
	{ 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6},/* 10 */
	{ 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6},
	{ 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6},
	{ 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6},
	{ 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6},
	{ 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6},/* 15 */
	{ 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6},
	{ 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6},
	{ 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6},
	{ 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6},
	{ 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6},/* 20 */
	{ 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6},
	{ 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6},
	{ 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6},
	{ 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6},
	{ 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6},/* 25 */
	{ 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6},
	{ 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6},
	{ 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6},
	{ 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6},
	{ 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6},/* 30 */
};

char uiFrame[30][41] =
{
	//  1 2 3 4 5 6 7 8 91011121314151617181920
	// ▽▼▽▼▽▼▽▼▽▼▽▼▽▼▽▼▽▼▽▼
	{ "┌――――――――――――――――――┐"},/* 1 */
	{ "│                                    │"},
	{ "│                                    │"},
	{ "│                                    │"},
	{ "│                                    │"},/* 5 */
	{ "│                                    │"},
	{ "│                                    │"},
	{ "│                                    │"},
	{ "│                                    │"},
	{ "│                                    │"},/* 10 */
	{ "│                                    │"},
	{ "│                                    │"},
	{ "│                                    │"},
	{ "│                                    │"},
	{ "│                                    │"},/* 15 */
	{ "│                                    │"},
	{ "│                                    │"},
	{ "│                                    │"},
	{ "│                                    │"},
	{ "│                                    │"},/* 20 */
	{ "│                                    │"},
	{ "│                                    │"},
	{ "│                                    │"},
	{ "│                                    │"},
	{ "│                                    │"},/* 25 */
	{ "│                                    │"},
	{ "│                                    │"},
	{ "│                                    │"},
	{ "│                                    │"},
	{ "└――――――――――――――――――┘"},/* 30 */
};

char uiWeapon[10][10] =//未使用
{
	//  1 2 3 4 5 6 7 8 91011121314151617181920
	// ▽▼▽▼▽▼▽▼▽▼▽▼▽▼▽▼▽▼▽▼
	{ "冂〒刀"},/* 1 */
	{ "＼∧ノ"},
	{ " /=ﾐﾍ"},
	{ "│ ⌒│"},
	{ "│| ﾐ│"},/* 5 */
	{ "│| ﾐ│"},
	{ "│: ｿ│"},
	{ " ﾍ⌒ﾉ"},
	{ "  ∀"},
};

char uiTreasur[6][30] =
{
	//  1 2 3 4 5 6 7 8 91011121314151617181920
	// ▽▼▽▼▽▼▽▼▽▼▽▼▽▼▽▼▽▼▽▼
	{ "    _＿___＿"},/* 1 */
	{ "  ／ \"\"\"\"γ⌒＼"},
	{ " //_____/___=ﾐ│"},
	{ "│ ;廿 |Τ|ﾞﾞﾞﾐ│"},
	{ "│ ;_＿|│ |_ ﾐﾐ│"},/* 5 */
	{ "└───── ┴───── ┘"},
};
	
char uiExplosionRange[7][16] =//未使用
{
	//  1 2 3 4 5 6 7 8 91011121314151617181920
	// ▽▼▽▼▽▼▽▼▽▼▽▼▽▼▽▼▽▼▽▼
	{ "＿／＼∧／＼＿"},/* 1 */
	{ "＼　　　　　／"},
	{ "／　／∨＼　＼"},
	{ "＞　＞　＜　＜"},
	{ "＼　＼∧／　／"},/* 5 */
	{ "／　　　　　＼"},
	{ "￣＼／∨＼／￣"},
};

/*
┌┬┐─┏┳┓━┠╂┨|
├┼┤│┣╋┫┃┰┸┯┷
└┴┘  ┗┻┛  ┝┿┥
＿￣∥「」=＝二≡三_
⊂⊃∪∩∈∋⊆丶ヽヾゝゞ´｀＼／
.¨ﾟﾞ":;_/ｿﾍﾉ|~^@#[]{}()=_
巛＜＞》《へヘﾍミﾐ／/丿ノﾉソｿ〆⊿彡∠∟∨∧
□■◇◆△▲▽▼○●☆★◎↑→←↓
＋－±×÷＝≠≡≒＜＞≦≧≪≫
∞∽∝√∠⊥⌒∂∫∬∴∵『』【】()〔〕{}〈〉「」
∧∨￢⇒⇔∀∃♂♀∇＃＆＊＠§※〒〓◯♯♭♪†‡¶￥＄℃￠￡％Å‰°′″
ΑΒΓΔΕΖΗΘΙΚΛΜΝΞΟΠΡΣΤΥΦΧΨΩαβγδεζηθικλμνξοπρστυφχψω
イ彳匚亠斤廿个〒┴ΠΤυιθσρδбъЦ庁丁了凵∂三イ
一凹叶干久災咋昨皿三山士什十汁升小少上人心壬石川大只中丁刀凸乍二廿入八ワ
亡卜又毛夕了丶丿乂亅亠从仆儿兀冂冖冫几凵勹匕匚匸卅卞厂叮叭叨夂宀幵广廾弋彡彳鬥丨＇＂人

    _＿___＿
  ／ """"γ⌒＼
 //_____/___=ﾐ│
│;廿 |Τ|ﾞﾞﾞﾐ│
│;_＿|│|__ﾐﾐ│
└── ┴── ┘


  冂〒刀
  ＼∧ノ
   /=ﾐﾍ
  │⌒│
  │|ﾐ│
  │|ﾐ│
  │:ｿ│
   ﾍ⌒ﾉ
	∀

*/

//----------------------------------------------------
//プロトタイプ宣言
//----------------------------------------------------
void screenSize(int x, int y);
void createMap(OBJECT* pEntity, int color, int seed);
void inputKey(int* pMoveKey);
void inputMouse(int* pMoveMouse);
bool moveDalay(int moveKey, int oldMoveKey);
void randomMapCreate(int roomNumMax, int roomNumMin, int roomScaleMax, int roomScaleMin, int* pSeed);
void playerSet(int* playerX, int* playerY);
void mapTileRandomSet(int tileName, int tileNumMax, int tileNumMin);
void gameover(SCORE* pPlayerScore);
void uiSetWeapon(int x, int y, int num, int space);
void uiSetTreasure(int x, int y, int num, int space);
void uiSetFrame(void);
void savePlayerScore(SCORE* pPlayerScore);
void roadPlayerScore(void);
void mainGame(int seed);

//----------------------------------------------------
//メイン関数
//----------------------------------------------------
int main()
{
	int seed = 0;
	OBJECT tile[ENTITY_MAX];//最初の画面タイル実体

	//最初の画面タイル設定
	for (int i = 0; i < ENTITY_MAX; i++)
	{
		tile[i].number = i;
		if (tile[i].number == TILE_AIR)
		{
			strcpy(tile[i].visual, "　");
		}

		if (tile[i].number == TILE_PLAYER)
		{
			strcpy(tile[i].visual, "●");
		}

		if (tile[i].number == TILE_ENEMY)
		{
			strcpy(tile[i].visual, "Ｅ");
		}

		if (tile[i].number == TILE_ENEMY_DETECTION_RED)
		{
			strcpy(tile[i].visual, "Ｏ");
		}

		if (tile[i].number == TILE_ENEMY_DETECTION_YELLOW)
		{
			strcpy(tile[i].visual, "ｏ");
		}

		if (tile[i].number == TILE_TREASURE)
		{
			strcpy(tile[i].visual, "＄");
		}

		if (tile[i].number == TILE_WALL)
		{
			strcpy(tile[i].visual, "■");
		}
	}

	//最初の画面色
	int color = TILE_AIR;

	screenSize(100, 31);//画面サイズ(X, Y)

	while (true)
	{
		//シード値入力画面
		createMap(tile, color, 0);//全画面塗りつぶすために表示
		clrscr();
		createMap(tile, color, 0);//シード入力時のマップ画面表示
		uiSetFrame();//フレーム表示
		randomMapCreate(30, 5, 8, 2, &seed);//シード値を入力してマップを作成

		//ゲーム画面
		clrscr();
		mainGame(seed);
		roadPlayerScore();//ゲームオーバーになったときのスコア表示
	}
	
	//入力待ち
	rewind(stdin);//入力バッファを巻き戻す
	getchar();//Enterの入力待ち
}

//----------------------------------------------------
//画面サイズ変更
//----------------------------------------------------
void screenSize(int x, int y)
{
	//画面サイズ情報
	const COORD window_size = { x, y }; //画面サイズの定義
	SMALL_RECT console_screen_rect;   //コンソール画面のサイズ設定用
	console_screen_rect.Top = 0;
	console_screen_rect.Bottom = window_size.Y - 1;
	console_screen_rect.Left = 0;
	console_screen_rect.Right = window_size.X - 1;

	//バッファサイズの変更
	const HANDLE h_console_output = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleScreenBufferSize(h_console_output, window_size);

	//スクリーンサイズの変更
	CONSOLE_SCREEN_BUFFER_INFO console_screen_buffer_info;
	GetConsoleScreenBufferInfo(h_console_output, &console_screen_buffer_info);
	SetConsoleWindowInfo(h_console_output, TRUE, &console_screen_rect);
}

//----------------------------------------------------
//マップ作成 & 更新
//----------------------------------------------------
void createMap(OBJECT* pEntity, int color, int seed)
{
	srand(seed);
	int colorTheme = 0;

	if (seed != 0)
	{
		colorTheme = rand() % 10;
	}

	gotoxy(1, 1);

	for (int i = 0; i < MAP_HIGHT; i++)
	{
		for (int j = 0; j < MAP_WIDTH; j++)
		{
			if (colorTheme == 0)textattr(0xFF);
			else if (colorTheme == 1)textattr(0xCC);
			else if (colorTheme == 2)textattr(0xBB);
			else if (colorTheme == 3)textattr(0x66);
			else if (colorTheme == 4)textattr(0x00);
			else if (colorTheme == 5)textattr(0x44);
			else if (colorTheme == 6)textattr(0xFF);
			else if (colorTheme == 7)textattr(0x11);
			else if (colorTheme == 8)textattr(0xDD);
			else if (colorTheme == 9)textattr(0x0A);

			if (color == TILE_ENEMY) textattr(0x00);
			if (color == TILE_ENEMY_DETECTION_RED) textattr(0x00);
			if (color == TILE_ENEMY_DETECTION_YELLOW) textattr(0x88);

			if (map[i][j] == (pEntity + TILE_AIR)->number)//空
			{
				if (color == TILE_ENEMY) textattr(0x00);
				if (color == TILE_ENEMY_DETECTION_RED) textattr(0x00);
				if (color == TILE_ENEMY_DETECTION_YELLOW) textattr(0x88);
				
				printf("%s", (pEntity + TILE_AIR)->visual);
			}
			else if (map[i][j] == (pEntity + TILE_PLAYER)->number)//プレイヤー
			{
				textcolor(0xC);
				if (colorTheme == 1)textcolor(0x4);
				else if (colorTheme == 6)textcolor(0x0);
				else if (colorTheme == 8)textcolor(0xA);
				else if (colorTheme == 9)textcolor(0xA);

				if (color == TILE_ENEMY) textcolor(0x4);
				if (color == TILE_ENEMY_DETECTION_RED) textcolor(0xC);
				if (color == TILE_ENEMY_DETECTION_YELLOW) textcolor(0xC);

				printf("%s", (pEntity + TILE_PLAYER)->visual);
			}
			else if (map[i][j] == (pEntity + TILE_ENEMY)->number)//エネミー
			{
				if (colorTheme == 9)textcolor(0x0);
				if (color == TILE_ENEMY) textcolor(0xC);
				if (color == TILE_ENEMY_DETECTION_RED) textcolor(0x0);
				if (color == TILE_ENEMY_DETECTION_YELLOW) textcolor(0x8);

				printf("%s", (pEntity + TILE_ENEMY)->visual);
			}
			else if (map[i][j] == (pEntity + TILE_ENEMY_DETECTION_RED)->number)//エネミー感知(赤)
			{
				if (colorTheme == 9)textcolor(0x0);
				if (color == TILE_ENEMY) textcolor(0x0);
				if (color == TILE_ENEMY_DETECTION_RED) textcolor(0x0);
				if (color == TILE_ENEMY_DETECTION_YELLOW) textcolor(0x8);

				printf("%s", (pEntity + TILE_ENEMY_DETECTION_RED)->visual);
			}
			else if (map[i][j] == (pEntity + TILE_ENEMY_DETECTION_YELLOW)->number)//エネミー感知(黄)
			{
				if (colorTheme == 9)textcolor(0x0);
				if (color == TILE_ENEMY) textcolor(0x0);
				if (color == TILE_ENEMY_DETECTION_RED) textcolor(0x0);
				if (color == TILE_ENEMY_DETECTION_YELLOW) textcolor(0x8);

				printf("%s", (pEntity + TILE_ENEMY_DETECTION_YELLOW)->visual);
			}
			else if (map[i][j] == (pEntity + TILE_TREASURE)->number)//宝
			{
				textattr(0xE0);
				if (colorTheme == 6)textattr(0x0F);
				else if (colorTheme == 7)textattr(0x1F);
				else if (colorTheme == 8)textattr(0xAD);
				else if (colorTheme == 9)textattr(0xA0);

				if (color == TILE_ENEMY) textattr(0xF0);
				if (color == TILE_ENEMY_DETECTION_RED) textattr(0x40);
				if (color == TILE_ENEMY_DETECTION_YELLOW) textattr(0x67);
				
				printf("%s", (pEntity + TILE_TREASURE)->visual);
			}
			else if (map[i][j] == (pEntity + TILE_WALL)->number)//壁
			{
				textattr(0x87);
				if (colorTheme == 6)textattr(0x00);
				else if (colorTheme == 7)textattr(0xFC);
				else if (colorTheme == 8)textattr(0xAD);
				else if (colorTheme == 9)textattr(0xA0);

				if (color == TILE_ENEMY) textattr(0x0F);
				if (color == TILE_ENEMY_DETECTION_RED) textattr(0x04);
				if (color == TILE_ENEMY_DETECTION_YELLOW) textattr(0x86);

				printf("%s", (pEntity + TILE_WALL)->visual);
			}
		}
		printf("\n");
	}
}

//----------------------------------------------------
//キー入力確認
//----------------------------------------------------
void inputKey(int* pMoveKey)
{
	int moveY = inport(PK_W) - inport(PK_S);
	int moveX = inport(PK_A) - inport(PK_D);

	if (moveX == 1)
	{
		*pMoveKey = 3;
	}

	if (moveX == -1)
	{
		*pMoveKey = 4;
	}

	if (moveY == 1)
	{
		*pMoveKey = 1;
	}

	if (moveY == -1)
	{
		*pMoveKey = 2;
	}

	if (moveY == 0 && moveX == 0)
	{
		*pMoveKey = 0;//止
	}
}

//----------------------------------------------------
//移動のディレイ
//----------------------------------------------------
bool moveDalay(int moveKey, int oldMoveKey)
{
	int moveDalayCou = 0;
	bool result = false;

	if (oldMoveKey == moveKey && moveKey != 0)//同じ方向に連続で進んでいるかつ、止まっていない
	{
		while (true)
		{
			moveDalayCou++;
			oldMoveKey = moveKey;
			inputKey(&moveKey);//キー入力確認

			if (PLAYER_SPEED < moveDalayCou)
			{
				result = true;
				break;
			}
			if (oldMoveKey != moveKey || moveKey == 0)
			{
				break;
			}
		}
	}
	else
	{
		result = true;
	}

	return result;
}

//----------------------------------------------------
//ランダムにマップを生成
//----------------------------------------------------
void randomMapCreate(int roomNumMax, int roomNumMin, int roomScaleMax, int roomScaleMin, int* pSeed)
{
	char mapSeed[255];
	int seed = 0;
	int roomNum;
	int randomX[255] = { 0 };
	int randomY[255] = { 0 };
	int scaleSelect = 0;

	//マップを壁で埋め尽くす
	for (int i = 0; i < MAP_HIGHT; i++)
	{
		for (int j = 0; j < MAP_WIDTH; j++)
		{
			map[i][j] = TILE_WALL;
		}
	}

	gotoxy(71, 5);
	printf("マップを生成します");
	gotoxy(68, 7);
	printf("シード値を入れてください");
	gotoxy(70, 10);
	printf("￣￣￣￣￣￣￣￣￣￣");
	gotoxy(70, 9);
	setcursortype(SOLIDCURSOR);
	scanf("%s", &mapSeed);
	setcursortype(NOCURSOR);

	int len = strlen(mapSeed);

	//シード値計算
	for (int i = 0; i < len; i++)
	{
		if (i % 3 == 0)
		{
			if (i % 2 == 0)
			{
				seed += mapSeed[i];
			}
			else
			{
				seed += mapSeed[i] * 2;
			}
		}

		if (i % 3 == 1)
		{
			if (i % 2 == 1)
			{
				seed += mapSeed[i] * 3;
			}
			else
			{
				seed += mapSeed[i] * 4;
			}
		}

		if (i % 3 == 2)
		{
			if (i % 2 == 0)
			{
				seed += mapSeed[i] * 5;
			}
			else
			{
				seed += mapSeed[i] * 6;
			}
		}
	}
	
	srand(seed);
	*pSeed = seed;

	//部屋の生成
	roomNum = rand() % (roomNumMax - roomNumMin + 1) + roomNumMin;//部屋の数
	for (int i = 0; i < roomNum; i++)
	{
		randomX[i] = rand() % MAP_WIDTH;
		randomY[i] = rand() % MAP_HIGHT;

		for (int j = 0; j < rand() % (roomScaleMax - roomScaleMin + 1) + roomScaleMin; j++)//部屋の縦の長さ
		{
			for (int k = 0; k < rand() % (roomScaleMax - roomScaleMin + 1) + roomScaleMin; k++)//部屋の横の長さ
			{
				if ((randomY[i] + j >= 0) && (randomY[i] + j < MAP_HIGHT) && (randomX[i] + k >= 0) && (randomX[i] + k < MAP_WIDTH))//マップ外には生成しない
				{
					map[randomY[i] + j][randomX[i] + k] = TILE_AIR;
				}
			}
		}
	}

	//廊下の生成
	for (int i = 0; i < roomNum + 1; i++)//部屋数分ループ(最初の部屋と最後の部屋をつなげるため +1)
	{
		int targetRoom = i + 1;//つなげ先の部屋
		int randomXUpdate = 0;

		if (roomNum < targetRoom)//最初の部屋と最後の部屋をつなげる
		{
			targetRoom = 0;
		}
		
		if (randomX[i] < randomX[targetRoom])
		{
			for (int j = 0; j < abs(randomX[i] - randomX[targetRoom]); j++)
			{
				map[randomY[i]][randomX[i] + j + 1] = TILE_AIR;
				randomXUpdate = randomX[i] + j + 1;//最終x座標を代入
			}
		}
		else if (randomX[i] > randomX[targetRoom])
		{
			for (int j = 0; j < abs(randomX[i] - randomX[targetRoom]); j++)
			{
				map[randomY[i]][randomX[i] - j - 1] = TILE_AIR;
				randomXUpdate = randomX[i] - j - 1;//最終x座標を代入
			}
		}
		else
		{
			randomXUpdate = randomX[i];//最終x座標を代入
		}

		if (randomY[i] < randomY[targetRoom])
		{
			for (int j = 0; j < abs(randomY[i] - randomY[targetRoom]); j++)
			{
				if (j <= MAP_HIGHT)
				{
					map[randomY[i] + j + 1][randomXUpdate] = TILE_AIR;
				}
			}
		}
		else if (randomY[i] > randomY[targetRoom])
		{
			for (int j = 0; j < abs(randomY[i] - randomY[targetRoom]); j++)
			{
				map[randomY[i] - j- 1][randomXUpdate] = TILE_AIR;
			}
		}
	}
}

//----------------------------------------------------
//プレイヤーを配置
//----------------------------------------------------
void playerSet(int* playerX, int* playerY)
{
	bool playerCheck = false;
	int airCou = 0;
	int loopCou = 0;
	srand((unsigned int)time(0));//seed値のセット

	//空のタイル数を計算
	for (int i = 0; i < MAP_HIGHT; i++)
	{
		for (int j = 0; j < MAP_WIDTH; j++)
		{
			if (map[i][j] == TILE_AIR)
			{
				airCou++;
			}
		}
	}

	//プレイヤー配置
	for (int i = 0; i < MAP_HIGHT; i++)
	{
		for (int j = 0; j < MAP_WIDTH; j++)
		{
			if (playerCheck == false && map[i][j] == TILE_AIR)
			{
				if (rand() % (airCou - loopCou) == 0)//マップ内に必ずプレイヤーを配置する
				{
					*playerX = j;
					*playerY = i;
					map[*playerY][*playerX] = TILE_PLAYER;
					playerCheck = true;
				}
				else
				{
					loopCou++;
				}
			}
		}
	}
}

//----------------------------------------------------
//～のタイルを配置
//----------------------------------------------------
void mapTileRandomSet(int tileName, int tileNumMax, int tileNumMin)
{
	{
		bool treasureCheck = false;
		int airCou = 0;
		int loopCou = 0;
		srand((unsigned int)time(0));//seed値のセット

		//空のタイル数を計算
		for (int i = 0; i < MAP_HIGHT; i++)
		{
			for (int j = 0; j < MAP_WIDTH; j++)
			{
				if (map[i][j] == TILE_AIR)
				{
					airCou++;
				}
			}
		}

		//配置
		for (int k = 0; k < rand() % (tileNumMax - tileNumMin + 1) + tileNumMin; k++)
		{
			treasureCheck = false;
			loopCou = 0;
			for (int i = 0; i < MAP_HIGHT; i++)
			{
				for (int j = 0; j < MAP_WIDTH; j++)
				{
					if (treasureCheck == false && map[i][j] == TILE_AIR)
					{
						if (rand() % (airCou - loopCou) == 0)//マップ内に必ず配置する
						{
							map[i][j] = tileName;
							treasureCheck = true;
						}
						else
						{
							loopCou++;
						}
					}
				}
			}
		}
	}
}

//----------------------------------------------------
//ゲームオーバー(名前入力)
//----------------------------------------------------
void gameover(SCORE* pPlayerScore)
{
	char name[64];

	uiSetFrame();
	while (true)
	{
		setcursortype(SOLIDCURSOR);//ブロックカーソル
		strcpy(pPlayerScore->name, "-UNKNOWN-");

		textcolor(0xF);//白
		gotoxy(76, 5);
		printf("～ %d ～", pPlayerScore->score);

		gotoxy(70, 8);
		printf("名前を入れてください");

		gotoxy(74, 11);
		printf("￣￣￣￣￣￣");

		gotoxy(74, 10);
		scanf("%s", name);

		int len = strlen(name);

		if (len > 12)//12バイト以上は入力再入力
		{
			uiSetFrame();
			gotoxy(71, 9);
			textcolor(0x4);//赤
			printf("※名前が長すぎです");
		}
		else
		{
			strcpy(pPlayerScore->name, name);
			setcursortype(NOCURSOR);//カーソル非表示
			break;
		}
	}
}

//----------------------------------------------------
//爆撃UI表示
//----------------------------------------------------
void uiSetWeapon(int x, int y, int num, int space)
{
	int wideSpace = 0;
	for (int k = 0 ; k < num; k++, wideSpace += space)
	{
		for (int i = 0; i < 10; i++)
		{
			gotoxy(61 + x + wideSpace, 1 + y + i);
			for (int j = 0; j < 10; j++)
			{
				printf("%c", uiWeapon[i][j]);
			}
		}
	}
}

//----------------------------------------------------
//宝UI表示
//----------------------------------------------------
void uiSetTreasure(int x, int y, int num, int space)
{
	int wideSpace = 0;
	for (int k = 0; k < num; k++, wideSpace += space)
	{
		for (int i = 0; i < 6; i++)
		{
			gotoxy(61 + x + wideSpace, 1 + y + i);
			for (int j = 0; j < 30; j++)
			{
				printf("%c", uiTreasur[i][j]);
			}
		}
	}
}

//----------------------------------------------------
//UIフレーム表示
//----------------------------------------------------
void uiSetFrame(void)
{
	textattr(0x8F);
	for (int i = 0; i < 30; i++)
	{
		gotoxy(60 + 1, i + 1);
		for (int j = 0; j < 40; j++)
		{
			printf("%c", uiFrame[i][j]);
		}
	}
}

//----------------------------------------------------
//スコアのセーブ
//----------------------------------------------------
void savePlayerScore(SCORE* pPlayerScore)
{
	FILE* fp; //ファイルポインター

	//バイナリ書き込みモードでファイルオープン
	fp = fopen("score.sav", "ab");

	//書き込み
	fwrite(pPlayerScore, sizeof(SCORE), 1, fp);

	pPlayerScore = 0;

	//ファイルクローズ
	fclose(fp);
}

//----------------------------------------------------
//スコアの表示
//----------------------------------------------------
void roadPlayerScore(void)
{
	SCORE score[99];
	SCORE tmp;

	uiSetFrame();

	for (int i = 0; i < 99; i++)
	{
		score[i].score = 0;
		strcpy(score[i].name, "       ");
	}

	FILE* fp; //ファイルポインター

	//バイナリ書き込みモードでファイルオープン
	fp = fopen("score.sav", "rb");

	//読み込み
	if (fp != NULL)
	{
		fread(score, sizeof(SCORE), 99, fp);
	}

	//スコアをソート
	for (int i = 0; i < 99; i++)
	{
		for (int j = 0; j < 99 - i; j++)
		{
			if (score[i].score < score[i + j].score)
			{
				tmp = score[i];
				score[i] = score[i + j];
				score[i + j] = tmp;
			}
		}
	}
	
	gotoxy(68, 4);
	printf("─ ＧＡＭＥ　ＯＶＥＲ ─");
	gotoxy(82, 29);
	printf("R で Continue…");
	gotoxy(72, 7);
	printf("ＮＡＭＥ");
	gotoxy(87, 7);
	printf("ＳＣＯＲＥ");

	for (int i = 0; i < 20; i++)
	{
		gotoxy(63, 8 + i);
		printf("RANK %d", i + 1);

		gotoxy(72, 8 + i);
		printf("%s", score[i].name);

		if (999999 < score[i].score)
		{
			gotoxy(87, 8 + i);
			printf("999999+");
		}
		else
		{
			gotoxy(87, 8 + i);
			printf("%d", score[i].score);
		}
	}
	//ファイルクローズ
	fclose(fp);

	gotoxy(1, 31);

	reinport();
	while (inport(PK_R) == false);
}

//----------------------------------------------------
//ゲーム本編
//----------------------------------------------------
void mainGame(int seed)
{
	OBJECT_MOVE player;//プレイヤー座標実体
	//初期化
	player.x = 0;
	player.y = 0;
	player.oldX = 0;
	player.oldY = 0;

	OBJECT_MOVE enemy[64];//エネミー座標実体
	//初期化
	for (int i = 0; i < 64; i++)
	{
		enemy[i].x = 0;
		enemy[i].y = 0;
		enemy[i].oldX = 0;
		enemy[i].oldY = 0;
	}

	OBJECT_MOVE treasure[64];//宝座標実体
	//初期化
	for (int i = 0; i < 64; i++)
	{
		treasure[i].x = 0;
		treasure[i].y = 0;
		treasure[i].oldX = 0;
		treasure[i].oldY = 0;
	}

	uiSetFrame();
	
	textcolor(0xF);
	gotoxy(67, 3);
	textcolor(0xC);
	printf("●");
	textcolor(0xF);
	printf(" を ＷＡＳＤ で移動して");

	gotoxy(67, 5);
	textattr(0xE0);
	printf("＄");
	textattr(0x8F);
	printf(" をたくさん集めましょう");

	gotoxy(67, 7);
	printf("見えない 敵 には要注意");

	gotoxy(67, 8);
	printf("色が変わったときはキケン!");

	gotoxy(67, 9);
	printf("近くにいるかも...");

	playerSet(&player.x, &player.y);

	mapTileRandomSet(TILE_TREASURE, 5, 3);
	mapTileRandomSet(TILE_ENEMY, 3, 3);

	OBJECT tile[ENTITY_MAX];//タイル実体

	//タイル設定
	for (int i = 0; i < ENTITY_MAX; i++)
	{
		tile[i].number = i;
		if (tile[i].number == TILE_AIR)
		{
			strcpy(tile[i].visual, "　");
		}

		if (tile[i].number == TILE_PLAYER)
		{
			strcpy(tile[i].visual, "●");
		}

		if (tile[i].number == TILE_ENEMY)
		{
			strcpy(tile[i].visual, "Ｅ");
		}

		if (tile[i].number == TILE_ENEMY_DETECTION_RED)
		{
			strcpy(tile[i].visual, "Ｏ");
		}

		if (tile[i].number == TILE_ENEMY_DETECTION_YELLOW)
		{
			strcpy(tile[i].visual, "ｏ");
		}

		if (tile[i].number == TILE_TREASURE)
		{
			strcpy(tile[i].visual, "＄");
		}

		if (tile[i].number == TILE_WALL)
		{
			strcpy(tile[i].visual, "■");
		}
	}

	//色
	int color = TILE_AIR;
	//キーボード関係
	int moveKey = 0;
	int oldMoveKey = 0;
	//マウスカーソル関係
	int x, y;
	int oldX, oldY;
	int mouseLeft, oldMouseLeft;
	int cou = 0;
	bool response = true;
	x = y = 0;
	oldX = oldY = 0;
	mouseLeft = 0;
	oldMouseLeft = 0;
	//宝の所持数
	SCORE playerScore;
	playerScore.score = 0;
	int oldScore = playerScore.score;
	strcpy(playerScore.name, "UNKNOWN");

	setcursortype(NOCURSOR);//カーソルを消す

	createMap(tile, color, seed);//初回マップ表示

	reinport();

	while (true)
	{
		player.oldX = player.x;
		player.oldY = player.y;
		oldMoveKey = moveKey;

		inputKey(&moveKey);//キー入力確認

		//プレイヤー移動
		if (moveDalay(moveKey, oldMoveKey) == true)//移動のディレイ
		{
			switch (moveKey)
			{
			case 1:
				player.y--;
				break;
			case 2:
				player.y++;
				break;
			case 3:
				player.x--;
				break;
			case 4:
				player.x++;
				break;
			}

			//マップ外と壁に行けないようにする
			if ((player.y) > (MAP_HIGHT - 1) || (player.x) > (MAP_WIDTH - 1) ||
				(player.y) < 0 || (player.x) < 0 ||
				map[player.y][player.x] == TILE_WALL)//移動先が壁
			{
				player.x = player.oldX;
				player.y = player.oldY;
			}

		}

		//マップのエネミーの場所をenemy.x, yに入れる
		int enmeyCou = 0;

		for (int i = 0; i < MAP_HIGHT; i++)
		{
			for (int j = 0; j < MAP_WIDTH; j++)
			{
				if (map[i][j] == TILE_ENEMY)
				{
					enemy[enmeyCou].x = j;
					enemy[enmeyCou].y = i;
					enmeyCou++;
				}
			}
		}

		//マップの宝の場所をtreasure.x, yに入れる
		int treasureCou = 0;

		for (int i = 0; i < MAP_HIGHT; i++)
		{
			for (int j = 0; j < MAP_WIDTH; j++)
			{
				if (map[i][j] == TILE_TREASURE)
				{
					treasure[treasureCou].x = j;
					treasure[treasureCou].y = i;
					treasureCou++;
				}
			}
		}

		if (player.oldX != player.x || player.oldY != player.y)//プレイヤーが移動した場合
		{
			map[player.oldY][player.oldX] = TILE_AIR;//前のプレイヤーを空白に上書き

			//前のエネミー感知削除
			for (int i = 0; i < MAP_HIGHT; i++)
			{
				for (int j = 0; j < MAP_WIDTH; j++)
				{
					if (map[i][j] == TILE_ENEMY_DETECTION_RED || map[i][j] == TILE_ENEMY_DETECTION_YELLOW)
					{
						map[i][j] = TILE_AIR;
					}
				}
			}

			//エネミー移動
			srand((unsigned int)time(0));//seed値のセット
			int randomMove;

			for (int i = 0; i < enmeyCou; i++)
			{
				randomMove = rand() % 10;

				enemy[i].oldX = enemy[i].x;
				enemy[i].oldY = enemy[i].y;

				if (randomMove == 1)
				{
					enemy[i].y--;
				}
				else if (randomMove == 2)
				{
					enemy[i].y++;
				}
				else if (randomMove == 3)
				{
					enemy[i].x--;
				}
				else if (randomMove == 4)
				{
					enemy[i].x++;
				}
				else
				{
				}

				//マップ外と壁に行けないようにする
				if ((enemy[i].y) > (MAP_HIGHT - 1) || (enemy[i].x) > (MAP_WIDTH - 1) ||
					(enemy[i].y) < 0 || (enemy[i].x) < 0 ||
					map[enemy[i].y][enemy[i].x] == TILE_WALL ||//移動先が壁
					map[enemy[i].y][enemy[i].x] == TILE_ENEMY ||//配置先がエネミー
					map[enemy[i].y][enemy[i].x] == TILE_TREASURE ||//配置先が宝
					map[enemy[i].y][enemy[i].x] == TILE_PLAYER)//配置先がプレイヤー
				{
					enemy[i].x = enemy[i].oldX;
					enemy[i].y = enemy[i].oldY;
				}
				map[enemy[i].oldY][enemy[i].oldX] = TILE_AIR;//前のエネミーを空白に上書き
				map[enemy[i].y][enemy[i].x] = TILE_ENEMY;//エネミー配置
				//エネミー感知を配置

				//エネミー感知配置(黄)
				for (int k = 0; k < 7; k++)
				{
					for (int l = 0; l < 7; l++)
					{
						if (!((l == 0 && k == 0) || (l == 1 && k == 0) || (l == 0 && k == 1) ||
							(l == 5 && k == 0) || (l == 6 && k == 0) || (l == 6 && k == 1) ||
							(l == 0 && k == 5) || (l == 0 && k == 6) || (l == 1 && k == 6) ||
							(l == 6 && k == 5) || (l == 5 && k == 6) || (l == 6 && k == 6)))
						{
							//マップ外又は壁でなければ配置
							if (!((enemy[i].y - 3 + k) > (MAP_HIGHT - 1) || (enemy[i].x - 3 + l) > (MAP_WIDTH - 1) ||
								(enemy[i].y - 3 + k) < 0 || (enemy[i].x - 3 + l) < 0 ||
								map[enemy[i].y - 3 + k][enemy[i].x - 3 + l] == TILE_WALL ||//配置先が壁
								map[enemy[i].y - 3 + k][enemy[i].x - 3 + l] == TILE_ENEMY))//配置先がエネミー
							{
								map[enemy[i].y - 3 + k][enemy[i].x - 3 + l] = TILE_ENEMY_DETECTION_YELLOW;
							}
						}
					}
				}

				//エネミー感知配置(赤)
				for (int k = 0; k < 3; k++)
				{
					for (int l = 0; l < 3; l++)
					{
						//マップ外又は壁でなければ配置
						if (!((enemy[i].y - 1 + k) > (MAP_HIGHT - 1) || (enemy[i].x - 1 + l) > (MAP_WIDTH - 1) ||
							(enemy[i].y - 1 + k) < 0 || (enemy[i].x - 1 + l) < 0 ||
							map[enemy[i].y - 1 + k][enemy[i].x - 1 + l] == TILE_WALL ||//配置先が壁
							map[enemy[i].y - 1 + k][enemy[i].x - 1 + l] == TILE_ENEMY))//配置先がエネミー
						{
							map[enemy[i].y - 1 + k][enemy[i].x - 1 + l] = TILE_ENEMY_DETECTION_RED;
						}
					}
				}
			}

			//宝を配置
			for (int i = 0; i < treasureCou; i++)
			{
				map[treasure[i].y][treasure[i].x] = TILE_TREASURE;
			}

			//タイルが重なった時の処理
			if (map[player.y][player.x] == TILE_AIR)
			{
				color = TILE_AIR;
			}
			else if (map[player.y][player.x] == TILE_ENEMY)
			{
				color = TILE_ENEMY;
				createMap(tile, color, seed);
				gameover(&playerScore);
				savePlayerScore(&playerScore);
				break;
			}
			else if (map[player.y][player.x] == TILE_ENEMY_DETECTION_YELLOW)
			{
				color = TILE_ENEMY_DETECTION_YELLOW;
			}
			else if (map[player.y][player.x] == TILE_ENEMY_DETECTION_RED)
			{
				color = TILE_ENEMY_DETECTION_RED;
			}
			else if (map[player.y][player.x] == TILE_TREASURE)
			{
				color = TILE_AIR;
				playerScore.score++;

				if (playerScore.score % 2 == 0)
				{
					mapTileRandomSet(TILE_TREASURE, 4, 2);
				}

				if (playerScore.score % 5 == 0)
				{
					mapTileRandomSet(TILE_ENEMY, 1, 1);
				}

				if (playerScore.score % 10 == 0)
				{
					mapTileRandomSet(TILE_ENEMY, 1, 0);
				}
			}

			map[player.y][player.x] = TILE_PLAYER;//プレイヤー配置

			createMap(tile, color, seed);//マップ更新

			if (playerScore.score != 0)
			{
				if (oldScore < playerScore.score)
				{
					//UI宝箱色変更
					textattr(0x88);
					int per = 5;
					if (playerScore.score <= per * 1)textcolor(0x0);
					else if (playerScore.score <= per * 2)textcolor(0x7);
					else if (playerScore.score <= per * 3)textcolor(0xF);
					else if (playerScore.score <= per * 4)textcolor(0x2);
					else if (playerScore.score <= per * 5)textcolor(0xA);
					else if (playerScore.score <= per * 6)textcolor(0x3);
					else if (playerScore.score <= per * 7)textcolor(0x9);
					else if (playerScore.score <= per * 8)textcolor(0x5);
					else if (playerScore.score <= per * 9)textcolor(0xD);
					else if (playerScore.score <= per * 10)textcolor(0x1);
					else if (playerScore.score <= per * 11)textcolor(0x9);
					else if (playerScore.score <= per * 12)textcolor(0x4);
					else if (playerScore.score <= per * 13)textcolor(0xC);
					else if (playerScore.score <= per * 14)textcolor(0x6);
					else if (playerScore.score <= per * 15)textcolor(0xE);
					
					//UI宝箱表示
					if (playerScore.score % per == 1)uiSetTreasure(4, 23, 1, 0);
					else if (playerScore.score % per == 2)uiSetTreasure(19, 23, 1, 0);
					else if (playerScore.score % per == 3)uiSetTreasure(4, 17, 1, 0);
					else if (playerScore.score % per == 4)uiSetTreasure(19, 17, 1, 0);
					else if (playerScore.score % per == 0)uiSetTreasure(12, 11, 1, 0);
				}
			}
		}
	}
}