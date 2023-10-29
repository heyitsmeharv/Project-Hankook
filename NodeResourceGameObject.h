#pragma once

#include "GameObject.h"

namespace hk
{
	class Texture;

	struct NodeStage
	{
		const Texture*	texture = nullptr;
		std::string		resource_key;
		double			amount_on_change = 0.0;
	};

	struct NodeResourceGameObjectInitInfo : public GameObjectInitInfo
	{
		std::vector<NodeStage>	stages;
		int						starting_stage;
	};

	class NodeResourceGameObject : public GameObject
	{
	public:
				 NodeResourceGameObject(NodeResourceGameObjectInitInfo& init_info);
		virtual ~NodeResourceGameObject();

		void				OnInteraction(GameObject& interacting_obect) override;

		void				DecrementStage	();
		const NodeStage&	CurrentStage	() const;

	protected:
		std::vector<NodeStage>	m_stages;
		int						m_current_stage;
	};
}