import java.util.PriorityQueue;
import java.util.Scanner;
import java.io.File;
import java.io.FileNotFoundException;
import java.util.Collections;
import java.lang.Math;
/**
 *
 * @author HP
 */
public class PerformanceTest {

    /**
     * @param args the command line arguments
     * @throws java.io.FileNotFoundException
     */
    public static void main(String[] args) throws FileNotFoundException {

        Scanner scanner = new Scanner(new File("timing_test_2.txt"));
        int n =  (int) Math.pow(2,26);
        int[] arr = new int[n];
        int i=0;
        while(scanner.hasNextInt())
        {
            arr[i] = scanner.nextInt();
            i++;
        }
        
        PriorityQueue queue = new PriorityQueue(n, Collections.reverseOrder());
        long start = System.nanoTime();
        
        for (int k= 0; k<i; k++){
            queue.add(arr[k]);
        }
        Object[] newArray = queue.toArray();
        
        long end = System.nanoTime();
        long elapsedTime = end - start;
        double elapsedTimeInSecond = (double) elapsedTime / 1_000_000_000;
 
        System.out.println("\nTime passed:"+ elapsedTimeInSecond +" Seconds.");
        
    }
    
}