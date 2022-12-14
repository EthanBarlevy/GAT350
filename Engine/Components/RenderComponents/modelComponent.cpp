#include "modelComponent.h"
#include "Framework/actor.h"
#include "Renderer/model.h"
#include "Renderer/program.h"

namespace vl
{
	bool ModelComponent::Write(const rapidjson::Value& value) const
	{
		return false;
	}

	bool ModelComponent::Read(const rapidjson::Value& value)
	{
		std::string model_name;
		std::string material_name;
		READ_DATA(value, model_name);
		READ_DATA(value, material_name);

		model = g_resourceManager.Get<Model>(model_name);
		material = g_resourceManager.Get<Material>(material_name);

		READ_DATA(value, depth_test);

		return true;
	}
	
	void vl::ModelComponent::Update()
	{
		//
	}

	void vl::ModelComponent::Draw(Renderer& renderer)
	{
		material->Bind();
		// set mvp
		material->GetProgram()->SetUniform("model", (glm::mat4)m_owner->GetTransform());

		glDepthMask(depth_test);
		model->m_vertexBuffer.Draw();
	}


}
