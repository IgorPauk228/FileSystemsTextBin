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

//Открытие файла(ifstream)
void open_input_file(std::ifstream& fin, const std::string& filename){
    fin.open(filename);
    if (!fin.is_open()){
        std::string msg = "Can't open file: " + filename + "\n";
        throw msg;
    }
    if (fin.fail()){
        std::string msg = "Error with open file: " + filename + "\n";
        throw msg;
    }

    std::cout << "File " << filename << " succesfully opened\n";
}

//Открытие файла(fstream)
void open_input_file(std::fstream& fin, const std::string& filename){
    fin.open(filename);
    if (!fin.is_open()){
        std::string msg = "Can't open file: " + filename + "\n";
        throw msg;
    }
    if (fin.fail()){
        std::string msg = "Error with open file: " + filename + "\n";
        throw msg;
    }

    std::cout << "File " << filename << " succesfully opened\n";
}

//Открытие файла(ofstream)
void open_input_file(std::ofstream& fin, const std::string& filename){
    fin.open(filename);
    if (!fin.is_open()){
        std::string msg = "Can't open file: " + filename + "\n";
        throw msg;
    }
    if (fin.fail()){
        std::string msg = "Error with open file: " + filename + "\n";
        throw msg;
    }

    std::cout << "File " << filename << " succesfully opened\n";
}

//Проверка потока(ifstream)
void check_stream(std::ifstream& fin, const std::string& filename){
    if (!fin.is_open()){
        std::string msg = "Can't open file: " + filename + "\n";
        throw msg;
    }
    if (fin.fail()){
        std::string msg = "Error with open file: " + filename + "\n";
        throw msg;
    }

    std::cout << "File " << filename << " succesfully opened\n";
}

//Проверка потока(ofstream)
void check_stream(std::ofstream& fin, const std::string& filename){
    if (!fin.is_open()){
        std::string msg = "Can't open file: " + filename + "\n";
        throw msg;
    }
    if (fin.fail()){
        std::string msg = "Error with open file: " + filename + "\n";
        throw msg;
    }

    std::cout << "File " << filename << " succesfully opened\n";
}

//Проверка потока(fstream)
void check_stream(std::fstream& fin, const std::string& filename){
    if (!fin.is_open()){
        std::string msg = "Can't open file: " + filename + "\n";
        throw msg;
    }
    if (fin.fail()){
        std::string msg = "Error with open file: " + filename + "\n";
        throw msg;
    }

    std::cout << "File " << filename << " succesfully opened\n";
}

void check_and_add_extension(std::string& filename) {
    std::size_t len = filename.length();

    // достаточная ли длинна строка, чтоб содержать наше расширение
    // надо минимум 4 символа:)
    if (len >= 4) {
        // возьмем последние 4 символа строчки
        std::string ext = filename.substr(len - 4);

        // если у нас строчка заканчивается на .bin или .txt, то всё ок, ничего делать не надо
        if (ext == ".bin" || ext == ".txt") {
            return;
        }
    }

    // если подходящего расширения нет, добавляем .txt 
    // (если нужно .bin, просто заменим наше ".txt" на ".bin")
    filename += ".txt";
}