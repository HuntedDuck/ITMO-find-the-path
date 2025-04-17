#include <iostream>
#include<postprocessing_and_output.h>

int main(){
    std::cout<<"Enter the date you need (usage: YYYY-MM-DD)"<<std::endl;
    std::string input_date;
    std::cin>>input_date;

    output(postprocessing(input_date));
    return 0;
}