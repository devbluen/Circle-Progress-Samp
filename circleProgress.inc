

/*

                    ooooo      ooo       .o.       ooooooooooooo ooooo oooooo     oooo       .o.        .oooooo..o 
                    `888b.     `8'      .888.      8'   888   `8 `888'  `888.     .8'       .888.      d8P'    `Y8 
                    8 `88b.    8      .8"888.          888       888    `888.   .8'       .8"888.     Y88bo.      
                    8   `88b.  8     .8' `888.         888       888     `888. .8'       .8' `888.     `"Y8888o.  
                    8     `88b.8    .88ooo8888.        888       888      `888.8'       .88ooo8888.        `"Y88b 
                    8       `888   .8'     `888.       888       888       `888'       .8'     `888.  oo     .d8P 
                    o8o        `8  o88o     o8888o     o888o     o888o       `8'       o88o     o8888o 8""88888P'  


        native CreatePlayerCircleProgress(playerid, Float:pos_x, Float:pos_y, color = 0xFF0000FF, background_COLOR = 0x000000FF, Float:size = 10.0, Float:thickness = 0.2, polygons = DEFAULT_CIRCLE_POLYGONS);
        native UpdatePlayerCircleProgress(playerid, id, value);
        native DestroyPlayerCircleProgress(playerid, id);
        native DestroyPlayerCircleProgressAll(playerid);
                                                                                          
*/


            // Definers
#define                 DEFAULT_CIRCLE_POLYGONS         (15.0)  // If you want quality, use 3.0.
#define                 MAX_CIRCLES_POLYGONS            (120)
#define                 MAX_CIRCLES_DRAW                (10)
// The smaller the number, the more defined the circle will be. I recommend using 15.0 to support more circles and textdraws without exceeding the limit imposed by SAMP.

            // Includes
#include <YSI_Coding\y_hooks>
#include <YSI_Data\y_iterate>

static enum CIRCLE_ENUM {

        // Config
    Float:E_CIRCLEDRAW_POSITION[2],
    Float:E_CIRCLEDRAW_THICKNESS,
    Float:E_CIRCLEDRAW_SIZE,
    Float:E_CIRCLEDRAW_VALUE,
    Float:E_CIRCLEDRAW_POLYGONS,
    Float:E_CIRCLEDRAW_MAX_VALUE,

        // Colors
    E_CIRCLEDRAW_COLOR,
    E_CIRCLEDRAW_BACKGROUND,
    E_CIRCLEDRAW_POLYGONS_COUNT,

        // Draws
    bool:E_CIRCLEDRAW_CREATED[MAX_CIRCLES_POLYGONS + 1],
	PlayerText:E_CIRCLEDRAW_POINTS[MAX_CIRCLES_POLYGONS + 1]
};

static
    Iterator:Circles[MAX_PLAYERS]<MAX_CIRCLES_DRAW>,
    e_CircleDraw[MAX_PLAYERS][MAX_CIRCLES_DRAW][CIRCLE_ENUM];



/*

                    ooooooooo.   ooooo     ooo oooooooooo.  ooooo        ooooo   .oooooo.   
                    `888   `Y88. `888'     `8' `888'   `Y8b `888'        `888'  d8P'  `Y8b  
                    888   .d88'  888       8   888     888  888          888  888          
                    888ooo88P'   888       8   888oooo888'  888          888  888          
                    888          888       8   888    `88b  888          888  888          
                    888          `88.    .8'   888    .88P  888       o  888  `88b    ooo  
                    o888o           `YbodP'    o888bood8P'  o888ooooood8 o888o  `Y8bood8P'  

*/

hook OnPlayerDisconnect(playerid, reason) {

    DestroyPlayerCircleProgressAll(playerid);       // Invalid All [Not Required if you use Streamertextdraw :)]
    return Y_HOOKS_CONTINUE_RETURN_1;
}



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

    foreach(new i: Circles[playerid])
        DestroyPlayerCircleProgress(playerid, i);   

    return true;
}

stock DestroyPlayerCircleProgress(playerid, id) {
    
    if(!Iter_Contains(Circles[playerid], id)) 
        return false;

    for(new i = 0; i < e_CircleDraw[playerid][id][E_CIRCLEDRAW_POLYGONS_COUNT]; i++) {
        PlayerTextDrawDestroy(playerid, e_CircleDraw[playerid][id][E_CIRCLEDRAW_POINTS][i]);
        e_CircleDraw[playerid][id][E_CIRCLEDRAW_POINTS][i] = PlayerText:INVALID_TEXT_DRAW;
        e_CircleDraw[playerid][id][E_CIRCLEDRAW_CREATED][i] = false;
    }

    Iter_Remove(Circles[playerid], id);

    new dsadsa[CIRCLE_ENUM];
    e_CircleDraw[playerid][id] = dsadsa;
	return true;
}

stock CreatePlayerCircleProgress(playerid, Float:pos_x, Float:pos_y, max_value = 100, color = 0xFF0000FF, background_COLOR = 0x000000FF, Float:size = 10.0, Float:thickness = 0.2, Float:polygons = DEFAULT_CIRCLE_POLYGONS) {
	
    new index = Iter_Free(Circles[playerid]);
    if(index == -1) return -1;

    /*      Config                    */
    e_CircleDraw[playerid][index][E_CIRCLEDRAW_THICKNESS] = thickness;
    e_CircleDraw[playerid][index][E_CIRCLEDRAW_COLOR] = color;
    e_CircleDraw[playerid][index][E_CIRCLEDRAW_BACKGROUND] = background_COLOR;
    e_CircleDraw[playerid][index][E_CIRCLEDRAW_SIZE] = size;
    e_CircleDraw[playerid][index][E_CIRCLEDRAW_POSITION][0] = pos_x;
    e_CircleDraw[playerid][index][E_CIRCLEDRAW_POSITION][1] = pos_y;
    e_CircleDraw[playerid][index][E_CIRCLEDRAW_VALUE] = -1.0;   // Prevent Bugs
    e_CircleDraw[playerid][index][E_CIRCLEDRAW_POLYGONS] = polygons;
    e_CircleDraw[playerid][index][E_CIRCLEDRAW_MAX_VALUE] = max_value;

    Iter_Add(Circles[playerid], index);
    UpdatePlayerCircleProgress(playerid, index, 100);
    return index;
}

stock UpdatePlayerCircleProgress(playerid, id, value) {
    
    if(e_CircleDraw[playerid][id][E_CIRCLEDRAW_VALUE] == value) 
        return true;

    new 
        Float:preValue = e_CircleDraw[playerid][id][E_CIRCLEDRAW_POLYGONS], 
        Float:x, 
        Float:y, 
        maxvalue = e_CircleDraw[playerid][id][E_CIRCLEDRAW_MAX_VALUE],
        preDraws,
        percent, 
        index;

    for(new Float:v = 0.0; v < 360.0; v += preValue)
        preDraws++;

    /*      Prevent and Fix Values    */
    value = value < 0 ? 0 : value;
	value = value > maxvalue ? maxvalue : value;

    /*      Color Fade?               */
	percent = (preDraws * value) / maxvalue;

    /*      Update and Create Points  */
    for(new Float:v = 0.0; v < 360.0; v += preValue) {
        ctd(v + 180.0, e_CircleDraw[playerid][id][E_CIRCLEDRAW_SIZE], e_CircleDraw[playerid][id][E_CIRCLEDRAW_POSITION][0], e_CircleDraw[playerid][id][E_CIRCLEDRAW_POSITION][1], x, y);

        if(!e_CircleDraw[playerid][id][E_CIRCLEDRAW_CREATED][index]) {
            e_CircleDraw[playerid][id][E_CIRCLEDRAW_POINTS][index] = CreatePlayerTextDraw(playerid, x, y, ".");
            PlayerTextDrawAlignment(playerid, e_CircleDraw[playerid][id][E_CIRCLEDRAW_POINTS][index], 2);
            PlayerTextDrawLetterSize(playerid, e_CircleDraw[playerid][id][E_CIRCLEDRAW_POINTS][index], e_CircleDraw[playerid][id][E_CIRCLEDRAW_THICKNESS], e_CircleDraw[playerid][id][E_CIRCLEDRAW_THICKNESS] + (e_CircleDraw[playerid][id][E_CIRCLEDRAW_THICKNESS] * 2));
            PlayerTextDrawSetShadow(playerid, e_CircleDraw[playerid][id][E_CIRCLEDRAW_POINTS][index], 0);

            e_CircleDraw[playerid][id][E_CIRCLEDRAW_CREATED][index] = true;
		}

		PlayerTextDrawColor(playerid, e_CircleDraw[playerid][id][E_CIRCLEDRAW_POINTS][index], percent <= index ? (e_CircleDraw[playerid][id][E_CIRCLEDRAW_BACKGROUND]) : (e_CircleDraw[playerid][id][E_CIRCLEDRAW_COLOR]));
        index++;
    }

    /*     Security Update           */
    e_CircleDraw[playerid][id][E_CIRCLEDRAW_VALUE] = value;
    e_CircleDraw[playerid][id][E_CIRCLEDRAW_POLYGONS_COUNT] = index;
    
    /*     Update                    */
    for(new i = 0; i < value; i++)
        PlayerTextDrawShow(playerid, e_CircleDraw[playerid][id][E_CIRCLEDRAW_POINTS][i]);  
    
    return true;
}
