#include <iostream>
#include <cstdint>
#include <fstream>
#include <string>
#include <cstring>

#include "functions.cpp"
#include "../headers/prnt_bins_hd.h"

//Файл для печати бинарников

void prnt_bin_books(const std::string& bin_book /*= "student_book.bin"*/){
    file_exists(bin_book);
    std::ifstream fin(bin_book, std::ios::binary);
    //Блок проверок
    if (is_empty(bin_book)){
        throw "Students book is empty";
    }
    check_stream(fin, bin_book);

    Student_book book;
    while (fin.read(reinterpret_cast<char*>(&book), sizeof(Student_book))){
        std::cout << book.number << ";" << book.surname << ";" << book.name 
        << ";" << book.second_name << "\n";
    }

    fin.close();
}


void prnt_bin_marks(const std::string& bin_mark /*= "student_mark.bin"*/){
    file_exists(bin_mark);
    std::ifstream fin(bin_mark, std::ios::binary);
    //Блок проверок
    if (is_empty(bin_mark)){
        throw "Students book is empty";
    }
    check_stream(fin, bin_mark);

    Student_book_marks book;
    while (fin.read(reinterpret_cast<char*>(&book), sizeof(Student_data))){
        std::cout << book.group << ";" << book.number << ";" << "МА" 
        << ";" << book.subj[0] << "ГЕО" 
        << ";" << book.subj[1]<< "ПРОГ" 
        << ";" << book.subj[2] << "\n";
    }

    fin.close();
}


void prnt_bin_data(const std::string& bin_data /*= "students_data.bin"*/){
    file_exists(bin_data);
    std::ifstream fin(bin_data, std::ios::binary);
    //Блок проверок
    if (is_empty(bin_data)){
        throw "Students book is empty";
    }
    check_stream(fin, bin_data);

    Student_data data;
    while (fin.read(reinterpret_cast<char*>(&data), sizeof(Student_data))){
        std::cout << data.group << ";" << data.number << ";"
        << data.surname << ";" << "МА" 
        << ";" << data.subj[0] << "ГЕО" 
        << ";" << data.subj[1]<< "ПРОГ" 
        << ";" << data.subj[2] << "\n";
    }

    fin.close();
}


void prnt_bin_avg(const std::string& avg_bin /*= "average_score.bin"*/){
    file_exists(avg_bin);
    std::ifstream fin(avg_bin, std::ios::binary);
    //Блок проверок
    if (is_empty(avg_bin)){
        throw "Students book is empty";
    }
    check_stream(fin, avg_bin);

    Student_avg avg;
    while (fin.read(reinterpret_cast<char*>(&avg), sizeof(Student_avg))){
        std::cout << avg.group << ";" << avg.number << ";"
        << avg.surname << ";" << avg.avg << '\n';
    }

    fin.close();
}


void prnt_bin_exels(const std::string& bin_exels /*= "exelent_list.bin"*/){
    file_exists(bin_exels);
    std::ifstream fin(bin_exels, std::ios::binary);
    //Блок проверок
    if (is_empty(bin_exels)){
        throw "Students book is empty";
    }
    check_stream(fin, bin_exels);

    Excelent exel;
    while (fin.read(reinterpret_cast<char*>(&exel), sizeof(Excelent))){
        std::cout << exel.group << ";" << exel.number << ";"
        << exel.surname << '\n';
    }

    fin.close();
}


//Файл для перевода бинарников в текстовы

void txt_bin_books(const std::string& bin_book /*= "student_book.bin"*/,
                    const std::string& new_txt /*= "std_book.txt"*/){
    file_exists(bin_book);
    std::ifstream fin(bin_book, std::ios::binary);
    std::ofstream fout(new_txt);
    //Блок проверок
    if (is_empty(bin_book)){
        throw "Students book is empty";
    }
    check_stream(fin, bin_book);
    check_stream(fout, new_txt);

    Student_book book;
    while (fin.read(reinterpret_cast<char*>(&book), sizeof(Student_book))){
        fout << book.number << ";" << book.surname << ";" << book.name 
        << ";" << book.second_name << "\n";
    }

    fin.close();
    fout.close();
}


void txt_bin_marks(const std::string& bin_mark /*= "student_mark.bin"*/,
                    const std::string& new_txt /*= "std_mark.txt"*/){
    file_exists(bin_mark);
    std::ifstream fin(bin_mark, std::ios::binary);
    std::ofstream fout(new_txt);
    //Блок проверок
    if (is_empty(bin_mark)){
        throw "Students book is empty";
    }
    check_stream(fin, bin_mark);
    check_stream(fout, new_txt);

    Student_book_marks book;
    while (fin.read(reinterpret_cast<char*>(&book), sizeof(Student_data))){
        fout << book.group << ";" << book.number << ";" << "МА" 
        << ";" << book.subj[0] << "ГЕО" 
        << ";" << book.subj[1]<< "ПРОГ" 
        << ";" << book.subj[2] << "\n";
    }

    fin.close();
    fout.close();
}


void txt_bin_data(const std::string& bin_data /*= "students_data.bin"*/,
                    const std::string& new_txt /*= "std_data.txt"*/){
    file_exists(bin_data);
    std::ifstream fin(bin_data, std::ios::binary);
    std::ofstream fout(new_txt);
    //Блок проверок
    if (is_empty(bin_data)){
        throw "Students book is empty";
    }
    check_stream(fin, bin_data);
    check_stream(fout, new_txt);

    Student_data data;
    while (fin.read(reinterpret_cast<char*>(&data), sizeof(Student_data))){
        fout << data.group << ";" << data.number << ";"
        << data.surname << ";" << "МА" 
        << ";" << data.subj[0] << "ГЕО" 
        << ";" << data.subj[1]<< "ПРОГ" 
        << ";" << data.subj[2] << "\n";
    }

    fin.close();
    fout.close();
}


void txt_bin_avg(const std::string& avg_bin /*= "average_score.bin"*/,
                const std::string& new_txt /*= "std_avg.txt"*/){
                    file_exists(avg_bin);
    std::ifstream fin(avg_bin, std::ios::binary);
    std::ofstream fout(new_txt);
    //Блок проверок
    if (is_empty(avg_bin)){
        throw "Students book is empty";
    }
    check_stream(fin, avg_bin);
    check_stream(fout, new_txt);

    Student_avg avg;
    while (fin.read(reinterpret_cast<char*>(&avg), sizeof(Student_avg))){
        fout << avg.group << ";" << avg.number << ";"
        << avg.surname << ";" << avg.avg << '\n';
    }

    fin.close();
    fout.close();
}


void txt_bin_exels(const std::string& bin_exels /*= "exelent_list.bin"*/,
                    const std::string& new_txt /*= "std_exel.txt"*/){
                        file_exists(bin_exels);
    std::ifstream fin(bin_exels, std::ios::binary);
    std::ofstream fout(new_txt);
    //Блок проверок
    if (is_empty(bin_exels)){
        throw "Students book is empty";
    }
    check_stream(fin, bin_exels);
    check_stream(fout, new_txt);

    Excelent exel;
    while (fin.read(reinterpret_cast<char*>(&exel), sizeof(Excelent))){
        fout << exel.group << ";" << exel.number << ";"
        << exel.surname << '\n';
    }

    fin.close();
    fout.close();
}
