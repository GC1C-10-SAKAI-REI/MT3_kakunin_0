#define USE_MATH_DEFINES
#define WINDOW_WIDTH 1280//ウィンドウの幅
#define WINDOW_HEIGHT 720//ウィンドウの高さ

#include <Novice.h>
#include <cmath>
#include <assert.h>
#include "Struct.h"

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

//1.x軸回転行列
Matrix4x4 MakeRotateXMatrix(float rad);
//2.y軸回転行列
Matrix4x4 MakeRotateYMatrix(float rad);
//3.z軸回転行列
Matrix4x4 MakeRotateZMatrix(float rad);

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

	Vec3 rotate{ 0.4f,1.43f,-0.8f };

	Matrix4x4 rotateXMatrix = MakeRotateXMatrix(rotate.X);
	Matrix4x4 rotateYMatrix = MakeRotateXMatrix(rotate.Y);
	Matrix4x4 rotateZMatrix = MakeRotateXMatrix(rotate.Z);
	//Matrix4x4 rotateXYZMatrix = 	

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

		MatrixScreenPrintf(0, 0, rotateXMatrix, "rotateXMatrix");
		MatrixScreenPrintf(0, rowHeight * 5, rotateYMatrix, "rotateYMatrix");
		MatrixScreenPrintf(0, rowHeight * 5, rotateZMatrix, "rotateZMatrix");
		//MatrixScreenPrintf(0, rowHeight * 5, rotateXYZMatrix, "rotateXYZMatrix");

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
	return Matrix4x4();
}

Matrix4x4 MakeRotateYMatrix(float rad)
{
	return Matrix4x4();
}

Matrix4x4 MakeRotateZMatrix(float rad)
{
	return Matrix4x4();
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