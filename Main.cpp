/**
 * @file main.cpp
 * @brief Демонстрация использования класса FineGrainedQueue
 * @author Кushnir Eduard
 * @date 28-03-2025
 */

 #include "FineGrainedQueue.h"
 #include <iostream>
 #include <thread>
 #include <vector>
 
 /**
  * @brief Функция для тестирования параллельных вставок
  * @param queue Ссылка на очередь, в которую производится вставка
  * @param startValue Начальное значение для вставки
  * @param count Количество элементов для вставки
  * @param pos Позиция для вставки
  */
 void insertElements(FineGrainedQueue& queue, int startValue, int count, int pos) {
   for (int i = 0; i < count; i++) {
     queue.insertIntoMiddle(startValue + i, pos);
   }
 }
 
 /**
  * @brief Главная функция программы
  * @return Код возврата программы
  */
 int main() {
   FineGrainedQueue queue;
   
   // Инициализация списка
   queue.initialize(1);
   
   // Базовый тест
   std::cout << "Базовый тест последовательной вставки:" << std::endl;
   queue.insertIntoMiddle(2, 0); // Вставляем после первого элемента
   queue.insertIntoMiddle(3, 1); // Вставляем после второго элемента
   queue.insertIntoMiddle(4, 10); // Вставляем в конец, т.к. позиция больше длины списка
   queue.printList();
   
   // Тест параллельной вставки
   std::cout << "\nТест параллельной вставки:" << std::endl;
   FineGrainedQueue parallelQueue;
   parallelQueue.initialize(0);
   
   // Создаем несколько потоков для параллельных вставок
   std::vector<std::thread> threads;
   int threadsCount = 3;
   
   for (int i = 0; i < threadsCount; i++) {
     threads.push_back(std::thread(insertElements, std::ref(parallelQueue), i*10 + 1, 3, i));
   }
   
   // Ждем завершения всех потоков
   for (auto& t : threads) {
     t.join();
   }
   
   // Выводим результат параллельных вставок
   parallelQueue.printList();
   
   return 0;
 }