#include "Arduino.h" // Подключаем билиотеку для работы с Arduino Nano-R3
#include "PiezoSensor.h" // Подключаем библиотеку для пьезодатчика
#define PIEZOSENSOR_PIN_POS	A0 // Определение Pin
PiezoSensor piezoSensor(PIEZOSENSOR_PIN_POS); // Глобальные переменные и определения
//определение переменных для меню тестирования
const int timeout = 10000; 
char menuOption = 0;
long time0;
// Настройка всего необходимого для работы схемы.
void setup() 
{
    // Серийный номер установки для отладки и вывод сообщений на мониторе
    Serial.begin(9600);
    while (!Serial) ; // Ожидание подключения порта, необходимого для порта USB
    Serial.println("start");
    menuOption = menu();
}
// Основная логика схемы. Она определяет взаимодействие между выбранными компонентами.
void loop() 
{
    if(menuOption == '1') {
    // Тестирование прьезоэлемента
    int piezoSensorVal = piezoSensor.read();
    Serial.print(F("Val: ")); Serial.println(piezoSensorVal)
    }
    if (millis() - time0 > timeout) menuOption = menu();
}
// Функция меню для выбора компонентов, подлежащих тестированию
char menu()
{
    Serial.println(F("\nWhich component would you like to test?"));
    Serial.println(F("(1) Piezo Element"));
    Serial.println(F("(menu) send anything else or press on board reset button\n"));
    while (!Serial.available());
    // Последовательное считывание данных
    while (Serial.available()) 
    {
        char c = Serial.read();
        if (isAlphaNumeric(c)) 
        {   
            
            if(c == '1') 
    			Serial.println(F("Now Testing Piezo Element"));
            else
            {
                Serial.println(F("illegal input!"));
                return 0;
            }
            time0 = millis();
            return c;
        }
    }
}
