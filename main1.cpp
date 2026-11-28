#include <SFML/Graphics.hpp> // Подключаем библиотеку SFML для создания графического окна и рисования
#include <iostream> // Подключаем ввод и вывод в консоль
#include <fstream> // Подключаем работу с файлами
#include <cstdlib> // Подключаем rand, srand
#include <ctime> // Подключаем time
#include <string> // Подключаем работу со строками
#include <clocale> // Подключаем настройку локали
#include <windows.h> // Подключаем функции Windows для настройки кодировки консоли
#include <sstream> // Подключаем поток для чтения координат из строки
int main() { // Главная функция программы
    SetConsoleCP(CP_UTF8); // Устанавливаем кодировку ввода консоли UTF-8
    SetConsoleOutputCP(CP_UTF8); // Устанавливаем кодировку вывода консоли UTF-8
    setlocale(LC_ALL, ".UTF8"); // Устанавливаем локаль для корректной работы с русским текстом
    std::string name; // Создаем строку для чтения очередной строки из файла
    std::string backgroundName, pathName, squaresName, emptyCellName; // Создаем строки для хранения названий цветов
    int rows_1, cols_1; // Объявляем переменные для количества строк и столбцов
    int startX, startY; // Объявляем координаты начальной точки
    srand(time(0)); // Инициализируем генератор случайных чисел текущим временем
    std::ifstream file("parameters.txt"); // Открываем файл с параметрами лабиринта
    if (!file.is_open()) { // Проверяем, удалось ли открыть файл
        std::cout << "Ошибка открытия файла!"; // Выводим сообщение об ошибке
        return 0; // Завершаем программу
    }
    std::getline(file, name); // Считываем первую строку файла (количество строк лабиринта)
    rows_1 = std::stoi(name.substr(name.find(':') + 1)); // Извлекаем число после двоеточия и преобразуем в int
    std::getline(file, name); // Считываем вторую строку файла (количество столбцов)
    cols_1 = std::stoi(name.substr(name.find(':') + 1)); // Извлекаем число после двоеточия и преобразуем в int
    std::getline(file, name); // Считываем третью строку (цвет фона)
    backgroundName = name.substr(name.find(':') + 2); // Записываем название цвета фона
    std::getline(file, name); // Считываем четвертую строку (цвет пути)
    pathName = name.substr(name.find(':') + 2); // Записываем название цвета пути
    std::getline(file, name); // Считываем пятую строку (цвет стен)
    squaresName = name.substr(name.find(':') + 2); // Записываем название цвета стен
    std::getline(file, name); // Считываем шестую строку (цвет свободных клеток)
    emptyCellName = name.substr(name.find(':') + 2); // Записываем название цвета свободных клеток
    std::getline(file, name); // Считываем седьмую строку (координаты начала)
    std::string coordinates = name.substr(name.find(':') + 1); // Получаем часть строки после двоеточия с координатами
    std::istringstream input(coordinates); // Создаем поток для извлечения чисел из строки
    input >> startX >> startY; // Извлекаем координаты X и Y из строки
    const int rows = rows_1; // Создаем постоянную переменную количества строк
    const int cols = cols_1; // Создаем постоянную переменную количества столбцов
    int maze[100][100]; // Создаем двумерный массив для хранения лабиринта
    file.close(); // Закрываем файл после чтения параметров
    if (rows < 5 || cols < 5 || rows > 100 || cols > 100) { // Проверяем допустимость размеров лабиринта
        std::cout << "Неверные размеры лабиринта!"; // Выводим сообщение при неправильных размерах
        return 0; // Завершаем программу
    }
    if (startX < 0 || startX >= cols || startY < 0 || startY >= rows) { // Проверяем, находится ли начало внутри лабиринта
        std::cout << "Неверные координаты начала!"; // Выводим сообщение при неправильных координатах
        return 0; // Завершаем программу
    }
    sf::Color backgroundColor; // Создаем переменную для хранения цвета фона окна
    sf::Color pathColor; // Создаем переменную для хранения цвета найденного пути
    sf::Color squaresColor; // Создаем переменную для хранения цвета стен
    sf::Color emptyCellColor; // Создаем переменную для хранения цвета свободных клеток
    if (backgroundName == "Black") // Если в файле указан черный цвет фона
        backgroundColor = sf::Color::Black; // Устанавливаем черный цвет
    else if (backgroundName == "White") // Если указан белый цвет
        backgroundColor = sf::Color::White; // Устанавливаем белый цвет
    else if (backgroundName == "Red") // Если указан красный цвет
        backgroundColor = sf::Color::Red; // Устанавливаем красный цвет
    else if (backgroundName == "Green") // Если указан зеленый цвет
        backgroundColor = sf::Color::Green; // Устанавливаем зеленый цвет
    else if (backgroundName == "Blue") // Если указан синий цвет
        backgroundColor = sf::Color::Blue; // Устанавливаем синий цвет
    if (pathName == "Black") // Если цвет пути черный
        pathColor = sf::Color::Black; // Устанавливаем черный цвет пути
    else if (pathName == "White") // Если цвет пути белый
        pathColor = sf::Color::White; // Устанавливаем белый цвет пути
    else if (pathName == "Red") // Если цвет пути красный
        pathColor = sf::Color::Red; // Устанавливаем красный цвет пути
    else if (pathName == "Green") // Если цвет пути зеленый
        pathColor = sf::Color::Green; // Устанавливаем зеленый цвет пути
    else if (pathName == "Blue") // Если цвет пути синий
        pathColor = sf::Color::Blue; // Устанавливаем синий цвет пути
    if (squaresName == "Black") // Если цвет стен черный
        squaresColor = sf::Color::Black; // Устанавливаем черный цвет стен
    else if (squaresName == "White") // Если цвет стен белый
        squaresColor = sf::Color::White; // Устанавливаем белый цвет стен
    else if (squaresName == "Red") // Если цвет стен красный
        squaresColor = sf::Color::Red; // Устанавливаем красный цвет стен
    else if (squaresName == "Green") // Если цвет стен зеленый
        squaresColor = sf::Color::Green; // Устанавливаем зеленый цвет стен
    else if (squaresName == "Blue") // Если цвет стен синий
        squaresColor = sf::Color::Blue; // Устанавливаем синий цвет стен
    if (emptyCellName == "Black") // Если цвет свободных клеток черный
        emptyCellColor = sf::Color::Black; // Устанавливаем черный цвет
    else if (emptyCellName == "White") // Если цвет свободных клеток белый
        emptyCellColor = sf::Color::White; // Устанавливаем белый цвет
    else if (emptyCellName == "Red") // Если цвет свободных клеток красный
        emptyCellColor = sf::Color::Red; // Устанавливаем красный цвет
    else if (emptyCellName == "Green") // Если цвет свободных клеток зеленый
        emptyCellColor = sf::Color::Green; // Устанавливаем зеленый цвет
    else if (emptyCellName == "Blue") // Если цвет свободных клеток синий
        emptyCellColor = sf::Color::Blue; // Устанавливаем синий цвет
    else if (emptyCellName == "Gray") // Если цвет свободных клеток серый
        emptyCellColor = sf::Color(70, 70, 70); // Создаем серый цвет с RGB-значениями 70, 70, 70
    for (int i = 0; i < rows; i++) { // Перебираем все строки лабиринта
        for (int j = 0; j < cols; j++) { // Перебираем все столбцы в текущей строке
            if (rand() % 2 == 0) { // Случайно выбираем, будет ли клетка свободной
                maze[i][j] = 0; // Записываем 0, если клетка свободна
            }
            else { // Если случайное число не подошло под условие
                maze[i][j] = 1; // Записываем 1, если клетка является стеной
            }
        }
    }
    int startR = startY; // Переводим координату Y в индекс строки
    int startC = startX; // Переводим координату X в индекс столбца
    int finishR = rows - 1; // Определяем строку финиша (последняя строка)
    int finishC = cols - 1; // Определяем столбец финиша (последний столбец)
    maze[startR][startC] = 0; // Делаем стартовую клетку свободной
    maze[finishR][finishC] = 0; // Делаем конечную клетку свободной
    int queueR[1000]; // Создаем массив очереди для хранения строк клеток
    int queueC[1000]; // Создаем массив очереди для хранения столбцов клеток
    int parentR[100][100]; // Создаем массив для хранения строки предыдущей клетки
    int parentC[100][100]; // Создаем массив для хранения столбца предыдущей клетки
    bool visited[100][100] = {}; // Создаем массив посещенных клеток и заполняем его false
    int front = 0; // Индекс следующего элемента для извлечения из очереди
    int back = 0; // Индекс следующего свободного места для добавления в очередь
    queueR[back] = startR; // Добавляем строку стартовой клетки в очередь
    queueC[back] = startC; // Добавляем столбец стартовой клетки в очередь
    back++; // Увеличиваем индекс добавления, так как один элемент уже помещен в очередь
    visited[startR][startC] = 1; // Отмечаем стартовую клетку как посещенную
    while (front < back && visited[finishR][finishC] == 0) { // Пока очередь не пуста и финиш еще не найден
        int r = queueR[front]; // Получаем строку текущей клетки из очереди
        int c = queueC[front]; // Получаем столбец текущей клетки из очереди
        front++; // Переходим к следующему элементу очереди
        int dr[4] = { -1, 1, 0, 0 }; // Задаем изменения строки для движения вверх, вниз, влево и вправо
        int dc[4] = { 0, 0, -1, 1 }; // Задаем изменения столбца для движения вверх, вниз, влево и вправо
        for (int k = 0; k < 4; k++) { // Перебираем все четыре направления движения
            int nr = r + dr[k]; // Вычисляем строку соседней клетки
            int nc = c + dc[k]; // Вычисляем столбец соседней клетки
            if (nr >= 0 && nr < rows && nc >= 0 && nc < cols) { // Проверяем, что соседняя клетка находится внутри лабиринта
                if (maze[nr][nc] == 0 && visited[nr][nc] == 0) { // Проверяем, что клетка свободна и еще не посещалась
                    visited[nr][nc] = 1; // Отмечаем соседнюю клетку посещенной
                    parentR[nr][nc] = r; // Запоминаем строку клетки, из которой пришли
                    parentC[nr][nc] = c; // Запоминаем столбец клетки, из которой пришли
                    queueR[back] = nr; // Добавляем строку соседней клетки в очередь
                    queueC[back] = nc; // Добавляем столбец соседней клетки в очередь
                    back++; // Увеличиваем индекс добавления в очередь
                }
            }
        }
    }
    int pathR[1000]; // Создаем массив для хранения строк клеток найденного пути
    int pathC[1000]; // Создаем массив для хранения столбцов клеток найденного пути
    int pathLength = 0; // Изначально длина пути равна нулю
    if (visited[finishR][finishC]) { // Если финишная клетка была посещена, значит путь найден
        int r = finishR; // Начинаем восстановление пути с конечной строки
        int c = finishC; // Начинаем восстановление пути с конечного столбца
        while (r != startR || c != startC) { // Пока не дошли обратно до стартовой клетки
            pathR[pathLength] = r; // Записываем строку текущей клетки в массив пути
            pathC[pathLength] = c; // Записываем столбец текущей клетки в массив пути
            pathLength++; // Увеличиваем длину пути на одну клетку
            int oldR = r; // Сохраняем текущую строку перед переходом к родителю
            int oldC = c; // Сохраняем текущий столбец перед переходом к родителю
            r = parentR[oldR][oldC]; // Переходим к строке предыдущей клетки
            c = parentC[oldR][oldC]; // Переходим к столбцу предыдущей клетки
        }
        pathR[pathLength] = startR; // Добавляем стартовую строку в путь
        pathC[pathLength] = startC; // Добавляем стартовый столбец в путь
        pathLength++; // Увеличиваем длину пути, учитывая стартовую клетку
        std::cout << "Путь найден!" << std::endl; // Выводим сообщение об успешном поиске пути
        std::cout << "Длина пути: " << pathLength - 1 << std::endl; // Выводим длину пути в шагах (без учета стартовой клетки)
    }
    else { // Если финишная клетка не была посещена
        std::cout << "Путь не найден!" << std::endl; // Выводим сообщение об отсутствии пути
    }
    std::cout << "Матрица лабиринта:" << std::endl; // Выводим заголовок матрицы
    for (int i = 0; i < rows; i++) { // Перебираем строки лабиринта
        for (int j = 0; j < cols; j++) { // Перебираем столбцы
            std::cout << maze[i][j] << " "; // Выводим значение клетки (0 или 1)
        }
        std::cout << std::endl; // Переходим на следующую строку консоли
    }
    sf::RenderWindow window(sf::VideoMode({ 1000u, 800u }), "Labirint"); // Создаем графическое окно размером 1000x800
    window.setFramerateLimit(60); // Ограничиваем частоту кадров до 60 в секунду
    float cellWidth = 900.0f / cols; // Вычисляем ширину клетки исходя из количества столбцов
    float cellHeight = 700.0f / rows; // Вычисляем высоту клетки исходя из количества строк
    float cellSize; // Объявляем переменную размера клетки (клетки будут квадратными)
    if (cellWidth < cellHeight) // Если ширина клетки меньше высоты
        cellSize = cellWidth; // Выбираем ширину, чтобы клетки поместились
    else
        cellSize = cellHeight; // Иначе выбираем высоту
    float offsetX = (1000.0f - cols * cellSize) / 2.0f; // Рассчитываем отступ лабиринта по горизонтали для центрирования
    float offsetY = (800.0f - rows * cellSize) / 2.0f; // Рассчитываем отступ лабиринта по вертикали для центрирования
    while (window.isOpen()) { // Пока графическое окно открыто
        while (const std::optional event = window.pollEvent()) { // Получаем события окна (закрытие и другие события)
            if (event->is<sf::Event::Closed>()) { // Проверяем, нажал ли пользователь крестик закрытия окна
                window.close(); // Закрываем окно
            }
        }
        window.clear(backgroundColor); // Очищаем окно выбранным цветом фона
        for (int i = 0; i < rows; i++) { // Перебираем строки лабиринта для рисования клеток
            for (int j = 0; j < cols; j++) { // Перебираем столбцы лабиринта
                sf::RectangleShape square; // Создаем прямоугольник для отображения одной клетки
                square.setSize(sf::Vector2f(cellSize - 1, cellSize - 1)); // Устанавливаем размер клетки с небольшим промежутком
                square.setPosition(sf::Vector2f( // Устанавливаем положение клетки в окне
                    offsetX + j * cellSize, // Вычисляем X-позицию клетки
                    offsetY + i * cellSize // Вычисляем Y-позицию клетки
                ));
                if (maze[i][j] == 1) { // Если клетка является стеной
                    square.setFillColor(squaresColor); // Закрашиваем ее цветом стен
                }
                else { // Если клетка свободна
                    square.setFillColor(emptyCellColor); // Закрашиваем ее цветом свободных клеток
                }
                window.draw(square); // Отображаем клетку в окне
            }
        }
        if (visited[finishR][finishC]) { // Если путь до финиша найден
            for (int i = 0; i < pathLength; i++) { // Перебираем все клетки восстановленного пути
                sf::RectangleShape square; // Создаем прямоугольник для отображения клетки пути
                square.setSize(sf::Vector2f(cellSize - 1, cellSize - 1)); // Устанавливаем размер клетки
                square.setPosition(sf::Vector2f( // Устанавливаем положение клетки
                    offsetX + pathC[i] * cellSize, // Вычисляем координату X по столбцу
                    offsetY + pathR[i] * cellSize // Вычисляем координату Y по строке
                ));
                square.setFillColor(pathColor); // Устанавливаем цвет найденного пути
                window.draw(square); // Отображаем клетку пути
            }
        }
        else { // Если путь до финиша не найден
            for (int i = 0; i < rows; i++) { // Перебираем все строки
                for (int j = 0; j < cols; j++) { // Перебираем все столбцы
                    if (visited[i][j]) { // Если клетка была посещена алгоритмом BFS
                        sf::RectangleShape square; // Создаем прямоугольник для отображения посещенной клетки
                        square.setSize(sf::Vector2f(cellSize - 1, cellSize - 1)); // Устанавливаем его размер
                        square.setPosition(sf::Vector2f( // Устанавливаем его позицию
                            offsetX + j * cellSize, // Вычисляем X по столбцу
                            offsetY + i * cellSize // Вычисляем Y по строке
                        ));
                        square.setFillColor(pathColor); // Закрашиваем посещенную клетку цветом пути
                        window.draw(square); // Отображаем клетку
                    }
                }
            }
        }
        sf::RectangleShape startSquare; // Создаем прямоугольник для выделения стартовой клетки
        startSquare.setSize(sf::Vector2f(cellSize - 2, cellSize - 2)); // Устанавливаем размер стартового выделения
        startSquare.setPosition(sf::Vector2f( // Устанавливаем его положение
            offsetX + startC * cellSize + 1, // Вычисляем X координату старта
            offsetY + startR * cellSize + 1 // Вычисляем Y координату старта
        ));
        startSquare.setFillColor(sf::Color::Transparent); // Делаем заливку прозрачной
        startSquare.setOutlineThickness(2); // Устанавливаем толщину границы в 2 пикселя
        startSquare.setOutlineColor(sf::Color::Green); // Устанавливаем зеленый цвет границы
        window.draw(startSquare); // Отображаем выделение старта
        sf::RectangleShape finishSquare; // Создаем прямоугольник для выделения финишной клетки
        finishSquare.setSize(sf::Vector2f(cellSize - 2, cellSize - 2)); // Устанавливаем размер выделения финиша
        finishSquare.setPosition(sf::Vector2f( // Устанавливаем положение финишного выделения
            offsetX + finishC * cellSize + 1, // Вычисляем X координату финиша
            offsetY + finishR * cellSize + 1 // Вычисляем Y координату финиша
        ));
        finishSquare.setFillColor(sf::Color::Transparent); // Делаем заливку прозрачной
        finishSquare.setOutlineThickness(2); // Устанавливаем толщину границы в 2 пикселя
        finishSquare.setOutlineColor(sf::Color::Green); // Устанавливаем зеленый цвет границы
        window.draw(finishSquare); // Отображаем выделение финиша
        window.display(); // Показываем полностью сформированный кадр окна
    }
    return 0; // Завершаем программу успешно
}