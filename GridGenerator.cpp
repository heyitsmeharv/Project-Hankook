#include "GridGenerator.h"

#include <entt/entt.hpp>
#include <algorithm>

#include "GridComponent.h"
#include "Rng.h"

namespace hk
{
	bool GridGenerator::GenerateGrid(GridComponent& grid)
	{
		grid.cell_list.resize(grid.width * grid.height, placeholder_char);

		const int backout_limit = 10;
		int backout_counter = 0;

		//Order the word list to longest word -> shortest word
		std::sort(grid.word_list.begin(), grid.word_list.end(), [](const auto& lhs, const auto& rhs) { return lhs.size() > rhs.size(); });

		for (const auto& word_to_be_placed : grid.word_list)
		{
			if (static_cast<int>(word_to_be_placed.size()) > std::min<int>(grid.width, grid.height))
			{
				continue;
			}

			backout_counter = 0;

			Orientations orientation = NUM_OF_ORIENTATIONS;
			std::vector<Vector2i> cell_coords;

			bool is_placed = false;
			while (is_placed == false)
			{
				if (backout_counter >= backout_limit)
				{
					return {};
				}

				cell_coords.clear();

				//Pick a random orientation
				orientation = static_cast<Orientations>(Rng::GetInRange(0, Orientations::NUM_OF_ORIENTATIONS - 1));
				const bool should_letter_share = Rng::GetInRange(0, 3) >= 3;

				std::vector<std::vector<Vector2i>> possible_locations;

				//Build the index list
				switch (orientation)
				{
					case VERTICAL:
					{
						if (should_letter_share)
						{
							//Does any placed word share any letters with our current word
							for (const auto& [placed_word, word_info] : grid.word_infos)
							{
								//If the word shares the same orientation, sharing a letter is not possible
								if (word_info.orientation != VERTICAL)
								{
									for (size_t l = 0; l < word_to_be_placed.size(); ++l)
									{
										//If we share a letter...
										int shared_letter_pos = placed_word.find(word_to_be_placed[l]);
										if (shared_letter_pos != -1)
										{
											//Does the shared letter have room above and below it to fit the word?
											const int shared_y_index = word_info.locations[shared_letter_pos].y;

											const int y_min = shared_y_index - l;
											const int y_max = shared_y_index + (word_to_be_placed.size() - l - 1);

											if (y_min >= 0 && y_max < grid.height)
											{
												std::vector<Vector2i> location_list;
												location_list.reserve(placed_word.size());

												bool had_collision = false;
												for (int n = y_min; n <= y_max; ++n)
												{
													Vector2i new_pos{ word_info.locations[shared_letter_pos].x, n };

													//Check for collisions to make sure we can place here
													if (new_pos == word_info.locations[shared_letter_pos] || grid.cell_list[grid.CoordToIndex(new_pos)] == placeholder_char)
													{
														location_list.emplace_back(word_info.locations[shared_letter_pos].x, n);

														if (location_list.size() > word_to_be_placed.size())
														{
															__debugbreak();
														}
													}
													else
													{
														had_collision = true;
														break;
													}
												}

												//Only push this as a possible location if there are no collisions
												if (had_collision == false)
												{
													possible_locations.push_back(location_list);
												}
											}
										}
									}
								}
							}

							//Pick a random entry in that list and place word
							if (possible_locations.empty() == false)
							{
								cell_coords = possible_locations[Rng::GetInRange(0, possible_locations.size() - 1)];
								if (cell_coords.size() != word_to_be_placed.size())
								{
									__debugbreak();
								}

								is_placed = true;
							}
						}

						if (cell_coords.empty())
						{
							const int required_space = word_to_be_placed.size();
							std::vector<Vector2i> column_locations;
							column_locations.reserve(required_space);

							//Loop through all columns
							for (int c = 0; c < grid.width; ++c)
							{
								//Does the current column have enough space for the current word?
								for (int r = 0; r < grid.height; ++r)
								{
									if (grid.cell_list[grid.CoordToIndex({ c, r })] == placeholder_char)
									{
										column_locations.emplace_back(c, r);
									}
									else 
									{
										column_locations.clear();
									}

									//If so, push it to a list
									if (static_cast<int>(column_locations.size()) >= required_space)
									{
										possible_locations.push_back(column_locations);
										column_locations.clear();
									}
								}

								column_locations.clear();
							}
						}

						//Pick a random entry in the list and place word
						if (possible_locations.empty() == false)
						{
							cell_coords = possible_locations[Rng::GetInRange(0, possible_locations.size() - 1)];
							is_placed = true;

							if (cell_coords.size() != word_to_be_placed.size())
							{
								__debugbreak();
							}
						}

						break;
					}
					case HORIZONTAL:
					{
						if (should_letter_share)
						{
							//Does any placed word share any letters with our current word
							for (const auto& [placed_word, word_loc_info] : grid.word_infos)
							{
								//If the word shares the same orientation, sharing a letter is not possible
								if (word_loc_info.orientation != HORIZONTAL)
								{
									for (size_t l = 0; l < word_to_be_placed.size(); ++l)
									{
										//If we share a letter...
										int shared_letter_pos = placed_word.find(word_to_be_placed[l]);
										if (shared_letter_pos != -1)
										{
											//Does the shared letter have room left and right to fit the word?
											const int shared_x_index = word_loc_info.locations[shared_letter_pos].x;

											const int x_min = shared_x_index - l;
											const int x_max = shared_x_index + (word_to_be_placed.size() - l - 1);

											if (x_min >= 0 && x_max < grid.width)
											{
												std::vector<Vector2i> location_list;
												location_list.reserve(placed_word.size());

												bool had_collision = false;
												for (int n = x_min; n <= x_max; ++n)
												{
													Vector2i new_pos{ n, word_loc_info.locations[shared_letter_pos].y };

													//Check for collisions to make sure we can place here
													if (new_pos == word_loc_info.locations[shared_letter_pos] || grid.cell_list[grid.CoordToIndex(new_pos)] == placeholder_char)
													{
														location_list.emplace_back(n, word_loc_info.locations[shared_letter_pos].y);
													}
													else
													{
														had_collision = true;
														break;
													}
												}

												//Only push this as a possible location if there are no collisions
												if (had_collision == false)
												{
													possible_locations.push_back(location_list);
												}
											}
										}
									}
								}
							}

							//Pick a random entry in that list and place word
							if (possible_locations.empty() == false)
							{
								cell_coords = possible_locations[Rng::GetInRange(0, possible_locations.size() - 1)];
								is_placed = true;

								if (cell_coords.size() != word_to_be_placed.size())
								{
									__debugbreak();
								}
							}
						}

						if (cell_coords.empty())
						{
							const int required_space = word_to_be_placed.size();
							std::vector<Vector2i> row_locations;
							row_locations.reserve(required_space);

							//Loop through all rows
							for (int r = 0; r < grid.height; ++r)
							{
								//Does the current row have enough space for the current word?
								for (int c = 0; c < grid.width; ++c)
								{
									if (grid.cell_list[grid.CoordToIndex({ c, r })] == placeholder_char)
									{
										row_locations.emplace_back(c, r);
									}
									else
									{
										row_locations.clear();
									}

									//If so, push it to a list
									if (static_cast<int>(row_locations.size()) >= required_space)
									{
										possible_locations.push_back(row_locations);
										row_locations.clear();
									}
								}

								row_locations.clear();
							}
						}

						//Pick a random entry in the list and place word
						if (possible_locations.empty() == false)
						{
							cell_coords = possible_locations[Rng::GetInRange(0, possible_locations.size() - 1)];
							is_placed = true;

							if (cell_coords.size() != word_to_be_placed.size())
							{
								__debugbreak();
							}
						}

						break;
					}
					case DIAGONAL:
					{
						if (should_letter_share)
						{
							//Does any placed word share any letters with our current word
							for (const auto& [placed_word, word_loc_info] : grid.word_infos)
							{
								for (size_t l = 0; l < word_to_be_placed.size(); ++l)
								{
									//If we share a letter...
									int shared_letter_pos = placed_word.find(word_to_be_placed[l]);
									if (shared_letter_pos != -1)
									{
										//Does the shared letter have room around it to fit the word?
										const int shared_x_index = word_loc_info.locations[shared_letter_pos].x;
										const int shared_y_index = word_loc_info.locations[shared_letter_pos].y;

										const int x_min = shared_x_index - l;
										const int x_max = shared_x_index + (word_to_be_placed.size() - l - 1);

										const int y_min = shared_y_index - l;
										const int y_max = shared_y_index + (word_to_be_placed.size() - l - 1);

										if (x_min >= 0 && x_max < grid.width && y_min >= 0 && y_max < grid.height)
										{
											std::vector<Vector2i> location_list;
											location_list.reserve(word_to_be_placed.size());

											bool had_collision = false;
											for (int delta = 0; delta < static_cast<int>(word_to_be_placed.size()); ++delta)
											{
												Vector2i new_pos{ x_min + delta, y_min + delta };

												//Check for collisions to make sure we can place here
												if (new_pos == word_loc_info.locations[shared_letter_pos] || grid.cell_list[grid.CoordToIndex(new_pos)] == placeholder_char)
												{
													location_list.emplace_back(new_pos);
												}
												else
												{
													had_collision = true;
													break;
												}
											}

											//Only push this as a possible location if there are no collisions
											if (had_collision == false)
											{
												possible_locations.push_back(location_list);
											}
										}
									}
								}
							}

							//Pick a random entry in that list and place word
							if (possible_locations.empty() == false)
							{
								cell_coords = possible_locations[Rng::GetInRange(0, possible_locations.size() - 1)];
								is_placed = true;

								if (cell_coords.size() != word_to_be_placed.size())
								{
									__debugbreak();
								}
							}
						}

						if (cell_coords.empty())
						{
							const int required_space = word_to_be_placed.size();
							std::vector<Vector2i> column_locations;
							column_locations.reserve(required_space);

							//Loop through every single cell and find eligble directions
							for (int c = 0; c < grid.width; ++c)
							{
								for (int r = 0; r < grid.height; ++r)
								{
									std::vector<Vector2i> directions;
									directions.reserve(4);

									for (int y_dir = -1; y_dir <= 1; y_dir += 2)
									{
										for (int x_dir = -1; x_dir <= 1; x_dir += 2)
										{
											const int x_bound = c + (required_space * x_dir);
											const int y_bound = r + (required_space * y_dir);

											if (x_bound >= 0 && x_bound < grid.width && y_bound >= 0 && y_bound < grid.height)
											{
												directions.emplace_back(x_dir, y_dir);
											}
										}
									}

									//Once we have all valid directions, loop through them and look for collisions
									std::vector<Vector2i> letter_locations;
									letter_locations.reserve(required_space);

									for (const auto& direction : directions)
									{
										for (int l = 0; l < static_cast<int>(word_to_be_placed.size()); ++l)
										{
											const int new_x_coord = c + (l * direction.x);
											const int new_y_coord = r + (l * direction.y);

											if (grid.cell_list[grid.CoordToIndex({ new_x_coord, new_y_coord })] == placeholder_char)
											{
												letter_locations.emplace_back(new_x_coord, new_y_coord);
											}
											else
											{
												letter_locations.clear();
												break;
											}

											if (static_cast<int>(letter_locations.size()) >= required_space)
											{
												possible_locations.push_back(letter_locations);
												letter_locations.clear();
											}
										}
									}
								}
							}
						}

						//Pick a random entry in the list and place word
						if (possible_locations.empty() == false)
						{
							cell_coords = possible_locations[Rng::GetInRange(0, possible_locations.size() - 1)];
							is_placed = true;

							if (cell_coords.size() != word_to_be_placed.size())
							{
								__debugbreak();
							}
						}

						break;
					}
					default:
					{
						break;
					}
				}
			}

			int letter_index = 0;
			for (const auto& cell_coord : cell_coords)
			{
				char& cell = grid.cell_list[grid.CoordToIndex(cell_coord)];
				cell = word_to_be_placed[letter_index++];
			}

			//Now place the word in the indices
			grid.word_infos.emplace(word_to_be_placed, WordInfo{ false, orientation, std::move(cell_coords) });
		}

		return true;
	}
}