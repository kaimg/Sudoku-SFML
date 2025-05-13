#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cstdlib>
#include <time.h>
#include <sstream>
#include <fstream>
#include "solver.h"
#include "filler.h"
using namespace sf;
bool isdMenu = false;
int delelle = 0; bool isMenu = 1;
bool settimelimit;

namespace FILES {
    namespace MENU {
        namespace IMAGES {
            const std::string BACKGROUND = "resources/images/menu/background.jpg";
            const std::string MENU = "resources/images/menu/menu.png";
            const std::string MENU1 = "resources/images/menu/menu1.png";
            const std::string MENU2 = "resources/images/menu/menu2.png";
            const std::string MENU3 = "resources/images/menu/menu3.png";
            const std::string MENU4 = "resources/images/menu/menu4.png";
            const std::string MENU5 = "resources/images/menu/menu5.png";
            const std::string MENU6 = "resources/images/menu/menu6.png";
            const std::string MENU7 = "resources/images/menu/menu7.png";
        }

        namespace SOUNDS {
            const std::string CLICK = "resources/audio/click.wav";
            const std::string WIN = "resources/audio/winsound.wav";
            const std::string LOSE = "resources/audio/gamedie.wav";
            const std::string MUSIC = "resources/audio/snowfall.ogg";
        }
    }

    namespace GAME {
        namespace IMAGES {
            const std::string ICON = "resources/images/game/icon.png";
            const std::string BOARD = "resources/images/game/boardnew.png";
            const std::string NUMBER_GRID = "resources/images/game/numbergrid.png";
        }

        namespace FONTS {
            const std::string BEBAS = "resources/fonts/bebas.ttf";
        }
    }
}

namespace DIFFICULTY {
    const int EASY = 36;
    const int MEDIUM = 48;
    const int HARD = 60;
    const int DEFAULT = 48;
}
void menu(RenderWindow& window, Sound sound, bool playMusic, Font font, int buff, int sd)
{
	int menunum = 0;
	Image record;
	record.loadFromFile(FILES::MENU::IMAGES::MENU7);
	record.createMaskFromColor(Color::White);
	Texture main, about, exit, background, recordt;
	background.loadFromFile(FILES::MENU::IMAGES::BACKGROUND);
	main.loadFromFile(FILES::MENU::IMAGES::MENU);
	about.loadFromFile(FILES::MENU::IMAGES::MENU1);
	exit.loadFromFile(FILES::MENU::IMAGES::MENU2);
	recordt.loadFromImage(record);
	Sprite menuMain(main), menuAbout(about), menuExit(exit), menubackground(background), menuRecord(recordt);
	menubackground.setPosition(0, 0);
	menuMain.setPosition(250, 240);
	menuAbout.setPosition(250, 340);
	menuExit.setPosition(250, 440);
	menuRecord.setPosition(0, 540);
	Text ftext;
	ftext.setFont(font);
	ftext.setCharacterSize(32);
	ftext.setFillColor(sf::Color::Black);
	ftext.setStyle(sf::Text::Bold);
	ftext.setPosition(130, 540);
	std::ostringstream stringh, stringd;
	if (buff <= 0 || buff > 300)
	{
		ftext.setString("YOU DON'T WIN YET");
	}
	else {
		int ftime = buff / 60, fminutes = buff - (ftime * 60);
		stringh << fminutes; stringd << ftime;
		ftext.setString(stringd.str() + " : " + stringh.str());
	}
	while (isMenu)
	{
		menuMain.setColor(Color::White); menuAbout.setColor(Color::White); menuExit.setColor(Color::White); menuRecord.setColor(Color::White);
		//window.clear(Color::White);
		if (IntRect(250, 240, 225, 45).contains(Mouse::getPosition(window))) { menuMain.setColor(Color::Cyan); menunum = 1; }
		if (IntRect(250, 340, 225, 45).contains(Mouse::getPosition(window))) { menuAbout.setColor(Color::Cyan); menunum = 2; }
		if (IntRect(250, 440, 225, 45).contains(Mouse::getPosition(window))) { menuExit.setColor(Color::Cyan); menunum = 3; }
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			sound.play();
			if (menunum == 1) { isMenu = false; }
			if (menunum == 2) { isdMenu = true; isMenu = false; }
			if (menunum == 3) { window.close(); isMenu = false; }
		}
		window.draw(menubackground); window.draw(menuMain); window.draw(menuAbout); window.draw(menuExit); window.draw(menuRecord);
		window.draw(ftext); window.display();
	};
}
void menum(RenderWindow& window, bool playMusic)
{
	Texture measy, mmedium, mhard, background, mtimed;
	background.loadFromFile(FILES::MENU::IMAGES::BACKGROUND);
	measy.loadFromFile(FILES::MENU::IMAGES::MENU3);
	mmedium.loadFromFile(FILES::MENU::IMAGES::MENU4);
	mhard.loadFromFile(FILES::MENU::IMAGES::MENU5);
	mtimed.loadFromFile(FILES::MENU::IMAGES::MENU6);
	Sprite menu1(measy), menu2(mmedium), menu3(mhard), menubackground(background), menu4(mtimed);
	menu1.setPosition(80, 200);
	menu2.setPosition(390, 200);
	menu3.setPosition(80, 300);
	menu4.setPosition(390, 300);
	int menudif = 0;
	while (isdMenu)
	{
		menu1.setColor(Color::White); menu2.setColor(Color::White); menu3.setColor(Color::White); menu4.setColor(Color::White);
		if (IntRect(80, 200, 225, 45).contains(Mouse::getPosition(window))) { menu1.setColor(Color::Cyan); menudif = 1; }
		if (IntRect(390, 200, 225, 45).contains(Mouse::getPosition(window))) { menu2.setColor(Color::Cyan); menudif = 2; }
		if (IntRect(80, 300, 225, 45).contains(Mouse::getPosition(window))) { menu3.setColor(Color::Cyan); menudif = 3; }
		if (IntRect(390, 300, 225, 45).contains(Mouse::getPosition(window))) { menu4.setColor(Color::Cyan); menudif = 4; }
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			if (menudif == 1) { playMusic = false; delelle = DIFFICULTY::EASY; isdMenu = false; }
			if (menudif == 2) { delelle = DIFFICULTY::MEDIUM; isdMenu = false; }
			if (menudif == 3) { delelle = DIFFICULTY::HARD; isdMenu = false; }
			if (menudif == 4) { settimelimit = true; delelle = DIFFICULTY::DEFAULT;  isdMenu = false; }
		}window.clear(); window.draw(menubackground); window.draw(menu1); window.draw(menu2); window.draw(menu3); window.draw(menu4); window.display();
	}
}
void finalscreen(RenderWindow& window, Text text, Font font, Sound winsound, bool playMusic, int second, int buff, bool start);
void setTimeLimit(int minutes, int time, Text text, Font font, RenderWindow& window, Sound losesound, bool playMusic)
{   
	if (playMusic) { losesound.setVolume(100); losesound.play(); }
	Text ftext;
	ftext.setFont(font);
	ftext.setCharacterSize(24);
	ftext.setFillColor(sf::Color(20, 20, 60));
	ftext.setStyle(sf::Text::Bold);
	ftext.setPosition(310, 200);
	ftext.setString("YOU LOSE!");
	while (minutes == 5 && time == 1)
	{
		text.setPosition(310, 300);
		window.clear();
		window.draw(text);
		window.draw(ftext);
		window.display();
	}
}
int main()
{
	int buff = -1000;
	int sd;
	std::ifstream fin;
	fin.open(("highscore.txt"));
	if (fin.is_open())
	{
		while (!fin.eof())
		{
			fin >> buff;
		}
	}
	std::cout << buff << std::endl;
	fin.close();
	bool playMusic = true;
	int temp;
	Time sleep;
	sf::RenderWindow window(sf::VideoMode(720, 585), "Sudoku", Style::Close | Style::Titlebar);
	window.setFramerateLimit(60);
	SoundBuffer buffer;
	buffer.loadFromFile(FILES::MENU::SOUNDS::CLICK);
	Sound sound;
	sound.setBuffer(buffer);
	SoundBuffer bufferw;
	bufferw.loadFromFile(FILES::MENU::SOUNDS::WIN);
	Sound winsound;
	winsound.setBuffer(bufferw);
	SoundBuffer bufferl;
	bufferl.loadFromFile(FILES::MENU::SOUNDS::LOSE);
	Sound losesound;
	losesound.setBuffer(bufferl);
	Music back;
	back.openFromFile(FILES::MENU::SOUNDS::MUSIC);
	back.setVolume(12);
	back.play();
	Font font;
	font.loadFromFile(FILES::GAME::FONTS::BEBAS);
	menu(window, sound, playMusic, font, buff, 0);
	if (isdMenu == true) { menum(window, playMusic); }
	if (playMusic) { back.setVolume(0); losesound.setVolume(0); winsound.setVolume(0); sound.setVolume(0); }
	a = delelle;
	if (a == 0) a = 48;
	finish();
	print();
	Image icon;
	icon.loadFromFile(FILES::GAME::IMAGES::ICON);
	window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
	Texture main;
	main.loadFromFile(FILES::MENU::IMAGES::MENU);
	Sprite mmain(main);
	mmain.setPosition(605, 80);
	mmain.setScale(Vector2f(0.5, 0.5));
	Texture exit;
	exit.loadFromFile(FILES::MENU::IMAGES::MENU2);
	Sprite mexit(exit);
	mexit.setPosition(605, 380);
	mexit.setScale(Vector2f(0.5, 0.5));
	Image heroimage;
	heroimage.loadFromFile(FILES::GAME::IMAGES::BOARD);
	Image numberstile;
	numberstile.loadFromFile(FILES::GAME::IMAGES::NUMBER_GRID);
	numberstile.createMaskFromColor(Color::White);
	Texture numbers;
	numbers.loadFromImage(numberstile);
	Sprite numbersS;
	numbersS.setTexture(numbers);
	Texture herotexture;
	herotexture.loadFromImage(heroimage);
	Sprite herosprite;
	herosprite.setTexture(herotexture);
	RectangleShape rect;
	rect.setSize(Vector2f(63, 63));
	rect.setFillColor(Color(255, 0, 0));
	Event event;
	Clock clock;
	String strtime;
	Text text;
	text.setFont(font);
	text.setCharacterSize(24);
	text.setFillColor(sf::Color(20, 20, 60));
	text.setStyle(sf::Text::Bold);
	text.setPosition(600, 0);
	int x = -1, y = -1, x1, y1;
	char number1;
	bool checkisnumber = false;
	bool start = false;
	int minutes = 0;
	int second = 0;
	int timet, secnum = 0;
	while (window.isOpen())
	{
		//if (start) { timet = 0; }
		isTue = false;
		start = false;
		mmain.setColor(Color::White);
		if (IntRect(605, 80, 110, 22).contains(Mouse::getPosition(window))) { mmain.setColor(Color::Cyan); start = true; }
		mexit.setColor(Color::White);
		if (IntRect(605, 380, 110, 22).contains(Mouse::getPosition(window))) 
		{ mexit.setColor(Color::Cyan); 
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			window.close();
		}
		}
		int timet = clock.getElapsedTime().asSeconds();
		timet = timet - secnum;
		second = timet;
		if (timet % 60 == 0) { minutes = timet / 60; }
		timet = timet - (minutes * 60);
		if (settimelimit == true) { setTimeLimit(minutes, timet, text, font, window, losesound, playMusic); }
		std::ostringstream strings, stringm;
		stringm << minutes; strings << timet;
		if (timet < 10 && minutes < 10)text.setString("Game time\n\t\t\t0" + stringm.str() + " : 0" + strings.str());
		else if (timet < 10)text.setString("Game time\n\t\t\t" + stringm.str() + " : " + "0" + strings.str());
		else text.setString("Game time\n\t\t\t" + stringm.str() + " : " + strings.str());
		text.setPosition(600, 0);
		x1 = x; y1 = y;
		while (window.pollEvent(event))
		{
			Vector2i vectords;

			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Escape) window.close();
			}
			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.key.code == sf::Mouse::Left) {
					if (start) { secnum = timet; second = 0; timet = 0; finish(); }
					sound.play();
					if (sudoku[y][x] == 10) { sudoku[y1][x1] = 0; }
					vectords = Mouse::getPosition(window);
					x = vectords.x / 65;
					y = vectords.y / 65;
					if (schecker[y][x] == 0 && sudoku[y][x] == 0 && 0 <= x && x < 9 && 0 <= y && y < 9) {
						sudoku[y][x] = 10;
					}
				}
			}
			if (event.type == sf::Event::KeyPressed)
			{
				switch (event.key.code)
				{
				case sf::Keyboard::Numpad0:
					if (schecker[y][x] == 0) {
						sudoku[y][x] = 0;
					}
					break;
				case sf::Keyboard::Numpad1:
					if (schecker[y][x] == 0) {
						sudoku[y][x] = 1; isTrue();
					}
					break;
				case sf::Keyboard::Numpad2:
					if (schecker[y][x] == 0) {
						sudoku[y][x] = 2; isTrue();
					}
					break;
				case sf::Keyboard::Numpad3:
					if (schecker[y][x] == 0) { sudoku[y][x] = 3; isTrue(); }
					
					break;
				case sf::Keyboard::Numpad4:
					if (schecker[y][x] == 0) { sudoku[y][x] = 4; isTrue();}
					break;
				case sf::Keyboard::Numpad5:
					if (schecker[y][x] == 0) { sudoku[y][x] = 5; isTrue(); }
					break;
				case sf::Keyboard::Numpad6:
					if (schecker[y][x] == 0) { sudoku[y][x] = 6; isTrue(); }
					break;
				case sf::Keyboard::Numpad7:
					if (schecker[y][x] == 0) { sudoku[y][x] = 7; isTrue(); }
					break;
				case sf::Keyboard::Numpad8:
					if (schecker[y][x] == 0) { sudoku[y][x] = 8; isTrue(); }
					break;
				case sf::Keyboard::Numpad9:
					if (schecker[y][x] == 0) { sudoku[y][x] = 9; isTrue(); }
				break; case sf::Keyboard::Num0:
					if (schecker[y][x] == 0) {
						sudoku[y][x] = 0;
					}
					break;
				case sf::Keyboard::Num1:
					if (schecker[y][x] == 0) {
						sudoku[y][x] = 1; isTrue();
					} //if (solsudoku[y][x] != sudoku[y][x]) numbersS.;
					break;
				case sf::Keyboard::Num2:
					if (schecker[y][x] == 0) {
						sudoku[y][x] = 2; isTrue();
					}
					break;
				case sf::Keyboard::Num3:
					if (schecker[y][x] == 0) { sudoku[y][x] = 3; isTrue(); }
					break;
				case sf::Keyboard::Num4:
					if (schecker[y][x] == 0) { sudoku[y][x] = 4; isTrue(); }
					break;
				case sf::Keyboard::Num5:
					if (schecker[y][x] == 0) { sudoku[y][x] = 5; isTrue(); }
					break;
				case sf::Keyboard::Num6:
					if (schecker[y][x] == 0) { sudoku[y][x] = 6; isTrue(); }
					break;
				case sf::Keyboard::Num7:
					if (schecker[y][x] == 0) { sudoku[y][x] = 7; isTrue(); }
					break;
				case sf::Keyboard::Num8:
					if (schecker[y][x] == 0) { sudoku[y][x] = 8; isTrue(); }
					break;
				case sf::Keyboard::Num9:
					if (schecker[y][x] == 0) { sudoku[y][x] = 9; isTrue(); }
					break;
				}
			}
		}
		window.clear(Color::White);
		for (int i = 0; i < 9; i++)
		{
			for (int j = 0; j < 9; j++)
			{
				numbersS.setTextureRect(IntRect(0, 0, 65, 65));
				numbersS.setPosition(65 * i, 65 * j);
				window.draw(numbersS);
			}
		}/*for (int i = 0; i < 9; i++)
		 {			for (int j = 0; j < 9; j++)
			{
				numbersS.setTextureRect(IntRect(650, 0, 65, 65)); numbersS.setPosition(j * 65, i * 65);
				window.draw(numbersS);
			}
		}*/
		if (0 <= x && x < 9 && 0 <= y && y < 9)
		{
			for (int i = 0; i < 9; i++)
			{
				numbersS.setTextureRect(IntRect(715, 0, 65, 65)); numbersS.setPosition((x * 65), (i * 65));
				window.draw(numbersS);
				numbersS.setTextureRect(IntRect(sudoku[y][x] * 65, 0, 65, 65)); numbersS.setPosition(x * 65, y * 65); window.draw(numbersS);
			}
			for (int i = 0; i < 9; i++)
			{
				numbersS.setTextureRect(IntRect(715, 0, 65, 65)); numbersS.setPosition((i * 65), (y * 65));
				window.draw(numbersS);
				numbersS.setTextureRect(IntRect(sudoku[y][x] * 65, 0, 65, 65)); numbersS.setPosition(x * 65, y * 65); window.draw(numbersS);
			}
		}
		int k = 0, f = 0;
		k = (x) / 3;
		f = (y) / 3;
		if (k == 0 && f == 0) {
			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					numbersS.setTextureRect(IntRect(715, 0, 65, 65)); numbersS.setPosition((i * 65), (j * 65));
					window.draw(numbersS);
					numbersS.setTextureRect(IntRect(sudoku[y][x] * 65, 0, 65, 65)); numbersS.setPosition(x * 65, y * 65); window.draw(numbersS);
				}
			}
		}if (k == 1 && f == 0) {
			for (int i = 3; i < 6; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					numbersS.setTextureRect(IntRect(715, 0, 65, 65)); numbersS.setPosition((i * 65), (j * 65));
					window.draw(numbersS);
					numbersS.setTextureRect(IntRect(sudoku[y][x] * 65, 0, 65, 65)); numbersS.setPosition(x * 65, y * 65); window.draw(numbersS);
				}
			}
		}if (k == 2 && f == 0) {
			for (int i = 6; i < 9; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					numbersS.setTextureRect(IntRect(715, 0, 65, 65)); numbersS.setPosition((i * 65), (j * 65));
					window.draw(numbersS);
					numbersS.setTextureRect(IntRect(sudoku[y][x] * 65, 0, 65, 65)); numbersS.setPosition(x * 65, y * 65); window.draw(numbersS);
				}
			}
		}if (k == 0 && f == 1) {
			for (int i = 0; i < 3; i++)
			{
				for (int j = 3; j < 6; j++)
				{
					numbersS.setTextureRect(IntRect(715, 0, 65, 65)); numbersS.setPosition((i * 65), (j * 65));
					window.draw(numbersS);
					numbersS.setTextureRect(IntRect(sudoku[y][x] * 65, 0, 65, 65)); numbersS.setPosition(x * 65, y * 65); window.draw(numbersS);
				}
			}
		}if (k == 0 && f == 2) {
			for (int i = 0; i < 3; i++)
			{
				for (int j = 6; j < 9; j++)
				{
					numbersS.setTextureRect(IntRect(715, 0, 65, 65)); numbersS.setPosition((i * 65), (j * 65));
					window.draw(numbersS);
					numbersS.setTextureRect(IntRect(sudoku[y][x] * 65, 0, 65, 65)); numbersS.setPosition(x * 65, y * 65); window.draw(numbersS);
				}
			}
		}if (k == 1 && f == 1) {
			for (int i = 3; i < 6; i++)
			{
				for (int j = 3; j < 6; j++)
				{
					numbersS.setTextureRect(IntRect(715, 0, 65, 65)); numbersS.setPosition((i * 65), (j * 65));
					window.draw(numbersS);
					numbersS.setTextureRect(IntRect(sudoku[y][x] * 65, 0, 65, 65)); numbersS.setPosition(x * 65, y * 65); window.draw(numbersS);
				}
			}
		}if (k == 2 && f == 2) {
			for (int i = 6; i < 9; i++)
			{
				for (int j = 6; j < 9; j++)
				{
					numbersS.setTextureRect(IntRect(715, 0, 65, 65)); numbersS.setPosition((i * 65), (j * 65));
					window.draw(numbersS);
					numbersS.setTextureRect(IntRect(sudoku[y][x] * 65, 0, 65, 65)); numbersS.setPosition(x * 65, y * 65); window.draw(numbersS);
				}
			}
		}
		if (k == 1 && f == 2) {
			for (int i = 3; i < 6; i++)
			{
				for (int j = 6; j < 9; j++)
				{
					numbersS.setTextureRect(IntRect(715, 0, 65, 65)); numbersS.setPosition((i * 65), (j * 65));
					window.draw(numbersS);
					numbersS.setTextureRect(IntRect(sudoku[y][x] * 65, 0, 65, 65)); numbersS.setPosition(x * 65, y * 65); window.draw(numbersS);
				}
			}
		}
		if (k == 2 && f == 1) {
			for (int i = 6; i < 9; i++)
			{
				for (int j = 3; j < 6; j++)
				{
					numbersS.setTextureRect(IntRect(715, 0, 65, 65)); numbersS.setPosition((i * 65), (j * 65));
					window.draw(numbersS);
					numbersS.setTextureRect(IntRect(sudoku[y][x] * 65, 0, 65, 65)); numbersS.setPosition(x * 65, y * 65); window.draw(numbersS);
				}
			}
		}
		for (int i = 0; i < 9; i++)
		{
			for (int j = 0; j < 9; j++)
			{
				temp = sudoku[i][j];
				switch (temp)
				{
				case 0: {numbersS.setTextureRect(IntRect(0, 0, 65, 65)); numbersS.setPosition(j * 65, i * 65);  break; }
				case 1: {numbersS.setTextureRect(IntRect(65, 0, 65, 65)); numbersS.setPosition(j * 65, i * 65); break; }
				case 2: {numbersS.setTextureRect(IntRect(130, 0, 65, 65)); numbersS.setPosition(j * 65, i * 65); break; }
				case 3: {numbersS.setTextureRect(IntRect(195, 0, 65, 65)); numbersS.setPosition(j * 65, i * 65); break; }
				case 4: {numbersS.setTextureRect(IntRect(260, 0, 65, 65)); numbersS.setPosition(j * 65, i * 65); break; }
				case 5: {numbersS.setTextureRect(IntRect(325, 0, 65, 65)); numbersS.setPosition(j * 65, i * 65); break; }
				case 6: {numbersS.setTextureRect(IntRect(390, 0, 65, 65)); numbersS.setPosition(j * 65, i * 65); break; }
				case 7: {numbersS.setTextureRect(IntRect(455, 0, 65, 65)); numbersS.setPosition(j * 65, i * 65); break; }
				case 8: {numbersS.setTextureRect(IntRect(520, 0, 65, 65)); numbersS.setPosition(j * 65, i * 65); break; }
				case 9: {numbersS.setTextureRect(IntRect(585, 0, 65, 65)); numbersS.setPosition(j * 65, i * 65); break; }
				case 10: {numbersS.setTextureRect(IntRect(650, 0, 65, 65)); numbersS.setPosition(j * 65, i * 65); break; }
				default: break;
				}

				window.draw(numbersS);
			}

		}rect.setTextureRect(IntRect(0, 0, 63, 63));
		rect.setPosition((x * 65) + 1, (y * 65) + 1);
		if (sudoku[y][x] != solsudoku[y][x])
		{
			if (sudoku[y][x] != 10 && sudoku[y][x] != 0)
			{
				checkisnumber = true;
			}
		}
		if (checkisnumber == true)
		{
			window.draw(rect);
			//numberstile.createMaskFromColor(Color::White);
			numbersS.setTextureRect(IntRect(sudoku[y][x] * 65, 0, 65, 65)); numbersS.setPosition(x * 65, y * 65); window.draw(numbersS);
		}
		checkisnumber = false;
		if (0 <= x && x < 9 && 0 <= y && y < 9)
		{
			for (int i = 0; i < 9; i++)
			{

				if (sudoku[y][i] == sudoku[y][x] && i != x) {
					numbersS.setTextureRect(IntRect((sudoku[y][x]) * 65, 65, 65, 65)); numbersS.setPosition((i * 65), (y * 65));
					window.draw(numbersS);
				}
			}
			for (int j = 0; j < 9; j++)
			{
				if (sudoku[j][x] == sudoku[y][x] && j != y) {
					numbersS.setTextureRect(IntRect((sudoku[y][x]) * 65, 65, 65, 65)); numbersS.setPosition((x * 65), (j * 65));
					window.draw(numbersS);
				}
			}
		}int ks, fs;
		ks = (y) / 3; ks *= 3;
		fs = (x) / 3; fs *= 3;
		if (0 <= x && x < 9 && 0 <= y && y < 9)
		{
			for (int i = ks; i < ks + 3; i++)
			{
				for (int j = fs; j < fs + 3; j++)
				{
					if (sudoku[i][j] == sudoku[y][x] && (i != y || j != x)) {
						numbersS.setTextureRect(IntRect((sudoku[y][x]) * 65, 65, 65, 65)); numbersS.setPosition((j * 65), (i * 65));
						window.draw(numbersS);
					}
				}
			}
		}

		window.draw(text);
		window.draw(mmain); 
		window.draw(mexit);
		window.display();
		if (isTue == 1) { finalscreen(window, text, font, winsound, playMusic, second, buff, start); }
	}
}
void finalscreen(RenderWindow& window, Text text, Font font, Sound winsound, bool playMusic, int second, int buff, bool start)
{
	//isTrue();
	if (isTue == true && second > 10)
	{  
		if (playMusic) { winsound.setVolume(100); winsound.play(); }
		Text ftext;
		ftext.setFont(font);
		ftext.setCharacterSize(24);
		ftext.setFillColor(sf::Color(20, 20, 60));
		ftext.setStyle(sf::Text::Bold);
		ftext.setPosition(310, 200);
		ftext.setString("YOU WIN!");
		std::ofstream highscore;
		highscore.open("highscore.txt");
		if (highscore.is_open())
		{
			if (second < buff || buff == 0)
			{
				highscore << second << std::endl;
			}
			else highscore << buff << std::endl;
		}
		while (isTue == true)
		{
			text.setPosition(310, 300);
			window.clear();
			window.draw(text);
			window.draw(ftext);
			window.display();
		}
	}
}