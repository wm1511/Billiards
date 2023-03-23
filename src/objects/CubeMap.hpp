#pragma once
#include "Object.hpp"

class CubeMap final : public Object
{
public:
	CubeMap();

	void Draw(const std::shared_ptr<Shader>& shader, unsigned type = GL_TEXTURE_CUBE_MAP) const override;
	void BindBuffer() const;
	void UnbindBuffer() const;

private:
	unsigned frame_buffer_;
};
