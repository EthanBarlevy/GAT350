#include "TilemapComponent.h"
#include "Components/includes.h"
#include "Framework/actor.h"
#include "Framework/factory.h"
#include "Framework/scene.h"

namespace vl
{
    void TilemapComponent::Initialize()
    {
        for (int i = 0; i < tiles.size(); i++)
        {
            int index = tiles[i];
            if (index == 0) continue;

            auto actor = Factory::Instance().Create<Actor>(tile_names[index]);
            if (actor)
            {
                int x = i % num_columns;
                int y = i / num_columns;

                //actor->GetTransform().position = m_owner->GetTransform().position + (Vector2{x, y} *size);
                m_owner->GetScene()->Add(std::move(actor));
            }
        }

    }

    void TilemapComponent::Update()
    {
        //
    }

    bool TilemapComponent::Write(const rapidjson::Value& value) const
    {
        return true;
    }

    bool TilemapComponent::Read(const rapidjson::Value& value)
    {
        READ_DATA(value, num_columns);
        READ_DATA(value, num_rows);
        READ_DATA(value, size);
        READ_DATA(value, tile_names);
        READ_DATA(value, tiles);

        return true;
    }

}
