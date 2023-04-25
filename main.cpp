#define USE_MATH_DEFINES
#define WINDOW_WIDTH 1280//ウィンドウの幅
#define WINDOW_HEIGHT 720//ウィンドウの高さ

#include <Novice.h>
#include <math.h>
#include <assert.h>
#include "Struct.h"

const char kWindowTitle[] = "GC2C_07_サカイレイ";

//行の間隔
static const int rowHeight = 20;
//列の間隔
static const int columnWidth = 60;

//ベクトル表示
void VectorScreenPrintf(int x, int y, const Vec3& vector, const char* label)
{
	Novice::ScreenPrintf(x, y, "%0.2f", vector.X);
	Novice::ScreenPrintf(x + columnWidth, y, "%0.2f", vector.Y);
	Novice::ScreenPrintf(x + columnWidth * 2, y, "%0.2f", vector.Z);
	Novice::ScreenPrintf(x + columnWidth * 3, y, "%s", label);
};

//3次元ベクトルの演算
//加算
Vec3 Add(Vec3& v1, Vec3& v2)
{
	Vec3 result;

	result.X = v1.X + v2.X;
	result.Y = v1.Y + v2.Y;
	result.Z = v1.Z + v2.Z;

	return result;
};
//減算
Vec3 Sub(Vec3& v1, Vec3& v2)
{
	Vec3 result;

	result.X = v1.X - v2.X;
	result.Y = v1.Y - v2.Y;
	result.Z = v1.Z - v2.Z;

	return result;
};
//スカラー倍
Vec3 Mul(float scalar, const Vec3& v)
{
	Vec3 result;

	result.X = scalar * v.X;
	result.Y = scalar * v.Y;
	result.Z = scalar * v.Z;

	return result;
};
//内積
float Dot(const Vec3& v1, const Vec3& v2)
{
	float result;

	result = (v1.X * v2.X) + (v1.Y * v2.Y) + (v1.Z * v2.Z);

	return result;
};
//長さ
float Length(const Vec3& v)
{
	return sqrt(pow(v.X, 2) + pow(v.Y, 2) + pow(v.Z, 2));
};
//正規化
Vec3 Normalize(const Vec3& v)
{
	Vec3 result = { 0 };
	float len = Length(v);

	if (len != 0)
	{
		result.X = v.X / len;
		result.Y = v.Y / len;
		result.Z = v.Z / len;
		return result;
	}
	else
	{
		return v;
	}
};

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, WINDOW_WIDTH, WINDOW_HEIGHT);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	Vec3 v1{ 1.0f,3.0f,-5.0f };
	Vec3 v2{ 4.0f,-1.0f,2.0f };
	float k = { 4.0f };

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0)
	{
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		/// ↓更新処理ここから

		//加算
		Vec3 resultAdd = Add(v1, v2);
		//減算
		Vec3 resultSub = Sub(v1, v2);
		//スカラー倍
		Vec3 resultMul = Mul(k, v1);
		//内積
		float resultDot = Dot(v1, v2);
		//長さ
		float resultLength = Length(v1);
		//正規化
		Vec3 resultNormalize = Normalize(v2);

		/// ↑更新処理ここまで



		/// ↓描画処理ここから

		//加算
		VectorScreenPrintf(0, 0, resultAdd, ": Add");
		//減算
		VectorScreenPrintf(0, rowHeight, resultSub, ": Sub");
		//スカラー倍
		VectorScreenPrintf(0, rowHeight * 2, resultMul, ": Mul");
		//内積
		Novice::ScreenPrintf(0, rowHeight * 3, "%0.2f : Dot", resultDot);
		//長さ
		Novice::ScreenPrintf(0, rowHeight * 4, "%0.2f : Length", resultLength);
		//正規化
		VectorScreenPrintf(0, rowHeight * 5, resultNormalize, ": Normalize");

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