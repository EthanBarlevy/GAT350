#include "modelComponent.h"
#include "Framework/actor.h"
#include "Renderer/model.h"

namespace vl
{
	bool ModelComponent::Write(const rapidjson::Value& value) const
	{
		return false;
	}

	bool ModelComponent::Read(const rapidjson::Value& value)
	{
		std::string model_name;
		READ_DATA(value, model_name);

		m_model = g_resourceManager.Get<Model>(model_name);
		return true;
	}
	
	void vl::ModelComponent::Update()
	{
		//
	}

	void vl::ModelComponent::Draw(Renderer& renderer)
	{
		m_model->Draw(renderer, m_owner->GetTransform());
	}


}
