#pragma once

class Texture
{
public:
	explicit Texture(const std::string& path);
	~Texture() = default;

	Texture(const Texture&) = delete;
	Texture(Texture&&) = delete;
	Texture& operator= (const Texture&) = delete;
	Texture& operator= (Texture&&) = delete;

	void Bind() const;
	void Unbind() const;
	[[nodiscard]] int GetId() const { return static_cast<int>(texture_); }

private:
	int width_{}, height_{};

	unsigned texture_;
};
