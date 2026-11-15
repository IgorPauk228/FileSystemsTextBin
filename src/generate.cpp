#include <iostream>
#include <cstdint>
#include <fstream>
#include <string>

#include "check.cpp"
#include "../headers/generate_hd.h"

//Функции для генерирования файла
//Структура для хранения наборов ФИО

//Инициализация структуры
void init_fios(fios_set& fios){
    fios.names = new std::string[10]{"Михаил", "Александр", "Лев", 
                                    "Дмитрий", "Максим", "Иван", 
                                    "Андрей", "Сергей", "Алексей", "Владимир"};
    fios.surnames = new std::string[10]{"Смирнов", "Петров", "Попов", 
                                    "Васильев", "Михайлов", "Федоров", 
                                    "Морозов", "Алексеев", "Семенов", "Егоров"};;
    fios.dad_names = new std::string[10]{"Иванович", "Андреевич", "Сергеевич", 
                                    "Алексеевич", "Владимирович", "Михаилович", 
                                    "Александрович", "Львович", "Дмитриевич", "Максимович"};;
    fios.names_qnt = 10;
    fios.sr_names_qnt = 10;
    fios.dd_names_qnt = 10;

}

//Очистка структуры
void clear_fios(fios_set& fios){
    delete[] fios.names;
    delete[] fios.surnames;
    delete[] fios.dad_names;
    fios.names = nullptr;
    fios.surnames = nullptr;
    fios.dad_names = nullptr;
    fios.names_qnt = 0;
    fios.sr_names_qnt = 0;
    fios.dd_names_qnt = 0;
}

//Функция для генерации рандомного числа
uint32_t rand_int(uint32_t min /* = 10000 */, uint32_t max /*= 99999*/){
    return rand() % (max - min + 1) + min;
}

//Функция для генерации текстового файла с зачетками
//Принимает на вход имя файла и список фамилий
void genere_stdnts_list(const fios_set& fios, uint32_t size, const std::string& filename /*= "student_book.txt" */){
    std::ofstream fout(filename);

    //Проверка на открытие
    open_input_file(fout, filename);

    uint32_t min_num = 45000;
    uint32_t delta = 3;

    fout << '\n';
    for (size_t i = 0; i < size; ++i){
        //Генерация рандомных данных студента
        fout << std::to_string(rand_int(min_num, min_num + delta)) << ';';
        fout << fios.surnames[rand_int(0, fios.sr_names_qnt - 1)] << ';';
        fout << fios.names[rand_int(0, fios.names_qnt - 1)] << ';';
        fout << fios.dad_names[rand_int(0, fios.sr_names_qnt - 1)] << '\n';

        min_num += delta + 1;
    }

    fout.close();

}

//Генерация файла с оценками на основе предыдущего
//Принимает имена 2-х файлов - созданного с именами и номерами, и создаваемого
void genere_marks(const std::string& books_file /*= "student_book.txt"*/, const std::string& marks_file /*= "student_marks.txt"*/){
    file_exists(books_file);

    std::ifstream fin(books_file);
    std::ofstream fout(marks_file);

    //Блок проверок
    is_empty(books_file);
    open_input_file(fin, books_file);
    open_input_file(fout, marks_file);


    std::string buff;
    while(std::getline(fin, buff)){
        //К номеру зачетки добавляются оценки и номер группы
        if (buff.empty()){
            fout << '\n';
            continue;
        }
        if (buff.length() < 5){
            throw "Invalid input file";
        }

        fout << std::to_string(rand_int(1, 7)) << ';';
        fout << buff.substr(0, 5) << ';';
        fout << "МА" << ';' << std::to_string(rand_int(1, 10)) << ';';
        fout << "ГЕО" << ';' << std::to_string(rand_int(1, 10)) << ';';
        fout << "ПРОГ" << ';' << std::to_string(rand_int(1, 10)) << '\n';

    }
    fout.close();
    fin.close();
}

//Функция для генерации 2-х файлов
void genere_all_data(uint32_t size, const std::string& books_file /*= "student_book.txt"*/, const std::string& marks_file /*= "student_marks.txt"*/){
    fios_set fios;
    init_fios(fios);

    genere_stdnts_list(fios, size, books_file);
    genere_marks(books_file, marks_file);

    clear_fios(fios);
}
