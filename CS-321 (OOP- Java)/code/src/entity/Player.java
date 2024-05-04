package entity;

import game_2d_resourceslayer.GamePanel;
import game_2d_resourceslayer.KL;
import java.awt.Graphics2D;
import java.awt.image.BufferedImage;
import java.io.IOException;
import javax.imageio.ImageIO;
import world.WorldTile;


public class Player extends Entity {
    
    GamePanel gp;
    KL keyH;
    CollisionBox bounds;
    
    public int money = 0;
    
    
    public Player(GamePanel gp, KL keyH){
        
        this.gp = gp;
        this.keyH = keyH;
        bounds = new CollisionBox(x, y, gp.tileSize, gp.tileSize);
        
        setDefaultValues();
        getPlayerImage();
    }
    
    public void setDefaultValues(){
        
        x = 360;
        y = 260;
        speed = 4;
        direction = "down";
    }
    
    public void getPlayerImage(){
        
        try{
            
            up1 = ImageIO.read(getClass().getResourceAsStream("/player/player_up1.png"));
            up2 = ImageIO.read(getClass().getResourceAsStream("/player/player_up2.png"));
            
            down1 = ImageIO.read(getClass().getResourceAsStream("/player/player_down1.png"));
            down2 = ImageIO.read(getClass().getResourceAsStream("/player/player_down2.png"));
            
            left1 = ImageIO.read(getClass().getResourceAsStream("/player/player_left1.png"));
            left2 = ImageIO.read(getClass().getResourceAsStream("/player/player_left2.png"));
            
            right1 = ImageIO.read(getClass().getResourceAsStream("/player/player_right1.png"));
            right2 = ImageIO.read(getClass().getResourceAsStream("/player/player_right2.png"));
            
            
        }catch(IOException e){
            e.printStackTrace();
        }
        
        
    }
    
    public void update(){ //this method gets called 60 times per second (60 FPS)
        
        if(keyH.upPressed == true || keyH.downPressed == true || keyH.leftPressed == true || keyH.rightPressed == true){
                                
            if(keyH.upPressed == true){
                direction = "up";
                if (!CheckCollision(0, -1)) y -= speed;
            }
            else if(keyH.downPressed == true){
               direction = "down";
               if (!CheckCollision(0, 1)) y += speed;
            }
            else if(keyH.leftPressed == true){
                direction = "left";
                if (!CheckCollision(-1, 0)) x -= speed;
            }
            else if(keyH.rightPressed == true){
                direction = "right";
                if (!CheckCollision(1, 0)) x += speed;
            }
            
        
            spriteCounter++;    //every time this method gets called, increases this counter by 1 = player image changes every 14 frame
       
            if(spriteCounter > 14){
                if(spriteNum == 1){
                    spriteNum = 2;
                }
                else if(spriteNum == 2){
                    spriteNum = 1;
                }
                spriteCounter = 0;
            }
        }
        
        if (keyH.actionPressed == true) {
                int TileX = x/gp.tileSize;
                int TileY = y/gp.tileSize;
                WorldTile tile;
                
                switch(direction) {
                    case "up":
                        TileY--;
                    case "down":
                        TileY++;
                    case "left":
                        TileX--;
                    case "right":
                        TileX++;
                }
                
                tile = gp.tile_M.world.getTile(TileX, TileY);
                if (tile.plant != null) {
                    if (tile.plant.harvest()) money += tile.plant.sellValue;
                } else {
                    gp.tile_M.addPlant(TileX, TileY);
                }
            }

    }
    
    public void draw(Graphics2D g2){
        
        
        BufferedImage image = null;
        
        switch(direction){
            case "up":
                if(spriteNum == 1){
                    image = up1;
                }
                if(spriteNum == 2){
                    image = up2;
                }
                break;
                
            case "down":
                if(spriteNum == 1){
                    image = down1;
                }
                if(spriteNum == 2){
                    image = down2;
                }
                break;
                
            case "left":
                if(spriteNum == 1){
                    image = left1;
                }
                if(spriteNum == 2){
                    image = left2;
                }
                break;
                
            case "right":
                if(spriteNum == 1){
                    image = right1;
                }
                if(spriteNum == 2){
                    image = right2;
                }
                break;
                
        }
        g2.drawImage(image, x, y, gp.tileSize, gp.tileSize, null);      //image observer
    }

    public boolean CheckCollision(int dx, int dy) {
        int tileX = (x/gp.tileSize);
        int tileY = (y/gp.tileSize);
        WorldTile tile = gp.tile_M.world.getTile(tileX + dx, tileY + dy);
        WorldTile tileAdjacent; 
        tileAdjacent = gp.tile_M.world.getTile(tileX + dx, tileY + 1);
        if (dy != 0) tileAdjacent = gp.tile_M.world.getTile(tileX + 1, tileY + dy);

        boolean forwardCollision = false;
        boolean adjacentCollision = false;
        
        if(tile.gethasCollision() || tileAdjacent.gethasCollision()) {
            this.bounds.setX(x + dx*speed);
            this.bounds.setY(y + dy*speed);
            if (tileAdjacent.gethasCollision()) adjacentCollision =  this.bounds.intersects(tileAdjacent.bounds);
            if (tile.gethasCollision()) forwardCollision =  this.bounds.intersects(tile.bounds);
            return forwardCollision || adjacentCollision;
        }
        return false;
    }
}
