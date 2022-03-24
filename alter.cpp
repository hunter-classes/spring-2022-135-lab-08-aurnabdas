#include <iostream> 
#include <fstream>
#include <cassert>
#include <vector>
#include <string> 
#include "alter.h"
#include "imageio.h"


void invert(std::string name, std::string out_name) 
{
    int ht, wd; 
    int image[MAX_H][MAX_W];
    readImage(name, image, ht, wd); 

    int out[MAX_H][MAX_W];

    for (int row = 0; row < ht; row++) 
	{
		for (int col = 0; col < wd; col++) 
		{
			assert(image[row][col] < 256);
			assert(image[row][col] >= 0);
            int temp = image[row][col];
            temp = 255 - temp; 
			out[row][col] = temp; 
		}
	}

    writeImage(out_name, out, ht, wd);
    return;
}

void invert_half(std::string name, std::string out_name) 
{
    int ht, wd; 
    int image[MAX_H][MAX_W];
    readImage(name, image, ht, wd); 

    int out[MAX_H][MAX_W];

    for (int row = 0; row < ht; row++) 
	{
		for (int col = 0; col < wd / 2; col++) 
		{
			assert(image[row][col] < 256);
			assert(image[row][col] >= 0);
			out[row][col] = image[row][col];
		}

        for (int col = wd / 2; col < wd; col++) 
		{
			assert(image[row][col] < 256);
			assert(image[row][col] >= 0);
            int temp = image[row][col];
            temp = 255 - temp; 
			out[row][col] = temp;
		}
	}

    writeImage(out_name, out, ht, wd);
    return;
}

void box(std::string name, std::string out_name) 
{
    int ht, wd; 
    int image[MAX_H][MAX_W];
    readImage(name, image, ht, wd); 

    int out[MAX_H][MAX_W];

    for (int row = 0; row < ht; row++) 
	{
		for (int col = 0; col < wd; col++) 
		{
			assert(image[row][col] < 256);
			assert(image[row][col] >= 0);
        
            if((ht / 4) * 3 >= row && wd / 4 <= col && ht / 4 <= row && (wd / 4) * 3 >= col) 
			{ 
                out[row][col] = 255;
            } else {
                out[row][col] = image[row][col];
            }
        }
    }

    writeImage(out_name, out, ht, wd);
    return;
}

void frame(std::string name, std::string out_name) 
{
    int ht, wd; 
    int image[MAX_H][MAX_W];
    readImage(name, image, ht, wd); 

    int out[MAX_H][MAX_W];

    for (int row = 0; row < ht; row++) 
	{
		for (int col = 0; col < wd; col++) 
		{
			assert(image[row][col] < 256);
			assert(image[row][col] >= 0);

            if((ht / 4 <= row && ht / 4 + 1 > row && wd / 4 <= col && (wd / 4) * 3 >= col) || 
			((ht / 4) * 3 >= row && (ht / 4) * 3 - 1 < row && wd / 4 <= col && (wd / 4) * 3 >= col) || 
			(wd / 4 <= col && wd / 4 + 1 > col && ht / 4 <= row && (ht / 4) * 3 >= row) || 
			((wd / 4) * 3 - 1 < col && (wd / 4) * 3 >= col && ht / 4 <= row && (ht / 4) * 3 >= row)) 
			{ 
                out[row][col] = 255; 
            } else { 
                out[row][col] = image[row][col];
            }
		}
	}

    writeImage(out_name, out, ht, wd);
    return; 
}

void scale(std::string name, std::string out_name) 
{
    int ht, wd; 
    int image[MAX_H][MAX_W];
    readImage(name, image, ht, wd); 

    std::ofstream ostr;
	ostr.open(out_name);
	if (ostr.fail()) {
		std::cout << "Unable\n";
		exit(1);
	};

    std::vector<int> row_vector; 

    
	ostr << "P2" << std::endl;
	
	ostr << wd * 2 << ' ';
	ostr << ht * 2 << std::endl;
	ostr << 255 << std::endl;

	for (int row = 0; row < ht; row++) 
	{
		for (int col = 0; col < wd; col++) 
		{
			assert(image[row][col] < 256);
			assert(image[row][col] >= 0);

			ostr << image[row][col] << ' ';
            ostr << image[row][col] << ' ';

            row_vector.push_back(image[row][col]);
            row_vector.push_back(image[row][col]);
		}

        for(int i = 0; i < row_vector.size(); i++) 
		{
            ostr << row_vector[i] << " ";
        }

        ostr << std::endl;
        row_vector.clear();
	}

	ostr.close();
}

void pixelate(std::string name, std::string out_name) 
{
    int ht, wd; 
    int image[MAX_H][MAX_W];
    readImage(name, image, ht, wd); 

    std::ofstream ostr;
	ostr.open(out_name);
	if (ostr.fail()) {
		std::cout << "Unable\n";
		exit(1);
	};


	ostr << "P2" << std::endl;
	ostr << wd << ' ';
	ostr << ht << std::endl;
	ostr << 255 << std::endl;

	std::vector<int> nums; 

	for (int row = 0; row < ht; row += 2) 
	{
		for (int col = 0; col < wd; col += 2) 
		{
			assert(image[row][col] < 256);
			assert(image[row][col] >= 0);

			// pixel is based on 2x2 squares 

			double temp = (image[row][col] + image[row][col + 1] + image[row + 1][col] + image[row + 1][col + 1]) / 4;

			if(temp - (int)temp != 0) 
			{ 
				temp = (int)temp + 1; 
			}
			
			nums.push_back((int)temp);
			nums.push_back((int)temp); 

		}
		
		for(int j = 0; j < 2; j++) 
		{ 
			for(int i = 0; i < wd; i++) 
			{ 
				ostr << nums[i] << ' ';
				ostr << std::endl;
			}
		}

		nums.clear();
	}

	ostr.close();
}