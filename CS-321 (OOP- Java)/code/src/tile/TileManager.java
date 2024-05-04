package tile;


import game_2d_resourceslayer.GamePanel;
import world.World;
import java.awt.Graphics2D;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import javax.imageio.ImageIO;
import world.WorldTile;


public class TileManager {
    
    GamePanel gp;
    Tile[] tile;
    public int mapTileNum [][];
    public World world;
    
    
    public TileManager(GamePanel gp){
        
        this.gp = gp;
        
        tile = new Tile[50]; //create # kinds of tiles (oragnzied it in an array)
        mapTileNum = new int[gp.maxScreenCol][gp.maxScreenRow];
        
        getTileImage();
        loadMap();
        world = new World(this);
    }
    
    public void getTileImage(){
        
        try{

            tile[0] = new Tile ();
            tile[0].image = ImageIO.read(getClass().getResourceAsStream("/tiles/left_bottom_edge_corner.png")); 
            
            tile[1] = new Tile ();
            tile[1].image = ImageIO.read(getClass().getResourceAsStream("/tiles/grass_middle.png"));
           
            tile[2] = new Tile ();
            tile[2].image = ImageIO.read(getClass().getResourceAsStream("/tiles/water.png"));
            
            tile[3] = new Tile ();
            tile[3].image = ImageIO.read(getClass().getResourceAsStream("/tiles/bottom_clift_edge.png"));
            
            tile[4] = new Tile ();
            tile[4].image = ImageIO.read(getClass().getResourceAsStream("/tiles/top_clift_edge.jpg"));
            
            tile[5] = new Tile ();
            tile[5].image = ImageIO.read(getClass().getResourceAsStream("/tiles/left_clift_edge.png"));
            
            tile[6] = new Tile ();
            tile[6].image = ImageIO.read(getClass().getResourceAsStream("/tiles/right_clift_edge.png"));
            
            tile[7] = new Tile ();
            tile[7].image = ImageIO.read(getClass().getResourceAsStream("/tiles/right_bottom_edge_corner.png"));
            
            tile[8] = new Tile ();
            tile[8].image = ImageIO.read(getClass().getResourceAsStream("/tiles/left_top_edge_corner.png"));
            
            tile[9] = new Tile ();
            tile[9].image = ImageIO.read(getClass().getResourceAsStream("/tiles/left_top_connecting_corner.png"));
            
            tile[10] = new Tile ();
            tile[10].image = ImageIO.read(getClass().getResourceAsStream("/tiles/inner_corner.png"));
            
            tile[11] = new Tile ();
            tile[11].image = ImageIO.read(getClass().getResourceAsStream("/tiles/right_connecting_corner.png"));   

            tile[12] = new Tile ();
            tile[12].image = ImageIO.read(getClass().getResourceAsStream("/tiles/inner_corner_top_left.png"));  
            
            tile[13] = new Tile ();
            tile[13].image = ImageIO.read(getClass().getResourceAsStream("/tiles/inner_corner_right.png"));  

            tile[14] = new Tile ();
            tile[14].image = ImageIO.read(getClass().getResourceAsStream("/tiles/water_text_2.png"));  
            
            tile[15] = new Tile ();
            tile[15].image = ImageIO.read(getClass().getResourceAsStream("/tiles/water_text_1.png"));  
            
            tile[16] = new Tile ();
            tile[16].image = ImageIO.read(getClass().getResourceAsStream("/tiles/water_text_3.png"));              

            tile[17] = new Tile ();
            tile[17].image = ImageIO.read(getClass().getResourceAsStream("/tiles/farm_left_top_corner_edge.png"));                

            tile[18] = new Tile ();
            tile[18].image = ImageIO.read(getClass().getResourceAsStream("/tiles/farm_middle_top_edge.png"));    

            tile[19] = new Tile ();
            tile[19].image = ImageIO.read(getClass().getResourceAsStream("/tiles/farm_right_top_corner_edge.png"));
            
            tile[20] = new Tile ();
            tile[20].image = ImageIO.read(getClass().getResourceAsStream("/tiles/Path_Middle.png"));  
            
            tile[21] = new Tile ();
            tile[21].image = ImageIO.read(getClass().getResourceAsStream("/tiles/farm_left_bottom_corner_edge.png"));  

            tile[22] = new Tile ();
            tile[22].image = ImageIO.read(getClass().getResourceAsStream("/tiles/farm_middle_bottom_edge.png"));  
            
            tile[23] = new Tile ();
            tile[23].image = ImageIO.read(getClass().getResourceAsStream("/tiles/farm_right_bottom_corner_edge.png")); 

            tile[24] = new Tile ();
            tile[24].image = ImageIO.read(getClass().getResourceAsStream("/tiles/farm_left_edge.png"));  

            tile[25] = new Tile ();
            tile[25].image = ImageIO.read(getClass().getResourceAsStream("/tiles/farm_right_edge.png")); 
            

            
        }catch(IOException e){
            e.printStackTrace();
        }
    }
    
    public void loadMap(){
        
        try{
            
            InputStream is = getClass().getResourceAsStream("/tile_maps/map.txt"); //import in the map.txt file
            BufferedReader br = new BufferedReader(new InputStreamReader(is)); //read the content of the txt file
            
            int col = 0;
            int row = 0;
            
            while (col < gp.maxScreenCol && row < gp.maxScreenRow){
                
                String line = br.readLine(); //read in a line of text 
                
                while(col < gp.maxScreenCol){
                    String coordinates[] = line.split(" "); //assigns the number retrieve from the single string into an array
                    
                    int num = Integer.parseInt(coordinates[col]); //using col as an index; change string to integer
                    
                    mapTileNum[col][row] = num;
                    col++;
                }
                if (col == gp.maxScreenCol){
                    col = 0;
                    row++;
                }
            }
            br.close(); 
            
        }catch(Exception e){
            
        }
        
    }
    
    public void addPlant(int x, int y) {
        WorldTile tile = world.getTile(x, y);
        if (tile.getisPlantable()) {
            tile.setPlant(gp.plant_M.addPlant("Corn"));
        }
    } 
    
    public void draw(Graphics2D g2){
        
       int col = 0;
       int row = 0;
       int x = 0;
       int y = 0;
       
       while(col < gp.maxScreenCol && row < gp.maxScreenRow){
           
           int tileNum = mapTileNum[col][row]; //tileNum is now used as an index to access what type of tile image to use
           
           g2.drawImage(tile[tileNum].image, x, y, gp.tileSize, gp.tileSize, null);
           
           col++;
           x += gp.tileSize;
           
           if(col == gp.maxScreenCol){
               col = 0;
               x = 0;
               row++;
               y += gp.tileSize;
           } 
    }
       
    }
}



