#include "stdafx.h"
#include "Table.hpp"

Table::Table() : Object(Config::table_path)
{
	//auto grass_d = std::make_unique<Texture>("fabric-d.png");
	//auto grass_n = std::make_unique<Texture>("fabric-n.png");
	//materials_[2] = std::make_shared<Material>(glm::vec3{0.2f}, glm::vec3{0.5f}, glm::vec3{1.0f}, std::move(grass_d), nullptr, std::move(grass_n));

	//auto texture_d = std::make_unique<Texture>("wood_table_d.png");
	//auto texture_s = std::make_unique<Texture>("wood_table_r.png");
	//auto texture_n = std::make_unique<Texture>("wood_table_n.png");
	//materials_[3] = std::make_shared<Material>(glm::vec3{0.2f}, glm::vec3{0.5f}, glm::vec3{1.0f}, std::move(texture_d), std::move(texture_s), std::move(texture_n));
}
