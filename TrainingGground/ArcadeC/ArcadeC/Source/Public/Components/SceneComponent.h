#pragma once
#include "../Framework/EntityComponentSystem.h"

class SceneComponent : public Component
{
public:

    SceneComponent();
    SceneComponent(const float x, const float y);
    SceneComponent(const int32_t x, const int32_t y);
    ~SceneComponent() override;

    float GetX() const { return X; }
    float GetY() const { return Y; }

    void SetPosition(const float x, const float y);
    void SetPosition(const int32_t x, const int32_t y);

    void ComponentUpdate() override;
private:

    //TODO Changt to vecto2d
    float X ,Y;
    
};
