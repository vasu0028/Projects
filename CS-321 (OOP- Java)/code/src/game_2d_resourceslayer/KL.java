/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package game_2d_resourceslayer;

import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;


public class KL implements KeyListener {

   public boolean upPressed, downPressed, leftPressed, rightPressed, actionPressed;

    @Override
    public void keyTyped(KeyEvent e) {    
    }

    @Override
    public void keyPressed(KeyEvent e) {
        
        int code = e.getKeyCode(); //returns the number of the key that was pressed
        
        if (code == KeyEvent.VK_W ){
            upPressed = true;
        }
        if (code == KeyEvent.VK_S ){
            downPressed = true;
        }
        if (code == KeyEvent.VK_A ){
            leftPressed = true;
        }
        if (code == KeyEvent.VK_D ){
            rightPressed = true;
        } 
        if (code == KeyEvent.VK_SPACE) {
            actionPressed = true;
        }
        
    }

    @Override
    public void keyReleased(KeyEvent e) {
        
        int code = e.getKeyCode();
        
        if (code == KeyEvent.VK_W ){
            upPressed = false;
        }
        if (code == KeyEvent.VK_S ){
            downPressed = false;
        }
        if (code == KeyEvent.VK_A ){
            leftPressed = false;
        }
        if (code == KeyEvent.VK_D ){
            rightPressed = false;
        }
        if (code == KeyEvent.VK_SPACE) {
            actionPressed = false;
        }
        
    }
    
}
