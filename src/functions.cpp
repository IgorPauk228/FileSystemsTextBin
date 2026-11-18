#include <iostream>
#include <cstdint>
#include <fstream>
#include <string>
#include <cstring>
#include <check_hd.h>
#include <cctype>
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
    if(is_empty(stud_books))
    {
        throw "File is empty";
    }
    check_stream(fin,stud_books);
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
    if(is_empty(stud_marks))
    {
        throw "File is empty";
    }
    check_stream(fin,stud_marks);
    std::string temp{};
    std::ofstream bin_out(bin_name,std::ios::binary);
    while(std::getline(fin,temp))
    {
        size_t beg = 0;
        fill_sb(student_marks.group,temp,delim,beg);
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
                const std::string& new_bin_name /*= "students_data.bin"*/)
{
    char delim = ';';
    Student_data data;
    std::ofstream bin_out(new_bin_name,std::ios::binary);
//открываем и проверяем файл stud_books
    std::ifstream fin1(stud_books);
    file_exists(stud_books);
    if(is_empty(stud_books))
    {
        
        throw "File is empty";
    }
    check_stream(fin1,stud_books);
//открываем и проверяем файл stud_marks
    std::ifstream fin2(stud_marks);
    file_exists(stud_marks);
    if(is_empty(stud_marks))
    {
        throw "File is empty";
    }
    check_stream(fin2,stud_marks);

    std::string temp_books = "";
    while(std::getline(fin1,temp_books))
    {
        if(temp_books == ""){continue;}
        size_t beg = temp_books.find_first_of(delim);
        size_t books_number = stoi(temp_books.substr(0,beg));
        fill_sb(data.surname,temp_books,delim,++beg);
        std::string temp_marks = "";
        std::getline(fin2,temp_marks);
        size_t marks_number = stoi(number_marks(temp_marks));
        bool flag = true;
        while(books_number != marks_number)
        {
            if(fin2.eof())
            {
                fin2.seekg(0,std::ios::beg);
                flag = false;
                break;
            }
            std::getline(fin2,temp_marks);
            if(temp_marks == ""){continue;}
            marks_number = stoi(number_marks(temp_marks));
        }
        if(flag)
        {
            beg = 0;
            fill_sb(data.group,temp_marks,delim,beg);
            fill_sb(data.number,temp_marks,delim,beg);
            for(size_t i = 0;i < 3;++i)
            {
                fill_sb(data.subj[i],temp_marks,delim,beg);
                fill_sb(data.marks[i],temp_marks,delim,beg);
            }
            bin_out.write((char*)&data,sizeof(data));
            fin2.seekg(0,std::ios::beg);
        }
    }
    bin_out.close();
    fin1.close();
    fin2.close();
}
//выделяет номер зачетки в строках файла stud_marks.txt
std::string number_marks(const std::string& stud_marks)
{
    size_t beg = stud_marks.find_first_of(';');
    size_t end = stud_marks.find_first_of(';',++beg);
    std::string number = stud_marks.substr(beg,end-beg);
    return number;
}
//Функция вычисления среднего балла студента
//Формируется новый файл(пользователь сам выбирает название)  
//Аргументы функции - название бинарника зачетками и оценками и фамилиями, название нового файла
void add_avg_score(const std::string& stud_data, const std::string& new_bin_name /*= "average_score.bin*/);


//Функция формирования списка неуспевающих
//Формируется новый файл(пользователь сам выбирает название)  
//Аргументы функции - название бинарника зачетками и оценками и фамилиями, название нового файла
void list_of_undr_achv(const std::string& stud_data, const std::string& new_bin_name = "under_achievment_list.bin") {
    try {
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
    catch (const std::string& e) {
        std::cerr << e;
    }
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
void sort_underscored(const std::string& und_data, const std::string& new_bin_name = "sorted_und_achieve.bin");


//Функция печати до сортировки и после
//Аргументы функции - название бинарника неуспевающих и его отсортированной версии
void print_norm_sort(const std::string& und_data, const std::string& sort_und_data);

//Лексикографический компаратор
int alphabet_comp(const void* a, const void* b){
    Student_data pa = *(const Student_data*)(a);
    Student_data pb = *(const Student_data*)(b);
    return std::strcmp(pa.surname, pb.surname);
}

//Сортировка бинарника группы по алфавиту
void alphabet_sort(const std::string& filename, uint32_t size){
    std::ifstream fin(filename, std::ios::binary);
    Student_data* std_arr = new Student_data[size];
    Student_data std_data;

    uint32_t counter = 0;
    
    while (fin.read(reinterpret_cast<char*>(&std_data), sizeof(Student_data)) && counter < size){
        std_arr[counter++] = std_data;
    }

    qsort(std_arr, size, sizeof(Student_data), alphabet_comp);
}

//Функция формирования ведомости по алфавиту для группы
//Формируется новый файл(пользователь сам выбирает название)  
//Аргументы функции - название бинарника зачетками и оценками и фамилиями, название нового файла
void create_stats(const std::string& stud_data, const std::string& new_bin_name /*= "stats_sort_lex.bin"*/,
                    size_t group_number){
    std::ofstream fout(new_bin_name, std::ios::binary);
    std::ifstream fin(stud_data, std::ios::binary);

    uint32_t size = 0;
    Student_data std_data;

    while (fin.read(reinterpret_cast<char*>(&std_data), sizeof(Student_data))){
        if (std_data.group == group_number){
            fout.write(reinterpret_cast<char*>(&std_data), sizeof(Student_data));
            ++size;
        }
    }
    
    alphabet_sort(new_bin_name, size);
}


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

