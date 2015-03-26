
package pkg3dobjectviewer;

import java.awt.Graphics;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.File;
import java.io.FileFilter;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.Locale;
import java.util.Scanner;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.swing.JButton;
import javax.swing.JFileChooser;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.JTextField;
import javax.swing.SwingUtilities;


public class Main {
    public static void main(String[] args) {
        SwingUtilities.invokeLater(new Runnable() {

            @Override
            public void run() {
                MyFrame frame = new MyFrame();
                frame.setVisible(true);
            }
        });
    }    
}

 class MyFrame extends JFrame {
   Data data;
   final Canvas canvas;
   JButton load;
   JButton render;
   JButton light;
   JButton hide;
   JButton plusx;
   JButton minusx;
   JButton plusy;
   JButton minusy;
   JButton plusz;
   JButton minusz;
   JButton rotpz;
   JButton rotmz;
   JButton rotpy;
   JButton rotmy;
   JButton rotpx;
   JButton rotmx;
   JButton plusscale;
   JButton minusscale;
   JButton unhide;
  
  
   MyFrame(){
        super("3Dviewer");
        this.setSize(1200, 700);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        data = new Data();
        
        
        // Layout & buttons
        this.setLayout(null);
        canvas = new Canvas(this, this.data);
        canvas.setSize(800, 600);
        canvas.setLocation(10, 10);
        add(canvas);
        
        load = new JButton("Load");
        load.setSize(100, 50);
        load.setLocation(850, 50);
        this.add(load);
        
        render = new JButton("Render");
        render.setSize(100, 50);
        render.setLocation(850, 150);
        this.add(render);
        final JTextField fieldR = new JTextField("R");
        final JTextField fieldG = new JTextField("G");
        final JTextField fieldB = new JTextField("B");
        fieldR.setSize(100, 20);
        fieldG.setSize(100, 20);
        fieldB.setSize(100, 20);
        fieldR.setLocation(960, 150);
        fieldG.setLocation(960, 170);
        fieldB.setLocation(960, 190);
        this.add(fieldR);
        this.add(fieldG);
        this.add(fieldB);
        
        
        hide = new JButton("Hide");
        hide.setSize(100, 50);
        hide.setLocation(850, 250);
        this.add(hide);
        
        unhide = new JButton("Unhide");
        unhide.setSize(100, 50);
        unhide.setLocation(970, 250);
        this.add(unhide);
        
        light = new JButton("Light");
        light.setSize(100, 50);
        light.setLocation(850, 350);
        this.add(light);
        final JTextField fieldx = new JTextField("X");
        final JTextField fieldy = new JTextField("Y");
        final JTextField fieldz = new JTextField("Z");
        fieldx.setSize(100, 20);
        fieldy.setSize(100, 20);
        fieldz.setSize(100, 20);
        fieldx.setLocation(960, 350);
        fieldy.setLocation(960, 370);
        fieldz.setLocation(960, 390);
        this.add(fieldx);
        this.add(fieldy);
        this.add(fieldz);        
        
        plusx = new JButton("+X");
        plusx.setSize(60, 50);
        plusx.setLocation(850, 450);
        this.add(plusx);
        minusx = new JButton("-X");
        minusx.setSize(60, 50);
        minusx.setLocation(920, 450);
        this.add(minusx);
        
        plusy = new JButton("+Y");
        plusy.setSize(60, 50);
        plusy.setLocation(850, 510);
        this.add(plusy);
        minusy = new JButton("-Y");
        minusy.setSize(60, 50);
        minusy.setLocation(920, 510);
        this.add(minusy);
        
        plusz = new JButton("+Z");
        plusz.setSize(60, 50);
        plusz.setLocation(850, 570);
        this.add(plusz);
        minusz = new JButton("-Z");
        minusz.setSize(60, 50);
        minusz.setLocation(920, 570);
        this.add(minusz);
        
        rotpz = new JButton("Rot +Z");
        rotpz.setSize(80, 50);
        rotpz.setLocation(1000, 570);
        this.add(rotpz);
        rotmz = new JButton("Rot -Z");
        rotmz.setSize(80, 50);
        rotmz.setLocation(1090, 570);
        this.add(rotmz);
        
        rotpx = new JButton("Rot +X");
        rotpx.setSize(80, 50);
        rotpx.setLocation(1000, 450);
        this.add(rotpx);
        rotmx = new JButton("Rot -X");
        rotmx.setSize(80, 50);
        rotmx.setLocation(1090, 450);
        this.add(rotmx);
        
        rotpy = new JButton("Rot +Y");
        rotpy.setSize(80, 50);
        rotpy.setLocation(1000, 510);
        this.add(rotpy);
        rotmy = new JButton("Rot -Y");
        rotmy.setSize(80, 50);
        rotmy.setLocation(1090, 510);
        this.add(rotmy);
        
        plusscale = new JButton("+");
        plusscale.setSize(80, 50);
        plusscale.setLocation(1000, 50);
        this.add(plusscale);
        minusscale = new JButton("-");
        minusscale.setSize(80, 50);
        minusscale.setLocation(1090, 50);
        this.add(minusscale);
        
        
        // Funkcionalita
        
        load.addActionListener(new ActionListener() {

            @Override
            public void actionPerformed(ActionEvent event) {
                JFileChooser chooser = new JFileChooser();
                chooser.showOpenDialog(canvas);
                File file = chooser.getSelectedFile();
                file.setReadable(true);
                data.dispose();
                try {
                    Scanner scan = new Scanner(file).useLocale(Locale.ENGLISH);
                    while(scan.hasNextLine() && scan.hasNext()){
                        String co = scan.next();
                        switch (co){
                            case "v": 
                                float x = scan.nextFloat();
                                float y = scan.nextFloat();
                                float z = scan.nextFloat();
                                Point toadd = new Point(x,y,z);
                                data.addPoint(toadd);
                                break;
                            case "f":
                                 ArrayList<Integer> points = new ArrayList<Integer>();
                                 while (scan.hasNextInt()){
                                     int next = scan.nextInt();
                                     points.add(next);
                                }
                                 data.createPlane(points);                               
                                break;
                            default: scan.nextLine();                               
                        }                     
                    }
                } catch (FileNotFoundException ex) {
                    Logger.getLogger(MyFrame.class.getName()).log(Level.SEVERE, null, ex);
                }
              repaint();  
            }
        });
        
             
        render.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent event) {
                int R = Integer.parseInt(fieldR.getText());
                int G = Integer.parseInt(fieldG.getText());
                int B = Integer.parseInt(fieldB.getText());
                data.render(R, G, B);
                repaint();
            }
        });
        
        light.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent event) {
                int x = Integer.parseInt(fieldx.getText());
                int y = Integer.parseInt(fieldy.getText());
                int z = Integer.parseInt(fieldz.getText());
                Point tosend = new Point(-x,-y,-z);
                data.setlight(tosend);
                repaint();
            }
        });
                      
        hide.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent event) {
                data.hide();
                repaint();
            }
        });
        
        unhide.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent event) {
                data.unhide();
                repaint();
            }
        });
            
        plusx.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent event) {
                data.translate(1, (float) 0.1);
                repaint();
            }
        });
        
        minusx.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent event) {
                data.translate(1, (float) -0.1);
                repaint();
            }
        });
        
        plusy.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent event) {
                data.translate(2, (float) 0.1);
                repaint();
            }
        });
        
        minusy.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent event) {
                data.translate(2,(float) -0.1);
                repaint();
            }
        });
        
        plusz.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent event) {
                data.translate(3,(float) 0.1);
                repaint();
            }
        });
        
        minusz.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent event) {
                data.translate(3, (float) -0.1);
                repaint();
            }
        });
        
        rotpz.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent event) {
                data.Rotate(3, Math.PI/36);
                repaint();
            }
        });
        
        rotmz.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent event) {
                data.Rotate(3, -Math.PI/36);
                repaint();
            }
        });
        
        rotpx.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent event) {
                data.Rotate(1, Math.PI/36);
                repaint();
            }
        });
        
        rotmx.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent event) {
                data.Rotate(1, -Math.PI/36);
                repaint();
            }
        });
        
        rotpy.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent event) {
                data.Rotate(2, Math.PI/36);
                repaint();
            }
        });
        
        rotmy.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent event) {
                data.Rotate(2, -Math.PI/36);
                repaint();
            }
        });
        
        plusscale.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent event) {
                data.scale(1);
                repaint();
            }
        });
        
        minusscale.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent event) {
                data.scale(0);
                repaint();
            }
        });      
     }
 }
