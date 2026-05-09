#include "spritesheets.hpp"

void initSumi(std::unordered_map<SpriteSheetID, SpriteSheetLoadData> &v)
{
    const std::string base = "assets/spritesheets/entities/sumi/";

    v[SpriteSheetID::Entity_SumiStaticHead]       = {base + "static/sumi_head.png", {7, 7}};
    v[SpriteSheetID::Entity_SumiStaticHeadUp45]   = {base + "static/sumi_head_up45.png", {7, 8}};
    v[SpriteSheetID::Entity_SumiStaticHeadDown45] = {base + "static/sumi_head_down45.png", {7, 9}};
    v[SpriteSheetID::Entity_SumiStaticLegs]       = {base + "static/sumi_legs.png", {3, 8}};
    v[SpriteSheetID::Entity_SumiIdleTorso]        = {base + "idle/sumi_idle_torso.png", {4, 8}};
    v[SpriteSheetID::Entity_SumiRunHeadFull]      = {base + "run/sumi_run_head_full.png", {8, 8}};
    v[SpriteSheetID::Entity_SumiRunHead]          = {base + "run/sumi_run_head.png", {8, 8}};
    v[SpriteSheetID::Entity_SumiRunHeadUp45]      = {base + "run/sumi_run_head_up45.png", {8, 9}};
    v[SpriteSheetID::Entity_SumiRunHeadDown45]    = {base + "run/sumi_run_head_down45.png", {8, 9}};
    v[SpriteSheetID::Entity_SumiRunTorso]         = {base + "run/sumi_run_torso.png", {11, 8}};
    v[SpriteSheetID::Entity_SumiRunLegs]          = {base + "run/sumi_run_legs.png", {15, 9}};
}
