#ifndef LAB2_H
#define LAB2_H

#include <iostream>
#include <vector>
#include <list>
#include <deque>
#include <set>
#include <map>
#include <algorithm>
#include <numeric>
#include <iterator>
#include <string>
#include <cctype>

// Задание 1: Заполнение и доступ к элементам. Обратные итераторы
void Task1();

// Задание 2: Вставка элементов
void Task2();

// Задание 3: Удаление элементов
void Task3();

// Задание 4: Итераторы и алгоритмы (арифметическая прогрессия)
void Task4();

// Задание 5: Алгоритмы поиска
void Task5();

// Задание 6: Базовые модифицирующие алгоритмы. Итераторы вставки
void Task6();

// Задание 7: Сортировка и слияние
void Task7();

// Задание 8: Численные алгоритмы (строки)
void Task8();

// Задание 9: Множества (multiset, includes)
void Task9();

// Задание 10: Отображения (multimap)
void Task10();

// Вспомогательные функции для проверки ввода и создания контейнеров
int GetValidatedInt(const std::string& prompt, bool positive_only = false, 
                    bool odd_check = false, bool even_check = false, int min_size = 0);
std::vector<int> InputIntVector(const std::string& prompt, std::size_t min_size = 0, 
                                 bool exact_size = false, std::size_t exact_size_value = 0, 
                                 bool odd_size = false, bool even_size = false);
std::list<int> InputIntList(const std::string& prompt, std::size_t min_size = 0, 
                             bool exact_size = false, std::size_t exact_size_value = 0);
std::deque<int> InputIntDeque(const std::string& prompt, std::size_t min_size = 0, 
                               bool exact_size = false, std::size_t exact_size_value = 0, 
                               bool even_size = false);
std::list<std::string> InputStringList(const std::string& prompt, std::size_t min_size = 0);

#endif  // LAB2_H
