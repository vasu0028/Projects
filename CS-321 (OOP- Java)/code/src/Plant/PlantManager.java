/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package Plant;

import PlantDataClasses.PlantData;
import game_2d_resourceslayer.GamePanel;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.util.ArrayList;
import java.util.HashMap;

/**
 *
 * @author Admin
 */
public class PlantManager {
    private final HashMap<String, Plant> plantPrototypes = new HashMap();
    public final ArrayList<Plant> plants = new ArrayList();
    
    public final PlantLoader loader = new PlantLoader();
    private final GamePanel gp;
    
    public PlantManager(GamePanel gp) {
        this.gp = gp;
        loader.ImportPlants();
        loadPlants();
    }
    
    public void update() {
        for(Plant plant: plants) {
            plant.update();
        }
    }
    
    public void loadPlants() {
        for(PlantData plant: loader.plantList()) createPlant(plant);
    }
    
    public void createPlant(PlantData data) {
        Plant plant = Plant.createFromData(data, this);
        plantPrototypes.put(plant.getName(), plant);
    }
    
    public Plant addPlant(String name) {
        Plant plant = plantPrototypes.get(name).clone();
        plants.add(plant);
        return plant;
    }
    
   public void draw(Graphics g) {
       Graphics2D g2 = (Graphics2D)g;
       //System.out.println(plants.size());
       for(Plant plant: plants) plant.draw(g2);
   }
    
    public void destroyPlant(Plant plant) {
        plants.remove(plant);
    }
}
