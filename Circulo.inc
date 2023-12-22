

/*

                    ooooo      ooo       .o.       ooooooooooooo ooooo oooooo     oooo       .o.        .oooooo..o 
                    `888b.     `8'      .888.      8'   888   `8 `888'  `888.     .8'       .888.      d8P'    `Y8 
                    8 `88b.    8      .8"888.          888       888    `888.   .8'       .8"888.     Y88bo.      
                    8   `88b.  8     .8' `888.         888       888     `888. .8'       .8' `888.     `"Y8888o.  
                    8     `88b.8    .88ooo8888.        888       888      `888.8'       .88ooo8888.        `"Y88b 
                    8       `888   .8'     `888.       888       888       `888'       .8'     `888.  oo     .d8P 
                    o8o        `8  o88o     o8888o     o888o     o888o       `8'       o88o     o8888o 8""88888P'  


        native CreatePlayerCircleProgress(playerid, Float:pos_x, Float:pos_y, color = 0xFF0000FF, background_color = 0x000000FF, Float:size = 10.0, Float:thickness = 0.2, polygons = DEFAULT_CIRCLE_POLYGONS);
        native UpdatePlayerCircleProgress(playerid, drawId, value);
        native DestroyPlayerCircleProgress(playerid, drawId);
        native DestroyPlayerCircleProgressAll(playerid);
                                                                                          
*/


            // Definers
#define                 MAX_CIRCULOS_DRAW               (50)
#define                 DEFAULT_CIRCLE_POLYGONS         (15.0)  // If you want quality, use 3.0.
// The smaller the number, the more defined the circle will be. I recommend using 15.0 to support more circles and textdraws without exceeding the limit imposed by SAMP.

enum CircleDraw_Enum {

        // Creating
    bool:CircleDraw_Valid,
    bool:CircleDraw_Update,

        // Config
    Float:CircleDraw_Position[2],
    Float:CircleDraw_Thickness,
    Float:CircleDraw_Size,
    Float:CircleDraw_Value,
    CircleDraw_Color,
    CircleDraw_Polygons,
    CircleDraw_Background,

        // Draws
	PlayerText:CircleDraw_Points[120 + 1]
}
new CircleDraw[MAX_PLAYERS][MAX_CIRCULOS_DRAW][CircleDraw_Enum];

public OnPlayerDisconnect(playerid, reason) {

	DestroyPlayerCircleProgressAll(playerid);       // Invalid All [Not Required if you use Streamertextdraw :)]

	new ret = 1;
	#if defined MainCircle_OnPlayerDisconnect
		ret = MainCircle_OnPlayerDisconnect(playerid, reason);
	#endif
	return ret;
}

#if defined _ALS_OnPlayerDisconnect
	#undef OnPlayerDisconnect
#else
	#define _ALS_OnPlayerDisconnect
#endif
#define OnPlayerDisconnect MainCircle_OnPlayerDisconnect
#if defined MainCircle_OnPlayerDisconnect
	forward MainCircle_OnPlayerDisconnect(playerid, reason);
#endif



/*

                    .oooooo..o ooooooooooooo   .oooooo.     .oooooo.   oooo    oooo  .oooooo..o
                    d8P'    `Y8 8'   888   `8  d8P'  `Y8b   d8P'  `Y8b  `888   .8P'  d8P'    `Y8
                    Y88bo.           888      888      888 888           888  d8'    Y88bo.     
                    `"Y8888o.       888      888      888 888           88888[       `"Y8888o. 
                        `"Y88b      888      888      888 888           888`88b.         `"Y88b
                    oo     .d8P      888      `88b    d88' `88b    ooo   888  `88b.  oo     .d8P
                    8""88888P'      o888o      `Y8bood8P'   `Y8bood8P'  o888o  o888o 8""88888P' 

*/

stock ctd(Float:angle, Float:distance, Float:sx, Float:sy, &Float:x, &Float:y) {
	x = sx + (distance * floatsin(-angle, degrees));
	y = sy + (distance * floatcos(angle, degrees));
	return true;
}

stock DestroyPlayerCircleProgressAll(playerid) {

    for(new i = 0; i < MAX_CIRCULOS_DRAW; i++)
        DestroyPlayerCircleProgress(playerid, i);   

    return true;
}

stock DestroyPlayerCircleProgress(playerid, drawId) {
    
    if(drawId >= MAX_CIRCULOS_DRAW) return false;
    if(CircleDraw[playerid][drawId][CircleDraw_Valid] == false) return false;

    for(new i = 0; i < 120; i ++) {
        if(CircleDraw[playerid][drawId][CircleDraw_Points][i] == PlayerText:INVALID_TEXT_DRAW) continue;
        PlayerTextDrawDestroy(playerid, CircleDraw[playerid][drawId][CircleDraw_Points][i]);
        CircleDraw[playerid][drawId][CircleDraw_Points][i] = PlayerText:INVALID_TEXT_DRAW;
	}

    new dsadsa[CircleDraw_Enum];
    CircleDraw[playerid][drawId] = dsadsa;
	return true;
}

stock CreatePlayerCircleProgress(playerid, Float:pos_x, Float:pos_y, color = 0xFF0000FF, background_color = 0x000000FF, Float:size = 10.0, Float:thickness = 0.2, polygons = DEFAULT_CIRCLE_POLYGONS) {
	
    for(new i = 0; i < MAX_CIRCULOS_DRAW; i++) {
        if(CircleDraw[playerid][i][CircleDraw_Valid] == true) continue;

        /*      Config                    */
        CircleDraw[playerid][i][CircleDraw_Valid] = true;
        CircleDraw[playerid][i][CircleDraw_Thickness] = thickness;
        CircleDraw[playerid][i][CircleDraw_Color] = color;
        CircleDraw[playerid][i][CircleDraw_Background] = background_color;
        CircleDraw[playerid][i][CircleDraw_Size] = size;
        CircleDraw[playerid][i][CircleDraw_Position][0] = pos_x;
        CircleDraw[playerid][i][CircleDraw_Position][1] = pos_y;
        CircleDraw[playerid][i][CircleDraw_Value] = -1.0;   // Prevent Bugs
        CircleDraw[playerid][i][CircleDraw_Polygons] = polygons;

        UpdatePlayerCircleProgress(playerid, i, 100);
        return i;
    }
    SendClientMessage(playerid, -1, "Error: Circle reached the limit");
    return -1;
}

stock UpdatePlayerCircleProgress(playerid, drawId, value) {
    if(CircleDraw[playerid][drawId][CircleDraw_Value] == value) return true;    // Prevent Lags

    new Float:x, Float:y, percent, count, Float:preValue = CircleDraw[playerid][drawId][CircleDraw_Polygons], preDraws;
    for(new Float:v = 0.0; v < 360.0; v += preValue)
        preDraws++;

    /*      Prevent and Fix Values    */
    value = value < 0 ? 0 : value;
	value = value > 100 ? 100 : value;

    /*      Color Fade?               */
	percent = (preDraws * value) / 100;

    /*      Update and Create Points  */
    for(new Float:v = 0.0; v < 360.0; v += preValue) {
        ctd(v + 180.0, CircleDraw[playerid][drawId][CircleDraw_Size], CircleDraw[playerid][drawId][CircleDraw_Position][0], CircleDraw[playerid][drawId][CircleDraw_Position][1], x, y);

        if(CircleDraw[playerid][drawId][CircleDraw_Update] == false) {
            CircleDraw[playerid][drawId][CircleDraw_Points][count] = CreatePlayerTextDraw(playerid, x, y, ".");
            PlayerTextDrawAlignment(playerid, CircleDraw[playerid][drawId][CircleDraw_Points][count], 2);
            PlayerTextDrawLetterSize(playerid, CircleDraw[playerid][drawId][CircleDraw_Points][count], CircleDraw[playerid][drawId][CircleDraw_Thickness], CircleDraw[playerid][drawId][CircleDraw_Thickness] + (CircleDraw[playerid][drawId][CircleDraw_Thickness] * 2));
            PlayerTextDrawSetShadow(playerid, CircleDraw[playerid][drawId][CircleDraw_Points][count], 0);
        }
        PlayerTextDrawColor(playerid, CircleDraw[playerid][drawId][CircleDraw_Points][count], percent <= count ? (CircleDraw[playerid][drawId][CircleDraw_Background]) : (CircleDraw[playerid][drawId][CircleDraw_Color]));
        count++;
    }

    /*     Security Update           */
    CircleDraw[playerid][drawId][CircleDraw_Update] = true;
    CircleDraw[playerid][drawId][CircleDraw_Value] = value;
    
    for(new i = 0; i < count; i++) {
        if(!IsValidDynamicPlayerTextDraw(playerid, CircleDraw[playerid][drawId][CircleDraw_Points][i])) continue;
        PlayerTextDrawShow(playerid, CircleDraw[playerid][drawId][CircleDraw_Points][i]);  
    }
    return true;
}
