#pragma once
#include <string>


class Texture {
public:
	Texture(const std::string& path);
	~Texture();

	void bind();
	void unbind();

private:
	unsigned int textureID;
};