#pragma once

#include <memory>

namespace hk
{
	class Camera;
	class ControllerInstance;
	class GameObject;

	class PlayerController
	{
	public:
				 PlayerController();
				 PlayerController(GameObject& game_object, Camera* camera);
		virtual ~PlayerController();

		void Update() const;

		void AttachGameObject			(GameObject& game_object);
		void AttachCamera				(Camera& camera);
		void AttachControllerInstance	(std::unique_ptr<ControllerInstance>&& controller_instance);

		void SetDisabled(const bool is_disabled);
		bool IsDisabled() const;

	protected:
		int			m_id;
		GameObject* m_game_object;
		Camera*		m_camera;

		bool		m_is_disabled;

		std::unique_ptr<ControllerInstance> m_controller_instance;
	};
}