#include "texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Texture::Texture(const char* filename, GLenum texType, GLenum slot, GLenum format,GLenum pixelType) {

    type = texType;

	stbi_set_flip_vertically_on_load(true);
	unsigned char *image_data = stbi_load(("src/" + std::string{filename}).c_str(), &width, &height, &channels, 0); 

    if (!image_data) {
        printf("ERR: Failed to load texture '%s'.\n", filename);
    }

	glGenTextures(1, &ID); 
    glActiveTexture(slot);
	glBindTexture(type, ID);  

	glTexParameteri(type, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
	glTexParameteri(type, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexParameteri(type, GL_TEXTURE_WRAP_S, GL_REPEAT);	
	glTexParameteri(type, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexImage2D(type, 0, GL_RGBA, width, height, 0, format, pixelType, image_data);
    glGenerateMipmap(type);

	stbi_image_free(image_data);

    glBindTexture(type, 0);
}

void Texture::texUnit(Shader& shader, const char* uniform, GLuint unit) {
    GLuint texUni = glGetUniformLocation(shader.ID, uniform);
    shader.Activate();
    glUniform1i(texUni, unit);
}

void Texture::Bind() {
	glBindTexture(type, ID);
}

void Texture::Unbind() {
    glBindTexture(type, 0);
}
void Texture::Delete() {
    glDeleteTextures(1, &ID);
}
