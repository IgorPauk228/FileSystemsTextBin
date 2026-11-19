#include <iostream>
#include <cstdint>
#include <fstream>
#include <string>
#include <cstring>

#include "functions.cpp"
#include "../headers/prnt_bins_hd.h"

//Файл для печати бинарников

void prnt_bin_books(const std::string& bin_book /*= "student_book.bin"*/){

}


void prnt_bin_marks(const std::string& bin_mark /*= "student_mark.bin"*/);


void prnt_bin_data(const std::string& bin_data /*= "students_data.bin"*/);


void prnt_bin_avg(const std::string& avg_bin /*= "average_score.bin"*/);


void prnt_bin_exels(const std::string& bin_exels /*= "exelent_list.bin"*/);


//Файл для перевода бинарников в текстовы

void prnt_bin_books(const std::string& bin_book /*= "student_book.bin"*/,
                    const std::string& new_txt /*= "std_book.txt"*/);


void prnt_bin_marks(const std::string& bin_mark /*= "student_mark.bin"*/,
                    const std::string& new_txt /*= "std_mark.txt"*/);


void prnt_bin_data(const std::string& bin_data /*= "students_data.bin"*/,
                    const std::string& new_txt /*= "std_data.txt"*/);


void prnt_bin_avg(const std::string& avg_bin /*= "average_score.bin"*/,
                const std::string& new_txt /*= "std_avg.txt"*/);


void prnt_bin_exels(const std::string& bin_exels /*= "exelent_list.bin"*/,
                    const std::string& new_txt /*= "std_exel.txt"*/);
