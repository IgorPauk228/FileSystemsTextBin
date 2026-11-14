#include <iostream>
#include <cstdint>
#include <fstream>
#include <string>

#ifndef GENERATE_H
#define GENERATE_H

//Функции для генерирования файла

//Функция для генерации текстового файла с зачетками
//Принимает на вход имя файла и список фамилий
void genere_stdnts_list(const std::string* surnames, const std::string& filename = "student_book.txt");

//Генерация файла с оценками на основе предыдущего
//Принимает имена 2-х файлов - созданного с именами и номерами, и создаваемого
void genere_marks(const std::string& books_file = "student_book.txt", const std::string& marks_file = "student_marks.txt");


#endif