#include "lab2.h"

#include <limits>

int main() {
  setlocale(LC_ALL, "Russian");

  int choice;

  do {
    std::cout << "\n========== МЕНЮ ЛАБОРАТОРНОЙ РАБОТЫ №2 ==========\n";
    std::cout << "1. Задание 1: Заполнение и доступ к элементам. Обратные итераторы\n";
    std::cout << "2. Задание 2: Вставка элементов\n";
    std::cout << "3. Задание 3: Удаление элементов\n";
    std::cout << "4. Задание 4: Итераторы и алгоритмы (арифметическая прогрессия)\n";
    std::cout << "5. Задание 5: Алгоритмы поиска\n";
    std::cout << "6. Задание 6: Базовые модифицирующие алгоритмы. Итераторы вставки\n";
    std::cout << "7. Задание 7: Сортировка и слияние\n";
    std::cout << "8. Задание 8: Численные алгоритмы (строки)\n";
    std::cout << "9. Задание 9: Множества (multiset, includes)\n";
    std::cout << "10. Задание 10: Отображения (multimap)\n";
    std::cout << "0. Выход\n";
    std::cout << "==================================================\n";
    std::cout << "Выберите задание (0-10): ";

    std::cin >> choice;

    if (std::cin.fail()) {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cout << "Ошибка ввода. Пожалуйста, введите число от 0 до 10.\n";
      continue;
    }

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    switch (choice) {
      case 1:
        Task1();
        break;
      case 2:
        Task2();
        break;
      case 3:
        Task3();
        break;
      case 4:
        Task4();
        break;
      case 5:
        Task5();
        break;
      case 6:
        Task6();
        break;
      case 7:
        Task7();
        break;
      case 8:
        Task8();
        break;
      case 9:
        Task9();
        break;
      case 10:
        Task10();
        break;
      case 0:
        std::cout << "Выход из программы.\n";
        break;
      default:
        std::cout << "Неверный выбор. Пожалуйста, выберите от 0 до 10.\n";
    }

  } while (choice != 0);

  return 0;
}
