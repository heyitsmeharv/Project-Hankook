#pragma once

#include <memory>

namespace hk
{
	class ControllerInstance;
	class GameObject;

	class PlayerController
	{
	public:
				 PlayerController();
				 PlayerController(GameObject* game_object);
		virtual ~PlayerController();

		void OnInputChange() const;

		void AttachGameObject		 (GameObject* game_object);
		void AttachControllerInstance(std::unique_ptr<ControllerInstance>&& controller_instance);

		void SetDisabled(const bool is_disabled);
		bool IsDisabled() const;

	protected:
		int			m_id;
		GameObject* m_game_object;
		bool		m_is_disabled;

		std::unique_ptr<ControllerInstance> m_controller_instance;
	};
}