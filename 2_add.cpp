/*
 * @author: GaoJun
 * @date: 20180308
 * @description: Homework_1
 * */

#include <iostream>
#include <cstdlib>

int main(int argc, char** argv)
{
    if (argc != 3)
    {
        std::cout << "Error\n";
    }
    else
    {
        std::cout << atoi(argv[1]) + atoi(argv[2]) << std::endl;
    }
}
