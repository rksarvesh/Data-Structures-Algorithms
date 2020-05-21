import java.io.*;
import java.util.*;
class RadixSort
{
   //Function to find Maximum number of Digits
   public static int findDigits(ArrayList<Integer> list)
   {
      int max=0;
      for(int i=0;i<list.size();i++)
      {
         if(list.get(i) > max)
         {
            max = list.get(i);
         }
      }
      int count = 0;
      while(max>0)
      {
         max = max/10;
         count++;
      }
      return count;
   }
   
   //Function to Perform Radix Sort
   public static void sort(ArrayList<Integer> list,int numDig)
   {
      //Creating an ArrayList of ArrayLists
      ArrayList<ArrayList<Integer>> sorter = new ArrayList<>(10);
      
      //Initializing the ArrayList with null
      for(int i=0;i<10;i++)
      {
         ArrayList<Integer> temp = new ArrayList<Integer>();
         temp.add(null);
         sorter.add(temp);
      }
      
      //n hold the position of the the digit upon which the list has to be sorted
      int n=1;
      //Divider is 1 less than the position and digit is the required digit
      int divider,digit;
      
      //Sorting for n digits
      while(n<=numDig)
      {
         //Indicating the Digit upon which sorting is taking place
         System.out.println("Sort by digit "+ n);
         //Calculating the divider
         divider = n-1;
         //Iterating the list
         for(int i = 0;i<list.size();i++)
         {
            //Finding the nth Digit
            int num = (int) (list.get(i) / Math.pow(10,divider));
            digit = num % 10;
            
            //Getting the List for that digit
            ArrayList<Integer> temp = sorter.get(digit);
            //Inserting the value
            temp.add(list.get(i));
            //Reinserting the list
            sorter.set(digit,temp);
         }
         
         //Printing and Re-Inserting the values based on the nth digit Sort
         int index = 0;
         for(int i = 0;i<sorter.size();i++)
         {
            ArrayList<Integer> temp = sorter.get(i);
            for(int j = 0;j<temp.size();j++)
            {
               if(temp.get(j) != null)
               {
                  System.out.print(temp.get(j) + " ");
                  list.set(index,temp.get(j));
                  index++;
               }
               else
               {
                  System.out.print("--");
               }
            }
            System.out.println();
         }
         
         //Re-Setting the Sorter List
         for(int i=0;i<10;i++)
         {
            ArrayList<Integer> temp = new ArrayList<Integer>();
            temp.add(null);
            sorter.set(i,temp);
         }
         //Incrementing the Position of sort
         n++;
      } 
   }
        
   public static void main(String[] args) throws FileNotFoundException, IOException
   {
      System.out.println("Program to Perform Radix Sort");
      File inputFile = new File("input.txt");
      Scanner sc = new Scanner(inputFile);
      ArrayList<Integer> arr = new ArrayList<>();
      int i = 0;
      while(sc.hasNextLine())
      {
         arr.add(sc.nextInt());
         i++;
      }
      
      //Find Maximum number of Digits
      int numDig = findDigits(arr);
      System.out.println("Maximum number of Digits = " + numDig);
      System.out.println();
      System.out.println("Performing Sort");
      
      //Perform Radix Sort
      sort(arr,numDig);
      
      //Declaring the BufferedWriter to write to the output file
      BufferedWriter out =new BufferedWriter(new FileWriter("output.txt"));
      //Printing the Final Sorted List
      System.out.println("Sorted List : ");
      for(int j=0;j<i;j++)
      {
         System.out.println(arr.get(j));
         //Writing to the output File
         out.write(String.valueOf(arr.get(j)));
         out.newLine();
      }
      out.close();
   }
}