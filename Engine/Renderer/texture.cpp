#include "texture.h"
#include "renderer.h"
#include "Core/logger.h"
#include <SDL.h>
#include <SDL_image.h>

namespace vl
{
    Texture::~Texture()
    {
        if (m_texture) glDeleteTextures(1, &m_texture);
    }

    bool Texture::Create(std::string name, ...)
    {
        va_list args;
        va_start(args, name);
        Renderer& renderer = va_arg(args, Renderer);
        va_end(args);

        return Create(renderer, name);
    }

    bool Texture::Create(Renderer& renderer, const std::string& filename)
    {
        // load surface
        SDL_Surface* surface = IMG_Load(filename.c_str());
        if (!surface)
        {
            LOG(SDL_GetError());
            return false;
        }

        // create texture
        glGenTextures(1, &m_texture);
        glBindTexture(m_target, m_texture);

        GLenum format = (surface->format->BytesPerPixel == 4) ? GL_RGBA : GL_RGB;
        glTexImage2D(m_target, 0, format, surface->w, surface->h, 0, format, GL_UNSIGNED_BYTE, surface->pixels);

        glTexParameteri(m_target, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(m_target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(m_target, GL_TEXTURE_WRAP_S, GL_CLAMP);
        glTexParameteri(m_target, GL_TEXTURE_WRAP_T, GL_CLAMP);

        SDL_FreeSurface(surface);

        return true;
    }

    bool Texture::CreateFromSurface(SDL_Surface* surface, Renderer& renderer)
    {
        // DEPRECATED 
        /*
        if (m_texture) SDL_DestroyTexture(m_texture);

        m_texture = SDL_CreateTextureFromSurface(renderer.m_renderer, surface);

        SDL_FreeSurface(surface);

        if (!m_texture)
        {
            LOG(SDL_GetError());
            return false;
        }
        */
        return true;

    }

    bool Texture::Load(const std::string& filename, Renderer& renderer)
    {
        // load surface
        SDL_Surface* surface = IMG_Load(filename.c_str());
        if (!surface)
        {
            LOG(SDL_GetError());
            return false;
        }
        FlipSurface(surface);

        // create texture
        glGenTextures(1, &m_texture);
        glBindTexture(m_target, m_texture);
        GLenum format = (surface->format->BytesPerPixel == 4) ? GL_RGBA : GL_RGB;
        glTexImage2D(m_target, 0, format, surface->w, surface->h, 0, format, GL_UNSIGNED_BYTE, surface->pixels);

        glTexParameteri(m_target, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(m_target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(m_target, GL_TEXTURE_WRAP_S, GL_CLAMP);
        glTexParameteri(m_target, GL_TEXTURE_WRAP_T, GL_CLAMP);

        // delete the surface
        SDL_FreeSurface(surface);

        return true;
    }

    Vector2 Texture::GetSize() const
    {
        // DEPRECATED
        /*
        SDL_Point point;
        SDL_QueryTexture(m_texture, nullptr, nullptr, &point.x, &point.y);

        return Vector2(point.x, point.y);
        */
        return { 0, 0 };
    }
    void Texture::FlipSurface(SDL_Surface* surface)
    {
        SDL_LockSurface(surface);

        int pitch = surface->pitch; // row size
        uint8_t* temp = new uint8_t[pitch];
        uint8_t* pixels = (uint8_t*)surface->pixels;

        for (int i = 0; i < surface->h / 2; ++i)
        {
            uint8_t* row1 = pixels + i * pitch;
            uint8_t* row2 = pixels + (surface->h - i - 1) * pitch;

            // swap rows
            memcpy(temp, row1, pitch);
            memcpy(row1, row2, pitch);
            memcpy(row2, temp, pitch);
        }

        delete[] temp;

        SDL_UnlockSurface(surface);
    }
}

