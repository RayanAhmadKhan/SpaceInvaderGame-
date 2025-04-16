#include <iostream>
#include <fstream>
#include <Windows.h>
#include <random>
#include "help.h"
#include <ctime>
#include <cstdlib>
#include <chrono>
using namespace std;

bool blast[5][10];
int I = 1, J = 1;
int score = 0;
const string highScoreFileName = "highscore.txt";
const int numberOfHighScores = 5;
struct HighScore {
    int score;

};
HighScore highScores[numberOfHighScores];
void welcomepage (int box_x, int box_y) {

    myRect(50, 50, 780, 380, 255, 0, 0);
    drawText(20, 50, 80, 255, 215, 0, "Menu");
    drawText(25, 240, 70, 160, 32, 240, "SPACE INVADERS");
    drawText(19, 230, 155, 255, 0, 0, "Start the game   (Press 1)");
    drawText(19, 280, 210, 255, 0, 0, "Quit          (Press 0)");
    drawText(19, 250, 260, 255, 0, 0, "High Score      (Press 8)");
    drawText(19, 260, 320, 255, 0, 0, "Continue       (Press 9)");

    myRect(40, 390, 800, 570, 255, 215, 0);
    drawText(16, 50, 400, 255, 215, 0, "PRESS SHIFT KEY TO FIRE");
    drawText(16, 50, 440, 255, 215, 0, "PRESS ESC KEY TO PAUSE");
    drawText(16, 50, 490, 255, 215, 0, "PRESS CURSOR KEYS TO MOVE");
    drawText(16, 50, 530, 255, 215, 0, "GAME CAN BE SAVED FROM PAUSE MENU");

}
void removeBox(int ship_x, int ship_y)
{
    myRect(ship_x, ship_y, ship_x + 40, ship_y + 20, 0, 0, 0);
    myRect(ship_x + 10, ship_y - 10, ship_x + 30, ship_y, 0, 0, 0);
    myLine(ship_x + 20, ship_y - 10, ship_x + 20, ship_y - 20, 0, 0, 0);
}
void drawPlayerShip(int ship_x, int ship_y)
{
    myRect(ship_x, ship_y, ship_x + 40, ship_y + 20, 255, 0, 0);
    myRect(ship_x + 10, ship_y - 10, ship_x + 30, ship_y, 255, 0, 0);
    myLine(ship_x + 20, ship_y - 10, ship_x + 20, ship_y - 20, 255, 0, 0);
}
void bullet(int bullet_x, int bullet_y) {
    myLine(bullet_x, bullet_y, bullet_x, bullet_y - 10, 255, 255, 0);
    myLine(bullet_x + 2, bullet_y, bullet_x + 2, bullet_y - 10, 255, 255, 0);
}
void removeBullet(int bullet_x, int bullet_y) {
    myLine(bullet_x, bullet_y, bullet_x, bullet_y - 10, 0, 0, 0);
    myLine(bullet_x + 2, bullet_y, bullet_x + 2, bullet_y - 10, 0, 0, 0);
}
void animiship(int box_x, int box_y) {

    myLine(box_x + 10, box_y + 15, box_x + 10, box_y + 30, 138, 24, 138);
    myEllipse(box_x + 10, box_y + 10, box_x + 50, box_y + 25, 138, 24, 138, 138, 24, 138);
    myLine(box_x + 50, box_y + 15, box_x + 50, box_y + 30, 138, 24, 138);
}
struct EnemyShip {
    int x;
    int y;
    char direction;
    bool alive;
};
void clearEnemyShip(EnemyShip& enemyShip) {

    if (enemyShip.alive) {
        myLine(enemyShip.x + 10, enemyShip.y + 15, enemyShip.x + 10, enemyShip.y + 30, 0, 0, 0);
        myEllipse(enemyShip.x + 10, enemyShip.y + 10, enemyShip.x + 50, enemyShip.y + 25, 0, 0, 0, 0, 0, 0);
        myLine(enemyShip.x + 50, enemyShip.y + 15, enemyShip.x + 50, enemyShip.y + 30, 0, 0, 0);

    }
}
void drawEnemyShip(EnemyShip& enemyShip) {
    if (enemyShip.alive)
        animiship(enemyShip.x, enemyShip.y);
}
int randomValue() {
    srand(time(0));
    return rand();
}
bool enemyFire(EnemyShip enemyShip[], int& x, int& y)
{
    srand(time(nullptr));
    int random = rand() % 50;
    int row = random / 10;

    for (int i = 4; i >= row; i--)
    {
        if (enemyShip[random + 10 * (i - row)].alive)
        {
            x = enemyShip[random + 10 * (i - row)].x + 30;
            y = enemyShip[random + 10 * (i - row)].y + 35;
            return true;
        }
    }

    return false;
}
void fire(int ship_x, int ship_y, int& i, int& j, EnemyShip enemyship[][10]) {
    int top_limit = 60;
    int step_size = 5;
    //int hits = 0;
    int bullet_x = ship_x + 20;
    int bullet_y = ship_y - 10;


    while (bullet_y > top_limit) {
        removeBullet(bullet_x, bullet_y);

        if (bullet_y > top_limit)
        {
            bullet_y -= step_size;
        }
        for (i = 0; i < 5; i++)
        {
            for (j = 0; j < 10; j++)
            {
                if (enemyship[i][j].alive) {
                    if (bullet_y >= enemyship[i][j].y && bullet_y <= enemyship[i][j].y + 15 && bullet_x >= enemyship[i][j].x && bullet_x <= enemyship[i][j].x + 40)
                    {
                        if (blast[i][j] = 1) {
                            score += 10;
                            myRect(1050, 120, 970, 70, 0, 0, 0);
                            drawText(20, 970, 75, 140, 0, 255, "", true, score);
                        }
                        enemyship[i][j].alive = false;
                        blast[i][j] = 0;
                        bullet_x = 20;
                        bullet_y = 60;
                        break;
                    }

                }
            }
        }
        bullet_x = ship_x + 20;
        bullet(bullet_x, bullet_y);
        Sleep(0.2);
    }
    removeBullet(bullet_x, bullet_y);
}
void saveHighScores() {
    ofstream highScoreFile(highScoreFileName);
    if (highScoreFile.is_open()) {
        for (int i = 0; i < numberOfHighScores; i++) {
            highScoreFile << highScores[i].score << endl;
        }
        highScoreFile.close();
        cout << "High scores saved." << endl;
    }
    else {
        cerr << "Unable to open high score file for writing." << endl;
    }
}
void loadHighScores() {
    ifstream highScoreFile(highScoreFileName);
    if (highScoreFile.is_open()) {
        for (int i = 0; i < numberOfHighScores; ++i) {
            highScoreFile >> highScores[i].score;
        }
        highScoreFile.close();
    }
    else {
        cerr << "Unable to open high score file for reading." << endl;
    }
}
void displayHighScores() {
    cout << "High Scores:" << endl;

    for (int i = 0; i < numberOfHighScores; i++) {
        cout << i + 1 << ". " << highScores[i].score << endl;
    }
}
bool compareHighScores(const HighScore& a, const HighScore& b) {
    return a.score > b.score;
}
void bubbleSort(HighScore arr[], int n) {
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {

            if (arr[j].score < arr[j + 1].score) {
                HighScore temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}
bool collision2(int ship_x, int ship_y, int enemy_x, int enemy_y) {
    int a;
    int ship_width = 40;
    int ship_height = 40;
    int enemy_width = 40;
    int enemy_height = 40;


    a = (ship_x < enemy_x + enemy_width && ship_x + ship_width > enemy_x && ship_y < enemy_y + enemy_height && ship_y + ship_height>enemy_y);
    return a;

}
bool collision3(int x, int y, int bottom_limit) {
    return (y + 15 >= bottom_limit);
}
void saveGame(int ship_x, int ship_y, int lives, int score, EnemyShip enemyShips[][10]) {
    ofstream saveFile("game_save.txt");

    if (saveFile.is_open()) {

        saveFile << ship_x << " " << ship_y << " " << lives << " " << score << " ";


        for (int i = 0; i < 5; ++i) {
            for (int j = 0; j < 10; ++j) {
                saveFile << enemyShips[i][j].x << " " << enemyShips[i][j].y << " " << enemyShips[i][j].direction << " " << enemyShips[i][j].alive << " ";
            }
        }

        saveFile.close();

    }
    else {
        cerr << "Unable to open save file for writing." << endl;
    }
}
void loadGame(int& ship_x, int& ship_y, int& lives, int& score, EnemyShip enemyShips[][10]) {
    ifstream loadFile("game_save.txt");

    if (loadFile.is_open()) {

        loadFile >> ship_x >> ship_y >> lives >> score;

        for (int i = 0; i < 5; ++i) {
            for (int j = 0; j < 10; ++j) {
                loadFile >> enemyShips[i][j].x >> enemyShips[i][j].y >> enemyShips[i][j].direction >> enemyShips[i][j].alive;
            }
        }

        loadFile.close();
        cout << "Game load" << endl;
    }
    else {
        cerr << "Unable to open save file for reading." << endl;
    }
}
bool endGame(EnemyShip enemyShip[][10]) {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 10; j++) {
            if (enemyShip[i][j].alive) {

                return false;
            }
        }
    }

    return true;
}

int main()
{
    int ship_x = 400, ship_y = 320;
    int lives = 3;
    int bullet_x = ship_x + 20;
    int bullet_y = ship_y - 10;

    int i, j;

    EnemyShip enemyShips[5][10];
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 10; j++) {
            enemyShips[i][j].x = 20 + j * 60;
            enemyShips[i][j].y = 60 + i * 20;
            enemyShips[i][j].direction = 'R';
            enemyShips[i][j].alive = true;
        }
    }

    int box_x = 20; int box_y = 60;

    int left_limit = 20, right_limit = 820, top_limit = 60, bottom_limit = 360;
    int  step_size = 5;
    int enemy_step_size = 5;



    char direction = ' ';
    int choice, levels;
    int count = 0;
    bool shot = false;
    bool isPlayerShipAlive = true;
    loadHighScores();
    int timerDurationLives = 5;
    int timerDurationScore = 10;

    auto startTimeLives = chrono::high_resolution_clock::now();
    auto startTimeScore = chrono::high_resolution_clock::now();


    welcomepage(box_x, box_y);
    cin >> choice;
    if (choice == 1 || choice == 9) {
        if (choice == 1) {

            myRect(40, 390, 800, 570, 0, 0, 0);
            myRect(40, 390, 800, 570, 160, 32, 240);
            myRect(left_limit - (-32), top_limit - 2, right_limit + (-42), bottom_limit + 2, 0, 0, 0);
            drawText(20, 350, 100, 255, 215, 0, "LEVELS");
            drawText(20, 250, 160, 255, 192, 203, "Medium (Press 3)");
            drawText(20, 280, 220, 255, 192, 203, "Hard (Press 4)");

            cin >> levels;
        }
        if (choice == 9) {
            myRect(15, 390, 950, 600, 0, 0, 0);
            levels = 3;
            loadGame(ship_x, ship_y, lives, score, enemyShips);
        }
        if (levels == 3) {
            //Sleep(25);

            myRect(left_limit - 15, top_limit - 25, right_limit + 25, bottom_limit + 25, 200, 10, 0);



            drawText(20, 850, 80, 0, 255, 0, "SCORE");

            drawText(20, 850, 280, 0, 255, 0, "LIVES");
            drawText(20, 970, 280, 140, 0, 255, "", true, lives);


            drawPlayerShip(ship_x, ship_y);
            //bullet(bullet_x, bullet_y);



            int pause = 1;
            while (pause != 0) {
                int whichKey = 0;

                while (whichKey != 7) // 7 is the code for ESC key
                {


                    for (int i = 0; i < 5; i++)
                    {
                        for (int j = 0; j < 10; j++)
                        {
                            if (enemyShips[i][j].alive)
                                drawEnemyShip(enemyShips[i][j]);
                            if (collision3(enemyShips[i][j].x, enemyShips[i][j].y, bottom_limit)) {
                                myRect(18, 58, 822, 362, 0, 0, 0);
                                drawText(20, 250, 160, 255, 0, 0, "GAME OVER");
                                highScores[numberOfHighScores - 1].score = score;
                                bubbleSort(highScores, numberOfHighScores);
                                saveHighScores();
                                return 0;

                            }
                            if (collision2(ship_x, ship_y, enemyShips[i][j].x, enemyShips[i][j].y)) {

                                myRect(18, 58, 822, 362, 0, 0, 0);
                                drawText(20, 250, 160, 255, 0, 0, "GAME OVER");
                                highScores[numberOfHighScores - 1].score = score;
                                bubbleSort(highScores, numberOfHighScores);
                                saveHighScores();
                                return 0;
                            }
                        }
                    }

                    int enemyBulletX, enemyBulletY;
                    int ans = enemyFire(enemyShips[0], enemyBulletX, enemyBulletY);
                    if (ans) {
                        while (enemyBulletY < bottom_limit && isPlayerShipAlive)
                        {

                            if (enemyBulletX >= ship_x && enemyBulletX <= ship_x + 40 &&
                                enemyBulletY >= ship_y && enemyBulletY <= ship_y + 20) {
                                Beep(1000, 400);
                                isPlayerShipAlive = false;
                                lives--;

                                myRect(1010, 320, 970, 270, 0, 0, 0);
                                drawText(20, 970, 280, 140, 0, 255, "", true, lives);

                                myLine(enemyBulletX, enemyBulletY, enemyBulletX + 2, enemyBulletY + 10, 0, 0, 0);

                                if (lives <= 0) {

                                    highScores[numberOfHighScores - 1].score = score;
                                    bubbleSort(highScores, numberOfHighScores);
                                    saveHighScores();
                                    myRect(18, 58, 822, 362, 0, 0, 0);
                                    drawText(20, 350, 230, 255, 0, 0, "GAME OVER");
                                    myRect(15, 390, 840, 550, 0, 0, 0);
                                    break;

                                }
                            }

                            myLine(enemyBulletX, enemyBulletY, enemyBulletX + 2, enemyBulletY + 10, 0, 0, 0);
                            enemyBulletY += 5;
                            myLine(enemyBulletX, enemyBulletY, enemyBulletX + 2, enemyBulletY + 10, 255, 255, 255);

                            Sleep(0.7);
                        }


                        myLine(enemyBulletX, enemyBulletY, enemyBulletX, enemyBulletY + 10, 0, 0, 0);
                    }


                    isPlayerShipAlive = true;

                    if (!isPlayerShipAlive) {

                        removeBox(ship_x, ship_y);
                        count++;


                    }

                    {

                        //myRect(left_limit - 2, top_limit - 2, right_limit + 2, bottom_limit + 2, 0, 0, 0);



                        myRect(left_limit - 15, top_limit - 25, right_limit + 25, bottom_limit + 25, 200, 10, 0);


                        drawPlayerShip(ship_x, ship_y);
                        //bullet(bullet_x, bullet_y);


                        for (int i = 0; i < 5; i++) {
                            for (int j = 0; j < 10; j++) {
                                clearEnemyShip(enemyShips[i][j]);
                                if (enemyShips[i][j].alive) {
                                    drawEnemyShip(enemyShips[i][j]);
                                }
                                if (enemyShips[i][j].direction == 'R') {

                                    enemyShips[i][j].x += step_size;
                                    if (enemyShips[i][j].x + 50 == right_limit) {
                                        for (int i = 0; i < 5; i++) {
                                            for (int j = 0; j < 10; j++) {
                                                enemyShips[i][j].direction = 'L';
                                                enemyShips[i][j].y += 20;
                                            }
                                        }
                                    }
                                }
                                else if (enemyShips[i][j].direction == 'L') {

                                    enemyShips[i][j].x -= step_size;
                                    if (enemyShips[i][j].x == left_limit) {
                                        for (int i = 0; i < 5; i++) {
                                            for (int j = 0; j < 10; j++) {
                                                enemyShips[i][j].direction = 'R';
                                                enemyShips[i][j].y += 20;
                                            }
                                        }
                                    }
                                }



                            }
                        }

                        if (isKeyPressed(whichKey))
                        {
                            switch (whichKey)
                            {
                            case 1:
                                direction = 'L';
                                break;
                            case 2:
                                direction = 'U';
                                break;
                            case 3:
                                direction = 'R';
                                break;
                            case 4:
                                direction = 'D';
                                break;
                            case 5:

                                break;

                            case 6:
                                shot = true;
                                fire(ship_x, ship_y, i, j, enemyShips);
                                shot = false;
                                continue;
                            }
                        }
                        //cross check
                        if (lives <= 0) {
                            myRect(18, 58, 822, 362, 0, 0, 0);
                            drawText(20, 250, 160, 255, 0, 0, "GAME OVER");
                            highScores[numberOfHighScores - 1].score = score;
                            bubbleSort(highScores, numberOfHighScores);
                            saveHighScores();
                            return 0;
                        }

                        Sleep(25); // 25 milliseconds

                        switch (direction)
                        {
                        case 'L':
                            // Left
                            removeBox(ship_x, ship_y);
                            if (ship_x > left_limit)
                                ship_x -= step_size;
                            drawPlayerShip(ship_x, ship_y);
                            break;
                        case 'U':
                            // Up
                            removeBox(ship_x, ship_y);
                            if (ship_y > top_limit)
                                ship_y -= step_size;
                            drawPlayerShip(ship_x, ship_y);
                            break;
                        case 'R':
                            // Right
                            removeBox(ship_x, ship_y);
                            if (ship_x + 20 < right_limit)
                                ship_x += step_size;
                            drawPlayerShip(ship_x, ship_y);
                            break;
                        case 'D':
                            // Down
                            removeBox(ship_x, ship_y);
                            if (ship_y + 20 < bottom_limit)
                                ship_y += step_size;
                            drawPlayerShip(ship_x, ship_y);
                            break;

                        }
                        auto currentTime = chrono::high_resolution_clock::now();
                        auto elapsedLives = chrono::duration_cast<chrono::seconds>(currentTime - startTimeLives).count();
                        if (elapsedLives >= timerDurationLives) {
                            startTimeLives = chrono::high_resolution_clock::now();
                            if (lives < 5) {
                                lives++;
                                drawText(16, 50, 440, 255, 215, 200, "Nice Moves");
                            }
                        }


                        auto elapsedScore = chrono::duration_cast<chrono::seconds>(currentTime - startTimeScore).count();
                        if (elapsedScore >= timerDurationScore) {
                            startTimeScore = chrono::high_resolution_clock::now();
                            if (score > 5) {
                                score -= 5;
                                drawText(16, 50, 490, 255, 215, 200, "Come On ! ");
                                drawText(16, 50, 530, 255, 215, 0, "You can do it ");
                            }

                            if (endGame(enemyShips)) {
                                myRect(18, 58, 822, 362, 0, 0, 0);
                                drawText(20, 250, 160, 255, 0, 0, "YOU WON");
                                highScores[numberOfHighScores - 1].score = score;
                                bubbleSort(highScores, numberOfHighScores);
                                saveHighScores();
                                return 0;
                            }
                        }


                    }

                }

                drawText(20, 250, 420, 160, 32, 240, "RESUME  (Press 1)");
                drawText(20, 270, 470, 160, 32, 240, "QUIT   (Press 0)");
                drawText(20, 270, 520, 160, 32, 240, "SAVE   (PRESS 2)");

                cin >> pause;

                if (pause == 0) {
                    highScores[numberOfHighScores - 1].score = score;
                    bubbleSort(highScores, numberOfHighScores);
                    saveHighScores();
                    myRect(18, 58, 822, 362, 0, 0, 0);
                    drawText(20, 350, 230, 255, 0, 0, "GAME OVER");
                    myRect(40, 390, 800, 570, 0, 0, 0);
                }
                else if (pause == 2) {
                    saveGame(ship_x, ship_y, lives, score, enemyShips);
                    drawText(20, 350, 230, 255, 0, 0, "Thank You");
                    return 0;

                }
                else {

                    myRect(40, 390, 800, 570, 0, 0, 0);
                    myRect(40, 390, 800, 570, 160, 32, 240);

                }




            }

        }


        else if (levels == 4)
        {

            //Sleep(25);

            myRect(left_limit - 15, top_limit - 25, right_limit + 25, bottom_limit + 25, 200, 10, 0);



            drawText(20, 850, 80, 0, 255, 0, "SCORE");

            drawText(20, 850, 280, 0, 255, 0, "LIVES");
            drawText(20, 970, 280, 140, 0, 255, "", true, lives);


            drawPlayerShip(ship_x, ship_y);
            //bullet(bullet_x, bullet_y);



            int pause = 1;
            while (pause != 0) {
                int whichKey = 0;

                while (whichKey != 7) // 7 is the code for ESC key
                {

                    for (int i = 0; i < 5; i++)
                    {
                        for (int j = 0; j < 10; j++)
                        {
                            if (enemyShips[i][j].alive)
                                drawEnemyShip(enemyShips[i][j]);
                            if (collision3(enemyShips[i][j].x, enemyShips[i][j].y, bottom_limit)) {
                                myRect(18, 58, 822, 362, 0, 0, 0);
                                drawText(20, 250, 160, 255, 0, 0, "GAME OVER");
                                highScores[numberOfHighScores - 1].score = score;
                                bubbleSort(highScores, numberOfHighScores);
                                saveHighScores();
                                return 0;

                            }
                            if (collision2(ship_x, ship_y, enemyShips[i][j].x, enemyShips[i][j].y)) {

                                myRect(18, 58, 822, 362, 0, 0, 0);
                                drawText(20, 250, 160, 255, 0, 0, "GAME OVER");
                                highScores[numberOfHighScores - 1].score = score;
                                bubbleSort(highScores, numberOfHighScores);
                                saveHighScores();
                                return 0;
                            }
                        }
                    }

                    int enemyBulletX, enemyBulletY;
                    int ans = enemyFire(enemyShips[0], enemyBulletX, enemyBulletY);
                    if (ans) {
                        while (enemyBulletY < bottom_limit && isPlayerShipAlive)
                        {

                            if (enemyBulletX >= ship_x && enemyBulletX <= ship_x + 40 &&
                                enemyBulletY >= ship_y && enemyBulletY <= ship_y + 20) {
                                Beep(1000, 400);
                                isPlayerShipAlive = false;
                                lives--;

                                myRect(1010, 320, 970, 270, 0, 0, 0);
                                drawText(20, 970, 280, 140, 0, 255, "", true, lives);

                                myLine(enemyBulletX, enemyBulletY, enemyBulletX, enemyBulletY + 10, 0, 0, 0);

                                if (lives <= 0) {

                                    highScores[numberOfHighScores - 1].score = score;
                                    bubbleSort(highScores, numberOfHighScores);
                                    saveHighScores();
                                    myRect(18, 58, 822, 362, 0, 0, 0);
                                    drawText(20, 350, 230, 255, 0, 0, "GAME OVER");
                                    myRect(15, 390, 840, 550, 0, 0, 0);
                                    break;
                                }
                            }

                            myLine(enemyBulletX, enemyBulletY, enemyBulletX, enemyBulletY + 10, 0, 0, 0);
                            enemyBulletY += 5;
                            myLine(enemyBulletX, enemyBulletY, enemyBulletX, enemyBulletY + 10, 255, 200, 150);

                            Sleep(0.2);
                        }


                        myLine(enemyBulletX, enemyBulletY, enemyBulletX, enemyBulletY + 10, 0, 0, 0);
                    }


                    isPlayerShipAlive = true;

                    if (!isPlayerShipAlive) {

                        removeBox(ship_x, ship_y);
                        count++;

                    }

                    {

                        //myRect(left_limit - 2, top_limit - 2, right_limit + 2, bottom_limit + 2, 0, 0, 0);



                        myRect(left_limit - 15, top_limit - 25, right_limit + 25, bottom_limit + 25, 200, 10, 0);


                        drawPlayerShip(ship_x, ship_y);
                        //bullet(bullet_x, bullet_y);


                        for (int i = 0; i < 5; i++) {
                            for (int j = 0; j < 10; j++) {
                                clearEnemyShip(enemyShips[i][j]);
                                if (enemyShips[i][j].alive) {
                                    drawEnemyShip(enemyShips[i][j]);
                                }
                                if (enemyShips[i][j].direction == 'R') {

                                    enemyShips[i][j].x += step_size;
                                    if (enemyShips[i][j].x + 50 == right_limit) {
                                        for (int i = 0; i < 5; i++) {
                                            for (int j = 0; j < 10; j++) {
                                                enemyShips[i][j].direction = 'L';
                                                enemyShips[i][j].y += 20;
                                            }
                                        }
                                    }
                                }
                                else if (enemyShips[i][j].direction == 'L') {

                                    enemyShips[i][j].x -= step_size;
                                    if (enemyShips[i][j].x == left_limit) {
                                        for (int i = 0; i < 5; i++) {
                                            for (int j = 0; j < 10; j++) {
                                                enemyShips[i][j].direction = 'R';
                                                enemyShips[i][j].y += 20;
                                            }
                                        }
                                    }
                                }



                            }
                        }

                        if (isKeyPressed(whichKey))
                        {
                            switch (whichKey)
                            {
                            case 1:
                                direction = 'L';
                                break;
                            case 2:
                                direction = 'U';
                                break;
                            case 3:
                                direction = 'R';
                                break;
                            case 4:
                                direction = 'D';
                                break;
                            case 5:

                                break;

                            case 6:
                                shot = true;
                                fire(ship_x, ship_y, i, j, enemyShips);
                                shot = false;
                                continue;
                            }
                        }

                        if (lives <= 0) {
                            myRect(18, 58, 822, 362, 0, 0, 0);
                            drawText(20, 250, 160, 255, 0, 0, "GAME OVER");
                            highScores[numberOfHighScores - 1].score = score;
                            bubbleSort(highScores, numberOfHighScores);
                            saveHighScores();
                            return 0;
                        }

                        Sleep(5); // 25 milliseconds

                        switch (direction)
                        {
                        case 'L':
                            // Left
                            removeBox(ship_x, ship_y);
                            if (ship_x > left_limit)
                                ship_x -= step_size;
                            drawPlayerShip(ship_x, ship_y);
                            break;
                        case 'U':
                            // Up
                            removeBox(ship_x, ship_y);
                            if (ship_y > top_limit)
                                ship_y -= step_size;
                            drawPlayerShip(ship_x, ship_y);
                            break;
                        case 'R':
                            // Right
                            removeBox(ship_x, ship_y);
                            if (ship_x + 20 < right_limit)
                                ship_x += step_size;
                            drawPlayerShip(ship_x, ship_y);
                            break;
                        case 'D':
                            // Down
                            removeBox(ship_x, ship_y);
                            if (ship_y + 20 < bottom_limit)
                                ship_y += step_size;
                            drawPlayerShip(ship_x, ship_y);
                            break;

                        }
                        auto currentTime = chrono::high_resolution_clock::now();
                        auto elapsedLives = chrono::duration_cast<chrono::seconds>(currentTime - startTimeLives).count();
                        if (elapsedLives >= timerDurationLives) {
                            startTimeLives = chrono::high_resolution_clock::now();
                            if (lives < 5) {
                                lives++;
                                drawText(16, 50, 440, 255, 215, 200, "Nice Moves");
                            }
                        }


                        auto elapsedScore = chrono::duration_cast<chrono::seconds>(currentTime - startTimeScore).count();
                        if (elapsedScore >= timerDurationScore) {
                            startTimeScore = chrono::high_resolution_clock::now();
                            if (score > 5) {
                                score -= 5;
                                drawText(16, 50, 490, 255, 215, 200, "Come On ! You can do it.");
                            }

                        }
                        if (endGame(enemyShips)) {
                            myRect(18, 58, 822, 362, 0, 0, 0);
                            drawText(20, 250, 160, 255, 0, 0, "GAME OVER");
                            highScores[numberOfHighScores - 1].score = score;
                            bubbleSort(highScores, numberOfHighScores);
                            saveHighScores();
                            return 0;
                        }
                    }

                }

                drawText(20, 250, 420, 160, 32, 240, "RESUME  (Press 1)");
                drawText(20, 270, 470, 160, 32, 240, "QUIT   (Press 0)");
                drawText(20, 270, 520, 160, 32, 240, "SAVE   (PRESS 2)");

                cin >> pause;

                if (pause == 0) {

                    myRect(18, 58, 822, 362, 0, 0, 0);
                    highScores[numberOfHighScores - 1].score = score;
                    bubbleSort(highScores, numberOfHighScores);
                    saveHighScores();
                    drawText(20, 350, 230, 255, 0, 0, "GAME OVER");
                    myRect(40, 390, 800, 570, 0, 0, 0);
                }
                else if (pause == 2) {
                    saveGame(ship_x, ship_y, lives, score, enemyShips);
                    drawText(20, 350, 230, 255, 0, 0, "Thank You");
                    return 0;

                }
                else {

                    myRect(40, 390, 800, 570, 0, 0, 0);
                    myRect(40, 390, 800, 570, 160, 32, 240);
                }




            }


        }
    }
    else if (choice == 8) {
        displayHighScores();
    }


    else if (choice == 0) {
        myRect(15, 390, 840, 550, 0, 0, 0);
        myRect(18, 58, 822, 362, 0, 0, 0);
        drawText(20, 350, 230, 255, 0, 0, "Take Care");
    }




    return 0;
}