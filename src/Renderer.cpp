#include "stdafx.h"
#include "Renderer.hpp"

void Renderer::Render(const std::shared_ptr<Shader>& shader, const std::shared_ptr<Object>& object)
{
	glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	object->Bind();
	shader->Bind();

	object->Draw();

	shader->Unbind();
	object->Unbind();
}

void Renderer::Update(const std::shared_ptr<Shader>& shader, const std::shared_ptr<Camera>& camera)
{
	shader->Bind();

	shader->SetVec3(camera->GetPosition(), "pointLight.position");
	shader->SetFloat(1.0f, "pointLight.intensity");
	shader->SetVec3(glm::vec3(1.0f), "pointLight.color");
	shader->SetFloat(2.0f, "pointLight.constant");
	shader->SetFloat(0.045f, "pointLight.linear");
	shader->SetFloat(0.0075f, "pointLight.quadratic");

	shader->SetMat4(camera->GetView(), "ViewMatrix");
    shader->SetMat4(camera->GetProjection(), "ProjectionMatrix");
    shader->SetVec3(camera->GetPosition(), "cameraPos");

	shader->Unbind();
}

void Renderer::Update(const std::shared_ptr<Shader>& shader, const std::shared_ptr<Object>& object)
{
	shader->Bind();

	shader->SetMat4(glm::mat4(1.0f), "ModelMatrix");

	const std::shared_ptr<Material> material = object->GetMaterial();

	shader->SetVec3(material->ambient, "material.ambient");
	shader->SetVec3(material->diffuse, "material.diffuse");
	shader->SetVec3(material->specular, "material.specular");

	if (material->diffuse_texture)
		[[likely]] shader->SetInt(material->diffuse_texture->GetId(), "material.diffuseTex");

	if (material->specular_texture)
		[[likely]] shader->SetInt(material->specular_texture->GetId(), "material.specularTex");

	if (material->normal_texture)
		[[likely]] shader->SetInt(material->normal_texture->GetId(), "material.normalTex");

	shader->Unbind();
}
