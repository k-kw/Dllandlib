#pragma once

#ifdef DLLLENSCLASS_EXPORTS
#define LENS_CLASS_DLL_API __declspec(dllexport)
#else 
#define LENS_CLASS_DLL_API __declspec(dllimport)
#endif

extern "C" LENS_CLASS_DLL_API class My_Lens {
private:
	//レンズサイズ
	int lx;
	int ly;

	////波長
	//double lamda;
	////ピッチ
	//double d;
	

public:
	//レンズ配列先頭ポインタ
	double* lens_Re;
	double* lens_Im;


	LENS_CLASS_DLL_API My_Lens(int lsx, int lsy/*, double lam, double dx, double* Re_pr, double* Im_pr*/);  //コンストラクタ
	LENS_CLASS_DLL_API void a_Lens(int approx, double f, double lamda, double d);                           //単一レンズ
	
    //式が合ってるかわからないから実装しない
	//void cylind_Lens(int approx, int vert_hori, double f);                            //シリンドリカルレンズ

	LENS_CLASS_DLL_API void diffuser_Random(int rand_seed);                                                //ランダム拡散板
	LENS_CLASS_DLL_API void diffuser_Lensarray(int ls, int approx, double f, double lamda, double d);      //レンズアレイ拡散板
	LENS_CLASS_DLL_API ~My_Lens();

};