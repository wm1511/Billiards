#include "stdafx.h"
#include "Object.hpp"

void Object::Bind() const
{
	glActiveTexture(GL_TEXTURE1);
	materials_[0]->diffuse_texture->Bind();

	glActiveTexture(GL_TEXTURE2);
	materials_[0]->specular_texture->Bind();

	glActiveTexture(GL_TEXTURE3);
	materials_[0]->normal_texture->Bind();

	mesh_->Bind();
}

void Object::Unbind() const
{
	mesh_->Unbind();
}

void Object::Draw() const
{
	mesh_->Draw();
}

std::shared_ptr<Material> Object::GetMaterial()
{
	return materials_[0];
}
