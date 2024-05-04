
package world;

// Import GameMaster and plant
import Plant.Plant;
import entity.CollisionBox;

/**
 *
 * @author Emmi Phillips
 */
public class WorldTile {

    private boolean isPlantable;
    private boolean hasCollision;
    public Plant plant;
    public CollisionBox bounds;
    
    private final int x;
    private final int y;
    
    public WorldTile(int x, int y) {
        this.x = x;
        this.y = y;
    }
    
    public void setCollision(boolean value, CollisionBox bounds){
        hasCollision = value;
        this.bounds = bounds;
    }
    
    public void setPlantable(boolean value) {
        isPlantable = value;
    }
    
    public void setPlant(Plant plant) {
        if (this.plant==null) {
            plant.setPosition(x, y);
            this.plant = plant;
        }
    }
    
    public boolean getisPlantable() {
       if (plant != null) return false;
       return isPlantable;
        
    }
    
    public boolean gethasCollision(){
        return hasCollision;
    }
    
}

