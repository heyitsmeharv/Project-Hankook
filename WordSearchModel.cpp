#include "WordSearchModel.h"

#include "KeyboardMouseInstance.h"
#include "Engine.h"
#include "GridGenerator.h"

#include "CountdownModeComponent.h"
#include "GridComponent.h"
#include "PlayerControllerComponent.h"
#include "TimedModeComponent.h"

#include "GameOverScreen.h"
#include "WordSearchScreen.h"
#include "WordSearchModelAccess.h"
#include "WordFoundEvent.h"

namespace hk
{
	WordSearchModel::WordSearchModel(Engine& engine)
		: BaseModel(engine)
		, m_model_command_queue()
		, m_registry()
		, m_camera_system()
		, m_game_mode_system(m_registry)
		, m_rendering_system()
		, m_ui_system(m_registry)
		, m_grid_entity(entt::null)
	{
	}

	WordSearchModel::~WordSearchModel()
	{
	}

	void WordSearchModel::Initialise()
	{
		m_registry.ctx().emplace<WordSearchModelAccess>(this);

		//----- GRID -----
		m_grid_entity = m_registry.create();
		GridComponent& grid_component = m_registry.emplace<GridComponent>(m_grid_entity);
		grid_component.height = 24;
		grid_component.width = 24;
		grid_component.word_list.push_back("agatha");
		grid_component.word_list.push_back("brilliant");
		grid_component.word_list.push_back("chlorophyll");
		grid_component.word_list.push_back("delta");
		grid_component.word_list.push_back("elephant");
		grid_component.word_list.push_back("fiddlesticks");
		grid_component.word_list.push_back("gráveyárd");
		grid_component.word_list.push_back("harrísón");
		grid_component.word_list.push_back("igloo");
		grid_component.word_list.push_back("jack");
		grid_component.word_list.push_back("koala");

		GridGenerator::GenerateGrid(grid_component);

		//----- GAME MODE -----
		m_game_mode_system.Initialise();

		entt::entity mode_entity = m_registry.create();
		CountdownModeComponent& countdown_component = m_registry.emplace<CountdownModeComponent>(mode_entity);
		countdown_component.time_limit_in_s = 10.0;
		countdown_component.time_left = 10.0;
		m_game_mode_system.SetCurrentMode(m_grid_entity, GameModes::COUNTDOWN, mode_entity);

		//TimedModeComponent& timed_component = m_registry.emplace<TimedModeComponent>(mode_entity);
		//timed_component.current_time = 0.0;
		//m_game_mode_system.SetCurrentMode(m_grid_entity, GameModes::TIMED, mode_entity);

		//----- CAMERA -----
		CameraInitInfo camera_init_info;
		camera_init_info.id = "main";
		camera_init_info.position = { 0.0f, 0.0f };
		camera_init_info.dimensions = m_engine.GameWindow().GetWindowDimensions();
		camera_init_info.zoom = 1.0f;

		m_camera_system.PushNewCamera(m_registry, camera_init_info);

		//----- UI -----
		std::unique_ptr<ui::WordSearchScreen> main_screen = std::make_unique<ui::WordSearchScreen>(m_registry);
		main_screen->SetGameInfo(m_grid_entity, mode_entity, GameModes::COUNTDOWN);
		m_ui_system.ChangeScreen(std::move(main_screen));
	}

	void WordSearchModel::Destroy()
	{
	}

	void WordSearchModel::Update(const double delta_time)
	{
		m_ui_system.HandleInput(m_engine.GetInputDeviceManager());

		ProcessModelCommands();

		const bool was_game_over = m_game_mode_system.IsGameOver();
		m_game_mode_system.Update(delta_time);
		if (was_game_over == false && m_game_mode_system.IsGameOver())
		{
			HandleGameOver();
		}

		m_ui_system.Update(delta_time);
		m_rendering_system.Update(m_registry, m_camera_system.CurrentCamera(), m_engine);
	}

	void WordSearchModel::QueueModelCommand(std::unique_ptr<ModelCommand>&& model_command)
	{
		m_model_command_queue.AddToQueue(std::move(model_command));
	}

	const entt::registry& WordSearchModel::GetRegistry() const
	{
		return m_registry;
	}

	bool WordSearchModel::LoadPlayerController()
	{
		std::unique_ptr<ControllerInstance> controller_instance = std::make_unique<hk::KeyboardMouseInstance>(&m_engine.GetInputDeviceManager().GetDefaultKeyboardMouse());

		entt::entity player_controller_entity = m_registry.create();
		PlayerControllerComponent& player_controller = m_registry.emplace<PlayerControllerComponent>(player_controller_entity);
		player_controller.id = "player_1";
		player_controller.controller = std::move(controller_instance);
		player_controller.is_enabled = true;

		return true;
	}

	void WordSearchModel::ProcessModelCommands()
	{
		m_model_command_queue.ProcessQueue(m_registry);
		m_model_command_queue.ClearQueue();
	}

	void WordSearchModel::OnWordFound(const std::string& word, std::vector<Vector2i>&& cell_list)
	{
		NotifyListeners(WordFoundEvent{ word, std::move(cell_list) });
	}

	void WordSearchModel::HandleGameOver()
	{
		ui::GameOverScreenInitInfo init_info;
		init_info.grid_entity = m_grid_entity;
		init_info.game_mode = m_game_mode_system.GetCurrentMode();
		init_info.finish_time = m_game_mode_system.GetCurrentTimeOnTimer();

		std::unique_ptr<ui::GameOverScreen> gameover_screen = std::make_unique<ui::GameOverScreen>(m_registry, init_info);
		m_ui_system.ChangeScreen(std::move(gameover_screen));
	}
}