#ifndef WINNERCOUNTER_H
#define WINNERCOUNTER_H

#include "HashTable.h"
#include <string>

class WinnerCounter : public HashTable<std::string, int> {
    public:
        struct TopWinners {
            int number;
            std::string first;
            std::string second;
            std::string third;

            TopWinners() : number(0), first(""), second(""), third("") {}
        };

        WinnerCounter();
        WinnerCounter(const WinnerCounter &other);

        TopWinners getTopThreeWinners();
};

WinnerCounter::WinnerCounter() : HashTable<std::string, int>() {}

WinnerCounter::WinnerCounter(const WinnerCounter &other) : HashTable<std::string, int>(other) {}

WinnerCounter::TopWinners WinnerCounter::getTopThreeWinners(){
    TopWinners top;
    int first_value, second_value, third_value;
    for (auto& node : this->table) {
        if (node.status != OCCUPIED) continue;
        // рассмотрели менее 3х людей
        if (top.number < 3){
            switch (top.number) {
            case 0:
                first_value = node.value;
                top.first = node.key;
                break;
            case 1:
                second_value = node.value;
                top.second = node.key;
                break;
            case 2:
                third_value = node.value;
                top.third = node.key;
                break;
            }
            top.number++;
        }else if (node.value > third_value){
            third_value = node.value;
            top.third = node.key;
        }
        // есть 3 случая
        // --------------------------->
        // ---third---second---first---
        //          /\
        //         node

        // --------------------------->
        // ---third---second---first---
        //                  /\
        //                 node

        // --------------------------->
        // ---third---second---first---
        //                          /\
        //                         node
        // рассматривать их по отдельности нет смысла
        // просто если вдруг оказалось, что second > first, то меняем их местами
        
        if (top.number == 3 && third_value > second_value){
            std::swap(third_value, second_value);
            std::swap(top.third, top.second);
        }
        if (top.number >= 2 && second_value > first_value){
            std::swap(second_value, first_value);
            std::swap(top.second, top.first);
        }
    }
    return top;
}

#endif