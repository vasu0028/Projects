/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package Plant;

import PlantDataClasses.PlantData;
import java.awt.Graphics2D;
import java.awt.image.BufferedImage;
import java.io.File;
import java.util.ArrayList;
import javax.imageio.ImageIO;

/**
 *
 * @author Admin
 */
public class Plant implements Cloneable {
    private String name;
    private ArrayList<BufferedImage> growthStages = new ArrayList<>();
    private int xp; 
    private int growthTime;
    private int timeTillNextStage;
    private int currentStage = 0;
    private boolean isDestroyed;
    private int fallbackStage = 0;
    private boolean isHarvestable;
    private int produces;
    public int sellValue;
    private int x;
    private int y;
    private final PlantManager pm;
    
    public Plant(PlantManager pm) {
        this.pm = pm;
    }
    
    public static Plant createFromData(PlantData data, PlantManager pm) {
        Plant plant = new Plant(pm);
        for(String imagePath: data.getGrowthStages().getSprite()) {
            try {
                File file = new File(imagePath); 
                System.out.println(file.getAbsolutePath());
                BufferedImage image = ImageIO.read(file);
                plant.growthStages.add(image);
            } catch(Exception e) {
                System.err.println(e);
            }
        }
        plant.sellValue = data.getHarvest().getCropValue();
        plant.name = data.getName();
        plant.growthTime = (data.getGrowthTime()/plant.growthStages.size())*60;
        plant.produces = data.getHarvest().getAmount();
        plant.fallbackStage = data.getHarvest().getFallBackStage(); 
        plant.isDestroyed = data.getHarvest().isIsDestroyed();
        plant.timeTillNextStage = plant.growthTime;
        return plant;
    } 
    
    @Override
    public Plant clone() {
        try {
            return (Plant) super.clone();
        } catch(CloneNotSupportedException e) {
            System.err.println(e);
        }
        return null;
    }
    
    public String getName() {
        return name;
    }
    
    protected void update() {
        if (isHarvestable == false) {
            timeTillNextStage--;
            if (timeTillNextStage <= 0) {
                currentStage++;
                timeTillNextStage = growthTime;
                if (currentStage == growthStages.size() - 1) {
                    isHarvestable = true;
                }
            }
        }
    }
    
    public boolean harvest() {
        if (isHarvestable) {
            if (!isDestroyed) {
                currentStage = fallbackStage - 1;
                isHarvestable = false;
            } else {
                destroy();
            }
            return true;
        }
        return false;
    }
    
    public void destroy() {
        pm.destroyPlant(this);
    }
    
    public void setPosition(int x, int y) {
        this.x = x;
        this.y = y;
    }

    public void draw(Graphics2D g2) {
        g2.drawImage(growthStages.get(currentStage), x, y, 48, 48, null); 
    }
}
