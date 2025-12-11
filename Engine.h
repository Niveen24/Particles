#pragma once
#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Particle.h"
using namespace sf;
using namespace std;

class Engine
{
private:
	// A regular RenderWindow
	RenderWindow m_Window;

	//vector for Particles
	vector<Particle> m_particles;

	// Private functions for internal use only
	void input();
	void update(float dtAsSeconds);
	void draw();


	//stuff for stewie griffin extra credit :D
	Texture texture;
	Sprite sprite;
	Texture bgTexture;
	Sprite bgSprite;
	SoundBuffer soundBuffers[9]; //actual sound stuff
	Sound sound; //to play the sounds
	int currentIndex = 0;
	bool gotHit = false; //start as hitless
	float hitTimer = 0.0;
	Vector2f originalSpritePos; //will used for shake
	float shakeStrength = 8.0;


public:
	// The Engine constructor
	Engine();

	// Run will call all the private functions
	void run();

};