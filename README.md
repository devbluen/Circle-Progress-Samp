# 🚀 Circle Progress
The project is an improved "model" of [freesampscripts](https://github.com/freesampscripts/circle-speedo)

# ⚙️ New Natives
```pawn
native CreatePlayerCircleProgress(playerid, Float:pos_x, Float:pos_y, color = 0xFFFFFFFF, background_color = 0x181818FF, Float:size = 10.0, Float:thickness = 0.2, Float:polygons = DEFAULT_CIRCLE_POLYGONS);
native UpdatePlayerCircleProgress(playerid, drawId, value);
native DestroyPlayerCircleProgress(playerid, drawId);
native DestroyPlayerCircleProgressAll(playerid);
```

# 🌐 What are the changes?
- Circles are created individually, allowing up to 40 progress indicators
- Added new native functions

# 📝 Credits
- freesampscripts - Create source code
- Diogo "blueN" - Recreate code with new natives and update functions

# Preview
![](https://github.com/igdiogo/Circular-Progress-Samp/blob/main/preview.gif)
