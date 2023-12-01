
/*
    native CreatePlayerCircleProgress(playerid, Float:pos_x, Float:pos_y, color = 0xFF0000FF, background_color = 0x000000FF, Float:size = 10.0, Float:thickness = 0.2);
    native UpdatePlayerCircleProgress(playerid, drawId, value);
    native DestroyPlayerCircleProgress(playerid, drawId);
    native DestroyPlayerCircleProgressAll(playerid);
*/

            // Definers
#define                 MAX_CIRCULOS_DRAW               (50)

enum CircleDraw_Enum {
    bool:CircleDraw_Valid,

        // Config
    Float:CircleDraw_Position[2],
    Float:CircleDraw_Thickness,
    Float:CircleDraw_Size,
    CircleDraw_Color,
    CircleDraw_Background,

        // Draws
	PlayerText:CircleDraw_Points[120]
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

                    STOCKS

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
        if(CircleDraw[playerid][drawId][CircleDraw_Points][i] == PlayerText:0xFFFF) continue;
        PlayerTextDrawDestroy(playerid, CircleDraw[playerid][drawId][CircleDraw_Points][i]);
        CircleDraw[playerid][drawId][CircleDraw_Points][i] = PlayerText:INVALID_TEXT_DRAW;
	}

    new dsadsa[CircleDraw_Enum];
    CircleDraw[playerid][drawId] = dsadsa;
	return true;
}

stock CreatePlayerCircleProgress(playerid, Float:pos_x, Float:pos_y, color = 0xFF0000FF, background_color = 0x000000FF, Float:size = 10.0, Float:thickness = 0.2) {
	
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

        UpdatePlayerCircleProgress(playerid, i, 100);
        
        return i;
    }
    SendClientMessage(playerid, -1, "Error: Circle reached the limit");
    return -1;
}

stock UpdatePlayerCircleProgress(playerid, drawId, value) {

    new Float:x, Float:y, percent, count;

    /*      Prevent and Fix Values    */
    value = value < 0 ? 0 : value;
	value = value > 100 ? 100 : value;

    /*      Color Fade?               */
	percent = (120 * value) / 100;

    /*      Destroy to Update         */
    for(new i = 0; i < 120; i ++) {
        if(CircleDraw[playerid][drawId][CircleDraw_Points][i] == PlayerText:0xFFFF) continue;
        PlayerTextDrawDestroy(playerid, CircleDraw[playerid][drawId][CircleDraw_Points][i]);
        CircleDraw[playerid][drawId][CircleDraw_Points][i] = PlayerText:INVALID_TEXT_DRAW;
	}

    /*      Update and Create Points  */
    for(new Float:v = 0.0; v < 360.0; v += 3.0) {
        ctd(v + 180.0, CircleDraw[playerid][drawId][CircleDraw_Size], CircleDraw[playerid][drawId][CircleDraw_Position][0], CircleDraw[playerid][drawId][CircleDraw_Position][1], x, y);

        CircleDraw[playerid][drawId][CircleDraw_Points][count] = CreatePlayerTextDraw(playerid, x, y, ".");
        PlayerTextDrawAlignment(playerid, CircleDraw[playerid][drawId][CircleDraw_Points][count], 2);
        PlayerTextDrawLetterSize(playerid, CircleDraw[playerid][drawId][CircleDraw_Points][count], CircleDraw[playerid][drawId][CircleDraw_Thickness], CircleDraw[playerid][drawId][CircleDraw_Thickness] * 3.0);
        PlayerTextDrawSetShadow(playerid, CircleDraw[playerid][drawId][CircleDraw_Points][count], 0);
        PlayerTextDrawColor(playerid, CircleDraw[playerid][drawId][CircleDraw_Points][count], percent <= count ? (CircleDraw[playerid][drawId][CircleDraw_Background]) : (CircleDraw[playerid][drawId][CircleDraw_Color]));
        PlayerTextDrawShow(playerid, CircleDraw[playerid][drawId][CircleDraw_Points][count]);
        count++;
    }
    return true;
}