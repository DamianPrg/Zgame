#pragma once

#include <cmath>
#include <cassert>
#include <iostream>

#include "SFML\Graphics.hpp"

// GFramework
namespace Gf
{
	/**
	  * Window
	  */
	extern sf::RenderWindow* window;

	/**
	  * Vector2
	  */
	class Vector2
	{
	public:

		Vector2() : X(0.0f), Y(0.0f) {}
		Vector2(float a, float b) : X(a), Y(b) {}

		float Length()
		{
			return sqrtf(this->X*this->X + this->Y*this->Y);
		}

		static float Distance(Vector2 a, Vector2 b)
		{
			Vector2 v;
			v.X = b.X - a.X;
			v.Y = b.Y - a.Y;
			return abs(v.Length());
		}

		Vector2 Normalized()
		{
			Vector2 norm;
			norm.X = this->X / this->Length();
			norm.Y = this->Y / this->Length();
			return norm;
		}

		void Normalize()
		{
			Vector2 l = Normalized();
			this->X = l.X;
			this->Y = l.Y;
		}

		static Vector2 GetVelocityToPoint(Vector2 from, Vector2 p)
		{
			Vector2 t;
			t.X = p.X - from.X;
			t.Y = p.Y - from.Y;
			return t.Normalized();
		}

		float X, Y;
	};

	inline void Log(std::string loc, std::string s)
	{
		std::cout << "[ " << loc << " ]: " << s << std::endl;
	}

	/**
	* Sprite
	*/
	class Sprite
	{
	public:
		Sprite() {
			this->Rotated = 0.0f;
			this->Rotation = 0.0f;
			this->Scale = 1.0f;
			this->Position = Vector2(0.0f, 0.0f);
			this->Color = sf::Color(255, 255, 255, 255);
			sprite = new sf::Sprite;
			texture = nullptr;
		}

		void Load(std::string filename)
		{
			texture = new sf::Texture;
			texture->loadFromFile(filename);
			texture->setSmooth(true);
			this->sprite->setTexture(*texture);
		}

		void SetTexture(std::string filename)
		{
			//if (filename != textureNameUsed)
		//	{
				texture->loadFromFile(filename);
				this->sprite->setTexture(*texture);

			//	textureNameUsed = filename;
			//}
		}

		void Draw()
		{
			sprite->setPosition(Position.X, Position.Y);
			sprite->setRotation(Rotation - Rotated);
			sprite->setScale(Scale, Scale);
			sprite->setColor(Color);

			window->draw(*sprite);
		}

		void DrawTiled(int max_x, int max_y)
		{
			for (int y = 0; y < max_y; y++)
			{
				for (int x = 0; x < max_x; x++)
				{
					float _x = x * texture->getSize().x;
					float _y = y * texture->getSize().y;

					sprite->setPosition(_x, _y);
					window->draw(*sprite);
				}
			}
		}

		void MakeHalfTransparent(bool yes)
		{
			if (yes)
				Color.a = 255.0f * 0.5f;
			else
				Color.a = 255.0f;
		}

		void MakeOriginCenter(bool yes=true)
		{
			if (yes)
				this->sprite->setOrigin(texture->getSize().x / 2, texture->getSize().y / 2);
			else 
				this->sprite->setOrigin(0.0f, 0.0f);
		}

		int GetWidth()
		{
			return texture->getSize().x;
		}

		int GetHeight()
		{
			return texture->getSize().y;
		}

		~Sprite() {
			delete sprite;
		}

		float        Rotation;
		float        Scale;
		Gf::Vector2  Position;
		sf::Color    Color;

		float        Rotated; // how many degrees is sprite rotated already in image file? (if it is facing right then this value should be set to 90.0f)

		sf::Sprite*  sprite;
		sf::Texture* texture;
	
		std::string textureNameUsed;
	};

	class IGame
	{
	public:
		virtual void Initialize() {}
		virtual void Update(float dt) {}
		virtual void Draw() {}

		// storing pointers
		std::vector<void*> pointers;
		std::vector<std::string> pointer_names;

		template<typename T> void store(T* p, std::string name)
		{
				void* gptr = reinterpret_cast<void*>(p);
				
				pointers.push_back(gptr);
				pointer_names.push_back(name);
			
		}

		template<typename T> T* get(std::string name)
		{
			for (int i = 0; i < pointer_names.size(); i++)
			{
				if (pointer_names[i] == name)
				{
					T* p = reinterpret_cast<T*>(pointers[i]);
					return p;
				}
			}

			return nullptr;
		}

		void release()
		{
			for (int i = 0; i < pointers.size(); i++)
			{
				delete pointers[i];
			}
		}
	};

	// Game instance
	extern IGame* game;

	class GameObject
	{
	public:
		virtual void Create() {}
		virtual void Update(float dt) {}
		virtual void Draw() {}

		void Teleport(Vector2 new_location)
		{
			Position = new_location;
		}

		void DrawSprite(Gf::Sprite* sprite, Gf::Vector2 offset = Gf::Vector2(0.0f, 0.0f))
		{
			assert(sprite != nullptr);

			sprite->Position.X = Position.X + offset.X;
			sprite->Position.Y = Position.Y + offset.Y;

			sprite->Draw();
		}

		void UpdatePosition()
		{
			Position.X += Velocity.X;
			Position.Y += Velocity.Y;
		}

		bool Touches(GameObject* Other)
		{
			//not finished, just for testign
			if (this->Position.X > Other->Position.X && this->Position.X < Other->Position.X + Other->Size.X &&
				this->Position.Y > Other->Position.Y && this->Position.Y < Other->Position.Y + Other->Size.Y)
			{
				return true;
			}

			return false;
		}

		bool TouchesAtX(GameObject* Other)
		{
			if (this->Position.X + this->Size.X > Other->Position.X && this->Position.X < Other->Position.X + Other->Size.X)
			{
				return true;
			}

			return false;
		}

		bool TouchesAtY(GameObject* Other)
		{

		}

		bool TouchesAtXY(GameObject* Other)
		{
			if (TouchesAtX(Other) && TouchesAtY(Other)) return true;

			return false;
		}
	
	public:
		Vector2 Position, Velocity, Size;
 
	};

	template<typename T=GameObject>
	class GameObjContainer
	{
	public:
		void Add(T* obj)
		{
			objs.push_back(obj);
		}

		void Update(float dt)
		{
			for (auto o : objs)
			{
				o->Udate(dt);
			}
		}

		void Draw()
		{
			for (auto o : objs)
			{
				o->Draw();
			}
		}

		void Release()
		{
			for (int i = 0; i < objs.size(); i++)
			{
				delete objs;
			}
		}
	public:
		std::vector<T*> objs;
	};

	// Animation
	class Animation
	{
	public:
		void Import(Animation* otherAnimation)
		{
			frame_filenames = otherAnimation->frame_filenames;
		}

		void AddFrame(std::string path)
		{
			frame_filenames.push_back(path);
		}

		void AddFrames(std::string directory, std::string name, int frames, std::string ext = "png")
		{
			for (int i = 0; i < frames; i++)
			{
				std::string fn = "";
				fn += directory;
				fn += name;
				fn += std::to_string(i);
				fn += ".";
				fn += ext;

				std::cout << "[ Gf::Animation:Frame ]: " << fn << std::endl;

				this->AddFrame(fn);
			}
		}

		// plays animation on sprite, must be called in update function.
		void Play(Gf::Sprite* sprite, float frame_time = 0.1f)
		{
			if (animClock.getElapsedTime().asSeconds() > frame_time)
			{
				if (frame >= frame_filenames.size())
				{
					frame = 0;
				
				}

				sprite->SetTexture(frame_filenames[frame]);
				
				frame++;
				animClock.restart();
			}
		}

		// use this one to play same animation on more sprites.
		void Play(Gf::Sprite* sprite, float frame_time, int* stored_frame_index)
		{
			if (animClock.getElapsedTime().asSeconds() > frame_time)
			{
				if ((*stored_frame_index) >= frame_filenames.size())
				{
					(*stored_frame_index) = 0;

				}

				sprite->SetTexture(frame_filenames[(*stored_frame_index)]);

				(*stored_frame_index)++;
				animClock.restart();
			}
		}
	private:
		std::vector<std::string> frame_filenames;
		int frame;
		sf::Clock animClock;
	};

	// AnimationSet
	class AnimationSet
	{
	public:
		AnimationSet() {
			sprite = nullptr;
			PlayedAnimation = "idle";
		}

		void SetSprite(Gf::Sprite * s) {
			sprite = s;
		}

		void Add(std::string name, Animation anim)
		{
			names.push_back(name);
			animations.push_back(anim);
		}

		void Play()
		{
			assert(sprite != nullptr);

			Animation& animPlayed = GetAnimation(PlayedAnimation);
			animPlayed.Play(sprite, 0.1f);
		}

		Animation& GetAnimation(std::string name)
		{
			for (int i = 0; i < animations.size(); i++)
			{
				if (name == names[i]) return animations[i];
			}

			return animations[0];
		}

		Gf::Sprite* sprite;
		std::vector<Animation> animations;
		std::vector<std::string> names;

		std::string PlayedAnimation;
	};

	class Camera
	{
	public:
		
		void Create()
		{
			View = window->getDefaultView();
		}

		void Update()
		{
			window->setView(View);
		}

		sf::View View;
	};

	class Collision
	{

	};

	class GameObject_Collidable : public 
		GameObject
	{
	public:
		bool IsInside(GameObject* Other)
		{
			// return false;
			return false;
		}

		// helper functions
	};


}