#pragma once

#ifdef DLLLENSCLASS_EXPORTS
#define LENS_CLASS_DLL_API __declspec(dllexport)
#else 
#define LENS_CLASS_DLL_API __declspec(dllimport)
#endif

extern "C" LENS_CLASS_DLL_API class My_Lens {
private:
	//�����Y�T�C�Y
	int lx;
	int ly;

	////�g��
	//double lamda;
	////�s�b�`
	//double d;
	

public:
	//�����Y�z��擪�|�C���^
	double* lens_Re;
	double* lens_Im;


	LENS_CLASS_DLL_API My_Lens(int lsx, int lsy/*, double lam, double dx, double* Re_pr, double* Im_pr*/);  //�R���X�g���N�^
	LENS_CLASS_DLL_API void a_Lens(int approx, double f, double lamda, double d);                           //�P�ꃌ���Y
	
    //���������Ă邩�킩��Ȃ�����������Ȃ�
	//void cylind_Lens(int approx, int vert_hori, double f);                            //�V�����h���J�������Y

	LENS_CLASS_DLL_API void diffuser_Random(int rand_seed);                                                //�����_���g�U��
	LENS_CLASS_DLL_API void diffuser_Lensarray(int ls, int approx, double f, double lamda, double d);      //�����Y�A���C�g�U��
	LENS_CLASS_DLL_API ~My_Lens();

};