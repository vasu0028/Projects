
package world;

import java.util.ArrayList;
import tile.TileManager;
import entity.CollisionBox;


/**
 *
 * @author Emmi Phillips
 */

public class World {
    
    public WorldTile[][] tileMap;
    private TileManager tm;
    private final int[] collisionTiles = {0, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};

    public World (TileManager tm) {
        this.tm = tm;
        tileMap = new WorldTile[20][12];
        buildWorld(tm.mapTileNum);
    }
    
    public void addTile(int x, int y, int id) {
        WorldTile tile = new WorldTile(x*48, y*48);
        tileMap[x][y] = tile;
        
        boolean collision = false;
        
        for (int i: collisionTiles) {
            if (!collision) collision = (i == id);
        }
        
        if(id == 20) tile.setPlantable(true);
        if(collision) tile.setCollision(true, new CollisionBox(x * 48, y * 48, 48, 48));

    };

    public WorldTile getTile(int x, int y){
        return tileMap[x][y];
    }
    
    public void delTile(){
        //implement eventually
    };

    public void buildWorld(int[][] tileMap) {
        for(int x = 0; x < tileMap.length; x++) {
            for(int y = 0; y < tileMap[x].length; y++) {
                addTile(x, y, tileMap[x][y]);
            }
  
        }
    }
    
    
}
