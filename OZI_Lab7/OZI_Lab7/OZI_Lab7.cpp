﻿#include <stdio.h>
#include <math.h>
#include <iostream>
#include <fstream>
using namespace std;




int main()
{
    setlocale(LC_ALL, "rus");

    // Выбираем 2 случайных простых числа:
    double p = 3, q = 7;
    cout << "p = " << p << "\nq = " << q << endl;

    // Вычисляем модуль: произведение этих чисел = 21
    double n = p * q;
    cout << "n = " << n << endl;

    // Функция Эйлера: ф = (p - 1) * (q - 1) = 12
    double fi = (p - 1) * (q - 1);
    cout << "ф = " << fi << endl;

    // Открытая экспонента: 1. Простое число; 2. Меньше ф; 3. Взаимно простое с ф
    double e = 5;
    cout << "e = " << e << endl;

    // Пара {e, n} — октрытый ключ




    // Теперь нужно получить закрытый ключ: нужно вычислить 
    // число d (закрытую экспоненту), обратное е по модулю φ.
    double d;

    // k — произвольное значение
    double k = 2;

    // d соответствует условию: d = e ^ (-1) mod ф  <=>  
    // <=> d * e = 1 + k * ф  <=>  (d * e) % ф = 1
    d = (1 + (k * fi)) / e;
    cout << "d = " << d << endl << endl;

    // Пара {d, n} — секретный ключ




    // 12 - хеш-функция оригинального документа:
    double msg = 12;
    cout << "Хеш-функция:          " << msg << endl;

    // Создание ЭЦП с помощью секретного ключа:
    double s = pow(msg, d);
    s = fmod(s, n);
    cout << "Электронная подпись:  " << s << endl;

    // Проверка подписи по открытому ключу:
    double m = pow(s, e);
    m = fmod(m, n);
    cout << "Проверка подписи:     " << m << endl;

}

