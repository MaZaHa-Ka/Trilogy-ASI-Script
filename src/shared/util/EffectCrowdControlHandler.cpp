#include "EffectCrowdControlHandler.h"

#include "util/Config.h"
#include "util/EffectBase.h"
#include "util/EffectHandler.h"
#include "util/GameUtil.h"
#include "util/GenericUtil.h"
#include "util/Websocket.h"

bool
EffectCrowdControlHandler::IsCrowdControlEnabled ()
{
    return CONFIG_CC_ENABLED;
}

void
EffectCrowdControlHandler::Initialise (const nlohmann::json &data)
{
    crowdControlId = data.value ("crowdControlID", -1);
}

bool
EffectCrowdControlHandler::HandleOnQueue () const
{
    if (!*this) return true;

    if (GenericUtil::IsMenuActive () || !GameUtil::IsPlayerSafe ())
    {
        SendRetry ();
        return false;
    }

    return true;
}

bool
EffectCrowdControlHandler::HandleOnAddEffect (EffectBase *effect) const
{
    if (*this && !effect->CanActivate ())
    {
        SendRetry ();
        return false;
    }

    return true;
}

bool
EffectCrowdControlHandler::HandleOnEffectIncompatibility () const
{
    if (*this)
    {
        SendRetry ();
        return false;
    }

    return true;
}

bool
EffectCrowdControlHandler::HandleOnEffectActivated (bool isOneTimeEffect) const
{
    if (CONFIG ("CrowdControl.PreventNewEffectsWhenFull", true))
    {
        if (isOneTimeEffect
            && EffectHandler::GetActiveEffectCount () >= RECENT_EFFECTS)
        {
            SendRetry ();
            return false;
        }
    }

    if (*this) SendSucceeded ();

    return true;
}

// 0 Success - 1 Failed - 2 Not Available - 3 Temp. Fail / Retry

void
EffectCrowdControlHandler::SendRetry () const
{
    Websocket::SendCrowdControlResponse (crowdControlId, 3);
}

void
EffectCrowdControlHandler::SendSucceeded () const
{
    Websocket::SendCrowdControlResponse (crowdControlId, 0);
}
