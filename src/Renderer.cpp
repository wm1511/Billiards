#include "stdafx.h"
#include "Renderer.hpp"

void Renderer::Render(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexIndexBuffer>& model)
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	shader->Bind();
	model->Bind();

	model->Draw();

	shader->Unbind();
	model->Unbind();
}

void Renderer::Update(const std::shared_ptr<Shader>& shader, const std::shared_ptr<Camera>& camera)
{
	shader->Bind();

	shader->SetVec3(camera->GetPosition(), "pointLight.position");
	shader->SetFloat(1.0f, "pointLight.intensity");
	shader->SetVec3(glm::vec3(1.0f), "pointLight.color");
	shader->SetFloat(1.0f, "pointLight.constant");
	shader->SetFloat(0.045f, "pointLight.linear");
	shader->SetFloat(0.0075f, "pointLight.quadratic");

	shader->SetMat4(camera->GetView(), "ViewMatrix");
    shader->SetMat4(camera->GetProjection(), "ProjectionMatrix");
    shader->SetVec3(glm::vec3(0.0f, 0.0f, 0.0f), "cameraPos");

    shader->SetMat4(glm::mat4(1.0f), "ModelMatrix"); 

	shader->SetVec3(glm::vec3(0.1f), "material.ambient");
	shader->SetVec3(glm::vec3(1.0f), "material.diffuse");
	shader->SetVec3(glm::vec3(1.0f), "material.specular");

	shader->Unbind();
}

