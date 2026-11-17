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
    size_t groop;
    size_t number;
    char subj[3][20];
    size_t marks[3];
};

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
void list_of_undr_achv(const std::string& stud_data, const std::string& new_bin_name /* = "under_achievment_list.bin" */) {
        //существует ли исходный файл
        file_exists(stud_data);

        //открываем входной файл в бинарном режиме
        std::ifstream fin;
        fin.open(stud_data, std::ios::binary);
        check_stream(fin, stud_data); 

        //открываем выходной файл в бинарном режиме
        std::ofstream fout;
        fout.open(new_bin_name, std::ios::binary);
        check_stream(fout, new_bin_name);

        Student_book book;
        Student_book_marks marks;

        //читаем и записываем наши замечательные структуры
        while (fin.read(reinterpret_cast<char*>(&book), sizeof(Student_book)) &&
            fin.read(reinterpret_cast<char*>(&marks), sizeof(Student_book_marks))) {

            if (is_underachieving(marks)) {
                fout.write(reinterpret_cast<const char*>(&book), sizeof(Student_book));
                fout.write(reinterpret_cast<const char*>(&marks), sizeof(Student_book_marks));
            }
        }

        fin.close();
        fout.close();
}

//доп функция для проверки неуспеваемости, неудовлетворительными считаются <= 4
bool is_underachieving(const Student_book_marks& marks_data) {
    for (size_t i = 0; i < 3; ++i) {
        if (marks_data.marks[i] <= 4) { // есть ли неудовлетворительные отметки
            return true;
        }
    }
    return false;
}


//Функция сортировки 
//Формируется новый файл(пользователь сам выбирает название)  
//Аргументы функции - название бинарника неуспевающих, название нового файла
void sort_underscored(const std::string& und_data, const std::string& new_bin_name /* = "sorted_und_achieve.bin" */)
{
        file_exists(und_data);

        // если файл пустой, то мы просто создаем пустой выходной файл и выходим
        if (is_empty(und_data)) {
            std::ofstream fout;
            fout.open(new_bin_name, std::ios::binary);
            check_stream(fout, new_bin_name);
            fout.close();
            return;
        }

        std::ifstream fin;
        fin.open(und_data, std::ios::binary);
        check_stream(fin, und_data);

        // Определяем размер файлика
        fin.seekg(0, std::ios::end);
        std::streamsize file_size = fin.tellg();
        fin.seekg(0, std::ios::beg);

        const size_t pair_size = sizeof(Student_book) + sizeof(Student_book_marks);
        size_t count = static_cast<size_t>(file_size) / pair_size;

        // Выделяем два динамических массива
        Student_book* books = new Student_book[count];
        Student_book_marks* marks_arr = new Student_book_marks[count];

        // Читаем данные
        for (size_t i = 0; i < count; ++i) {
            fin.read(reinterpret_cast<char*>(&books[i]), sizeof(Student_book));
            fin.read(reinterpret_cast<char*>(&marks_arr[i]), sizeof(Student_book_marks));
        }
        fin.close();

        // Сортировка пузырьком по фамилии (одновременно переставляем в обоих массивах)
        for (size_t i = 0; i < count - 1; ++i) {
            for (size_t j = 0; j < count - i - 1; ++j) {
                if (std::strcmp(books[j].surname, books[j + 1].surname) > 0) {
                    // Меняем местами данные зачетки
                    Student_book temp_book = books[j];
                    books[j] = books[j + 1];
                    books[j + 1] = temp_book;

                    // Синхронно меняем местами данные об оценках
                    Student_book_marks temp_marks = marks_arr[j];
                    marks_arr[j] = marks_arr[j + 1];
                    marks_arr[j + 1] = temp_marks;
                }
            }
        }

        // Записываем отсортированные данные
        std::ofstream fout;
        fout.open(new_bin_name, std::ios::binary);
        check_stream(fout, new_bin_name);

        for (size_t i = 0; i < count; ++i) {
            fout.write(reinterpret_cast<const char*>(&books[i]), sizeof(Student_book));
            fout.write(reinterpret_cast<const char*>(&marks_arr[i]), sizeof(Student_book_marks));
        }
        fout.close();

        // Освобождаем память
        delete[] books;
        delete[] marks_arr;
}


//Функция печати до сортировки и после
//Аргументы функции - название бинарника неуспевающих и его отсортированной версии
void print_norm_sort(const std::string& und_data, const std::string& sort_und_data) {
        std::cout <<'\t' << " НЕОТСОРТИРОВАННЫЙ список неуспевающих " << '\t' << '\n';

        file_exists(und_data);

        if (!is_empty(und_data)) 
        { 
            // file_exists выбросит исключение, если файла нет
            std::ifstream fin1;
            fin1.open(und_data, std::ios::binary);
            check_stream(fin1, und_data);

            Student_book book;
            Student_book_marks marks;
            int num = 1;

            while (fin1.read(reinterpret_cast<char*>(&book), sizeof(Student_book)) &&
                fin1.read(reinterpret_cast<char*>(&marks), sizeof(Student_book_marks))) {

                std::cout << num++ << ". " << book.surname << " " << book.name << " " << book.second_name
                    << " | Зач. книжка: " << book.number
                    << " | Группа: " << marks.groop << '\n';
                std::cout << "   Оценки: ";
                for (size_t i = 0; i < 3; ++i) {
                    std::cout << marks.subj[i] << ": " << marks.marks[i] << "  ";
                }
                std::cout << '\n';
            }
            fin1.close();
        }
        else {
            std::cout << "Файл пуст или не найден." << '\n';
        }

        std::cout << '\n' << '\t' << "ОТСОРТИРОВАННЫЙ список по неуспеваемости" << '\t' << '\n';

        file_exists(sort_und_data);

        if (!is_empty(sort_und_data)) {
            std::ifstream fin2;
            fin2.open(sort_und_data, std::ios::binary);
            check_stream(fin2, sort_und_data);

            Student_book book;
            Student_book_marks marks;
            int num = 1;

            while (fin2.read(reinterpret_cast<char*>(&book), sizeof(Student_book)) &&
                fin2.read(reinterpret_cast<char*>(&marks), sizeof(Student_book_marks))) {

                std::cout << num++ << ". " << book.surname << " " << book.name << " " << book.second_name
                    << " | Зач. книжка: " << book.number
                    << " | Группа: " << marks.groop << '\n';
                std::cout << "   Оценки: ";
                for (size_t i = 0; i < 3; ++i) {
                    std::cout << marks.subj[i] << ": " << marks.marks[i] << "  ";
                }
                std::cout << '\n';
            }
            fin2.close();
        }
        else {
            std::cout << "Файл пуст или не найден." << '\n';
        }
}

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

