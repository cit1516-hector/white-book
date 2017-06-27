/*//
//  txbrpg_item.h
//  TXBRPG
//
//  Created by Hector Denis on 01/06/17.
//  Copyright © 2017 Hector Denis. All rights reserved.
//*/

#ifndef txbrpg_item_h
#define txbrpg_item_h

#include <stdarg.h>
#include "hpl_struct_string.h"
#include "hpl_alloc.h"


enum Beatitude {
    beatitude_unknown = 0,
    beatitude_uncursed,
    beatitude_blessed,
    beatitude_cursed,
    beatitude_last
}; 
typedef enum Beatitude Beatitude;

enum Material {
    material_unknown = 0,
    material_iron,
    material_gold,
    material_silver,
    material_glass,
    material_bone,
    material_wood,
    material_bronze,
    material_cloth,
    material_dragon,
    material_leather,
    material_mithril,
    material_plastic,
    material_last
};
typedef enum Material Material;

enum ItemType {
    itemtype_unknown = 0,
    itemtype_amulet,
    itemtype_weapon,
    itemtype_armor,
    itemtype_potion,
    itemtype_scroll,
    itemtype_wand,
    itemtype_ring,
    itemtype_spellbook,
    itemtype_gem,
    itemtype_tool,
    itemtype_coin,
    itemtype_comestible,
    itemtype_last
};
typedef enum ItemType ItemType;

enum ArmorType {
    armortype_unknown = 0,
    armortype_bodyarmor,
    armortype_cloak,
    armortype_helm,
    armortype_shirt,
    armortype_shield,
    armortype_boots,
    armortype_gloves,
    armortype_last
};
typedef enum ArmorType ArmorType;

enum ScrollEffect {
    scrolleffect_unknown = 0,
    scrolleffect_fire,
    scrolleffect_last
};
typedef enum ScrollEffect ScrollEffect;

typedef struct Weapon Weapon;
struct Weapon {
    long dmg;
    long tohit;
    int equiped;
    Material material;
};

typedef struct Armor Armor;
struct Armor {
    long ac;
    long mc;
    int equiped;
    Material material;
    ArmorType type;
};

typedef struct Scroll Scroll;
struct Scroll {
    ScrollEffect effect;
};

typedef struct Item Item;
struct Item {
    String* name;
    String* appearance;
    /*same as name for now.*/
    
    long weight;
    long cost;
    Beatitude beatitude;
    
    ItemType type;
    union {
        Weapon weapon;
        Armor armor;
        Scroll scroll;
    } item;
};
/* When adding an extra item struct, change : 
 - rpg_ItemAlloc 
 - create a ***Create
 - create a ***Print
 - rpg_ItemPrint Strict.
 */



/*-------- STARTER ---------*/
void rpg_ItemUnitTestTemp(void);

/*
 Version: 1.0.0
 Changes: None.
 Goal: Allocate item.
 Params:
 Modif:
 Return:
 Comment:
 */
/*-------- ALLOCATION ---------*/
Item* rpg_ItemAlloc(const char* name, const char* appearance, long weight, long cost, Beatitude beatitude, ItemType type, ...);
int rpg_ItemFree(Item* it);

/*-------- MISC ---------*/
int rpg_ItemCmp(Item a, Item b);

/*-------- CREATION ---------*/
Weapon rpg_WeaponCreate(long dmg, long tohit, int equiped, Material material);
Armor rpg_ArmorCreate(long ac, long mc, int equiped, Material material, ArmorType type);
Scroll rpg_ScrollCreate(ScrollEffect effect);

/*-------- PRINTER ---------*/
int rpg_ItemPrint(Item* i, FILE* stream);
int rpg_ItemWeaponPrint(Weapon* w, FILE* stream);
int rpg_ItemArmorPrint(Armor* a, FILE* stream);
int rpg_ItemScrollPrint(Scroll* s, FILE* stream);

/*-------- ENUMERATIONS ---------*/
int rpg_BeatitudeValid(Beatitude beatitude);
const char* rpg_BeatitudeToString(Beatitude beatitude);
int rpg_MaterialValid(Material material);
const char* rpg_MaterialToString(Material material);
int rpg_ItemTypeValid(ItemType itemtype);
const char* rpg_ItemTypeToString(ItemType itemtype);
int rpg_ArmorTypeValid(ArmorType type);
const char* rpg_ArmorTypeToString(ArmorType type);
int rpg_ScrollEffectValid(ScrollEffect effect);
const char* rpg_ScrollEffectToString(ScrollEffect effect);

#endif /* txbrpg_item_h */
