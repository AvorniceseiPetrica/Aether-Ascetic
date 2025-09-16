#pragma once

class AA_State
{
    public:

        virtual ~AA_State() = default;
        virtual void Init() = 0;
        virtual void Update() = 0;
        virtual void Render() = 0;
};