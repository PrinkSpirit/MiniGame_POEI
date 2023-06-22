# MiniGame POEI

## Constants

Struct Hardware info:

1. Window_Size_x
1. Window_Size_y
1. Has_Focus

## Main loop

1. Check Inputs
    1. Per key
1. Game logic
    1. Update positions
    1. Play colision function
    1. Update positions again if necessary
1. Render
    1. Background (optional)
    1. Walls
    1. Actors
    1. Player
    1. Foreground (optional)
    1. UI

## Structs

### Level

#### attributes

1. Gravity (uint)
1. Size_x (uint) - Level Size in
1. Size_y (uint)

#### Data Reference

1. Player
1. Walls []
1. Actors []
1. Background
1. Foreground

### Player

#### Attributes

1. Health
1. pos_x
1. pos_y
1. h_a: Horizontal accelaration
1. v_a: Vertical acceleration
1. ha_softCap
1. va_softCap
1. isRunning
1. needs_Update
1. hitbox (x1,y1,x2,y2)

#### Actions

1. Move
    - Accumulation: get higher the longer the same dirrection is held.
1. Jump
    - Accumulation: Keep rising if jump is held, rise slower until cap
1. Strike

#### Triggers

1. OnCollision
1. On0Hp
1. OnStruck

### Actors

#### Attributes

1. pos_x
1. pos_y
1. needs_Update
1. hitbox (x1,y1,x2,y2)

#### Triggers

1. OnColision
1. OnStruck
1. On0Hp

### WallBlock

1. pos_x
1. pos_y
1. sprite
1. Colide
1. hitbox (16x16px)

### Events

1. types
    1. Starting position
    1. Actor position (Enemy, heart, key, Door, ect)
    1. Goal Position
1. trigger
