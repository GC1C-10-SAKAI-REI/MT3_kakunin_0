#define USE_MATH_DEFINES
#define WINDOW_WIDTH 1280//ウィンドウの幅
#define WINDOW_HEIGHT 720//ウィンドウの高さ

#include <Novice.h>
#include <cmath>
#include <assert.h>
#include "Struct.h"

using namespace std;

const char kWindowTitle[] = "GC2C_07_サカイレイ";

//4x4行列
typedef struct Matrix4x4
{
	float m[4][4];
};

//行の間隔
static const int rowHeight = 20;
//列の間隔
static const int columnWidth = 60;

//X軸回転
Matrix4x4 MakeRotateXMatrix(float rad);
//Y軸回転
Matrix4x4 MakeRotateYMatrix(float rad);
//Z軸回転
Matrix4x4 MakeRotateZMatrix(float rad);
//積
Matrix4x4 Multiply(Matrix4x4& m1, const Matrix4x4& m2);
//3次元アフィン変換行列
Matrix4x4 MakeAffineMatrix(const Vec3 &scale, const Matrix4x4 &roate, const Vec3 &translate);

//行列表示関数
void MatrixScreenPrintf(int x, int y, const Matrix4x4 &matrix, const char *label);
//ベクトル表示
void VectorScreenPrintf(int x, int y, const Vec3 &vector, const char *label);

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, WINDOW_WIDTH, WINDOW_HEIGHT);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	Vec3 scale{ 1.2f,0.79f,-2.1f };
	Vec3 rotate{ 0.4f,1.43f,-0.8f };
	Vec3 translate{ 2.7f,-4.15f,1.57f };
	
	/*Matrix4x4 scaleMatrix = MakeScaleMatrix(scale);
	Matrix4x4 translateMatrix = MakeTranslateMatrix(translate);*/
	Matrix4x4 rotateXMatrix = MakeRotateXMatrix(rotate.X);
	Matrix4x4 rotateYMatrix = MakeRotateYMatrix(rotate.Y);
	Matrix4x4 rotateZMatrix = MakeRotateZMatrix(rotate.Z);
	Matrix4x4 rotateXYZMatrix = Multiply(rotateXMatrix, Multiply(rotateYMatrix, rotateZMatrix));
	Matrix4x4 worldMatrix = MakeAffineMatrix(scale, rotateXYZMatrix, translate);

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0)
	{
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		/// ↓更新処理ここから

		

		/// ↑更新処理ここまで



		/// ↓描画処理ここから

		MatrixScreenPrintf(0, 0, worldMatrix, "worldMatrix");

		/// ↑描画処理ここまで


		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0)
		{
			break;
		}
	}
	// ライブラリの終了
	Novice::Finalize();

	return 0;
}

Matrix4x4 MakeRotateXMatrix(float rad)
{
	Matrix4x4 result;

	result.m[0][0] = 1;
	result.m[0][1] = 0;
	result.m[0][2] = 0;
	result.m[0][3] = 0;
	result.m[1][0] = 0;
	result.m[1][1] = cos(rad);
	result.m[1][2] = sin(rad);
	result.m[1][3] = 0;
	result.m[2][0] = 0;
	result.m[2][1] = -sin(rad);
	result.m[2][2] = cos(rad);
	result.m[2][3] = 0;
	result.m[3][0] = 0;
	result.m[3][1] = 0;
	result.m[3][2] = 0;
	result.m[3][3] = 1;

	return result;
}

Matrix4x4 MakeRotateYMatrix(float rad)
{
	Matrix4x4 result;

	result.m[0][0] = cos(rad);
	result.m[0][1] = 0;
	result.m[0][2] = -sin(rad);
	result.m[0][3] = 0;
	result.m[1][0] = 0;
	result.m[1][1] = 1;
	result.m[1][2] = 0;
	result.m[1][3] = 0;
	result.m[2][0] = sin(rad);
	result.m[2][1] = 0;
	result.m[2][2] = cos(rad);
	result.m[2][3] = 0;
	result.m[3][0] = 0;
	result.m[3][1] = 0;
	result.m[3][2] = 0;
	result.m[3][3] = 1;

	return result;
}

Matrix4x4 MakeRotateZMatrix(float rad)
{
	Matrix4x4 result;

	result.m[0][0] = cos(rad);
	result.m[0][1] = sin(rad);
	result.m[0][2] = 0;
	result.m[0][3] = 0;
	result.m[1][0] = -sin(rad);
	result.m[1][1] = cos(rad);
	result.m[1][2] = 0;
	result.m[1][3] = 0;
	result.m[2][0] = 0;
	result.m[2][1] = 0;
	result.m[2][2] = 1;
	result.m[2][3] = 0;
	result.m[3][0] = 0;
	result.m[3][1] = 0;
	result.m[3][2] = 0;
	result.m[3][3] = 1;

	return result;
}

Matrix4x4 Multiply(Matrix4x4& m1, const Matrix4x4& m2)
{
	Matrix4x4 result;
	//0行目
	result.m[0][0] = (m1.m[0][0] * m2.m[0][0]) + (m1.m[0][1] * m2.m[1][0]) + (m1.m[0][2] * m2.m[2][0]) + (m1.m[0][3] * m2.m[3][0]);
	result.m[0][1] = (m1.m[0][0] * m2.m[0][1]) + (m1.m[0][1] * m2.m[1][1]) + (m1.m[0][2] * m2.m[2][1]) + (m1.m[0][3] * m2.m[3][1]);
	result.m[0][2] = (m1.m[0][0] * m2.m[0][2]) + (m1.m[0][1] * m2.m[1][2]) + (m1.m[0][2] * m2.m[2][2]) + (m1.m[0][3] * m2.m[3][2]);
	result.m[0][3] = (m1.m[0][0] * m2.m[0][3]) + (m1.m[0][1] * m2.m[1][3]) + (m1.m[0][2] * m2.m[2][3]) + (m1.m[0][3] * m2.m[3][3]);
	//1行目
	result.m[1][0] = (m1.m[1][0] * m2.m[0][0]) + (m1.m[1][1] * m2.m[1][0]) + (m1.m[1][2] * m2.m[2][0]) + (m1.m[1][3] * m2.m[3][0]);
	result.m[1][1] = (m1.m[1][0] * m2.m[0][1]) + (m1.m[1][1] * m2.m[1][1]) + (m1.m[1][2] * m2.m[2][1]) + (m1.m[1][3] * m2.m[3][1]);
	result.m[1][2] = (m1.m[1][0] * m2.m[0][2]) + (m1.m[1][1] * m2.m[1][2]) + (m1.m[1][2] * m2.m[2][2]) + (m1.m[1][3] * m2.m[3][2]);
	result.m[1][3] = (m1.m[1][0] * m2.m[0][3]) + (m1.m[1][1] * m2.m[1][3]) + (m1.m[1][2] * m2.m[2][3]) + (m1.m[1][3] * m2.m[3][3]);
	//2行目
	result.m[2][0] = (m1.m[2][0] * m2.m[0][0]) + (m1.m[2][1] * m2.m[1][0]) + (m1.m[2][2] * m2.m[2][0]) + (m1.m[2][3] * m2.m[3][0]);
	result.m[2][1] = (m1.m[2][0] * m2.m[0][1]) + (m1.m[2][1] * m2.m[1][1]) + (m1.m[2][2] * m2.m[2][1]) + (m1.m[2][3] * m2.m[3][1]);
	result.m[2][2] = (m1.m[2][0] * m2.m[0][2]) + (m1.m[2][1] * m2.m[1][2]) + (m1.m[2][2] * m2.m[2][2]) + (m1.m[2][3] * m2.m[3][2]);
	result.m[2][3] = (m1.m[2][0] * m2.m[0][3]) + (m1.m[2][1] * m2.m[1][3]) + (m1.m[2][2] * m2.m[2][3]) + (m1.m[2][3] * m2.m[3][3]);
	//3行目
	result.m[3][0] = (m1.m[3][0] * m2.m[0][0]) + (m1.m[3][1] * m2.m[1][0]) + (m1.m[3][2] * m2.m[2][0]) + (m1.m[3][3] * m2.m[3][0]);
	result.m[3][1] = (m1.m[3][0] * m2.m[0][1]) + (m1.m[3][1] * m2.m[1][1]) + (m1.m[3][2] * m2.m[2][1]) + (m1.m[3][3] * m2.m[3][1]);
	result.m[3][2] = (m1.m[3][0] * m2.m[0][2]) + (m1.m[3][1] * m2.m[1][2]) + (m1.m[3][2] * m2.m[2][2]) + (m1.m[3][3] * m2.m[3][2]);
	result.m[3][3] = (m1.m[3][0] * m2.m[0][3]) + (m1.m[3][1] * m2.m[1][3]) + (m1.m[3][2] * m2.m[2][3]) + (m1.m[3][3] * m2.m[3][3]);

	return result;
}

Matrix4x4 MakeAffineMatrix(const Vec3 &scale, const Matrix4x4 &roate, const Vec3 &translate)
{
	Matrix4x4 result;

	result.m[0][0] = scale.X * roate.m[0][0];
	result.m[0][1] = scale.X * roate.m[0][1];
	result.m[0][2] = scale.X * roate.m[0][2];
	result.m[0][3] = 0;
	result.m[1][0] = scale.Y * roate.m[1][0];
	result.m[1][1] = scale.Y * roate.m[1][1];
	result.m[1][2] = scale.Y * roate.m[1][2];
	result.m[1][3] = 0;
	result.m[2][0] = scale.Z * roate.m[2][0];
	result.m[2][1] = scale.Z * roate.m[2][1];
	result.m[2][2] = scale.Z * roate.m[2][2];
	result.m[2][3] = 0;
	result.m[3][0] = translate.X;
	result.m[3][1] = translate.Y;
	result.m[3][2] = translate.Z;
	result.m[3][3] = 1;

	return result;
}

void MatrixScreenPrintf(int x, int y, const Matrix4x4 &matrix, const char *label)
{
	Novice::ScreenPrintf(x, y, "%s", label);
	for (int row = 0; row < 4; ++row)
	{
		for (int column = 0; column < 4; ++column)
		{
			Novice::ScreenPrintf(x + column * columnWidth, (y + 20) + row * rowHeight, "%6.02f", matrix.m[row][column]);
		}
	}
}

void VectorScreenPrintf(int x, int y, const Vec3& vector, const char* label)
{
	Novice::ScreenPrintf(x, y, "%0.2f", vector.X);
	Novice::ScreenPrintf(x + columnWidth, y, "%0.2f", vector.Y);
	Novice::ScreenPrintf(x + columnWidth * 2, y, "%0.2f", vector.Z);
	Novice::ScreenPrintf(x + columnWidth * 3, y, "%s", label);
};