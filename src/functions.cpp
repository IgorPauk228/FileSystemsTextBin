#include <iostream>
#include <cstdint>
#include <fstream>
#include <string>
#include <cstring>

#include "generate.cpp"
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
void create_bin_books(const std::string& stud_books /*= "student_book.txt"*/,
                 const std::string& bin_name /*= "student_book.bin"*/)
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
        if (temp.empty()){
            continue;
        }
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
void create_bin_marks(const std::string& stud_marks /*= "student_marks.txt"*/, const std::string& bin_name /*= "student_mark.bin"*/)
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
        if (temp.empty()){
            continue;
        }
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
void create_bin(const std::string& stud_books /*= "student_book.txt"*/, 
                const std::string& stud_marks /*= "student_marks.txt"*/, 
                const std::string& bin_name_book /*= "student_book.bin"*/, 
                const std::string& bin_name_mark /*= "student_mark.bin"*/)
{
    create_bin_books(stud_books);
    create_bin_marks(stud_marks);
}

//Функция подсоединения фамилий студентов к их оценкам
//Формируется новый файл(пользователь сам выбирает название)  
//Аргументы функции - название бинарников с зачетками и оценками, название нового файла           
void add_surnames(const std::string& stud_books /*= "student_book.bin"*/, 
                const std::string& stud_marks /*= "student_mark.bin"*/, 
                const std::string& new_bin_name /*= "students_data.bin"*/)
{
     //открываем и проверяем stud_books
    std::ifstream fin_books (stud_books,std::ios::binary);
    file_exists(stud_books);
    if(is_empty(stud_books))
    {
        throw "File is empty";
    }
    check_stream(fin_books,stud_books);
    //открываем и проверяем stud_marks
    std::ifstream fin_marks (stud_marks,std::ios::binary);
    file_exists(stud_marks);
    if(is_empty(stud_marks))
    {
        throw "File is empty";
    }
    check_stream(fin_marks,stud_marks);
    
    std::ofstream fout_data (new_bin_name,std::ios::binary);
    file_exists(new_bin_name);
    check_stream(fout_data,new_bin_name);
    Student_book books;
    Student_book_marks marks;
    Student_data data;
    while(fin_books.read((char*)&books, sizeof(Student_book)))
    {
        bool flag = true;
        strcpy(data.surname,books.surname);
        fin_marks.read((char*)&marks, sizeof(Student_book_marks));
        while(books.number != marks.number)
        {
                if(fin_marks.eof())
            {
                fin_marks.clear();
                fin_marks.seekg(0,std::ios::beg);
                flag = false;
                break;
            }
            fin_marks.read((char*)&marks, sizeof(Student_book_marks));
        }
        if(!flag)
        {
            continue;
        }
        data.group = marks.group;
        data.number = marks.number;
        for(uint8_t i = 0;i < 3;++i)
        {
            data.marks[i] = marks.marks[i];
            strcpy(data.subj[i],marks.subj[i]);
        }
        fout_data.write((char*)&data,sizeof(Student_data));
    }
    fin_books.close();
    fin_marks.close();
    fout_data.close();
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
void add_avg_score(const std::string& stud_books /*= "student_book.bin"*/, 
                const std::string& stud_marks /*= "student_mark.bin"*/,
                const std::string& new_bin_name /*=students_data.bin"*/,
                const std::string& avg_bin /*= "average_score.bin"*/)
{
    add_surnames(stud_books,stud_marks);  // создаем бинарник для считывания балла
    std::ofstream fout(avg_bin,std::ios::binary);
    std::ifstream fin(new_bin_name,std::ios::binary); //открываем и проверяем созданный бинарник
    file_exists(new_bin_name);
    if(is_empty(new_bin_name))
    {
        throw "File is empty";
    }
    check_stream(fin,new_bin_name);
    Student_data data;
    Student_avg student_avg;
    while(fin.read((char*)&data, sizeof(Student_data)))
    {
        student_avg.group = data.group;
        student_avg.number = data.number;
        strcpy(student_avg.surname,data.surname);
        student_avg.avg = static_cast<double>(data.marks[0] + data.marks[1] + data.marks[2])/3.0;
        fout.write((char*)&student_avg,sizeof(Student_avg));
    }
    fin.close();
    fout.close();
}

//Функция формирования списка неуспевающих
//Формируется новый файл(пользователь сам выбирает название)  
//Аргументы функции - название бинарника зачетками и оценками и фамилиями, название нового файла
void list_of_undr_achv(const std::string& stud_data /*= "students_data.bin"*/, 
                    const std::string& new_bin_name /* = "under_achievment_list.bin" */) {
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

        Student_data data;

        //читаем и записываем наши замечательные структуры
        while (fin.read(reinterpret_cast<char*>(&data), sizeof(Student_data))) {

            if (is_underachieving(data)) {
                fout.write(reinterpret_cast<const char*>(&data), sizeof(Student_data));
            }
        }

        fin.close();
        fout.close();
}

//доп функция для проверки неуспеваемости, неудовлетворительными считаются <= 4
bool is_underachieving(const Student_data& marks_data) {
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
void sort_underscored(const std::string& und_data /* = "under_achievment_list.bin" */, 
                    const std::string& new_bin_name /* = "sorted_und_achieve.bin" */)
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

        const size_t pair_size = sizeof(Student_data);
        size_t count = static_cast<size_t>(file_size) / pair_size;

        // Выделяем два динамических массива
        Student_data* datas = new Student_data[count];

        // Читаем данные
        for (size_t i = 0; i < count; ++i) {
            fin.read(reinterpret_cast<char*>(&datas[i]), sizeof(Student_data));
        }
        fin.close();
        
        // Сортировка пузырьком по фамилии (одновременно переставляем в обоих массивах)
        for (size_t i = 0; i < count - 1; ++i) {
            for (size_t j = 0; j < count - i - 1; ++j) {
                if (std::strcmp(datas[j].surname, datas[j + 1].surname) > 0) {
                    // Меняем местами данные зачетки
                    Student_data temp_data = datas[j];
                    datas[j] = datas[j + 1];
                    datas[j + 1] = temp_data;

                }
            }
        }

        // Записываем отсортированные данные
        std::ofstream fout;
        fout.open(new_bin_name, std::ios::binary);
        check_stream(fout, new_bin_name);

        for (size_t i = 0; i < count; ++i) {
            fout.write(reinterpret_cast<const char*>(&datas[i]), sizeof(Student_data));
        }
        fout.close();

        // Освобождаем память
        delete[] datas;
}


//Функция печати до сортировки и после
//Аргументы функции - название бинарника неуспевающих и его отсортированной версии
void print_norm_sort(const std::string& und_data /* = "under_achievment_list.bin" */, 
                    const std::string& sort_und_data /* = "sorted_und_achieve.bin" */) {
    std::cout <<'\t' << " НЕОТСОРТИРОВАННЫЙ список неуспевающих " << '\t' << '\n';

    if (file_exists(und_data), !is_empty(und_data)) 
    { 
        // file_exists выбросит исключение, если файла нет
        std::ifstream fin1;
        fin1.open(und_data, std::ios::binary);
        check_stream(fin1, und_data);

        Student_data data;
        int num = 1;

        while (fin1.read(reinterpret_cast<char*>(&data), sizeof(Student_data))) {

            std::cout << num++ << ". " << data.surname
                << " | Зач. книжка: " << data.number
                << " | Группа: " << data.group << std::endl;
            std::cout << "   Оценки: ";
            for (size_t i = 0; i < 3; ++i) {
                std::cout << data.subj[i] << ": " << data.marks[i] << "  ";
            }
            std::cout << std::endl;
        }
        fin1.close();
    }
    else {
        std::cout << "Файл пуст или не найден." << std::endl;
    }

    std::cout << '\n' << '\t' << "ОТСОРТИРОВАННЫЙ список по неуспеваемости" << '\t' << '\n';

    if (file_exists(sort_und_data), !is_empty(sort_und_data)) {
        std::ifstream fin2;
        fin2.open(sort_und_data, std::ios::binary);
        check_stream(fin2, sort_und_data);

        Student_data data;
        int num = 1;

        while (fin2.read(reinterpret_cast<char*>(&data), sizeof(Student_data))) {

            std::cout << num++ << ". " << data.surname
                << " | Зач. книжка: " << data.number
                << " | Группа: " << data.group << std::endl;
            std::cout << "   Оценки: ";
            for (size_t i = 0; i < 3; ++i) {
                std::cout << data.subj[i] << ": " << data.marks[i] << "  ";
            }
            std::cout << std::endl;
        }
        fin2.close();
    }
    else {
        std::cout << "Файл пуст или не найден." << std::endl;
    }
}

//Лексикографический компаратор
int alphabet_comp(const void* a, const void* b){
    Student_data pa = *(const Student_data*)(a);
    Student_data pb = *(const Student_data*)(b);
    return std::strcmp(pa.surname, pb.surname);
}

//Сортировка бинарника группы по алфавиту
void alphabet_sort(const std::string& filename, uint32_t size){
    file_exists(filename);
    std::ifstream fin(filename, std::ios::binary);
    if (is_empty(filename)){
        std::string msg = "Students book " + filename + " is empty";
        throw msg;
    }
    check_stream(fin, filename);

    Student_data* std_arr = new Student_data[size];
    Student_data std_data;

    uint32_t counter = 0;
    
    while (fin.read(reinterpret_cast<char*>(&std_data), sizeof(Student_data)) && counter < size){
        std_arr[counter++] = std_data;
    }

    qsort(std_arr, size, sizeof(Student_data), alphabet_comp);

    std::ofstream fout(filename, std::ios::binary);
    check_stream(fout, filename);
    for (uint32_t i = 0; i < size; ++i){
        fout.write(reinterpret_cast<char*>(&std_arr[i]), sizeof(Student_data));
    }

    delete[] std_arr;
    fout.close();
    fin.close();
}

//Функция формирования ведомости по алфавиту для группы
//Формируется новый файл(пользователь сам выбирает название)  
//Аргументы функции - название бинарника зачетками и оценками и фамилиями, название нового файла
void create_stats(size_t group_number,
                const std::string& stud_data /* = "students_data.bin"*/, 
                const std::string& new_bin_name /*= "stats_sort_lex.bin"*/){
    file_exists(stud_data);
    std::ofstream fout(new_bin_name, std::ios::binary);
    std::ifstream fin(stud_data, std::ios::binary);
    //Блок проверок
    if (is_empty(stud_data)){
        std::string msg = "Students book " + stud_data + " is empty";
        throw msg;
    }
    check_stream(fin, stud_data);
    check_stream(fout, new_bin_name);

    uint32_t size = 0;
    Student_data std_data;

    while (fin.read(reinterpret_cast<char*>(&std_data), sizeof(Student_data))){
        if (std_data.group == group_number){
            fout.write(reinterpret_cast<char*>(&std_data), sizeof(Student_data));
            ++size;
        }
    }

    fout.close();
    fin.close();

    alphabet_sort(new_bin_name, size);
    
}

//Компаратор по среднему баллу
int score_comp(const void* a, const void* b){
    Student_avg pa = *(const Student_avg*)(a);
    Student_avg pb = *(const Student_avg*)(b);
    return pa.avg < pb.avg;
}


//Сортировка бинарника группы по убыванию среднего балла
void med_score_sort(const std::string& filename, uint32_t size){
    file_exists(filename);
    std::ifstream fin(filename, std::ios::binary);
    if (is_empty(filename)){
        throw "Students book is empty";
    }
    check_stream(fin, filename);

    Student_avg* std_arr = new Student_avg[size];
    Student_avg std_avg;

    uint32_t counter = 0;
    
    while (fin.read(reinterpret_cast<char*>(&std_avg), sizeof(Student_avg)) && counter < size){
        std_arr[counter++] = std_avg;
    }

    qsort(std_arr, size, sizeof(Student_avg), score_comp);

    std::ofstream fout(filename, std::ios::binary);
    check_stream(fout, filename);
    for (uint32_t i = 0; i < size; ++i){
        fout.write(reinterpret_cast<char*>(&std_arr[i]), sizeof(Student_avg));
    }
    
    delete[] std_arr;
    fout.close();
    fin.close();
}

//Функция формирования ведомости по среднему баллу(убывание) для заданной группы
//Формируется новый файл(пользователь сам выбирает название)  
//Аргументы функции - название бинарника зачетками и оценками и фамилиями, название нового файла
void create_sorted_stats(size_t group_number,
                    const std::string& stud_avg /* = "average_score.bin"*/, 
                    const std::string& new_bin_name /*= "stats_sort_score.bin"*/){
    file_exists(stud_avg);

    std::ofstream fout(new_bin_name, std::ios::binary);
    std::ifstream fin(stud_avg, std::ios::binary);

    if (is_empty(stud_avg)){
        std::string msg = "Students book " + stud_avg + " is empty";
        throw msg;
    }
    check_stream(fin, stud_avg);
    check_stream(fout, new_bin_name);

    uint32_t size = 0;
    Student_data std_avg;

    while (fin.read(reinterpret_cast<char*>(&std_avg), sizeof(Student_avg))){
        if (std_avg.group == group_number){
            fout.write(reinterpret_cast<char*>(&std_avg), sizeof(Student_avg));
            ++size;
        }
    }
    fout.close();
    fin.close();

    med_score_sort(new_bin_name, size);
    
}


//Функция формирования списка отличников
//Формируется новый файл(пользователь сам выбирает название)  
//Аргументы функции - название бинарника зачетками и оценками и фамилиями, название нового файла
void create_exlnts_list(const std::string& stud_data /*= "students_data.bin"*/, 
                        const std::string& new_bin_name /*= "exelent_list.bin"*/){
    file_exists(stud_data);

    std::ofstream fout(new_bin_name, std::ios::binary);
    std::ifstream fin(stud_data, std::ios::binary);

    if (is_empty(stud_data)){
        throw "Students book is empty";
    }
    check_stream(fin, stud_data);
    check_stream(fout, new_bin_name);

    Student_data std_data;

    bool is_exel = true;

    while (fin.read(reinterpret_cast<char*>(&std_data), sizeof(Student_data))){
        is_exel = true;
        for (size_t i = 0; i < 3; ++i){
            if (std_data.marks[i] < 8){
                is_exel = false;
            }
        }
        if (is_exel) fout.write(reinterpret_cast<char*>(&std_data), sizeof(Student_data));
    }
    
    fout.close();
    fin.close();
}

