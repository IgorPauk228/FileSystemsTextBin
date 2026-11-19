#include <iostream>
#include <clocale>
#include "prnt_bins.cpp"

int main(){
    srand(time(0));
    std::setlocale(LC_ALL, "Russian");
    try{
        genere_all_data(100);
        create_bin();
        prnt_bin_books();
        prnt_bin_marks();
        add_surnames();
        prnt_bin_data();
        add_avg_score();
        prnt_bin_avg();
        list_of_undr_achv();
        sort_underscored();
        print_norm_sort();
        create_stats(3);
        prnt_bin_data("stats_sort_lex.bin");
        create_sorted_stats(4);
        prnt_bin_avg("stats_sort_score.bin");
        create_exlnts_list();
        prnt_bin_data("exelent_list.bin");
    }
    catch (std::string msg){
        std::cout << msg << "\n";
    }
    return 0;
}