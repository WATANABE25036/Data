/*==============================================================================

   �֐��W [Library.cpp]
														 Author : �n� �C
														 Date   : 2024/01/18
--------------------------------------------------------------------------------

==============================================================================*/
#include "Library.h"

//-----------------------------------------------------------------------------
// 0�Ȃ�0�A���̕����Ȃ�1�A�s�̕����Ȃ�-1��Ԃ�
//-----------------------------------------------------------------------------
int Sign(int value)
{
	if (value == 0)return 0;
	else if (value > 0)return 1;
	else return -1;
}

int Sign(float value)
{
	if (value == 0)return 0;
	else if (value > 0)return 1;
	else return -1;
}

//-----------------------------------------------------------------------------
// ���R����Ԃ�
//-----------------------------------------------------------------------------
int Nat(int value)
{
	if (value < 0)return 0;

	return (int)value;
}

int Nat(float value)
{
	if (value < 0)return 0;

	return (int)value;
}

//-----------------------------------------------------------------------------
// �����̐؂�̂� (digit = 10, 100, 1000...)
//-----------------------------------------------------------------------------
float Round(float num, int digit)
{
	int value = int(num * digit);
	num = float(value) / digit;
	return num;
}

//-----------------------------------------------------------------------------
// ���W����p�x���v�Z����֐� �x
//-----------------------------------------------------------------------------
double PointDirection(double x1, double y1, double x2, double y2)
{
	// ���W�A���P�ʂ̊p�x���v�Z
	double angle = std::atan2(y2 - y1, x2 - x1);

	// ���W�A����x�ɕϊ�
	double degrees = angle * 180.0f / 3.14159f;

	// 0����360�x�͈̔͂ɒ���
	if (degrees < 0)
	{
		degrees += 360.0;
	}

	return degrees;
}

//-----------------------------------------------------------------------------
// ���W����p�x���v�Z����֐� ���W�A��
//-----------------------------------------------------------------------------
double PointDirectionRadian(double x1, double y1, double x2, double y2)
{
	// ���W�A���P�ʂ̊p�x���v�Z
	double angle = std::atan2(y2 - y1, x2 - x1);

	return angle;
}

//-----------------------------------------------------------------------------
// �Ώۂ܂ł�x��y�̋�����Ԃ�
//-----------------------------------------------------------------------------
D3DXVECTOR2 PointDistance(float x1, float y1, float x2, float y2)
{
	D3DXVECTOR2 distance;
	distance.x = x2 - x1;
	distance.y = y2 - y1;

	return distance;
}

//-----------------------------------------------------------------------------
// x��y�̃X�J���[(�����������Ȃ��͂̑傫��)
//-----------------------------------------------------------------------------
float PointScalar(float x1, float y1, float x2, float y2)
{
	D3DXVECTOR2 distance;
	distance.x = x2 - x1;
	distance.y = y2 - y1;

	// �s�^�S���X�̒藝���g����2�_�Ԃ̋������v�Z
	float scalar = sqrt(distance.x * distance.x + distance.y * distance.y);

	return scalar;
}

//-----------------------------------------------------------------------------
// �p�x�ƒ�������x�N�g�� (x, y) ���v�Z
//-----------------------------------------------------------------------------
D3DXVECTOR2 CalculateVector(double length, double angleRadians)
{
	D3DXVECTOR2 result;

	result.x = float(cos(angleRadians));
	result.y = float(sin(angleRadians));

	D3DXVec2Normalize(&result, &result);
	result *= length;//�ړI�̃X�s�[�h�ɂ��邽�߂ɃX�s�[�h����Z����

	return result;
}

//-----------------------------------------------------------------------------
// �O���[�o�����W�����[�J�����W�ɂ���
//-----------------------------------------------------------------------------
D3DXVECTOR3 GlobalToLocal(D3DXVECTOR3 starting, D3DXVECTOR3 subject)
{
	D3DXVECTOR3 pos = subject - starting;
	return pos;
}

////-----------------------------------------------------------------------------
//// �O���[�o���Ō����p�x�����߂�
////-----------------------------------------------------------------------------
//float LocalAngle(D3DXVECTOR3 startingPos, D3DXVECTOR3 startingDir, D3DXVECTOR3 subject)
//{
//	// �v���C���[�̈ʒu���瑊��̈ʒu�ւ̃x�N�g�������߂�
//	D3DXVECTOR3 enemyVector = subject - startingPos;
//
//	// �v���C���[�̕����x�N�g���Ƒ���̈ʒu�x�N�g���̊Ԃ̊p�x���v�Z����
//	float angle = atan2f(enemyVector.z, enemyVector.x) - atan2f(startingDir.z, startingDir.x);
//	if (angle < 0.0f)
//	{
//		angle += 2.0f * D3DX_PI;
//	}
//
//	// �p�x��x���@�ɕϊ�����
//	angle = D3DXToDegree(angle);
//	return angle;
//}

//-----------------------------------------------------------------------------
// �A�j���[�V������ݒ肷��
// [����] basePattern: �����0�Ƃ����J�n�t���[��, 
//		  widthPattern: ���̃A�j���p�^�[����, 
//-----------------------------------------------------------------------------
D3DXVECTOR2 SetAnimation(int basePattern, int animeCount, int allWidthPattern, int allHeightPattern, int widthPattern, bool reverse)
{
	D3DXVECTOR2 uv;
	//U      W											N�Ԗڂ� % ���̃p�^�[����
	uv.x = (1.0f / allWidthPattern) * ((animeCount + basePattern) % widthPattern);	//���̍��W�v�Z
	//V     H											N�Ԗڂ� / ���̑S�p�^�[��
	uv.y = (1.0f / allHeightPattern) * ((animeCount + basePattern) / allWidthPattern); //�c�̍��W�v�Z

	//�e�N�X�`�����]
	if (reverse)
	{
		uv.x = 1 + (1 - uv.x) - Round(1.0f / allWidthPattern, 100);//���[�Ȃ̂�-0.25
	}

	return uv;
}

//-----------------------------------------------------------------------------
// UV���W���Z�b�g(���� : ����[��0���̉E�ׂ��1,2,3...�Ƃ����Ƃ��̐�)
//-----------------------------------------------------------------------------
D3DXVECTOR2 GetUV(int index, int widthPattern, int heightPattern)
{
	float U = (index % widthPattern) * (1.0f / widthPattern);
	float V = (index / widthPattern) * (1.0f / heightPattern);
	D3DXVECTOR2 UV = D3DXVECTOR2(U, V);
	return UV;
}

//-----------------------------------------------------------------------------
// ���������������ɂȂ�����0�ɂ���
//-----------------------------------------------------------------------------
int Counter(int count, int max)
{
	count++;

	if (count >= max)
	{
		count = 0;
	}
	return count;
}

//-----------------------------------------------------------------------------
// �����_��
//-----------------------------------------------------------------------------
int GetRandomInt(int min, int max)
{
	std::random_device rd;
	std::uniform_int_distribution<> dist(min, max);
	return dist(rd);
}

float GetRandomFloat(float min, float max)
{
	std::random_device rd;
	std::uniform_real_distribution<> dist(min, max);
	return float(dist(rd));
}

//-----------------------------------------------------------------------------
// ���Œ��I���܂�
// �����ɉ�%���������������I�΂���1��������Ȃ�2��Ԃ��܂�
// �ǂ���I�΂�Ȃ����0��Ԃ��܂�
//-----------------------------------------------------------------------------
int RandomPercent(float percent1, float percent2, float percent3, float percent4, float percent5, float percent6, float percent7, float percent8, float percent9, float percent10)
{
	float percent[10] = { percent1 ,percent2 ,percent3 ,percent4 ,percent5 ,percent6 ,percent7 ,percent8 ,percent9 ,percent10 };
	float ran = GetRandomFloat(1.0f, 100.0f);

	for (int i = 0; i < 10; i++)
	{
		if (ran < percent[i])return i + 1;

		ran -= int(percent[i]);
	}

	return 0;
}