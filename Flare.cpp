#include "Flare.h"
void Flare::mainProcess()
{
    timer += 0.016f;
    smokes[smokeNum].SetPosition(position);
    position = VAdd(position, forward);
    DrawBillboard3D(position, 0.5f, 0.5f, 10, 0, missileBurnerHandle, true);
    if (timer > 4)
    {
        isActivated = false;
        timer = 0;
    }
    smokeNum++;
    if (smokeNum >= 180)
    {
        smokeNum = 0;
    }
}
void Flare::Passive()
{
    for (int i = 0; i < 180; i++)
    {
        smokes[i].DrawSmoke();
    }
}