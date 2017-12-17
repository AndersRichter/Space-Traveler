#include <SFML/Graphics.hpp>
#include "map.hpp"
#include "view.hpp"
#include <iostream>

#define RIGHT 0
#define LEFT 1
#define DOWN 2
#define UP 3
#define UP_RIGHT 4
#define UP_LEFT 5
#define DOWN_RIGHT 6
#define DOWN_LEFT 7


class Player
{
	private:
		float x;
		float y;
	
	public:
		float w, h, dx, dy, speed ; //координаты игрока х и у, высота ширина, ускорение (по х и по у), сама скорость
 		int dir ; //направление (direction) движения игрока
 		sf::String file; //файл с расширением
 		sf::Image image;	//сфмл изображение
 		sf::Texture texture;	//сфмл текстура
 		sf::Sprite sprite;	//сфмл спрайт
	
	Player(sf::String F, float X, float Y, float W, float H)
	{ //Конструктор с параметрами(формальными) для класса Player. При создании объекта класса мы будем задавать имя файла, координату Х и У, ширину и высоту
		dx=0;
		dy=0;
		speed=0;
		dir=0;
 		file = F;//имя файла+расширение
 		w = W; 
		h = H;//высота и ширина
		image.loadFromFile("images/" + file);//запихиваем в image наше изображение вместо File мы передадим то, что пропишем при создании объекта. В нашем случае "hero.png" и получится запись идентичная image.loadFromFile("images/hero/png");
 		//image.createMaskFromColor(Color(41, 33, 59));//убираем ненужный темно-синий цвет, эта тень мне показалась не красивой.
 		texture.loadFromImage(image);//закидываем наше изображение в текстуру
		sprite.setTexture(texture);//заливаем спрайт текстурой
 		x = X; 
		y = Y;//координата появления спрайта
		sprite.setTextureRect(sf::IntRect(0, 0, w, h)); //Задаем спрайту один прямоугольник для вывода одного льва, а не кучи львов сразу. IntRect - приведение типов
 	}
	
	void update(float time) //функция "оживления" объекта класса. update - обновление. принимает в себя время SFML , вследствие чего работает бесконечно, давая персонажу движение.
 	{
 		switch (dir)	//реализуем поведение в зависимости от направления. (каждая цифра соответствует направлению)
 		{
			case RIGHT: dx = speed; dy = 0; break;//по иксу задаем положительную скорость, по игреку зануляем. получаем, что персонаж идет только вправо
			case LEFT: dx = -speed; dy = 0; break;//по иксу задаем отрицательную скорость, по игреку зануляем. получается, что персонаж идет только влево
			case DOWN: dx = 0; dy = speed; break;//по иксу задаем нулевое значение, по игреку положительное. получается, что персонаж идет только вниз
 			case UP: dx = 0; dy = -speed; break;//по иксу задаем нулевое значение, по игреку отрицательное. получается, что персонаж идет только вверх
			case UP_RIGHT: dx = speed; dy = -speed; break;
			case UP_LEFT: dx = -speed; dy = -speed; break;
			case DOWN_RIGHT: dx = speed; dy = speed; break;
			case DOWN_LEFT: dx = -speed; dy = speed; break;
		 }
 
		x += dx*time;//то движение из прошлого урока. наше ускорение на время получаем смещение координат и как следствие движение
 		y += dy*time;//аналогично по игреку
 
		speed = 0;//зануляем скорость, чтобы персонаж остановился.
 		sprite.setPosition(x,y); //выводим спрайт в позицию x y , посередине. бесконечно выводим в этой функции, иначе бы наш спрайт стоял на месте.
 	}
	
	float get_x()
	{
		return x;
	}
		
	float get_y()
	{
		return y;
	}
};


int main()
{
	sf::RenderWindow window(sf::VideoMode(900, 696), "Space Travaler");
	sf::Clock clock; //создаем переменную времени, т.о. привязка ко времени(а не загруженности/мощности процессора).
 	Player player("3_red.png", 5, 296, 352, 356);
	view.reset(sf::FloatRect(0, 0, 900, 696));//размер "вида" камеры при создании объекта вида камеры. (потом можем менять как хотим) Что то типа инициализации.
	
	sf::Image map_image;//объект изображения для карты
	map_image.loadFromFile("images/3_map.jpg");//загружаем файл для карты
	sf::Texture map;//текстура карты
	map.loadFromImage(map_image);//заряжаем текстуру картинкой
	sf::Sprite s_map;//создаём спрайт для карты
	s_map.setTexture(map);//заливаем текстуру спрайтом
	
	int chet = 0;
	
	//starsprite.setTextureRect(sf::IntRect(5,15,352,336));//получили нужный нам прямоугольник с котом
	//starsprite.setPosition(5, 296);//задаем начальные координаты появления спрайта
	player.sprite.setScale(0.27, 0.27);
	
	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asMicroseconds(); //дать прошедшее время в микросекундах
		float time_map;
		float time_player;
		
		clock.restart(); //перезагружает время
		time_map = time/600; //скорость игры
		time_player = time/200; //скорость игрока
		
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) 
		{ 
			player.dir = LEFT;
			player.speed = 0.1;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) 
		{ 
			if (player.get_x() <= chet+770)
			{
				player.dir = RIGHT;
				player.speed = 0.1;
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) 
		{
			if (player.get_y() > 92)
			{
				player.dir = UP;
				player.speed = 0.1;
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) 
		{
			if (player.get_y() <= 504)
			{
				player.dir = DOWN;
				player.speed = 0.1;
			}
		}
		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Left))&&(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)))
		{
			if (player.get_y() <= 92)
			{
				player.dir = LEFT;
				player.speed = 0.1;
			}
			else
			{
				player.dir = UP_LEFT;
				player.speed = 0.07;
			}
		}
		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Left))&&(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))) 
		{ 
			if (player.get_y() >= 504)
			{
				player.dir = LEFT;
				player.speed = 0.1;
			}
			else
			{
				player.dir = DOWN_LEFT;
				player.speed = 0.07;
			}
		}
		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Right))&&(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)))
		{ 
			if ((player.get_y() <= 92)&(player.get_x() <= 770))
			{
				player.dir = RIGHT;
				player.speed = 0.1;
			}
			if ((player.get_x() >= 770)&(player.get_y() >= 92))
			{
				player.dir = UP;
				player.speed = 0.1;
			}
			else
			{
				player.dir = UP_RIGHT;
				player.speed = 0.07;
			}
		}
		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Right))&&(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))) 
		{ 
			if (player.get_y() >= 504)
			{
				player.dir = RIGHT;
				player.speed = 0.1;
			}
			if (player.get_x() >= 770)
			{
				player.dir = DOWN;
				player.speed = 0.1;
			}
			else
			{
				player.dir = DOWN_RIGHT;
				player.speed = 0.07;
			}
		}
		if (player.get_x() <= chet+10)
		{
			player.dir = RIGHT;
			player.speed = 0.07;
			player.update(time_map);
		}
 
		player.update(time_player);//оживляем объект p класса Player с помощью времени sfml, передавая время в качестве параметра функции update. благодаря этому персонаж может двигаться
		
		window.setView(view);//"оживляем" камеру в окне sfml
		window.clear();
		
		camera_move(chet);
		
		for (int i = 0; i < WIDTH_MAP; i++)
		{
			if (TileMap[i] == 's') s_map.setTextureRect(sf::IntRect(0, 0, 619, 696));
			if (TileMap[i] == 'p') s_map.setTextureRect(sf::IntRect(619, 0, 619, 696));
			if (TileMap[i] == 'i') s_map.setTextureRect(sf::IntRect(1238, 0, 619, 696));
			
			s_map.setPosition(i * 619, 0);//по сути раскидывает квадратики, превращая в карту. то есть задает каждому из них позицию. если убрать, то вся карта нарисуется в одном квадрате 32*32 и мы увидим один квадрат
 
			window.draw(s_map);
		}
		window.draw(player.sprite);
		window.display();
		
		chet += 0.1*time_map;
		
		//std::cout << "x = " << player.get_x() << "    chet = " << chet << std::endl;
	}
 
	return 0;
}
