#include "DxLib.h"

#define BACKGROUNDSIXZE_X 1920			//�摜�̉���
#define BACKGROUNDSIXZE_Y 1080			//�摜�̏c��
#define SCREENSIZE_X 1920				//�X�N���[���̉���
#define SCREENSIZE_Y 1080				//�X�N���[���̏c��
#define SCROLLSPEED 2					//�X�N���[���X�s�[�h
#define ANIMATION_COUNT 20

//�ėp�ϐ�
//int grv = 1;//�d�͒�`
int timer;						//�A�j���[�V�����̂��߂Ƀ^�C�}�[���Ă�
int frame;						//�A�j���[�V�����̃t���[����
int frame2;						//�A�j���[�V�����t���[�����i��������j

 //���@�̕ϐ�
int clear;
int player[4];					//���@�@�R�E����
int dash;						//�ړ���
int normal;						//���@�ʏ�
int yarare[4];					//���@��e
int kyarare[4];
int yarare2;					//���@��e
int yarares;					//��e��
int px = 0, py = 444;			//���@�����ʒu
int lpx = -10, rpx = 8, apy = -10, upy = 10;//���@�X�s�[�h
bool ani = false;				//�A�j���[�V�����Ǘ�
int hitpoint = 5;				//���@�q�b�g�|�C��
bool ef = true;					//������Ǘ��t���O
bool ebf = true;				//�G�e������Ǘ��t���O
//�G�@�̕ϐ�
int enemy[11];//�G�@
int enormal;//�G�@�ʏ�
int ex = 480, ey = 10;//�G�@�����ʒu 
int shot;//�e
int eshot;//�G�e
int eshot2;//�G�e�i�����j
int esx = 8, esy = 12;//�G�@�X�s�[�h
int explosion;//������
 //�w�i�̕ϐ�
 //�w�i�u���b�N
int bg[2];
int haikei;
int haikeix = 0, haikeiy = 0;
int muteki = 1;
int stage;
int goal;
int goalx = 5120, goaly = 0;

int bgxs = 5;//�w�i�ړ����x
int bgys = 5;//�w�i�ړ����x
int bg1x = -(BACKGROUNDSIXZE_X - SCREENSIZE_X) / 2, bg1y = -(BACKGROUNDSIXZE_Y - SCREENSIZE_Y) / 2;
int bg2x = BACKGROUNDSIXZE_X - (BACKGROUNDSIXZE_X - SCREENSIZE_X) / 2, bg2y = -(BACKGROUNDSIXZE_Y - SCREENSIZE_Y) / 2;
int scr; // �X�N���[�� 
int animation_count = ANIMATION_COUNT;
int button;
int button1;
int button2;
bool flag_button = true;
int start;//�J�n
int title;//�^�C�g����
int setumei;
int battle;//�퓬��
int win;//����
int wins;//������
int loose;//�s�k
int looses;//�s�k��
int overTime;
int overFlag;
bool yFlag = false;
bool nFlag = false;
bool nomaFlag = false;
int zahyou = 0;
int status;//�Q�[���̏��
enum { TITLE, SETUMEI, PLAY, OVER, CLEAR };//�Q�[����ԊǗ�

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
	ChangeWindowMode(TRUE);//�E�B���h�E���[�h�L����
	SetMainWindowText("�R�E�����_���W����");// �E�B���h�E�^�C�g��
	DxLib_Init();//���C�u����������
	SetDrawScreen(DX_SCREEN_BACK);//�v�����[�h�J�n
	SetGraphMode(1920, 1080, 32);//��ʃT�C�Y�̕ύX
	LoadDivGraph("img/bat.png", 4, 4, 1, 128, 128, player);//���@�v�����[�h
	LoadDivGraph("img/enemyfire.png", 11, 4, 3, 300, 300, enemy);
	LoadDivGraph("img/bg.png", 2, 2, 1, 128, 128, bg);
	LoadDivGraph("img/yarare.png", 4, 4, 1, 128, 128, yarare);
	LoadDivGraph("img/kyarare.png", 4, 4, 1, 128, 128, kyarare);

	//-----------------------------------------------�q�b�g�|�C���g------------------------------------------------//
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
	enormal = LoadGraph("img/enemy.png");//�G�@�v�����[�h
	explosion = LoadSoundMem("sound/explosion.mp3");//�������v�����[�h
	button1 = LoadGraph("img/Button2.png");
	button2 = LoadGraph("img/Button1.png");
	clear = LoadGraph("img/clear.png");
	goal = LoadGraph("img/goal.png");
	start = LoadGraph("img/�z���[�w�i2.png");//�J�n�v�����[�h
	title = LoadSoundMem("sound/title.mp3");//�^�C�g���ȃv�����[�h
	setumei = LoadGraph("img/setumei.png");
	atiti = LoadSoundMem("sound/atiti.mp3");//�M�����ʉ���������������������������
	battle = LoadSoundMem("sound/battle.mp3");//�퓬�ȃv�����[�h
	win = LoadGraph("img/win.png");//������ʃv�����[�h
	wins = LoadSoundMem("sound/wins.mp3");//�����ȃv�����[�h
	loose = LoadGraph("img/loose.png");//�s�k��ʃv�����[�h
	looses = LoadSoundMem("sound/looses.mp3");//�s�k�ȃv�����[�h

	while (1) 
	{

		//�^�C�g�����
		StopSoundMem(wins);//����BGM���~�߂�
		StopSoundMem(looses);//�s�kBGM���~�߂�
		PlaySoundMem(title, DX_PLAYTYPE_BACK);// BGM���Đ�����
		while (!ProcessMessage() && status == TITLE) 
		{
			ClearDrawScreen();//�`�揉����
			DrawGraph(0, 0, start, FALSE);//�w�i�\��
			SetFontSize(24);//�t�H���g�T�C�Y�w��

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
			DrawGraph(160, 870, button, TRUE);//�w�i�\��
			if (CheckHitKey(KEY_INPUT_RETURN))
			{
				status = SETUMEI;//���^�[���L�[�ŊJ�n

								 //�Q�[���������֘A
				scr = 0; //�X�N���[��������
				overTime = -1;
				overFlag = false;
				yFlag = false;
			}
			ScreenFlip();//��ʍX�V����
		}

		///////////////////////////////////////////////
		//����//
		///////////////////////////////////////////////

		while (!ProcessMessage() && status == SETUMEI) {
			ClearDrawScreen();//�`�揉����
			DrawGraph(0, 0, setumei, FALSE);//�w�i�\��

			if (CheckHitKey(KEY_INPUT_SPACE))
			{
				status = PLAY;
			}

			ScreenFlip();//��ʍX�V����
		}


		//�Q�[�����C��
		StopSoundMem(title);
		PlaySoundMem(battle, DX_PLAYTYPE_BACK);// BGM���Đ�����

		while (!ProcessMessage() && status == PLAY)
		{
			overTime--;

			//�`�揉����
			ClearDrawScreen();

			DrawGraph(haikeix, haikeiy, haikei, FALSE);//�w�i�\��






			if (overTime < 0 && overFlag == FALSE)
			{
				scr -= SCROLLSPEED;


				//���@�ړ�����

				nFlag = true;



				//���@���ړ���`
				if (CheckHitKey(KEY_INPUT_LEFT)) {
					px += lpx;
				}
				//���@�E�ړ���`
				if (CheckHitKey(KEY_INPUT_RIGHT)) {
					px += rpx;
				}
				//���@��ړ���`
				if (CheckHitKey(KEY_INPUT_UP)) {
					py += apy;
				}
				//���@���ړ���`
				if (CheckHitKey(KEY_INPUT_DOWN)) {
					py += upy;
				}
				//���@�X�N���[������
				px = px + SCROLLSPEED;
				if (px <= 0)
				{
					px = 0;
					if (CheckHitKey(KEY_INPUT_D))
					{
						px += rpx;
					}

				}

				if (px + scr <= 0) lpx = 0; else lpx = -8;//���ɓ����������~
				if (px + scr >= 1800) rpx = 0; else rpx = 10;//�E�ɓ����������~
				if (py + apy <= 0) apy = 0; else apy = -10;//��ɓ����������~
				if (py + upy >= 990) upy = 0; else upy = 10;//���ɓ����������~




															//�G�@�����ړ�����
				ex -= esx;//�G�@���ړ���`
				ey += esy;//�G�@�c�ړ���`
						  //���ɓ��������甽�]
				if (ex <= -150)
				{
					esx = -esx;
					esy = 34;
					esy = -esy;
				}
				//�E�ɓ��������甽�]
				if (ex >= 1600)
				{
					esx = -esx;
					esy = 35;
					esy = -esy;
				}
				//��ɓ��������甽�]
				if (ey <= -100)
				{
					esy = -24;
					esy = -esy;
				}
				//���ɓ��������甽�]
				if (ey >= 830)
				{
					esy = 37;
					esy = -esy;
				}

				//���@�ƃ}�b�v�̓����蔻��
				if (overFlag == FALSE)
				{
					int ix, iy;//�Ђ��肤��
					ix = (px + 50) / 128;
					iy = (py + 50) / 128;
					if (map[stage][iy][ix] != 0)
					{
						overFlag = TRUE;
						overTime = 120;
					}
					//�݂�����
					ix = (px + 95) / 128;
					iy = (py + 50) / 128;
					if (map[stage][iy][ix] != 0)
					{
						overFlag = TRUE;
						overTime = 120;
					}
					//�݂���������
					ix = (px + 95) / 128;
					iy = (py + 100) / 128;
					if (map[stage][iy][ix] != 0)
					{
						overFlag = TRUE;
						overTime = 120;
					}
					//�Ђ��肵��
					ix = (px + 50) / 128;
					iy = (py + 100) / 128;
					if (map[stage][iy][ix] != 0)
					{
						overFlag = TRUE;
						overTime = 120;
					}
				}


				//�Q�[���N���A����
				if (px >= 5000)
				{
					status = CLEAR;
				}
				//�G�@�Ǝ��@�̓����蔻��
				if (ef)
				{
					if ((px + scr) + 20 > ex + 100 && (px + scr) + 120 < ex + 300 && py + 120 > ey + 100 && py + 20 < ey + 300)
					{
						hitpoint -= 1;//�q�b�g�|�C���g���Z
						ef = false;//�����薳��
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
							overFlag = true;//�Q�[���I�[�o�[����
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
				//������v���O����
				nFlag = false;
				py += 5;
			}

			////////////////////////////////////////////////////////////////////////////////

			if (overFlag == TRUE && overTime < 0)
			{
				status = OVER;
			}
			//�`�揈��

			//�w�i�`��

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

			timer = GetNowCount();//�^�C�}�[�Ō��ݎ������擾
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

			//HPbar�\��///////////////

			DrawGraph(50, 20, HPbar[hitpoint], TRUE);
			ScreenFlip();//��ʍX�V����


		}

		if (ProcessMessage() < 0)
		{
			break;
		}

		//�Q�[���I�[�o�[���
		StopSoundMem(battle);//�Q�[��BGM���~�߂�
		PlaySoundMem(looses, DX_PLAYTYPE_BACK);// BGM���Đ�����
		while (!ProcessMessage() && status == OVER) 
		{
			ClearDrawScreen();//�`�揉����
			DrawGraph(0, 0, loose, FALSE);
			if (CheckHitKey(KEY_INPUT_SPACE)) status = TITLE;//���^�[���L�[�Ń^�C�g��
			hitpoint = 5;
			px = 0, py = 444;
			ex = 480, ey = 10;

			ScreenFlip();//��ʍX�V����


		}

		//WaitTimer(300);//�J�n�x������

		//�Q�[���N���A���
		StopSoundMem(battle);//�Q�[��BGM���~�߂�
		PlaySoundMem(wins, DX_PLAYTYPE_BACK);// BGM���Đ�����
		while (!ProcessMessage() && status == CLEAR) 
		{
			ClearDrawScreen();//�`�揉����
			DrawGraph(0, 0, win, FALSE);
			hitpoint = 5;
			zahyou = 0, 0;
			px = 0, py = 444;
			ex = 480, ey = 10;

			if (CheckHitKey(KEY_INPUT_SPACE)) status = TITLE;//���^�[���L�[�Ń^�C�g��
			ScreenFlip();//��ʍX�V����
		}

		//WaitTimer(1000);//�J�n�x������

		if (ProcessMessage() != 0)
		{
			break;
		}

		if (CheckHitKey(KEY_INPUT_ESCAPE))
		{
			break;
		}

		//���[�v���甲����

	}
	DxLib_End();//�Q�[���I������

	return 0;

}
