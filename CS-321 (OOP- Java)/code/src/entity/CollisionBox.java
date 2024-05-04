/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package entity;

/**
 *
 * @author colin
 */
public class CollisionBox {
    protected int x;
    protected int y; 
    protected int width;
    protected int height;

    public boolean intersects(CollisionBox box) {
        return(x < box.x + box.width &&
        x + width > box.x &&
        y < box.y + box.height &&
        y + height > box.y);
    }

    public CollisionBox (int x, int y, int width, int height){
        this.x = x;
        this.y = y;
        this.height = height;
        this.width = width;
    }

    public void setX(int x) {
        this.x = x;
    }

    public void setY(int y){
        this.y = y;
    }
}
