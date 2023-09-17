#include "GameObject.h"

#include "CollisionResolver.h"
#include "Engine.h"
#include "InputCommand.h"
#include "ProjectileGameObject.h"
#include "TextureDrawRequest.h"
#include "Texture.h"

namespace hk
{
	GameObject::GameObject(const GameObjectInitInfo& info)
		: Drawable()
		, Transformable()
		, m_id(std::move(info.id))
		, m_parent(nullptr)
		, m_texture(info.texture)
		, m_is_visible(true)
		, m_is_disabled(false)
		, m_colour_mod(info.colour_mod)
		, m_collidable(std::nullopt)
	{
		SetDimensions(info.dimensions);
		SetPosition(info.position);
	}

	GameObject::~GameObject()
	{
		Destroy();
	}

	void GameObject::Destroy()
	{
		if (m_collidable)
		{
			GetEngine().GetCollisionSystem().DeregisterCollidable(*m_collidable);
		}

		m_children.clear();

		//We have no ownership over these things so don't delete them, just null
		m_texture = nullptr;
		m_parent = nullptr;
	}

	void GameObject::Update(const double delta_time)
	{
		if (IsDisabled() == false && m_children.empty() == false)
		{
			m_health.Update(delta_time);

			for(auto& child : m_children)
			{
				if (child)
				{
					child->Update(delta_time);
				}
			}
		}
	}

	void GameObject::Draw() const
	{
		if (IsVisible() && IsDisabled() == false)
		{
			if (m_texture)
			{
				std::unique_ptr<TextureDrawRequest> draw_request = std::make_unique<TextureDrawRequest>();

				draw_request->texture = m_texture;
				draw_request->draw_info.dimensions = m_dimensions;
				draw_request->draw_info.position = { (int)m_position.x, (int)m_position.y };
				draw_request->draw_info.flip = m_flip;
				draw_request->draw_info.angle_in_deg = m_rotation_in_deg;
				draw_request->draw_info.colour_mod = m_colour_mod;
				draw_request->draw_info.viewport_rect = GetEngine().GetCameraManager().CurrentCamera()->GetCameraRect();

				AddDrawToQueue(std::move(draw_request));
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
				Vector2f new_pos = m_position;
				if (ImGui::InputFloat("X: ", &new_pos.x))
				{
					SetPosition(new_pos);
				}

				if (ImGui::InputFloat("Y: ", &new_pos.y))
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
	void GameObject::SetPosition(float new_x_pos, float new_y_pos)
	{
		SetPosition({ new_x_pos, new_y_pos });
	}

	void GameObject::SetPosition(const Vector2f& new_pos)
	{
		Vector2f diff{ new_pos.x - m_position.x, new_pos.y - m_position.y };
		m_position = new_pos;

		for (auto& child : m_children)
		{
			if (child)
			{
				child->MovePosition(diff);
			}
		}
	}

	void GameObject::MovePosition(float x_delta, float y_delta)
	{
		MovePosition({ x_delta, y_delta });
	}

	void GameObject::MovePosition(const Vector2f& delta)
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

	//----- COLLISION -----
	void GameObject::AddCollidable(Collidable&& collidable)
	{
		m_collidable = std::move(collidable);
		m_collidable->SetOwner(*this);

		GetEngine().GetCollisionSystem().RegisterCollidable(*m_collidable);
	}

	void GameObject::HandleCollision(GameObject& rhs)
	{
		ResolveCollisionVisitor visitor(*this);
		rhs.Visit(visitor);
	}

	void GameObject::Visit(const GameObjectCollisionVisitor& visitor)
	{
		visitor.Visit(*this);
	}

	void GameObject::OnCollide(GameObject& rhs)
	{
		//Do nothing
	}

	void GameObject::OnCollide(PowerUpGameObject& power_up)
	{
		//add a resource modifier?
		//Do nothing? We'll work this shit out later
	}

	void GameObject::OnCollide(ProjectileGameObject& projectile)
	{
		//Damage health?
		projectile.HitObject(*this);
	}


	//----- HEALTH -----
	double GameObject::CurrentHealth() const
	{
		return m_health.CurrentAmount();
	}

	void GameObject::ChangeHealth(const double delta)
	{
		m_health.ChangeAmount(delta);
	}

	void GameObject::SetHealth(const double new_amount)
	{
		m_health.SetCurrentAmount(new_amount);
	}

	void GameObject::AddHealthModifier(ResourceModifier* new_modifier)
	{
		m_health.AddModifier(new_modifier);
	}

	//----- UTILITY -----
	void GameObject::SetRootObject(GameObject& root_object)
	{
		m_root_object = &root_object;
	}

	GameObject* GameObject::RootObject()
	{
		return m_root_object;
	}

	const std::string& GameObject::GetId() const
	{
		return m_id;
	}

	bool GameObject::IsDisabled() const
	{
		return m_is_disabled;
	}

	bool GameObject::IsPointDirectlyWithinObject(const Vector2f& point) const
	{
		const bool is_within_bounds_x = point.x >= m_position.x && (point.x + m_dimensions.x) <= point.x;
		const bool is_within_bounds_y = point.y >= m_position.y && (point.y + m_dimensions.y) <= point.y;

		return is_within_bounds_x && is_within_bounds_y;
	}

	bool GameObject::IsPointWithinObjectOrChildren(const Vector2f& point) const
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