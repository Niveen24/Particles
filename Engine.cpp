#include "Engine.h"

Engine::Engine()
{
	m_Window.create(VideoMode::getDesktopMode(), "Particle Guy", Style::Default);

	//stewie stuff:
	texture.loadFromFile("assets/stewie5.png");
	sprite.setTexture(texture);
	sprite.setOrigin(texture.getSize().x / 2.0, texture.getSize().y / 2.0);
	sprite.setPosition(m_Window.getSize().x / 2.0, m_Window.getSize().y / 2.0);
	originalSpritePos = sprite.getPosition();
	//bg
	bgTexture.loadFromFile("assets/background.jpg");
	bgSprite.setTexture(bgTexture);
	bgSprite.setPosition(0, 0);
	float scaleX = (m_Window.getSize().x / float(bgTexture.getSize().x)) * 1.0;
	float scaleY = (m_Window.getSize().y / float(bgTexture.getSize().y)) * 1.0;
	bgSprite.setScale(scaleX, scaleY);
	//load stewie sounds
	soundBuffers[0].loadFromFile("assets/audio_stewie_4.wav");
	soundBuffers[1].loadFromFile("assets/audio_stewie.wav");
	soundBuffers[2].loadFromFile("assets/what-the-deuce.wav");
	soundBuffers[3].loadFromFile("assets/audio_stewie_3.wav");
	soundBuffers[4].loadFromFile("assets/audio_peter_3.wav");
	soundBuffers[5].loadFromFile("assets/audio_peter_2.wav");
	soundBuffers[6].loadFromFile("assets/does-a-dog-not-feel.wav");
}

void Engine::input()
{
	Event event;
	while (m_Window.pollEvent(event))
	{
		if (event.type == Event::Closed)
		{
			m_Window.close(); //quit game when closed
		}

		if (event.type == sf::Event::MouseButtonPressed)
		{
			if (event.mouseButton.button == sf::Mouse::Left)	//if left mouse button clicked
			{

				//stewie stuff:

				Vector2f mousePos = m_Window.mapPixelToCoords(Vector2i(event.mouseButton.x, event.mouseButton.y)); //gets mouse pos
				bool spriteHit = sprite.getGlobalBounds().contains(mousePos);	//checks if mouse pos is inside stewie bounds
				if (spriteHit)
				{
					currentIndex = (currentIndex + 1) % 7;	//cycle stewie image

					string images[7] =	//ADD IMAGES HERE
					{
						"assets/stewie5.png",
						"assets/stewie2.png",
						"assets/stewie4.png",
						"assets/stewie3.png",
						"assets/Peter_Griffin.png",
						"assets/peter2.png",
						"assets/brian.png"
					};

					texture.loadFromFile(images[currentIndex]);
					sprite.setTexture(texture, true);
					sprite.setOrigin(texture.getSize().x / 2.0, texture.getSize().y / 2.0);
					Texture bgTexture;
					Sprite bgSprite;
					sound.setBuffer(soundBuffers[currentIndex]);//soud change
					sound.play();
					gotHit = true; //oh no someone hit stewie
					hitTimer = 0.15;
					sprite.setColor(Color::Red); //make him red
					//particle burst
					Vector2f pos = sprite.getPosition();
					Vector2i pixelPos((int)pos.x, (int)pos.y);

						for (int b = 0; b < 120; b++) //bigger burst
						{
							int offx = (rand() % 1400) - 700; //-700 to 700
							int offy = (rand() % 1400) - 700;

							if (rand() % 4 == 0)
							{
								offx /= 4;
								offy /= 4;
							}

							if (rand() % 7 == 0)
							{
								offx *= 2;
								offy *= 2;
							}

							Vector2i pos(pixelPos.x + offx, pixelPos.y + offy); //random offset from stewie pos
							int numPoints = rand() % 26 + 25;
							Particle burst(m_Window, numPoints, pos);	//make particle at mouse click

							burst.setColors(Color::Red, Color::Yellow); //make stewie hit particles red/yellow
							m_particles.push_back(burst);

						}
				}
				
				else   //normal particles as per assignment, else state so it doesnt do this if stewie is hit
				{
					for (int i = 0; i < 5; i++) //create 5 particles
					{
						int numPoints = rand() % 26 + 25; //random num 25-50
						Particle p(m_Window, numPoints, { event.mouseButton.x, event.mouseButton.y }); //make particle at mouse click coords
						m_particles.push_back(p); //add particle to vector
					}
				}
			}
		}
	}

	if (Keyboard::isKeyPressed(Keyboard::Escape))	//if escape key pressed, exit
	{
		m_Window.close();
	}
}

void Engine::update(float dtAsSeconds)
{
	for (auto i = m_particles.begin(); i != m_particles.end();)
	{
		if (i->getTTL() > 0.0) //particle still alive
		{
			i->update(dtAsSeconds);
			i++;
		}
		else //ttl dead x_x
		{
			i = m_particles.erase(i); //erases particle and i == next element
		}
	}


	//stewie stuff:

	if (gotHit)
	{
		hitTimer -= dtAsSeconds;	//timer for hit 

		//shake stewie around orig position
		float offsetX = (float)(rand() % (int)(2 * shakeStrength)) - shakeStrength;
		float offsetY = (float)(rand() % (int)(2 * shakeStrength)) - shakeStrength;
		sprite.setPosition(originalSpritePos.x + offsetX, originalSpritePos.y + offsetY);

		if (hitTimer <= 0.0) //timer done
		{
			gotHit = false;
			sprite.setColor(Color::White); //red tint off
			sprite.setPosition(originalSpritePos);
		}
	}
}

void Engine::draw()
{
	m_Window.clear();
	m_Window.draw(bgSprite); //background
	m_Window.draw(sprite); //STEWIE
	for (auto& particle : m_particles)	//for each object in particle vector
	{
		m_Window.draw(particle);	//calls polymorphic draw NOT the sfml draw
	}
	m_Window.display();
}

void Engine::run()
{
	Clock clock; //local clock to track time per frame

	//unit test code
	cout << "Starting Particle unit tests..." << endl;	
	Particle p(m_Window, 4, { (int)m_Window.getSize().x / 2, (int)m_Window.getSize().y / 2 });
	p.unitTests();
	cout << "Unit tests complete.  Starting engine..." << endl;

	//game loop
	while (m_Window.isOpen())
	{
		Time dt = clock.restart(); //restart clock
		float dtSeconds = dt.asSeconds();
		input();
		update(dtSeconds);
		draw();
	}
}