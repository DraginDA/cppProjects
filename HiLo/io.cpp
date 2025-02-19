
#include "io.h"
#include <iostream>
#include <limits> // for std::numeric_limits

// Очистка  постороннего ввода:
void ignoreLine()
{
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}


// Проверит и исправит ошибки при извлечении данных или переполнении (а также удалит лишние данные):
// возвращает true, если извлечение не удалось, false в противном случае
bool clearFailedExtraction()
{
    // Проверяем на неудачное извлечение
    if (!std::cin) // Если предыдущее извлечение не удалось
    {
        if (std::cin.eof()) // Если поток был закрыт
        {
            std::exit(0); // Завершаем программу сейчас
        }
        
        // Обработаем ошибку
        std::cin.clear(); // Вернем std::cin в 'нормальный' режим работы
        ignoreLine();     // И удалим некорректный ввод
        return true;
    }
    
    return false;
}

// Мы можем проверить, есть ли нераспознанный ввод (кроме новой строки), следующим образом:
// возвращает значение true, если std::cin содержит не извлеченные входные данные в текущей строке, в противном случае значение false
bool hasUnextractedInput()
{
    return !std::cin.eof() && std::cin.peek() != '\n';
}
