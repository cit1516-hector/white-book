/*//
//  txbrpg_item.c
//  TXBRPG
//
//  Created by Hector Denis on 01/06/17.
//  Copyright © 2017 Hector Denis. All rights reserved.
//*/

#include "txbrpg_item.h"

void rpg_ItemUnitTestTemp(void) {
    Item* i = NULL;
    fprintf(stdout, "\tUnit Start.\n");
    i = rpg_ItemAlloc("Sword", "Lame", 10, 12, beatitude_blessed, itemtype_weapon, rpg_WeaponCreate(6, 3, 0, material_glass));
    rpg_ItemPrint(i, stdout);
    rpg_ItemFree(i);
    
    i = rpg_ItemAlloc("Scroll", "README", 5, 10, beatitude_cursed, itemtype_scroll, rpg_ScrollCreate(scrolleffect_fire));
    rpg_ItemPrint(i, stdout);
    rpg_ItemFree(i);
    fprintf(stdout, "\tUnit End.\n");
}

#define ITEMCMPNUM (7)
int rpg_ItemCmp(Item a, Item b) {
    int acc = 1, i = 0;
    int t[ITEMCMPNUM] = {0};
    t[0] = !strcmp(b.name->str, b.name->str),
    t[1] = !strcmp(a.appearance->str, b.appearance->str),
    t[2] = a.weight == b.weight,
    t[3] = a.cost == b.cost,
    t[4] = a.beatitude == b.beatitude,
    t[5] = a.type == b.type;
    t[6] = a.item.weapon.dmg == b.item.weapon.dmg &&
            a.item.weapon.tohit == b.item.weapon.tohit &&
            a.item.weapon.equiped == b.item.weapon.equiped &&
            a.item.weapon.material == b.item.weapon.material;
    /* t[6] = memcmp(&a.item, &b.item, sizeof(a.item)); */
    /* Shouldnt be memcmp... */
    for (i = 0; i < ITEMCMPNUM; i++) if (0 == t[i]) acc = 0;
    
    return acc;
}

/* --------- ALLOCATION --------- */
int rpg_ItemFree(Item* it) {
    if (NULL == it) {
        return -1;
    } 
    /* Call the necessary free function for the item. */
    hpl_StringFree(it->appearance);
    hpl_StringFree(it->name);
    it->appearance = NULL;
    it->name = NULL;
    free(it);
    it = NULL;
    return 1;
}

Item* rpg_ItemAlloc(const char* name, const char* appearance, long weight, long cost, Beatitude beatitude, ItemType type, ...) {
    /* Order is important. function calls/params*/
    
    va_list ap;
    const size_t str_len = 64; /*name/ apparence length.*/
    Item* it = hpl_Malloc(sizeof(*it));
    if (NULL == it) {
        return NULL;
    }
    memset(it, 0, sizeof(*it));
    
    it->name = hpl_StringAlloc(str_len);
    if (NULL == it->name) {
        rpg_ItemFree(it);
        it = NULL;
        return NULL;
    }
    
    it->appearance = hpl_StringAlloc(str_len);
    if (NULL == it->appearance) {
        rpg_ItemFree(it);
        it = NULL;
        return NULL;
    }
    
    strncpy(it->name->str, name, str_len - 1);
    strncpy(it->appearance->str, appearance, str_len - 1);
    it->name->wri = strlen(it->name->str);
    it->appearance->wri = strlen(it->appearance->str);
    
    it->weight = weight;
    it->cost = cost;
    it->beatitude = beatitude;
    it->type = type;
    
    /* Let the magic happen. */
    va_start(ap, type);
    
    switch (it->type) {
        case itemtype_weapon:
            it->item.weapon = va_arg(ap, Weapon);
            break;
        case itemtype_armor:
            it->item.armor = va_arg(ap, Armor);
            break;
        case itemtype_scroll:
            it->item.scroll = va_arg(ap, Scroll);
            break;
        default:
            fprintf(stderr, "itemalloc, unhandled type\n");
            break;
    }
    va_end(ap);
    return it;
}

/*-------- CREATION ---------*/
Armor rpg_ArmorCreate(long ac, long mc, int equiped, Material material, ArmorType type) {
    Armor new;
    memset(&new, 0, sizeof(new));
    new.ac = ac;
    new.mc = mc;
    new.equiped = equiped;
    new.material = material;
    new.type = type;
    return new;
}
Weapon rpg_WeaponCreate(long dmg, long tohit, int equiped, Material material) {
    Weapon new;
    memset(&new, 0, sizeof(new));
    new.dmg = dmg;
    new.tohit = tohit;
    new.equiped = equiped;
    new.material = material;
    return new;
}

Scroll rpg_ScrollCreate(ScrollEffect effect) {
    Scroll new;
    memset(&new, 0, sizeof(new));
    new.effect = effect;
    return new;
}

/* --------- PRINTER --------- */
int rpg_ItemWeaponPrint(Weapon* w, FILE* stream) {
    if (NULL == w) {
        return -1;
    }
    fprintf(stream, "dmg: %ld\n", w->dmg);
    fprintf(stream, "tohit: %ld\n", w->tohit);
    fprintf(stream, "eqp: %d\n", w->equiped);
    fprintf(stream, "mat: %u/%s\n", w->material, rpg_MaterialToString(w->material));
    return 1;
}

int rpg_ItemArmorPrint(Armor* a, FILE* stream) {
    if (NULL == a) {
        return -1;
    }
    fprintf(stream, "ac: %ld\n", a->ac);
    fprintf(stream, "mc: %ld\n", a->mc);
    fprintf(stream, "eqp: %d\n", a->equiped);
    fprintf(stream, "mat: %u/%s\n", a->material, rpg_MaterialToString(a->material));
    fprintf(stream, "type: %u/%s\n", a->type, rpg_ArmorTypeToString(a->type));
    return 1;
}

int rpg_ItemScrollPrint(Scroll* s, FILE* stream) {
    if (NULL == s) {
        return -1;
    }
    fprintf(stream, "effect: %u/%s\n", s->effect, rpg_ScrollEffectToString(s->effect));
    
    return 1;
}

int rpg_ItemPrint(Item* i, FILE* stream) {
    if (NULL == i) {
        return -1;
    }
    fprintf(stream, "name: %s\n", i->name->str);
    fprintf(stream, "app: %s\n", i->appearance->str);
    fprintf(stream, "weight: %ld\n", i->weight);
    fprintf(stream, "cost: %ld\n", i->cost);
    fprintf(stream, "BUC: %u/%s\n", i->beatitude, rpg_BeatitudeToString(i->beatitude));
    fprintf(stream, "type: %u/%s\n", i->type, rpg_ItemTypeToString(i->type));
    switch (i->type) {
        case itemtype_weapon:
            rpg_ItemWeaponPrint(&i->item.weapon, stream);
            break;
        case itemtype_armor:
            rpg_ItemArmorPrint(&i->item.armor, stream);
            break;
        case itemtype_scroll:
            rpg_ItemScrollPrint(&i->item.scroll, stream);
            break;
        default:
            fprintf(stderr, "Item print unhadleld.\n");
            return 0;
            break;
    }
    return 1;
}

/* --- --- --- ENUMERATIONS --- --- --- */
int rpg_BeatitudeValid(Beatitude beatitude) {
    if (beatitude_unknown < beatitude && beatitude < beatitude_last) return 1;
    return 0;
}
const char* rpg_BeatitudeToString(Beatitude beatitude) {
    if (1 != rpg_BeatitudeValid(beatitude)) {
        return "Unknown";
    }
    /*the above check is useless, as we ret "" at the end. */
    switch (beatitude) {
        case beatitude_uncursed:
            return "Uncursed";
            break;
        case beatitude_blessed:
            return "Blessed";
            break;
        case beatitude_cursed:
            return "Cursed";
            break;
        default:
            return "Unhandled";
            break;
    }
    return "Unknown";
}

int rpg_MaterialValid(Material material) {
    if (material_unknown < material && material < material_last) return 1;
    return 0;
}
const char* rpg_MaterialToString(Material material) {
    if (1 != rpg_MaterialValid(material)) {
        return "Unknown";
    }
    /*the above check is useless, as we ret "" at the end. */
    switch (material) {
        case material_iron:
            return "Iron";
            break;
        case material_gold:
            return "Gold";
            break;
        case material_silver:
            return "Silver";
            break;
        case material_glass:
            return "Glass";
            break;
        case material_bone:
            return "Bone";
            break;
        case material_wood:
            return "Wood";
            break;
        case material_bronze:
            return "Bronze";
            break;
        case material_cloth:
            return "Cloth";
            break;
        case material_dragon:
            return "Dragon";
            break;
        case material_leather:
            return "Leather";
            break;
        case material_mithril:
            return "Mithril";
            break;
            
        default:
            return "Unhandled";
            break;
    }
    return "Unknown";
}

int rpg_ItemTypeValid(ItemType itemtype) {
    if (itemtype_unknown < itemtype && itemtype < itemtype_last) return 1;
    return 0;
}
const char* rpg_ItemTypeToString(ItemType itemtype) {
    if (1 != rpg_ItemTypeValid(itemtype)) {
        return "Unknown";
    }
    /*the above check is useless, as we ret "" at the end. */
    switch (itemtype) {
        case itemtype_amulet:
            return "Amulet";
            break;
        case itemtype_weapon:
            return "Weapon";
            break;
        case itemtype_armor:
            return "Armor";
            break;
        case itemtype_potion:
            return "Potion";
            break;
        case itemtype_scroll:
            return "Scroll";
            break;
        case itemtype_wand:
            return "Wand";
            break;
        case itemtype_ring:
            return "Ring";
            break;
        case itemtype_spellbook:
            return "Spellbook";
            break;
        case itemtype_gem:
            return "Gem";
            break;
        case itemtype_tool:
            return "Tool";
            break;
        case itemtype_coin:
            return "Coin";
            break;
        case itemtype_comestible:
            return "Comestible";
            break;
            
        default:
            return "Unhandled";
            break;
    }
    return "Unknown";
}

int rpg_ArmorTypeValid(ArmorType type) {
    if (armortype_unknown < type && type < armortype_last) return 1;
    return 0;
}
const char* rpg_ArmorTypeToString(ArmorType type) {
    if (1 != rpg_ArmorTypeValid(type)) {
        return "Unknown";
    }
    /*the above check is useless, as we ret "" at the end. */
    switch (type) {
        case armortype_bodyarmor:
            return "Body Armor";
            break;
        case armortype_cloak:
            return "Cloak";
            break;
        case armortype_helm:
            return "Helm";
            break;
        case armortype_shirt:
            return "Shirt";
            break;
        case armortype_shield:
            return "Shield";
            break;
        case armortype_boots:
            return "Boots";
            break;
        case armortype_gloves:
            return "Gloves";
            break;
        default:
            return "Unhandled";
            break;
    }
    return "Unknown";
}

int rpg_ScrollEffectValid(ScrollEffect effect) {
    if (scrolleffect_unknown < effect && effect < scrolleffect_last) return 1;
    return 0;
}
const char* rpg_ScrollEffectToString(ScrollEffect effect) {
    if (1 != rpg_ScrollEffectValid(effect)) {
        return "Unknown";
    }
    /*the above check is useless, as we ret "" at the end. */
    switch (effect) {
        case scrolleffect_fire:
            return "Fire";
            break;
        default:
            return "Unhandled";
            break;
    }
    return "Unknown";
}
