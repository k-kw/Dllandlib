#include <string>
#include <iostream>
#include <fstream>
#include <windows.h>
#include "Bmp_class_dll.h"


#pragma warning(disable:4996)

using namespace std;


//���̃t�@�C�����݂̂Ŏg��inline�֐�
template <class Type>
inline Type get_max(Type* data, int size)
{
	Type max = data[0];
	for (int i = 0; i < size; i++) {
		if (max < data[i]) {
			max = data[i];
		}
	}

	return max;
}

//�ŏ��l
template <class Type>
inline Type get_min(Type* data, int size)
{
	Type min = data[0];
	for (int i = 0; i < size; i++) {
		if (min > data[i]) {
			min = data[i];
		}
	}

	return min;
}

//�ő�l�Ő��K��
template <class Type>
inline void norm_max(Type* data_in, int size, double* data_out)
{
	Type max;
	max = get_max(data_in, size);

	for (int i = 0; i < size; i++) {
		data_out[i] = (double)((double)data_in[i] / (double)max);
	}

}

//�ő�l�ƍŏ��l�Ő��K��(�m����0~1)
template <class Type>
inline void norm_max_min(Type* data_in, int size, double* data_out)
{
	Type max;
	max = get_max(data_in, size);
	Type min;
	min = get_min(data_in, size);

	double* tmp;
	tmp = new double[size];

	for (int i = 0; i < size; i++) {
		tmp[i] = (double)((data_in[i] - min) / (max - min));
	}

	for (int i = 0; i < size; i++) {
		data_out[i] = tmp[i];
	}


	delete[]tmp;
}

//���K����,n�K����,int�^�o��
template <typename Type>
inline void norm_reso_n(Type* data_in, int* data_out, int n, int size)
{
	double* tmp;
	tmp = new double[size];
	norm_max_min(data_in, size, tmp);

	for (int i = 0; i < size; i++) {
		data_out[i] = (int)(round(tmp[i] * n));
	}

	delete[]tmp;
}


//int�f�[�^��unsigned char�ɕϊ���A�i�[
//0~255�̃f�[�^�Ɍ���
inline void to_uch(int* data_in, int size, unsigned char* data_img)
{
	for (int i = 0; i < size; i++) {
		data_img[i] = (unsigned char)data_in[i];
	}
}




//�N���X�����o�֐���`

//�R���X�g���N�^
My_Bmp::My_Bmp(int sx, int sy)
{
	img = new unsigned char[sx * sy];
	im_x = sx;
	im_y = sy;
	//cout << "BMP�R���X�g���N�^" << endl;
}


//BMP�ǂݍ���
void My_Bmp::img_read(string imgpath) {


	//�]���ȃw�b�_�̃o�b�t�@
	BITMAPFILEHEADER BmpFileHeader;
	BITMAPINFOHEADER BmpInfoHeader;
	int color[1024];


	//�ǂݍ���
	fstream ifs(imgpath, ios::binary | ios::in);
	ifs.read((char*)&BmpFileHeader, sizeof(BITMAPFILEHEADER));
	ifs.read((char*)&BmpInfoHeader, sizeof(BITMAPINFOHEADER));
	ifs.read((char*)color, 1024);

	ifs.read((char*)img, sizeof(unsigned char) * im_x * im_y);


}


//�ǂݍ���unsigned char��double�ɂ��Ċi�[
void My_Bmp::ucimg_to_double(double* data_out)
{
	for (int i = 0; i < im_y * im_x; i++) {
		long tmp = (long)img[i];
		data_out[i] = (double)tmp;
	}
}





//�������݂����f�[�^��256�K�����Aunsigned char�ɕϊ���img�Ɋi�[
//���d��`
//double
void My_Bmp::data_to_ucimg(double* data_in)
{
	int* dataint;
	dataint = new int[im_x * im_y];
	norm_reso_n<double>(data_in, dataint, 255, im_x * im_y);

	to_uch(dataint, im_x * im_y, img);

	delete[]dataint;

}

//int
void My_Bmp::data_to_ucimg(int* data_in)
{
	int* dataint;
	dataint = new int[im_x * im_y];
	norm_reso_n<int>(data_in, dataint, 255, im_x * im_y);

	to_uch(dataint, im_x * im_y, img);

	delete[]dataint;

}

//float
void My_Bmp::data_to_ucimg(float* data_in)
{
	int* dataint;
	dataint = new int[im_x * im_y];
	norm_reso_n<float>(data_in, dataint, 255, im_x * im_y);

	to_uch(dataint, im_x * im_y, img);

	delete[]dataint;

}


//unsigned char��img�Ɋi�[
void My_Bmp::uc_to_img(unsigned char* data_in)
{
	for (int i = 0; i < im_x * im_y; i++) {
		img[i] = data_in[i];
	}
}


//BMP��������
void My_Bmp::img_write(string imgpath)
{
	//���̎��_�ŉ�f�f�[�^��256�K��������Aimg�Ɋi�[����Ă��Ȃ���΂Ȃ�Ȃ�
	//�w�b�_���p��
	BITMAPFILEHEADER BmpFileHeader;
	BITMAPINFOHEADER BmpInfoHeader;
	RGBQUAD			 RGBQuad[256];
	BmpFileHeader = { 19778, 14 + 40 + 1024 + (DWORD)(im_x * im_y), 0, 0, 14 + 40 + 1024 };
	BmpInfoHeader = { 40, im_x, im_y, 1, 8, 0L, 0L, 0L, 0L, 0L, 0L };
	for (int i = 0; i < 256; i++) {
		RGBQuad[i].rgbBlue = i;
		RGBQuad[i].rgbGreen = i;
		RGBQuad[i].rgbRed = i;
		RGBQuad[i].rgbReserved = 0;
	}

	//�o�̓t�@�C���I�[�v��
	fstream ofs(imgpath, ios::binary | ios::out);

	//�w�b�_����������
	ofs.write((char*)&BmpFileHeader, sizeof(BITMAPFILEHEADER));
	ofs.write((char*)&BmpInfoHeader, sizeof(BITMAPINFOHEADER));
	ofs.write((char*)RGBQuad, sizeof(RGBQuad));

	//��f�f�[�^��������
	ofs.write((char*)img, sizeof(unsigned char) * im_x * im_y);
	
}



My_Bmp::~My_Bmp()
{
	delete[]img;
	//cout << "BMP�f�R���X�g���N�^" << endl;
}

