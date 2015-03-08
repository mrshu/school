
package pkg3dobjectviewer;

import java.awt.Color;
import java.util.ArrayList;
import java.util.HashMap;


public class Data {
    boolean isrendered;
    boolean hides;
    int points;
    int planes;
    Matrix light;
    boolean elight; // exist light    
    Color cl;
    HashMap<Integer, Point> body;
    ArrayList<ArrayList<Integer>> plochy;
    ArrayList<Color> shades; 
    
    Data(){
        isrendered = false;
        hides = false;
        cl = new Color(255,255,255);
        elight =false;
        light = new Matrix(0,0,0);
        points=0;
        planes= 0;
        body = new HashMap<Integer, Point>();
        plochy = new ArrayList<ArrayList<Integer>>();
        shades = new ArrayList<Color>();
    }
    
    public void addPoint(Point in){
        points++;               //body cislovane od jedna !
        body.put(points, in);
    }
    
    public void createPlane(ArrayList list){
        plochy.add(list);
        planes++;
        shades.add(cl);
    }
    
    public Point getPoints(int key){
        return body.get(key);
    }
    
    public ArrayList<Integer> getPlane(int i){
        return plochy.get(i);
    }
    
    public int numofPoints() { return this.points;}
    
    public int numofPlanes() {return this.planes;}
    
    public void setlight(Matrix toset){  
        elight = true;
        light = toset;
    }
    
    /**Reevaluates data in matrices. first argument 1 -> X, 2 -> Y, 3 -> Z, 
     **/
    public void Rotate(int which, double angle){
        Matrix rotating = new Matrix();
        if(which == 1){ 
                rotating = new Matrix();
                rotating.setsomething(0, 0, 1);
                rotating.setsomething(1, 1,(float) Math.cos(angle));
                rotating.setsomething(1, 2, (float) Math.sin(angle));
                rotating.setsomething(2, 1,(float) -Math.sin(angle));
                rotating.setsomething(2, 2, (float) Math.cos(angle));
                rotating.setsomething(3, 3, 1);       
            }
        if(which == 2){
                rotating = new Matrix();
                rotating.setsomething(0, 0,(float) Math.cos(angle) );
                rotating.setsomething(1, 1, 1);
                rotating.setsomething(0, 2, (float) Math.sin(angle));
                rotating.setsomething(2, 0,(float) -Math.sin(angle));
                rotating.setsomething(2, 2, (float) Math.cos(angle));
                rotating.setsomething(3, 3, 1); 
            }
        if(which == 3){
                rotating = new Matrix();
                rotating.setsomething(2, 2, 1);
                rotating.setsomething(0, 0,(float) Math.cos(angle));
                rotating.setsomething(0, 1, (float) Math.sin(angle));
                rotating.setsomething(1, 0,(float) -Math.sin(angle));
                rotating.setsomething(1, 1, (float) Math.cos(angle));
                rotating.setsomething(3, 3, 1); 
            }
        for(int i = 1; i< points+1;i++ ){
                Point each = this.body.get(i);
                each = rotating.multiply(each);
                body.remove(i);
                body.put(i, each);
                } 
        
    }
    
    /**0 for minus, 1 for plus. **/
    public void scale(int how){
        Matrix scaling = new Matrix();
        if(how == 0){ 
            scaling = new Matrix( (float)0.9 ,(float) 0.9 ,(float) 0.9 );
            }
        if(how == 1){
            scaling = new Matrix( (float)1.1 ,(float) 1.1 ,(float) 1.1 );
        }
        for(int i = 1; i< points+1;i++ ){
                Point each = this.body.get(i);
                each = scaling.multiply(each);
                body.remove(i);
                body.put(i, each);
                } 
    }
    
    /**Reevaluates data in matrices. first argument 1 -> X, 2 -> T, 3 -> Z, 
     second argument 0 -> minus, 1 -> plus**/
    public void translate(int which, int direction){
        Matrix trans = new Matrix();
        if(which == 1){ 
            if(direction == 0){
                    trans = new Matrix( (float)1 ,(float) 1 ,(float) 1 );
                    trans.setsomething(0, 3, (float)-0.1);
                }
            if(direction == 1){
                    trans = new Matrix( (float)1 ,(float) 1 ,(float) 1 );
                    trans.setsomething(0, 3, (float)0.1);
                   }
            }
        if(which == 2){
            if(direction == 0){
                    trans = new Matrix( (float)1 ,(float) 1 ,(float) 1 );
                    trans.setsomething(1, 3, (float)-0.1);
                }
            if(direction == 1){
                    trans = new Matrix( (float)1 ,(float) 1 ,(float) 1 );
                    trans.setsomething(1, 3, (float)0.1);
                    }
            }
        if(which == 3){
            if(direction == 0){
                    trans = new Matrix( (float)1 ,(float) 1 ,(float) 1 );
                    trans.setsomething(2, 3, (float)-0.1);
                    }
            if(direction == 1){
                    trans = new Matrix( (float)1 ,(float) 1 ,(float) 1 );
                    trans.setsomething(2, 3, (float)0.1); 
                    }
             }
        for(int i = 1; i< points+1;i++ ){
               Point each = this.body.get(i);
               each = trans.multiply(each);
               body.remove(i);
               body.put(i, each);
                }
    
    }
    
    public void setColor(int r, int g, int b){
        cl = new Color(r,g,b);
    }
    
    
    void dispose(){
        cl = new Color(255,255,255);
        elight =false;
        light = new Matrix(0,0,0);
        points=0;
        planes= 0;
        body = new HashMap<Integer, Point>();
        plochy = new ArrayList<ArrayList<Integer>>();
        isrendered = false;
        hides = false;
        
    }
    
}
