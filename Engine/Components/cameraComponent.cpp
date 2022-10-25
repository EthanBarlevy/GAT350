#include "cameraComponent.h"
#include "Framework/actor.h"

void vl::CameraComponent::Initialize()
{
    //SetViewport(viewport_size);
}

void vl::CameraComponent::Update()
{
    m_view = glm::lookAt(m_owner->GetTransform().position, m_owner->GetTransform().position + m_owner->GetTransform().getForwards(), glm::vec3{0, 1, 0});
}

void vl::CameraComponent::SetPerspective(float fov, float aspectRatio, float near, float far)
{
    m_projection = glm::perspective(glm::radians(fov), aspectRatio, near, far);
}

bool vl::CameraComponent::Write(const rapidjson::Value& value) const
{
    return false;
}

bool vl::CameraComponent::Read(const rapidjson::Value& value)
{
    float fov;
    READ_DATA(value, fov);
    float aspect_ratio;
    if (!READ_DATA(value, aspect_ratio))
    {
        aspect_ratio = g_renderer.GetWidth() / (float(g_renderer.GetHeight()));
    }
    float near;
    READ_DATA(value, near);
    float far;
    READ_DATA(value, far);

    SetPerspective(fov, aspect_ratio, near, far);

    return true;
}
