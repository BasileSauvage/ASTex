/*******************************************************************************
* ASTex:                                                                       *
* Copyright (C) IGG Group, ICube, University of Strasbourg, France             *
*                                                                              *
* This library is free software; you can redistribute it and/or modify it      *
* under the terms of the GNU Lesser General Public License as published by the *
* Free Software Foundation; either version 2.1 of the License, or (at your     *
* option) any later version.                                                   *
*                                                                              *
* This library is distributed in the hope that it will be useful, but WITHOUT  *
* ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or        *
* FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License  *
* for more details.                                                            *
*                                                                              *
* You should have received a copy of the GNU Lesser General Public License     *
* along with this library; if not, write to the Free Software Foundation,      *
* Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301 USA.           *
*                                                                              *
* Web site: https://astex-icube.github.io                                      *
* Contact information: astex@icube.unistra.fr                                  *
*                                                                              *
*******************************************************************************/



#include <iostream>
#include <chrono>

#include <ASTex/image_gray.h>
#include <ASTex/image_rgb.h>
#include <ASTex/image_rgba.h>
#include <ASTex/easy_io.h>


using namespace ASTex;


const int NB_ITER = 20;
const int IMG_SZ = 4096;


void bench_pixels()
{
	using IMG  = ImageRGBAu8;
	using PIX  = IMG::PixelType;
	IMG img1(IMG_SZ, IMG_SZ);
	IMG img2(IMG_SZ, IMG_SZ);
	IMG img3(IMG_SZ, IMG_SZ);

	img1.for_all_pixels([](PIX& p)
	{
		p = IMG::itkPixel(11);
	});

	img2.for_all_pixels([](PIX& p)
	{
		p = IMG::itkPixel(33);
	});

	auto start_chrono = std::chrono::system_clock::now();

	for (int k = 0; k<NB_ITER; ++k)
	{
		for (int j = 0; j<img3.height(); ++j)
			for (int i = 0; i < img3.width(); ++i)
			{
				const auto& P = img1.pixelAbsolute(i, j);
				const auto& Q = img2.pixelAbsolute(i, j);
				auto& R = img3.pixelAbsolute(i, j);
				for (uint32_t c = 0; c<IMG::NB_CHANNELS; ++c)
					channel(R, c) = (channel_long(P, c) + channel_long(Q, c)) / 2;
			}
	}

	std::chrono::duration<double> elapsed_seconds = std::chrono::system_clock::now() - start_chrono;
	std::cout << "pixels uint8: "<< elapsed_seconds.count() << " s."<< std::endl;
	std::cout << "P : " << NICE(img3.pixelAbsolute(0,0)) << " / " << NICE(img3.pixelAbsolute(10,10)) << " / " << NICE(img3.pixelAbsolute(100,100)) << " / " << std::endl;
}


void bench_pixels_double()
{
	using IMG  = ImageRGBAd;
	using PIX  = IMG::PixelType;
	IMG img1(IMG_SZ, IMG_SZ);
	IMG img2(IMG_SZ, IMG_SZ);
	IMG img3(IMG_SZ, IMG_SZ);

	img1.for_all_pixels([](PIX& p)
	{
		p = IMG::itkPixel(11);
	});

	img2.for_all_pixels([](PIX& p)
	{
		p = IMG::itkPixel(33);
	});

	auto start_chrono = std::chrono::system_clock::now();

	for (int k = 0; k<NB_ITER; ++k)
	{
		for (int j = 0; j<img3.height(); ++j)
			for (int i = 0; i < img3.width(); ++i)
			{
				const auto& P = img1.pixelAbsolute(i, j);
				const auto& Q = img2.pixelAbsolute(i, j);
				auto& R = img3.pixelAbsolute(i, j);
				for (uint32_t c = 0; c<IMG::NB_CHANNELS; ++c)
					channel(R, c) = (channel(P, c) + channel(Q, c)) / 2;
			}
	}

	std::chrono::duration<double> elapsed_seconds = std::chrono::system_clock::now() - start_chrono;
	std::cout << "pixels double : "<< elapsed_seconds.count() << " s."<< std::endl;
	std::cout << "P : " << NICE(img3.pixelAbsolute(0,0)) << " / " << NICE(img3.pixelAbsolute(10,10)) << " / " << NICE(img3.pixelAbsolute(100,100)) << " / " << std::endl;
}


void bench_eigen_pixels()
{
	using IMG = ImageRGBAu8;
	using PIX = IMG::PixelType;
	IMG img1(IMG_SZ, IMG_SZ);
	IMG img2(IMG_SZ, IMG_SZ);
	IMG img3(IMG_SZ, IMG_SZ);

	img1.for_all_pixels([](PIX& p)
	{
		p = IMG::itkPixel(11);
	});

	img2.for_all_pixels([](PIX& p)
	{
		p = IMG::itkPixel(33);
	});

	auto start_chrono = std::chrono::system_clock::now();

	for (int k = 0; k<NB_ITER; ++k)
	{
		for (int j = 0; j<img3.height(); ++j)
			for (int i = 0; i < img3.width(); ++i)
			{
				IMG::DoublePixelEigen P = img1.pixelEigenAbsolute(i, j);
				IMG::DoublePixelEigen Q = img2.pixelEigenAbsolute(i, j);
				img3.pixelEigenAbsolute(i, j) = (P+Q)/2;
			}
	}

	std::chrono::duration<double> elapsed_seconds = std::chrono::system_clock::now() - start_chrono;
	std::cout << "uint8 -> double_eigen_pixels : " << elapsed_seconds.count() << " s." << std::endl;
	std::cout << "P : " << NICE(img3.pixelAbsolute(0,0)) << " / " << NICE(img3.pixelAbsolute(10,10)) << " / " << NICE(img3.pixelAbsolute(100,100)) << " / " << std::endl;

}

void bench_eigen_pixels_2()
{
	using IMG = ImageRGBAu8;
	using PIX = IMG::PixelType;
	IMG img1(IMG_SZ, IMG_SZ);
	IMG img2(IMG_SZ, IMG_SZ);
	IMG img3(IMG_SZ, IMG_SZ);

	img1.for_all_pixels([](PIX& p)
	{
		p = IMG::itkPixel(11);
	});

	img2.for_all_pixels([](PIX& p)
	{
		p = IMG::itkPixel(33);
	});

	auto start_chrono = std::chrono::system_clock::now();

	for (int k = 0; k<NB_ITER; ++k)
	{
		for (int j = 0; j<img3.height(); ++j)
			for (int i = 0; i < img3.width(); ++i)
			{
				IMG::LongPixelEigen P = img1.pixelEigenAbsolute(i, j);
				IMG::LongPixelEigen Q = img2.pixelEigenAbsolute(i, j);
				img3.pixelEigenAbsolute(i, j) =  (P+Q)/2;
			}
	}

	std::chrono::duration<double> elapsed_seconds = std::chrono::system_clock::now() - start_chrono;
	std::cout << "uint8 -> long_eigen_pixels : " << elapsed_seconds.count() << " s." << std::endl;
	std::cout << "P : " << NICE(img3.pixelAbsolute(0,0)) << " / " << NICE(img3.pixelAbsolute(10,10)) << " / " << NICE(img3.pixelAbsolute(100,100)) << " / " << std::endl;
}


void bench_double_eigen_pixels()
{
	using IMG = ImageRGBAd;
	using PIX = IMG::PixelType;
	IMG img1(IMG_SZ, IMG_SZ);
	IMG img2(IMG_SZ, IMG_SZ);
	IMG img3(IMG_SZ, IMG_SZ);

	img1.for_all_pixels([](PIX& p)
	{
		p = IMG::itkPixel(11);
	});

	img2.for_all_pixels([](PIX& p)
	{
		p = IMG::itkPixel(33);
	});

	auto start_chrono = std::chrono::system_clock::now();

	for (int k = 0; k<NB_ITER; ++k)
	{
		for (int j = 0; j<img3.height(); ++j)
			for (int i = 0; i < img3.width(); ++i)
			{
				IMG::DoublePixelEigen P = img1.pixelEigenAbsolute(i, j);
				IMG::DoublePixelEigen Q = img2.pixelEigenAbsolute(i, j);
				img3.pixelEigenAbsolute(i, j) = (P+Q)/2;
			}
	}

	std::chrono::duration<double> elapsed_seconds = std::chrono::system_clock::now() - start_chrono;
	std::cout << "double -> eigen_double : " << elapsed_seconds.count() << " s." << std::endl;
	std::cout << "P : " << NICE(img3.pixelAbsolute(0,0)) << " / " << NICE(img3.pixelAbsolute(10,10)) << " / " << NICE(img3.pixelAbsolute(100,100)) << " / " << std::endl;

}

void bench_parallel_eigen()
{
	using IMG = ImageRGBAu8;
	using PIX = IMG::PixelType;
	IMG img1(IMG_SZ, IMG_SZ);
	IMG img2(IMG_SZ, IMG_SZ);
	IMG img3(IMG_SZ, IMG_SZ);

	img1.for_all_pixels([](PIX& p)
	{
		p = IMG::itkPixel(11);
	});

	img2.for_all_pixels([](PIX& p)
	{
		p = IMG::itkPixel(33);
	});

	auto start_chrono = std::chrono::system_clock::now();

	for (int k = 0; k<NB_ITER; ++k)
	{
		img3.parallel_for_all_pixels([&img1,&img2,&img3] (PIX& p, int i, int j)
		{
			IMG::DoublePixelEigen P = img1.pixelEigenAbsolute(i, j);
			IMG::DoublePixelEigen Q = img2.pixelEigenAbsolute(i, j);
			p = IMG::itkPixel((P+Q)/2);
		});
	}

	std::chrono::duration<double> elapsed_seconds = std::chrono::system_clock::now() - start_chrono;
	std::cout << "// uint8 -> double_eigen_pixels : " << elapsed_seconds.count() << " s." << std::endl;
	std::cout << "P : " << NICE(img3.pixelAbsolute(0,0)) << " / " << NICE(img3.pixelAbsolute(10,10)) << " / " << NICE(img3.pixelAbsolute(100,100)) << " / " << std::endl;
}

int main()
{
	bench_pixels();
	bench_pixels_double();
	bench_eigen_pixels();
	bench_eigen_pixels_2();
	bench_double_eigen_pixels();
	bench_parallel_eigen();

	return EXIT_SUCCESS;
}

