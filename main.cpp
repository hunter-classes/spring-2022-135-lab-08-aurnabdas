#include <iostream>
#include <array> 
#include <string> 
#include <cassert>
#include "imageio.h"
#include "alter.h"

const std::array<std::string, 2> names_of_images = {"image1.pgm", "image2.pgm"};
const std::array<std::string, 6> task = {"a", "b", "c", "d", "e", "f"}; 

typedef void (*Functions) (std::string name, std::string out_name); 


int main() { 
    std::string out; 

    Functions funcs[] = {invert, invert_half, box, frame, scale, pixelate}; 

    for(int i = 0; i < task.size(); i++) {
        for(int j = 0; j < names_of_images.size(); j++) {
            std::string out = "task" + task[i] + "-" + names_of_images[j];
            funcs[i](names_of_images[j], out);
        }
    }

    return 0;
}