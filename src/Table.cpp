#include "stdafx.h"
#include "Table.hpp"

Table::Table()
{
	mesh_ = std::make_unique<Mesh>(Config::table_path);
	auto texture = std::make_unique<Texture>("wood_table_d.png");
	auto texture_s = std::make_unique<Texture>("wood_table_r.png");
	auto texture_n = std::make_unique<Texture>("wood_table_n.png");
	materials_.emplace_back(std::make_shared<Material>(glm::vec3{0.0f}, glm::vec3{1.0f}, glm::vec3{1.0f}, std::move(texture), std::move(texture_s), std::move(texture_n)));
}
