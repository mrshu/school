package pkg3dobjectviewer;

import java.awt.Color;
import java.util.ArrayList;
import java.util.HashMap;

public class Data {

    boolean isrendered;
    boolean hides;
    boolean elight; // exist light  
    int points;
    int planes;
    Point light;
    Color cl;
    HashMap<Integer, Point> body;
    ArrayList<ArrayList<Integer>> plochy;
    ArrayList<Color> shades;
    float posx;
    float posy;
    float posz;

    Data() {
        isrendered = false;
        hides = false;
        elight = false;
        cl = new Color(255, 255, 255);
        light = new Point(0, 0, 0);
        points = 0;
        planes = 0;
        body = new HashMap<Integer, Point>();
        plochy = new ArrayList<ArrayList<Integer>>();
        shades = new ArrayList<Color>();
        posx = 0;
        posy = 0;
        posz = 0;
    }

    public void addPoint(Point in) {
        points++;              
        body.put(points, in);
    }

    public void createPlane(ArrayList list) {
        plochy.add(list);
        planes++;
        shades.add(cl);
    }

    public Point getPoints(int key) {
        return body.get(key);
    }

    public ArrayList<Integer> getPlane(int i) {
        return plochy.get(i);
    }

    public Color getPlaneColor(int i) {
        return shades.get(i);
    }

    public int numofPoints() {
        return this.points;
    }

    public int numofPlanes() {
        return this.planes;
    }

    public void setlight(Point toset) {
        elight = true;
        light = toset;
        if (hides == false) {
            hide();
        }
        for(ArrayList<Integer> indexy : plochy){         
            ArrayList<Point> body = new ArrayList<Point>();
            for(int j = 0 ; j< indexy.size(); j++){
                body.add(getPoints(indexy.get(j)));
                }
        
        Point p0 = body.get(0);
        Point p1 = body.get(1);
        Point p2 = body.get(2);
        float[] vectorA =  {p1.x - p0.x , p1.y-p0.y , p1.z-p0.z }; 
        float[] vectorB =  {p2.x - p0.x , p2.y-p0.y , p2.z-p0.z }; 
        float[] normal = { vectorA[1]*vectorB[2] - vectorA[2]*vectorB[1] ,
                           vectorA[2]*vectorB[0] - vectorA[0]*vectorB[2] ,
                           vectorA[0]*vectorB[1] - vectorA[1]*vectorB[0]     };
        float tonorm = (float) Math.sqrt(normal[0]*normal[0] + normal[1]*normal[1]+normal[2]*normal[2]);
        }
    }

    public void unhide() {
        this.hides = false;
    }

    /**
     * Hides invisible faces.
     */
    public void hide() {
        hides = true;
        for (int i = 0; i < this.planes; i++) {
            this.shades.add(i, Color.WHITE);
        }
    }

    /**
     * Render object with given color. *
     */
    public void render(int r, int g, int b) {
        hides = true;
        cl = new Color(r, g, b);
        for (int i = 0; i < this.planes; i++) {
            this.shades.set(i, cl);
        }
    }

    /**
     * Reevaluates data in matrices. first argument 1 -> X, 2 -> Y, 3 -> Z, 
     *
     */
    public void Rotate(int which, double angle) {
        Matrix rotating = new Matrix();
        float oldposx = posx;
        float oldposy = posy;
        float oldposz = posz;
        translate(1,-posx);
        translate(2,-posy);
        translate(3,-posz);
        if (which == 1) {
            
            rotating = new Matrix();
            rotating.setsomething(0, 0, 1);
            rotating.setsomething(1, 1, (float) Math.cos(angle));
            rotating.setsomething(1, 2, (float) Math.sin(angle));
            rotating.setsomething(2, 1, (float) -Math.sin(angle));
            rotating.setsomething(2, 2, (float) Math.cos(angle));
            rotating.setsomething(3, 3, 1);
            
        }
        if (which == 2) {
            rotating = new Matrix();
            rotating.setsomething(0, 0, (float) Math.cos(angle));
            rotating.setsomething(1, 1, 1);
            rotating.setsomething(0, 2, (float) Math.sin(angle));
            rotating.setsomething(2, 0, (float) -Math.sin(angle));
            rotating.setsomething(2, 2, (float) Math.cos(angle));
            rotating.setsomething(3, 3, 1);
        }
        if (which == 3) {
            rotating = new Matrix();
            rotating.setsomething(2, 2, 1);
            rotating.setsomething(0, 0, (float) Math.cos(angle));
            rotating.setsomething(0, 1, (float) Math.sin(angle));
            rotating.setsomething(1, 0, (float) -Math.sin(angle));
            rotating.setsomething(1, 1, (float) Math.cos(angle));
            rotating.setsomething(3, 3, 1);
        }
        for (int i = 1; i < points + 1; i++) {
            Point each = this.body.get(i);
            each = rotating.multiply(each);
            body.remove(i);
            body.put(i, each);
        }
        translate(1,oldposx);
        translate(2,oldposy);
        translate(3,oldposz);
       // setlight(light);
    }

    /**
     * 0 for minus, 1 for plus. *
     */
    public void scale(int how) {
        Matrix scaling = new Matrix();
        if (how == 0) {
            scaling = new Matrix((float) 0.9, (float) 0.9, (float) 0.9);
        }
        if (how == 1) {
            scaling = new Matrix((float) 1.1, (float) 1.1, (float) 1.1);
        }
        for (int i = 1; i < points + 1; i++) {
            Point each = this.body.get(i);
            each = scaling.multiply(each);
            body.remove(i);
            body.put(i, each);
        }
    }

    /**
     * Reevaluates data in matrices. first argument is for direction 1 -> X, 2 -> Y, 3 -> Z,
     * second is for size of vector*
     */
    public void translate(int direction, float amount) {
        Matrix trans = new Matrix();
        if (direction == 1) {
            trans = new Matrix((float) 1, (float) 1, (float) 1);
            trans.setsomething(0, 3, amount);
            posx += amount;
        }
        if (direction == 2) {
            trans = new Matrix((float) 1, (float) 1, (float) 1);
            trans.setsomething(1, 3, amount);
            posy += amount;
        }
        if (direction == 3) {
            trans = new Matrix((float) 1, (float) 1, (float) 1);
            trans.setsomething(2, 3, amount);
            posz += amount;
        }
        for (int i = 1; i < points + 1; i++) {
            Point each = this.body.get(i);
            each = trans.multiply(each);
            body.remove(i);
            body.put(i, each);
        }

    }

    void dispose() {
        cl = new Color(255, 255, 255);
        elight = false;
        light = new Point(0, 0, 0);
        points = 0;
        planes = 0;
        body = new HashMap<Integer, Point>();
        plochy = new ArrayList<ArrayList<Integer>>();
        isrendered = false;
        hides = false;
        posx = 0;
        posy = 0;
        posz = 0;
    }
}
