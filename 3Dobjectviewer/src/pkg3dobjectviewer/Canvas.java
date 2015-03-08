
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
        
        for(ArrayList<Integer> indexy : data.plochy){         
            ArrayList<Point> body = new ArrayList<Point>();
            
            for(int j = 0 ; j< indexy.size(); j++){
                body.add(data.getPoints(indexy.get(j)));
                }
            //nakresli rovinu z danych bodov; stred je 0,0 ; 1 == 100, teda -4,-3 je 0,0 v canvase a 4,3 je max   
            int xs[] = new int[body.size()];
            int ys[] = new int[body.size()];
            for(int k = 0; k<body.size(); k++){
                Point bod = body.get(k);
                xs[k]=(int) (bod.x *100 )+400;
                ys[k]=(int) (bod.y *100 )+300;
                }
             g.drawPolygon(xs, ys, body.size());       
            }
       
    }
}
