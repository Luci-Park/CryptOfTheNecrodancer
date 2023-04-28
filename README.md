# CryptOfTheNecrodancer
WindowAPI Project (2/14 ~ )

## Week 5 (3/17 ~ 3/18)
* Changed project from [Friday Night Funkin'](https://github.com/Luci-Park/FridayNightFunkin-), reused engine codes.
* Added the concept of parent and child relationship for transform.
    * Added the concept of world, local position.
    * Added the concept of world, local scale.
    * Now child transform is effected by parent transform.
* ```Player```(Cadence)'s head and body moves as one.
* ```Player``` turns depending on look direction.

## Week 6(3/19 ~ 3/ 25)
* Created class ```GameManager``` that calculates beat duration, move speed etc depending on bpm.
* Changed ```Player```'s idle animation speed to match bpm. One idle animation for each beat.
* Added ```Player``` jump animation. Now ```Player``` jumps with each movement.
* Added ```Player``` attack animation.
* Created ```Camera``` shake. Shakes with every attack.
* Warning and Title Screen added.
* Added class ```MapManager``` and ```Map```.
    * ```MapManager``` connects ```Map``` and ```GameObject```.
    * ```Map``` creates floor tiles and walls, and notifies what is where.
* Added ```MoveTowards()``` function.

## Week 7(3/26 ~ 4/1)
* ```FloorTile``` has ```FloorStrategy``` to easily change sprite.
-> therefore uses strategy pattern.
* ```StairTile``` added
* ```Map``` now only acts as a factory. The role of maintaining between objects has moved to ```MapManager```.
* ```MapManager``` also has a role in rendering order because objects in lower rows must be rendered later than those on upper lows
    * objects in ```foreground``` layer must render their children.
* ```Player``` can interact with ```Wall```.
* ```Player``` movement is the beat.
* BGM added to title screen and lobby.

## Week 8(4/2 ~ 4/8)
* ```WaterTile``` done
* Player->EnemyInteract->WallInteract->Move->TileInteract
* Monster Creation
    * ```GreenSlime```
    * `BlueSlime`
    * `OrangeSlime`
* Monster Attack Pattern
* AudioAssets organized
* Item structurizing start

## Week 9(4/9 ~ 4/15)
* Items on board implemented.
* Monster Creation
    * ```Bat```
    * `RedBat`
    * `Skeleton`
    * `GreenSkeleton`
    * `BlackSkeleton`
    * `Zombie`
* Monsters Now Move in Sync
* `Door`
* `Deep Blues`
    * `Bishop`

## Week 10(4/16 ~ 4/22)
* Map Brightness
* Reveal
    - Illuminated and line of sight
    - Revealed but not illuminated or in line of sight.
    - line of sight implemented with `Bresenham's line algorithm`
* Tile Shadow
    * Floor Shadow
    * Tile Shadow
    * Behavior
        * If illuminated and in line of sight = show as much as the illumination.
        * If not but was revealed, show 30%
        * If not, don't show
* Tile Behavior according to light
    * If illuminated and in line of sight = is active.
    * If was revealed = show in default state.
* Monsters
    * Sprites
        * Tile not revealed = don't show
        * If Tile revealed but not inSight or not illuminated = inShadows
        * If inSight and illuminated = full color
    * Behavior
        * Aggroed
            * if in sight
            * and inside a 20 * 12 tile rectangle
            * permanent
        * Activated
            * Is within a certain radius
        * Can act if either aggroed or activated
    * MidBoss added
        * `Virebat`
        * `Minotaur`
        * `Dragon`
## Week 10(4/23 ~ 4/29)
* `Dragon`
    * `Fireball`
        * Damage and Animation
        * Shoots until meets wall
        * Fireball emits light
* Health UI
* `Deep Blues`
    * `Pawn`
    * `Bishop`
    * `Rook`
    * `Knight`
    * `Queen`
    * `King`