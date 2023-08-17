#pragma once

#include <vector>
#include <memory>
#include <string>
#include <optional>

#include "Drawable.h"
#include "Transformable.h"
#include "ImGuiUser.h"

namespace hk
{
	class GameObject;
	using GameObjectList = std::vector<std::unique_ptr<GameObject>>;

	class Texture;

	struct GameObjectInitInfo
	{
		std::string id;
		Vector2f position = { 0, 0 };
		Vector2i dimensions = { -1, -1 };
		const Texture* texture = nullptr;
		std::optional<SDL_Color> colour_mod = std::nullopt;
	};

	class GameObject	: public Drawable
						, public Transformable
						, public IImGuiUser
	{
	public:
				 GameObject(GameObjectInitInfo& init_data);
		virtual ~GameObject();

				void Destroy();

		virtual void Update	(const double delta_time);
				void Draw	(const DrawInfo& draw_info) const override;


		//----- HIERARCHY -----
		void					AddChild(std::unique_ptr<GameObject>&& child);
		GameObjectList&			GetChildren();
		const GameObjectList&	GetChildren() const;

		//----- VISIBILITY -----
		bool IsVisible			() const;
		void SetIsVisible		(const bool is_visible);
		void ToggleVisibility	();

		//----- TRANSFORM -----
		void SetPosition		(float new_x_pos, float new_y_pos) override;
		void SetPosition		(const Vector2f& new_pos) override;

		void MovePosition		(float x_delta, float y_delta) override;
		void MovePosition		(const Vector2f& delta) override;

		//---- LIFETIME -----
		bool IsAlive() const;

		//----- UTILITY -----
		static void			SetRootObject(GameObject& root_object);
		static GameObject*	RootObject();

		bool IsPointDirectlyWithinObject(const Vector2f& point) const;
		bool IsPointWithinObjectOrChildren(const Vector2f& point) const;

		//----- DEBUG -----
		void AddToImGui() override;

	protected:
		std::string					m_id;
		GameObject*					m_parent;
		GameObjectList				m_children;
		const Texture*				m_texture;
		bool						m_is_visible;
		bool						m_is_alive;
		std::optional<SDL_Color>	m_colour_mod;

		static inline GameObject* m_root_object = nullptr;
	};
}