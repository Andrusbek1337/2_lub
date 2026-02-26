#include "lab2.h"

#include <limits>
#include <sstream>

// Вспомогательная функция для проверки ввода числа
int GetValidatedInt(const std::string& prompt, bool positive_only, bool odd_check, 
                     bool even_check, int min_size) {
  int value;
  while (true) {
    std::cout << prompt;
    std::cin >> value;

    if (std::cin.fail()) {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cout << "Ошибка: необходимо ввести целое число. Повторите ввод.\n";
      continue;
    }

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (positive_only && value <= 0) {
      std::cout << "Ошибка: число должно быть положительным. Повторите ввод.\n";
      continue;
    }

    if (odd_check && value % 2 == 0) {
      std::cout << "Ошибка: число должно быть нечетным. Повторите ввод.\n";
      continue;
    }

    if (even_check && value % 2 != 0) {
      std::cout << "Ошибка: число должно быть четным. Повторите ввод.\n";
      continue;
    }

    if (min_size > 0 && value < min_size) {
      std::cout << "Ошибка: число должно быть не меньше " << min_size 
                << ". Повторите ввод.\n";
      continue;
    }

    break;
  }
  return value;
}

// Вспомогательная функция для ввода вектора целых чисел
std::vector<int> InputIntVector(const std::string& prompt, std::size_t min_size, 
                                  bool exact_size, std::size_t exact_size_value, 
                                  bool odd_size, bool even_size) {
  std::vector<int> result;
  int n;
  std::string line;

  std::cout << prompt;

  // Сначала определяем размер, если нужно
  if (min_size > 0 || exact_size || odd_size || even_size) {
    std::string size_prompt = "Введите количество элементов";
    if (exact_size) {
      size_prompt += " (должно быть равно " + std::to_string(exact_size_value) + ")";
    } else if (min_size > 0) {
      size_prompt += " (не менее " + std::to_string(min_size) + ")";
    }
    if (odd_size) size_prompt += " (нечетное)";
    if (even_size) size_prompt += " (четное)";
    size_prompt += ": ";

    n = GetValidatedInt(size_prompt, true, odd_size, even_size, min_size);

    if (exact_size && static_cast<std::size_t>(n) != exact_size_value) {
      std::cout << "Ошибка: количество элементов должно быть равно " 
                << exact_size_value << ". Будем использовать " << exact_size_value << ".\n";
      n = static_cast<int>(exact_size_value);
    }

    std::cout << "Введите " << n << " целых чисел через пробел: ";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, line);
    std::istringstream iss(line);
    int num;
    for (int i = 0; i < n && iss >> num; ++i) {
      result.push_back(num);
    }

    if (result.size() < static_cast<std::size_t>(n)) {
      std::cout << "Введено недостаточно чисел. Заполняем нулями недостающие.\n";
      while (result.size() < static_cast<std::size_t>(n)) {
        result.push_back(0);
      }
    }
  } else {
    // Просто ввод с консоли
    std::getline(std::cin, line);
    std::istringstream iss(line);
    int num;
    while (iss >> num) {
      result.push_back(num);
    }
  }

  return result;
}

// Вспомогательная функция для ввода списка целых чисел
std::list<int> InputIntList(const std::string& prompt, std::size_t min_size, 
                              bool exact_size, std::size_t exact_size_value) {
  std::vector<int> vec = InputIntVector(prompt, min_size, exact_size, exact_size_value);
  return std::list<int>(vec.begin(), vec.end());
}

// Вспомогательная функция для ввода дека целых чисел
std::deque<int> InputIntDeque(const std::string& prompt, std::size_t min_size, 
                                bool exact_size, std::size_t exact_size_value, 
                                bool even_size) {
  std::vector<int> vec = InputIntVector(prompt, min_size, exact_size, exact_size_value, 
                                          false, even_size);
  return std::deque<int>(vec.begin(), vec.end());
}

// Вспомогательная функция для ввода списка строк (английских слов)
std::list<std::string> InputStringList(const std::string& prompt, std::size_t min_size) {
  std::list<std::string> result;
  int n;
  std::string line;

  std::cout << prompt;
  n = GetValidatedInt("Введите количество слов: ", true, false, false, min_size);

  std::cout << "Введите " << n << " английских слов через пробел: ";
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  std::getline(std::cin, line);
  std::istringstream iss(line);
  std::string word;
  for (int i = 0; i < n && iss >> word; ++i) {
    result.push_back(word);
  }

  if (result.size() < static_cast<std::size_t>(n)) {
    std::cout << "Введено недостаточно слов. Заполняем пустыми строками недостающие.\n";
    while (result.size() < static_cast<std::size_t>(n)) {
      result.push_back("");
    }
  }

  return result;
}

// Задание 1: Заполнение и доступ к элементам. Обратные итераторы
void Task1() {
  std::cout << "\n=== Задание 1: Заполнение и доступ к элементам. "
            << "Обратные итераторы ===\n";

  std::list<int> l = InputIntList("Введите набор целых чисел "
                                   "(введите числа через пробел): ", 0);

  if (l.empty()) {
    std::cout << "Список пуст.\n";
    return;
  }

  std::cout << "Исходный порядок: ";
  for (std::list<int>::iterator it = l.begin(); it != l.end(); ++it) {
    std::cout << *it << " ";
  }
  std::cout << std::endl;

  std::cout << "Обратный порядок: ";
  for (std::list<int>::reverse_iterator rit = l.rbegin(); rit != l.rend(); ++rit) {
    std::cout << *rit << " ";
  }
  std::cout << std::endl;
}

// Задание 2: Вставка элементов
void Task2() {
  std::cout << "\n=== Задание 2: Вставка элементов ===\n";

  std::vector<int> v = InputIntVector("Введите вектор V с четным количеством элементов: ", 
                                       2, false, 0, false, true);
  std::deque<int> d = InputIntDeque("Введите дек D с четным количеством элементов: ", 
                                     2, false, 0, true);

  std::size_t half_d = d.size() / 2;
  std::size_t half_v = v.size() / 2;

  // Добавить в конец вектора первую половину элементов дека (в исходном порядке)
  v.insert(v.end(), d.begin(), std::next(d.begin(), half_d));

  // Добавить в начало дека вторую половину элементов вектора (в обратном порядке)
  d.insert(d.begin(), std::make_reverse_iterator(std::next(v.begin(), half_v)), 
           std::make_reverse_iterator(v.begin()));

  std::cout << "Результат:\n";
  std::cout << "Вектор V: ";
  for (std::vector<int>::const_iterator it = v.begin(); it != v.end(); ++it) {
    std::cout << *it << " ";
  }
  std::cout << "\nДек D: ";
  for (std::deque<int>::const_iterator it = d.begin(); it != d.end(); ++it) {
    std::cout << *it << " ";
  }
  std::cout << std::endl;
}

// Задание 3: Удаление элементов
void Task3() {
  std::cout << "\n=== Задание 3: Удаление элементов ===\n";

  std::vector<int> v = InputIntVector("Введите вектор V с нечетным количеством элементов "
                                       "(N ≥ 5): ", 5, false, 0, true);

  int n = v.size();
  int start = (n - 3) / 2;  // индекс первого из трех средних

  v.erase(v.begin() + start, v.begin() + start + 3);

  std::cout << "Результат после удаления трех средних элементов: ";
  for (std::vector<int>::const_iterator it = v.begin(); it != v.end(); ++it) {
    std::cout << *it << " ";
  }
  std::cout << std::endl;
}

// Задание 4: Итераторы и алгоритмы (арифметическая прогрессия)
void Task4() {
  std::cout << "\n=== Задание 4: Итераторы и алгоритмы (арифметическая прогрессия) ===\n";

  double a, d;
  int n;

  std::cout << "Введите первый элемент прогрессии A: ";
  while (!(std::cin >> a)) {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Ошибка: введите число: ";
  }

  std::cout << "Введите разность прогрессии D: ";
  while (!(std::cin >> d)) {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Ошибка: введите число: ";
  }

  std::cout << "Введите количество членов N (> 0): ";
  n = GetValidatedInt("", true);

  std::vector<double> progression(n);
  double current = a;
  std::generate_n(progression.begin(), n, [&current, d]() {
    double val = current;
    current += d;
    return val;
  });

  std::cout << "Первые " << n << " членов арифметической прогрессии: ";
  std::copy(progression.begin(), progression.end(), 
            std::ostream_iterator<double>(std::cout, " "));
  std::cout << std::endl;
}

// Задание 5: Алгоритмы поиска
void Task5() {
  std::cout << "\n=== Задание 5: Алгоритмы поиска ===\n";

  std::vector<int> v = InputIntVector("Введите вектор V с четным количеством элементов: ", 
                                       2, false, 0, false, true);

  std::size_t half = v.size() / 2;
  std::vector<int>::iterator first_half_end = v.begin() + half;
  std::vector<int>::iterator second_half_begin = v.begin() + half;

  // Ищем в первой половине элемент, который есть во второй половине
  std::vector<int>::iterator it = std::find_first_of(v.begin(), first_half_end, 
                                                      second_half_begin, v.end());

  if (it != first_half_end) {
    // Нашли такой элемент, вставляем перед ним 0
    v.insert(it, 0);
    std::cout << "Вектор после вставки 0: ";
  } else {
    std::cout << "Элемент не найден. Вектор не изменен: ";
  }

  for (std::vector<int>::const_iterator cit = v.begin(); cit != v.end(); ++cit) {
    std::cout << *cit << " ";
  }
  std::cout << std::endl;
}

// Задание 6: Базовые модифицирующие алгоритмы. Итераторы вставки
void Task6() {
  std::cout << "\n=== Задание 6: Базовые модифицирующие алгоритмы. "
            << "Итераторы вставки ===\n";

  std::list<int> l = InputIntList("Введите список L, содержащий не менее 10 элементов: ", 10);

  int k = GetValidatedInt("Введите число K (0 < K < 5): ", true);
  while (k >= 5) {
    std::cout << "K должно быть меньше 5. Повторите ввод: ";
    k = GetValidatedInt("", true);
  }

  std::list<int> result;

  // Копируем первые 5 элементов и циклически сдвигаем вправо на K
  std::list<int> first5;
  std::list<int>::iterator it = l.begin();
  for (int i = 0; i < 5; ++i) {
    first5.push_back(*it);
    ++it;
  }

  // Циклический сдвиг вправо
  std::rotate(first5.begin(), std::prev(first5.end(), k), first5.end());

  // Вставляем в конец результата
  std::copy(first5.begin(), first5.end(), std::back_inserter(result));

  // Копируем последние 5 элементов исходного списка
  std::list<int> last5;
  std::list<int>::reverse_iterator rit = l.rbegin();
  for (int i = 0; i < 5; ++i) {
    last5.push_front(*rit);
    ++rit;
  }

  // Циклический сдвиг влево
  std::rotate(last5.begin(), std::next(last5.begin(), k), last5.end());

  // Вставляем в начало результата
  std::copy(last5.begin(), last5.end(), std::front_inserter(result));

  // Вставляем оставшиеся элементы (если есть) из середины исходного списка
  std::list<int>::iterator middle_begin = std::next(l.begin(), 5);
  std::list<int>::iterator middle_end = std::prev(l.end(), 5);
  std::copy(middle_begin, middle_end, std::back_inserter(result));

  std::cout << "Результат: ";
  for (std::list<int>::const_iterator cit = result.begin(); cit != result.end(); ++cit) {
    std::cout << *cit << " ";
  }
  std::cout << std::endl;
}

// Задание 7: Сортировка и слияние
void Task7() {
  std::cout << "\n=== Задание 7: Сортировка и слияние ===\n";

  std::vector<int> v = InputIntVector("Введите вектор V с четным количеством элементов: ", 
                                       2, false, 0, false, true);

  std::size_t half = v.size() / 2;
  std::vector<int> sorted_half(half);

  // Копируем первую половину отсортированного вектора
  std::partial_sort_copy(v.begin(), v.end(), sorted_half.begin(), sorted_half.end());

  // Вставляем в конец
  v.insert(v.end(), sorted_half.begin(), sorted_half.end());

  std::cout << "Результат: ";
  for (std::vector<int>::const_iterator it = v.begin(); it != v.end(); ++it) {
    std::cout << *it << " ";
  }
  std::cout << std::endl;
}

// Задание 8: Численные алгоритмы (строки)
void Task8() {
  std::cout << "\n=== Задание 8: Численные алгоритмы (строки) ===\n";

  std::list<std::string> l = InputStringList("Введите список английских слов: ", 2);

  std::deque<std::string> d;
  d.push_back("");  // Заглушка для adjacent_difference

  // Лямбда-функция для обработки соседних элементов
  std::adjacent_difference(l.begin(), l.end(), std::back_inserter(d), 
    [](const std::string& left, const std::string& right) {
      if (left.empty() || right.empty()) return std::string("");
      return std::string(1, left[0]) + std::string(1, right.back());
    });

  // Удаляем первый элемент (заглушку)
  if (!d.empty()) {
    d.erase(d.begin());
  }

  std::cout << "Результат в деке D: ";
  for (std::deque<std::string>::const_iterator it = d.begin(); it != d.end(); ++it) {
    std::cout << *it << " ";
  }
  std::cout << std::endl;
}

// Задание 9: Множества (multiset, includes)
void Task9() {
  std::cout << "\n=== Задание 9: Множества (multiset, includes) ===\n";

  std::vector<int> v0 = InputIntVector("Введите вектор V0: ", 0);
  int n = GetValidatedInt("Введите количество векторов V1...VN (> 0): ", true);

  std::multiset<int> ms0(v0.begin(), v0.end());
  int count = 0;

  for (int i = 1; i <= n; ++i) {
    std::cout << "Введите вектор V" << i << ": ";
    std::vector<int> vi = InputIntVector("", 0);
    std::multiset<int> ms(vi.begin(), vi.end());

    if (std::includes(ms.begin(), ms.end(), ms0.begin(), ms0.end())) {
      count++;
    }
  }

  std::cout << "Количество векторов, содержащих все элементы V0: " << count << std::endl;
}

// Задание 10: Отображения (multimap)
void Task10() {
  std::cout << "\n=== Задание 10: Отображения (multimap) ===\n";

  std::vector<int> v = InputIntVector("Введите вектор V: ", 0);

  std::multimap<int, int> m;

  for (std::vector<int>::const_iterator it = v.begin(); it != v.end(); ++it) {
    int key = std::abs(*it) % 10;  // последняя цифра
    m.insert(std::make_pair(key, *it));
  }

  std::cout << "Результат группировки (ключ: значение):\n";
  for (std::multimap<int, int>::const_iterator it = m.begin(); it != m.end(); ++it) {
    std::cout << it->first << ": " << it->second << std::endl;
  }
}
