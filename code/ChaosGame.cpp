// Include important C++ libraries here
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <sstream>
#include <vector>

//Make the code easier to type with "using namespace"
using namespace sf;
using namespace std;


int main()
{
	// Create a video mode object
	int pixelWidth = VideoMode::getDesktopMode().width;
	int pixelHeight = VideoMode::getDesktopMode().height;
	VideoMode vm(pixelWidth, pixelHeight);
	// Create and open a window for the game
	RenderWindow window(vm, "Chaos Game!!", Style::Default);

	Font font;
	font.loadFromFile("font/RobotoSlab-Black.ttf");

	Text message;
	message.setFont(font);
	message.setString("Please click the mouse in 4 different spots.");
	message.setFillColor(Color::White);

	//srand(time(0));
	
	vector<Vector2f> vertices;
	vector<Vector2f> points;
	const float RATIO = 0.5;
	const int VERTS = 3;
	int lastVert = -1;


	while (window.isOpen())
	{
		/*
		****************************************
		Handle the players input
		****************************************
		*/
		Event event;
		while (window.pollEvent(event))
		{
		    if (event.type == Event::Closed)
		    {
					// Quit the game when the window is closed
					window.close();
		    }
		    if (event.type == sf::Event::MouseButtonPressed)
		    {
			if (event.mouseButton.button == sf::Mouse::Left)
			{
			    std::cout << "the left button was pressed" << std::endl;
			    std::cout << "mouse x: " << event.mouseButton.x << std::endl;
			    std::cout << "mouse y: " << event.mouseButton.y << std::endl;
	
			    if(vertices.size() < VERTS)
			    {
				vertices.push_back(Vector2f(event.mouseButton.x, event.mouseButton.y));
			    }
			    else if(points.size() == 0)
			    {
				///fourth click
				///push back to points vector
				points.push_back(Vector2f(event.mouseButton.x, event.mouseButton.y));
			    }
			}
		    }
		}
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}
		/*
		****************************************
		Update
		****************************************
		*/
	
		if(points.size() > 0)
		{
		    ///generate more point(s)
		    ///select random vertex
		    ///calculate midpoint between random vertex and the last point in the vector
		    ///push back the newly generated coord.
			for (int i = 0; i < 2; i++)
			{
				int randNum = rand() % VERTS;
				//check to see if vertice is use twice in a row
				while (randNum == lastVert && VERTS > 3)
				{
					randNum = rand() % VERTS;
				}
				lastVert = randNum;
				Vector2f randVert = vertices[randNum];
				Vector2f latestPoint = points.back();
				Vector2f newPoint;




				newPoint.x = latestPoint.x + (randVert.x - latestPoint.x) * RATIO;
				newPoint.y = latestPoint.y + (randVert.y - latestPoint.y) * RATIO;

				points.push_back(newPoint);
			}
			

		}
	
		/*
		****************************************
		Draw
		****************************************
		*/
		window.clear();
		for(int i = 0; i < vertices.size(); i++)
		{
		    CircleShape circle(1);
		    circle.setPosition(vertices[i]);
		    circle.setFillColor(Color::Red);
		    window.draw(circle);
		}
		///TODO:  Draw points
		for (int i = 0; i < points.size(); i++)
		{
			CircleShape circle(1);
			circle.setPosition(points[i]);
			circle.setFillColor(Color::Red);
			window.draw(circle);
		}
		window.draw(message);
		window.display();
	}
}
