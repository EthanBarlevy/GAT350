#include "cameraComponent.h"
#include "Framework/actor.h"

void vl::CameraComponent::Initialize()
{
    SetViewport(viewport_size);
}

void vl::CameraComponent::Update()
{
    Matrix3x3 mxTranslation = Matrix3x3::CreateTranslation({ -m_owner->GetTransform().position.x, -m_owner->GetTransform().position.y + 100 });
    Matrix3x3 mxRotation = Matrix3x3::CreateRotation(-m_owner->GetTransform().rotation);

    m_view = mxTranslation * mxRotation;

    g_renderer.SetViewMatrix(m_view);
}

void vl::CameraComponent::SetViewport(const Vector2& size)
{
    Matrix3x3 mxTranslation = Matrix3x3::CreateTranslation(size * 0.5f);

    m_viewport = mxTranslation;
    g_renderer.SetViewportMatrix(m_viewport);
}

bool vl::CameraComponent::Write(const rapidjson::Value& value) const
{
    return false;
}

bool vl::CameraComponent::Read(const rapidjson::Value& value)
{
    READ_DATA(value, viewport_size);
    return true;
}
