#include "Random.h"
#include <iostream>
#include <string_view>

bool repeat()
{
    char choice{};
    std::cout << "Хотите сыграть ещё раз (y/n)? ";
    std::cin >> choice;
    
    return (choice == 'y');
}

bool getAnswer(int num, int rand)
{
    if (num < rand)
    {
        std::cout << "Ваше предположение слишком мало." << '\n';
        return 0;
    }
    else if (num > rand)
    {
        std::cout << "Ваше предположение слишком велико." << '\n';
        return 0;
    }
    else
    {
        std::cout << "Верно! Вы победили!" << '\n';
        return 1;
    }
    return 0;
}

void HiLo(int attempt, int min, int max)
{ 
    const int rand {Random::get(min, max)};
    
    int num{};
    for (int i{1}; i<=attempt; ++i)
    {
        std::cout << "Угадайте #" << i << ": ";
        std::cin >> num;
        
        if (getAnswer(num, rand))
            return;
    }

    std::cout << "К сожалению, вы проиграли. Правильное число - " << rand << '\n';
    
}

int getData(std::string_view str)
{
    std::cout << str;
    int num{};
    std::cin >> num;

    return num;
}

int main()
{
    const int attempt{getData("Введите количество попыток: ")};
    const int min{getData("Введите min значение: ")};
    const int max{getData("Введите max значение: ")};
    std::cout << "Давайте сыграем в игру. Я загадал число от "
              << min << " до " << max << ". У вас есть "
              << attempt << " попыток угадать, что это за число" << '\n';
    
    do
    {
        HiLo(attempt, min, max);
    }while (repeat());

    std::cout << "Спасибо вам за игру.";

    return 0;
}
