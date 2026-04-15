package org.example;

import java.util.Arrays;
import java.util.HashSet;
import java.util.Set;

public class TwoNumberSum {
    private int[] array;
    private int targetSum;

    TwoNumberSum(int[] array, int targetSum) {
        this.array = array;
        this.targetSum = targetSum;
    }

    public int[] solution1(int[] array, int targetSum) {
        // O(n^2) time |  O(1) space
        for (var i = 0; i < array.length - 1; i++) {
            var targetNum = targetSum - array[i];
            for (var j = i + 1; j < array.length; j++) {
                if (array[j] == targetNum) {
                    return new int[]{array[i], array[j]};
                }
            }
        }
        return new int[0];
    }

    public int[] solution2(int[] array, int targetSum) {
        // O(n) time | O(n) space
        Set<Integer> nums = new HashSet<>();

        for (int num : array) {
            int potentialMatch = targetSum - num;
            if (nums.contains(potentialMatch)) {
                return new int[]{potentialMatch, num};
            }

            nums.add(num);
        }

        return new int[0];
    }

    public int[] solution3(int[] array, int targetSum) {
        Arrays.sort(array);
        var left = 0;
        var right = array.length - 1;
        while(left < right) {
           var sum = array[left]  + array[right];
           if (sum == targetSum) return new int[] {array[left], array[right]};
           if (sum > targetSum) {
               right--;
           } else {
               left++;
           }
        }

        return new int[0];
    }

    public void printResults(int[]array, String name) {
        System.out.println("result " + name + ": " + Arrays.toString(array));
    }

    public void run() {
        System.out.println("Array: " + array);
        System.out.println("targetSum: " + targetSum);

        printResults(solution1(array, targetSum), "1");
        printResults(solution2(array, targetSum), "2");
        printResults(solution3(array, targetSum), "3");
    }
}