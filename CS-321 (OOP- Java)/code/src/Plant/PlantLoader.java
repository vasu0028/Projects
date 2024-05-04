/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package Plant;

import PlantDataClasses.PlantData;
import java.io.FileReader;
import java.io.File;
import java.util.Collection;
import java.util.HashMap;
import javax.xml.bind.JAXBContext;

/**
 *
 * @author Admin
 */
public class PlantLoader {
    private final File filePath;
    private final HashMap<String, PlantData>  loadedData = new HashMap();
    
    public PlantLoader() {
        filePath = new File("plants");
    }
    
    public void ImportPlants() {
        File[] plantFiles = filePath.listFiles();
        System.out.println(filePath.getAbsoluteFile());
        for(File plantFile: plantFiles) {
            PlantData data = loadPlant(plantFile.getPath());
            loadedData.put(data.getName(), data);
        }
    } 
    
    public PlantData getPlant(String plant) {
        return loadedData.get(plant);
    }
    
    public PlantData[] plantList() {
        Collection dataCollection = loadedData.values();
        return (PlantData[]) dataCollection.toArray(PlantData[]::new);
    }
    
    private PlantData loadPlant(String path) {
        try {
            JAXBContext context = JAXBContext.newInstance(PlantData.class);
            return (PlantData) context.createUnmarshaller().unmarshal(new FileReader(path));
        } catch(Exception e) {
            System.err.println(e);
            System.exit(0);
            return null;
        }
    }
}
