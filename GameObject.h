#pragma once

#include <vector>
#include <memory>
#include <string>

#include "Drawable.h"
#include "Transformable.h"
#include "ImGuiUser.h"

namespace hk
{
	class GameObject;
	using GameObjectList = std::vector<std::unique_ptr<GameObject>>;

	class Texture;

	class GameObject	: public Drawable
						, public Transformable
	{
	public:
				 GameObject(std::string&& id, const Vector2i& position, const Vector2i& dimensions, const Texture* texture);
		virtual ~GameObject();

		void Destroy();

		//----- HIERARCHY -----
		void					AddChild(std::unique_ptr<GameObject>&& child);
		GameObjectList&			GetChildren();
		const GameObjectList&	GetChildren() const;

		//----- VISIBILITY -----
		bool IsVisible			() const;
		void SetIsVisible		(const bool is_visible);
		void ToggleVisibility	();

		//----- TRANSFORM -----
		void SetPosition		(int new_x_pos, int new_y_pos) override;
		void SetPosition		(const Vector2i& new_pos) override;

		void MovePosition		(int x_delta, int y_delta) override;
		void MovePosition		(const Vector2i& delta) override;

		//----- UTILITY -----
		bool IsPointDirectlyWithinObject(const Vector2i& point) const;
		bool IsPointWithinObjectOrChildren(const Vector2i& point) const;

		void Draw() const override;

		void AddToImGui();

	protected:
		std::string		m_id;
		GameObject*		m_parent;
		GameObjectList	m_children;
		const Texture*	m_texture;
		bool			m_is_visible;
	};
}