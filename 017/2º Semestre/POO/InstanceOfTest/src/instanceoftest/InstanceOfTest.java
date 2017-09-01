/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package instanceoftest;

/**
 *
 * @author suzukawa
 */
public class InstanceOfTest {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        Integer intObj = new Integer(123);
        Long longObj = new Long(1234567890);
        Double doubleObj = new Double(12.345);
        Boolean boolObj = new Boolean(true);
        
        Object[] objArray = {intObj, longObj, doubleObj, boolObj};
        
        for(int i = 0; i < objArray.length; i++) {
            if(objArray[i] instanceof Number) {
                System.out.println("Number");
            } else {
                System.out.println("not a number");
            }
        }
    }
    
}
