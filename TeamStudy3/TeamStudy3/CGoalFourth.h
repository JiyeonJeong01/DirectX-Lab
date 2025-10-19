#pragma once
#include "CObjectFourth.h"
class CGoalFourth : public CObjectFourth {
private:
    bool isGoal;
public:
    CGoalFourth();
    virtual ~CGoalFourth();

    void Initialize() override;
    int Update() override;
    void Render(HDC hDC) override;
    void Release() override;

    const bool GetGoal() const { return isGoal; }
    void SetGoal(const bool& isGoal) { this->isGoal = isGoal; }
};
