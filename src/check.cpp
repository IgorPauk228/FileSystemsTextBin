#include <iostream>
#include <cstdint>
#include <fstream>
#include <string>

#include "../headers/check_hd.h"

//Функции проверки
//Существование файла
void file_exists(const std::string& filename){
    std::ifstream fin(filename);
    if (!fin.good()){
        throw "File " + filename + " not exists\n";
    }
}

//Проверка на пустоту
bool is_empty(const std::string& filename){
    std::ifstream file(filename);
    file.seekg(0, std::ios::end);
    return file.tellg() == 0;
}

//Проверка на открытие(ifstream)
void open_input_file(std::ifstream& fin, const std::string& filename){
    fin.open(filename);
    if (!fin.is_open()){
        throw "Can't open file: " + filename + "\n"; 
    }
    if (fin.fail()){
        throw "Error with open file: " + filename + "\n";
    }

    std::cout << "File " << filename << " succesfully opened\n";
}

//Проверка на открытие(fstream)
void open_input_file(std::fstream& fin, const std::string& filename){
    fin.open(filename);
    if (!fin.is_open()){
        throw "Can't open file: " + filename + "\n"; 
    }
    if (fin.fail()){
        throw "Error with open file: " + filename + "\n";
    }

    std::cout << "File " << filename << " succesfully opened\n";
}

//Проверка на открытие(ofstream)
void open_input_file(std::ofstream& fin, const std::string& filename){
    fin.open(filename);
    if (!fin.is_open()){
        throw "Can't open file: " + filename + "\n"; 
    }
    if (fin.fail()){
        throw "Error with open file: " + filename + "\n";
    }

    std::cout << "File " << filename << " succesfully opened\n";
}

