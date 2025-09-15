#pragma once

class AA2_State
{
    public:

        virtual ~AA2_State() = default;
        virtual void Update() = 0;
        virtual void Render() = 0;
};