#include "../../Public/UI/Simple_Text.h"

Simple_Text::Simple_Text()
{
}

Simple_Text::~Simple_Text()
{
}

void Simple_Text::Draw()
{
}

void Simple_Text::Update()
{
}

void Simple_Text::AddChild(IUItem* Child)
{
}

void Simple_Text::RemoveChild(IUItem* Child)
{
}

std::vector<IUItem*> Simple_Text::GetChildren() const
{
    return {};
}

void Simple_Text::SetParent(IUItem* Parent)
{
}

void Simple_Text::Destroy()
{
}

void Simple_Text::SetPosition(float x, float y)
{
}

void Simple_Text::SetVisibility(const E_Visibility Visibility, const bool bPropagate)
{
}

E_Visibility Simple_Text::GetVisibility() const
{
    return E_Visibility_Visible;
}
