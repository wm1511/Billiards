#include "stdafx.h"
#include "Object.hpp"
#include "../core/Loader.hpp"

Object::Object(const std::string& path)
{
	Loader::LoadModel(path, meshes_, materials_);
}

void Object::Draw(const std::shared_ptr<Shader>& shader) const
{
	shader->Bind();

	shader->SetMat4(GetModelMatrix(), "modelMatrix");

	for (const auto& mesh : meshes_)
	{
		const auto material = materials_[mesh->GetMaterialId()];

		material->Bind(shader);
		mesh->Bind();
		mesh->Draw();
		mesh->Unbind();
		material->Unbind(shader);
	}
	
	shader->Unbind();
}

void Object::Translate(const glm::vec3& translation)
{
	translation_ += translation;
}

void Object::Scale(const glm::vec3& scale)
{
	scale_ *= scale;
}

void Object::Rotate(const glm::vec3& rotation)
{
	rotation_ += rotation;
}

glm::mat4 Object::GetModelMatrix() const
{
	auto model_matrix = glm::mat4(1.0f);

	if (glm::length(translation_) > Config::min_change)
		model_matrix *= glm::translate(model_matrix, translation_);

	if (glm::length(scale_) > Config::min_change)
		model_matrix *= glm::scale(model_matrix, scale_);

	if (glm::length(rotation_) > Config::min_change)
		model_matrix *= glm::toMat4(glm::quat(rotation_));

	return model_matrix;
}


