#include <memory>

#include "Example_Tile_ID.h"
#include "EntityStatus.h"

namespace PLUSH {
    class TileGridLayer;
    class TileGrid;
    class WindowHandler;
    class Entity;
}

class TileGame{
    public:
        TileGame();

        void run();
    
    // private:
        int getMouseTileX();
        int getMouseTileY();

        void prepareBoard();

        void setTileGridDimensions();
        void setTileGridOffset();
        void snapAvatarPosition();

        void flipTile(unsigned int i, unsigned int j);
        
        void iterateGameState();

        void processKeys(float frame_time = 0.0);
        void processMouse(float frame_time = 0.0);

        void processInputs(float frame_time = 0.0);

        void performAction(Action_ID action, int i = -1, int j = -1);

        Tile_ID getTileID(int i, int j);
        PLUSH::EntityStatus* getTileStatusPointer(unsigned int i,unsigned  int j);

        bool isOutOfBounds(int i, int j);

        void burnTile(int i = -1, int j = -1);
        void magifyTile(int i = -1, int j = -1);
        void stompTile(int i = -1, int j = -1);

        void reorientTile(int i = -1, int j = -1);
        void reorientHeldTile();

        bool pickupTile(int i = -1, int j = -1);
        bool putDownTile(int i = -1, int j = -1);
        void pickPutTile(int i = -1, int j = -1);

        bool setupCoolTime(int i, int j);
        bool setupMachine(int i, int j);

        void warmTile(int i = -1, int j = -1);
        void coolTile(int i = -1, int j = -1);

        void burnNeighbors(int i, int j);
        void warmNeighbors(int i, int j);

        void transformNeighbors(int i, int j, Tile_ID coatingTile);
        void transformChain(int i, int j, Tile_ID transformingTile);
        bool transformTile(int i, int j, Tile_ID coatingTile);

        bool placeCombineTile(int i, int j, Tile_ID combineTile, int orientation = -1);
        bool placeOverTile(int i, int j, Tile_ID placeTile, int orientation = -1);

        bool canPlaceOverTile(int i, int j);
        bool canBurnMoveTile(int i, int j);

        bool isCooleable(unsigned int i, unsigned int j);
        bool isCooleable(Tile_ID id);

        bool isLiquid(unsigned int i, unsigned int j);
        bool isLiquid(Tile_ID id);

        void runCooling();
        void testCooling(unsigned int i, unsigned int j);

        void runMechanisms();
        void runMechanism(unsigned int i, unsigned int j);

        float currentTime = 0.0;

        void setTile(Tile_ID new_tile_id, int i = -1, int j = -1, int orientation = -1);

        void setHeldTile(Tile_ID new_tile_id, int orientation = -1);
        void clearHeldTile();

        bool setOrientationInts(int orientation, int i, int j, int& source_i, int& source_j, int& dest_i, int& dest_j);

        Tile_ID heldTile = EMPTY;
        std::shared_ptr<PLUSH::Entity> heldTile_ptr;
        PLUSH::EntityStatus* heldTileStatus;

        std::string getTextureNameForTileID(Tile_ID tile_id, int orientation = -1);
        std::string getSuffixForOrientation(int orientation);

        float aspectratio;
        float invaspectratio;
        float tilegriddimensionsX;
        float tilegriddimensionsY;
        float tiledimensionsX;
        float tiledimensionsY;
        float positionX;
        float positionY;
        float offsetX;
        float offsetY;

        float movementBoundaryRatioX;
        float movementBoundaryRatioY;

        unsigned int width;
        unsigned int height;

        float x_pos = 0.0;
        float y_pos = 0.0;

        int mouse_target_i, mouse_target_j;
        bool mouse_target_changed = false;

        int self_target_i, self_target_j;
        bool self_target_changed = false;

        float duration_of_action = 0.0; 

        Action_ID current_action = NO_ACTION;
        Action_ID previous_action = NO_ACTION;

        float duration_unit = 0.8f;

        std::shared_ptr<PLUSH::WindowHandler> window;
        std::shared_ptr<PLUSH::TileGridLayer> tilegridlayer;
        std::shared_ptr<PLUSH::TileGrid> tilegrid;

};