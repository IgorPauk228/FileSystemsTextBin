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

//Проверка на открытие(ofstream)
void open_input_file(std::ofstream& fin, const std::string& filename);

//Проверка потока(fstream)
void check_stream(std::fstream& fin, const std::string& filename);

//Проверка потока(ifstream)
void check_stream(std::ifstream& fin, const std::string& filename);

//Проверка потока(ofstream)
void check_stream(std::ofstream& fin, const std::string& filename);

// Проверяет наличие расширения .txt в конце строки.
void check_and_add_txt_extension(std::string& filename);

// Проверяет наличие расширения .bin в конце строки.
void check_and_add_bin_extension(std::string& filename);

#endif