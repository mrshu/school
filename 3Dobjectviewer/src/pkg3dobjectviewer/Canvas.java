
package pkg3dobjectviewer;

import java.awt.Color;
import java.awt.Graphics;
import java.awt.Polygon;
import java.util.ArrayList;
import javax.swing.BorderFactory;
import javax.swing.JPanel;


public class Canvas extends JPanel {    
   MyFrame frame;
   Data data;
   
   
   public Canvas(MyFrame inframe, Data in){
       this.setBorder(BorderFactory.createLineBorder(Color.black));
       this.setBackground(Color.white);
       this.frame = inframe;
       this.data = in; 
   }
   
    @Override
    public void paintComponent(Graphics g) {
        super.paintComponent(g);
        int i = 0;
        for(ArrayList<Integer> indexy : data.plochy){         
            ArrayList<Point> body = new ArrayList<Point>();
            
            for(int j = 0 ; j< indexy.size(); j++){
                body.add(data.getPoints(indexy.get(j)));
                }
            //draws plane from the points; center is 0,0 ; 1 == 100, so -4,-3 is min and 4,3 is max
                int xs[] = new int[body.size()];
                int ys[] = new int[body.size()];
                float zs[] = new float[body.size()];
                for(int k = 0; k<body.size(); k++){
                    Point bod = body.get(k);
                    xs[k]=(int) (bod.x *100 )+400;
                    ys[k]=(int) -(bod.y *100 )+300;
                    }
                if (data.hides==false){ g.drawPolygon(xs, ys, body.size());} 
                else{ 
                    Point p0 = body.get(0);
                    Point p1 = body.get(1);
                    Point p2 = body.get(2);
                    float[] vectorA =  {p2.x - p1.x , p2.y-p1.y , p2.z-p1.z }; 
                    float[] vectorB =  {p2.x - p0.x , p2.y-p0.y , p2.z-p0.z }; 
                    float[] normal = { vectorA[1]*vectorB[2] - vectorA[2]*vectorB[1] ,
                                       vectorA[2]*vectorB[0] - vectorA[0]*vectorB[2] ,
                                       vectorA[0]*vectorB[1] - vectorA[1]*vectorB[0]     };
                    if (normal[2]>=0){
                        g.setColor(data.getPlaneColor(i));
                        g.fillPolygon(xs, ys, body.size());
                        g.setColor(Color.BLACK);
                        g.drawPolygon(xs, ys, body.size());}
                }
                i++;
             }   
    } 
}

// z-buffering
/* Color[][]image = new Color[800][600];
            for(int x = 0;  x<800 ; x++){ 
                    for(int y = 0;  y<600 ; y++){ 
                        image[x][y] = Color.WHITE;
                        }
                    }
            float [][] zbuffer = new float[800][600];
            for(int x = 0;  x<800 ; x++){ 
                    for(int y = 0;  y<600 ; y++){ 
                        zbuffer[x][y] = 1000000;
                        }
                    }
            int i = 0;
            for(ArrayList<Integer> indexy : data.plochy){         
                ArrayList<Point> body = new ArrayList<Point>();
            
                for(int j = 0 ; j< indexy.size(); j++){
                    body.add(data.getPoints(indexy.get(j))); 
                 }
                int xs[] = new int[body.size()];
                int ys[] = new int[body.size()];
                for(int k = 0; k<body.size(); k++){
                    Point bod = body.get(k);
                    xs[k]=(int) (bod.x *100 )+400;
                    ys[k]=(int) (bod.y *100 )+300;
                    }
                Polygon pol = new Polygon(xs,ys,body.size());
                for(int x = 0;  x<800 ; x++){ 
                    for(int y = 0;  y<600 ; y++){ 
                        float depth =0; // TODO count depth
                       if  (pol.contains(x, y) && depth < zbuffer[x][y]){
                           image[x][y] = data.shades.get(i);
                            }
                        
                        }
                    }
                 for(int x = 0;  x<800 ; x++){ 
                    for(int y = 0;  y<600 ; y++){ 
                        g.drawLine(x, y, x, y);
                        }
                    }  
               } */