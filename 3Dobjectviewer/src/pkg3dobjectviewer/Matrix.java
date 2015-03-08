
package pkg3dobjectviewer;

public class Matrix {
    float [][] array;
    
    Matrix(float[][] in){
        this.array = in;    
    }
    
    Matrix(){
        this.array = new float[4][4];
        for(int i = 0; i < 4;i++){
            for(int j = 0; j< 4; j++){
                array[i][j] = 0;
                }
            }
    }
    Matrix(float x, float y, float z){
        this.array = new float[4][4];
        for(int i = 0; i < 4;i++){
            for(int j = 0; j< 4; j++){
                array[i][j] = 0;
                }
            }
        array[0][0] = x;
        array[1][1] = y;
        array[2][2] = z;
        array[3][3] = 1;
    }
    
   public void setsomething(int row, int col, float val ){
        this.array[row][col] = val;
   }
   //**mat2 is umltiplied by matrix, on which function si called.**//
   Matrix multiply( Matrix mat2){
       float[][] toret = new float[array.length][array.length];
       for(int i = 0; i < array.length; i++ ){
           for(int j = 0; j<array.length ; j++){
                  float result = 0;
                  for(int k =0; k< array.length; k++){
                      result+=this.array[k][j]*mat2.array[i][k] ;
                  }
                  toret[i][j] = result;
                 }
            }
       return (new Matrix(toret));
   }
   
   
   Point multiply(Point p){ 
     float nx = 0;
     nx+= p.x * this.array[0][0];
     nx+= p.y * this.array[0][1];
     nx+= p.z * this.array[0][2];
     nx+= p.idk * this.array[0][3];
     float ny = 0;
     ny+= p.x * this.array[1][0];
     ny+= p.y * this.array[1][1];
     ny+= p.z * this.array[1][2];
     ny+= p.idk * this.array[1][3];
     float nz = 0;
     nz+= p.x * this.array[2][0];
     nz+= p.y * this.array[2][1];
     nz+= p.z * this.array[2][2];
     nz+= p.idk * this.array[2][3];
   return new Point(nx,ny,nz);
   }
 
}
