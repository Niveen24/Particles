#include "Engine.h"

Engine::Engine()
{
	m_Window.create(VideoMode::getDesktopMode(), "Particles", Style::Default);
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
				for (int i = 0; i < 5; i++) //create 5 particles
				{
					int numPoints = rand() % 26 + 25; //random num 25-50
					Particle p(m_Window, numPoints, { event.mouseButton.x, event.mouseButton.y }); //make particle at mouse click coords
					m_particles.push_back(p); //add particle to vector
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
}

void Engine::draw()
{
	m_Window.clear();
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