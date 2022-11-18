#pragma once
#include "mathUtils.h"
#include "Serialization/serializable.h"

namespace vl 
{
	struct Transform : public ISerializable
	{
		glm::vec3 position{ 0 };
		glm::quat rotation;
		glm::vec3 scale{ 1 };

		glm::mat4 matrix;

		Transform() = default;
		Transform(const glm::vec3& pos, const glm::quat& rot = glm::vec3{ 0, 0, 0 }, const glm::vec3& scl = { 1, 1, 1 })
		{
			position = pos;
			rotation = rot;
			scale = scl;
		}

		virtual bool Write(const rapidjson::Value& value) const override;
		virtual bool Read(const rapidjson::Value& value) override;

		glm::vec3 getRight() { return rotation * glm::vec3{ 1, 0, 0 }; }
		glm::vec3 getUp() { return rotation * glm::vec3{ 0, 1, 0 }; }
		glm::vec3 getForwards() { return rotation * glm::vec3{ 0, 0, 1 }; }

		void Update()
		{
			matrix = *this;
		}

		void Update(const glm::mat4& parent)
		{
			matrix = parent * (glm::mat4)*this;
		}

		operator glm::mat4 () const
		{
			glm::mat4 mxS = glm::scale(scale);
			glm::mat4 mxR = glm::mat4_cast(rotation);
			glm::mat4 mxT = glm::translate(position);

			return { mxT * mxR * mxS };
		}
	};
}