#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include "Lens_class_dll.h"

using namespace std;

#define sqr(x) ((x)*(x))

My_Lens::My_Lens(int lsx, int lsy)
{ 
	lens_Re = new double[lsx * lsy];
	lens_Im = new double[lsx * lsy];
	lx = lsx;
	ly = lsy;
	//cout << "レンズコンストラクタ" << endl;
}

My_Lens::~My_Lens()
{
	delete[]lens_Re;
	delete[]lens_Im;
	//cout << "レンズデコンストラクタ" << endl;
}

//レンズの位相変換作用
void My_Lens::a_Lens(int approx, double f, double lamda, double d)
{
	if (approx == 0) {
		//近似
		for (int i = 0; i < ly; i++) {
			for (int j = 0; j < lx; j++) {
				double dx, dy;
				dx = ((double)j - (lx / 2)) * d;
				dy = ((double)i - (ly / 2)) * d;

				lens_Re[i * lx + j] = cos((-2 * M_PI / lamda) * (sqr(dx) + sqr(dy)) / (2 * f));
				lens_Im[i * lx + j] = sin((-2 * M_PI / lamda) * (sqr(dx) + sqr(dy)) / (2 * f));
			}
		}

	}
	else {
		//近似なし
		for (int i = 0; i < ly; i++) {
			for (int j = 0; j < lx; j++) {
				double dx, dy;
				dx = ((double)j - (lx / 2)) * d;
				dy = ((double)i - (ly / 2)) * d;

				lens_Re[i * lx + j] = cos((-2 * M_PI / lamda) * sqrt(sqr(dx) + sqr(dy) + sqr(f)));
				lens_Im[i * lx + j] = sin((-2 * M_PI / lamda) * sqrt(sqr(dx) + sqr(dy) + sqr(f)));
			}
		}

	}
}

//ランダム拡散板
void My_Lens::diffuser_Random(int rand_seed)
{
	srand(rand_seed);
	double random_num;

	for (int i = 0; i < ly; i++) {
		for (int j = 0; j < lx; j++) {

			random_num = rand();
			lens_Re[i * lx + j] = cos(((double)random_num / RAND_MAX) * 2 * M_PI);
			lens_Im[i * lx + j] = sin(((double)random_num / RAND_MAX) * 2 * M_PI);
		}
	}

}

//レンズアレイ拡散板
void My_Lens::diffuser_Lensarray(int ls, int approx, double f, double lamda, double d)
{
	double* Re_one, * Im_one;
	Re_one = new double[ls * ls];
	Im_one = new double[ls * ls];

	//微小単一レンズ作成
	My_Lens one_lens(ls, ls);
	one_lens.a_Lens(approx, f, lamda, d);


	for (int i = 0; i < ly; i++) {
		for (int j = 0; j < lx; j++) {
			lens_Re[i * lx + j] = one_lens.lens_Re[(i % ls) * ls + (j % ls)];
			lens_Im[i * lx + j] = one_lens.lens_Im[(i % ls) * ls + (j % ls)];
		}
	}

	delete[]Re_one;
	delete[]Im_one;
}