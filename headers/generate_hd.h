#include <iostream>
#include <cstdint>
#include <fstream>
#include <string>

#ifndef GENERATE_H
#define GENERATE_H

//Функции для генерирования файла

//Функция для генерации текстового файла с зачетками
//Принимает на вход имя файла и список фамилий
void genere_stdnts_list(const std::string& filename, const std::string* surnames);

//Генерация файла с оценками на основе предыдущего
//Принимает имена 2-х файлов - созданного с именами и номерами, и создаваемого
void genere_marks(const std::string& marks_file, const std::string& books_file);


#endif