/*
 * Simple Implementation for Kruksal Minimum Spanning Tree
 * The input is taken from a CSV file which has the adjacency list of the graph.
 * Done By:- Sarvesh.K.Ramiya
 * Date : 7/25/19
 */
import java.util.*;
import java.io.*;

//Code for Disjoint sets has been taken from https://users.cs.fiu.edu/~weiss/dsaajava2/code/DisjSets.java

class DisjSets
{
    /*
     *
     * Construct the disjoint sets object.
     * @param numElements the initial number of disjoint sets.
     *
     */
    public DisjSets( int numElements )
    {
        s = new int [ numElements ];
        for( int i = 0; i < s.length; i++ )
            s[ i ] = -1;
    }

    /*
     *
     * Union two disjoint sets using the height heuristic.
     * For simplicity, we assume root1 and root2 are distinct
     * and represent set names.
     * @param root1 the root of set 1.
     * @param root2 the root of set 2.
     *
     */
    public void union( int root1, int root2 )
    {
        if( s[ root2 ] < s[ root1 ] )  // root2 is deeper
            s[ root1 ] = root2;        // Make root2 new root
        else
        {
            if( s[ root1 ] == s[ root2 ] )
                s[ root1 ]--;          // Update height if same
            s[ root2 ] = root1;        // Make root1 new root
        }
    }

    /*
     *
     * Perform a find with path compression.
     * Error checks omitted again for simplicity.
     * @param x the element being searched for.
     * @return the set containing x.
     *
     */
    public int find( int x )
    {
        if( s[ x ] < 0 )
            return x;
        else
            return s[ x ] = find( s[ x ] );
    }

    private int [ ] s;
}

public class Graphs
{
   //List to store the vertices and Edges
   private ArrayList<Vertex> vertexList;
   private ArrayList<Edge> EdgeList;
   
   //Default Constructor
   public Graphs()
   {
      vertexList = new ArrayList<Vertex>();
      EdgeList = new ArrayList<Edge>();
   }
   
   //Class for Vertex
   public class Vertex
   {
      private String name;
      private int num;
      public Vertex(String newName,int newNum)
      {
         name = newName;
         num = newNum;
      }
      public String getName()
      {
         return name;
      }
      public int getNum()
      {
         return num;
      }
   }
   
   //Class for Edges
   public class Edge implements Comparable<Edge>
   {
      private Vertex A;
      private Vertex B;
      private int weight;
      
      public Edge(Vertex newA,Vertex newB,int newWeight)
      {
         A = newA;
         B = newB;
         weight = newWeight;
      }
      
      public Vertex getA()
      {
         return A;
      }
      
      public Vertex getB()
      {
         return B;
      }
      public int getWeight()
      {
         return weight;
      }
      public int compareTo(Edge x)
      {
         if(this.weight > x.weight)
         {
            return 1;
         }
         else if(this.weight == x.weight)
         {
            return 0;
         }
         else 
         {
            return -1;
         }
      }
   }
   
   //Function to Add a Vertex
   public Vertex addVertex(String newName,int num)
   {
      boolean flag = true;
      for(int i=0;i<vertexList.size();i++)
      {
         if(((vertexList.get(i)).name).equals(newName))
         {
            flag = false;
         }
      }
      if(flag == true)
      {
         Vertex temp = new Vertex(newName,num);
         vertexList.add(temp);
         return temp;
      }
      return null;
   }
   
   //Function to get a Specific Vertex
   public Vertex getVertex(String newName)
   {
      for(int i=0;i<vertexList.size();i++)
      {
         if(((vertexList.get(i)).name).equals(newName))
         {
            return vertexList.get(i);
         }
      }
      return null;
   }
   
   //Function to add an edge
   public void addEdge(Vertex A,Vertex B,int weight)
   {
      boolean flag = true;
      Edge E = new Edge(A,B,weight);
      for(int i=0;i<EdgeList.size();i++)
      {
         if((EdgeList.get(i).B).equals(A) && (EdgeList.get(i).A).equals(B))
         {
            flag = false;
         }
      }
      if(flag == true)
      {
         EdgeList.add(E);
      }
   }
   
   //Function to print the graph
   public void printGraph()
   {
      System.out.println("Vertex List:-");
      System.out.println();
      for(int i = 0;i<vertexList.size();i++)
      {
         System.out.println((vertexList.get(i)).getName());
      }
      System.out.println();
      System.out.println("All Duplicate Edges have been removed since graph is undirected");
      System.out.println("Edge List:-");
      System.out.println(); 
      int sum =0;     
      for(int j = 0;j<EdgeList.size();j++)
      {
         System.out.println((((EdgeList.get(j)).A).getName()) + "==" + (((EdgeList.get(j)).weight))+ "==>" + (((EdgeList.get(j)).B).getName()));
         sum += (EdgeList.get(j)).weight;
      }
      System.out.println();
      System.out.println("Sum of all Edge Weights in the Graph = " + sum);
   }
   
   //Function to Find the Minimum Spanning Tree
   public void kruksal()
   {
      int accepted = 0;
      int sum = 0;
      //Sets of Vertices
      DisjSets ds = new DisjSets(vertexList.size());
      //Priority Queue for Edges based on Weight
      PriorityQueue<Edge> pq = new PriorityQueue<>(EdgeList);
      //Edges of the Minimum spanning tree
      ArrayList<Edge> result = new ArrayList<>();
      Edge e;
      while(accepted< vertexList.size()-1)
      {
         //Getting the minimum edges
         e=pq.poll();
         //Checking if it causes the cycle
         int aset = ds.find((e.A).getNum());
         int bset = ds.find((e.B).getNum());
         if(aset != bset)
         {
            //If no cycle then adding the edge
            accepted++;
            result.add(e);
            sum += e.weight;
            ds.union(aset,bset);
         }
      }
      System.out.println();
      //Printing the tree
      System.out.println("Minimum Spanning Tree (Answer) :-");
      System.out.println();
      for(int j = 0;j<result.size();j++)
      {
         System.out.println((((result.get(j)).A).getName()) + "==" + (((result.get(j)).weight))+ "==>" + (((result.get(j)).B).getName()));
      }
      System.out.println();
      System.out.println("Sum of All Distances in the Minimum Spanning Tree = " + sum);
   }
   
   //Main Function
   public static void main(String[] args) throws FileNotFoundException, IOException
   {
      Graphs g = new Graphs();
      ArrayList<ArrayList<String>> data = new ArrayList<>();
      BufferedReader csvReader = new BufferedReader(new FileReader("kruksal_data.csv"));
      String row;
      int i=0;
      //Reading the Vertices
      while((row =  csvReader.readLine()) != null)
      {
         String[] data1 = (row.split(","));
         g.addVertex(data1[0],i);
         i++;
      }
      csvReader.close();
      BufferedReader csvReader1 = new BufferedReader(new FileReader("kruksal_data.csv"));
      int j=0;
      //Reading the edges
      while((row = csvReader1.readLine()) != null)
      {
         String[] data1 = (row.split(","));
         Vertex A = g.getVertex(data1[0]);
         for(int k=1;k<data1.length;k++)
         {
            Vertex B = g.getVertex(data1[k++]);
            int weight = Integer.parseInt(data1[k]);
            g.addEdge(A,B,weight);
         }
      }
      
      //Printing the Graph
      g.printGraph();
      
      //Printing the Minimum Spanning tree
      g.kruksal();
   }
}
