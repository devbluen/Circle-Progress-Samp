# 🚀 Shapes Progress
The project is a fork of [Circular-Progress-Samp](https://github.com/igdiogo/Circular-Progress-Samp), an improved "model" of [freesampscripts](https://github.com/freesampscripts/circle-speedo), now with support for multiple shapes.

# ⚙️ New Natives
```pawn
native CreatePlayerCircleProgress(playerid, Float:pos_x, Float:pos_y, max_value = 100, color = 0xFF0000FF, background_COLOR = 0x000000FF, Float:size = 10.0, Float:thickness = 0.2, Float:polygons = DEFAULT_CIRCLE_POLYGONS);
native UpdatePlayerCircleProgress(playerid, id, value);
native DestroyPlayerCircleProgress(playerid, id);
native DestroyPlayerCircleProgressAll(playerid);

native CreatePlayerHexagonProgress(playerid, Float:pos_x, Float:pos_y, max_value = 100, color = 0xFF0000FF, background_COLOR = 0x000000FF, Float:size = 10.0, Float:thickness = 0.2, Float:polygons = DEFAULT_CIRCLE_POLYGONS);
native UpdatePlayerHexagonProgress(playerid, id, value);
native DestroyPlayerHexagonProgress(playerid, id);
native DestroyPlayerHexagonProgressAll(playerid);

native CreatePlayerDiamondProgress(playerid, Float:pos_x, Float:pos_y, max_value = 100, color = 0xFF0000FF, background_COLOR = 0x000000FF, Float:size = 10.0, Float:thickness = 0.2, Float:polygons = DEFAULT_CIRCLE_POLYGONS);
native UpdatePlayerDiamondProgress(playerid, id, value);
native DestroyPlayerDiamondProgress(playerid, id);
native DestroyPlayerDiamondProgressAll(playerid);

native CreatePlayerSquareProgress(playerid, Float:pos_x, Float:pos_y, max_value = 100, color = 0xFF0000FF, background_COLOR = 0x000000FF, Float:size = 10.0, Float:thickness = 0.2, Float:polygons = DEFAULT_CIRCLE_POLYGONS);
native UpdatePlayerSquareProgress(playerid, id, value);
native DestroyPlayerSquareProgress(playerid, id);
native DestroyPlayerSquareProgressAll(playerid);

native CreatePlayerTriangleProgress(playerid, Float:pos_x, Float:pos_y, max_value = 100, color = 0xFF0000FF, background_COLOR = 0x000000FF, Float:size = 10.0, Float:thickness = 0.2, Float:polygons = DEFAULT_CIRCLE_POLYGONS, bool:invert = false);
native UpdatePlayerTriangleProgress(playerid, id, value);
native DestroyPlayerTriangleProgress(playerid, id);
native DestroyPlayerTriangleProgressAll(playerid);

native CreatePlayerParensProgress(playerid, Float:pos_x, Float:pos_y, max_value = 100, color = 0xFF0000FF, background_COLOR = 0x000000FF, Float:size = 10.0, Float:thickness = 0.2, Float:polygons = DEFAULT_CIRCLE_POLYGONS, bool:invert = false);
native UpdatePlayerParensProgress(playerid, id, value);
native DestroyPlayerParensProgress(playerid, id);
native DestroyPlayerParensProgressAll(playerid);

native CreatePlayerArcProgress(playerid, Float:pos_x, Float:pos_y, max_value = 100, color = 0xFF0000FF, background_COLOR = 0x000000FF, Float:size = 10.0, Float:thickness = 0.2, Float:polygons = DEFAULT_CIRCLE_POLYGONS);
native UpdatePlayerArcProgress(playerid, id, value);
native DestroyPlayerArcProgress(playerid, id);
native DestroyPlayerArcProgressAll(playerid);
```

> [!IMPORTANT]
> About params:
> - **Max Value:** Maximum value of the progress, default `100`
> - **Thickness:** Shape line size
> - **Polygons:** Number of points to form a perfect circle, the smaller it is, the more defined it will be, but it will use more textdraw resources, the limit is 120 (recommended `15.0`, use `3.0` for quality)
> - **Size:** Shape size (match Polygons)
> - **Invert:** Invert the shape direction (only **Triangle** and **Parens**)
> - **Id:** ID returned by ***CreatePlayerXxxProgress*** with the shape ID

# 📝 Example use
```pawn
new circleId = CreatePlayerCircleProgress(playerid, Float:pos_x, Float:pos_y, 100, 0xFF0000FF, 0x000000FF, 10.0, 0.2, 15.0);
UpdatePlayerCircleProgress(playerid, circleId, 100);
```

# 🌐 What are the changes?
- Shapes are created individually, allowing up to 10 progress indicators per player
- Added 6 new shapes: **Hexagon**, **Diamond**, **Square**, **Triangle**, **Parens** and **Arc**
- Added `max_value` param to all create natives
- Added `invert` param to **Triangle** and **Parens** natives
- Added new native functions
- Auto cleanup on `OnPlayerDisconnect`

# 📝 Credits
- freesampscripts - Create source code
- Diogo "blueN" - Recreate code with new natives and update functions
- Vitor "greeN" - Added support for new progress formats

# Preview
![](https://github.com/igdiogo/Circular-Progress-Samp/blob/main/preview.gif)
