#include "util/EffectBase.h"
#include "util/Teleportation.h"

#include <CTaskSimpleCarSetPedOut.h>

class FreefallEffect : public EffectBase
{
public:
    bool
    CanActivate () override
    {
        return Teleportation::CanTeleport ();
    }

    void
    OnTick (EffectInstance *inst) override
    {
        CPlayerPed *player = FindPlayerPed ();
        if (!player || !CanActivate ()) return;

        CVehicle *playerVehicle = FindPlayerVehicle (-1, false);
        if (playerVehicle)
        {
            player->m_pIntelligence->m_TaskMgr.SetTask (
                new CTaskSimpleCarSetPedOut (playerVehicle, 0, false), 0,
                false);

            return;
        }

        CCheat::ParachuteCheat ();

        CVector position = player->GetPosition ();
        position.z       = 1250.0f;

        Teleportation::Teleport (position);

        inst->Disable ();
    }
};

DEFINE_EFFECT (FreefallEffect, "effect_freefall", 0);
