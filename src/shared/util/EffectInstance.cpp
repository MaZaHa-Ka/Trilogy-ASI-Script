#include "EffectInstance.h"
#include "EffectBase.h"
#include "GenericUtil.h"

#include <CTheScripts.h>

EffectInstance::EffectInstance (EffectBase *effect) : effect (effect) {}

void
EffectInstance::Start ()
{
    if (this->effect)
        this->effect->OnStart (this);
}

void
EffectInstance::End ()
{
    if (this->effect)
        this->effect->OnEnd (this);
}

void
EffectInstance::Tick ()
{
    int tick = (int) GenericUtil::CalculateTick (1.0f);
    this->remaining -= tick;

    if (GetEffectRemaining () < 0)
        Disable ();

    if (effect && isRunning)
        effect->OnTick (this);
}

std::string_view
EffectInstance::GetName () const
{
    if (effect && overrideName.length () == 0)
        return effect->GetMetadata ().name;

    return overrideName;
}

bool
EffectInstance::IsOtherEffectIncompatible (const EffectInstance &other)
{
    auto &thisMetadata  = this->effect->GetMetadata ();
    auto &otherMetadata = other.effect->GetMetadata ();

    // Check for equal id
    if (thisMetadata.id == otherMetadata.id)
        return true;

    // Check for common groups
    if ((thisMetadata.groups & otherMetadata.groups).any ())
        return true;

    // Check for same description/name (old Chaos code did as well)
    if (this->GetName () == other.GetName ())
        return true;

    return false;
}