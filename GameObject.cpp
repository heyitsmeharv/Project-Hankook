#include "Command.h"
#include "GameObject.h"

#include "Texture.h"
#include "imgui/imgui.h"

namespace hk
{
	GameObject::GameObject(std::string&& id, const Vector2i& position, const Vector2i& dimensions, const Texture* texture)
		: Drawable()
		, Transformable()
		, m_id(std::move(id))
		, m_parent(nullptr)
		, m_texture(texture)
		, m_is_visible(true)
	{
		SetDimensions(dimensions);
		SetPosition(position);
	}

	GameObject::~GameObject()
	{
		Destroy();
	}

	void GameObject::Destroy()
	{
		m_children.clear();

		//We have no ownership over these things so don't delete them, just null
		m_texture = nullptr;
		m_parent = nullptr;
	}

	void GameObject::Draw() const
	{
		if (IsVisible())
		{
			if (m_texture)
			{
				hk::TextureDrawInfo draw_info = {};
				draw_info.dimensions = m_dimensions;
				draw_info.position = m_position;
				draw_info.flip = m_flip;
				draw_info.angle_in_deg = m_rotation_in_deg;

				m_texture->Draw(draw_info);
			}

			for (const auto& child : m_children)
			{
				if (child)
				{
					child->Draw();
				}
			}
		}
	}

	void GameObject::AddToImGui()
	{
		if (ImGui::TreeNode(this, "%s", m_id.data()))
		{
			ImGui::Checkbox("Is Visible: ", &m_is_visible);

			if (ImGui::TreeNode("Position"))
			{
				//We don't directly access m_position as that bypasses the hierarchy
				Vector2i new_pos = m_position;
				if (ImGui::InputInt("X: ", &new_pos.x))
				{
					SetPosition(new_pos);
				}

				if (ImGui::InputInt("Y: ", &new_pos.y))
				{
					SetPosition(new_pos);
				}

				ImGui::TreePop();
			}

			if (ImGui::TreeNode("Dimensions"))
			{
				ImGui::InputInt("Width: ", &m_dimensions.x);
				ImGui::InputInt("Height: ", &m_dimensions.y);

				ImGui::TreePop();
			}

			if (m_children.empty() == false && ImGui::TreeNode("Children"))
			{
				for (auto& child : m_children)
				{
					if (child)
					{
						child->AddToImGui();
					}
				}

				ImGui::TreePop();
			}

			ImGui::TreePop();
		}
	}

	//----- HIERARCHY -----
	void GameObject::AddChild(std::unique_ptr<GameObject>&& child)
	{
		m_children.push_back(std::move(child));
	}

	GameObjectList& GameObject::GetChildren()
	{
		return m_children;
	}

	const GameObjectList& GameObject::GetChildren() const
	{
		return m_children;
	}

	//----- VISIBILITY -----
	bool GameObject::IsVisible() const
	{
		return m_is_visible;
	}

	void GameObject::SetIsVisible(const bool is_visible)
	{
		m_is_visible = is_visible;
	}

	void GameObject::ToggleVisibility()
	{
		m_is_visible = m_is_visible == false;
	}

	//----- TRANSFORM -----
	void GameObject::SetPosition(int new_x_pos, int new_y_pos)
	{
		SetPosition({ new_x_pos, new_y_pos });
	}

	void GameObject::SetPosition(const Vector2i& new_pos)
	{
		Vector2i diff{ new_pos.x - m_position.x, new_pos.y - m_position.y };
		m_position = new_pos;

		for (auto& child : m_children)
		{
			if (child)
			{
				child->MovePosition(diff);
			}
		}
	}

	void GameObject::MovePosition(int x_delta, int y_delta)
	{
		MovePosition({ x_delta, y_delta });
	}

	void GameObject::MovePosition(const Vector2i& delta)
	{
		m_position += delta;

		for (auto& child : m_children)
		{
			if (child)
			{
				child->MovePosition(delta);
			}
		}
	}

	//----- UTILITY -----
	bool GameObject::IsPointDirectlyWithinObject(const Vector2i& point) const
	{
		const bool is_within_bounds_x = point.x >= m_position.x && (point.x + m_dimensions.x) <= point.x;
		const bool is_within_bounds_y = point.y >= m_position.y && (point.y + m_dimensions.y) <= point.y;

		return is_within_bounds_x && is_within_bounds_y;
	}

	bool GameObject::IsPointWithinObjectOrChildren(const Vector2i& point) const
	{
		if (IsPointDirectlyWithinObject(point))
		{
			return true;
		}

		for (const auto& child : m_children)
		{
			if (child)
			{
				if (child->IsPointWithinObjectOrChildren(point))
				{
					return true;
				}
			}
		}

		return false;
	}
}