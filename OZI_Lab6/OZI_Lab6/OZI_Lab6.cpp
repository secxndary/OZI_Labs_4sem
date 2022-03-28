#include <stdio.h>
#include <math.h>
#include <iostream>
#include <fstream>
using namespace std;



// Посчитать значение a ^ b ( mod P )
int power(int a, int b, int p)
{
    int tmp = a;
    int sum = tmp;

    for (int i = 1; i < b; i++) 
    {
        for (int j = 1; j < a; j++) 
        {
            sum += tmp;
            if (sum >= p)
                sum -= p;
        }
        tmp = sum;
    }

    return tmp;
}



// a * b mod n 
int mul(int a, int b, int n)
{
    int sum = 0;

    for (int i = 0; i < b; i++) 
    {
        sum += a;
        if (sum >= n)
            sum -= n;
    }
    return sum;
}



/*****************************************************
    p - простое число
    0 < g < p-1
    0 < x < p-1
    m - шифруемое сообщение m < p
*****************************************************/


void crypt(int p, int g, int x, string inFileName, string outFileName) 
{
    ifstream inf(inFileName.c_str());
    ofstream outf(outFileName.c_str());

    // y = g ^ x (mod p)
    int y = power(g, x, p);

    cout << "Открытый ключ (p, g, y) = " << "(" << p << ", " << g << ", " << y << ")" << endl;
    cout << "Закрытый ключ x = " << x << endl;

    cout << "\nШифруемый текст: " << endl;

    while (inf.good()) 
    {
        int m = inf.get();
        if (m > 0) 
        {
            cout << (char)m;
            int k = rand() % (p - 2) + 1;       // случайное число 1 < k < (p - 1) 
            int a = power(g, k, p);             // а = g ^ k (mod p)
            int b = mul(power(y, k, p), m, p);  // b = m * y ^ k (mod p)
            outf << a << " " << b << " ";       // пара {a, b} — шифротекст
        }
    }

    cout << endl;
    inf.close();
    outf.close();
}



void decrypt(int p, int x, string inFileName, string outFileName) 
{
    ifstream inf(inFileName.c_str());
    ofstream outf(outFileName.c_str());

    cout << "\nДешифрованый текст: " << endl;

    // Получатель, используя открытый ключ {a, b}, вычисляет:
    while (inf.good()) 
    {
        int a = 0;
        int b = 0;
        inf >> a;
        inf >> b;

        if (a != 0 && b != 0) 
        {
            int deM = mul(b, power(a, p - 1 - x, p), p);
            char m = static_cast<char>(deM);
            outf << m;      // m = b * a ^ (p - 1 - x) mod p
            cout << m;      // m — дешифрованный текст
        }
    }
    cout << endl;

    inf.close();
    outf.close();
}








int main()
{
    setlocale(LC_ALL, "rus");
    int publicAlice, publicBob, privateAlice, privateBob, partialAlice, partialBob, fullKeyAlice, fullKeyBob;
    cout << "==========  Алгоритм Диффи-Хеллмана  ==========\n\n";



    // Открыто обмениваемся публичными ключами и договариваемся, что публичный ключ Алисы 
    // используется в качестве основания, а Боба — в качестве модуля (ключи — простые числа)
    publicAlice = 71;
    publicBob = 97;

    cout << "Публичный ключ Алисы:\t" << publicAlice << endl;
    cout << "Публичный ключ Боба:\t" << publicBob << endl << endl;



    // Каждый из них выбирает простое число в качестве приватного ключа. Он известен только
    // самому пользователю и не отправляется по сети, т.е. Алиса не знает приватного ключа Боба, 
    // а Боб — Алисы, и тем более прослушивающая сеть Ева не знает информации ни об одном приватном ключе
    privateAlice = 151;
    privateBob = 101;

    cout << "Приватный ключ Алисы:\t" << privateAlice << endl;
    cout << "Приватный ключ Боба:\t" << privateBob << endl << endl;



    // Далее Алиса и Боб по своему приватному и двум публичным ключам высчитывают свои частичные ключи 
    // и отправляют их по сети. За счет того, что они считаются по формуле модуля больших степеней 
    // простых чисел, расшифровать по публичным частичным ключам приватные ключи практически невозможно.
    partialAlice = power(publicAlice, privateAlice, publicBob);
    partialBob = power(publicAlice, privateBob, publicBob);

    cout << "Частичный ключ Алисы:\t" << partialAlice << endl;
    cout << "Частичный ключ Боба:\t" << partialBob << endl << endl;



    // Теперь на основании полученных частичных ключей Алиса и Боб могут сгенерировать свои полные 
    // ключи по той же формуле. Благодаря свойству математическог сооотношения модулей мы получили 
    // одинаковый секретный ключ, при этом не обмениваясь по открытому каналу никакой информаицей, 
    // которая помогла бы расшифровать общий секретный ключ! Ева пососала хуйца и сидит в ахуе.
    fullKeyAlice = power(partialBob, privateAlice, publicBob);
    fullKeyBob = power(partialAlice, privateBob, publicBob);

    cout << "Полный ключ Алисы:\t" << fullKeyAlice << endl;
    cout << "Полный ключ Боба:\t" << fullKeyBob << endl << endl;







    cout << "\n\n====================  RSA  ====================\n\n";

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




    // Теперь нужно получить закрытый ключ: нужно вычислить число d (закрытую экспоненту), обратное е по модулю φ.
    double d;

    // k — произвольное значение
    double k = 2;

    // d соответствует условию: d = e ^ (-1) mod ф  <=>  d * e = 1 + k * ф  <=>  (d * e) % ф = 1
    d = (1 + (k * fi)) / e;
    cout << "d = " << d << endl << endl;

    // Пара {d, n} — секретный ключ




    // Зашифруем сообщение, например, число 12 (оно должно быть меньше n = 21!)
    double msg = 12;
    cout << "Оригинальный текст:   " << msg << endl;

    // Шифрование: возводим msg в степень e по модулю n (с помощью открытого ключа)
    double c = pow(msg, e);
    c = fmod(c, n);
    cout << "Зашифрованный текст:  " << c << endl;

    // Расшифровка: возводим шифротекст в степень d по модулю n (с помощью закрытого ключа)
    double m = pow(c, d);
    m = fmod(m, n);
    cout << "Расшифрованный текст: " << m << endl;





    cout << "\n\n\n============  Алгоритм Эль-Гамаля  ============\n\n";

    srand(time(NULL));
    crypt(593, 123, 8, "in.txt", "out_crypt.txt");
    decrypt(593, 8, "out_crypt.txt", "out_decrypt.txt");

    cout << "\n================================================\n\n";



    return 0;
}




