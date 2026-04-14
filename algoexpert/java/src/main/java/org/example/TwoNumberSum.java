package org.example;

public class TwoNumberSum {
    private int[] array;
    private int targetSum;

    TwoNumberSum(int[] array, int targetSum) {
        this.array = array;
        this.targetSum = targetSum;
    }

    public int[] solutionOne(int [] array, int targetSum) {
        // O(n^2) time |  O(1) space
        for (var i = 0; i < array.length - 1 ; i++) {
            var targetNum  = targetSum - array[i];
            for (var j = i + 1; j < array.length; j++) {
                if (array[j] == targetNum)  {
                    return new int[]{array[i], array[j]};
                }
            }
        }
        return new int[0];
    }

    public void solutionTwo() {
    }
    public void solutionThree() {
    }

    public void run() {
      var result =  solutionOne(array, targetSum);
      System.out.println("Result is " + result[0] + ", " + result[1]);
    }
}