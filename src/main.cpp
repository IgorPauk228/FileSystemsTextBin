#include <iostream>
#include "functions.cpp"

int main(){
    try{
        genere_all_data(100);
        create_bin();
        add_surnames();
        add_avg_score();
        list_of_undr_achv();
        sort_underscored();
        print_norm_sort();
        create_stats(4);
        create_sorted_stats(5);
        create_exlnts_list();
    }
    catch (std::string msg){
        std::cout << msg << "\n";
    }
    return 0;
}