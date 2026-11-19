#include <iostream>
#include <cstdint>
#include <fstream>
#include <string>

#ifndef GENERATE_H
#define GENERATE_H

//Функции для генерирования файла
//Структура для хранения наборов ФИО(понадобятся для генерации)
struct fios_set{
    std::string* names;
    std::string* surnames;
    std::string* dad_names;
    uint32_t names_qnt;
    uint32_t sr_names_qnt;
    uint32_t dd_names_qnt;
};

//Инициализация структуры
void init_fios(fios_set& fios);

//Очистка структуры
void clear_fios(fios_set& fios);

//Функция для генерации рандомного числа
uint32_t rand_int(uint32_t min = 10000, uint32_t max = 99999);

//Функции для генерирования файла

//Функция для генерации текстового файла с зачетками
//Принимает на вход имя файла и список фамилий
void genere_stdnts_list(const std::string* surnames, const std::string& filename = "student_book.txt");

//Генерация файла с оценками на основе предыдущего
//Принимает имена 2-х файлов - созданного с именами и номерами, и создаваемого
void genere_marks(const std::string& books_file = "student_book.txt", const std::string& marks_file = "student_mark.txt");

//Функция для генерации 2-х файлов
void genere_all_data(uint32_t size, const std::string& books_file = "student_book.txt", 
                    const std::string& marks_file = "student_mark.txt");

#endif