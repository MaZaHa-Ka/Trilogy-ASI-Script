#pragma once

#include "util/EffectBase.h"

#include <list>
#include <queue>
#include <string_view>

class EffectHandler
{
    inline static std::queue<std::function<void ()>> effectQueue;
    inline static std::deque<EffectInstance>         effects;

public:
    static void Tick ();
    static void ProcessScripts ();

    static void EmptyQueue ();

    static void RemoveStaleEffects ();

    template <typename _Callable, typename... _Args>
    static void QueueFunction (_Callable &&__f, _Args &&...__args);

    static void QueueEffect (EffectBase           *effect,
                             const nlohmann::json &effectData);

    static void HandleFunction (const nlohmann::json &effectData);

    static std::deque<EffectInstance> &
    GetActiveEffects ()
    {
        return effects;
    };

    static void
    Clear ()
    {
        std::deque<EffectInstance> ().swap (effects);
    };
};
