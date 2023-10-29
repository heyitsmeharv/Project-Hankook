#pragma once

#include <vector>
#include <memory>
#include <string>
#include <optional>

#include "Collidable.h"
#include "CollisionInterface.h"
#include "Drawable.h"
#include "ListenerReporter.h"
#include "Resource.h"
#include "Transformable.h"
#include "ImGuiUser.h"

namespace hk
{
	class GameObject;
	using GameObjectList = std::vector<std::unique_ptr<GameObject>>;

	class Texture;
	struct GameObjectCollisionVisitor;

	struct GameObjectInitInfo
	{
		std::string						id;
		Vector2f						position = { 0, 0 };
		Vector2i						dimensions = { 0, 0 };
		const Texture*					texture = nullptr;
		bool							is_interactable = false;
		float							interaction_range = 0.0f;
		std::optional<SDL_Color>		colour_mod = std::nullopt;
		std::vector<ResourceInitInfo>	resources_info;
	};

	class GameObject	: public Drawable
						, public Transformable
						, public CollisionInterface
						, public IImGuiUser
	{
	public:
				 GameObject(const GameObjectInitInfo& init_info);
		virtual ~GameObject();

				void Destroy();

		virtual void Update	(const double delta_time);
				void Draw	() const override;

		//----- HIERARCHY -----
		void					AddChild(std::unique_ptr<GameObject>&& child);
		GameObjectList&			GetChildren();
		const GameObjectList&	GetChildren() const;

		//----- VISIBILITY -----
		bool	IsVisible			() const;
		void	SetIsVisible		(const bool is_visible);
		void	ToggleVisibility	();

		//----- TRANSFORM -----
		void	SetPosition		(float new_x_pos, float new_y_pos) override;
		void	SetPosition		(const Vector2f& new_pos) override;

		void	MovePosition	(float x_delta, float y_delta) override;
		void	MovePosition	(const Vector2f& delta) override;

		//----- COLLISION -----
		void	AddCollidable(Collidable&& collidable);

		void	Visit		(const GameObjectCollisionVisitor& visitor) override;

		void	HandleCollision(GameObject& rhs) override;

		void	OnCollide	(GameObject& rhs) override;
		void	OnCollide	(PowerUpGameObject& power_up) override;
		void	OnCollide	(ProjectileGameObject& projectile) override;

		//----- INTERACTIONS -----
		bool			IsInteractable		() const;
		void			SetInteractable		(const bool is_interactable);
		virtual void	OnInteraction		(GameObject&);
		virtual float	InteractableRange	() const;

		//----- RESOURCES -----
		Resource*		GetResource(const std::string& resource_key);
		const Resource* GetResource(const std::string& resource_key) const;

		//----- UTILITY -----
		static void			SetRootObject(GameObject& root_object);
		static GameObject*	RootObject();

		const std::string&	GetId		() const;
		bool				IsDisabled	() const;

		bool IsPointDirectlyWithinObject	(const Vector2f& point) const;
		bool IsPointWithinObjectOrChildren	(const Vector2f& point) const;

		template<typename F>
		GameObject* FindClosestGameObject(F filter_func) const
		{
			GameObject* closest_object = nullptr;

			if (hk::GameObject::RootObject())
			{
				float shortest_dist = std::numeric_limits<float>::max();

				std::vector<GameObject*> to_check;
				to_check.reserve(1024);
				to_check.push_back(hk::GameObject::RootObject());

				while (to_check.empty() == false)
				{
					GameObject* current = to_check.front();
					if (filter_func(current))
					{
						if ((current->GetPosition() - m_position).MagnitudeSquared() < shortest_dist)
						{
							closest_object = current;
						}
					}

					for (auto& child : current->GetChildren())
					{
						to_check.push_back(child.get());
					}

					to_check.erase(to_check.begin());
				}
			}

			return closest_object;
		}

		//----- DEBUG -----
		void AddToImGui() override;

	protected:
		std::string						m_id;
		GameObject*						m_parent;
		GameObjectList					m_children;
		const Texture*					m_texture;
		bool							m_is_visible;
		bool							m_is_disabled;
		bool							m_is_interactable;
		float							m_interaction_range;
		std::optional<SDL_Color>		m_colour_mod;
		std::optional<Collidable>		m_collidable;
		std::vector<Resource>			m_resources;

		static inline GameObject* m_root_object = nullptr;
	};
}