#include "PLUSH_core_includes.h"
#include "PLUSH_includes.h"
#include "Helpers.h"
#include <random>

#include <cmath>
#include <iostream>

TileGame::TileGame(){
    std::shared_ptr<PLUSH::WindowHandler> newwindow(new PLUSH::WindowHandler("TileGame"));
    window = newwindow;

    std::shared_ptr<PLUSH::TileGrid> newtilegrid(new PLUSH::TileGrid(48, 48));
    tilegrid = newtilegrid;

    std::shared_ptr<PLUSH::TileGridLayer> newtilegridlayer(new PLUSH::TileGridLayer("TileGrid1"));
    tilegridlayer = newtilegridlayer;

    tilegridlayer->setTileGrid(tilegrid);

    window->addDrawableLayer(tilegridlayer);

    setTileGridDimensions();

    x_pos = 0.0;
    y_pos = 0.0;

    offsetX = 0.0;
    offsetY = 0.0;

    tiledimensionsX = 0.08;
    tiledimensionsY = 0.08;

    movementBoundaryRatioX = 0.25;
    movementBoundaryRatioY = 0.25;

    tilegridlayer->setOffset(offsetX, offsetY);
    tilegridlayer->setTileDimensions(tiledimensionsX, tiledimensionsY);

    std::shared_ptr<PLUSH::Entity> character(new PLUSH::Entity("Avatar", "tile.vx"));
    character->getStatusPointer()->visible = true;
    character->setTexture2DUniform("primaryTexture", "Dragon");

    std::shared_ptr<PLUSH::Entity> held(new PLUSH::Entity("HeldTile", "tile.vx"));
    heldTileStatus = held->getStatusPointer();
    heldTileStatus->visible = false;
    held->setTexture2DUniform("primaryTexture", "TheBlundon");

    heldTile_ptr = held;

    tilegridlayer->addMoveable(character);
    tilegridlayer->setMoveablePosition("Avatar", x_pos, y_pos);
    tilegridlayer->addMoveable(held);
    tilegridlayer->setMoveablePosition("HeldTile", x_pos, y_pos+1);

    // std::cout << "Set initial avatar position to " << tilegridlayer->getMoveables()[0]->getPosition()[0] <<", " << tilegridlayer->getMoveables()[0]->getPosition()[1] << std::endl;

    tilegridlayer->resetHighlights();
    // tilegridlayer->addHighlight(2, 2);

    // PLUSH_helpers::Set_V_Sync(false);
}

void TileGame::setTileGridDimensions(){
    aspectratio = window->getAspectRatio();
    invaspectratio = window->getInverseAspectRatio();

    tilegriddimensionsX = 1.8;
    tilegriddimensionsY = 1.8*invaspectratio;

    positionX = -0.9;
    positionY = -0.9*invaspectratio;

    width = tilegrid->getWidth();
    height = tilegrid->getHeight();

    tilegridlayer->setDimensions(tilegriddimensionsX, tilegriddimensionsY);
    tilegridlayer->setPosition(positionX, positionY);
}

void TileGame::snapAvatarPosition(){
    if (x_pos < 0.0){
        x_pos = 0.0;
    }
    if(y_pos < 0.0){
        y_pos = 0.0;
    }
    if(x_pos > width-1){
        x_pos = width-1;
    }
    if(y_pos > height-1){
        y_pos = height - 1;
    }
}

void TileGame::run(){
    prepareBoard();

    currentTime = PLUSH_helpers::GetTime();

    float time_float_prev = currentTime;

    while(!window->ShouldClose()){

        window->draw(); // draw

        //check and process (TBD) inputs
        PLUSH_helpers::PollEvents_GLFW();

        time_float_prev = currentTime;
        currentTime = PLUSH_helpers::GetTime();

        processInputs(currentTime - time_float_prev);
        
        snapAvatarPosition();
        tilegridlayer->setMoveablePosition("Avatar", x_pos, y_pos);

        tilegridlayer->setMoveablePosition("HeldTile", x_pos, y_pos+1);

        iterateGameState();

        setTileGridDimensions();

        setTileGridOffset();
    }
    PLUSH_helpers::Terminate_GLFW();
}

void TileGame::processMouse(float frame_time){
    int new_target_i = getMouseTileX();
    int new_target_j = getMouseTileY();


    tilegridlayer->resetHighlights();

    if((std::abs(new_target_i - x_pos) < 4.5) && (std::abs(new_target_j - y_pos) < 4.5)){
        tilegridlayer->addHighlight(new_target_i, new_target_j);
    }else{
        new_target_i = -1;
        new_target_j = -1;
    }

    if (mouse_target_i != new_target_i || mouse_target_j != new_target_j){
        mouse_target_changed = true;
        mouse_target_i = new_target_i;
        mouse_target_j = new_target_j;
    } else {
        mouse_target_changed = false;
    }

    PLUSH_helpers::MouseStatus* mousestatus = window->getMouseStatusPointer();

    if(mousestatus->LEFT_MOUSE_PRESSED){
        current_action = FIRE;
    }
    if(mousestatus->RIGHT_MOUSE_PRESSED){
        current_action = MAGIC;
    }
}

void TileGame::processInputs(float frame_time){
    current_action = NO_ACTION;

    processKeys(frame_time);
    processMouse(frame_time);

    int new_self_target_i = (int)(x_pos + 0.5);
    int new_self_target_j = (int)(y_pos + 0.5);

    if(new_self_target_i != self_target_i || new_self_target_j != self_target_j){
        self_target_changed = true;
        self_target_i = new_self_target_i;
        self_target_j = new_self_target_j;
    } else {
        self_target_changed = false;
    }


    if(current_action == NO_ACTION){
        duration_of_action = 0.0f;
    } else {
        if (current_action == previous_action){
            duration_of_action += frame_time;
        } else {
            duration_of_action = 0.0f;
        }
    }

    switch (current_action) {
        case FIRE:
        case MAGIC:
            if(mouse_target_changed){
                duration_of_action = 0.0;
            }
            break;
        case STOMP:
            if (self_target_changed){
                duration_of_action = 0.0;
            }
            break;
        default:
            break;
    }

    previous_action = current_action;
}

void TileGame::setTileGridOffset(){
    float adjustedX = (x_pos + 0.5)*tiledimensionsX - offsetX - tilegriddimensionsX/2.0;
    float adjustedY = (y_pos + 0.5)*tiledimensionsY - offsetY - tilegriddimensionsY/2.0;
    
    if(adjustedX < -movementBoundaryRatioX*tilegriddimensionsX/2.0){
        offsetX += adjustedX + movementBoundaryRatioX*tilegriddimensionsX/2.0;
    }
    if(adjustedX > movementBoundaryRatioX*tilegriddimensionsX/2.0){
        offsetX += adjustedX - movementBoundaryRatioX*tilegriddimensionsX/2.0;
    }

    if(adjustedY < -movementBoundaryRatioY*tilegriddimensionsY/2.0){
        offsetY += adjustedY + movementBoundaryRatioY*tilegriddimensionsY/2.0;
    }
    if(adjustedY > movementBoundaryRatioY*tilegriddimensionsY/2.0){
        offsetY += adjustedY - movementBoundaryRatioY*tilegriddimensionsY/2.0;
    }

    tilegridlayer->setOffset(offsetX, offsetY);
    
    tilegridlayer->snapToEdges_IfOutOfBounds();

    offsetX = tilegridlayer->getOffsetX();
    offsetY = tilegridlayer->getOffsetY();
}

void TileGame::prepareBoard(){
    for(unsigned int i = 0; i < tilegrid->getWidth() ; i++){
        for(unsigned int j = 0; j < tilegrid->getHeight() ; j++){
            int random_value = (int)(rand()*3.0/RAND_MAX);

            switch (random_value) {
                case 0:
                    setTile(FOREST, i, j);
                    break;
                case 1:
                    setTile(FOLIAGE, i, j);
                    break;
                case 2:
                    setTile(EARTH, i, j);
                    break;
                default:
                    setTile(BLUNDON, i, j);
                    break;
            }

        }
    }
}

void TileGame::flipTile(unsigned int i, unsigned int j){
    Tile_ID id = (Tile_ID) tilegrid->getTile(i, j)->getStatusPointer()->ID;
    tilegrid->getTile(i, j)->getStatusPointer()->ID = (id==BLUNDON ? AWESOME : BLUNDON);

    if(id == BLUNDON){
        tilegrid->getTile(i, j)->setTexture2DUniform("primaryTexture", "AwesomeFace");
    }else{
        tilegrid->getTile(i, j)->setTexture2DUniform("primaryTexture", "TheBlundon");
    }
}

void TileGame::iterateGameState(){
    if (current_action == FIRE){
        warmTile(mouse_target_i, mouse_target_j);
    }

    if (duration_of_action > duration_unit){
        switch(current_action){
            case FIRE:
            case MAGIC:
                performAction(current_action, mouse_target_i, mouse_target_j);
                break;
            case STOMP:
                performAction(current_action, self_target_i, self_target_j);
                break;
            default:
                break;
        }

        duration_of_action = 0.0f;
    }

    runCooling();

    runMechanisms();
}

void TileGame::warmTile(int i, int j){
    if(i < 0 || j < 0){
        return;
    }

    setupCoolTime(i, j);
}

void TileGame::runCooling(){
    for (unsigned int i = 0 ; i < width; i++){
        for(unsigned int j = 0; j < height ; j++){
            testCooling(i, j);
        }
    }
}

void TileGame::testCooling(unsigned int i, unsigned int j){
    bool cooleable = isCooleable(i,j);

    PLUSH::Entity* tile = tilegrid->getTile(i, j).get();
    PLUSH::EntityStatus* status = tile->getStatusPointer();

    if(cooleable){
        // std::cout << "Cooleable tile found" << std::endl;

        if(currentTime > status->time + status->duration){
            coolTile(i, j);
        }
    }
}

bool TileGame::isCooleable(unsigned int i, unsigned int j){
    return isCooleable((Tile_ID)tilegrid->getTile(i, j)->getStatusPointer()->ID);
}

bool TileGame::isCooleable(Tile_ID id){
    switch(id){
        case LAVA:
        case MOLTEN_TITANITE:
            return true;
        default:
            return false;
    }
}

bool TileGame::isLiquid(unsigned int i, unsigned int j){
    return isLiquid((Tile_ID)tilegrid->getTile(i, j)->getStatusPointer()->ID);
}

bool TileGame::isLiquid(Tile_ID id){
    switch(id){
        case LAVA:
        case MOLTEN_TITANITE:
            return true;
        default:
            return false;
    }
}

// void TileGame::iterateGameState(){
//     unsigned int width = tilegrid->getWidth();
//     unsigned int height = tilegrid->getHeight();

//     unsigned int i = (unsigned int)(width*((float)std::rand())/RAND_MAX);
//     unsigned int j = (unsigned int)(height*((float)std::rand())/RAND_MAX);

//     flipTile(i, j);
// }

void TileGame::performAction(Action_ID action, int i, int j){\
    if(i < 0 || j < 0){
        return;
    }

    switch(action){
        case STOMP:
            stompTile(i, j);
            break;
        
        case FIRE:
            burnTile(i, j);
            break;

        case MAGIC:
            magifyTile(i, j);
            break;
        
        case PICK_UP:
            pickupTile(i,j);
            break;

        default:
            break;
    }

    // flipTile(i, j);
}

void TileGame::processKeys(float frame_time){
    PLUSH_helpers::KeyboardStatus* keyboardstatus = window->getKeyboardStatusPointer();

    float speed = 5.0;

    if(keyboardstatus->keystatus[PLUSH_helpers::KEY_ESCAPE] == PLUSH_helpers::JUST_PRESSED){
        window->Close();
    }

    if(keyboardstatus->keystatus[PLUSH_helpers::KEY_W] == PLUSH_helpers::JUST_PRESSED){
        keyboardstatus->keystatus[PLUSH_helpers::KEY_W] = PLUSH_helpers::PRESSED;
    }
    if(keyboardstatus->keystatus[PLUSH_helpers::KEY_W] == PLUSH_helpers::PRESSED){
        y_pos += speed*frame_time;
    }

    if(keyboardstatus->keystatus[PLUSH_helpers::KEY_S] == PLUSH_helpers::JUST_PRESSED){
        keyboardstatus->keystatus[PLUSH_helpers::KEY_S] = PLUSH_helpers::PRESSED;
    }
    if(keyboardstatus->keystatus[PLUSH_helpers::KEY_S] == PLUSH_helpers::PRESSED){
        y_pos -= speed*frame_time;
    }

    if(keyboardstatus->keystatus[PLUSH_helpers::KEY_D] == PLUSH_helpers::JUST_PRESSED){
        keyboardstatus->keystatus[PLUSH_helpers::KEY_D] = PLUSH_helpers::PRESSED;
    }
    if(keyboardstatus->keystatus[PLUSH_helpers::KEY_D] == PLUSH_helpers::PRESSED){
        x_pos += speed*frame_time;
    }

    if(keyboardstatus->keystatus[PLUSH_helpers::KEY_A] == PLUSH_helpers::JUST_PRESSED){
        keyboardstatus->keystatus[PLUSH_helpers::KEY_A] = PLUSH_helpers::PRESSED;
    }
    if(keyboardstatus->keystatus[PLUSH_helpers::KEY_A] == PLUSH_helpers::PRESSED){
        x_pos -= speed*frame_time;
    }

    if(keyboardstatus->keystatus[PLUSH_helpers::KEY_SPACE] == PLUSH_helpers::JUST_PRESSED){
        keyboardstatus->keystatus[PLUSH_helpers::KEY_SPACE] = PLUSH_helpers::PRESSED;
    }
    if(keyboardstatus->keystatus[PLUSH_helpers::KEY_SPACE] == PLUSH_helpers::PRESSED){
        current_action = STOMP;
    }

    if(keyboardstatus->keystatus[PLUSH_helpers::KEY_E] == PLUSH_helpers::JUST_PRESSED){
        keyboardstatus->keystatus[PLUSH_helpers::KEY_E] = PLUSH_helpers::PRESSED;
        // pickupTile(mouse_target_i, mouse_target_j);
        pickPutTile(mouse_target_i, mouse_target_j);
    }
    if(keyboardstatus->keystatus[PLUSH_helpers::KEY_E] == PLUSH_helpers::PRESSED){
        // current_action = PICK_UP;
    }

    // if(keyboardstatus->keystatus[PLUSH_helpers::KEY_R] == PLUSH_helpers::JUST_PRESSED){
    //     keyboardstatus->keystatus[PLUSH_helpers::KEY_R] = PLUSH_helpers::PRESSED;
    //     putDownTile(mouse_target_i, mouse_target_j);
    // }
    // if(keyboardstatus->keystatus[PLUSH_helpers::KEY_R] == PLUSH_helpers::PRESSED){
    //     // current_action = PICK_UP;
    // }

    if(keyboardstatus->keystatus[PLUSH_helpers::KEY_F] == PLUSH_helpers::JUST_PRESSED){
        keyboardstatus->keystatus[PLUSH_helpers::KEY_F] = PLUSH_helpers::PRESSED;
        reorientTile(mouse_target_i, mouse_target_j);
    }
    if(keyboardstatus->keystatus[PLUSH_helpers::KEY_F] == PLUSH_helpers::PRESSED){
        
    }
    
}

int TileGame::getMouseTileX(){
    double mousex = window->getMouseX();
    double relativeposition = mousex - positionX;
    double tileposition = relativeposition + offsetX;
    double tilecoord = tileposition/tiledimensionsX;

    return (int) tilecoord;
}

int TileGame::getMouseTileY(){
    double mousey = window->getMouseYAspectScaled();
    double relativeposition = mousey - positionY;
    double tileposition = relativeposition + offsetY;
    double tilecoord = tileposition/tiledimensionsY;

    return (int) tilecoord;
}

Tile_ID TileGame::getTileID(int i, int j){
    if(i < 0 || j < 0){
        return EMPTY;
    }

    return (Tile_ID) tilegrid->getTile(i, j)->getStatusPointer()->ID;
}

void TileGame::setTile(Tile_ID new_tile_id, int i, int j, int orientation){
    if(i < 0 || j < 0){
        return;
    }

    PLUSH::Entity* tile = tilegrid->getTile(i, j).get();

    PLUSH::EntityStatus* status_ptr = tile->getStatusPointer();
    status_ptr->ID = new_tile_id;
    status_ptr->orientation = orientation;

    switch(new_tile_id){
        // case MOVER:
        //     tile->setTexture2DUniform("primaryTexture",getTextureNameForTileID(new_tile_id, orientation));
        //     break;
        default:
            tile->setTexture2DUniform("primaryTexture", getTextureNameForTileID(new_tile_id, orientation));
            break;
    }
    setupCoolTime(i, j);

    setupMachine(i, j);

}

PLUSH::EntityStatus* TileGame::getTileStatusPointer(unsigned int i, unsigned int j){


    return tilegrid->getTile(i, j)->getStatusPointer();
}

std::string TileGame::getSuffixForOrientation(int orientation){
    switch(orientation){
        case -1:
            return "";
        case 0:
            return "_Down";
        case 1:
            return "_Right";
        case 2:
            return "_Up";
        case 3:
            return "_Left";
    }
}

bool TileGame::setupMachine(int i, int j){
    if(i < 0 || j < 0){
        return false;
    }

    PLUSH::EntityStatus* status_ptr = tilegrid->getTile(i, j)->getStatusPointer();

    switch(status_ptr->ID){
        case HEATER:
            status_ptr->time = currentTime;
            status_ptr->duration = 1.0f;
            return true;
        case MOVER:
        case HEATERMOVER:
            status_ptr->time = currentTime;
            status_ptr->mode = 0;
            status_ptr->duration = 1.0f;
            status_ptr->duration2 = 2.0f;
            return true;
            
        default:
            return false;
    }
}

bool TileGame::setupCoolTime(int i, int j){
    if(i < 0 || j < 0){
        return false;
    }

    PLUSH::EntityStatus* status_ptr = tilegrid->getTile(i, j)->getStatusPointer();

    switch(status_ptr->ID){
        case MOLTEN_TITANITE:
            status_ptr->time = currentTime;
            status_ptr->duration = 2.0f;
            return true;
        case LAVA:
            status_ptr->time = currentTime;
            status_ptr->duration = 3.0f;
            return true;
        default:
            return false;
    }
}

std::string TileGame::getTextureNameForTileID(Tile_ID tile_id, int orientation){
    switch (tile_id) {
        case AWESOME:
            return "AwesomeFace";
        case FOREST:
            return "ForestTile";
        case FOLIAGE:
            return "FoliageTile";
        case EARTH:
            return "EarthTile";
        case ASH:
            return "AshTile";
        case PACKED_ASH:
            return "PackedAshTile";
        case STONE:
            return "StoneTile";
        case GLASS:
            return "GlassTile";
        case STONEGLASS:
            return "StoneglassTile";
        case SPAWN_CRYSTAL:
            return "SpawnCrystalTile";
        case TITANITE:
            return "TitaniteTile";
        case MOLTEN_TITANITE:
            return "MoltenTitaniteTile";
        case CRYSTAL:
            return "CrystalTile";
        case AMBER:
            return "AmberTile";
        case GEMS:
            return "GemsTile";
        case RESIDUE:
            return "ResidueTile";
        case COALCHROME:
            return "CoalchromeTile";
        case REINFORCED_SPAWN_CRYSTAL:
            return "ReinforcedSpawnCrystalTile";
        case DRAGONSTEEL:
            return "DragonsteelTile";
        case LAVA:
            return "LavaTile";
        case OBSIDIAN:
            return "ObsidianTile";
        case HEATER:
            return "HeaterTile"+getSuffixForOrientation(orientation);
        case HEATER_MATERIAL:
            return "HeaterMaterialTile";
        case MOVER_MATERIAL:
            return "MoverMaterialTile";
        case MOVER:
            return "MoverTile"+getSuffixForOrientation(orientation);
        case HEATERMOVER_MATERIAL:
            return "HeaterMoverMaterialTile";
        case HEATERMOVER:
            return "HeaterMoverTile"+getSuffixForOrientation(orientation);
        case BLUNDON:
        default:
            return "TheBlundon";
    }

    return "TheBlundon";
}

void TileGame::stompTile(int i, int j){
    if(i < 0 || j < 0){
        return;
    }

    switch((Tile_ID)tilegrid->getTile(i, j)->getStatus().ID){
        case FOREST:
            setTile(FOLIAGE, i, j);
            return;
        case FOLIAGE:
            setTile(EARTH, i, j);
            return;
        case ASH:
            setTile(PACKED_ASH, i, j);
            return;
        default:
            return;
    }
}

void TileGame::burnTile(int i, int j){

    if(i < 0 || j < 0){
        return;
    }

    switch((Tile_ID)tilegrid->getTile(i, j)->getStatus().ID){
        case FOREST:
            setTile(ASH, i, j);
            return;
        case FOLIAGE:
            setTile(ASH, i, j);
            return;
        case ASH:
            setTile(STONE, i, j);
            return;
        case PACKED_ASH:
            setTile(STONEGLASS, i, j);
            return;
        case EARTH:
            setTile(GLASS, i, j);
            return;
        case SPAWN_CRYSTAL:
            transformChain(i, j, SPAWN_CRYSTAL);
            setTile(RESIDUE, i, j);
            return;
        case REINFORCED_SPAWN_CRYSTAL:
            transformChain(i, j, SPAWN_CRYSTAL);
            return;
        case TITANITE:
            setTile(MOLTEN_TITANITE, i, j);
            return;
        case STONE:
            setTile(LAVA, i, j);
            return;
        default:
            return;
    }
}

bool TileGame::isOutOfBounds(int i, int j){
    if (i < 0 || j < 0 || i > width || j > height){
        return true;
    }
    return false;
}

void TileGame::magifyTile(int i, int j){
    if(i < 0 || j < 0){
        return;
    }

    switch((Tile_ID)tilegrid->getTile(i, j)->getStatus().ID){
        case STONEGLASS:
            setTile(SPAWN_CRYSTAL, i, j);
            return;
        case CRYSTAL:
            transformNeighbors(i, j, CRYSTAL);
            return;
        case HEATER_MATERIAL:
            setTile(HEATER, i, j, -1);
            return;
        case MOVER_MATERIAL:
            setTile(MOVER, i, j, -1);
            return;
        case HEATERMOVER_MATERIAL:
            setTile(HEATERMOVER, i, j, -1);
        default:
            return;
    }
}

void TileGame::coolTile(int i, int j){
    if(i < 0 || j < 0){
        return;
    }

    switch((Tile_ID)tilegrid->getTile(i, j)->getStatus().ID){
        case LAVA:
            setTile(OBSIDIAN, i, j);
            return;
        case MOLTEN_TITANITE:
            transformNeighbors(i , j, MOLTEN_TITANITE);
            setTile(EARTH, i, j);
            return;
        default:
            return;
    }
}

void TileGame::transformNeighbors(int i, int j, Tile_ID coatingTile){
    transformTile(i-1, j, coatingTile);
    transformTile(i+1, j, coatingTile);
    transformTile(i, j-1, coatingTile);
    transformTile(i, j+1, coatingTile);
}

void TileGame::transformChain(int i, int j, Tile_ID transformingTile){
    if(transformTile(i-1, j, transformingTile)){
        transformChain(i-1, j, transformingTile);
    }
    if(transformTile(i+1, j, transformingTile)){
        transformChain(i+1, j, transformingTile);
    }
    if(transformTile(i, j-1, transformingTile)){
        transformChain(i, j-1, transformingTile);
    }
    if(transformTile(i, j+1, transformingTile)){
        transformChain(i, j+1, transformingTile);
    }
}

bool TileGame::transformTile(int i, int j, Tile_ID coatingTile){
    if(i < 0 || j < 0){
        return false;
    }

    Tile_ID coatedTile = (Tile_ID)tilegrid->getTile(i, j)->getStatusPointer()->ID;

    switch(coatingTile){
        case MOLTEN_TITANITE:
            switch(coatedTile){
                case FOREST:
                case FOLIAGE:
                    setTile(COALCHROME, i, j);
                    return true;
                case ASH:
                case PACKED_ASH:
                    setTile(DRAGONSTEEL, i, j);
                    return true;
                case SPAWN_CRYSTAL:
                    setTile(REINFORCED_SPAWN_CRYSTAL, i, j);
                    return true;
                default:
                    return false;
            }
        case SPAWN_CRYSTAL:
            switch(coatedTile){
                case GLASS:
                    setTile(CRYSTAL, i, j);
                    return true;
                case STONE:
                    setTile(TITANITE, i, j);
                    return true;
                default:
                    return false;
            }
        case CRYSTAL:
            switch (coatedTile) {
                case FOREST:
                    setTile(AMBER, i, j);
                    return true;
                case FOLIAGE:
                    setTile(GEMS, i, j);
                    return true;
                default:
                    return false;
            }
        default:
            return false;
    }
    
}

bool TileGame::pickupTile(int i, int j){
    if(i < 0 || j < 0){
        return false;
    }

    if(heldTile != EMPTY){
        return false;
    }

    if(isLiquid(i, j)){
        return false;
    }

    PLUSH::EntityStatus* status = tilegrid->getTile(i, j)->getStatusPointer();

    setHeldTile((Tile_ID)status->ID, status->orientation);
    setTile(EARTH, i, j);
    
    return true;
}

void TileGame::pickPutTile(int i, int j){
    if (heldTile == EMPTY){
        pickupTile(i, j);
    } else {
        putDownTile(i, j);
    }
}

void TileGame::reorientTile(int i, int j){
    if(i < 0 || j < 0){
        return;
    }

    int newOrientation = (tilegrid->getTile(i, j)->getStatusPointer()->orientation + 2) % 5 - 1;
    setTile(getTileID(i, j), i, j, newOrientation);
}

void TileGame::reorientHeldTile(){
    int newOrientation = (heldTileStatus->orientation + 2) % 5 - 1;
    setHeldTile(heldTile, newOrientation);
}

void TileGame::setHeldTile(Tile_ID new_tile_id, int orientation){
    heldTile = new_tile_id;
    heldTileStatus->visible = true;
    heldTileStatus->ID = heldTile;
    heldTile_ptr->setTexture2DUniform("primaryTexture", getTextureNameForTileID(heldTile, orientation));
    heldTileStatus->orientation = orientation;
}

void TileGame::clearHeldTile(){
    heldTile = EMPTY;
    heldTileStatus->visible = false;
    heldTileStatus->ID = EMPTY;
    heldTile_ptr->setTexture2DUniform("primaryTexture", "TheBlundon");
}

bool TileGame::putDownTile(int i, int j){
    if(i < 0 || j < 0){
        return false;
    }

    if(heldTile == EMPTY){
        return false;
    }

    if(placeCombineTile(i, j, heldTile)){
        clearHeldTile();
        return true;
    } 

    if(placeOverTile(i, j, heldTile, heldTileStatus->orientation)){
        clearHeldTile();
        return true;
    }

    return false;
}

bool TileGame::placeCombineTile(int i, int j, Tile_ID combineTile, int orientation){
    Tile_ID destinationTile = (Tile_ID)tilegrid->getTile(i, j)->getStatusPointer()->ID;

    switch(destinationTile){
        case COALCHROME:
            switch(combineTile){
                case AMBER:
                    setTile(HEATER_MATERIAL, i, j);
                    return true;    
                case GEMS:
                    setTile(MOVER_MATERIAL, i, j);
                    return true;
                default:
                    break;
            }
        case AMBER:
            if(combineTile == COALCHROME){
                setTile(HEATER_MATERIAL, i, j);
                return true;
            }
        case GEMS:
            if(combineTile == COALCHROME){
                setTile(MOVER_MATERIAL, i, j);
                return true;
            }
        case MOVER:
            if(combineTile == HEATER){
                setTile(HEATERMOVER_MATERIAL, i,j);
                return true;
            }
        case HEATER:
            if(combineTile == MOVER){
                setTile(HEATERMOVER_MATERIAL, i, j);
                return true;
            }
        default:
            break;
    }

    return false;
}


bool TileGame::placeOverTile(int i, int j, Tile_ID placeTile, int orientation){

    if(canPlaceOverTile(i, j)){
        setTile(placeTile, i,j, orientation);
        return true;
    }
    return false;
}

bool TileGame::canPlaceOverTile(int i, int j){
    Tile_ID destinationTile = (Tile_ID)tilegrid->getTile(i, j)->getStatusPointer()->ID;

    switch(destinationTile){
        case EARTH:
        case FOLIAGE:
        case FOREST:
        case LAVA:
        case MOLTEN_TITANITE:
            return true;

        default:
            return false;
    }
}

bool TileGame::canBurnMoveTile(int i, int j){
    Tile_ID tile = (Tile_ID)tilegrid->getTile(i, j)->getStatusPointer()->ID;

    switch (tile) {
        case EARTH:
            return false;

        default:
            return true;
    }
}

bool TileGame::setOrientationInts(int orientation, int i, int j, int &source_i, int &source_j, int &dest_i, int &dest_j){
    switch(orientation){
        case 0:
            source_i = i;
            source_j = j+1;

            dest_i = i;
            dest_j = j-1;
            break;
        case 1:
            source_i = i-1;
            source_j = j;

            dest_i = i+1;
            dest_j = j;
            break;
        case 2:
            source_i = i;
            source_j = j-1;

            dest_i = i;
            dest_j = j+1;
            break;
        case 3:
            source_i = i+1;
            source_j = j;

            dest_i = i-1;
            dest_j = j;
            break;
        default:
            break;
    }

    if(isOutOfBounds(source_i, source_j) || isOutOfBounds(dest_i, dest_j)){
        return false;
    }

    return true;
}

void TileGame::runMechanisms(){
    for (unsigned int i = 0 ; i < width ; i++){
        for(unsigned int j = 0; j < height ; j++){
            runMechanism(i, j);
        }
    }
}

void TileGame::runMechanism(unsigned int i, unsigned int j){
    PLUSH::EntityStatus* status = tilegrid->getTile(i, j)->getStatusPointer();
    switch(status->ID){
        case HEATER:{
            int source_i, source_j, dest_i, dest_j = -1;
            if (!setOrientationInts(status->orientation, i, j, source_i, source_j, dest_i, dest_j)){
                return;
            }

            warmTile(dest_i, dest_j);
            if (currentTime > status->time+status->duration){
                burnTile(dest_i, dest_j);
                status->time = currentTime;
            }
            return;}

        case HEATERMOVER:{
            if (status->mode == 2){
                if(currentTime > status->time + status->duration2){
                    status->time = currentTime;
                    status->mode = 0;
                }
                else{
                    return;
                }
            }

            int source_i, source_j, dest_i, dest_j = -1;
            if (!setOrientationInts(status->orientation, i, j, source_i, source_j, dest_i, dest_j)){
                return;
            }

            if(!canBurnMoveTile(source_i, source_j)){
                status->mode = 0;
            }else{

                if(status->mode == 0){
                    status->time = currentTime;
                }
                status->mode = 1;
                if(currentTime > status->time + status->duration){
                    if(canPlaceOverTile(dest_i, dest_j)){
                        placeOverTile(dest_i, dest_j, getTileID(source_i, source_j));
                        setTile(EARTH, source_i, source_j);
                        burnTile(dest_i, dest_j);
                        status->mode = 2;
                        status->time = currentTime;
                    }
                }
            }
            return;
        }

        case MOVER:{
            if (status->mode == 2){
                if(currentTime > status->time + status->duration2){
                    status->time = currentTime;
                    status->mode = 0;
                }
                else{
                    return;
                }
            }

            int source_i, source_j, dest_i, dest_j = -1;
            if (!setOrientationInts(status->orientation, i, j, source_i, source_j, dest_i, dest_j)){
                return;
            }

            if(getTileID(source_i, source_j)==EARTH){
                status->mode = 0;
            }else{

                if(status->mode == 0){
                    status->time = currentTime;
                }
                status->mode = 1;
                if(currentTime > status->time + status->duration){
                    if(canPlaceOverTile(dest_i, dest_j)){
                        placeOverTile(dest_i, dest_j, getTileID(source_i, source_j));
                        setTile(EARTH, source_i, source_j);
                        status->mode = 2;
                        status->time = currentTime;
                    }
                }
            }
            return;
        }

    }
}

void TileGame::burnNeighbors(int i, int j){
    burnTile(i + 1, j);
    burnTile(i - 1, j);
    burnTile(i, j + 1);
    burnTile(i, j - 1);
}

void TileGame::warmNeighbors(int i, int j){
    warmTile(i + 1, j);
    warmTile(i - 1, j);
    warmTile(i, j + 1);
    warmTile(i, j - 1);
}