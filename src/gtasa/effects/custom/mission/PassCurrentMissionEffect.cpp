#include "util/EffectBase.h"
#include "util/EffectHandler.h"
#include "util/GameUtil.h"
#include "util/GenericUtil.h"
#include "util/Teleportation.h"

#include <CGangWars.h>
#include <CTheScripts.h>
#include <extensions/ScriptCommands.h>

using namespace plugin;

class PassCurrentMissionEffect : public EffectBase
{
    static inline bool isEnabled = false;

    std::map<std::string, int> offsetMap = {
        /* Los Santos */
        {"INTRO1", 18131}, // Big Smoke
        {"INTRO2", 13692}, // Ryder
        {"SWEET1", 14682}, // Tagging Up Turf
        {"SWEET1B", 8674}, // Cleaning The Hood
        {"SWEET3", 12908}, // Drive-Thru
        {"SWEET2", 20304}, // Nines And AK's
        {"SWEET4", 23785}, // Drive-By
        {"HOODS5", 15274}, // Sweet's Girl
        {"SWEET6", 147},   // Cesar Vialpando
        {"SWEET7", 32422}, // Los Sepulcros
        {"CRASH1", 1199},  // Burning Desire
        {"CRASH4", 6337},  // Doberman
        {"DRUGS3", 19361}, // Gray Imports
        {"GUNS1", 40660},  // Home Invasion
        {"RYDER2", 238},   // Robbing Uncle Sam
        {"RYDER3", 2254},  // Catalyst
        {"TWAR7", 23183},  // OG Loc
        {"SMOKE2", 11352}, // Running Dog
        {"SMOKE3", 20115}, // Wrong Side Of The Tracks
        {"DRUGS1", 52043}, // Just Business
        {"MUSIC1", 15574}, // Life's a Beach
        {"MUSIC2", 10527}, // Madd Dogg's Rhymes
        {"MUSIC3", 15510}, // Management Issues
        {"MUSIC5", 15889}, // House Party
        {"DRUGS4", 67765}, // Reuniting The Families
        {"LA1FIN2", 390},  // The Green Sabre
        /* ######################### */
        /* Badlands */
        {"BCRASH1", 13609}, // Badlands
        {"CAT1", 292},      // Local Liquor Store
        {"CAT2", 30025},    // Small Town Bank
        {"CAT3", 4141},     // Tanker Commander
        {"CAT4", 6648},     // Against All Odds
        {"TRUTH1", 16397},  // Body Harvest
        {"TRUTH2", 11942},  // Are You Going To San Fierro?
        /* ######################### */
        /* San Fierro */
        {"GARAG1", 4928},  // Wear Flowers In Your Hair
        {"DECON", 133},    // Deconstruction
        {"SCRASH3", 679},  // 555 WE TIP
        {"SCRASH2", 661},  // Snail Trail
        {"WUZI1", 27975},  // Mountain Cloud Boys
        {"FARLIE4", 608},  // Ran Fa Li
        {"DRIV6", 12781},  // Lure
        {"WUZI2", 26588},  // Amphibious Assault
        {"WUZI5", 20684},  // The Da Nang Thang
        {"SYN1", 14568},   // Photo Opportunity
        {"SYN2", 84},      // Jizzy
        {"SYN3", 19158},   // Outrider
        {"SYND4", 12241},  // Ice Cold Killa
        {"SYN6", 9169},    // Toreno's Last Flight
        {"SYN7", 14730},   // Yay Ka-Boom Boom
        {"SYN5", 23169},   // Pier 69
        {"DRIV2", 12885},  // T-Bone Mendez
        {"DRIV3", 2674},   // Mike Toreno
        {"STEAL1", 7659},  // Zeroing In
        {"STEAL2", 26031}, // Test Drive
        {"STEAL4", 89},    // Customs Fast Track
        {"STEAL5", 5117},  // Puncture Wounds
        {"ZERO1", 5321},   // Air Raid
        {"ZERO2", 3285},   // Supply Lines...
        {"ZERO4", 2105},   // New Model Army
        /* ######################### */
        /* Las Venturas */
        {"TORENO1", 14457}, // Monster
        {"TORENO2", 10715}, // Highjack
        {"DES3", 147},      // Interdiction
        {"DESERT6", 726},   // N.O.E.
        {"DESERT9", 21869}, // Stowaway
        {"MAF4", 29924},    // Black Project
        {"DES10", 4130},    // Green Goo
        {"CASINO1", 19542}, // Fender Ketchup
        {"CASINO2", 16387}, // Explosive Situation
        {"CASINO3", 14129}, // You've Had Your Chips
        {"CASINO4", 45880}, // Don Peyote
        {"CASINO5", 12838}, // Intensive Care
        {"CASINO6", 1290},  // The Meat Business
        {"CASINO9", 12440}, // Freefall
        {"CASIN10", 15339}, // Saint Mark's Bistro
        {"VCRASH1", 7980},  // Misappropriation
        {"VCR2", 5058},     // High Noon
        {"DOC2", 13233},    // Madd Dogg
        {"HEIST1", 23694},  // Architectural Espionage
        {"HEIST3", 2606},   // Key To Her Heart
        {"HEIST2", 18813},  // Dam And Blast
        {"HEIST4", 13180},  // Cop Wheels
        {"HEIST5", 13735},  // Up, Up and Away!
        {"HEIST9", 44516},  // Breaking the Bank at Caligula's
        /* ######################### */
        /* Return To Los Santos */
        {"MANSIO1", 6889}, // A Home In The Hills
        {"MANSIO2", 1456}, // Vertical Bird
        {"MANSIO3", 6740}, // Home Coming
        {"MANSON5", 1350}, // Cut Throat Business
        {"GROVE1", 18881}, // Beat Down on B Dup
        {"GROVE2", 3159},  // Grove 4 Life
        {"RIOT1", 2997},   // Riot
        {"RIOT2", 30259},  // Los Desperados
        {"FINALEA", 1473}, // End Of The Line (Part 1)
        {"FINALEB", -1},   // End Of The Line (Part 2)
        {"FINALEC", 1817}, // End Of The Line (Part 3)
        /* ######################### */
    };
    std::vector<std::string> debugCodeMap = {
        /* Los Santos */
        "SWEET1B", // Cleaning The Hood
        "SWEET6",  // Cesar Vialpando
        "CRASH1",  // Burning Desire
        "RYDER2",  // Robbing Uncle Sam
        "RYDER3",  // Catalyst
        "LA1FIN2", // The Green Sabre
        /* ######################### */
        /* Badlands */
        "CAT1", // Local Liquor Store
        "CAT2", // Small Town Bank
        "CAT3", // Tanker Commander
        "CAT4", // Against All Odds
        /* ######################### */
        /* San Fierro */
        "GARAG1",  // Wear Flowers In Your Hair
        "DECON",   // Deconstruction
        "SCRASH3", // 555 We Tip
        "SCRASH2", // Snail Trail
        "FARLIE4", // Ran Fa Li
        "SYN2",    // Jizzy
        "DRIV3",   // Mike Toreno
        "STEAL4",  // Customs Fast Track
        "ZERO1",   // Air Raid
        "ZERO2",   // Supply Lines...
        "ZERO4",   // New Model Army
        /* ######################### */
        /* Las Venturas */
        "DES3",    // Interdiction
        "DESERT6", // N.O.E.
        "CASINO6", // The Meat Business
        "HEIST3",  // Key To Her Heart
        /* ######################### */
        /* Return To Los Santos */
        "MANSIO1", // A Home In The Hills
        "MANSIO2", // Vertical Bird
        "MANSON5", // Cut Throat Business
        "FINALEA", // End Of The Line (Part 1)
        "FINALEB", // End Of The Line (Part 2)
        "FINALEC", // End Of The Line (Part 3)
        /* ######################### */
    };
    bool triedPassingMission = false;
    int  missionPassWait     = 100;

public:
    void
    OnStart (EffectInstance *inst) override
    {
        isEnabled           = false;
        triedPassingMission = false;
        missionPassWait     = 100;

        for (int address : {0x46DDED, 0x46DE32})
        {
            injector::MakeCALL (address, Hooked_Debug_GetKeyDown);
        }
    }

    void
    OnEnd (EffectInstance *inst) override
    {
        // TODO: Unhook
    }

    void
    OnTick (EffectInstance *inst) override
    {
        if (triedPassingMission)
        {
            missionPassWait -= (int) GenericUtil::CalculateTick ();
            if (missionPassWait <= 0) inst->Disable ();

            return;
        }

        if (triedPassingMission || CCutsceneMgr::ms_running
            || TheCamera.m_bWideScreenOn)
        {
            return;
        }

        for (auto i = CTheScripts::pActiveScripts; i; i = i->m_pNext)
        {
            if (i->m_bIsMission && i->m_bIsActive && !i->m_bIsExternal)
            {
                std::string missionName
                    = GenericUtil::ToUpper (std::string (i->m_szName));
                if (offsetMap.contains (missionName))
                {
                    if (ContainsDebugCode (missionName)) isEnabled = true;

                    if (offsetMap[missionName] != -1)
                    {
                        i->m_pCurrentIP = i->m_pBaseIP + offsetMap[missionName];
                    }

                    ClearPlayerStatus ();

                    Teleportation::TeleportOutOfMission (missionName);

                    if (missionName == "FINALEC")
                    { // End Of The Line (Part 3)
                        Command<eScriptCommands::COMMAND_SET_LA_RIOTS> (0);
                        Command<eScriptCommands::
                                    COMMAND_SET_CAR_DENSITY_MULTIPLIER> (1.0f);
                        Command<eScriptCommands::
                                    COMMAND_SET_PED_DENSITY_MULTIPLIER> (1.0f);
                    }

                    break;
                }
                else if (missionName == "CPRACE")
                { // High Stakes, Low-Rider / Wu Zi Mu / Farewell, My Love...
                    /*
                    // TODO: Races are handled differently.
                    // We need to increase global variables, which during
                    initial testing didn't work as planned.

                    int raceIndex = 0;
                    Command<eScriptCommands::COMMAND_SET_LVAR_INT_TO_VAR_INT>(&raceIndex,
                    CallMethodAndReturn<short, 0x464700, CRunningScript*>(i,
                    352)); if (raceIndex == 0) { // High Stakes, Low-rider
                            i->m_pCurrentIP = i->m_pBaseIP + 19649;
                    }
                    else if (raceIndex == 7) { // Wu Zi Mu
                            int cesarPassed = 5, wuzimuStarted = 0;
                            Command<eScriptCommands::COMMAND_SET_VAR_INT_TO_LVAR_INT>(CallMethodAndReturn<short,
                    0x464700, CRunningScript*>(i, 492), &cesarPassed);
                            Command<eScriptCommands::COMMAND_SET_VAR_INT_TO_LVAR_INT>(CallMethodAndReturn<short,
                    0x464700, CRunningScript*>(i, 2196), &wuzimuStarted);

                            Command<eScriptCommands::COMMAND_FAIL_CURRENT_MISSION>();
                    }
                    else if (raceIndex == 8) { // Farewell, My Love...
                            int cesarPassed = 10, wuzimuStarted = 0;
                            Command<eScriptCommands::COMMAND_SET_VAR_INT_TO_LVAR_INT>(CallMethodAndReturn<short,
                    0x464700, CRunningScript*>(i, 492), &cesarPassed);
                            Command<eScriptCommands::COMMAND_SET_VAR_INT_TO_LVAR_INT>(CallMethodAndReturn<short,
                    0x464700, CRunningScript*>(i, 2196), &wuzimuStarted);

                            Command<eScriptCommands::COMMAND_FAIL_CURRENT_MISSION>();
                    }
                    return;
                    */
                }
                else if (ContainsDebugCode (missionName))
                {
                    isEnabled = true;
                    break;
                }
            }
        }

        triedPassingMission = true;
    }

    bool
    ContainsDebugCode (std::string missionName)
    {
        return std::find (debugCodeMap.begin (), debugCodeMap.end (),
                          missionName)
               != debugCodeMap.end ();
    }

    void
    ClearPlayerStatus ()
    {
        GameUtil::RemovePlayerBalaclava ();

        CPed *player;
        Command<eScriptCommands::COMMAND_GET_PLAYER_CHAR> (0, &player);
        if (player)
        {
            Command<eScriptCommands::COMMAND_SKIP_CUTSCENE_END> ();
            Command<eScriptCommands::COMMAND_CLEAR_CHAR_TASKS> (player);
            Command<eScriptCommands::COMMAND_SET_CAMERA_BEHIND_PLAYER> ();
            Command<eScriptCommands::COMMAND_SWITCH_WIDESCREEN> (0);
            Command<eScriptCommands::COMMAND_SET_PLAYER_CONTROL> (0, 1);
            Command<eScriptCommands::COMMAND_RESTORE_CAMERA_JUMPCUT> ();
            Command<eScriptCommands::COMMAND_DETACH_CHAR_FROM_CAR> (player);
        }
    }

    static char __stdcall Hooked_Debug_GetKeyDown (int keyCode, int a2, int a3)
    {
        return isEnabled && keyCode == 83; // 83 / S for mission skip
    }
};

DEFINE_EFFECT (PassCurrentMissionEffect, "effect_pass_current_mission", 0);