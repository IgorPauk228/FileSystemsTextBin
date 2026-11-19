#include <iostream>
#include <cstdint>
#include <fstream>
#include <string>
#include <cctype>

#ifndef FUNCTIONS_H
#define FUNCTIONS_H
//Сами функции
//Замечания(далее не оговаривается):
//1)Если файл уже существует, то он перезаписывается с нуля
//2)Названия новых файлов задаются как параметры по умолчанию
//3)Программа, если пользователь не указал формат, сама его дописывает по контексту

//структурка для зачетки
struct Student_book
{
    size_t number;
    char surname[20];
    char name[20];
    char second_name[20];
};

//структурка для оценок
struct Student_book_marks
{
    size_t group;
    size_t number;
    char subj[3][20];
    size_t marks[3];
};

//
struct Student_data
{
    size_t group;
    size_t number;
    char surname[20];
    char subj[3][20];
    size_t marks[3];
};

struct Student_avg
{
    size_t group;
    size_t number;
    char surname[20];
    double avg;
};

struct Excelent{
    size_t group;
    size_t number;
    char surname[20];
};


//заполняет числовые поля структур Student_book/Student_book_marks 
void fill_sb(size_t& info,std::string& temp,char delim,size_t& beg);

//заполняет поля-строки структур Student_book/Student_book_marks 
void fill_sb(char(&)[20],std::string&,char,size_t&);

//Функции формирования бинарных файлов на основе исходных
//Формирования бинарника зачеток
//Пользователь передает имя файла с зачетками и имя для нового файла
void create_bin_books(const std::string& stud_books = "student_book.txt", 
                    const std::string& bin_name = "student_book.bin");

//Формирование бинарника с оценками
//Пользователь передает имя файла с оценками и имя для нового файла
void create_bin_marks(const std::string& stud_marks = "student_mark.txt", 
                    const std::string& bin_name = "student_mark.bin");

//Функция формирования 2-х бинарников
//Пользователь передает имя файлов с зачетками и оценками и имена 2-х новых файлов
void create_bin(const std::string& stud_books = "student_book.txt", 
                const std::string& stud_marks = "student_mark.txt", 
                const std::string& bin_name_book = "student_book.bin", 
                const std::string& bin_name_mark = "student_mark.bin");


//Функция подсоединения фамилий студентов к их оценкам
//Формируется новый файл(пользователь сам выбирает название)  
//Аргументы функции - название бинарников с зачетками и оценками, название нового файла           
void add_surnames(const std::string& stud_books = "student_book.bin", 
                const std::string& stud_marks = "student_mark.bin", 
                const std::string& new_bin_name = "students_data.bin");

//Функция выделяет номер зачетки файла stud_marks.txt
std::string number_marks(const std::string&);

//Функция вычисления среднего балла студента
//Формируется новый файл(пользователь сам выбирает название)  
//Аргументы функции - название бинарника зачетками и оценками и фамилиями, название нового файла
void add_avg_score(const std::string& stud_books = "student_book.bin", 
                    const std::string& stud_marks = "student_mark.bin",
                    const std::string& new_bin_name = "students_data.bin",
                    const std::string& avg_bin = "average_score.bin");


//Функция формирования списка неуспевающих
//Формируется новый файл(пользователь сам выбирает название)  
//Аргументы функции - название бинарника зачетками и оценками и фамилиями, название нового файла
void list_of_undr_achv(const std::string& stud_data = "students_data.bin", 
                    const std::string& new_bin_name = "under_achievment_list.bin");

//доп функция для проверки неуспеваемости, неудовлетворительными считаются <= 4
bool is_underachieving(const Student_data& marks_data);

//Функция сортировки 
//Формируется новый файл(пользователь сам выбирает название)  
//Аргументы функции - название бинарника неуспевающих, название нового файла
void sort_underscored(const std::string& und_data = "under_achievment_list.bin", 
                    const std::string& new_bin_name = "sorted_und_achieve.bin");


//Функция печати до сортировки и после
//Аргументы функции - название бинарника неуспевающих и его отсортированной версии
void print_norm_sort(const std::string& und_data = "under_achievment_list.bin" , 
                    const std::string& sort_und_data = "sorted_und_achieve.bin");


//Лексикографический компаратор
int alphabet_comp(const void* a, const void* b);

//Сортировка бинарника группы по алфавиту
void alphabet_sort(const std::string& filename, uint32_t size);

//Функция формирования ведомости по алфавиту
//Формируется новый файл(пользователь сам выбирает название)  
//Аргументы функции - название бинарника зачетками и оценками и фамилиями, название нового файла
void create_stats(size_t group_number,
                const std::string& stud_data  = "students_data.bin", 
                const std::string& new_bin_name = "stats_sort_lex.bin");

//Компаратор по среднему баллу
int score_comp(const void* a, const void* b);

//Сортировка бинарника группы по убыванию среднего балла
void med_score_sort(const std::string& filename, uint32_t size);

//Функция формирования ведомости по среднему баллу(убывание)
//Формируется новый файл(пользователь сам выбирает название)  
//Аргументы функции - название бинарника зачетками и оценками и фамилиями, название нового файла
void create_sorted_stats(size_t group_number,
                        const std::string& stud_avg = "average_score.bin", 
                        const std::string& new_bin_name = "stats_sort_score.bin");




//Функция формирования списка отличников
//Формируется новый файл(пользователь сам выбирает название)  
//Аргументы функции - название бинарника зачетками и оценками и фамилиями, название нового файла
void create_exlnts_list(const std::string& stud_data = "students_data.bin", 
                        const std::string& new_bin_name = "exelent_list.bin");



#endif