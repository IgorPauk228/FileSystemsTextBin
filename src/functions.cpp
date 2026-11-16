#include <iostream>
#include <cstdint>
#include <fstream>
#include <string>
#include <cstring>
#include <check_hd.h>
#include "../headers/functions_hd.h"
//Сами функции
//Замечания(далее не оговаривается):
//1)Если файл уже существует, то он перезаписывается с нуля
//2)Названия новых файлов задаются как параметры по умолчанию
//3)Программа, если пользователь не указал формат, сама его дописывает по контексту

//заполняет числовые поля структур Student_book/Student_book_marks 
void fill_sb(size_t& info,std::string& temp,char delim,size_t& beg)
{
    size_t end = temp.find_first_of(delim,beg);
    if(end == std::string::npos)
    {
        end = temp.length();
    }
    info = stoi(temp.substr(beg,end-beg));
    beg = ++end;
}

//заполняет поля-строки структур Student_book/Student_book_marks 
void fill_sb(char(&info)[20],std::string& temp,char delim,size_t& beg)
{
        size_t end = temp.find_first_of(delim,beg);
        if(end == std::string::npos)
        {
            end = temp.length();
        }
        std::string part = temp.substr(beg,end-beg);
        strcpy(info,part.c_str());
        beg = ++end;
}

//Функции формирования бинарных файлов на основе исходных
//Формирования бинарника зачеток
//Пользователь передает имя файла с зачетками и имя для нового файла
void create_bin_books(const std::string& stud_books, const std::string& bin_name /*= "student_book.bin"*/)
{
    Student_book student_book;
    std::ifstream fin(stud_books);
    char delim = ';';
    file_exists(stud_books);
    is_empty(stud_books);
    open_input_file(fin,stud_books);
    std::string temp{};
    std::ofstream bin_out(bin_name,std::ios::binary);
    while(std::getline(fin,temp))
    {
        size_t beg = 0;
        fill_sb(student_book.number,temp,delim,beg);
        fill_sb(student_book.surname,temp,delim,beg);
        fill_sb(student_book.name,temp,delim,beg);
        fill_sb(student_book.second_name,temp,delim,beg);
        bin_out.write((char*)&student_book,sizeof(student_book));
    }
    bin_out.close();
    fin.close();
}
//Формирование бинарника с оценками
//Пользователь передает имя файла с оценками и имя для нового файла
void create_bin_marks(const std::string& stud_marks, const std::string& bin_name /*= "student_mark.bin"*/)
{
    Student_book_marks student_marks;
    std::ifstream fin(stud_marks);
    char delim = ';';
    file_exists(stud_marks);
    is_empty(stud_marks);
    open_input_file(fin,stud_marks);
    std::string temp{};
    std::ofstream bin_out(bin_name,std::ios::binary);
    while(std::getline(fin,temp))
    {
        size_t beg = 0;
        fill_sb(student_marks.groop,temp,delim,beg);
        fill_sb(student_marks.number,temp,delim,beg);
        for(size_t i = 0;i < 3;++i)
        {
            fill_sb(student_marks.subj[i],temp,delim,beg);
            fill_sb(student_marks.marks[i],temp,delim,beg);
        }
        bin_out.write((char*)&student_marks,sizeof(student_marks));
    }
    bin_out.close();
    fin.close();
}
//Функция формирования 2-х бинарников
//Пользователь передает имя файлов с зачетками и оценками и имена 2-х новых файлов
void create_bin(const std::string& stud_books, const std::string& stud_marks, 
                const std::string& bin_name_book /*= "student_book.bin"*/, const std::string& bin_name_mark /*= "student_mark.bin"*/)
{
    create_bin_books(stud_books);
    create_bin_marks(stud_marks);
}

//Функция подсоединения фамилий студентов к их оценкам
//Формируется новый файл(пользователь сам выбирает название)  
//Аргументы функции - название бинарников с зачетками и оценками, название нового файла           
void add_surnames(const std::string& stud_books, const std::string& stud_marks, 
                const std::string& new_bin_name /*= "students_data.bin"*/);


//Функция вычисления среднего балла студента
//Формируется новый файл(пользователь сам выбирает название)  
//Аргументы функции - название бинарника зачетками и оценками и фамилиями, название нового файла
void add_avg_score(const std::string& stud_data, const std::string& new_bin_name /*= "average_score.bin*/);


//Функция формирования списка неуспевающих
//Формируется новый файл(пользователь сам выбирает название)  
//Аргументы функции - название бинарника зачетками и оценками и фамилиями, название нового файла
void list_of_undr_achv(const std::string& stud_data, const std::string& new_bin_name /*= "under_achievment_list.bin"*/);


//Функция сортировки 
//Формируется новый файл(пользователь сам выбирает название)  
//Аргументы функции - название бинарника неуспевающих, название нового файла
void sort_underscored(const std::string& und_data, const std::string& new_bin_name = "sorted_und_achieve.bin");


//Функция печати до сортировки и после
//Аргументы функции - название бинарника неуспевающих и его отсортированной версии
void print_norm_sort(const std::string& und_data, const std::string& sort_und_data);


//Функция формирования ведомости по алфавиту
//Формируется новый файл(пользователь сам выбирает название)  
//Аргументы функции - название бинарника зачетками и оценками и фамилиями, название нового файла
void create_stats(const std::string& stud_data, const std::string& new_bin_name /*= "stats_sort_lex.bin"*/);


//Функция формирования ведомости по среднему баллу(возрастание)
//Формируется новый файл(пользователь сам выбирает название)  
//Аргументы функции - название бинарника зачетками и оценками и фамилиями, название нового файла
void create_sorted_stats(const std::string& stud_data, const std::string& new_bin_name /*= "stats_sort_score.bin"*/);


//Функция формирования ведомости по среднему баллу(убывание)
//Формируется новый файл(пользователь сам выбирает название)  
//Аргументы функции - название бинарника зачетками и оценками и фамилиями, название нового файла
void create_rev_sorted_stats(const std::string& stud_data, const std::string& new_bin_name /*= "stats_revsort_score.bin"*/);


//Функция формирования списка отличников
//Формируется новый файл(пользователь сам выбирает название)  
//Аргументы функции - название бинарника зачетками и оценками и фамилиями, название нового файла
void create_exlnts_list(const std::string& stud_data, const std::string& new_bin_name /*= "exelent_list.bin"*/);

