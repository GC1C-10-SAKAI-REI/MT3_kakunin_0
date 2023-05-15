#define USE_MATH_DEFINES
#define WINDOW_WIDTH 1280//ウィンドウの幅
#define WINDOW_HEIGHT 720//ウィンドウの高さ

#include <Novice.h>
#include <math.h>
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

//1.平行移動行列
Matrix4x4 MakeTranslateMatrix(const Vec3 &translate);
//2.拡大縮小行列
Matrix4x4 MakeScaleMatrix(const Vec3 &scale);
//3.座標返還
Vec3 Transform(const Vec3 &vector, const Matrix4x4 &matrix);

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

	Vec3 translate{ 4.1f,2.6f,0.8f };
	Vec3 scale{ 1.5f,5.2f,7.3f };
	Matrix4x4 translateMatrix = MakeTranslateMatrix(translate);
	Matrix4x4 scaleMatrix = MakeScaleMatrix(scale);
	Vec3 point{ 2.3f,3.8f,1.4f };
	Matrix4x4 transformMatrix =
	{
		1.0f,2.0f,3.0f,4.0f,
		3.0f,1.0f,1.0f,2.0f,
		1.0f,4.0f,2.0f,3.0f,
		2.0f,2.0f,1.0f,3.0f
	};

	Vec3 transformed = Transform(point, transformMatrix);

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

		VectorScreenPrintf(0, 0, transformed, "transformed");
		MatrixScreenPrintf(0, 20, translateMatrix, "translateMatrix");
		MatrixScreenPrintf(0, rowHeight * 5, scaleMatrix, "scaleMatrix");

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

Matrix4x4 MakeTranslateMatrix(const Vec3 &translate)
{
	Matrix4x4 result;

	result.m[0][0] = 1;
	result.m[0][1] = 0;
	result.m[0][2] = 0;
	result.m[0][3] = 0;
	result.m[1][0] = 0;
	result.m[1][1] = 1;
	result.m[1][2] = 0;
	result.m[1][3] = 0;
	result.m[2][0] = 0;
	result.m[2][1] = 0;
	result.m[2][2] = 1;
	result.m[2][3] = 0;
	result.m[3][0] = translate.X;
	result.m[3][1] = translate.Y;
	result.m[3][2] = translate.Z;
	result.m[3][3] = 1;

	return result;
}

Matrix4x4 MakeScaleMatrix(const Vec3 &scale)
{
	Matrix4x4 result;

	result.m[0][0] = scale.X;
	result.m[0][1] = 0;
	result.m[0][2] = 0;
	result.m[0][3] = 0;
	result.m[1][0] = 0;
	result.m[1][1] = scale.Y;
	result.m[1][2] = 0;
	result.m[1][3] = 0;
	result.m[2][0] = 0;
	result.m[2][1] = 0;
	result.m[2][2] = scale.Z;
	result.m[2][3] = 0;
	result.m[3][0] = 0;
	result.m[3][1] = 0;
	result.m[3][2] = 0;
	result.m[3][3] = 1;

	return result;
}

Vec3 Transform(const Vec3& vector, const Matrix4x4& matrix)
{
	Vec3 result;

	result.X = (vector.X * matrix.m[0][0]) + (vector.Y * matrix.m[1][0]) + (vector.Z * matrix.m[2][0]) + matrix.m[3][0];
	result.Y = (vector.X * matrix.m[0][1]) + (vector.Y * matrix.m[1][1]) + (vector.Z * matrix.m[2][1]) + matrix.m[3][1];
	result.Z = (vector.X * matrix.m[0][2]) + (vector.Y * matrix.m[1][2]) + (vector.Z * matrix.m[2][2]) + matrix.m[3][2];

	float w = (vector.X * matrix.m[0][3]) + (vector.Y * matrix.m[1][3]) + (vector.Z * matrix.m[2][3]) + matrix.m[3][3];
	assert(w != 0.0f);

	result.X /= w;
	result.Y /= w;
	result.Z /= w;

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