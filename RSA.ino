
#include <Arduino.h>

// Функция получения ключей
void getKeys(unsigned long p, unsigned long q, unsigned long& k, unsigned long& d, unsigned long& s) {
  unsigned long F = (p - 1) * (q - 1);
  
  // Поиск числа k, взаимно простого с F
  for (k = 2; k < F; k++) {
    if (gcd(k, F) == 1) {
      break;
    }
  }
  
  // Поиск числа d, такого что (d * k) % F = 1
  for (d = 1; d < F; d++) {
    if (mulMod(d, k, F) == 1) {
      break;
    }
  }
  
  s = p * q;
}

// Функция нахождения наибольшего общего делителя
unsigned long gcd(unsigned long a, unsigned long b) {
  if (b == 0) {
    return a;
  }
  
  return gcd(b, a % b);
}

// Функция вычисления остатка от деления двух чисел
unsigned long mulMod(unsigned long a, unsigned long b, unsigned long m) {
  unsigned long res = 0;
  
  while (b > 0) {
    if (b & 1) {
      res = (res + a) % m;
    }
    
    a = (a * 2) % m;
    b >>= 1;
  }
  
  return res;
}

// Функция дешифровки данных с помощью закрытого ключа
unsigned long decrypt(unsigned long encrypted, unsigned long d, unsigned long s) {
  return mulMod(encrypted, d, s);
}

void setup() {
  Serial.begin(9600);
  
  unsigned long p = 11; // Простое число p
  unsigned long q = 17; // Простое число q
  unsigned long k, d, s;
  
  getKeys(p, q, k, d, s);
  
  Serial.print("Открытый ключ: [");
  Serial.print(k);
  Serial.print(", ");
  Serial.print(s);
  Serial.println("]");
  
  Serial.print("Закрытый ключ: [");
  Serial.print(d);
  Serial.print(", ");
  Serial.print(s);
  Serial.println("]");
  
  unsigned long M = 10; // Число M для шифровки
  unsigned long encrypted = mulMod(M, k, s);
  
  // Отправка зашифрованных данных на условную наземную станцию
  Serial.print("Зашифрованные данные: ");
  Serial.println(encrypted);
  
  // Дешифровка данных с помощью закрытого ключа
  unsigned long decrypted = decrypt(encrypted, d, s);
  
  Serial.print("Дешифрованные данные: ");
  Serial.println(decrypted);
}

void loop() {
  // В loop() ничего не делаем
}
