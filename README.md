# 🚀 Circle Progress
The project is an improved "model" of [freesampscripts](https://github.com/freesampscripts/circle-speedo)

# ⚙️ New Natives
```pawn
native CreatePlayerCircleProgress(playerid, Float:pos_x, Float:pos_y, color = 0xFFFFFFFF, background_color = 0x181818FF, Float:size = 10.0, Float:thickness = 0.2, Float:polygons = DEFAULT_CIRCLE_POLYGONS);
native UpdatePlayerCircleProgress(playerid, drawId, value);
native DestroyPlayerCircleProgress(playerid, drawId);
native DestroyPlayerCircleProgressAll(playerid);
```

> [!IMPORTANT]
> About params:
> - **Thickness:** Circle line size
> - **Polygons:** Number of points to form a perfect circle, the larger it is, the more defined it will be, but it will use more textdraw resources, the limit is 256
> - **Size:** Circle size (match Polygons)
> - **drawId:** ID returned by ***CreatePlayerCircleProgress*** with the circle ID

# 🌐 What are the changes?
- Circles are created individually, allowing up to 40 progress indicators
- Added new native functions

# 📝 Credits
- freesampscripts - Create source code
- Diogo "blueN" - Recreate code with new natives and update functions

# Preview
![](https://github.com/igdiogo/Circular-Progress-Samp/blob/main/preview.gif)
