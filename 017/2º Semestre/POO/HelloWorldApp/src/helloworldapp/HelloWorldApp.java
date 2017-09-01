/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

package helloworldapp;

import java.util.Scanner;

/**
 *
 * @author suzukawa
 */
public class HelloWorldApp {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        
        int[] nline = new int[2];
        int[] ncol  = new int[2];
        
        for(int i = 0; i < 2; i++) {
            System.out.print("Digite o num de linhas da " + (i+1) + "ª matriz: ");
            nline[i] = sc.nextInt();
            
            System.out.print("Digite o num de colunas da " + (i+1) + "ª matriz: ");
            ncol[i] = sc.nextInt();
        }
        
        if(nline[1] != ncol[0]) {
            System.out.println("Erro: Matrizes incompatíveis.");
            return;
        }
        
        int[][] matrix1 = new int[nline[0]][ncol[0]];
        int[][] matrix2 = new int[nline[1]][ncol[1]];
        
        for(int i = 0; i < nline[0]; i++) {
            for(int j = 0; j < ncol[0]; j++) {
                System.out.print("Digite o elemento de endereço (" + i + ", " + j + ") da 1ª matriz: ");

                matrix1[i][j] = sc.nextInt();
            }
        }

        for(int i = 0; i < nline[1]; i++) {
            for(int j = 0; j < ncol[1]; j++) {
                System.out.print("Digite o elemento de endereço (" + i + ", " + j + ") da 2ª matriz: ");

                matrix2[i][j] = sc.nextInt();
            }
        }
        
        int[][] matrixr = new int[nline[0]][ncol[1]]; 
        
        for(int i = 0; i < nline[0]; i++) {
            for(int j = 0; j < ncol[1]; j++) {
                matrixr[i][j] = 0;
                for(int k = 0; k < nline[1]; k++) {
                    matrixr[i][j] += matrix1[i][k] * matrix2[k][j];
                }
            }
        }
        
        for(int i = 0; i < nline[0]; i++) {
            for(int j = 0; j < ncol[1]; j++) {
                System.out.print(matrixr[i][j] + " ");
            }
            System.out.print("\n");
        }
    }
    
}
