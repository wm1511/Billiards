#include "stdafx.h"
#include "Material.hpp"

void Material::Bind(const std::shared_ptr<Shader>& shader, const unsigned type) const
{
	shader->SetVec3(diffuse, "material.diffuse");
	shader->SetVec3(ambient, "material.ao");
	shader->SetFloat(metallic, "material.metallic");
	shader->SetFloat(roughness, "material.roughness");

	if (diffuse_texture)
	{
		const auto id = diffuse_texture->GetId();
		glActiveTexture(GL_TEXTURE0 + id);
		shader->SetInt(id, "material.diffuseMap");
		shader->SetBool(true, "material.hasDiffuseMap");
		diffuse_texture->Bind(type);
	}

	if (roughness_texture)
	{
		const auto id = roughness_texture->GetId();
		glActiveTexture(GL_TEXTURE0 + id);
		shader->SetInt(id, "material.roughnessMap");
		shader->SetBool(true, "material.hasRoughnessMap");
		roughness_texture->Bind(type);
	}

	if (normal_texture)
	{
		const auto id = normal_texture->GetId();
		glActiveTexture(GL_TEXTURE0 + id);
		shader->SetInt(id, "material.normalMap");
		shader->SetBool(true, "material.hasNormalMap");
		normal_texture->Bind(type);
	}

	if (ao_texture)
	{
		const auto id = ao_texture->GetId();
		glActiveTexture(GL_TEXTURE0 + id);
		shader->SetInt(id, "material.aoMap");
		shader->SetBool(true, "material.hasAoMap");
		roughness_texture->Bind(type);
	}

	if (normal_texture)
	{
		const auto id = normal_texture->GetId();
		glActiveTexture(GL_TEXTURE0 + id);
		shader->SetInt(id, "material.metallicMap");
		shader->SetBool(true, "material.hasMetallicMap");
		normal_texture->Bind(type);
	}
}

void Material::Unbind(const std::shared_ptr<Shader>& shader) const
{
	if (diffuse_texture)
	{
		shader->SetInt(0, "material.diffuseMap");
		shader->SetBool(false, "material.hasDiffuseMap");
	}

	if (roughness_texture)
	{
		shader->SetInt(0, "material.roughnessMap");
		shader->SetBool(false, "material.hasRoughnessMap");
	}

	if (normal_texture)
	{
		shader->SetInt(0, "material.normalMap");
		shader->SetBool(false, "material.hasNormalMap");
	}

	if (ao_texture)
	{
		shader->SetInt(0, "material.aoMap");
		shader->SetBool(false, "material.hasAoMap");
	}

	if (metallic_texture)
	{
		shader->SetInt(0, "material.metallicMap");
		shader->SetBool(false, "material.hasMetallicMap");
	}

	glActiveTexture(GL_TEXTURE0);
}
