#include "DxLib.h"

#define BACKGROUNDSIXZE_X 1920			//画像の横幅
#define BACKGROUNDSIXZE_Y 1080			//画像の縦幅
#define SCREENSIZE_X 1920				//スクリーンの横幅
#define SCREENSIZE_Y 1080				//スクリーンの縦幅
#define SCROLLSPEED 2					//スクロールスピード
#define ANIMATION_COUNT 20

//汎用変数
//int grv = 1;//重力定義
int timer;						//アニメーションのためにタイマーを呼ぶ
int frame;						//アニメーションのフレーム数
int frame2;						//アニメーションフレーム数（こうもり）

 //自機の変数
int clear;
int player[4];					//自機　コウモリ
int dash;						//移動音
int normal;						//自機通常
int yarare[4];					//自機被弾
int kyarare[4];
int yarare2;					//自機被弾
int yarares;					//被弾音
int px = 0, py = 444;			//自機初期位置
int lpx = -10, rpx = 8, apy = -10, upy = 10;//自機スピード
bool ani = false;				//アニメーション管理
int hitpoint = 5;				//自機ヒットポイン
bool ef = true;					//当たり管理フラグ
bool ebf = true;				//敵弾当たり管理フラグ
//敵機の変数
int enemy[11];//敵機
int enormal;//敵機通常
int ex = 480, ey = 10;//敵機初期位置 
int shot;//弾
int eshot;//敵弾
int eshot2;//敵弾（爆発）
int esx = 8, esy = 12;//敵機スピード
int explosion;//爆発音
 //背景の変数
 //背景ブロック
int bg[2];
int haikei;
int haikeix = 0, haikeiy = 0;
int muteki = 1;
int stage;
int goal;
int goalx = 5120, goaly = 0;

int bgxs = 5;//背景移動速度
int bgys = 5;//背景移動速度
int bg1x = -(BACKGROUNDSIXZE_X - SCREENSIZE_X) / 2, bg1y = -(BACKGROUNDSIXZE_Y - SCREENSIZE_Y) / 2;
int bg2x = BACKGROUNDSIXZE_X - (BACKGROUNDSIXZE_X - SCREENSIZE_X) / 2, bg2y = -(BACKGROUNDSIXZE_Y - SCREENSIZE_Y) / 2;
int scr; // スクロール 
int animation_count = ANIMATION_COUNT;
int button;
int button1;
int button2;
bool flag_button = true;
int start;//開始
int title;//タイトル曲
int setumei;
int battle;//戦闘曲
int win;//勝利
int wins;//勝利曲
int loose;//敗北
int looses;//敗北曲
int overTime;
int overFlag;
bool yFlag = false;
bool nFlag = false;
bool nomaFlag = false;
int zahyou = 0;
int status;//ゲームの状態
enum { TITLE, SETUMEI, PLAY, OVER, CLEAR };//ゲーム状態管理

bool buttonstate = false;

int atiti;
int HPbar[6];

const int mapXMax = 40;
const int mapYMax = 9;

int selectImg[3];
int noselectImg[3];

int map[][mapYMax][mapXMax] =
{

	{
		{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
		{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
		{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1 },
		{ 0,0,0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0 },
		{ 1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,1,1,1,1 },
		{ 1,1,1,1,1,1,1,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,1,1,1,1,1 },
		{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
		{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
	},

	{
		{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
		{ 1,1,1,1,1,1,1,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,1,1,1,1 },
		{ 1,1,1,1,1,1,0,0,0,1,1,1,0,0,0,1,1,1,1,0,0,0,1,1,0,0,0,1,1,1,0,0,0,0,0,0,1,1,1,1 },
		{ 0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,1,1,1,1,0,1,1,1,1 },
		{ 0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0 },
		{ 1,1,1,1,1,1,0,0,0,1,1,1,0,0,0,1,1,1,1,0,0,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,0,0,0,0 },
		{ 1,1,1,1,1,1,1,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,0 },
		{ 1,1,1,1,1,1,1,1,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
		{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
	},

	{
		{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
		{ 1,1,1,1,1,1,1,0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,1,1 },
		{ 1,1,1,1,1,1,0,0,1,0,0,1,0,0,0,1,1,1,0,0,1,0,0,1,1,1,0,0,0,1,1,1,1,1,1,1,0,0,1,1 },
		{ 0,0,0,0,0,0,0,1,1,0,0,1,1,1,1,1,1,0,0,1,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,1 },
		{ 0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,1,0,1,0,1,0,0,0,0,0,1,0,0,1,1,1,1,1,1,1,1,1 },
		{ 1,1,1,1,1,1,0,0,1,0,0,1,1,1,1,1,1,0,0,1,0,1,0,0,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1 },
		{ 1,1,1,1,1,1,1,0,0,0,0,0,1,0,0,0,1,1,0,0,1,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0 },
		{ 1,1,1,1,1,1,1,1,1,1,1,0,0,0,1,0,0,1,1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
		{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
	},
};

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR lpCmdLine, int nCmdShow) 
{
	ChangeWindowMode(TRUE);//ウィンドウモード有効化
	SetMainWindowText("コウモリダンジョン");// ウィンドウタイトル
	DxLib_Init();//ライブラリ初期化
	SetDrawScreen(DX_SCREEN_BACK);//プリロード開始
	SetGraphMode(1920, 1080, 32);//画面サイズの変更
	LoadDivGraph("img/bat.png", 4, 4, 1, 128, 128, player);//自機プリロード
	LoadDivGraph("img/enemyfire.png", 11, 4, 3, 300, 300, enemy);
	LoadDivGraph("img/bg.png", 2, 2, 1, 128, 128, bg);
	LoadDivGraph("img/yarare.png", 4, 4, 1, 128, 128, yarare);
	LoadDivGraph("img/kyarare.png", 4, 4, 1, 128, 128, kyarare);

	//-----------------------------------------------ヒットポイント------------------------------------------------//
	HPbar[0] = LoadGraph("img/0.png");
	HPbar[1] = LoadGraph("img/1.png");
	HPbar[2] = LoadGraph("img/2.png");
	HPbar[3] = LoadGraph("img/3.png");
	HPbar[4] = LoadGraph("img/4.png");
	HPbar[5] = LoadGraph("img/5.png");

	haikei = LoadGraph("img/doukutu.png");
	noselectImg[0] = LoadGraph("img/easy1.png");
	noselectImg[1] = LoadGraph("img/normal1.png");
	noselectImg[2] = LoadGraph("img/hard1.png");
	selectImg[0] = LoadGraph("img/easy.png");
	selectImg[1] = LoadGraph("img/normal.png");
	selectImg[2] = LoadGraph("img/hard.png");
	enormal = LoadGraph("img/enemy.png");//敵機プリロード
	explosion = LoadSoundMem("sound/explosion.mp3");//爆発音プリロード
	button1 = LoadGraph("img/Button2.png");
	button2 = LoadGraph("img/Button1.png");
	clear = LoadGraph("img/clear.png");
	goal = LoadGraph("img/goal.png");
	start = LoadGraph("img/ホラー背景2.png");//開始プリロード
	title = LoadSoundMem("sound/title.mp3");//タイトル曲プリロード
	setumei = LoadGraph("img/setumei.png");
	atiti = LoadSoundMem("sound/atiti.mp3");//熱い効果音んんんんんんんんんんんんんんんんんんんんんんんんんｎ
	battle = LoadSoundMem("sound/battle.mp3");//戦闘曲プリロード
	win = LoadGraph("img/win.png");//勝利画面プリロード
	wins = LoadSoundMem("sound/wins.mp3");//勝利曲プリロード
	loose = LoadGraph("img/loose.png");//敗北画面プリロード
	looses = LoadSoundMem("sound/looses.mp3");//敗北曲プリロード

	while (1) 
	{

		//タイトル画面
		StopSoundMem(wins);//勝利BGMを止める
		StopSoundMem(looses);//敗北BGMを止める
		PlaySoundMem(title, DX_PLAYTYPE_BACK);// BGMを再生する
		while (!ProcessMessage() && status == TITLE) 
		{
			ClearDrawScreen();//描画初期化
			DrawGraph(0, 0, start, FALSE);//背景表示
			SetFontSize(24);//フォントサイズ指定

			for (int i = 0; i < 3; i++)
			{
				if (stage == i)
				{
					DrawGraph(1250, 300 + i * 200, selectImg[i], TRUE);
				}
				else
				{
					DrawGraph(1250, 300 + i * 200, noselectImg[i], TRUE);
				}
				if (CheckHitKey(KEY_INPUT_DOWN) == 1 && buttonstate == false)
				{
					stage++;
					if (stage >= 3)
					{
						stage = 0;
					}
					//WaitTimer(200);
					buttonstate = true;
				}

				if (CheckHitKey(KEY_INPUT_UP) == 1 && buttonstate == false)
				{
					stage--;
					if (stage < 0)
					{
						stage = 2;
					}
					//WaitTimer(200);
					buttonstate = true;
				}
			}
			if (buttonstate == true && !CheckHitKey(KEY_INPUT_UP) && !CheckHitKey(KEY_INPUT_DOWN))
			{
				buttonstate = false;
			}

			animation_count--;
			if (animation_count <= 1)
			{
				animation_count = ANIMATION_COUNT;
				if (flag_button == true)
				{
					button = button2;
					flag_button = false;
				}
				else
				{
					button = button1;
					flag_button = true;
				}

			}
			DrawGraph(160, 870, button, TRUE);//背景表示
			if (CheckHitKey(KEY_INPUT_RETURN))
			{
				status = SETUMEI;//リターンキーで開始

								 //ゲーム初期化関連
				scr = 0; //スクロール初期化
				overTime = -1;
				overFlag = false;
				yFlag = false;
			}
			ScreenFlip();//画面更新処理
		}

		///////////////////////////////////////////////
		//説明//
		///////////////////////////////////////////////

		while (!ProcessMessage() && status == SETUMEI) {
			ClearDrawScreen();//描画初期化
			DrawGraph(0, 0, setumei, FALSE);//背景表示

			if (CheckHitKey(KEY_INPUT_SPACE))
			{
				status = PLAY;
			}

			ScreenFlip();//画面更新処理
		}


		//ゲームメイン
		StopSoundMem(title);
		PlaySoundMem(battle, DX_PLAYTYPE_BACK);// BGMを再生する

		while (!ProcessMessage() && status == PLAY)
		{
			overTime--;

			//描画初期化
			ClearDrawScreen();

			DrawGraph(haikeix, haikeiy, haikei, FALSE);//背景表示






			if (overTime < 0 && overFlag == FALSE)
			{
				scr -= SCROLLSPEED;


				//自機移動処理

				nFlag = true;



				//自機左移動定義
				if (CheckHitKey(KEY_INPUT_LEFT)) {
					px += lpx;
				}
				//自機右移動定義
				if (CheckHitKey(KEY_INPUT_RIGHT)) {
					px += rpx;
				}
				//自機上移動定義
				if (CheckHitKey(KEY_INPUT_UP)) {
					py += apy;
				}
				//自機下移動定義
				if (CheckHitKey(KEY_INPUT_DOWN)) {
					py += upy;
				}
				//自機スクロール処理
				px = px + SCROLLSPEED;
				if (px <= 0)
				{
					px = 0;
					if (CheckHitKey(KEY_INPUT_D))
					{
						px += rpx;
					}

				}

				if (px + scr <= 0) lpx = 0; else lpx = -8;//左に当たったら停止
				if (px + scr >= 1800) rpx = 0; else rpx = 10;//右に当たったら停止
				if (py + apy <= 0) apy = 0; else apy = -10;//上に当たったら停止
				if (py + upy >= 990) upy = 0; else upy = 10;//下に当たったら停止




															//敵機自動移動処理
				ex -= esx;//敵機横移動定義
				ey += esy;//敵機縦移動定義
						  //左に当たったら反転
				if (ex <= -150)
				{
					esx = -esx;
					esy = 34;
					esy = -esy;
				}
				//右に当たったら反転
				if (ex >= 1600)
				{
					esx = -esx;
					esy = 35;
					esy = -esy;
				}
				//上に当たったら反転
				if (ey <= -100)
				{
					esy = -24;
					esy = -esy;
				}
				//下に当たったら反転
				if (ey >= 830)
				{
					esy = 37;
					esy = -esy;
				}

				//自機とマップの当たり判定
				if (overFlag == FALSE)
				{
					int ix, iy;//ひだりうえ
					ix = (px + 50) / 128;
					iy = (py + 50) / 128;
					if (map[stage][iy][ix] != 0)
					{
						overFlag = TRUE;
						overTime = 120;
					}
					//みぎうえ
					ix = (px + 95) / 128;
					iy = (py + 50) / 128;
					if (map[stage][iy][ix] != 0)
					{
						overFlag = TRUE;
						overTime = 120;
					}
					//みぎしたした
					ix = (px + 95) / 128;
					iy = (py + 100) / 128;
					if (map[stage][iy][ix] != 0)
					{
						overFlag = TRUE;
						overTime = 120;
					}
					//ひだりした
					ix = (px + 50) / 128;
					iy = (py + 100) / 128;
					if (map[stage][iy][ix] != 0)
					{
						overFlag = TRUE;
						overTime = 120;
					}
				}


				//ゲームクリア条件
				if (px >= 5000)
				{
					status = CLEAR;
				}
				//敵機と自機の当たり判定
				if (ef)
				{
					if ((px + scr) + 20 > ex + 100 && (px + scr) + 120 < ex + 300 && py + 120 > ey + 100 && py + 20 < ey + 300)
					{
						hitpoint -= 1;//ヒットポイント減算
						ef = false;//当たり無効
						muteki = 0;


						nFlag = false;
						nomaFlag = false;
						yFlag = true;

						if (yFlag = true)
						{
							PlaySoundMem(atiti, DX_PLAYTYPE_BACK);
						}

						player[4] = yarare[4];
						if (hitpoint <= 0)
						{
							overFlag = true;//ゲームオーバー条件
							overTime = 120;
						}
					}
					else
					{
						nomaFlag = true;
						nFlag = true;
						yFlag = false;
					}

				}
				if (ef == false)
				{
					++muteki;
					if (muteki > 100)
					{
						ef = true;
						//nomaFlag = true, yFlag = false;
					}
				}

			}

			////////////////////////////////////////////////////////////////////////////////

			if (overFlag == TRUE && overTime > 0)
			{
				//落ちるプログラム
				nFlag = false;
				py += 5;
			}

			////////////////////////////////////////////////////////////////////////////////

			if (overFlag == TRUE && overTime < 0)
			{
				status = OVER;
			}
			//描画処理

			//背景描画

			DrawGraph(goalx + scr, goaly, goal, FALSE);



			for (int iy = 0; iy < mapYMax; iy++)
			{
				for (int ix = 0; ix < mapXMax; ix++)
				{
					int type = map[stage][iy][ix];
					if (type != 0)
					{
						DrawGraph(ix * 128 + scr, iy * 128, bg[type], FALSE);
					}
				}
			}

			//DrawGraph(px + scr, py, yarare, TRUE);

			timer = GetNowCount();//タイマーで現在時刻を取得
			frame = timer / 50 % 11;
			frame2 = timer / 70 % 4;
			if (nFlag == true)
			{
				DrawGraph(px + scr, py, player[frame2], TRUE);
			}
			if (yFlag == true)
			{
				DrawGraph(px + scr, py, yarare[frame2], TRUE);
			}
			if (overFlag == TRUE)
			{
				frame2 = timer / 90 % 4;
				DrawGraph(px + scr, py, kyarare[frame2], TRUE);
			}

			DrawGraph(ex, ey, enemy[frame], TRUE);

			//HPbar表示///////////////

			DrawGraph(50, 20, HPbar[hitpoint], TRUE);
			ScreenFlip();//画面更新処理


		}

		if (ProcessMessage() < 0)
		{
			break;
		}

		//ゲームオーバー画面
		StopSoundMem(battle);//ゲームBGMを止める
		PlaySoundMem(looses, DX_PLAYTYPE_BACK);// BGMを再生する
		while (!ProcessMessage() && status == OVER) 
		{
			ClearDrawScreen();//描画初期化
			DrawGraph(0, 0, loose, FALSE);
			if (CheckHitKey(KEY_INPUT_SPACE)) status = TITLE;//リターンキーでタイトル
			hitpoint = 5;
			px = 0, py = 444;
			ex = 480, ey = 10;

			ScreenFlip();//画面更新処理


		}

		//WaitTimer(300);//開始遅延処理

		//ゲームクリア画面
		StopSoundMem(battle);//ゲームBGMを止める
		PlaySoundMem(wins, DX_PLAYTYPE_BACK);// BGMを再生する
		while (!ProcessMessage() && status == CLEAR) 
		{
			ClearDrawScreen();//描画初期化
			DrawGraph(0, 0, win, FALSE);
			hitpoint = 5;
			zahyou = 0, 0;
			px = 0, py = 444;
			ex = 480, ey = 10;

			if (CheckHitKey(KEY_INPUT_SPACE)) status = TITLE;//リターンキーでタイトル
			ScreenFlip();//画面更新処理
		}

		//WaitTimer(1000);//開始遅延処理

		if (ProcessMessage() != 0)
		{
			break;
		}

		if (CheckHitKey(KEY_INPUT_ESCAPE))
		{
			break;
		}

		//ループから抜ける

	}
	DxLib_End();//ゲーム終了処理

	return 0;

}
