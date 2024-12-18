#include "HashTable.h"
#include "WinnerCounter.h"

#include <iostream>
#include <assert.h>
#include <string>

void assert_that(bool expression, std::string test_description){
    std::cout << test_description << " ";
    assert(
        expression == true
    );
    std::cout << "✅PASSED" << std::endl;
}

int main(){
    HashTable<std::string, int> h;
    
    assert_that(
        h.getNumberOfItems() == 0, 
        "размер коллекции, созданной конструктором по умолчанию, равен нулю"
    );
    
    h.insert("intern", 100000);
    assert_that(
        h.getNumberOfItems() == 1,
        "при добавлении нового значения размер увеличивается на единицу"
    );

    h.insert("intern", 90000);
    assert_that(
        h.getNumberOfItems() == 1,
        "при добавлении имеющегося значения размер остаётся прежним"
    );
    
    h.pop("intern");
    assert_that(
        h.getNumberOfItems() == 0,
        "при удалении имеющегося значения размер уменьшается на 1"
    );

    h.insert("intern", 85000);
    h.insert("juniour", 150000);
    h.pop("middle");
    assert_that(
        h.getNumberOfItems() == 2,
        "при удалении отсутствующего значения размер не изменяется"
    );

    HashTable<std::string, int> empty_h;
    h.clear();
    assert_that(
        empty_h == h,
        "непустая коллекция после удаления всех объектов равна коллекции, созданной при помощи конструктора по умолчанию"
    );

    h.insert("senior", 500000);
    assert_that(
        (h && empty_h) == empty_h,
        "при пересечении любой коллекции с пустой, оператор && возвращает пустую коллекцию"
    );

    assert_that(
        (h && h) == h,
        "при пересечении одинаковых коллекций, оператор && возвращает новую коллекцию, равную любой из них"
    );
    
    HashTable<std::string, int> copied_h;
    copied_h = h;

    assert_that(
        h == copied_h,
        "копия непустой коллекции равна оригиналу"
    );

    copied_h.insert("courier", 60000);
    assert_that(
        !(h == copied_h),
        "после вставки равенство нарушается"
    );

    h.insert("intern", 90000);
    h.insert("juniour", 150000);
    h.insert("middle", 250000);
    h.saveToFile("incomes.txt");

    HashTable<std::string, int> loaded_h;
    loaded_h.loadFromFile("incomes.txt");

    assert_that(
        h == loaded_h,
        "непустая коллекция, сохранённая в файл, равна новой коллекции, загруженной из того же файла"
    );

    WinnerCounter w_c;

    w_c.insert("Николай", 14);
    w_c.insert("Сергей", 4);
    w_c.insert("Артем", 15);
    w_c.insert("Изабель", 19);

    auto top_winners = w_c.getTopThreeWinners();
    assert_that(
        (
            top_winners.first == "Изабель" &&
            top_winners.second == "Артем" &&
            top_winners.third == "Николай" &&
            top_winners.number == 3
        ),
        "метод получения 3х наибольших по значению ключей: только добавление"
    );

    w_c.pop("Изабель");
    top_winners = w_c.getTopThreeWinners();
    assert_that(
        (
            top_winners.first == "Артем" &&
            top_winners.second == "Николай" &&
            top_winners.third == "Сергей" &&
            top_winners.number == 3
        ),
        "метод получения 3х наибольших по значению ключей: некоторые элементы удалены"
    );

    w_c.pop("Сергей");
    top_winners = w_c.getTopThreeWinners();
    assert_that(
        (
            top_winners.first == "Артем" &&
            top_winners.second == "Николай" &&
            top_winners.number == 2
        ),
        "метод получения 3х наибольших по значению ключей: меньше 3х участников"
    );
    std
    ::cout << "Все тесты прошли успешно!\nМожно идти трогать траву 🌿" << std::endl;
    return 0;
}