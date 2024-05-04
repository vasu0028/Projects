package game_2d_resourceslayer;

import Plant.PlantManager;
import entity.Player;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.Font;
import java.awt.Graphics;
import java.awt.Graphics2D;
import javax.swing.JPanel;
import tile.TileManager;


public class GamePanel extends JPanel implements Runnable {
    
    //Screen settings
    final int originalTileSize = 16;    //16x16 tile
    final int scale = 3;                //16x3 = 48 (we create 16x16 character by itll loook 48x48 on the screen
    
    public final int tileSize = originalTileSize * scale;    //48x48 tile 
    public final int maxScreenCol = 20; //20 tiles vertically
    public final int maxScreenRow = 12; //12 tiles horizontally
    public final int screenWidth = tileSize * maxScreenCol;        //960 pixels (16*3*16) 
    public final int screenHeight = tileSize * maxScreenRow;       //576 pixels (12*3*16)
    
    // FPS 
    int FPS = 60;
    
    public TileManager tile_M = new TileManager(this);
    public PlantManager plant_M = new PlantManager(this);
    KL keyH = new KL();
    Thread gameThread;
    Player player = new Player(this, keyH);    

    
    
    
    public GamePanel(){
        
        this.setPreferredSize(new Dimension(screenWidth, screenHeight));
        this.setBackground(Color.black);
        this.setDoubleBuffered(true);
        this.addKeyListener(keyH);
        this.setFocusable(true);
    }
    
    public void startGameThread(){
        
        gameThread = new Thread(this);
        gameThread.start();
        
    }

    @Override
    public void run() {
        
        double drawInterval = 1000000000/FPS; //0.1666 second
        double delta = 0;
        long lastTime = System.nanoTime();
        long currentTime;
        long timer = 0;
        int drawCount = 0;

        
        while(gameThread != null){
            
            currentTime = System.nanoTime();
            
            delta += (currentTime - lastTime) / drawInterval;
            timer += (currentTime - lastTime);
            lastTime = currentTime;
            
            if(delta >= 1){
                
                //Update: update information (such as character position)
                update();
                //Draw: draw the screen with the updated information
                repaint();
                
                delta--;
                drawCount ++;
            }
            
            if(timer >= 1000000000){
                System.out.println("FPS: " + drawCount);
                drawCount = 0;
                timer = 0;
            }
        }

    }
    
    public void update(){
     
        player.update();
        plant_M.update();
        
    }
    
    
    public void paintComponent(Graphics g){
        
        super.paintComponent(g);
        
        Graphics2D g2 = (Graphics2D)g;
       
        tile_M.draw(g2); //draw tiles first, then player 
        plant_M.draw(g2);
        player.draw(g2);

        g2.setFont(new Font("Minecraft", Font.BOLD, 48));
        g2.setColor(Color.YELLOW);
        
        g2.drawString("$" + player.money, 48, 96);

        g2.dispose();
        
    }
}
