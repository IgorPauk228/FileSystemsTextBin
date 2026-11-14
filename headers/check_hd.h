#include <iostream>
#include <cstdint>
#include <fstream>
#include <string>

#ifndef HEADERS_CHECK
#define HEADERS_CHECK

//Функции проверки
//Существование файла
void file_exists(const std::string& filename);

//Проверка на пустоту
bool is_empty(const std::string& filename);

//Проверка на открытие(ifstream)
void open_input_file(std::ifstream& fin, const std::string& filename);

//Проверка на открытие(fstream)
void open_input_file(std::fstream& fin, const std::string& filename);

//Проверка на принадлежность файла к классу бинарных
bool is_bin(const std::string& filename);

#endif