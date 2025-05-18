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
namespace FILES {
    namespace MENU {
        namespace IMAGES {
            const std::string BACKGROUND = "resources/images/menu/background.jpg";
            const std::string BUTTON_NEW_GAME = "resources/images/menu/button_new_game.png";
            const std::string BUTTON_OPTIONS = "resources/images/menu/button_options.png";
            const std::string BUTTON_EXIT = "resources/images/menu/button_exit.png";
            const std::string BUTTON_EASY = "resources/images/menu/button_easy.png";
            const std::string BUTTON_MEDIUM = "resources/images/menu/button_medium.png";
            const std::string BUTTON_HARD = "resources/images/menu/button_hard.png";
            const std::string BUTTON_TIMED = "resources/images/menu/button_timed.png";
            const std::string BUTTON_RECORD = "resources/images/menu/button_record.png";
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
	
	namespace OPTION {
		const int NONE = 0;
		const int EASY = 1;
		const int MEDIUM = 2;
		const int HARD = 3;
		const int TIMED = 4;
	}
}
namespace MENU {
	namespace STATE {
		const int NEW_GAME = 1;
		const int OPTIONS = 2;
		const int EXIT = 3;
	}
}

bool isDifficultyMenuActive = false;
bool isTimeLimitActive = false;
bool isMainMenuActive = true;

int selectedDifficulty = DIFFICULTY::OPTION::NONE;

namespace UI {	
	namespace POSITION {
		const sf::Vector2f BACKGROUND(0.f, 0.f);
        const sf::Vector2f MENU_MAIN(250.f, 240.f);
        const sf::Vector2f MENU_ABOUT(250.f, 340.f);
        const sf::Vector2f MAIN_MENU_EXIT(250.f, 440.f);
        const sf::Vector2f MENU_RECORD(0.f, 540.f);
		const sf::Vector2f MENU_OPTIONS(80.f, 200.f);
        const sf::Vector2f MENU_EXIT(390.f, 200.f);
        const sf::Vector2f MENU_EASY(80.f, 300.f);
        const sf::Vector2f MENU_MEDIUM(390.f, 300.f);
		
	}
}
sf::Text createMessage(const std::string& message, const sf::Font& font, unsigned int size = 24, const sf::Color& color = sf::Color(20, 20, 60), float x = 310, float y = 200)
{
	sf::Text text;
	text.setFont(font);
	text.setCharacterSize(size);
	text.setFillColor(color);
	text.setStyle(sf::Text::Bold);
	text.setPosition(x, y);
	text.setString(message);
	return text;
}
void showMainMenu(RenderWindow& window, Sound sound, bool playMusic, Font font, int buff, int sd)
{
	int menunum = 0;
	Image record;
	record.loadFromFile(FILES::MENU::IMAGES::BUTTON_RECORD);
	record.createMaskFromColor(Color::White);
	Texture mainTexture, aboutTexture, exitTexture, backgroundTexture, recordTexture;
	backgroundTexture.loadFromFile(FILES::MENU::IMAGES::BACKGROUND);
	mainTexture.loadFromFile(FILES::MENU::IMAGES::BUTTON_NEW_GAME);
	aboutTexture.loadFromFile(FILES::MENU::IMAGES::BUTTON_OPTIONS);
	exitTexture.loadFromFile(FILES::MENU::IMAGES::BUTTON_EXIT);
	recordTexture.loadFromImage(record);
	Sprite menuMain(mainTexture), menuAbout(aboutTexture), menuExit(exitTexture), menuBackground(backgroundTexture), menuRecord(recordTexture);
	menuBackground.setPosition(UI::POSITION::BACKGROUND);
	menuMain.setPosition(UI::POSITION::MENU_MAIN);
	menuAbout.setPosition(UI::POSITION::MENU_ABOUT);
	menuExit.setPosition(UI::POSITION::MAIN_MENU_EXIT);
	menuRecord.setPosition(UI::POSITION::MENU_RECORD);
	sf::Text bestResultText = createMessage("YOU DON'T WIN YET", font, 32, sf::Color::Black, 130, 540);
	std::ostringstream stringh, stringd;
	if (buff <= 0 || buff > 300)
	{
		sf::Text bestResultText;
	}
	else {
		int ftime = buff / 60, fminutes = buff - (ftime * 60);
		stringh << fminutes; stringd << ftime;
		sf::Text bestResultText = createMessage(String(stringd.str() + " : " + stringh.str()), font, 32, sf::Color::Black, 130, 540);
	}
	while (isMainMenuActive)
	{
		menuMain.setColor(Color::White); menuAbout.setColor(Color::White); menuExit.setColor(Color::White); menuRecord.setColor(Color::White);
		//window.clear(Color::White);
		if (IntRect(250, 240, 225, 45).contains(Mouse::getPosition(window))) { menuMain.setColor(Color::Cyan); menunum = MENU::STATE::NEW_GAME; }
		if (IntRect(250, 340, 225, 45).contains(Mouse::getPosition(window))) { menuAbout.setColor(Color::Cyan); menunum = MENU::STATE::OPTIONS; }
		if (IntRect(250, 440, 225, 45).contains(Mouse::getPosition(window))) { menuExit.setColor(Color::Cyan); menunum = MENU::STATE::EXIT; }
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			sound.play();
			if (menunum == MENU::STATE::NEW_GAME) { isMainMenuActive = false; }
			if (menunum == MENU::STATE::OPTIONS) { isDifficultyMenuActive = true; isMainMenuActive = false; }
			if (menunum == MENU::STATE::EXIT) { window.close(); isMainMenuActive = false; }
		}
		window.draw(menuBackground); window.draw(menuMain); window.draw(menuAbout); window.draw(menuExit); window.draw(menuRecord);
		window.draw(bestResultText); window.display();
	};
}
void showDifficultyMenu(RenderWindow& window, bool playMusic)
{
	Texture menuEasy, menuMedium, menuHard, background, menuTimed;
	background.loadFromFile(FILES::MENU::IMAGES::BACKGROUND);
	menuEasy.loadFromFile(FILES::MENU::IMAGES::BUTTON_EASY);
	menuMedium.loadFromFile(FILES::MENU::IMAGES::BUTTON_MEDIUM);
	menuHard.loadFromFile(FILES::MENU::IMAGES::BUTTON_HARD);
	menuTimed.loadFromFile(FILES::MENU::IMAGES::BUTTON_TIMED);
	Sprite menu1(menuEasy), menu2(menuMedium), menu3(menuHard), menuBackground(background), menu4(menuTimed);
	menu1.setPosition(UI::POSITION::MENU_OPTIONS);
	menu2.setPosition(UI::POSITION::MENU_EXIT);
	menu3.setPosition(UI::POSITION::MENU_EASY);
	menu4.setPosition(UI::POSITION::MENU_MEDIUM);
	int menuDifficulty = DIFFICULTY::OPTION::NONE;
	while (isDifficultyMenuActive)
	{
		menu1.setColor(Color::White); menu2.setColor(Color::White); menu3.setColor(Color::White); menu4.setColor(Color::White);
		if (IntRect(80, 200, 225, 45).contains(Mouse::getPosition(window))) { menu1.setColor(Color::Cyan); menuDifficulty = DIFFICULTY::OPTION::EASY; }
		if (IntRect(390, 200, 225, 45).contains(Mouse::getPosition(window))) { menu2.setColor(Color::Cyan); menuDifficulty = DIFFICULTY::OPTION::MEDIUM; }
		if (IntRect(80, 300, 225, 45).contains(Mouse::getPosition(window))) { menu3.setColor(Color::Cyan); menuDifficulty = DIFFICULTY::OPTION::HARD; }
		if (IntRect(390, 300, 225, 45).contains(Mouse::getPosition(window))) { menu4.setColor(Color::Cyan); menuDifficulty = DIFFICULTY::OPTION::TIMED; }
		
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			if (menuDifficulty == DIFFICULTY::OPTION::EASY) { playMusic = false; selectedDifficulty = DIFFICULTY::EASY; isDifficultyMenuActive = false; }
			if (menuDifficulty == DIFFICULTY::OPTION::MEDIUM) { selectedDifficulty = DIFFICULTY::MEDIUM; isDifficultyMenuActive = false; }
			if (menuDifficulty == DIFFICULTY::OPTION::HARD) { selectedDifficulty = DIFFICULTY::HARD; isDifficultyMenuActive = false; }
			if (menuDifficulty == DIFFICULTY::OPTION::TIMED) { isTimeLimitActive = true; selectedDifficulty = DIFFICULTY::DEFAULT;  isDifficultyMenuActive = false; }
		}window.clear(); window.draw(menuBackground); window.draw(menu1); window.draw(menu2); window.draw(menu3); window.draw(menu4); window.display();
	}
}
void finalScreen(RenderWindow& window, Text text, Font font, Sound winsound, bool playMusic, int second, int buff, bool start);
void setTimeLimit(int minutes, int time, Text text, Font font, RenderWindow& window, Sound losesound, bool playMusic)
{   
	if (playMusic) { losesound.setVolume(100); losesound.play(); }
	sf::Text loseText = createMessage("YOU LOSE!", font);
	while (minutes == 5 && time == 1)
	{
		text.setPosition(310, 300);
		window.clear();
		window.draw(text);
		window.draw(loseText);
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
	showMainMenu(window, sound, playMusic, font, buff, 0);
	if (isDifficultyMenuActive == true) { showDifficultyMenu(window, playMusic); }
	if (playMusic) { back.setVolume(0); losesound.setVolume(0); winsound.setVolume(0); sound.setVolume(0); }
	a = selectedDifficulty;
	if (a == 0) { a = DIFFICULTY::DEFAULT; }
	finish();
	print();
	Image icon;
	icon.loadFromFile(FILES::GAME::IMAGES::ICON);
	window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
	Texture main;
	main.loadFromFile(FILES::MENU::IMAGES::BUTTON_NEW_GAME);
	Sprite mmain(main);
	mmain.setPosition(605, 80);
	mmain.setScale(Vector2f(0.5, 0.5));
	Texture exit;
	exit.loadFromFile(FILES::MENU::IMAGES::BUTTON_EXIT);
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
	sf::Text gameOverText = createMessage("GAME OVER", font, 24, sf::Color(20, 20, 60), 600, 0);
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
		if (isTimeLimitActive == true) { setTimeLimit(minutes, timet, gameOverText, font, window, losesound, playMusic); }
		std::ostringstream strings, stringm;
		stringm << minutes; strings << timet;
		if (timet < 10 && minutes < 10){
			gameOverText.setString("Game time\n\t\t\t0" + stringm.str() + " : 0" + strings.str());
		}
		else if (timet < 10){
			gameOverText.setString("Game time\n\t\t\t" + stringm.str() + " : " + "0" + strings.str());
		}
		else {
			gameOverText.setString("Game time\n\t\t\t" + stringm.str() + " : " + strings.str());
		}
		gameOverText.setPosition(600, 0);
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
					if (schecker[y][x] == 0) { sudoku[y][x] = 0; }
					break;
				case sf::Keyboard::Numpad1:
				case sf::Keyboard::Num1:
					if (schecker[y][x] == 0) { sudoku[y][x] = 1; isTrue(); }//if (solsudoku[y][x] != sudoku[y][x]) numbersS.;
					break;
				case sf::Keyboard::Numpad2:
				case sf::Keyboard::Num2:
					if (schecker[y][x] == 0) { sudoku[y][x] = 2; isTrue(); }
					break;
				case sf::Keyboard::Numpad3:
				case sf::Keyboard::Num3:
					if (schecker[y][x] == 0) { sudoku[y][x] = 3; isTrue(); }
					
					break;
				case sf::Keyboard::Numpad4:
				case sf::Keyboard::Num4:
					if (schecker[y][x] == 0) { sudoku[y][x] = 4; isTrue();}
					break;
				case sf::Keyboard::Numpad5:
				case sf::Keyboard::Num5:
					if (schecker[y][x] == 0) { sudoku[y][x] = 5; isTrue(); }
					break;
				case sf::Keyboard::Numpad6:
				case sf::Keyboard::Num6:
					if (schecker[y][x] == 0) { sudoku[y][x] = 6; isTrue(); }
					break;
				case sf::Keyboard::Numpad7:
				case sf::Keyboard::Num7:
					if (schecker[y][x] == 0) { sudoku[y][x] = 7; isTrue(); }
					break;
				case sf::Keyboard::Numpad8:
				case sf::Keyboard::Num8:
					if (schecker[y][x] == 0) { sudoku[y][x] = 8; isTrue(); }
					break;
				case sf::Keyboard::Numpad9:
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

		window.draw(gameOverText);
		window.draw(mmain); 
		window.draw(mexit);
		window.display();
		if (isTue == 1) { finalScreen(window, gameOverText, font, winsound, playMusic, second, buff, start); }
	}
}
void finalScreen(RenderWindow& window, Text text, Font font, Sound winsound, bool playMusic, int second, int buff, bool start)
{
	//isTrue();
	if (isTue == true && second > 10)
	{  
		if (playMusic) { winsound.setVolume(100); winsound.play(); }
		sf::Text winText = createMessage("YOU WIN!", font);
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
			window.draw(winText);
			window.display();
		}
	}
}