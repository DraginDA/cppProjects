#ifndef RANDOM_MT_H
#define RANDOM_MT_H
#include <chrono>
#include <random>

// Этот header-only пространство имен Random реализует 
//самозаполняющийся генератор Мерсенна-Твистера.
// Требуется C++17 или новее.
// Его можно #включить в любое количество файлов кода 
//(ключевое слово inline позволяет избежать нарушений ODR)
namespace Random
{
    // Возвращает инициализированный генератор Мерсенна-Твистера
    // Примечание: мы бы предпочли вернуть std::seed_seq 
    //(для инициализации std::mt19937), но std::seed нельзя скопировать, 
    //поэтому его нельзя вернуть по значению.
    // Вместо этого мы создадим std::mt19937, инициализируем его, 
    //а затем вернем std::mt19937 (который можно копировать).
    inline std::mt19937 generate()
    {
        std::random_device rd{};

        // Создаем seed_seq с помощью часов и 7 случайных чисел из std::random_device
        std::seed_seq ss{
            static_cast<std::seed_seq::result_type>(std::chrono::steady_clock::now().time_since_epoch().count()),
                rd(), rd(), rd(), rd(), rd(), rd(), rd() };

        return std::mt19937{ ss };
    }

    // Вот наш глобальный объект std::mt19937.
    // Ключевое слово inline означает, что у нас есть 
    //только один глобальный экземпляр для всей программы.
    inline std::mt19937 mt{ generate() }; // генерирует инициализированный std::mt19937 
    //и копирует его в наш глобальный объект

    // Генерирует случайное целое число между [min, max] (включительно)
    // * также обрабатывает случаи, когда два аргумента имеют разные типы, 
    //но могут быть преобразованы в int
    inline int get(int min, int max)
    {
        return std::uniform_int_distribution{min, max}(mt);
    }

    // Следующие шаблоны функций можно использовать 
    //для генерации случайных чисел в других случаях

    // Генерирует случайное значение между [min, max] (включительно)
    // * min и max должны иметь одинаковый тип
    // * возвращаемое значение имеет тот же тип, что и min и max
    // * Поддерживаемые типы:
    // *    short, int, long, long long
    // *    unsigned short, unsigned int, unsigned long, или unsigned long long
    // Пример вызова: Random::get(1L, 6L);             // возвращает long
    // Пример вызова: Random::get(1u, 6u);             // возвращает unsigned int
    template <typename T>
    T get(T min, T max)
    {
        return std::uniform_int_distribution<T>{min, max}(mt);
    }

    // Генерирует случайное значение между [min, max] (включительно)
    // * min и max могут иметь разные типы
    // * тип возвращаемого значения должен быть явно указан как аргумент шаблона
    // * min и max будут преобразованы в тип возвращаемого значения
    // Пример вызова: Random::get<std::size_t>(0, 6);  // возвращает std::size_t
    // Пример вызова: Random::get<std::size_t>(0, 6u); // возвращает std::size_t
    // Пример вызова: Random::get<std::int>(0, 6u);    // возвращает int
    template <typename R, typename S, typename T>
    R get(S min, T max)
    {
        return get<R>(static_cast<R>(min), static_cast<R>(max));
    }
}

#endif
