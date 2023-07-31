#pragma once
#include <list>
#include "Actor.h"

namespace kiko
{
	class Renderer; //reduce amount of header calls
	//class Actor; //forward declaration

	class Scene
	{
	public:
		Scene() = default;
		
		void Update(float dt);
		void Draw(Renderer& renderer);

		void Add(std::unique_ptr<Actor> actor);
		void RemoveAll();

		template<typename T>
		T* GetActor();

		friend class Actor;
		
	private:
		std::list<std::unique_ptr<Actor>> m_actors;
		// A vector is a dynamic array. When you push back past the size of the vector, it will duplicate the array to double space
		// A list is a node or block of data. Is much simpler to add or remove data than a vector. "Remove slot 5", the list just skips that slot
	};

	template<typename T>
	inline T* Scene::GetActor()
	{
		for (auto& actor : m_actors)
		{
			T* result = dynamic_cast<T*>(actor.get()); //tries to cast data to type provided
			if (result) return result; // if not nullptr
		}

		return nullptr;
	}

}