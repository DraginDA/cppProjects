#include "Random.h"
#include "io.h"
#include <iostream>
#include <string_view>
#include <cassert>


bool repeat()
{
    while (true)
    {
        char choice{};
        std::cout << "Хотите сыграть ещё раз (y/n)? ";
        std::cin >> choice;
        ignoreLine();
        
        switch (choice)
        {
        case 'y': return true;
        case 'n': return false;
        }
    }
    
    
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

int getGuess(int attempt, int min, int max)
{
    int num{};
    while (true)
    {
        std::cout << "Угадайте #" << attempt << ": ";
        std::cin >> num;
    
        bool success {std::cin};
        std::cin.clear();
        ignoreLine();

        if (!success || num < min || num > max)
            continue;
        
        return num;
    }
}

void HiLo(int attempt, int min, int max)
{ 
    const int rand {Random::get(min, max)};

    for (int i{1}; i<=attempt; ++i)
    {
        int num{getGuess(i, min, max)};
        
        if (getAnswer(num, rand))
            return;
    }

    std::cout << "К сожалению, вы проиграли. Правильное число - " << rand << '\n';
}

int getData(std::string_view str)
{
    int num{};
    do
    {
        std::cout << str;
        std::cin >> num;
    }while (clearFailedExtraction());

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
