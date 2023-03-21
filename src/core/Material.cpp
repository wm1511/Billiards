#include "stdafx.h"
#include "Material.hpp"

void Material::Bind(const std::shared_ptr<Shader>& shader) const
{
	shader->SetFloat(metallic, "material.metallic");
	shader->SetFloat(roughness, "material.roughness");
	shader->SetVec3(diffuse, "material.diffuse");

	if (diffuse_texture) [[likely]] 
	{
		const auto id = diffuse_texture->GetId();
		glActiveTexture(GL_TEXTURE0 + id);
		shader->SetInt(id, "material.diffuseMap");
		shader->SetBool(true, "material.hasDiffuseMap");
		diffuse_texture->Bind();
	}

	if (roughness_texture) [[unlikely]]
	{
		const auto id = roughness_texture->GetId();
		glActiveTexture(GL_TEXTURE0 + id);
		shader->SetInt(id, "material.roughnessMap");
		shader->SetBool(true, "material.hasRoughnessMap");
		roughness_texture->Bind();
	}

	if (normal_texture) [[unlikely]]
	{
		const auto id = normal_texture->GetId();
		glActiveTexture(GL_TEXTURE0 + id);
		shader->SetInt(id, "material.normalMap");
		shader->SetBool(true, "material.hasNormalMap");
		normal_texture->Bind();
	}
}

void Material::Unbind(const std::shared_ptr<Shader>& shader) const
{
	if (diffuse_texture) [[likely]] 
	{
		shader->SetInt(0, "material.diffuseMap");
		shader->SetBool(false, "material.hasDiffuseMap");
	}

	if (roughness_texture) [[unlikely]]
	{
		shader->SetInt(0, "material.roughnessMap");
		shader->SetBool(false, "material.hasRoughnessMap");
	}

	if (normal_texture) [[unlikely]]
	{
		shader->SetInt(0, "material.normalMap");
		shader->SetBool(false, "material.hasNormalMap");
	}

	glActiveTexture(GL_TEXTURE0);
}
