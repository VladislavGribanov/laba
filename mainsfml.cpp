#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <clocale>
#include <windows.h>
#include <sstream>
int main(){
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
    setlocale(LC_ALL, ".UTF8");
	std::string name;
	std::string backgroundName, pathName, squaresName;
	int rows_1, cols_1;
    int startX, startY;
    srand(time(0));
	std::ifstream file("parameters.txt");
	if (!file.is_open()) {
		std::cout << "Ошибка открытия файла!";
		return 0;
	}
    std::getline(file, name);
    rows_1 = std::stoi(name.substr(name.find(':') + 1));
    std::getline(file, name);
    cols_1 = std::stoi(name.substr(name.find(':') + 1));
    std::getline(file, name);
    backgroundName = name.substr(name.find(':') + 2);
    std::getline(file, name);
    pathName = name.substr(name.find(':') + 2);
    std::getline(file, name);
    squaresName = name.substr(name.find(':') + 2);
    std::getline(file, name);
    std::string coordinates = name.substr(name.find(':') + 1);
    std::istringstream input(coordinates);
    input >> startX >> startY;
    const int rows = rows_1;
    const int cols = cols_1;
    int maze[100][100];
    file.close();
    if (rows < 5 || cols < 5 || rows > 100 || cols > 100)
    {
        std::cout << "Неверные размеры лабиринта!";
        return 0;
    }
    if (startX < 0 || startX >= cols || startY < 0 || startY >= rows)
    {
        std::cout << "Неверные координаты начала!";
        return 0;
    }
    sf::Color backgroundColor;
    sf::Color pathColor;
    sf::Color squaresColor;
    if (backgroundName == "Black")
        backgroundColor = sf::Color::Black;
    else if (backgroundName == "White")
        backgroundColor = sf::Color::White;
    else if (backgroundName == "Red")
        backgroundColor = sf::Color::Red;
    else if (backgroundName == "Green")
        backgroundColor = sf::Color::Green;
    else if (backgroundName == "Blue")
        backgroundColor = sf::Color::Blue;
    if (pathName == "Black")
        pathColor = sf::Color::Black;
    else if (pathName == "White")
        pathColor = sf::Color::White;
    else if (pathName == "Red")
        pathColor = sf::Color::Red;
    else if (pathName == "Green")
        pathColor = sf::Color::Green;
    else if (pathName == "Blue")
        pathColor = sf::Color::Blue;
    if (squaresName == "Black")
        squaresColor = sf::Color::Black;
    else if (squaresName == "White")
        squaresColor = sf::Color::White;
    else if (squaresName == "Red")
        squaresColor = sf::Color::Red;
    else if (squaresName == "Green")
        squaresColor = sf::Color::Green;
    else if (squaresName == "Blue")
        squaresColor = sf::Color::Blue;
    for (int i = 0;i < rows;i++) {
        for (int j = 0;j < cols;j++) {
            if (rand() % 2 == 0) {
                maze[i][j] = 0;
            }
            else {
                maze[i][j] = 1;
            }
        }
    }
    int startR = startY;
    int startC = startX;
    int finishR = rows - 1;
    int finishC = cols - 1;
    maze[startR][startC] = 0;
    maze[finishR][finishC] = 0;
    int queueR[1000];
    int queueC[1000];
    int parentR[100][100];
    int parentC[100][100];
    bool visited[100][100] = {};
    int front = 0;
    int back = 0;
    queueR[back] = startR;
    queueC[back] = startC;
    back++;
    visited[startR][startC] = 1;
    while (front<back)
    {
        int r = queueR[front];
        int c = queueC[front];
        front++;
        if (r == finishR && c == finishC)
            break;
        int dr[4] = { -1,1,0,0 };
        int dc[4] = { 0,0,-1,1 };
        for (int k = 0;k < 4;k++) {
            int nr = r + dr[k];
            int nc = c + dc[k];
            if (nr >= 0 && nr < rows && nc >= 0 && nc < cols) {
                if (maze[nr][nc] == 0 && visited[nr][nc] == 0) {
                    visited[nr][nc] = 1;
                    parentR[nr][nc] = r;
                    parentC[nr][nc] = c;
                    queueR[back] = nr;
                    queueC[back] = nc;
                    back++;
                }
            }
        }
    }

    int pathR[1000];
    int pathC[1000];
    int pathLength = 0;
    if (visited[finishR][finishC]) {
        int r = finishR;
        int c = finishC;
        while (r != startR || c != startC)
        {
            pathR[pathLength] = r;
            pathC[pathLength] = c;
            pathLength++;
            int oldR = r;
            int oldC = c;
            r = parentR[oldR][oldC];
            c = parentC[oldR][oldC];
        }
        pathR[pathLength] = startR;
        pathC[pathLength] = startC;
        pathLength++;
        std::cout << "Путь найден!" << std::endl;
        std::cout << "Длина пути: " << pathLength - 1 << std::endl;
    }
    else
    {
        std::cout << "Путь не найден!" << std::endl;
        std::cout << "Показываем достигнутую область." << std::endl;
    }
    for (int i = 0;i < rows;i++) {
        for (int j = 0;j < cols;j++) {
            std::cout << maze[i][j] << " ";
        }
        std::cout << std::endl;
    }
    for (int i = 0;i < pathLength;i++) {
        std::cout<<pathR[i] << " " << pathC[i] << std::endl;
    }
}
