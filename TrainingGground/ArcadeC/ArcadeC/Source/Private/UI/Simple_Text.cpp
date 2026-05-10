#include "../../Public/UI/Simple_Text.h"

#include <algorithm>

Simple_Text::Simple_Text()
{
    Text = "";
    Parent = nullptr;
    Visibility = E_Visibility_Visible;
}

void Simple_Text::Draw()
{
}

void Simple_Text::Update()
{
}

void Simple_Text::AddChild(IUItem* Child)
{
    if (std::ranges::contains(Children, Child))
    {
        return;
    }
    
    Children.push_back(Child);
}

void Simple_Text::RemoveChild(IUItem* Child)
{
    //c++20 feture
    std::erase(Children, Child);
}

std::vector<IUItem*> Simple_Text::GetChildren() const
{
    return Children;
}

void Simple_Text::SetParent(IUItem* NewParent)
{
    Parent = NewParent;
}

IUItem* Simple_Text::GetParent() const
{
    return Parent;
}

void Simple_Text::Destroy()
{
}

void Simple_Text::SetPosition(float x, float y)
{
}

void Simple_Text::SetVisibility(const E_Visibility NewVisibility, const bool bPropagate)
{
    Visibility = NewVisibility;
    
    if (!bPropagate)
    {
        return;
    }

    for (IUItem* ChildItem : Children)
    {
        if (ChildItem)
        {
            ChildItem->SetVisibility(NewVisibility, bPropagate);
        }
    }
}

E_Visibility Simple_Text::GetVisibility() const
{
    return E_Visibility_Visible;
}

void Simple_Text::SetText(const std::string& NewText)
{
    Text = NewText;
}
