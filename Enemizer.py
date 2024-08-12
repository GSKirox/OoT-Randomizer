import random
from ProcessActors import *
from EnemizerList import *
from World import World


def get_rom_enemies(scenes: list[Scene], rom: Rom):
    enemy_list: dict[tuple[int,int,int,int],Actor] = {}
    for scene in scenes:
        for room in scene.rooms:
            for setup in room.setups:
                actors = room.setups[setup].actors
                for i in range(0, len(actors)):
                    if actors[i].id in enemy_actor_types.keys():
                        filter = enemy_actor_types[actors[i].id].filter_func
                        if(filter is None or filter(actors[i])):
                            enemy_list[(scene.id, room.id,setup,i)] = (actors[i])
    return enemy_list

def set_enemies(worlds: list[World]):
    for world in worlds:
        world.enemy_list = build_enemylist(world)

def build_enemylist(world: World):
    enemy_list = base_enemy_list.copy()
    mq_dungeons = [dungeon for dungeon in world.dungeon_mq if world.dungeon_mq[dungeon] == True]
    vanilla_dungeons = [dungeon for dungeon in world.dungeon_mq if world.dungeon_mq[dungeon] == False]
    
    for dungeon in mq_dungeons:
        if dungeon in mq_dungeon_enemies.keys():
            enemy_list.update(mq_dungeon_enemies[dungeon])
    
    for dungeon in vanilla_dungeons:
        if dungeon in vanilla_dungeon_enemies.keys():
            enemy_list.update(vanilla_dungeon_enemies[dungeon])

    return enemy_list

def shuffle_enemies(worlds: list[World]):
    for world in worlds:
        world.shuffled_enemies = _shuffle_enemies(world.enemy_list)
        # Enemies by scene/room
        scene_enemies = {}
        for key in world.shuffled_enemies:
            scene, room, setup, index = key
            if scene not in scene_enemies.keys():
                scene_enemies[scene] = {}
            if room not in scene_enemies[scene].keys():
                scene_enemies[scene][room] = {}
            if setup not in scene_enemies[scene][room].keys():
                scene_enemies[scene][room][setup] = {}
            scene_enemies[scene][room][setup][key] = world.shuffled_enemies[key]
        world.enemies_by_scene = scene_enemies

def _shuffle_enemies(enemy_list: dict[tuple[int,int,int,int],int]) -> dict[tuple[int,int,int,int], tuple[int,bool]]: 
    shuffled: dict[tuple[int,int,int,int], tuple[int,bool]] = {}
    enemy_choices = list(enemy_actor_types.keys())
    for enemy_key in enemy_list:
        enemy_type = enemy_list[enemy_key]
        choice = random.choice(enemy_choices)
        enemy = enemy_actor_types[choice]
        if type(enemy) is EnemyWithOpts:
            enemy = random.choice(enemy.enemyOpts)
        shuffled[enemy_key] = (choice, enemy, True)
    return shuffled

def patch_enemies(enemy_list: dict[tuple[int,int,int,int],Actor], shuffled_enemies: dict[tuple[int,int,int,int], tuple[int,bool]], rom):
    for enemy_key in shuffled_enemies:
        keys = [enemy_key]
        if enemy_key in base_enemy_alts.keys():
            alt = base_enemy_alts[enemy_key]
            if type(alt) is list:
                keys.extend(base_enemy_alts[enemy_key])
            else:
                keys.append(base_enemy_alts[enemy_key])
        for key in keys:
            enemy_id, enemy, shuffled = shuffled_enemies[enemy_key]
            if key in enemy_list.keys():
                enemy_actor = enemy_list[key]
                if shuffled:
                    enemy_actor.rot_x = 0
                    enemy_actor.rot_z = 0
                    enemy_actor.id = enemy_id
                    enemy_actor.var = enemy.var
                    rom.write_bytes(enemy_actor.addr, enemy_actor.get_bytes())
            else:
                print(f"Missing enemy actor {key}")
