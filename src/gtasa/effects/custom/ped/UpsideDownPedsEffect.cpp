#include <util/BoneHelper.h>
#include <util/EffectBase.h>
#include <util/GenericUtil.h>

#include "CTimer.h"

#include "ePedBones.h"

using namespace plugin;

static ThiscallEvent<AddressList<0x5B1F31, H_CALL>, PRIORITY_AFTER,
                     ArgPickN<CPed *, 0>, void (CPed *)>
    cutscenePedRenderEvent;

class UpsideDownPedsEffect : public EffectBase
{
public:
    void
    OnStart (EffectInstance *inst) override
    {
        cutscenePedRenderEvent += RenderPed;
    }

    void
    OnEnd (EffectInstance *inst) override
    {
        cutscenePedRenderEvent -= RenderPed;
    }

    void
    OnTick (EffectInstance *inst) override
    {
        for (CPed *ped : CPools::ms_pPedPool)
        {
            RenderPed (ped);
        }
    }

    static void
    RenderPed (CPed *ped)
    {
        RwV3d angles = BoneHelper::GetBoneRotation (ped, 0);
        angles.x     = fmod (angles.x + 180.0f, 360.0f);
        BoneHelper::SetBoneRotation (ped, 0, angles);

        BoneHelper::UpdatePed (ped);
    }
};

DEFINE_EFFECT (UpsideDownPedsEffect, "effect_upside_down_peds",
               GROUP_PED_BONES);