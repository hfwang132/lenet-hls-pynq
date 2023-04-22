#ifndef _TB_UTILS_H_
#define _TB_UTILS_H_

#include "op.h"
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>


template<typename T, size_t M, size_t N>
void disp_arr(T (&arr)[M][N])
{
    for (size_t i = 0; i < M; i ++ ) {
        for (size_t j = 0; j < N; j++ ) {
            std::cout << arr[i][j] << ' ';
        }
        std::cout << std::endl;
    }
}

template<typename T, size_t M, size_t N>
void txt2arr(std::string filename, T (&arr)[M][N])
{
    std::ifstream infile;
	infile.open(filename);
	for (size_t i = 0; i < M; i++)
	{
		for (size_t j = 0; j < N; j++)
		{
			infile >> arr[i][j];
		}
    }
    infile.close();
}

template<typename D, typename S, size_t M, size_t N>
void copy_arr(D (dst)[M][N], S (&src)[M][N])
{
    for (size_t i = 0; i < M; i++) {
        for (size_t j = 0; j < N; j++) {
            dst[i][j] = src[i][j];
        }
    }
}

template<typename T, size_t M, size_t N>
void arr2txt(std::string filename, T (&arr)[M][N], int width=2, int precision=4)
{
    std::ofstream outfile;
	outfile.open(filename);
    outfile.precision(precision);
	for (size_t i = 0; i < M; i++)
	{
		for (size_t j = 0; j < N; j++)
		{
			outfile << std::setw(width) << arr[i][j] << " ";
		}
		outfile << std::endl;
    }
	outfile << std::endl;
    outfile.close();
}

template<typename T, size_t M>
void arr1d2txt(std::string filename, T (&arr)[M], int width=2, int precision=4)
{
    std::ofstream outfile;
	outfile.open(filename);
    outfile.precision(precision);
	for (size_t i = 0; i < M; i++)
	{
		outfile << std::setw(width) << arr[i] << std::endl;
    }
    outfile.close();
}

#endif
